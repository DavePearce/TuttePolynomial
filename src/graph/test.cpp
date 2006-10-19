#include "adjacency_list.hpp"
#include "algorithms.hpp"
#include "spanning_graph.hpp"

int main(int c, char *argv[]) {
  spanning_graph<adjacency_list> g(10);
  g.remove(7);
  g.add_edge(1,2);
  g.add_edge(4,5);
  print_graph(cout,g);
}
