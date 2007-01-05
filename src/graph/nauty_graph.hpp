#ifndef NAUTYGRAPH_HPP
#define NAUTYGRAPH_HPP

#define MAXN 0
#include "nauty.h" // nauty include must come first, otherwise it interferes with std::set
#include <iostream>
#include <cstring>
#include <stdexcept>
#include "../config.h"

// this is a problem
static graph *workspace = NULL;
static int worksize = 0;

template<class Alloc = std::allocator<setword> >
class nauty_graph {
private:
  Alloc alloc; // allocator

  int N;
  int REAL_N;  // real number of vertices in original graph
  int M;       // MAXM, cached for efficiency
  int E;

  graph *ptr; // pointer to the data  
public:
  // copy constructors  
  nauty_graph(nauty_graph const &g) {
    N = g.N;
    M = g.M;
    E = g.E;
    REAL_N = g.REAL_N;
    ptr = alloc.allocate(N*M);    
    memcpy(ptr,g.ptr,sizeof(setword)*M*N);
  }

  // this one is needed for moving between 
  // allocator domains.
  template<class T>
  nauty_graph(nauty_graph<T> const &g) {
    N = g.N;
    M = g.M;
    E = g.E;
    REAL_N = g.REAL_N;
    ptr = alloc.allocate(N*M);    
    memcpy(ptr,g.ptr,sizeof(setword)*M*N);
  }

  ~nauty_graph() { 
    alloc.deallocate(ptr,N*M); 
  }
  
  template<class T>
  nauty_graph(T g) {
    // need to include number of multiedges in the following,
    // since the nauty format does not support multigraphs
    // therefore, we must create an extra vertex for every
    // multiedge in the graph.  Multi self-loops are modelled as a
    // single edge to a fresh vertex.
    N = g.num_vertices() + g.num_multiedges();
    REAL_N = g.num_vertices();
    M = N / WORDSIZE;
    E = 0;
    if((N % WORDSIZE) > 0) { M++; }    
    ptr = alloc.allocate(N*M);
    for(int i=0;i!=N*M;++i) { ptr[i] = 0; } // this is wierd.  I thought this should be initialised to 0 by default?
    graph *p = ptr;

    // now create the graph
    int mestart = REAL_N; // new vertices representing multiedges
    for(int v=0;v!=REAL_N;++v) {
      for(typename T::edge_iterator j(g.begin_edges(v));j!=g.end_edges(v);++j) {	
	int w = *j;
	if(v <= w) {
	  if(!add_edge(v,w)) {
	    // attempt to add edge failed, which means
	    // this must be a multi-edge ...
	    add_edge(v,mestart);
	    add_edge(mestart,w);
	    // increment to ensure fresh vertex for next multi-edge
	    mestart++;
	  }
	  E ++;
	}
      }
    }
  }

  unsigned int num_vertices() const { return N; }
  unsigned int num_edges() const { return E; }
  unsigned int num_real_vertices() const { return REAL_N; }

  nauty_graph const &operator=(nauty_graph const &g) {
    if(this != &g) { 
      N = g.N;
      REAL_N = g.REAL_N;
      M = g.M;
      E = g.E;
      ptr = alloc.allcate(N*M);
      memcpy(ptr,g.ptr,M*N*sizeof(setword));
    }
    return *this;
  }
  
  // missing equality operator
  bool operator==(nauty_graph const &g) const {
    if(N != g.N || E != g.E || REAL_N != g.REAL_N) { return false; }
    else {
      for(int i=0;i!=N*M;++i) {
	if(ptr[i] != g.ptr[i]) { return false; }
      }
    }
    return true;
  }

  // return value indicates whether
  // edge was added or not
  inline bool add_edge(int from, int to) {    
    unsigned int wb = from / WORDSIZE;      
    unsigned int wo = from - (wb*WORDSIZE); 
    setword mask = (1U << (WORDSIZE-wo-1));
    if(ptr[(to*M)+wb] & mask) { return false; }
    ptr[(to*M)+wb] |= mask; 	  

    wb = to / WORDSIZE;       
    wo = to - (wb*WORDSIZE);  
    mask = (1U << (WORDSIZE-wo-1));	  
    ptr[(from*M)+wb] |= mask;
    return true;
  }

  // hash operator
  size_t hash() const {
    int e = N*M;
    size_t r = 0;
    for(int i=0;i!=e;++i) { r ^= ptr[i]; }
    return r;
  }

  void makeCanonical() {
    if(worksize < (50*M)) {
      delete [] workspace;
      workspace = new setword[50*M];
      worksize = 50*M; // could change this parameter ??
    }
    
    graph *optr = ptr;
    ptr = alloc.allocate(N*M);
    statsblk stats;

    // options
    DEFAULTOPTIONS(opts); 
    opts.getcanon=TRUE;
    opts.defaultptn = FALSE;
    opts.writemarkers = FALSE;

    int lab[N];
    int ptn[N];    
    for(int i=0;i!=N;++i) { 
      lab[i] = i; 
      ptn[i] = 1;
    }
    ptn[N-1] = 0;
    ptn[REAL_N-1]=0;
    nvector orbits[N];
    // call nauty
    nauty(optr,lab,ptn,NULL,orbits,&opts,&stats,workspace,worksize,M,N,ptr);

    // tidy up
    alloc.deallocate(optr,N*M);

    // check for error
    if(stats.errstatus != 0) {
      throw std::runtime_error("internal error: nauty returned an error?");
    }
  }

  void print() {
    setword *p = ptr; 

    std::cout << "V = { 0.." << REAL_N << " }" << std::endl;
    std::cout << "E = { ";

    for(int i=0;i!=REAL_N;++i) {
      int bp=0;
      for(int j=0;j!=M;++j,bp=bp+WORDSIZE,p=p+1) {
	setword mask = 1U;
	// could eliminate first check in loop condition
	// by splitting out the last iteration.
	for(int k=0;k!=WORDSIZE;++k) {
	  if(((*p) & mask)) { 
	    int tail = (j*WORDSIZE) + (WORDSIZE-k-1);
	    
	    if(tail >= REAL_N) {
	      // this is a multi-edge.  need to figure out where it
	      // goes
	      graph *p = ptr+(tail*M);
	      tail = WORDSIZE;	      
	      for(int l=0;l!=M;++l,tail=tail+WORDSIZE) {
		// there's a bug here
		if(p[l] != 0) {
		  setword v = p[l];
		  while(v != 1U) { tail--;v >>= 1U; }
		  break;
		}
	      }
	    }
	    if(i <= tail) {
	      std::cout << i << "--" << tail << " "; 
	    }
	  }
	  mask = mask << 1;
	}
      }
    }
    std::cout << " }" << std::endl;
  }

  void print_raw() {
    setword *p = ptr; 

    std::cout << "V = { 0.." << N << " }" << std::endl;
    std::cout << "E = { ";

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
	      std::cout << i << "--" << tail << " "; 
	    }
	  }
	  mask = mask << 1;
	}
      }
    }
    std::cout << " }" << std::endl;
  }

  template<class T>
  T toGraph() {
    T g(N);
    graph *p = ptr;

    // now build the graph
    for(int i=0;i!=N;++i) {
      int bp=0;
      for(int j=0;j!=M;++j,bp=bp+WORDSIZE,p=p+1) {
	setword mask = 1U;
	// could eliminate first check in loop condition
	// by splitting out the last iteration.
	for(int k=0;k!=WORDSIZE;++k) {
	  if((*p & mask) != 0) { g.add_edge(i,bp+ (WORDSIZE-k)); }
	  mask = mask << 1;
	}
      }    
    }
    
    return g;
  }
};

// standard hash function for nauty graph
template<class Alloc = std::allocator<setword> >
class hash_nauty_graph {
public:
  size_t operator()(nauty_graph<Alloc> const &g) const {
    return g.hash();
  }
};

#endif
