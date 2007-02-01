#ifndef SPANNING_GRAPH_HPP
#define SPANNING_GRAPH_HPP

#include <vector>
#include <stack>
#include <utility>

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
  std::vector<edge_t> nontree_edges; // all non-tree edges *except* loop edges
  std::vector<int> pendant_vertices;
  std::vector<bool> visited;
public:
  spanning_graph(int n) : graph(n), visited(n)  {  }
  spanning_graph(G const &g) : graph(g), visited(g.domain_size())  {  
    build_tree();
  }

  unsigned int domain_size() const { return graph.domain_size(); }
  unsigned int num_vertices() const { return graph.num_vertices(); }
  unsigned int num_edges() const { return graph.num_edges(); }
  unsigned int num_edges(unsigned int vertex) const { return graph.num_edges(vertex); }
  unsigned int num_pendant_vertices() const { return pendant_vertices.size(); }
  unsigned int num_multiedges() const { return graph.num_multiedges(); }
  bool is_multi_graph() const { return graph.is_multi_graph(); }

  bool clear(int v) { graph.clear(v); }

  void remove(int vertex) { 
    // use reverse iterator to reflect fact that likely
    // vertex being removed comes from select_pendant_vertex
    for(std::vector<int>::reverse_iterator i(pendant_vertices.rbegin());
	    i!=pendant_vertices.rend();++i) {
      if(*i == vertex) {
	// see: "Effective STL", item 28, p125 for explanation
	// as to why it's "(++i).base()", not "i.base()"
	pendant_vertices.erase((++i).base());
	// now, we know a pendant vertex is being removed
	// check whether its neighbour has only 2 edges
	// since these are by definition pendants now
	for(typename G::edge_iterator j(graph.begin_edges(vertex));
	    j!=graph.end_edges(vertex);++j) {
	  if(graph.num_edges(j->first) == 2) {
	    // yes, found one!  
	    //
	    // BUG HERE WHEN EDGE IS A LOOP (BUT THIS
 	    // CURRENTLY NEVER HAPPENS, SINCE LOOPS ARE REMOVED IN
	    // DELCONTRACT).
	    pendant_vertices.push_back(j->first);
	  }
	}
	graph.remove(vertex); 
	return;
      }
    }
    // non-pendant vertex case
    graph.remove(vertex); 
    build_tree();
  }

  void add_edge(int from, int to) { 
    graph.add_edge(from,to); 
    build_tree(); // WOAH, rather inefficient!
  }

  unsigned int remove_loops() {
    unsigned int c=0;    
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
      // if we've removed a tree edge then we'd
      // need to rebuild the tree.
      //
      // but, given the way the overall tutte 
      // algorithm works, this is unlikely...
      // 
      // I use the reverse iterator, since I know
      // the most likely edge to be removed is
      // the nontree edge on the top of the stack

      if(from == to) {
	// check for pendant vertices
	if(num_edges(from) == 1) { pendant_vertices.push_back(from); }
	return true;
      } else {
	// check for pendant vertices
	if(num_edges(from) == 1) { pendant_vertices.push_back(from); }
	if(num_edges(to) == 1) { pendant_vertices.push_back(to); }
	// now, check to see if this was a non-tree
	for(std::vector<edge_t>::reverse_iterator i(nontree_edges.rbegin());
	    i!=nontree_edges.rend();++i) {
	  if((i->first == from && i->second == to) ||
	     (i->first == to && i->second == from)) {
	    // yes, this is a nontree edge, so no big deal
	    i->third -= c;
	    if(i->third == 0) {
	      // see: "Effective STL", item 28, p125 for explanation
	      // as to why it's "(++i).base()", not "i.base()"
	      nontree_edges.erase((++i).base()); 
	      return true;
	    }
	  }
	}
      }
      
      // oh dear, we removed a tree edge.  must recompute
      // the tree then ...
      build_tree();
      return true;
    }
    return false;
  }

  // pretty simple ... if there are no nontree and loop edges, then we must be a tree!
  bool is_tree() { return nontree_edges.size() == 0; }

  // assumes this graph is NOT a tree
  edge_t select_nontree_edge() {
    return nontree_edges.back();
  }
  
  edge_t select_multi_edge() {
    // this is a simple hack for now
    edge_t cur(0,0,0);
    for(std::vector<edge_t>::reverse_iterator i(nontree_edges.rbegin());
	i!=nontree_edges.rend();++i) {
      if(i->third > cur.third) {
	cur = *i;
      }
    }
    return cur;
  }

  int select_pendant_vertex() const {
    return pendant_vertices.back();
  }

  void contract_edge(int from, int to) { 
    graph.contract_edge(from,to); 
    // for now, simply assume that we need to rebuild
    // the spanning tree!
    build_tree();
  }
  
  vertex_iterator begin_verts() const { return graph.begin_verts(); }
  vertex_iterator end_verts() const { return graph.end_verts(); }
  
  edge_iterator begin_edges(int f) const { return graph.begin_edges(f); }
  edge_iterator end_edges(int f) const { return graph.end_edges(f); }

private:
  void build_tree() { // was retree
    // reset visited information
    fill(visited.begin(),visited.end(),false);
    nontree_edges.clear();
    pendant_vertices.clear();
    // now, make sure each vertex is explored
    for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
      unsigned int v = *i;
      if(!visited[v]) { traverse(-1,v); }
    }
  }

  void traverse(int tail, int head) {
    // traverse edge tail->head
    visited[head] = true;
    // now, consider edges
    unsigned int total(0);
    for(typename G::edge_iterator i(graph.begin_edges(head));
	i!=graph.end_edges(head);++i) {
      int next = i->first;
      int k = i->second; // number of multi edges

      total += k;

      if(!visited[next]) { traverse(head,next); k--; }
      else if(next == tail) { k--; }

      if(k > 0 && head < next) { 
	nontree_edges.push_back(edge_t(head,next,k));
      } 
    }

    // pendant vertex check
    if(total == 1) { pendant_vertices.push_back(head); }
  }
};

#endif
