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
  G spanning_tree;

  std::vector<int> pendant_vertices;
  std::vector<bool> visited;
public:
  spanning_graph(int n) : graph(n), spanning_tree(n), visited(n)  {  }

  spanning_graph(G const &g) : graph(g), spanning_tree(g.domain_size()), visited(g.domain_size())  {  
    build_spanning_tree();
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
	spanning_tree.remove(vertex);
	return;
      }
    }
    // non-pendant vertex case
    graph.remove(vertex); 
    spanning_tree.remove(vertex);
    build_spanning_tree();
  }

  void add_edge(int from, int to) { 
    graph.add_edge(from,to); 
    build_spanning_tree(); // WOAH, rather inefficient!
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
	if(spanning_tree.remove_edge(from,to,c) && 
	   spanning_tree.num_edges(from,to) == 0) {
	  // ok, have removed tree edge!
	  build_spanning_tree();
	}
	return true;
      }
    }
    return false;
  }

  bool is_tree() { return spanning_tree.num_underlying_edges() == graph.num_edges(); }

  // assumes this graph is NOT a tree
  edge_t select_nontree_edge() {
    // interesting observation is that picking the edge with least
    // underlying edges on either vertex is the best strategy.
    
    for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
      for(typename G::edge_iterator j(graph.begin_edges(*i));
	  j!=graph.end_edges(*i);++j) {	
	unsigned int c = j->second;
	if(spanning_tree.num_edges(*i,j->first) > 0) { c = c - 1; }
	if(c > 0) {
	  return edge_t(*i,j->first,c);
	}
      }
    }
    throw std::runtime_error("shouldn't get here");
  }

  int select_pendant_vertex() const {
    return pendant_vertices.back();
  }

  void contract_edge(int from, int to) { 
    graph.contract_edge(from,to); 
    spanning_tree.contract_edge(from,to);
    // now, incrementally update the spanning tree
    correct_spanning_tree(-1,from,from);

    // finally, incrementally update the pendant edges    

    // how to do this efficiently ?
    pendant_vertices.erase(std::remove(pendant_vertices.begin(),pendant_vertices.end(),from), pendant_vertices.end());
    pendant_vertices.erase(std::remove(pendant_vertices.begin(),pendant_vertices.end(),to), pendant_vertices.end());
  }
  
  vertex_iterator begin_verts() const { return graph.begin_verts(); }
  vertex_iterator end_verts() const { return graph.end_verts(); }
  
  edge_iterator begin_edges(int f) const { return graph.begin_edges(f); }
  edge_iterator end_edges(int f) const { return graph.end_edges(f); }

private:
  void build_spanning_tree() { // was retree
    // reset visited information
    fill(visited.begin(),visited.end(),false);
    // remove all spanning tree edges
    spanning_tree.clearall();
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

      if(!visited[next]) { 
	spanning_tree.add_edge(head,next,k);
	traverse(head,next); 
      }     
    }

    // pendant vertex check
    if(total == 1) { pendant_vertices.push_back(head); }
  }
  
  bool correct_spanning_tree(int tail, int head, int start) {
    for(typename G::edge_iterator i(spanning_tree.begin_edges(head));
	i!=spanning_tree.end_edges(head);++i) {
      int w(i->first);
      // don't traverse edge we've alread seen!
      if(w != tail) {
	if(w == start) { 
	  spanning_tree.remove_edge(head,start,i->second);
	  return true;
	} else if(correct_spanning_tree(head,w,start)) {
	  return true;
	}
      }    
    }
    return false;
  }
};

#endif
