#ifndef ADJACENCY_LIST_HPP
#define ADJACENCY_LIST_HPP

#include <vector>
#include <list>
#include <algorithm>

using namespace std;

// This graph type is simply the most basic implementation
// you could think of.

class adjacency_list {
public:
  typedef list<int>::const_iterator vertex_iterator;
  typedef vector<int>::const_iterator edge_iterator;
private:
  list<int> vertices;
  vector<vector<int> > edges;  
public:
  adjacency_list(int n) : edges(n)  { 
    for(int i=0;i!=n;++i) {
      vertices.push_back(i);
    }
  }

  int num_vertices() { return vertices.size(); }
  int num_edges() { return 0; }

  bool is_multi_graph() { return false; }

  // there is no add vertex!
  bool remove(int v) { 
    vertices.remove(v); 
    // remove all edges involving v
    for(edge_iterator i(begin_edges(v));i!=end_edges(v);++i) {
      if(*i != v) {
	std::vector<int>::iterator ne = std::remove(edges[*i].begin(),edges[*i].end(),v);
	edges[*i].erase(ne,edges[*i].end());
      }
    }
    edges[v] = vector<int>(); // save memory
  }

  void add_edge(int from, int to) {
    if(from == to) {
      edges[to].push_back(from);
    } else {
      edges[from].push_back(to);
      edges[to].push_back(from);
    }
  }

  void remove_edge(int from, int to) {
    // this is horribly inefficient
    for(vector<int>::iterator i(edges[from].begin());i!=edges[from].end();++i) {
      if(*i == to) {
	// first match!
	edges[from].erase(i);
	break;
      }
    }

    if(from != to) {
      // only if not loop!
      for(vector<int>::iterator i(edges[to].begin());i!=edges[to].end();++i) {
	if(*i == from) {
	  // first match!
	  edges[to].erase(i);
	  break;
	}
      }
    }
  }

  // Ok, this implementation is seriously inefficient! 
  // could use an indirection trick here as one solution?  
  void contract_edge(int from, int to) { 
    if(from == to) { throw std::runtime_error("cannot contract a loop!"); } 
    for(edge_iterator i(begin_edges(to));i!=end_edges(to);++i) {
      if(*i == to) { 
	// is self loop
	add_edge(from,from);
      } else {
	add_edge(from,*i); 
      }
    }
    remove(to);
  }  

  // These do nothing yet!!!
  int remove_loops() { return 0; }

  vertex_iterator begin_verts() const { return vertices.begin(); }
  vertex_iterator end_verts() const { return vertices.end(); }
  
  edge_iterator begin_edges(int f) const { return edges[f].begin(); }
  edge_iterator end_edges(int f) const { return edges[f].end(); }
};

#endif
