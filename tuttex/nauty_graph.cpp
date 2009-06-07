#include "nauty_graph.hpp"

extern "C" {
uint32_t hashlittle( const void *key, size_t length, uint32_t initval);
}

nauty_graph::nauty_graph(unsigned int nverts) {
  buffer = new unsigned char[nverts*nverts];
  ptn = new unsigned int[nverts];
  labs = new unsigned int[nverts];

  for(unsigned int i=0;i!=nverts;++i) {
    labs[i]=i;
    ptn[i]=1;
  }

  N = nverts;
  NN = nverts;
  E = 0;
}

nauty_graph::nauty_graph(nauty_graph const &graph) {
  N = graph.N;
  NN = graph.NN;
  E = graph.E;

  buffer = new unsigned char[N*N];
  ptn = new unsigned int[N];
  labs = new unsigned int[N];

  for(unsigned int i=0;i!=N;++i) {
    labs[i]=graph.labs[i];
    ptn[i]=graph.ptn[i];
  }
}

nauty_graph::~nauty_graph() {
  delete buffer;
  delete ptn;
  delete labs;
} 

nauty_graph &nauty_graph::operator=(nauty_graph const &graph) {
  if(this != &graph) {
    delete buffer;
    delete labs;
    delete ptn;
    
    N = graph.N;
    NN = graph.NN;
    E = graph.E;
    
    buffer = new unsigned char[N*N];
    ptn = new unsigned int[N];
    labs = new unsigned int[N];
    
    for(unsigned int i=0;i!=N;++i) {
      labs[i]=graph.labs[i];
      ptn[i]=graph.ptn[i];
    }
  }
  return *this;
}

int nauty_graph::num_vertices() const {
  return N;
}

int nauty_graph::num_edges() const {
  return E;
}

bool nauty_graph::add_edge(unsigned int from, unsigned to) {
  setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;  
  unsigned int wb = (from / WORDSIZE);      
  unsigned int wo = from - (wb*WORDSIZE); 
  
  setword mask = (((setword)1U) << (WORDSIZE-wo-1));
  if(buffer[(to*M)+wb] & mask) { return false; }
  buffer[(to*M)+wb] |= mask; 	  
  
  wb = (to / WORDSIZE);       
  wo = to - (wb*WORDSIZE);  
  mask = (((setword)1U) << (WORDSIZE-wo-1));
  buffer[(from*M)+wb] |= mask;

  return true;
}

void nauty_graph::remove_edge(unsigned int from, unsigned to) {
  setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;  
  unsigned int wb = (from / WORDSIZE);      
  unsigned int wo = from - (wb*WORDSIZE); 
  
  setword mask = ~(((setword)1U) << (WORDSIZE-wo-1));
  buffer[(to*M)+wb] &= mask; 	  
  
  wb = (to / WORDSIZE);       
  wo = to - (wb*WORDSIZE);  
  mask = (((setword)1U) << (WORDSIZE-wo-1));
  buffer[(from*M)+wb] &= mask;  
}

void nauty_graph::contract_edge(unsigned int from, unsigned to) {
  // it's here that we must essentially "union-find" the vertices in 
}

bool nauty_graph::operator==(nauty_graph const &graph) const {
  if(graph.NN != graph.NN || graph.E != graph.E) { return false; }
  else {
    setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;
    unsigned char const *k1 = buffer;
    unsigned char const *k2 = graph.buffer;
    for(int i=0;i!=(NN*M);++i,++k1,++k2) {
      if(*k1 != *k2) { 	return false; }
    }
  }
  return true;
}

// ----------------------------------
// METHODS FOR INTERFACING WITH NAUTY
// ----------------------------------

bool compare_graph_keys(unsigned char const *_k1, unsigned char const *_k2) {
  setword *k1 = (setword*) _k1;
  setword *k2 = (setword*) _k2;
  
  setword N1 = k1[0];
  setword N2 = k2[0];
  setword REAL_N1 = k1[1];
  setword REAL_N2 = k2[1];

  if(N1 != N2 || REAL_N1 != REAL_N2) { return false; }
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

// returns the sizeof the graph key in bytes
size_t sizeof_graph_key(unsigned char const *key) {
  setword *k1 = (setword*) key;  
  setword N = k1[0];
  setword M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  return ((N*M)+NAUTY_HEADER_SIZE) * sizeof(setword);
}

// generate a hash code from a graph key
unsigned int hash_graph_key(unsigned char const *key) {
  setword *p = (setword*) key;  
  setword N = p[0];
  setword M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  return hashlittle(key,sizeof(setword)*((N*M)+NAUTY_HEADER_SIZE),0);
}

size_t graph_size(unsigned char *key) {
  setword *p = (setword*) key;  
  setword N = p[0];
  setword REAL_N = p[1];
  return REAL_N;
}
