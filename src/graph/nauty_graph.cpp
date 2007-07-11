#include <sstream>
#include "nauty_graph.hpp"

extern "C" {
  uint32_t hashlittle( const void *key, size_t length, uint32_t initval);
}

using namespace std;

nauty_graph::~nauty_graph() {
  delete [] canong_graph;
}

bool nauty_graph::operator==(nauty_graph const &key) const {
  setword *k1 = (setword*) canong_graph;
  setword *k2 = (setword*) key.canong_graph;
  
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

bool nauty_graph::operator!=(nauty_graph const &key) const {
  return !(*this == key);
}

// returns the sizeof the graph key in bytes
size_t nauty_graph::size() const {
  unsigned int N = canong_graph[0];
  unsigned int M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  return ((N*M)+NAUTY_HEADER_SIZE) * sizeof(setword);
}

// generate a hash code from a graph key
unsigned int nauty_graph::hashcode() const {
  unsigned int N = canong_graph[0];
  unsigned int M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  return hashlittle(canong_graph,sizeof(setword)*((N*M)+NAUTY_HEADER_SIZE),0);
}

string nauty_graph::str() const {
  setword *p = (setword*) canong_graph;  
  unsigned int N = p[0];
  unsigned int REAL_N = p[1];
  unsigned int M = ((N % WORDSIZE) > 0) ? (N / WORDSIZE)+1 : N / WORDSIZE;
  p=p+NAUTY_HEADER_SIZE;
  
  ostringstream out;
  out << "{ ";

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
	    out << i << "--" << tail << " "; 
	  }
	}
	mask = mask << 1;
      }
    }
  }

  out << " }";

  return out.str();
}

setword *nauty_graph::tmp_graph = NULL;
size_t nauty_graph::tmp_graph_size = 0;
setword *nauty_graph::workspace = NULL;
size_t nauty_graph::workspace_size = 0;

// -------------------------------
// Helper functions
// -------------------------------

bool nauty_graph::internal_add_edge(int from, int to, int M) {    
  unsigned int wb = (from / WORDSIZE);      
  unsigned int wo = from - (wb*WORDSIZE); 

  setword mask = (1U << (WORDSIZE-wo-1));
  if(tmp_graph[(to*M)+wb] & mask) { return false; }
  tmp_graph[(to*M)+wb] |= mask; 	  
  
  wb = (to / WORDSIZE);       
  wo = to - (wb*WORDSIZE);  
  mask = (1U << (WORDSIZE-wo-1));	  
  tmp_graph[(from*M)+wb] |= mask;

  return true;
}

#include "adjacency_list.hpp"

int main(int argc, char* argv[]) {
  adjacency_list<> g1(10);
  g1.add_edge(0,1);
  g1.add_edge(1,2);
  g1.add_edge(2,3);

  nauty_graph ng1(g1);

  cout << ng1.str() << endl;

  adjacency_list<> g2(10);
  g2.add_edge(9,6);
  g2.add_edge(6,4);
  g2.add_edge(4,1);

  nauty_graph ng2(g2);

  cout << ng2.str() << endl;

  exit(0);
}
