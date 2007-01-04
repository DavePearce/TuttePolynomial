#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

#include <iostream>
#include <set>

template<class T>
void print_graph(ostream &ostr, T const &graph) {
  ostr << "V = { ";
  for(int i=0;i!=graph.num_vertices();++i) {
    ostr << i << " ";
  }
  ostr << "}" << endl;

  ostr << "E = { ";

  for(int i=0;i!=graph.num_vertices();++i) {
    for(typename T::edge_iterator j(graph.begin_edges(i));j!=graph.end_edges(i);++j) {
      if(i <= *j) {
	cout << i << "--" << *j << " ";
      } 
    }
  }

  ostr << "}" << endl;
}

#endif
