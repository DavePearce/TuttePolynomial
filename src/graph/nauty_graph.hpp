#ifndef NAUTYGRAPH_HPP
#define NAUTYGRAPH_HPP

#include "nauty.h" // nauty include must come first, otherwise it interferes with std::set
#include <iostream>
#include <cstring>

// this is a problem
static graph *workspace = NULL;
static int worksize = 0;

class nauty_graph {
private:
  int N;
  int M;      // MAXM, cached for efficiency
  graph *ptr; // pointer to the data
  
public:
  nauty_graph(int N) {
    M = N / WORDSIZE;
    if((N % WORDSIZE) > 0) { M++; }
    ptr = new setword[N*M];
  }

  // copy constructor
  nauty_graph(nauty_graph const &g) {
    N = g.N;
    M = g.M;
    ptr = new setword[N*M];    
    memcpy(ptr,g.ptr,M*N*sizeof(setword));
  }

  ~nauty_graph() { delete [] ptr; }
  
  template<class T>
  nauty_graph(T g) {
    N = g.num_vertices();
    M = N / WORDSIZE;
    if((N % WORDSIZE) > 0) { M++; }
    ptr = new setword[N*M];
    graph *p = ptr;

    // now create the graph
    for(typename T::vertex_iterator i(g.begin_verts());i!=g.end_verts();++i) {
      int v = *i;
      for(typename T::edge_iterator j(g.begin_edges(v));j!=g.end_edges(v);++j) {
	int w = *j;
	// represents edge v--w
	int wb = w / WORDSIZE;      // index of word holding succ bit for w
	int wo = w - (wb*WORDSIZE); // offset within word for succ bit
	p[wb] |= (1U << wo);      // set succ bit!
      }
      p += M;
    }    
  }

  nauty_graph const &operator=(nauty_graph const &g) {
    if(this != &g) { 
      N = g.N;
      M = g.M;
      ptr = new setword[N*M];    
      memcpy(ptr,g.ptr,M*N*sizeof(setword));
    }
    return *this;
  }
  
  // missing hash function
  // missing equality operator

  bool add_edge(int tail, int head) {
    int wb = head / WORDSIZE;      // index of word holding bit for head
    int wo = head - (wb*WORDSIZE); // offset within word for bit
    wb = wb + (tail*M);
    setword mask = (1U << wo);
    bool r = (ptr[wb] & mask) != 0;
    ptr[wb] |= mask;               // set bit!
    return r;
  }

  bool remove_edge(int tail, int head) {
    int wb = head / WORDSIZE;      // index of word holding bit for head
    int wo = head - (wb*WORDSIZE); // offset within word for bit
    wb = wb + (tail*M);
    setword mask = (1U << wo);
    bool r = (ptr[wb] & mask) != 0;
    ptr[wb] = ptr[wb] ^ mask;      // xor bit!
    return r;
  }  

  void makeCanonical() {
    if(worksize < (50*M)) {
      delete [] workspace;
      workspace = new setword[50*M];
      worksize=50*M;
    }
    graph *optr = ptr;
    ptr = new setword[N*M];
    statsblk stats;
    // options
    DEFAULTOPTIONS(opts); // could make static to save space
    opts.getcanon=TRUE;
    opts.writemarkers = FALSE;
    opts.defaultptn = TRUE;
    int lab[N];
    int ptn[N];
    for(int i=0;i!=N;++i) { lab[i] = 0; }
    nvector orbits[N];
    // call nauty
    nauty(optr,lab,ptn,NULL,orbits,&opts,&stats,workspace,worksize,M,N,ptr);
    // tidy up
    delete [] optr;
  }

  void print() {
    setword *p = ptr; 

    cout << "V = { 0.." << N << " }" << endl;
    cout << "E = { ";

    for(int i=0;i!=N;++i) {
      int bp=0;
      for(int j=0;j!=M;++j,bp=bp+WORDSIZE,p=p+1) {
	setword mask = 1U;
	// could eliminate first check in loop condition
	// by splitting out the last iteration.
	for(int k=0;(bp+k) < N && k!=WORDSIZE;++k) {
	  if(((*p) & mask)) { 
	    int tail = (j*WORDSIZE) + k;
	    if(i <= tail) {
	      cout << i << "--" << tail << " "; 
	    }
	  }
	  mask = mask << 1;
	}
      }
    }
    cout << " }" << endl;
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
	for(int k=0;(bp+k) < N && k!=WORDSIZE;++k) {
	  if((*p & mask) != 0 && i < (bp+k)) { g.add_edge(i,bp+k); }
	  mask = mask << 1;
	}
      }    
    }
    
    return g;
  }
};

#endif
