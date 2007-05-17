#ifndef SIMPLE_CACHE_HPP
#define SIMPLE_CACHE_HPP

#include "../graph/algorithms.hpp"
#include "../misc/bstreambuf.hpp"
#include <stdexcept>
#include <ext/hash_map>
#include <cstdlib>
#include <climits>

/**
 * This file implements a simple cache for storing graph_keys and
 * their polynomials.  It's quite ugly in places, and I wonder how
 * this could be improved.
 */

struct cache_node {
  struct cache_node *next;  
  struct cache_node *prev;  
  unsigned int hit_count; 
  // graph key comes here
  // followed by polynomial
};

class simple_cache_iterator {
private:
  struct cache_node *ptr;
public:
  simple_cache_iterator(struct cache_node *p) : ptr(p) {}
  
  void operator++() { 
    unsigned char *p = (unsigned char *) ptr;
    unsigned int header_size = sizeof(struct cache_node);
    unsigned int key_size = sizeof_graph_key(p + header_size);
    unsigned int poly_size = sizeof_compact_poly(p + header_size + key_size);
    p += header_size + key_size + poly_size;
    ptr = (struct cache_node *) p;
  }

  simple_cache_iterator operator++(int) { 
    simple_cache_iterator tmp(*this);
    ++(*this);
    return tmp;
  }
  
  // the following two methods should be
  // replaced with an operator*() when
  // I implement a graph_key class

  unsigned char *key() {
    unsigned char *p = (unsigned char *) ptr;
    return p + sizeof(struct cache_node);
  }

  unsigned int hit_count() {
    return ptr->hit_count;
  }

  bool operator==(simple_cache_iterator const &o) const {
    return ptr == o.ptr;
  }

  bool operator!=(simple_cache_iterator const &o) const {
    return ptr != o.ptr;
  }
};

class simple_cache {
public:
  typedef simple_cache_iterator iterator;
private:
  unsigned int hits;
  unsigned int misses;
  unsigned int collisions;
  unsigned int dealloced;  // for computing fragmentation
  unsigned int numentries; 
  struct cache_node* buckets;    // start of bucket array
  unsigned int nbuckets;         // number of buckets
  unsigned char *start_p;        // buffer start ptr
  unsigned char *next_p;         // buffer next ptr
  unsigned int bufsize;
  float replacement;
  bool random_replacement;
public:
  // max_size in bytes
  simple_cache(size_t max_size, size_t nbs = 10000) {
    hits = 0;
    misses = 0;
    collisions = 0;
    dealloced = 0;
    bufsize = max_size;
    nbuckets = nbs;
    buckets = create_bucket_array(nbs);
    start_p = new unsigned char[max_size];
    next_p = start_p;
    random_replacement=false;
    replacement=0.3;
  }
  
  ~simple_cache() { 
    delete [] buckets; 
    delete [] start_p; 
  }
    
  int num_hits() { return hits; }
  int num_misses() { return misses; }
  int num_entries() { return numentries; }
  int num_collisions() { return collisions; }
  int num_buckets() { return nbuckets; }

  // get space used by cache in bytes
  unsigned int size() {  return next_p - start_p; }
  // get available space in bytes
  unsigned int capacity() { return bufsize; }

  unsigned int min_bucket_size() {
    unsigned int r = UINT_MAX;
    for(unsigned int i=0;i!=nbuckets;++i) {
      r = std::min(r,bucket_length(i));
    }
    return r;
  }
  
  unsigned int max_bucket_size() {
    unsigned int r = 0;
    for(unsigned int i=0;i!=nbuckets;++i) {
      r = std::max(r,bucket_length(i));
    }
    return r;
  }

  unsigned int count_buckets_sized(int l, int u) {
    unsigned int c = 0;
    for(unsigned int i=0;i!=nbuckets;++i) {
      unsigned int bl = bucket_length(i);
      if(bl >= l && bl <= u) { c ++; }
    }
    return c;
  }

  unsigned int bucket_length(unsigned int b) {
    struct cache_node *ptr = buckets[b].next;
    int len=0;
    while(ptr != NULL) {
      ptr = ptr->next;
      len++;
    }
    return len;
  }

  double density() {
    size_t used = next_p - start_p;
    return ((double)numentries) / used;
  }

  void clear() {
    // reset next pointer
    next_p = start_p;
    // empty all buckets
    for(int i=0;i!=nbuckets;++i) { 
      buckets[i].next=NULL; 
      buckets[i].prev=NULL; 
    }    
    // done
  }

  void reset_stats() {
    hits = 0;
    misses = 0;
    collisions = 0;
  }

  void set_replacement(float f) {
    replacement = f;
  }

  void set_random_replacement() {
    random_replacement=true;
  }

  void resize(size_t max_size) {
    unsigned int old_size = next_p - start_p;
    unsigned char *ostart_p = start_p;
    if(old_size > max_size) {
      throw std::runtime_error("cache contains to much data to to be resized!");
    } 
    bufsize = max_size;
    start_p = new unsigned char[max_size];

    // update simple pointers
    unsigned int diff = start_p - ostart_p;   
    next_p = next_p + diff;

    // first, copy old data into new location
    memcpy(start_p,ostart_p,old_size);
    // now, update pointers and links    
    for(int i=0;i!=nbuckets;++i) {
      if(buckets[i].next != NULL) {
	buckets[i].next += diff;
	struct cache_node *ptr = buckets[i].next;
	int len=0;
	while(ptr != NULL) {
	  unsigned char *p = (unsigned char *) ptr->next;
	  p += diff;
	  ptr->next = (struct cache_node *) p;
	  ptr = ptr->next;
	}
      }
    }
    // done ?
    delete [] ostart_p;
  }

  void rebucket(size_t nbs) {
    struct cache_node* bs = create_bucket_array(nbs);

    // now, rebucket everything
    for(int i=0;i!=nbuckets;++i) {
      struct cache_node *nptr, *ptr = buckets[i].next;
      int len=0;
      while(ptr != NULL) {
	nptr = ptr->next;
	unsigned char *key_p = (unsigned char *) ptr;
	key_p += sizeof(struct cache_node);
	unsigned int b = hash_graph_key(key_p) % nbs; 
	ptr->next = bs[b].next;
	ptr->prev = &(bs[b]);
	if(ptr->next != NULL) {
	  ptr->next->prev = ptr;
	}
	bs[b].next = ptr;
	ptr = nptr;
      }
    }

    delete [] buckets; // free up space
    buckets = bs;      // assign new buckets
    nbuckets = nbs;

  }

  template<class P>
  bool lookup(unsigned char const *key, P &dst) {
    // identify containing bucket
    unsigned int bucket = hash_graph_key(key) % nbuckets;
    struct cache_node *node_p = buckets[bucket].next;
    // traverse bucket looking for match
    while(node_p != NULL) {
      unsigned char *key_p = (unsigned char *) node_p;
      key_p += sizeof(struct cache_node);
      if(compare_graph_keys(key,key_p)) {
	// match made
	size_t sizeof_key = sizeof_graph_key(key_p);
	dst = read_compact_poly<P>(key_p + sizeof_key);
	// update hit count
	node_p->hit_count++;
	// move node to front of bucket
	remove_node(node_p);
	insert_node_after(node_p,&(buckets[bucket]));
	// update hit count and we're done!
	hits++;
	return true;
      }
      collisions++;
      node_p = node_p->next;
    }
    misses++;
    return false;    
  }

  template<class P>  
  void store(unsigned char const *key, P const &p) {
    // allocate space for new node
    unsigned int sizeof_key = sizeof_graph_key(key);
    // convert poly into stream
    static bstreambuf bout;
    bout.reset();
    bout << p;
    // allocate space in cache
    unsigned char *ptr = alloc_node(sizeof(struct cache_node) + sizeof_key + bout.size());  
    struct cache_node *node_p = (struct cache_node *) ptr;
    unsigned char *key_p = ptr + sizeof(struct cache_node);
    // now put key at head of its bucket list
    unsigned int bucket = hash_graph_key(key) % nbuckets;
    insert_node_after(node_p,&(buckets[bucket]));
    // init hit count
    node_p->hit_count = 0;
    // load the key into the node
    memcpy(key_p,key,sizeof_key);
    // load poly stream into node
    memcpy(key_p+sizeof_key,bout.c_ptr(),bout.size());
    // update stats
    numentries++;
    // done.
  }  

  // methods for accessing the internal state

  iterator begin() { return iterator((struct cache_node *) start_p); }
  iterator end() { return iterator((struct cache_node *) next_p); }

private:
  simple_cache(simple_cache const &src) {
  }  

  inline unsigned char *alloc_node(size_t size) {
    // cannot ask for more than the buffer can contain
    if(size >= bufsize) { throw std::bad_alloc();  }
    // if there's not enough space left, free up some!
    while(((next_p-start_p)+size) >= bufsize) { 
      if(random_replacement) {
	randomly_remove_nodes(replacement);  
      } else {
	remove_unused_nodes(replacement);
      }
      pack_buffer();
    }
    unsigned char *r = next_p;
    next_p += size;
    return r;
  }

  struct cache_node *create_bucket_array(size_t nbs) {
    struct cache_node *bs = new struct cache_node[nbs];
    // initialise buckets
    for(int i=0;i!=nbs;++i) { 
      bs[i].next=NULL; 
      bs[i].prev=NULL; 
    }
    return bs;
  }

  // randomly remove nodes with a probability of p
  void randomly_remove_nodes(double p) {
    int count=0;
    for(int i=0;i!=nbuckets;++i) {
      struct cache_node *ptr = buckets[i].next;
      while(ptr != NULL) {
	struct cache_node *optr=ptr;
	ptr = ptr->next;
	double f = ((double)rand())/RAND_MAX;
	if(f < p) { 
	  count++; 
	  remove_node(optr); 
	}
      }
    }
    numentries-=count;
  }

  // remove unused nodes to reduce cache by p % 
  void remove_unused_nodes(double p) {
    unsigned int hc = 0;    
    unsigned orig_size = (next_p-start_p);
    double amount=0;
    do {
      hc = hc + 1;
      unsigned int count=0;
      for(int i=0;i!=nbuckets;++i) {
	struct cache_node *ptr = buckets[i].next;
	while(ptr != NULL) {
	  struct cache_node *optr=ptr;
	  ptr = ptr->next;
	  if(optr->hit_count < hc) { 
	    count++; 
	    amount += sizeof_node(optr);
	    remove_node(optr); 
	  }
	}
      }
      numentries-=count;
    } while((amount / orig_size) < p);
  }

  // compact buffer which pushes all free space to end
  void pack_buffer() {
    unsigned int diff = 0;
    struct cache_node *ptr = (struct cache_node *) start_p;
    struct cache_node *pend = (struct cache_node *) next_p;

    while(ptr != pend) {
      struct cache_node *nptr = next_node(ptr);
      if(ptr->next == NULL && ptr->prev == NULL) {
	// this node is free
	diff += sizeof_node(ptr);
      } else if(diff > 0){
	// move node along
	unsigned char *dst = (unsigned char *) ptr;
	dst -= diff;
	move_node(dst,ptr);
      }
      ptr = nptr;
    }

    next_p -= diff;
  }

  // ---------------------------
  // note manipulation functions 
  // ---------------------------

  struct cache_node *next_node(struct cache_node *ptr) {
    unsigned char *p = (unsigned char *) ptr;
    p += sizeof_node(ptr);
    return (struct cache_node *) p;
  }

  size_t sizeof_node(struct cache_node *node) {
    unsigned char *p = (unsigned char *) node;
    unsigned int header_size = sizeof(struct cache_node);
    unsigned int key_size = sizeof_graph_key(p + header_size);
    unsigned int poly_size = sizeof_compact_poly(p + header_size + key_size);
    return header_size + key_size + poly_size;
  }

  void insert_node_after(struct cache_node *new_node, struct cache_node *pos) {
    new_node->next = pos->next;
    new_node->prev = pos;
    pos->next = new_node;
    if(new_node->next != NULL) { new_node->next->prev = new_node; }
  }
  
  void remove_node(struct cache_node *node) {
    node->prev->next = node->next;
    if(node->next != NULL) {
      node->next->prev = node->prev;
    }
    node->next = NULL;
    node->prev = NULL;
  }

  void move_node(unsigned char *dst, struct cache_node *ptr) {
    struct cache_node *dstptr = (struct cache_node *) dst;
    ptr->prev->next = dstptr;
    if(ptr->next != NULL) {
      ptr->next->prev = dstptr;
    }
    memmove(dst,ptr,sizeof_node(ptr));
  }
};

#endif
