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

  // there is no add vertex!
  bool remove(int v) { graph.remove(v); }
  void add_edge(int from, int to) { graph.add_edge(from,to); }
  void remove_edge(int from, int to) { graph.remove_edge(from,to);  }
  int remove_loops() { return g.remove_loops(); }
  void constract_edge(int from, int to) { g.contract_edge(from,to); }

  bool in_spanning_tree(int from, int to) { return false; } // to be completed

  vertex_iterator vert_begin() const { return graph.vert_begin(); }
  vertex_iterator vert_end() const { return graph.vert_end(); }
  
  edge_iterator edges_begin(int f) const { return graph.edges_begin(f); }
  edge_iterator edges_end(int f) const { return graph.edges_end(f); }
};

#endif
