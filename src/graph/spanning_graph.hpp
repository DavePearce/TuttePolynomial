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
  std::vector<unsigned int> lowlink;
  std::vector<unsigned int> dfsnum;
  unsigned int vindex;
  unsigned int nartics;
public:
  spanning_graph(int n, bool bfs = false) : graph(n), visited(n), lowlink(n), dfsnum(n), nartics(0)  {  
  }

  spanning_graph(G const &g, bool bfs = false) : graph(g), visited(g.domain_size()), 
						 lowlink(g.domain_size()), dfsnum(g.domain_size()) {  
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

  bool is_biconnected() const { return nartics == 1; }

  bool clear(int v) { 
    check_biconnectivity();
    graph.clear(v); 
  }

  void remove(int vertex) { 
    graph.remove(vertex); 
    check_biconnectivity();
  }

  void add_edge(int from, int to) { add_edge(from,to,1); }

  void add_edge(int from, int to, int count) { 
    graph.add_edge(from,to,count); 
    check_biconnectivity();
  }

  unsigned int remove_all_edges(int from, int to) {     
    unsigned int r = graph.remove_all_edges(from,to);
    if(r > 0 && from != to) { check_biconnectivity(); }
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

  void contract_edge(int from, int to) { 
    graph.contract_edge(from,to);     
    // This is needed, since during a contract operation an edge is
    // first removed and then the end vertices are joined.  There
    // should be a way to avoid this unnecessary recomputation.
    check_biconnectivity();
  }

  void extract_biconnected_components(std::vector<spanning_graph<G> > &bcs) { // was retree
    // Now, we traverse the entire graph and extract any and all biconnected components

    // reset visited information
    fill(visited.begin(),visited.end(),false);
    vindex = 0;
    std::vector<edge_t> cstack;
    // now, check for connectedness
    for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
      if(!visited[*i]) { 
	// dfs search to identify component roots
	extract_biconnects(*i,*i,bcs,cstack);
      }
    }
    // finally, remove all edges present in the biconnects
    // how could this be optimised a little?
    for(unsigned int i=0;i!=bcs.size();++i) {
      graph.remove(bcs[i].graph);
    }
    // could remove any isolated vertices here,
    // but I don't think it's necessary for the tutte
    // algorithm!

    nartics=0; // this is a tree by definition now!!!!!
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
    nartics = 0;
    // dfs search to identify component roots
    biconnect(*graph.begin_verts(),*graph.begin_verts());
    // now, check for connectedness
    for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
      if(!visited[*i]) { 
	nartics += 2;
	return; // short circuit remainder of computation
      }
    }
  }
  
  void biconnect(unsigned int u, unsigned int v) {
    // traverse edge tail->head
    dfsnum[v] = vindex;
    visited[v] = true;
    lowlink[v] = vindex++;
    // now, consider edges
    for(typename G::edge_iterator i(graph.begin_edges(v));
	i!=graph.end_edges(v);++i) {
      int w = i->first;
      if(!visited[w]) { 
	biconnect(v,w); 
	lowlink[v] = std::min(lowlink[v],lowlink[w]);
	if(lowlink[w] == dfsnum[v]) {
	  // v is an articulation point separating
	  // the component containing w from others.
	  nartics++;
	} else {
	  // v is not in an bicomp with w
	  nartics += 2;
	}
      } else if(u != w && dfsnum[v] > dfsnum[w]) {	
	// this is a real back edge ...
	lowlink[v] = std::min(lowlink[v],dfsnum[w]);
      }
    }
  }

  void extract_biconnects(unsigned int u, unsigned int v, 
			  std::vector<spanning_graph<G> > &bcs,
			  std::vector<edge_t> &cstack) {
    // traverse edge tail->head
    dfsnum[v] = vindex;
    visited[v] = true;
    lowlink[v] = vindex++;
    // now, consider edges
    for(typename G::edge_iterator i(graph.begin_edges(v));
	i!=graph.end_edges(v);++i) {
      int w = i->first;
      edge_t e(v,w,i->second);

      if(!visited[w]) { 
	cstack.push_back(e);
	extract_biconnects(v,w,bcs,cstack); 
	lowlink[v] = std::min(lowlink[v],lowlink[w]);
	if(lowlink[w] == dfsnum[v]) {
	  // v is an articulation point separating
	  // the component containing w from others.
	  bcs.push_back(extract_biconnect(e,cstack));
	} else if(lowlink[w] > dfsnum[v]) { 
	  // v is not in a biconnected component with w
	  cstack.pop_back(); 
	}
      } else if(w != u && dfsnum[v] > dfsnum[w]) {	
	// this is a back edge ...
	lowlink[v] = std::min(lowlink[v],dfsnum[w]);
	// which means we're in a biconnected component ...
	cstack.push_back(e); 
      }
    }
  }

  spanning_graph<G> extract_biconnect(edge_t e, std::vector<edge_t> &cstack) {
    spanning_graph<G> g(graph.domain_size());
    edge_t c(0,0,0);
    do {
      c = cstack.back();
      // in what follows, I use g.graph to avoid rechecking
      // biconnectivity every time...
      g.graph.add_edge(c.first,c.second,c.third); 
      cstack.pop_back();
    } while(c != e);

    // finally, remove any dumb vertices!
    for(unsigned int i=0;i!=graph.domain_size();++i) {
      if(g.num_edges(i) == 0) { g.graph.remove(i); }
    }

    g.nartics = 1; // since this is a biconnected component!

    return g;
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
