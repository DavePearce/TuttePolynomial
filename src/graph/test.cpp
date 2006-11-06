#include "adjacency_list.hpp"
#include "nauty_graph.hpp"
#include "algorithms.hpp"

int main(int c, char *argv[]) {
  cout << "=== G1 ===" << endl;
  adjacency_list g1(10);
  g1.add_edge(1,2);
  g1.add_edge(2,3);
  g1.add_edge(3,1);
  print_graph(cout,g1);
  
  nauty_graph ng1(g1);
  ng1.print();
  ng1.makeCanonical();
  ng1.print();

  cout << "=== G2 ===" << endl;

  adjacency_list g2(10);
  g2.add_edge(4,5);
  g2.add_edge(5,6);
  g2.add_edge(6,4);
  print_graph(cout,g2);
  
  nauty_graph ng2(g2);
  ng2.print();
  ng2.makeCanonical();
  ng2.print();
}
