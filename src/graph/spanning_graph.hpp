#ifndef SPANNING_GRAPH_HPP
#define SPANNING_GRAPH_HPP

#include <vector>

// this is a simple implementation of a dynamic algorithm for maintaining 
// a spanning tree [ACTUALLY IT DOESN'T EVEN WORK YET!]

template<class G>
class spanning_graph {
public:
  typedef typename G::vertex_iterator vertex_iterator;
  typedef typename G::edge_iterator edge_iterator;
private:
  G graph;
public:
  spanning_graph(int n) : graph(n)  {  }

  int num_vertices() { return graph.num_vertices(); }
  int num_edges() { return graph.num_edges(); }
  bool is_multi_graph() { return graph.is_multi_graph(); }

  // there is no add vertex!
  bool remove(int v) { graph.remove(v); }
  void add_edge(int from, int to) { graph.add_edge(from,to); }
  void remove_edge(int from, int to) { graph.remove_edge(from,to);  }
  int remove_loops() { return graph.remove_loops(); }
  void contract_edge(int from, int to) { graph.contract_edge(from,to); }

  bool in_spanning_tree(int from, int to) { return false; } // to be completed

  vertex_iterator begin_verts() const { return graph.begin_verts(); }
  vertex_iterator end_verts() const { return graph.end_verts(); }
  
  edge_iterator begin_edges(int f) const { return graph.begin_edges(f); }
  edge_iterator end_edges(int f) const { return graph.end_edges(f); }
};

#endif
