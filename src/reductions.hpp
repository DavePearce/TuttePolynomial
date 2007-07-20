#ifndef REDUCTIONS_HPP
#define REDUCTIONS_HPP


template<class G>
unsigned int remove_pendants(G &graph) {
  unsigned int num_pendants(0);
  while(graph.num_pendant_vertices() > 0) {
    unsigned int l = graph.select_pendant_vertex();
    graph.remove(l);
    num_pendants++;
  }
  return num_pendants;
}

#endif
