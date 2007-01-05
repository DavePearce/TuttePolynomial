#ifndef SIMPLE_CACHE_HPP
#define SIMPLE_CACHE_HPP

#include "../graph/nauty_graph.hpp"
#include <bits/allocator.h>
#include <ext/hash_map>



template<class T>
class simple_cache_alloc {
  static T *allocate(int count) {
    
  }

  static void deallocate(T *ptr, int count) {
    // do nothing for the moment!
  }
};

template<class P>
class simple_cache {
private:
  static __gnu_cxx::hash_map<nauty_graph<>,P,hash_nauty_graph<> > polystore; 
  static unsigned int hits;
  static unsigned int misses;

  simple_cache() {} 
public:
  static void initialise(int max_size) {
    hits = 0;
    misses = 0;
  }

  static int num_hits() { return hits; }
  static int num_misses() { return misses; }
  static int num_entries() { return polystore.size(); }

  static P *lookup(nauty_graph<> const &ng) {
    
    // Ok, now we have the nauty graph we can generate the unique
    // canonical labelling to check whether it's really a match

    typename __gnu_cxx::hash_map<nauty_graph<>,P,hash_nauty_graph<> >::iterator i = polystore.find(ng);
    if(i != polystore.end()) {
      hits++;
      return &(i->second);
    } else {
      misses++;
      return NULL;
    }
  }
  
  static void store(nauty_graph<> const &ng, P const &p) {
    polystore.insert(make_pair(ng,p));
  }  
};

template<class P>
unsigned int simple_cache<P>::hits = 0;

template<class P>
unsigned int simple_cache<P>::misses = 0;


#endif
