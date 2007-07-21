#ifndef REDUCTIONS_HPP
#define REDUCTIONS_HPP

#include <stdexcept>

template<class G>
unsigned int remove_pendants(G &graph) {
  unsigned int num_pendants(0);
  /*
  std::vector<unsigned int> pendants;
  
  for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    // change to num_underlying_edges for multi_edge removal
    if(graph.num_edges(*i) == 1) {
      pendants.push_back(*i);
    }
  }

  while(pendants.size() > 0) {
    unsigned int p(pendants.back());
    pendants.pop_back();
    num_pendants++;
    // now, recursively eliminate any pendants created by this
    typename G::edge_iterator i(graph.begin_edges(p));
    unsigned int w(i->first);
    graph.remove(p);
    if(graph.num_edges(w) == 1) { pendants.push_back(w); } 
  }
  */
  while(graph.num_pendant_vertices() > 0) {
    unsigned int l = graph.select_pendant_vertex();
    graph.remove(l);
    num_pendants++;
  }

  return num_pendants;
}

#endif
