#ifndef ADJACENCY_LIST_HPP
#define ADJACENCY_LIST_HPP

#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <stdexcept>

// This graph type is simply the most basic implementation
// you could think of.

// Note, T here must implement the multiple sorted 
// associative container interface defined in the STL
template<class T = std::map<unsigned int, unsigned int> >
class adjacency_list {
public:
  typedef std::list<unsigned int>::const_iterator vertex_iterator;
  typedef typename T::iterator int_edge_iterator;
  typedef typename T::const_iterator edge_iterator;
private:
  int numedges; // useful cache
  std::list<unsigned int> vertices;
  unsigned int _domain_size;
  std::vector<T> edges;  
  int nummultiedges;
public:
  adjacency_list(int n) : edges(n), numedges(0), nummultiedges(0), _domain_size(n) { 
    for(int i=0;i!=n;++i) { vertices.push_back(i); }
  }

  unsigned int domain_size() const { return _domain_size; }
  unsigned int num_vertices() const { return vertices.size(); }
  unsigned int num_edges() const { return numedges; }
  unsigned int num_underlying_edges() const { return numedges - nummultiedges; }

  unsigned int num_edges(unsigned int vertex) const { 
    // this could also be cached.
    unsigned int count=0;
    for(edge_iterator i(edges[vertex].begin());i!=edges[vertex].end();++i) {
      count += i->second;
    }
    return count; 
  }

  unsigned int num_underlying_edges(unsigned int vertex) const { 
    return edges[vertex].size();
  }

  unsigned int num_edges(unsigned int from, unsigned int to) {
    T &fset = edges[from];         
    typename T::iterator fend = fset.end(); // optimisation
    typename T::iterator i = fset.find(to);
    if(i != fend) {
      return i->second;
    } else {
      return 0;
    }
  }

  unsigned int num_multiedges() const { return nummultiedges; }
  bool is_multi_graph() const { return nummultiedges > 0; }
  
  // there is no add vertex!
  void clear(unsigned int v) { 
    // Now, clear all edges involving v

    T &vset = edges[v];                    // optimisation
    int_edge_iterator vend(vset.end());        // optimisation
    int_edge_iterator i(vset.begin());
    for(;i!=vend;++i) {
      unsigned int k = i->second;
      nummultiedges -= (k - 1);
      numedges -= k;
      if(i->first != v) {
	edges[i->first].erase(v);
      } 
    }
    edges[v] = T(); // save memory
  }

  void clearall() {
    for(vertex_iterator i(begin_verts());i!=end_verts();++i) {
      clear(*i);
    }
  }

  // remove vertex from graph
  void remove(unsigned int v) {
    vertices.remove(v);
    clear(v);
  }

  bool add_edge(unsigned int from, unsigned int to, unsigned int c) {
    numedges += c;
    
    // the following is a hack to check
    // whether the edge we're inserting
    // is already in the graph or not
    T &tos = edges[to];                     // optimisation
    int_edge_iterator i = tos.find(from);
    if(i != tos.end()) {
      // edge already present so another multi-edge!
      nummultiedges += c;
      i->second += c;
      // don't want to increment same edge twice!
      if(from != to) {
	i = edges[from].find(to);
	i->second += c;
      }
      return true;
    } else {
      // completely new edge!
      nummultiedges += (c - 1);
      tos.insert(std::make_pair(from,c));
      // self-loops only get one mention in the edge set
      if(from != to) { 
	edges[from].insert(std::make_pair(to,c));
      }
      return false;
    }
  }

  bool add_edge(unsigned int from, unsigned int to) { return add_edge(from,to,1); }

  bool remove_edge(unsigned int from, unsigned int to, unsigned int c) {
    T &fset = edges[from];                  // optimisation
    typename T::iterator fend = fset.end(); // optimisation
    typename T::iterator i = fset.find(to);
    if(i != fend) {
      if(i->second > c) {
	// this is a multi-edge, so decrement count.
	nummultiedges -= c;
	numedges -= c;
	i->second -= c;
	if(from != to) {
	  i = edges[to].find(from);
	  i->second -= c;
	}
      } else {
	// clear our ALL edges
	numedges -= i->second;
	nummultiedges -= (i->second - 1);
	fset.erase(to);	
	if(from != to) {
	  edges[to].erase(from);
	}
      }
      return true;
    }

    return false;
  }

  unsigned int remove_all_edges(unsigned int from, unsigned int to) {
    // remove all edges "from--to"
    unsigned int r=0;
    T &fset = edges[from];                  // optimisation
    typename T::iterator fend = fset.end(); // optimisation
    typename T::iterator i = fset.find(to);
    if(i != fend) {
      r = i->second;
      numedges -= r;
      nummultiedges -= (r - 1);
      fset.erase(to);	
      if(from != to) { edges[to].erase(from); }
    }

    return r;
  }

  bool remove_edge(unsigned int from, unsigned int to) {
    return remove_edge(from,to,1);
  } 

  // Ok, this implementation is seriously inefficient! 
  // could use an indirection trick here as one solution?  
  //
  // POST: vertex 'from' remains, whilst vertex 'to' is removed
  void contract_edge(unsigned int from, unsigned int to) { 
    if(from == to) { throw std::runtime_error("cannot contract a loop!"); } 
    for(edge_iterator i(begin_edges(to));i!=end_edges(to);++i) {
      if(i->first == to) { 
	// is self loop
	add_edge(from,from,i->second);
      } else {
	add_edge(from,i->first,i->second); 
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
