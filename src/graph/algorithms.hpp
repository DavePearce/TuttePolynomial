#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

#include <iostream>

template<class T>
void print_graph(ostream &ostr, T const &graph) {
  ostr << "V = { ";
  for(typename T::vertex_iterator i(graph.vert_begin());i!=graph.vert_end();++i) {
    ostr << *i << " ";
  }
  ostr << "}" << endl;

  ostr << "E = { ";
  for(typename T::vertex_iterator i(graph.vert_begin());i!=graph.vert_end();++i) {
    for(typename T::edge_iterator j(graph.edges_begin(*i));j!=graph.edges_end(*i);++j) {
      ostr << *i << "--" << *j << " ";
    }
  }
  ostr << "}" << endl;
}

#endif
