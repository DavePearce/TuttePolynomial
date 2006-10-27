#ifndef SPANNING_GRAPH_HPP
#define SPANNING_GRAPH_HPP

#include <vector>
#include <stack>
#include <utility>

// this is a simple implementation of a dynamic algorithm for maintaining 
// a spanning tree [ACTUALLY IT DOESN'T EVEN WORK YET!]

template<class G>
class spanning_graph {
public:
  typedef typename G::vertex_iterator vertex_iterator;
  typedef typename G::edge_iterator edge_iterator;
private:
  G graph;
  std::vector<std::pair<int,int> > nontree_edges;
  std::vector<bool> visited;
public:
  spanning_graph(int n) : graph(n), visited(n)  {  }

  int num_vertices() { return graph.num_vertices(); }
  int num_edges() { return graph.num_edges(); }
  bool is_multi_graph() { return graph.is_multi_graph(); }

  // there is no add vertex!
  bool remove(int v) { graph.remove(v); }

  void add_edge(int from, int to) { 
    graph.add_edge(from,to); 
    build_tree(); // WOAH, rather inefficient!
  }

  void remove_edge(int from, int to) {     

    graph.remove_edge(from,to);  

    // if we've removed a tree edge then we'd
    // need to rebuild the tree.
    //
    // but, given the way the overall tutte 
    // algorithm works, this is unlikely...
    // 
    // I use the reverse iterator, since I know
    // the most likely edge to be removed is
    // the nontree edge on the top of the stack

    for(std::vector<pair<int,int> >::reverse_iterator i(nontree_edges.rbegin());
	i!=nontree_edges.rend();++i) {
      if((i->first == from && i->second == to) ||
	 (i->first == to && i->second == from)) {
	// yes, this is a nontree edge, so no big deal
	nontree_edges.erase(i.base());
	return;
      }
    }
    
    // oh dear, we removed a tree edge.  must recompute
    // the tree then ...
    build_tree();
  }

  // pretty simple ... if there are no nontree edges,
  // then we must be a tree!
  bool is_tree() { return nontree_edges.size() == 0; }

  // assumes this is graph is NOT a tree
  pair<int,int> const &select_nontree_edge() {
    return nontree_edges.back();
  }

  int remove_loops() { return graph.remove_loops(); }

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
	}
      } else {
	// we're allows to ignore visiting the same edge
	// just once, since other multiedges may exist ...
	backlink_count=0;
      }
    }
  }
};

#endif
