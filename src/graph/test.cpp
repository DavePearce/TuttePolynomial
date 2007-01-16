#include "nauty.h"
#include <string>
#include <ext/hash_map>
#include "adjacency_list.hpp"
#include "algorithms.hpp"

using namespace std;
using namespace __gnu_cxx;

int main(int c, char *argv[]) {
  cout << "=== SOURCE GRAPH ===" << endl;
  adjacency_list<> g1(4);
  g1.add_edge(1,2);
  g1.add_edge(1,2);
  g1.add_edge(0,2);
  g1.add_edge(0,1);
  g1.add_edge(0,3);
  print_graph(cout,g1);  
  unsigned char *key = graph_key(g1);
  adjacency_list<> g2 = graph_from_key<adjacency_list<> >(key);
  cout << "=== CONVERTED GRAPH ===" << endl;
  print_graph(cout,g2);    
}
