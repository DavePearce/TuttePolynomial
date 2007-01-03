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
  int nummultiedges;
public:
  adjacency_list(int n) : edges(n), numedges(0), nummultiedges(0) { 
    for(int i=0;i!=n;++i) {
      vertices.push_back(i);
    }
  }

  int num_vertices() const { return vertices.size(); }
  int num_edges() const { return numedges; }
  int num_multiedges() { return nummultiedges; }

  bool is_multi_graph() const { return nummultiedges > 0; }
  
  // there is no add vertex!
  bool remove(int v) { 
    vertices.remove(v); 

    // Now, remove all edges involving v
    //
    // I make j one step ahead of i so that I can tell whether I'm
    // deleting a multi edge or not.  Also, it means I don't
    // need to call erase twice for the same vertex, since only
    // one call is necessary to remove all traces of this "v"

    T &vset = edges[v];                    // optimisation
    edge_iterator vend(vset.end());        // optimisation
    edge_iterator i(vset.begin());
    edge_iterator j(i);
    ++j;
    for(;i!=vend;++i,++j) {
      if(*i != v) {
	if(j != vend && *j == *i) {
	  // removing a multi edge
	  nummultiedges--;
	} else {
	  edges[*i].erase(v);
	}
      } 
    }
    numedges -= vset.size();
    edges[v] = T(); // save memory
  }

  bool add_edge(int from, int to) {
    bool r(false);

    numedges++;
    
    // the following is a hack to check
    // whether the edge we're inserting
    // is already in the graph or not
    T &tos = edges[to];                     // optimisation
    edge_iterator i = tos.lower_bound(from);
    if(i != tos.end() && *i == from) {      
      nummultiedges++;
      r=true;
    }
    // hmmm, is this really efficient?
    tos.insert(i,from);

    // self-loops only get one mention in the edge set
    if(from != to) { edges[from].insert(to); }

    return r;
  }

  bool remove_edge(int from, int to) {
    bool r=false;
    T &fset = edges[from];                  // optimisation
    typename T::iterator fend = fset.end(); // optimisation
    typename T::iterator i = fset.find(to);
    if(i != fend) {
      fset.erase(i++);
      numedges--;
      r = true;
      // check if this was a multi-edge or not.
      if(i != fend && *i == to) { nummultiedges--; }
    }

    if(from != to && r) {
      T &tset = edges[to];                  // optimisation    
      i = tset.find(from);
      tset.erase(i);
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
