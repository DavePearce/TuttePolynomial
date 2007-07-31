#ifndef SPANNING_GRAPH_HPP
#define SPANNING_GRAPH_HPP

#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <algorithm>

#include "misc/triple.hpp"

// this is a simple implementation of a dynamic algorithm for maintaining 
// a spanning tree.  The notion we use of a spanning tree is slightly
// different from normal in that we permit loops to be part of the tree.  I call
// this a spanning "loop tree" !

template<class G>
class spanning_graph {
public:
  typedef typename G::vertex_iterator vertex_iterator;
  typedef typename G::edge_iterator edge_iterator;
  typedef triple<unsigned int, unsigned int, unsigned int> edge_t;
private:
  G graph;
  std::vector<bool> visited;
  std::vector<unsigned int> roots;
public:
  spanning_graph(int n, bool bfs = false) : graph(n), visited(n)  {  }

  spanning_graph(G const &g, bool bfs = false) : graph(g), visited(g.domain_size()) {  
  }

  unsigned int domain_size() const { return graph.domain_size(); }
  unsigned int num_vertices() const { return graph.num_vertices(); }

  unsigned int num_edges() const { return graph.num_edges(); }
  unsigned int num_edges(unsigned int vertex) const { return graph.num_edges(vertex); }
  unsigned int num_edges(unsigned int v1, unsigned int v2) const { return graph.num_edges(v1,v2); }

  unsigned int num_underlying_edges() const { return graph.num_underlying_edges(); }
  unsigned int num_underlying_edges(unsigned int vertex) const { return graph.num_underlying_edges(vertex); }

  unsigned int num_multiedges() const { return graph.num_multiedges(); }

  unsigned int num_components() const { return roots.size(); }
 
  bool clear(int v) { graph.clear(v); }

  void remove(int vertex) { 
    graph.remove(vertex); 
    find_components();
  }

  void add_edge(int from, int to) { add_edge(from,to,1); }
  void add_edge(int from, int to, int count) { 
    graph.add_edge(from,to,count); 
  }

  // THIS LOOP IS DEPRECATED
  unsigned int remove_loops() {   
    unsigned int c=0U;    
    for(typename G::vertex_iterator i(graph.begin_verts());
	i!=graph.end_verts();++i) {
      c += graph.remove_all_edges(*i,*i);
    }
    return c;
  }

  bool remove_edge(int from, int to) {     
    remove_edge(from,to,1);
  }

  bool remove_edge(int from, int to, int c) {     
    if(graph.remove_edge(from,to,c)) {    
      // by removing an edge, we may have disconnected the
      // graph ...
      find_components();
      return true;
    }
    return false;
  }

  void contract_edge(int from, int to) { 
    graph.contract_edge(from,to); 
  }

  spanning_graph<G> component(unsigned int n) const {
    // this needs to be fixed
    spanning_graph<G> r(graph);
    return r;
  }
  
  vertex_iterator begin_verts() const { return graph.begin_verts(); }
  vertex_iterator end_verts() const { return graph.end_verts(); }
  
  edge_iterator begin_edges(int f) const { return graph.begin_edges(f); }
  edge_iterator end_edges(int f) const { return graph.end_edges(f); }

private:
  void find_components() { // was retree
    // reset component infomration
    roots.clear();
    // reset visited information
    fill(visited.begin(),visited.end(),false);
    // dfs search to identify component roots
    for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
      unsigned int v = *i;
      if(!visited[v]) { 
	roots.push_back(v);
	traverse(-1,v); 
      }
    }      
  }
  
  void traverse(int tail, int head) {
    // traverse edge tail->head
    visited[head] = true;
    // now, consider edges
    for(typename G::edge_iterator i(graph.begin_edges(head));
	i!=graph.end_edges(head);++i) {
      int next = i->first;
      if(!visited[next]) { 
	traverse(head,next); 
      }     
    }
  }
};

#endif
