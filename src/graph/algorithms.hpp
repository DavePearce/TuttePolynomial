#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

#include "../config.h"

#include <iostream>
#include <set>
#include <stdexcept>
#include <cstring>

template<class T>
void print_graph(std::ostream &ostr, T const &graph) {
  ostr << "V = { ";
  for(typename T::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    ostr << *i << " ";
  }
  ostr << "}" << std::endl;

  ostr << "E = { ";
  for(typename T::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    for(typename T::edge_iterator j(graph.begin_edges(*i));j!=graph.end_edges(*i);++j) {
      if(*i <= *j) {
	ostr << *i << "--" << *j << " ";
      } 
    }
  }

  ostr << "}" << std::endl;
}

// ----------------------------------
// METHODS FOR INTERFACING WITH NAUTY
// ----------------------------------

#define NAUTY_HEADER_SIZE 2

extern setword nauty_graph_buf[];
extern setword *nauty_workspace;

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
  unsigned int N = graph.num_vertices();
  unsigned int NN = N + graph.num_multiedges();
  unsigned int M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;
  // quick sanity check
  if(NN > MAXN) { throw std::runtime_error("graph to large for MAXN setting --- try changing it in config.h"); }

  // clear temporary space
  memset(nauty_graph_buf,0,sizeof(setword)*NN*M);

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
      unsigned int _w = *j;

      // convert vertices into nauty graph vertex space
      unsigned int v = vtxmap[_v];
      unsigned int w = vtxmap[_w];

      // now add this edge to nauty graph
      if(v <= w) {
	if(!nauty_add_edge(v,w,M)) {
	  // attempt to add edge failed, which means
	  // this must be a multi-edge ...
	  nauty_add_edge(v,mes,M);
	  nauty_add_edge(mes,w,M);
	  // increment to ensure fresh vertex for next multi-edge
	  mes++;
	} 
      }
    }
  }  

  // At this stage, we have constructed a nauty graph representing our
  // original graph.  We now need to run nauty to generate the
  // canonical graph which essentially corresponds to our "graph key"

  statsblk stats;
  DEFAULTOPTIONS(opts); 
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

  setword *nauty_canong_buf = new setword[((NN*M)+NAUTY_HEADER_SIZE) * sizeof(setword)];

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


#endif
