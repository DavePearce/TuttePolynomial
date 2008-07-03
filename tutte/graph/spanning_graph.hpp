#ifndef SPANNING_GRAPH_HPP
#define SPANNING_GRAPH_HPP

#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <algorithm>

#include "misc/triple.hpp"

class bc_dat {
public:
  unsigned int vindex;
  std::vector<bool> visited;
  std::vector<unsigned int> lowlink;
  std::vector<unsigned int> dfsnum;
  std::vector<triple<unsigned int, unsigned int, unsigned int> > cstack;
  
  void reset(unsigned int v) {
    vindex=0;
    visited.resize(v);
    lowlink.resize(v);
    dfsnum.resize(v);
    std::fill(visited.begin(),visited.end(),false);
  }
};

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
  unsigned int nartics;
  unsigned int ncomponents;
public:
  spanning_graph(int n, bool bfs = false) : graph(n), nartics(0), ncomponents(0)  {  
  }
  
  spanning_graph(G const &g, bool bfs = false) : graph(g), nartics(0), ncomponents(0) {  
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

  bool is_connected() const { return ncomponents == 1; }
  bool is_biconnected() const { return ncomponents == 1 && nartics == 1; }
  bool is_tree() const { return graph.num_edges() < graph.num_vertices(); }
  bool is_multitree() const { return graph.num_underlying_edges() < graph.num_vertices(); }
  bool is_multicycle() const { return nartics == 1 && graph.num_underlying_edges() == graph.num_vertices(); }
  
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

  void contract_edge(edge_t edge) {
    graph.remove_edge(edge.first,edge.second,edge.third); 
    graph.contract_edge(edge.first,edge.second); 
    check_biconnectivity();    
  }

  void simple_contract_edge(edge_t edge) {
    graph.remove_edge(edge.first,edge.second,edge.third); 
    graph.simple_contract_edge(edge.first,edge.second); 
    check_biconnectivity();    
  }

  void contract_line(std::vector<edge_t> line) {
    if(line.size() == 1) { 
      graph.remove_edge(line[0].first,line[0].second,line[0].third); 
    } else {
      // now, remove all internal vertices
      for(unsigned int i=0;i!=line.size()-1;++i) {
	graph.remove(line[i].second);
      }
    }
    graph.contract_edge(line[0].first,line[line.size()-1].second); 
    check_biconnectivity();
  }

  void simple_contract_line(std::vector<edge_t> line) {
    if(line.size() == 1) { 
      graph.remove_edge(line[0].first,line[0].second,line[0].third); 
    } else {
      // now, remove all internal vertices
      for(unsigned int i=0;i!=line.size()-1;++i) {
	graph.remove(line[i].second);
      }
    }
    graph.simple_contract_edge(line[0].first,line[line.size()-1].second); 
    // don't need to check biconnectivity here!
    check_biconnectivity();
  }

  void extract_biconnected_components(std::vector<spanning_graph<G> > &bcs) { // was retree
    // Now, we traverse the entire graph and extract any and all biconnected components
    static bc_dat data;
    data.reset(graph.domain_size());

    // now, check for connectedness
    for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
      if(!data.visited[*i]) { 
	// dfs search to identify component roots
	extract_biconnects(*i,*i,bcs,data);
      }
    }
  }

  void remove_graphs(std::vector<spanning_graph<G> > const &graphs) {
    // finally, remove all edges present in the biconnects
    // how could this be optimised a little?
    for(unsigned int i=0;i!=graphs.size();++i) {
      graph.remove(graphs[i].graph);
    }
    // could remove any isolated vertices here,
    // but I don't think it's necessary for the tutte
    // algorithm!
    
    nartics=0; // this is a tree by definition now!!!!!
    ncomponents = 99; // not sure how many there are ...
  }

  vertex_iterator begin_verts() const { return graph.begin_verts(); }
  vertex_iterator end_verts() const { return graph.end_verts(); }
  
  edge_iterator begin_edges(int f) const { return graph.begin_edges(f); }
  edge_iterator end_edges(int f) const { return graph.end_edges(f); }

private:
  void check_biconnectivity() { // was retree
    // reset visited information
    static bc_dat data;
    data.reset(graph.domain_size());

    nartics = 0;
    ncomponents = 1;
    // dfs search to identify component roots
    biconnect(*graph.begin_verts(),*graph.begin_verts(),data);
    // now, check for connectedness
    for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
      if(!data.visited[*i]) { 
	ncomponents ++;
	return; // short circuit remainder of computation
      }
    }
  }
  
  void biconnect(unsigned int u, unsigned int v, bc_dat &data) {
    // traverse edge tail->head
    data.dfsnum[v] = data.vindex;
    data.visited[v] = true;
    data.lowlink[v] = data.vindex++;
    // now, consider edges
    for(typename G::edge_iterator i(graph.begin_edges(v));
	i!=graph.end_edges(v);++i) {
      int w = i->first;
      if(!data.visited[w]) { 
	biconnect(v,w,data); 
	data.lowlink[v] = std::min(data.lowlink[v],data.lowlink[w]);
	if(data.lowlink[w] == data.dfsnum[v]) {
	  // v is an articulation point separating
	  // the component containing w from others.
	  nartics++;
	} else if(data.lowlink[w] > data.dfsnum[v]) {
	  // v is not in an bicomp with w
	  nartics += 2;
	}
      } else if(u != w && data.dfsnum[v] > data.dfsnum[w]) {	
	// this is a real back edge ...
	data.lowlink[v] = std::min(data.lowlink[v],data.dfsnum[w]);
      }
    }
  }

  void extract_biconnects(unsigned int u, unsigned int v, 
			  std::vector<spanning_graph<G> > &bcs,
			  bc_dat &data) {    
    // traverse edge tail->head
    data.dfsnum[v] = data.vindex;
    data.visited[v] = true;
    data.lowlink[v] = data.vindex++;
    // now, consider edges
    for(typename G::edge_iterator i(graph.begin_edges(v));
	i!=graph.end_edges(v);++i) {
      int w = i->first;
      edge_t e(v,w,i->second);

      if(!data.visited[w]) { 
	data.cstack.push_back(e);
	extract_biconnects(v,w,bcs,data); 
	data.lowlink[v] = std::min(data.lowlink[v],data.lowlink[w]);
	if(data.lowlink[w] == data.dfsnum[v]) {
	  // v is an articulation point separating
	  // the component containing w from others.
	  bcs.push_back(extract_biconnect(e,data));
	} else if(data.lowlink[w] > data.dfsnum[v]) { 
	  // v is not in a biconnected component with w
	  data.cstack.pop_back(); 
	}
      } else if(w != u && data.dfsnum[v] > data.dfsnum[w]) {	
	// this is a back edge ...
	data.lowlink[v] = std::min(data.lowlink[v],data.dfsnum[w]);
	// which means we're in a biconnected component ...
	data.cstack.push_back(e); 
      }
    }
  }

  spanning_graph<G> extract_biconnect(edge_t e, bc_dat &data) {
    spanning_graph<G> g(graph.domain_size());
    edge_t c(0,0,0);
    do {
      c = data.cstack.back();
      // in what follows, I use g.graph to avoid rechecking
      // biconnectivity every time...
      g.graph.add_edge(c.first,c.second,c.third); 
      data.cstack.pop_back();
    } while(c != e);

    // finally, remove any dumb vertices!
    for(unsigned int i=0;i!=graph.domain_size();++i) {
      if(g.num_edges(i) == 0) { g.graph.remove(i); }
    }

    g.check_biconnectivity();

    g.nartics = 1; // since this is a biconnected component!
    g.ncomponents = 1;

    return g;
  }
};

#endif
