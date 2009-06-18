#include "nauty_graph.hpp"

extern "C" {
  uint32_t hashlittle( const void *key, size_t length, uint32_t initval);
}

setword *nauty_graph_buf = NULL;
setword *nauty_workspace = NULL;
size_t nauty_graph_buf_size=0;
size_t nauty_workspace_size = 0;

// add an edge to a nauty graph.  if the edge already exists, then it
// returns false.
bool nauty_graph_add(unsigned char *k1, unsigned int from, unsigned to) {
  setword *p = (setword*) k1;  
  setword N = p[0];
  setword NN = p[1];
  setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;  
  unsigned int wb = (from / WORDSIZE);      
  unsigned int wo = from - (wb*WORDSIZE); 
  
  setword mask = (((setword)1U) << (WORDSIZE-wo-1));
  setword *buffer = p + NAUTY_HEADER_SIZE;
  if(buffer[(to*M)+wb] & mask) { return false; }
  buffer[(to*M)+wb] |= mask; 	  
  
  wb = (to / WORDSIZE);       
  wo = to - (wb*WORDSIZE);  
  mask = (((setword)1U) << (WORDSIZE-wo-1));
  buffer[(from*M)+wb] |= mask;

  p[2]++;

  return true;
}

// delete an edge from the nauty_graph.  note that this method doesn't
// delete any multiple edges, if they exist.
bool nauty_graph_delete(unsigned char *k1, unsigned int from, unsigned to) {
  setword *p = (setword*) k1;  
  setword N = p[0];
  setword NN = p[1];
  setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;  
  unsigned int wb = (from / WORDSIZE);      
  unsigned int wo = from - (wb*WORDSIZE); 
  
  setword mask = (((setword)1U) << (WORDSIZE-wo-1));
  setword *buffer = p + NAUTY_HEADER_SIZE;
  if(buffer[(to*M)+wb] & mask) { return false; }
  buffer[(to*M)+wb] &= mask; 	  
  
  wb = (to / WORDSIZE);       
  wo = to - (wb*WORDSIZE);  
  mask = ~(((setword)1U) << (WORDSIZE-wo-1));
  buffer[(from*M)+wb] &= mask;  

  p[2]++;
  return true;
}

// determine whether two nauty graphs are equal
bool nauty_graph_equals(unsigned char const *_k1, unsigned char const *_k2) {
  setword *k1 = (setword*) _k1;
  setword *k2 = (setword*) _k2;
  
  setword N1 = k1[0];
  setword N2 = k2[0];
  setword REAL_N1 = k1[1];
  setword REAL_N2 = k2[1];
  setword E1 = k1[2];
  setword E2 = k2[2];

  if(N1 != N2 || REAL_N1 != REAL_N2 || E1 != E2) { return false; }
  else {
    k1=k1+NAUTY_HEADER_SIZE;
    k2=k2+NAUTY_HEADER_SIZE;
    setword M = ((N1 % WORDSIZE) > 0) ? (N1 / WORDSIZE)+1 : N1 / WORDSIZE;
    for(int i=0;i!=(N1*M);++i,++k1,++k2) {
      if(*k1 != *k2) { 	return false; }
    }
  }
  // success!
  return true;
}

// make an exact copy of a nauty graph.
void nauty_graph_clone(unsigned char const *graph, unsigned char *output) {
  setword const *p = (setword const *) graph;
  
  setword N = p[0];
  setword NN = p[1];  
  setword M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  
  memcpy(output,graph,((N*M)+NAUTY_HEADER_SIZE) * sizeof(setword));
}

// returns the sizeof the nauty graph in bytes
size_t nauty_graph_size(unsigned char const *key) {
  setword *k1 = (setword*) key;  
  setword N = k1[0];
  setword M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  return ((N*M)+NAUTY_HEADER_SIZE) * sizeof(setword);
}

// generate a hash code from a nauty graph
unsigned int nauty_graph_hashcode(unsigned char const *key) {
  setword *p = (setword*) key;  
  setword N = p[0];
  setword M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  return hashlittle(key,sizeof(setword)*((N*M)+NAUTY_HEADER_SIZE),0);
}

// This method simply accepts a nauty graph and computes a canonical
// graph, placing it in the output array.  The output array must be of
// the right size, as determined by nauty_graph_size().
void nauty_graph_canon(unsigned char const *key, unsigned char *output) {
  setword *p = (setword*) key;  
  setword N = p[0];
  setword NN = p[1];
  setword E = p[2];
  setword M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;

  // allocate a clear space for graph
  if((NN*M) >= nauty_graph_buf_size) {
    // need to increase size of temporary buffer!
    delete [] nauty_graph_buf;
    nauty_graph_buf = new setword[NN*M];  
    nauty_graph_buf_size = NN*M;
    delete [] nauty_workspace;
    nauty_workspace = new setword[100 * M];
    nauty_workspace_size = 100 * M;
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
  nvector orbits[NN]; // unused.

  for(int i=0;i!=NN;++i) { 
    lab[i] = i; 
    ptn[i] = 1;
  }

  ptn[NN-1] = 0;
  ptn[N-1] = 0;

   // call nauty
  nauty((setword*) key + NAUTY_HEADER_SIZE,
	lab,
	ptn,
	NULL,
	orbits,
	&opts,
	&stats,
	nauty_workspace,
	nauty_workspace_size,
	M,
	NN, // true graph size, since includes vertices added for multi edges.
	(setword*) output+NAUTY_HEADER_SIZE  // add two for header
	);
  
  output[0] = NN; 
  output[1] = N;
  output[2] = E;
}


size_t nauty_graph_numedges(unsigned char *graph) {
  setword *p = (setword*) graph;
  return graph[2];
}

// The purpose of the following method is to optimise the process of
// deleting an edge and then computing the canonical graph from it.
// The method assumes that *all* multiple edges must be deleted.
void nauty_graph_canong_delete(unsigned char const *graph, unsigned char *output, unsigned int from, unsigned int to) {
  
}

// The purpose of the following method is to optimise the process of
// contracting an edge, and then computing the canonical graph from
// it.
void nauty_graph_canong_contract(unsigned char const *graph, unsigned char *output, unsigned int from, unsigned int to) {
  
}
