#include <string>
#include <ext/hash_map>
#include "adjacency_list.hpp"
#include "spanning_graph.hpp"
#include "algorithms.hpp"

using namespace std;
using namespace __gnu_cxx;

int main(int c, char *argv[]) {
  cout << "=== SOURCE GRAPH ===" << endl;
  spanning_graph<adjacency_list<> > g1(6);
  g1.add_edge(0,1);
  g1.add_edge(1,2);
  g1.add_edge(2,0);
  g1.add_edge(2,3);
  g1.add_edge(3,4);
  g1.add_edge(4,5);
  g1.add_edge(5,3);
  cout << graph_str(g1) << endl;  
  exit(0);
}
