#ifndef REDUCTIONS_HPP
#define REDUCTIONS_HPP

#include <stdexcept>

template<class G, class P>
xy_term reduce_pendants(G &graph) {
  unsigned int num_pendants(0);

  std::vector<unsigned int> pendants;
  
  for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    if(graph.num_edges(*i) == 1) {
      pendants.push_back(*i);
    }
  }

  while(pendants.size() > 0) {
    unsigned int p(pendants.back());
    pendants.pop_back();
    num_pendants++;
    // now, recursively eliminate any pendants created by this
    typename G::edge_iterator i(graph.begin_edges(p));
    unsigned int w(i->first);
    graph.remove(p);
    if(graph.num_edges(w) == 1) { pendants.push_back(w); } 
  }

  /*
  while(graph.num_pendant_vertices() > 0) {
    unsigned int l = graph.select_pendant_vertex();
    graph.remove(l);
    num_pendants++;
  }
  */

  return X(num_pendants);
}

template<class G, class P>
P reduce_multi_pendants(G &graph) {
  P r = Y(0);

  std::vector<unsigned int> pendants;
  
  for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    if(graph.num_underlying_edges(*i) == 1) {
      pendants.push_back(*i);
    }
  }

  while(pendants.size() > 0) {
    unsigned int p(pendants.back());
    pendants.pop_back();
    // now, recursively eliminate any pendants created by this
    typename G::edge_iterator i(graph.begin_edges(p));
    unsigned int w(i->first);
    unsigned int count(i->second);

    P tmp(X(1));
    if(count > 1) {  tmp += Y(1,count-1); }
    r *= tmp;

    graph.remove(p);
    if(graph.num_underlying_edges(w) == 1) { pendants.push_back(w); } 
  }

  return r;
}

template<class G>
std::vector<triple<unsigned int, unsigned int, unsigned int> > trace_line(unsigned int v, G const &graph) {
  // This is a crude, O(v) time algorithm for tracing out a line in the graph.
  std::vector<triple<unsigned int, unsigned int, unsigned int> > line;
  unsigned int start=v; // needed to protect against cycles

  // First, find one end of the line  
  unsigned int w = graph.begin_edges(v)->first;
  
  while(graph.num_edges(v) == 2) {    
    // determine edge from w
    typename G::edge_iterator i(graph.begin_edges(v));
    unsigned int u = i->first;
    if(u == w) { u = (++i)->first; }
    if(u == start) { break; }
    w = v;
    v = u;
  }

  // Second, traverse the entire line
  start = v;
  std::swap(v,w);
  line.push_back(make_triple(w,v,1U));

  while(graph.num_edges(v) == 2) {
    // determine edge from w
    typename G::edge_iterator i(graph.begin_edges(v));
    unsigned int u = i->first;
    if(u == w) { u = (++i)->first; }
    if(u == start) { break; }
    w = v;
    v = u;
    line.push_back(make_triple(w,v,1U)); 
  }  

  return line;
}

template<class G>
std::vector<triple<unsigned int, unsigned int, unsigned int> > select_line(G const &graph) {
  std::vector<bool> visited(graph.domain_size(),false);
  for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {    
    if(!visited[*i] && graph.num_edges(*i) == 2) {
      std::vector<triple<unsigned int, unsigned int, unsigned int> > line = trace_line(*i,graph);
      // now, check line is not a line bridge
      for(unsigned int j=0;j!=line.size();++j) {
	visited[line[j].first] = true;
	if(!graph.on_spanning_tree(line[j].first,line[j].second)) {
	  // Ok, it's definitely *not* a line bridge
	  std::cout << "MATCHED: ";
	  for(unsigned int k=0;k!=line.size();++k) {
	    if(k!=0) { std::cout << ", "; }
	    std::cout << line[k].first << "--" << line[k].second << "(" << line[k].third << ")";
	  }
	  std::cout << std::endl;
	  return line;
	}
      }
    }
  }
  
  // return nothing to signal no lines found
  return std::vector<triple<unsigned int, unsigned int, unsigned int> >();
}

#endif
