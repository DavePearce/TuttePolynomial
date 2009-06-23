#ifndef GRAPH_IO_HPP
#define GRAPH_IO_HPP

#include <sstream>

template<class T>
std::string graph_ascii_str(T const &graph) {
  std::ostringstream out;
  out << "{";
  bool first=true;
  for(typename T::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    for(typename T::edge_iterator j(graph.begin_edges(*i));j!=graph.end_edges(*i);++j) {
      if(*i <= j->first) {
	if(!first) {
	  out << ",";
	}
	first=false;
	if(j->second == 1) {
	  out << *i << "-" << j->first;
	} else {
	  out << *i << "-" << j->first << "(" << j->second << ")";
	}
      } 
    }
  }
  
  out << "}";
  return out.str();
}

#endif
