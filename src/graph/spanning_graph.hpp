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
  mutable std::vector<bool> visited;
  std::vector<unsigned int> lowlink;
  std::vector<unsigned int> dfsnum;
  std::vector<unsigned int> stack;
  unsigned int vindex;
  bool biconnected;
public:
  spanning_graph(int n, bool bfs = false) : graph(n), visited(n), lowlink(n), dfsnum(n)  {  
    stack.reserve(n);
  }

  spanning_graph(G const &g, bool bfs = false) : graph(g), visited(g.domain_size()), 
						 lowlink(g.domain_size()), dfsnum(g.domain_size()) {  
    stack.reserve(g.domain_size());
    check_biconnectivity();
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
 
  bool clear(int v) { 
    find_components();
    graph.clear(v); 
  }

  void remove(int vertex) { 
    graph.remove(vertex); 
    find_components();
  }

  void add_edge(int from, int to) { add_edge(from,to,1); }

  void add_edge(int from, int to, int count) { 
    graph.add_edge(from,to,count); 
    check_biconnectivity();
  }

  unsigned int remove_all_edges(int from, int to) {     
    unsigned int r = graph.remove_all_edges(from,to);
    if(r > 0 && from != to) { find_components(); }
    return r;
  }

  bool remove_line(std::vector<edge_t> const &line) {
    if(line.size() == 1) { return remove_edge(line[0]); }
    // now, remove all internal vertices
    for(unsigned int i=0;i!=line.size()-1;++i) {
      graph.remove(line[i].second);
    }
    check_biconnectivity();
  }

  bool remove_edge(int from, int to) {     
    return remove_edge(from,to,1);
  }

  bool remove_edge(int from, int to, int c) {     
    if(graph.remove_edge(from,to,c)) {    
      if(from != to) {
	// by removing an edge, we may have disconnected the
	// graph ...
	check_biconnectivity();
      }
      return true;
    }
    return false;
  }

  bool remove_edge(edge_t const &e) {     
    if(graph.remove_edge(e.first,e.second,e.third)) {    
      if(e.first != e.second) {
	// by removing an edge, we may have disconnected the
	// graph ...
	check_biconnectivity();
      }
      return true;
    }
    return false;
  }

  spanning_graph<G> extract_component(unsigned int i) {
    // first, identify component
    spanning_graph<G> g(component(i));
    // now remove it!
    for(typename G::vertex_iterator j(g.begin_verts());
	j!=g.end_verts();++j) {
      graph.remove(*j);
    }
    roots.erase(roots.begin()+i);
    return g;
  }

  void contract_edge(int from, int to) { 
    graph.contract_edge(from,to);     
    if(roots.size() > 1) {
      // This is needed, since during a contract operation an edge is
      // first removed and then the end vertices are joined.  There
      // should be a way to avoid this unnecessary recomputation.
      check_biconnectivity();
    } else {
      // safety check
      std::replace(roots.begin(),roots.end(),to,from);
    }
  }

  vertex_iterator begin_verts() const { return graph.begin_verts(); }
  vertex_iterator end_verts() const { return graph.end_verts(); }
  
  edge_iterator begin_edges(int f) const { return graph.begin_edges(f); }
  edge_iterator end_edges(int f) const { return graph.end_edges(f); }

private:
  void check_biconnectivity() { // was retree
    // reset visited information
    fill(visited.begin(),visited.end(),false);
    vindex = 0;
    std::cout << "=== FIND COMPONENTS: " << graph_str(graph) << std::endl;
    biconnectivity=false;
    // dfs search to identify component roots
    biconnect(*graph.begin_verts());
    // now, check for connectedness
    for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
      if(!visited[*i]) { 
	biconnected = false;
	return; // short circuit remainder of computation
      }
    }
  }
  
  void biconnect(unsigned int v) {
    // traverse edge tail->head
    std::cout << "VISIT: " << v << std::endl;
    dfsnum[v] = vindex;
    visited[v] = true;
    lowlink[v] = vindex++;
    // now, consider edges
    for(typename G::edge_iterator i(graph.begin_edges(v));
	i!=graph.end_edges(v);++i) {
      int w = i->first;
      if(!visited[w]) { 
	biconnect(w); 
	lowlink[v] = std::min(lowlink[v],lowlink[w]);
	if(lowlink[w] >= dfsnum[v]) {
	  // v is an articulation point separating
	  // the component containing w from others.
	  std::cout << "IDENTIFIED ARTICULATION EDGE: " << v << "--" << w << std::endl;
	  // should pop component from stack here.
	}
      } else if(dfsnum[v] > dfsnum[w]) {	
	// this is a back edge ...
	lowlink[v] = std::min(lowlink[v],dfsnum[w]);
	// which means we're in a biconnected component ...
      }
    }
  }

  void add_component(unsigned int v, spanning_graph<G> &component) const {
    // traverse edge tail->head
    visited[v] = true;
    // now, consider edges
    for(typename G::edge_iterator i(graph.begin_edges(v));
	i!=graph.end_edges(v);++i) {
      unsigned int next = i->first; // neighbour
      unsigned int count = i->second; // mult edge count
      if(v <= next) { component.add_edge(v,next,count); }
      if(!visited[next]) { add_component(next,component); }     
    }
  }
};

#endif
