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
      if(*i <= j->first) {
	if(j->second == 1) {
	  ostr << *i << "--" << j->first << " ";
	} else {
	  ostr << *i << "--" << j->first << "(" << j->second << ") ";
	}
      } 
    }
  }

  ostr << "}" << std::endl;
}

// ----------------------------------
// METHODS FOR INTERFACING WITH NAUTY
// ----------------------------------

#define NAUTY_HEADER_SIZE 2

class nauty_graph {
private:
  static setword *tmp_graph;
  static size_t tmp_graph_size;
  static setword *workspace;
  static size_t workspace_size;
  
  // I keep the graph in a completely
  // "flat" format as this makes it quicker
  // to "flatten" it for the cache.
  setword *canong_graph; 
public:

  template<class G>
  nauty_graph(G const &graph) {
    unsigned int N = graph.num_vertices();
    unsigned int NN = N + graph.num_multiedges();
    unsigned int M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;
  
    // check and clear temporary graph buffer
    unsigned int graph_size(sizeof(setword)*NN*M);
    if(graph_size > tmp_graph_size) {
      // need to increase size of temporary buffer!
      delete [] tmp_graph;
      tmp_graph = new setword[sizeof(setword)*NN*M];  
      delete [] workspace;
      workspace = new setword[100 * M];
      workspace_size = 100 * M;
    }
  
    memset(tmp_graph,0,graph_size);

    // build map from graph vertex space to nauty vertex space
    unsigned int vtxmap[graph.domain_size()];
    unsigned int idx=0;
    for(typename G::vertex_iterator i(graph.begin_verts());
	i!=graph.end_verts();++i,++idx) {
      vtxmap[*i] = idx;
    }

    // now, build nauty graph.
    int mes = N; // multi-edge start
    for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
      unsigned int _v = *i;
      for(typename G::edge_iterator j(graph.begin_edges(_v));j!=graph.end_edges(_v);++j) {	
	unsigned int _w = j->first;
      
	// convert vertices into nauty graph vertex space
	unsigned int v = vtxmap[_v];
	unsigned int w = vtxmap[_w];

	// now add this edge(s) to nauty graph
	if(v <= w) {
	  internal_add_edge(v,w,M);
	  unsigned int k=j->second-1;
	  if(k > 0) {
	    // this is a multi-edge!
	    for(;k!=0;--k,++mes) {
	      internal_add_edge(v,mes,M);
	      internal_add_edge(mes,w,M);	    
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

    canong_graph = new setword[((NN*M)+NAUTY_HEADER_SIZE) * sizeof(setword)];

    // call nauty
    nauty(tmp_graph,
	  lab,
	  ptn,
	  NULL,
	  orbits,
	  &opts,
	  &stats,
	  workspace,
	  workspace_size,
	  M,
	  NN, // true graph size, since includes vertices added for multi edges.
	  canong_graph+NAUTY_HEADER_SIZE  // add two for header
	  );
  
    // check for error
    if(stats.errstatus != 0) {
      throw std::runtime_error("internal error: nauty returned an error?");
    }  

    canong_graph[0] = NN;
    canong_graph[1] = N;
  }

  ~nauty_graph();

  template<class G>
  G graph() {
    setword *p = canong_graph;  
    unsigned int N = p[0];
    unsigned int REAL_N = p[1];
    unsigned int M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
    p=p+NAUTY_HEADER_SIZE;
  
    G graph(REAL_N); // should make real N
  
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
      
	setword mask = (1U << (WORDSIZE-wo-1));
	if(p[(j*M)+wb] & mask) { y=x; x=j; }
      }
      graph.add_edge(x,y);
    }

    return graph;    
  }

  bool operator==(nauty_graph const &) const;
  bool operator!=(nauty_graph const &) const;

  unsigned int size() const;
  unsigned int hashcode() const;
  std::string str() const;
  unsigned char *ptr() const { return (unsigned char *) tmp_graph; }
private:
  bool internal_add_edge(int from, int to, int M);  
};

#endif
