// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

#include <iostream>
#include <set>
#include <stdexcept>
#include <sstream>
#include <cstring>
#include <vector>
#include <deque>

template<class T>
std::string graph_str(T const &graph) {
  std::ostringstream out;
  out << "{";
  bool first=true;
  for(typename T::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    for(typename T::edge_iterator j(graph.begin_edges(*i));j!=graph.end_edges(*i);++j) {
      if(*i <= j->first) {
	if(!first) {
	  out << ",";
	}
	first=false;
	if(j->second == 1) {
	  out << *i << "-" << j->first;
	} else {
	  out << *i << "-" << j->first << "(" << j->second << ")";
	}
      } 
    }
  }

  out << "}";
  return out.str();
}

template<class T>
std::string input_graph_str(T const &graph) {
  std::ostringstream out;
  bool first=true;
  for(typename T::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    for(typename T::edge_iterator j(graph.begin_edges(*i));j!=graph.end_edges(*i);++j) {
      if(*i <= j->first) {
	for(unsigned int k=0;k!=j->second;++k){
	  if(!first) {
	    out << ",";
	  }
	  first=false;
	  out << *i << "--" << j->first;
	}
      } 
    }
  }
  return out.str();
}

template<class T>
void depth_first_search(T const &graph, std::vector<unsigned int> &order) {
    // reset visited information
  std::vector<bool> visited(graph.domain_size(),false);
  // dfs search to identify component roots
  for(typename T::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    if(!visited[*i]) { 
      visit(*i,graph,visited,order);
    }
  }
}  

template<class T>
void visit(unsigned int v, T const &graph, std::vector<bool> &visited, std::vector<unsigned int> &order) {
  visited[v] = true;
  // now, consider edges
  for(typename T::edge_iterator i(graph.begin_edges(v));
      i!=graph.end_edges(v);++i) {
    int w = i->first;
    if(!visited[w]) { 
      visit(w,graph,visited,order); 
    }
  }
  order.push_back(v);
}

template<class T>
void breadth_first_search(T const &graph, std::vector<unsigned int> &order) {
    // reset visited information
  std::vector<bool> visited(graph.domain_size(),false);
  std::deque<int> stack;

  stack.push_back(0); // root
  order.push_back(0);

  while(stack.size() != 0) {
    int v = stack.front();
    stack.pop_front();
    // dfs search to identify component roots
    for(typename T::edge_iterator i(graph.begin_edges(v));
	i!=graph.end_edges(v);++i) {
      int w = i->first;
      if(!visited[w]) { 
	stack.push_back(w);
	visited[w] = true;
	order.push_back(w);
      }
    }
  }
}  



// ----------------------------------
// METHODS FOR INTERFACING WITH NAUTY
// ----------------------------------

// the following is needed for Nauty and determines
// the maximum graph size
#define MAXN 0
#include "nauty.h"

#define NAUTY_HEADER_SIZE 2

extern setword *nauty_graph_buf;
extern size_t nauty_graph_buf_size;
extern setword *nauty_workspace;
extern size_t _nauty_workspace_size;

void print_graph_key(std::ostream &ostr, unsigned char const *key);
bool compare_graph_keys(unsigned char const *_k1, unsigned char const *_k2);
size_t sizeof_graph_key(unsigned char const *key);
unsigned int hash_graph_key(unsigned char const *key);
void print_graph_key(std::ostream &ostr, unsigned char const *key);
bool nauty_add_edge(int from, int to, int M);
// methods for manipulating workspace
size_t nauty_workspace_size();
void resize_nauty_workspace(int newsize);

template<class T>
unsigned char *graph_key(T const &graph) {
  setword N = graph.num_vertices();
  setword NN = N + graph.num_multiedges();
  setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;

  // allocate a clear space for graph
  if((NN*M) >= nauty_graph_buf_size) {
    // need to increase size of temporary buffer!
    delete [] nauty_graph_buf;
    nauty_graph_buf = new setword[NN*M];  
    nauty_graph_buf_size = NN*M;
    // SHOULD CHECK FOR INCREASE IN WORKSPACE SIZE?
    delete [] nauty_workspace;
    nauty_workspace = new setword[100 * M];
    _nauty_workspace_size = 100 * M;
  }

  memset(nauty_graph_buf,0,nauty_graph_buf_size * sizeof(setword));

  // build map from graph vertex space to nauty vertex space
  unsigned int vtxmap[graph.domain_size()];
  unsigned int idx=0;
  for(typename T::vertex_iterator i(graph.begin_verts());
      i!=graph.end_verts();++i,++idx) {
    vtxmap[*i] = idx;
  }

  // now, build nauty graph.
  int mes = N; // multi-edge start
  for(typename T::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    unsigned int _v = *i;
    for(typename T::edge_iterator j(graph.begin_edges(_v));j!=graph.end_edges(_v);++j) {	
      unsigned int _w = j->first;
      
      // convert vertices into nauty graph vertex space
      unsigned int v = vtxmap[_v];
      unsigned int w = vtxmap[_w];

      // now add this edge(s) to nauty graph
      if(v <= w) {
	nauty_add_edge(v,w,M);
	unsigned int k=j->second-1;
	if(k > 0) {
	  // this is a multi-edge!
	  for(;k!=0;--k,++mes) {
	    nauty_add_edge(v,mes,M);
	    nauty_add_edge(mes,w,M);	    
	  }
	} 
      }   
    }
  }  
  
  // At this stage, we have constructed a nauty graph representing our
  // original graph.  We now need to run nauty to generate the
  // canonical graph which essentially corresponds to our "graph key"

  statsblk stats;
  DEFAULTOPTIONS(opts); 
  opts.getcanon = TRUE;
  opts.defaultptn = FALSE;
  opts.writemarkers = FALSE;

  // could optimise this further by making lab and ptn static
  int lab[NN];
  int ptn[NN];    

  for(int i=0;i!=NN;++i) { 
    lab[i] = i; 
    ptn[i] = 1;
  }

  ptn[NN-1] = 0;
  ptn[N-1]=0;
  nvector orbits[NN];

  setword *nauty_canong_buf = new setword[((NN*M)+NAUTY_HEADER_SIZE)];

  // call nauty
  nauty(nauty_graph_buf,
	lab,
	ptn,
	NULL,
	orbits,
	&opts,
	&stats,
	nauty_workspace,
	nauty_workspace_size(),
	M,
	NN, // true graph size, since includes vertices added for multi edges.
	nauty_canong_buf+NAUTY_HEADER_SIZE  // add two for header
	);

  // check for error
  if(stats.errstatus != 0) {
    throw std::runtime_error("internal error: nauty returned an error?");
  }  

  nauty_canong_buf[0] = NN;
  nauty_canong_buf[1] = N;

  return (unsigned char*) nauty_canong_buf;
}

template<class T>
int graph_size(unsigned char *key) {
  setword *p = (setword*) key;  
  setword N = p[0];
  setword REAL_N = p[1];
  return REAL_N;
}

template<class T>
T graph_from_key(unsigned char *key) {
  setword *p = (setword*) key;  
  setword N = p[0];
  setword REAL_N = p[1];
  setword M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  p=p+NAUTY_HEADER_SIZE;

  T graph(REAL_N); // should make real N
  
  // first, deal with normal edges
  for(int i=0;i!=REAL_N;++i) {    
    for(int j=i;j!=REAL_N;++j) {
      unsigned int wb = (i / WORDSIZE);      
      unsigned int wo = i - (wb*WORDSIZE); 
      
      setword mask = (1U << (WORDSIZE-wo-1));
      if(p[(j*M)+wb] & mask) { graph.add_edge(i,j); }
    }
  }

  // second, deal with multi-edges
  for(int i=REAL_N;i!=N;++i) {
    unsigned int y=N;
    unsigned int x=N;
    for(int j=0;j!=REAL_N;++j) {
      unsigned int wb = (i / WORDSIZE);      
      unsigned int wo = i - (wb*WORDSIZE); 

      setword mask = (((setword)1U) << (WORDSIZE-wo-1));      
      if(p[(j*M)+wb] & mask) { y=x; x=j; }
    }
    graph.add_edge(x,y);
  }

  return graph;
}

#endif
