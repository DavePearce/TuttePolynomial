#ifndef SIMPLE_CACHE_HPP
#define SIMPLE_CACHE_HPP

#include "../graph/algorithms.hpp"
#include <bits/allocator.h>
#include <ext/hash_map>

template<class P>
class simple_cache {
private:
  unsigned int hits;
  unsigned int misses;
  unsigned int collisions;
  unsigned int dealloced;  // for computing fragmentation
  unsigned int numentries; 

  unsigned char *start_p;        // buffer start ptr
  unsigned char *next_p;         // buffer next ptr
  unsigned int bufsize;
  
public:
  // max_size in bytes
  simple_cache(size_t max_size) {
    hits = 0;
    misses = 0;
    collisions = 0;
    dealloced = 0;
    bufsize = max_size;
    start_p = new unsigned char[max_size];
  }

  ~simple_cache() { delete [] start_p; }

  int num_hits() { return hits; }
  int num_misses() { return misses; }
  int num_entries() { return numentries; }

  P *lookup(char const *key) {
    misses++;
    return NULL;    
  }
  
  static void store(char const *key, P const &p) {
    // do nothing for now
  }  
};

#endif
