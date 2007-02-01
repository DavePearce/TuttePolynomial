#include "algorithms.hpp"

setword nauty_graph_buf[(MAXN*MAXM)];
setword *nauty_workspace = new setword[50*MAXM];
size_t _nauty_workspace_size = 50*MAXM;

extern "C" {
uint32_t hashlittle( const void *key, size_t length, uint32_t initval);
}

void resize_nauty_workspace(int newsize) {
  nauty_workspace = new setword[newsize];
  _nauty_workspace_size = newsize;
}

size_t nauty_workspace_size() {
  return _nauty_workspace_size;
}

bool compare_graph_keys(unsigned char const *_k1, unsigned char const *_k2) {
  setword *k1 = (setword*) _k1;
  setword *k2 = (setword*) _k2;
  
  unsigned int N1 = k1[0];
  unsigned int N2 = k2[0];
  unsigned int REAL_N1 = k1[1];
  unsigned int REAL_N2 = k2[1];

  if(N1 != N2 || REAL_N1 != REAL_N2) { return false; }
  else {
    k1=k1+NAUTY_HEADER_SIZE;
    k2=k2+NAUTY_HEADER_SIZE;
    unsigned int M = ((N1 % WORDSIZE) > 0) ? (N1 / WORDSIZE)+1 : N1 / WORDSIZE;
    for(int i=0;i!=(N1*M);++i,++k1,++k2) {
      if(*k1 != *k2) { 	return false; }
    }
  }
  // success!
  return true;
}

// returns the sizeof the graph key in bytes
size_t sizeof_graph_key(unsigned char const *key) {
  setword *k1 = (setword*) key;  
  unsigned int N = k1[0];
  unsigned int M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  return ((N*M)+NAUTY_HEADER_SIZE) * sizeof(setword);
}

// generate a hash code from a graph key
unsigned int hash_graph_key(unsigned char const *key) {
  setword *p = (setword*) key;  
  unsigned int N = p[0];
  unsigned int M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  return hashlittle(key,sizeof(setword)*((N*M)+NAUTY_HEADER_SIZE),0);
}

void print_graph_key(std::ostream &ostr, unsigned char const *key) {
  setword *p = (setword*) key;  
  unsigned int N = p[0];
  unsigned int REAL_N = p[1];
  unsigned int M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  p=p+NAUTY_HEADER_SIZE;
  
  ostr << "V = { 0.." << N << "(" << REAL_N << ") }" << std::endl;
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

// -------------------------------
// Helper functions
// -------------------------------

bool nauty_add_edge(int from, int to, int M) {    
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

