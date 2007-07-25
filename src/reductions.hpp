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
    // Check whether p is still a pendant
    if(graph.num_edges(p) == 0) { continue; }
    // Generate multiply factor
    typename G::edge_iterator i(graph.begin_edges(p));
    unsigned int w(i->first);
    unsigned int count(i->second);

    P tmp(X(1));
    if(count > 1) {  tmp += Y(1,count-1); }
    r *= tmp;
    graph.remove(p);
    // Recursively eliminate any pendants created by this
    if(graph.num_underlying_edges(w) == 1) { 
      pendants.push_back(w); } 
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
P reduce_cycles(G &graph) {
  // This is not exactly the most efficient algorithm
  // especially since it will quadratically visit
  // lines which are not in fact cycles.
  P r = Y(0);

  std::vector<unsigned int> candidates;
  std::vector<bool> visited(graph.domain_size(),false);

  for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {    
    if(graph.num_underlying_edges(*i) == 2) {
      candidates.push_back(*i);
    }
  }

  while(!candidates.empty()) {
    unsigned int c(candidates.back());
    candidates.pop_back();    

    if(visited[c]) { continue; }
        
    std::vector<triple<unsigned int, unsigned int, unsigned int> > line = trace_line(c,graph);
    
    // mark whole line as visited
    for(unsigned int j=0;j!=line.size()-1;++j) {
      visited[line[j].second]=true;
    }
    
    if(line[0].first == line[line.size()-1].second) {      
      // Found a cycle!
      for(unsigned int j=0;j!=line.size()-1;++j) {
	graph.remove(line[j].second);
      }

      // Now, build its factor!
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
      r *= xs;

      // Finally, check if this has exposed another candidate
      if(graph.num_underlying_edges(line[0].first) == 2) {
	// yes it has!
	candidates.push_back(line[0].first);
      }
    }
  }

  return r;
}

#endif
