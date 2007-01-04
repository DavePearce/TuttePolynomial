#include <string>
#include <ext/hash_map>
#include "nauty_graph.hpp"
#include "adjacency_list.hpp"
#include "algorithms.hpp"

using namespace std;
using namespace __gnu_cxx;

int main(int c, char *argv[]) {
  cout << "=== G1 ===" << endl;
  adjacency_list<> g1(4);
  //  g1.add_edge(1,2);
  //  g1.add_edge(0,2);
  g1.add_edge(0,2);
  print_graph(cout,g1);  
  cout << "=== REMOVING VERTEX 1 ===" << endl;
  g1.clear(1);
  print_graph(cout,g1);  
  
  nauty_graph ng1(g1);
  ng1.print_raw();
  ng1.makeCanonical();
  ng1.print_raw();

}
