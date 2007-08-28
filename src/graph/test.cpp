#include <string>
#include <ext/hash_map>
#include "adjacency_list.hpp"
#include "spanning_graph.hpp"
#include "algorithms.hpp"

using namespace std;
using namespace __gnu_cxx;

typedef spanning_graph<adjacency_list<> > graph_t;

int main(int c, char *argv[]) {
  cout << "=== SOURCE GRAPH ===" << endl;
  graph_t g1(2);
  g1.add_edge(0,1);
  //  g1.add_edge(0,3);
  //  g1.add_edge(1,2);
  //  g1.add_edge(1,3);

  //  g1.add_edge(1,2);
  //  g1.add_edge(2,3);
  //  g1.add_edge(4,5);
  //  g1.add_edge(5,3);

  cout << graph_str(g1) << endl;  
  cout << "IS BICONNECTED: " << g1.is_biconnected() << endl;
  cout << "BICONNECTS:" <<  endl;
  vector<graph_t> biconnects;

  g1.extract_biconnected_components(biconnects);

  for(unsigned int i=0;i!=biconnects.size();++i) {
    cout << graph_str(biconnects[i]) << endl;
  }

  cout << "REMAINDER: " << graph_str(g1) << endl;
  exit(0);
}
