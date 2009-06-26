// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#ifndef DIRECTED_ADJACENCY_LIST_HPP
#define DIRECTED_ADJACENCY_LIST_HPP

#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <stdexcept>

template<class T = std::vector<unsigned int> >
class directed_adjacency_list {
public:
  typedef std::list<unsigned int>::const_iterator vertex_iterator;
  typedef typename T::iterator int_edge_iterator;
  typedef typename T::const_iterator edge_iterator;
private:
  unsigned int _domain_size;
  std::list<unsigned int> vertices;
  std::vector<T> outedges;  
  // inedges not implemented yet
public:
  directed_adjacency_list(int n = 0) : outedges(n),  _domain_size(n) { 
    for(int i=0;i!=n;++i) { vertices.push_back(i); }
  }

  unsigned int domain_size() const { return _domain_size; }
  unsigned int num_vertices() const { return vertices.size(); }

  bool add_edge(unsigned int from, unsigned int to) {
    outedges[from].push_back(to);
    return false;
  }

  vertex_iterator begin_verts() const { return vertices.begin(); }
  vertex_iterator end_verts() const { return vertices.end(); }

  edge_iterator begin_outedges(int f) const { return outedges[f].begin(); }
  edge_iterator end_outedges(int f) const { return outedges[f].end(); }
};

#endif
