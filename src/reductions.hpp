// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#ifndef REDUCTIONS_HPP
#define REDUCTIONS_HPP

#include <stdexcept>
#include <vector>
#include "misc/triple.hpp"

typedef triple<unsigned int, unsigned int, unsigned int> edge_t;
typedef std::vector<edge_t> line_t;

template<class G, class P>
P reduce_pendant(unsigned int p, G &graph) {
  unsigned int count(graph.num_edges(p));
  graph.remove(p);
  
  P r = X(1);
  if(count > 1) { r += Y(1,count-1); }
  return r;
}

template<class G, class P>
P reduce_tree(G &graph) {
  P r(Y(0));

  for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    for(typename G::edge_iterator j(graph.begin_edges(*i));j!=graph.end_edges(*i);++j) {
      if(*i >= j->first) {
	P xy = X(1);
	if(j->second > 1) { xy += Y(1,j->second-1); }
	r *= xy;
      }
    }
  }  
  
  return r;
}

template<class G, class P>
P reduce_cycle(G const &graph) {
  // This is a somewhat icky piece of code for reducing 
  // a cycle.  it's really a hack at the moment.

  static std::vector<edge_t> line;

  unsigned int last = *graph.begin_verts();
  unsigned int v = *graph.begin_verts();
  unsigned int s = *graph.begin_verts();

  do {
    typename G::edge_iterator j(graph.begin_edges(v));
    if(j->first == last) { ++j; }
    last = v;
    line.push_back(edge_t(v,j->first,j->second));
    v = j->first;
  } while(v != s);

  P xs(X(1)), acc(X(1));
  if(line[0].third > 1) { 
    acc += Y(1,line[0].third-1); 
    xs += Y(1,line[0].third-1); 
  }
      
  for(unsigned int k=1;k<line.size()-1;++k) {
    P tmp(X(1));
    if(line[k].third > 1) { tmp += Y(1,line[k].third-1); }
    if(line[k+1].third > 1) { xs *= Y(0,line[k+1].third-1); }
    acc *= tmp;
    xs += acc;
  }      
  
  P ys = Y(line[0].third,line[0].third);
  for(unsigned int k=1;k<line.size();++k) {
    if(line[k].third > 1) { ys *= Y(0,line[k].third-1); }
  }
  xs += ys;

  line.clear(); // clear it for next time around

  return xs;
}

template<class G>
unsigned int reduce_loops(G &graph) {   
  unsigned int c=0U;    
  for(typename G::vertex_iterator i(graph.begin_verts());
      i!=graph.end_verts();++i) {
    c += graph.remove_all_edges(*i,*i);
  }
  return c;
}

// THIS ALGORITHM IS BROKEN!
template<class G>
line_t trace_line(unsigned int v, unsigned int u, G const &graph) {  
  // This is a crude, O(v) time algorithm for tracing out a line in the graph.
  line_t line;
  if(graph.num_edges(v) != 2) { v = u; }
  unsigned int start=v; // needed to protect against cycles

  // First, find one end of the line  
  unsigned int w = graph.begin_edges(v)->first;
  
  while(graph.num_underlying_edges(v) == 2) {    
    // determine edge from w
    typename G::edge_iterator i(graph.begin_edges(v));
    unsigned int u = i->first;
    if(u == w) { u = (++i)->first; }
    w = v;
    v = u;
    if(v == start) { break; }
  }

  // Second, traverse the entire line
  start = v;
  std::swap(v,w);
  line.push_back(make_triple(w,v,graph.num_edges(w,v)));

  while(graph.num_underlying_edges(v) == 2) {
    // determine edge from w
    typename G::edge_iterator i(graph.begin_edges(v));
    unsigned int u = i->first;
    if(u == w) { u = (++i)->first; }
    w = v;
    v = u;
    line.push_back(make_triple(w,v,i->second)); 
    if(v == start) { break; }
  }  

  return line;
}

#endif
