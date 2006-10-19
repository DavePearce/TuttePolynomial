#ifndef TUTTE_GRAPH_HPP
#define TUTTE_GRAPH_HPP

#include <vector>

// this graph maintains the X and Y powers for a graph
// as it undergoes constracts and deletes.

template<class G>
class tutte_graph {
public:
  typedef typename G::vertex_iterator vertex_iterator;
  typedef typename G::edge_iterator edge_iterator;
private:
  G graph;
  int xpower; // powers of x
  int ypower; // powers of y
  int xp1power; // powers of x+1
public:
  spanning_graph(int n) : graph(n)  {  }

  // there is no add vertex!
  bool remove(int v) { graph.remove(v); }
  void add_edge(int from, int to) { graph.add_edge(from,to); }
  void remove_edge(int from, int to) { graph.remove_edge(from,to);  }  
  int remove_loops() { return g.remove_loops(); }
  void constract_edge(int from, int to) { g.contract_edge(from,to); }

  int xpower() { return xpower; }
  int xp1power() { return xp1power; }
  int ypower() { return ypower; }

  vertex_iterator vert_begin() const { return graph.vert_begin(); }
  vertex_iterator vert_end() const { return graph.vert_end(); }
  
  edge_iterator edges_begin(int f) const { return graph.edges_begin(f); }
  edge_iterator edges_end(int f) const { return graph.edges_end(f); }
};

#endif
