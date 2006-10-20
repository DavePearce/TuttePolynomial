#ifndef TUTTE_GRAPH_HPP
#define TUTTE_GRAPH_HPP

#include <stdexcept>
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
  int _xpower; // powers of x
  int _ypower; // powers of y
  int _xp1power; // powers of x+1
public:
  tutte_graph(int n) : graph(n)  {  }

  int num_vertices() { return graph.num_vertices(); }
  int num_edges() { return graph.num_edges(); }
  bool is_multi_graph() { return graph.is_multi_graph(); }

  // This method returns true if the graph is a loop.
  // Note that this *includes* multi-loops.
  bool is_loop() { 
    if(graph.num_vertices() == 1) {
      // ok, could be a loop
      int v = *graph.begin_verts();
      int c = 0;
      for(typename G::edge_iterator i(graph.begin_edges(v));
	  i!=graph.end_edges(v);++i) {
	// this is more of a safety check at the moment
	if(*i != v) { throw std::runtime_error("Graph with single vertex and > 1 edges is not a loop???"); }
	++c;
      }
      return c != 0;
    }
    return false;
  }

  // this method returns true if the graph is a tree
  // for the moment, the method actually only catches the case
  // when it's a single edge ...
  bool is_tree() { 
    if(graph.num_vertices() == 2) {
      int v1 = *graph.begin_verts();
      int v2 = *(++graph.begin_verts());
      int c = 0;
      for(typename G::edge_iterator i(graph.begin_edges(v1));
	  i!=graph.end_edges(v1);++i) {
	if(*i == v1) { return false; }
	else if(*i != v2) { throw std::runtime_error("Graph with two vertices and > 1 edges has impossible edge ???"); }
	++c;
      }     
      return c != 0;
    }
    return false;
  }

  // there is no add vertex!
  bool remove(int v) { graph.remove(v); }

  void remove_degree1_vertices() { /* replaces core/findDegOne */ }

  void add_edge(int from, int to) { graph.add_edge(from,to); }
  void remove_edge(int from, int to) { graph.remove_edge(from,to);  }  
  int remove_loops() { return graph.remove_loops(); }
  void contract_edge(int from, int to) { graph.contract_edge(from,to); }

  // these functions shouldn't be here !
  void set_xpower(int p) { _xpower = p; }
  void set_ypower(int p) { _ypower = p; }
  void set_xp1power(int p) { _xp1power = p; }

  int xpower() { return _xpower; }
  int xp1power() { return _xp1power; }
  int ypower() { return _ypower; }

  vertex_iterator begin_verts() const { return graph.begin_verts(); }
  vertex_iterator end_verts() const { return graph.end_verts(); }
  
  edge_iterator begin_edges(int f) const { return graph.begin_edges(f); }
  edge_iterator end_edges(int f) const { return graph.end_edges(f); }
};

#endif
