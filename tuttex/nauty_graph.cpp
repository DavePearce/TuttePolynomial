#include <sstream>
#include "nauty_graph.hpp"

using namespace std;

extern "C" {
  uint32_t hashlittle( const void *key, size_t length, uint32_t initval);
}

setword *nauty_graph_buf = NULL;
setword *nauty_workspace = NULL;
size_t nauty_graph_buf_size=0;
size_t nauty_workspace_size = 0;

// add an edge to a nauty graph.  if the edge already exists, then it
// returns false.
bool nauty_graph_add(unsigned char *graph, unsigned int from, unsigned to) {
  setword *p = (setword*) graph;  
  setword N = p[0];
  setword NN = p[1];
  setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;  
  setword *buffer = p + NAUTY_HEADER_SIZE;

  unsigned int wb = (from / WORDSIZE);      
  unsigned int wo = from - (wb*WORDSIZE);   
  setword mask = (((setword)1U) << (WORDSIZE-wo-1));
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
bool nauty_graph_delete(unsigned char *graph, unsigned int from, unsigned to) {
  setword *p = (setword*) graph;  
  setword N = p[0];
  setword NN = p[1];
  setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;  
  setword *buffer = p + NAUTY_HEADER_SIZE;

  unsigned int wb = (from / WORDSIZE);      
  unsigned int wo = from - (wb*WORDSIZE); 
  setword mask = (((setword)1U) << (WORDSIZE-wo-1));
  if(!(buffer[(to*M)+wb] & mask)) { return false; }
  buffer[(to*M)+wb] &= ~mask; 	  
  
  wb = (to / WORDSIZE);       
  wo = to - (wb*WORDSIZE);  
  mask = ((setword)1U) << (WORDSIZE-wo-1);
  buffer[(from*M)+wb] &= ~mask;  

  p[2]--;
  return true;
}

// delete a vertex from the nauty_graph.
void nauty_graph_delvert(unsigned char const *input, unsigned char *output, unsigned int vertex) {
  setword *p_in = (setword*) input;  
  setword *p_out = (setword*) output;  

  setword N_IN = p_in[0];
  setword NN_IN = p_in[1];
  setword M_IN = ((NN_IN % WORDSIZE) > 0) ? (NN_IN / WORDSIZE)+1 : NN_IN / WORDSIZE;  

  setword NN_OUT = NN_IN - 1U;
  setword M_OUT = ((NN_OUT % WORDSIZE) > 0) ? (NN_OUT / WORDSIZE)+1 : NN_OUT / WORDSIZE;  

  p_out[0] = N_IN - 1U;
  p_out[1] = NN_OUT;

  setword *inbuffer = p_in + NAUTY_HEADER_SIZE;  
  setword *outbuffer = p_out + NAUTY_HEADER_SIZE;    

  // the following loop could certainly be made more efficient.
  unsigned int oi = 0;
  for(unsigned int i=0;i!=NN_IN;++i) {
    if(i == vertex) { continue; }

    unsigned int oj = 0;
    for(unsigned int j=0;j!=NN_IN;++j) {
      if(j == vertex) { continue; }

      unsigned int wb = (j / WORDSIZE);      
      unsigned int wo = j - (wb*WORDSIZE);  
      setword mask = (((setword)1U) << (WORDSIZE-wo-1));

      if(inbuffer[(i*M_IN)+wb] & mask) {
	// edge found, therefore add it!
	wb = (oj / WORDSIZE);      
	wo = oj - (wb*WORDSIZE);  
	mask = (((setword)1U) << (WORDSIZE-wo-1));	
	outbuffer[(oi*M_OUT)+wb] |= mask;
      }
      
      oj++;
    }

    oi++;
  }

  // finally, count the number of edges which have been deleted.
  unsigned int deledges = 0;
  for(unsigned int i=0;i!=M_IN;++i) {
    setword tmp = inbuffer[(vertex*M_IN) + i];
    while(tmp != 0U) {
      if(tmp & 1U) { deledges++; }
      tmp = tmp >> 1U;
    }
  }

  p_out[2] = p_in[2] - deledges;
}

// Extract a subgraph from the input graph.  The subgraph is
// determined by the vertices in the component list.
void nauty_graph_extract(unsigned char *graph, unsigned char *output, unsigned int const *component, unsigned int N) {
  // this loop could be optimised somewhat to avoid recalculating M
  // etc for each edge addition.

  setword *op = (setword*) output;
  op[0] = N;
  op[1] = N;

  for(unsigned int i=0;i<N;++i) {
    for(unsigned int j=(i+1);j<N;++j) {
      unsigned int mi = component[i];
      unsigned int mj = component[j];
      if(nauty_graph_is_edge(graph,mi,mj)) {
	nauty_graph_add(output,i,j);
	nauty_graph_delete(graph,mi,mj);
      }
    }
  }
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
  setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;
  
  memcpy(output,graph,((N*M)+NAUTY_HEADER_SIZE) * sizeof(setword));
}

// returns the sizeof the nauty graph in bytes
size_t nauty_graph_size(unsigned char const *key) {
  setword *k1 = (setword*) key;  
  setword NN = k1[1];
  setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;
  return ((NN*M)+NAUTY_HEADER_SIZE) * sizeof(setword);
}

// generate a hash code from a nauty graph
unsigned int nauty_graph_hashcode(unsigned char const *key) {
  setword *p = (setword*) key;  
  setword NN = p[1];
  setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;

  return hashlittle(key,sizeof(setword)*((NN*M)+NAUTY_HEADER_SIZE),0);
}

// This method simply accepts a nauty graph and computes a canonical
// graph, placing it in the output array.  The output array must be of
// the right size, as determined by nauty_graph_size().
void nauty_graph_canon(unsigned char const *key, unsigned char *output) {
  setword *p = (setword*) key;  
  setword *op = (setword*) output;  
  setword N = p[0];
  setword NN = p[1];
  setword E = p[2];
  setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;

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
  
  op[0] = N; 
  op[1] = NN;
  op[2] = E;
}


// The purpose of the following method is to optimise the process of
// deleting an edge and then computing the canonical graph from it.
// The method assumes that *all* multiple edges must be deleted.
void nauty_graph_canong_delete(unsigned char const *graph, unsigned char *output, unsigned int from, unsigned int to) {
  unsigned char *tgraph = (unsigned char *) graph;
  // To avoid creating a second copy of graph, I actually delete the
  // edge from it temporarily.  Then I add it back so it seems as
  // though nothing has changed.
  nauty_graph_delete(tgraph,from,to);
  nauty_graph_canon(tgraph,output);
  nauty_graph_add(tgraph,from,to);
}

// The purpose of the following method is to optimise the process of
// contracting two vertices together.  The new vertex retains the
// smaller of the two labels.
void nauty_graph_canong_contract(unsigned char const *graph, unsigned char *output, unsigned int from, unsigned int to, bool loops) {
  unsigned char *tgraph = (unsigned char *) graph;
  // To avoid creating a second copy of graph, I actually delete the
  // edge from it temporarily.  Then I add it back so it seems as
  // though nothing has changed.
  nauty_graph_delete(tgraph,from,to);
  if(from > to) { std::swap(from,to); }
  // determine dimensions of output graph based on input graph.
  setword *p = (setword *) graph;
  setword NN = p[1] - 1U; // account for deleted vertex
  setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;  

  // allocate a clear space for graph
  if(((NN*M)+NAUTY_HEADER_SIZE) >= nauty_graph_buf_size) {
    // need to increase size of temporary buffer!
    delete [] nauty_graph_buf;
    nauty_graph_buf = new setword[(NN*M) + NAUTY_HEADER_SIZE];  
    nauty_graph_buf_size = (NN*M) + NAUTY_HEADER_SIZE;    
  }

  // clear the temporary buffer.
  memset(nauty_graph_buf,0,((NN*M) + NAUTY_HEADER_SIZE)*sizeof(setword));

  // construct new graph with given vertex deleted.
  nauty_graph_delvert(graph,(unsigned char*)nauty_graph_buf,to);

  // add all edges from the deleted vertex to the remaining
  // vertex
  setword NN_IN = NN+1;
  setword M_IN = ((NN_IN % WORDSIZE) > 0) ? (NN_IN / WORDSIZE)+1 : NN_IN / WORDSIZE;  
  setword *inbuffer = p+NAUTY_HEADER_SIZE;
  setword *outbuffer = nauty_graph_buf+NAUTY_HEADER_SIZE;
  inbuffer += to*M_IN;
  for(unsigned int i=0;i!=NN_IN;++i) {
    unsigned int wb = (i / WORDSIZE);      
    unsigned int wo = i - (wb*WORDSIZE);  
    setword mask = (((setword)1U) << (WORDSIZE-wo-1));
    
    if((inbuffer[wb] & mask) && (loops || (i != to && i != from))) {
      unsigned int w = i;
      if(i == to) { 
	w = from;
      } else if(i > to) { w--; }
      
      wb = (w / WORDSIZE);      
      wo = w - (wb*WORDSIZE);   
      mask = (((setword)1U) << (WORDSIZE-wo-1));
      if(!(outbuffer[(from*M)+wb] & mask)) { 
	outbuffer[(from*M)+wb] |= mask; 	  	
	wb = (from / WORDSIZE);       
	wo = from - (wb*WORDSIZE);  
	mask = (((setword)1U) << (WORDSIZE-wo-1));
	outbuffer[(w*M)+wb] |= mask;	
	nauty_graph_buf[2]++;
      }
    } 
  }

  // finally, compute canonical labelling
  nauty_graph_canon((unsigned char const *)nauty_graph_buf,output);
  nauty_graph_add(tgraph,from,to);
}

// Generate a human readable string representing the nauty graph.
string nauty_graph_str(unsigned char const *graph) {
  setword *p = (setword *) graph;
  setword N = p[0];
  setword NN = p[1];
  setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;  
  setword *buffer = p + NAUTY_HEADER_SIZE;    

  std::ostringstream out;
  out << "[N=" << N << ",NN=" << NN << ",E=" << p[2] << "]{";
  
  bool firstTime = true;
  for(unsigned int i=0;i!=NN;++i) {
    for(unsigned int j=(i+1);j<NN;++j) {
      if(nauty_graph_is_edge(graph,i,j)) {
	if(!firstTime) {
	  out << ",";
	}
	firstTime=false;
	out << i << "--" << j;
      }
    }    
  }

  out << "}";

  return out.str();
}
