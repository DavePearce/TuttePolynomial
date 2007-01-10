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
public:
  tutte_graph(int n) : graph(n)  {  }

  unsigned int domain_size() const { return graph.domain_size(); }
  unsigned int num_vertices() const { return graph.num_vertices(); }
  unsigned int num_edges() const { return graph.num_edges(); }
  unsigned int num_multiedges() const { return graph.num_multiedges(); }
  unsigned int num_loops() const { return graph.num_loops(); }
  bool is_multi_graph() const { return graph.is_multi_graph(); }

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

  // there is no add vertex!
  bool clear(int v) { graph.clear(v); }
  void remove_degree1_vertices() { /* replaces core/findDegOne */ }

  void add_edge(int from, int to) { graph.add_edge(from,to); }
  void remove_edge(int from, int to) { graph.remove_edge(from,to);  }  
  
  // assumes this is graph is NOT a tree
  int select_loop_edge() const { return graph.select_loop_edge(); }

  int remove_loops(int from) { 
    int r=0;
    while(graph.remove_edge(from,from)) { r++; }
    return r;
  }
  void contract_edge(int from, int to) { graph.contract_edge(from,to); }  
  

  // spanning tree stuff
  bool is_tree() { return graph.is_tree(); }
  bool is_looptree() { return graph.is_looptree(); }

  pair<int,int> const &select_nontree_edge() {
    return graph.select_nontree_edge();
  }

  // these functions shouldn't be here !
  vertex_iterator begin_verts() const { return graph.begin_verts(); }
  vertex_iterator end_verts() const { return graph.end_verts(); }
  
  edge_iterator begin_edges(int f) const { return graph.begin_edges(f); }
  edge_iterator end_edges(int f) const { return graph.end_edges(f); }
};

#endif
