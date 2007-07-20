#ifndef REDUCTIONS_HPP
#define REDUCTIONS_HPP


template<class G>
unsigned int remove_pendants(G &graph) {
  unsigned int num_pendants(0);
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
    typename G::edge_t e(*graph.begin_edges(p));
    graph.remove(p);
    if(graph.num_edges( ... edge thing goes here ... ) == 1) {

    }
  }

  /*
  while(graph.num_pendant_vertices() > 0) {
    unsigned int l = graph.select_pendant_vertex();
    graph.remove(l);
    num_pendants++;
  }
  return num_pendants;
  */
}

#endif
