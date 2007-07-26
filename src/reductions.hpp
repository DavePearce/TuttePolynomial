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
P reduce_cycle(line_t const &line, G &graph) {
  // This is a somewhat icky piece of code for reducing 
  // a cycle.

  for(unsigned int j=0;j!=line.size()-1;++j) {
    graph.remove(line[j].second);
  }
    
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

  return xs;
}

template<class G>
line_t trace_line(unsigned int v, G const &graph) {  
  // This is a crude, O(v) time algorithm for tracing out a line in the graph.
  line_t line;
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

template<class G, class P>
P reduce(G &graph) {
  P r = Y(0);

  // I make the following things static
  // in an effort to improve performance.
  static std::vector<line_t> cycles;
  static std::vector<unsigned int> pendants;
  static std::vector<bool> visited;
  // ensure enough space for this graph
  visited.resize(graph.domain_size());
  // make sure to reset visited flags!
  std::fill(visited.begin(),visited.end(),false);

  // now, initialise the worklists
  for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {    
    if(!visited[*i] && graph.num_underlying_edges(*i) == 2) {
      // mark all members as visited, to avoid revisiting
      // them in a potentially quadratic fashion.
      line_t line = trace_line(*i,graph);      
      for(line_t::iterator j(line.begin());j!=line.end();++j) {
	visited[j->second]=true;
      }
      // check if this is a cycle ...
      if(line[0].first == line[line.size()-1].second) {      
	// yes, it is!
	cycles.push_back(line);
      }
    } else if(graph.num_underlying_edges(*i) == 1) {
      // this is a pendant edge
      pendants.push_back(*i);
    }
  }

  // apply the reductions, whilst ensuring that
  // any further cycles / pendants exposed are
  // also reduced upon.
  while(!cycles.empty() || !pendants.empty()) {
    unsigned int w; // this is a candidate cycle/pendant

    if(!pendants.empty()) {
      unsigned int p(pendants.back());
      pendants.pop_back();
      // check that p is still a pendant
      if(graph.num_edges(p) == 0) { continue; }
      // identify the next candidate
      w = graph.begin_edges(p)->first;
      // now, remove it!
      r *= reduce_pendant<G,P>(p,graph);
    } else {
      line_t &cycle(cycles.back());
      r *= reduce_cycle<G,P>(cycle,graph);
      w = cycle[0].first;
      cycles.pop_back();
    }
    
    // now, check whether w has become a cycle or pendant
    if(!visited[w] && graph.num_underlying_edges(w) == 2) {
      line_t line = trace_line(w,graph);      
      visited[w]=true;
      // check if this is a cycle ...
      if(line[0].first == line[line.size()-1].second) {      
	// yes, it is!
	cycles.push_back(line);
      }
    } else if(graph.num_underlying_edges(w) == 1) {
      // this is a pendant edge
      pendants.push_back(w);
    }
  }

  return r;
}


#endif
