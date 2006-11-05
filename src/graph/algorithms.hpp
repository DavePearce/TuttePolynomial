#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

#include "nauty.h" // nauty include must come first, otherwise it interferes with std::set
#include <iostream>
#include <set>

template<class T>
void print_graph(ostream &ostr, T const &graph) {
  ostr << "V = { ";
  for(typename T::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    ostr << *i << " ";
  }
  ostr << "}" << endl;

  ostr << "E = { ";

  for(typename T::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    for(typename T::edge_iterator j(graph.begin_edges(*i));j!=graph.end_edges(*i);++j) {
      if(*i <= *j) {
	cout << *i << "--" << *j << " ";
      } 
    }
  }

  ostr << "}" << endl;
}


/**
 * This methods converts a normal graph into a nauty graph.
 * The first parameter is the graph to be converted, whilst
 * the second is the destination graph.  It is assumed there
 * is enough space in the destination parameter.
 */

template<class T>
void graph2nauty(T const &g, graph &ng) {
  setword *ptr = &ng; // a little ugly.  

  // compute the array dimensions
  int maxm = (g.num_vertices() / WORDSIZE);
  if((g.num_vertices() % WORDSIZE) > 0) { maxm = maxm + 1; }

  // now create the graph
  for(typename T::vertex_iterator i(g.begin_verts());i!=g.end_verts();++i) {
    int v = *i;
    for(typename T::edge_iterator j(g.begin_edges(v));j!=g.end_edges(v);++j) {
      int w = *j;
      // represents edge v--w
      int wb = w / WORDSIZE;      // index of word holding succ bit for w
      int wo = w - (wb*WORDSIZE); // offset within word for succ bit
      ptr[wb] |= (1U << wo);        // set succ bit!
    }
    ptr += maxm;
  }
}

void print_nauty(graph &ng, int n) {
  setword *ptr = &ng; // a little ugly.  

  // compute the array dimensions
  int maxm = (n / WORDSIZE);
  if((n % WORDSIZE) > 0) { maxm = maxm + 1; }
  for(int i=0;i!=n;++i) {
    int bp=0;
    for(int j=0;j!=maxm;++j,bp=bp+WORDSIZE,ptr=ptr+1) {
      setword mask = 1U;
      // could eliminate first check in loop condition
      // by splitting out the last iteration.
      for(int k=0;(bp+k) < n && k!=WORDSIZE;++k) {
	if(((*ptr) & mask)) { cout << "1"; }
	else { cout << "0"; }
	mask = mask << 1;
      }
    }
    cout << endl;
  }
}

template<class T>
T nauty2graph(graph &ng, int n) {
  T g(n);
  setword *ptr = &ng; // a little ugly.  

  // compute the array dimensions
  int maxm = (n / WORDSIZE);
  if((n % WORDSIZE) > 0) { maxm = maxm + 1; }
  
  // now build the graph
  for(int i=0;i!=n;++i) {
    int bp=0;
    for(int j=0;j!=maxm;++j,bp=bp+WORDSIZE,ptr=ptr+1) {
      setword mask = 1U;
      // could eliminate first check in loop condition
      // by splitting out the last iteration.
      for(int k=0;(bp+k) < n && k!=WORDSIZE;++k) {
	if((*ptr & mask) != 0 && i < (bp+k)) { g.add_edge(i,bp+k); }
	mask = mask << 1;
      }
    }    
  }

  return g;
}

#endif
