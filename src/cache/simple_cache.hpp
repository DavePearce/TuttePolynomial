#ifndef SIMPLE_CACHE_HPP
#define SIMPLE_CACHE_HPP

#include "../graph/nauty_graph.hpp"
#include <ext/hash_map>

template<class P>
class simple_cache {
private:
  __gnu_cxx::hash_map<nauty_graph,P,hash_nauty_graph> polystore; 
  unsigned int hits;
  unsigned int misses;

public:

  simple_cache() : hits(0), misses(0) {}

  int num_hits() const { return hits; }
  int num_misses() const { return misses; }
  int num_entries() const { return polystore.size(); }

  P *lookup(nauty_graph const &ng) {
    
    // Ok, now we have the nauty graph we can generate the unique
    // canonical labelling to check whether it's really a match

    typename __gnu_cxx::hash_map<nauty_graph,P,hash_nauty_graph>::iterator i = polystore.find(ng);
    if(i != polystore.end()) {
      hits++;
      return &(i->second);
    } else {
      misses++;
      return NULL;
    }
  }
  
  void store(nauty_graph const &ng, P const &p) {
    polystore.insert(make_pair(ng,p));
  }  
};

#endif
