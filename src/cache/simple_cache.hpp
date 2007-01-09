#ifndef SIMPLE_CACHE_HPP
#define SIMPLE_CACHE_HPP

#include "../graph/algorithms.hpp"
#include "../poly/algorithms.hpp"
#include <stdexcept>
#include <ext/hash_map>
#include <climits>

/**
 * This file implements a simple cache for storing graph_keys and
 * their polynomials.  It's quite ugly in places, and I wonder how
 * this could be improved.
 */

struct cache_node {
  struct cache_node *next;  
  // graph key comes here
  // followed by polynomial
};

template<class P>
class simple_cache {
private:
  unsigned int hits;
  unsigned int misses;
  unsigned int collisions;
  unsigned int dealloced;  // for computing fragmentation
  unsigned int numentries; 
  struct cache_node** buckets;      // start of bucket array
  unsigned int nbuckets;         // number of buckets
  unsigned char *start_p;        // buffer start ptr
  unsigned char *next_p;         // buffer next ptr
  unsigned int bufsize;
  
public:
  // max_size in bytes
  simple_cache(size_t max_size, size_t nbs = 10000) {
    hits = 0;
    misses = 0;
    collisions = 0;
    dealloced = 0;
    bufsize = max_size;
    nbuckets = nbs;
    buckets = new (cache_node*)[nbs];
    start_p = new unsigned char[max_size];
    next_p = start_p;
    for(int i=0;i!=nbs;++i) { buckets[i]=NULL; }
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

  unsigned int min_bucket_size() {
    unsigned int r = UINT_MAX;
    for(unsigned int i=0;i!=nbuckets;++i) {
      r = min(r,bucket_length(i));
    }
    return r;
  }
  
  unsigned int max_bucket_size() {
    unsigned int r = 0;
    for(unsigned int i=0;i!=nbuckets;++i) {
      r = max(r,bucket_length(i));
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

  double density() {
    size_t used = next_p - start_p;
    return ((double)numentries) / used;
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
      if(buckets[i] != NULL) {
	buckets[i] += diff;
	struct cache_node *ptr = buckets[i];
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

  bool lookup(unsigned char const *key, P &dst) {
    // identify containing bucket
    unsigned int bucket = hash_graph_key(key) % nbuckets;
    struct cache_node *node_p = buckets[bucket];
    // traverse bucket looking for match
    while(node_p != NULL) {
      unsigned char *key_p = (unsigned char *) node_p;
      key_p += sizeof(struct cache_node);
      if(compare_graph_keys(key,key_p)) {
	// match made
	size_t sizeof_key = sizeof_graph_key(key_p);
	dst = read_compact_poly<P>(key_p + sizeof_key);
	hits++;
	return true;
      }
      collisions++;
      node_p = node_p->next;
    }
    misses++;
    return false;    
  }
  
  void store(unsigned char const *key, P const &p) {
    // allocate space for new node
    unsigned int sizeof_key = sizeof_graph_key(key);
    unsigned int sizeof_poly = sizeof_compact_poly(p);
    unsigned char *ptr = alloc(sizeof(struct cache_node) + sizeof_key + sizeof_poly);  
    struct cache_node *node_p = (struct cache_node *) ptr;
    unsigned char *key_p = ptr + sizeof(struct cache_node);
    // now put key at head of its bucket list
    unsigned int bucket = hash_graph_key(key) % nbuckets; 
    node_p->next = buckets[bucket];
    buckets[bucket] = node_p;
    // load the key into the node
    memcpy(key_p,key,sizeof_key);
    // load the poly into the node
    write_compact_poly(key_p+sizeof_key,p);
    // update stats
    numentries++;
    // done.
  }  
  
private:
  simple_cache const &operator=(simple_cache const &src) {
    return this;
  }

  simple_cache(simple_cache const &src) {
  }

  inline unsigned char *alloc(size_t size) {
    // keep allocating until we run out of space ...
    if(((next_p-start_p)+size) >= bufsize) { throw std::bad_alloc();  }
    unsigned char *r = next_p;
    next_p += size;
    return r;
  }

  unsigned int bucket_length(unsigned int b) {
    struct cache_node *ptr = buckets[b];
    int len=0;
    while(ptr != NULL) {
      ptr = ptr->next;
      len++;
    }
    return len;
  }
};

#endif
