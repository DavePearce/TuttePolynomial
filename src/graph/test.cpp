#include "adjacency_list.hpp"
#include "nauty_graph.hpp"
#include "algorithms.hpp"

int main(int c, char *argv[]) {
  adjacency_list g(10);
  g.add_edge(1,2);
  g.add_edge(4,5);
  print_graph(cout,g);
  
  nauty_graph ng(g);
  ng.print();
  ng.makeCanonical();
  ng.print();
}
