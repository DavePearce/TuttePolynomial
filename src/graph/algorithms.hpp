#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

#define MAXN 64    // will this be enough?
#include "nauty.h" // nauty include must come first, otherwise it interferes with std::set

#include <iostream>
#include <set>
#include <stdexcept>
#include <cstring>

template<class T>
void print_graph(std::ostream &ostr, T const &graph) {
  ostr << "V = { ";
  for(int i=0;i!=graph.num_vertices();++i) {
    ostr << i << " ";
  }
  ostr << "}" << std::endl;

  ostr << "E = { ";

  for(int i=0;i!=graph.num_vertices();++i) {
    for(typename T::edge_iterator j(graph.begin_edges(i));j!=graph.end_edges(i);++j) {
      if(i <= *j) {
	ostr << i << "--" << *j << " ";
      } 
    }
  }

  ostr << "}" << std::endl;
}

// ----------------------------------
// METHODS FOR INTERFACING WITH NAUTY
// ----------------------------------

#define NAUTY_HEADER_SIZE 2
#define NAUTY_WORKSPACE_SIZE (50*MAXM)
static setword nauty_graph_buf[(MAXN*MAXM)];
static setword nauty_canong_buf[(MAXN*MAXM) + NAUTY_HEADER_SIZE];
static setword nauty_workspace[NAUTY_WORKSPACE_SIZE];

// return value indicates whether
// edge was added or not
template<class T>
inline bool nauty_add_edge(int from, int to, int M) {    
  unsigned int wb = (from / WORDSIZE);      
  unsigned int wo = from - (wb*WORDSIZE); 

  setword mask = (1U << (WORDSIZE-wo-1));
  if(nauty_graph_buf[(to*M)+wb] & mask) { return false; }
  nauty_graph_buf[(to*M)+wb] |= mask; 	  
  
  wb = (to / WORDSIZE);       
  wo = to - (wb*WORDSIZE);  
  mask = (1U << (WORDSIZE-wo-1));	  
  nauty_graph_buf[(from*M)+wb] |= mask;

  return true;
}

bool compare_graph_keys(char *_k1, char *_k2) {
  setword *k1 = (setword*) _k1;
  setword *k2 = (setword*) _k2;
  
  unsigned int N1 = k1[0];
  unsigned int N2 = k2[0];
  
  if(N1 != N2) { return false; }
  else {
    k1++;k2++;
    unsigned int M = ((N1 % WORDSIZE) > 0) ? (N1 / WORDSIZE)+1 : N1 / WORDSIZE;
    for(int i=0;i!=(N1*M);++i,++k1,++k2) {
      if(*k1 != *k2) { return false; }
    }
  }
  // success!
  return true;
}

template<class T>
char *graph_key(T const &graph) {
  unsigned int N = graph.num_vertices();
  unsigned int M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  memset(nauty_graph_buf,sizeof(setword),N*M);
  // quick sanity check
  if((graph.num_vertices() + graph.num_multiedges()) > MAXN) {
    throw std::runtime_error("Graph to large for MAXN setting");
  }
     
  int NN = N; // new vertices representing multiedges
  for(int v=0;v!=N;++v) {
    for(typename T::edge_iterator j(graph.begin_edges(v));j!=graph.end_edges(v);++j) {	
      int w = *j;
      if(v <= w) {
	if(!nauty_add_edge<T>(v,w,M)) {
	  // attempt to add edge failed, which means
	  // this must be a multi-edge ...
	  nauty_add_edge<T>(v,NN,M);
	  nauty_add_edge<T>(NN,w,M);
	  // increment to ensure fresh vertex for next multi-edge
	  NN++;
	}
      }
    }
  }  

  // At this stage, we have constructed a nauty graph representing our
  // original graph.  We now need to run nauty to generate the
  // canonical graph which essentially corresponds to our "graph key"

  statsblk stats;
  static DEFAULTOPTIONS(opts); 
  opts.getcanon=TRUE;
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
  // call nauty
  nauty(nauty_graph_buf,
	lab,
	ptn,
	NULL,
	orbits,
	&opts,
	&stats,
	nauty_workspace,
	NAUTY_WORKSPACE_SIZE,
	M,
	NN, // true graph size, since includes vertices added for multi edges.
	nauty_canong_buf+1 // add one for header
	);
  
  // check for error
  if(stats.errstatus != 0) {
    throw std::runtime_error("internal error: nauty returned an error?");
  }  

  nauty_canong_buf[0] = NN;
  
  return (char*) nauty_canong_buf;
}

// returns the sizeof the graph key 
// in bytes
size_t sizeof_graph_key(char *key) {
  setword *k1 = (setword*) key;  
  unsigned int N = k1[0];
  unsigned int M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  return (N*M) * sizeof(setword);
}

void print_graph_key(std::ostream &ostr, char *key) {
  setword *p = (setword*) key;  
  unsigned int N = p[0];
  unsigned int M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  p=p+1;
  
  ostr << "V = { 0.." << N << " }" << std::endl;
  ostr << "E = { ";
  
  for(int i=0;i!=N;++i) {
    int bp=0;
    for(int j=0;j!=M;++j,bp=bp+WORDSIZE,p=p+1) {
      setword mask = 1U;
      // could eliminate first check in loop condition
      // by splitting out the last iteration.
      for(int k=0;k!=WORDSIZE;++k) {
	if(((*p) & mask)) { 
	  int tail = (j*WORDSIZE) + (WORDSIZE-k-1);
	  
	  if(i <= tail) {
	    ostr << i << "--" << tail << " "; 
	  }
	}
	mask = mask << 1;
      }
    }
  }
  ostr << " }" << std::endl;
}

#endif
