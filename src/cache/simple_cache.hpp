#ifndef SIMPLE_CACHE_HPP
#define SIMPLE_CACHE_HPP

#include "../graph/algorithms.hpp"
#include "../poly/algorithms.hpp"
#include <stdexcept>
#include <ext/hash_map>

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

  double density() {
    size_t used = next_p - start_p;
    return ((double)numentries) / used;
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
  
  inline unsigned char *alloc(size_t size) {
    // keep allocating until we run out of space ...
    if(((next_p-start_p)+size) >= bufsize) { throw std::bad_alloc();  }
    unsigned char *r = next_p;
    next_p += size;
    return r;
  }
};

#endif
