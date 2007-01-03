#ifndef ADJACENCY_LIST_HPP
#define ADJACENCY_LIST_HPP

#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <stdexcept>

using namespace std;

// This graph type is simply the most basic implementation
// you could think of.

// Note, T here must implement the multiple sorted 
// associative container interface defined in the STL
template<class T = std::multiset<int> >
class adjacency_list {
public:
  typedef list<int>::const_iterator vertex_iterator;
  typedef typename T::const_iterator edge_iterator;
private:
  int numedges; // useful cache
  list<int> vertices;
  vector<T> edges;  
public:
  adjacency_list(int n) : edges(n), numedges(0)  { 
    for(int i=0;i!=n;++i) {
      vertices.push_back(i);
    }
  }

  int num_vertices() const { return vertices.size(); }
  int num_edges() const { return numedges; }

  bool is_multi_graph() const { return false; }

  // there is no add vertex!
  bool remove(int v) { 
    vertices.remove(v); 

    // remove all edges involving v
    for(edge_iterator i(begin_edges(v));i!=end_edges(v);++i) {
      if(*i != v) {
	edges[*i].erase(v);
      } 
    }
    numedges -= edges[v].size();
    edges[v] = T(); // save memory
  }

  bool add_edge(int from, int to) {
    bool r(false);

    numedges++;
    
    // the following is a hack to check
    // whether the edge we're inserting
    // is already in the graph or not
    T &tos = edges[to];
    edge_iterator i = tos.lower_bound(from);
    if(i != tos.end() && *i == from) {      
      r=true;
    }
    // hmmm, is this really efficient?
    tos.insert(i,from);

    if(from != to) {
      edges[from].insert(to);
    }

    return r;
  }

  bool remove_edge(int from, int to) {
    bool r=false;

    typename T::iterator i = edges[from].find(to);
    if(i != edges[from].end()) {
      edges[from].erase(i);
      numedges--;
      r = true;
    }
    
    if(from != to && r) {
      i = edges[to].find(from);
      edges[to].erase(i);
    }

    return r;
  }

  // Ok, this implementation is seriously inefficient! 
  // could use an indirection trick here as one solution?  
  //
  // POST: vertex 'from' remains, whilst vertex 'to' is removed
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

  vertex_iterator begin_verts() const { return vertices.begin(); }
  vertex_iterator end_verts() const { return vertices.end(); }
  
  edge_iterator begin_edges(int f) const { return edges[f].begin(); }
  edge_iterator end_edges(int f) const { return edges[f].end(); }
};

#endif
