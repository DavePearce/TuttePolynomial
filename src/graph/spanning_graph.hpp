#ifndef SPANNING_GRAPH_HPP
#define SPANNING_GRAPH_HPP

#include <vector>
#include <stack>
#include <utility>

// this is a simple implementation of a dynamic algorithm for maintaining 
// a spanning tree.  The notion we use of a spanning tree is slightly
// different from normal in that we permit loops to be part of the tree.  I call
// this a spanning "loop tree" !

template<class G>
class spanning_graph {
public:
  typedef typename G::vertex_iterator vertex_iterator;
  typedef typename G::edge_iterator edge_iterator;
private:
  G graph;
  std::vector<std::pair<int,int> > nontree_edges; // all non-tree edges *except* loop edges
  std::vector<int> loop_edges;
  std::vector<bool> visited;
public:
  spanning_graph(int n) : graph(n), visited(n)  {  }

  int num_vertices() { return graph.num_vertices(); }
  int num_edges() { return graph.num_edges(); }
  int num_loops() { return loop_edges.size(); }
  int num_multiedges() { return graph.num_multiedges(); }

  bool is_multi_graph() { return graph.is_multi_graph(); }

  // there is no add vertex!
  bool remove(int v) { graph.remove(v); }

  void add_edge(int from, int to) { 
    graph.add_edge(from,to); 
    build_tree(); // WOAH, rather inefficient!
  }

  bool remove_edge(int from, int to) {     

    if(graph.remove_edge(from,to)) {    
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
	// this *must* be a loop edge
	for(std::vector<int>::reverse_iterator i(loop_edges.rbegin());
	    i!=loop_edges.rend();++i) {
	  if(*i == from) {
	    // see: "Effective STL", item 28, p125 for explanation
	    // as to why it's "(++i).base()", not "i.base()"
	    loop_edges.erase((++i).base());
	    return true;
	  }
	}
      } else {
	for(std::vector<pair<int,int> >::reverse_iterator i(nontree_edges.rbegin());
	    i!=nontree_edges.rend();++i) {
	  if((i->first == from && i->second == to) ||
	     (i->first == to && i->second == from)) {
	    // yes, this is a nontree edge, so no big deal
	    //
	    // see: "Effective STL", item 28, p125 for explanation
	    // as to why it's "(++i).base()", not "i.base()"
	    nontree_edges.erase((++i).base()); 
	    return true;
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
  bool is_tree() { return nontree_edges.size() == 0 && loop_edges.size() == 0; }

  // if there are no nontree edges, but there are loop edges then we're a "looptree" :)
  bool is_looptree() { return nontree_edges.size() == 0; }

  // assumes this graph is NOT a tree
  pair<int,int> const &select_nontree_edge() const {
    return nontree_edges.back();
  }

  // assumes this graph is NOT a tree
  int select_loop_edge() const {
    return loop_edges.back();
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
    loop_edges.clear();
    // now, make sure each vertex is explored
    for(typename G::vertex_iterator i(graph.begin_verts());
	i!=graph.end_verts();++i) {
      int v = *i;
      if(!visited[v]) { traverse(-1,v); }
    }
  }

  void traverse(int tail, int head) {
    // traverse edge tail->head
    visited[head] = true;
    int backlink_count = 1;
    for(typename G::edge_iterator i(graph.begin_edges(head));
	i!=graph.end_edges(head);++i) {
      int next = *i;

      if(!visited[next]) { traverse(head,next); }
      else if(tail != next || backlink_count == 0) {
	// this is a nontree edge
	if(head < next) { // to prevent adding same edge twice
	  nontree_edges.push_back(make_pair(head,next));
	} else if(head == next) {
	  loop_edges.push_back(head);
	}
      } else {
	// we're allowed to ignore visiting the same edge
	// just once, since other multiedges may exist ...
	backlink_count=0;
      }
    }
  }
};

#endif
