//
// This is the small graph generator, which automatically generates
// code for matching graphs of a particular size.

#include "nauty.h"
#include <iostream>
#include <vector>
#include <string>
#include <ext/hash_map>
#include <ext/hash_set>
#include "../graph/adjacency_list.hpp"
#include "../graph/algorithms.hpp"

using namespace std;
using namespace __gnu_cxx;

vector<vector<int> > combinator(int N, int min, int max) {
  bool finished;
  int counts[N];
  vector<vector<int> > vecs;
  // initialise counter array
  int j=min;
  for(int i=N-1;i>=0;--i) { counts[i]=j++; }
  // now, iterate edge array combinations
  do {
    // add this permuation!
    vector<int> v;
    for(int i=0;i!=N;++i) { v.push_back(counts[i]); }
    vecs.push_back(v);
    // now, increment to next
    finished = true;
    for(int i=0;i!=N;i++) {
      counts[i]++;
      if(counts[i] < (max-i)) {
	// go backwards and reset counters.
	for(int j=counts[i];i>=0;--i) {
	  counts[i]=j++;
	}
	finished = false;
	break;
      } 
    }
  } while(!finished);
  
  return vecs;
}


// this function recursively generates the list of all possible graphs
void generate_all_graphs(int v, int V, adjacency_list<> graph, list<adjacency_list<> > &graphs) {  
  if(v == (V-1)) {
    // this is the base case --- there are no more edges to add!
    graphs.push_back(graph);    
  } else {
    // add edges for vertex v
    for(int E=0;E!=V-v;++E) {      
      vector<vector<int> > combs = combinator(E,v+1,V);
      for(int i=0;i!=combs.size();++i) {
	vector<int> const &vec(combs[i]);
	// create graph for this combination
	adjacency_list<> g(graph);
	for(vector<int>::const_iterator j(vec.begin());j!=vec.end();++j) {
	  g.add_edge(v,*j); 
	}
        generate_all_graphs(v+1,V,g,graphs); 
      }
    }
  }
}

class degree_sequence_hash {
public:
  unsigned int operator()(vector<int> const &vec) const {
    unsigned int r = 0;
    for(vector<int>::const_iterator i(vec.begin());i!=vec.end();i++) {
      r ^= *i;
    }
    return r;
  }
};

vector<int> degree_sequence(adjacency_list<> const &graph) {
  vector<int> r(graph.num_vertices());
  for(int i=0;i!=r.size();++i) { r[i] = 0; }

  for(int i=0;i!=r.size();++i) { 
    r[graph.num_edges(i)]++;
  }

  return r;
}

bool two_connected(adjacency_list<> const &g) {
  for(int i=0;i!=g.num_vertices();++i) {
    if(g.num_edges(i) < 2) {
      return false;
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  bool simple=true;
  long size = strtol(argv[1],NULL,10);
  cout << "Generating code for matching simple graphs of size " << size << endl;

  try {
    
    // First, we generate the set of all unique graphs
    list<adjacency_list<> > graphs;
    generate_all_graphs(0,size, adjacency_list<>(size), graphs);  

    // Second, remove graphs with pendant edges
    for(list<adjacency_list<> >::iterator i(graphs.begin());i!=graphs.end();) {
      if(!two_connected(*i)) { graphs.erase(i++); }
      else { i++; }
    }

    // Third, remove isomorphic graphs (this could be made more efficient)
    unsigned int ngraphs_generated(graphs.size());
    for(list<adjacency_list<> >::iterator i(graphs.begin());i!=graphs.end();) {
      boolean unique(true);
      unsigned char *k1 = graph_key(*i);
      list<adjacency_list<> >::iterator j(i);
      for(++j;j!=graphs.end();++j) {
	unsigned char *k2 = graph_key(*j);
	if(compare_graph_keys(k1,k2)) {
	  // this graph is not unique
	  unique=false;
	  break;
	}
	delete [] k2;
      }
      delete [] k1;
      if(!unique) { graphs.erase(i++); }
      else { i++; }
    }

    cout << "Generated " << ngraphs_generated << " graphs, of which " << graphs.size() << " are unique." << endl;

    // Second, we bucket this list according to edge degree sequence
    hash_map<vector<int>, adjacency_list<>, degree_sequence_hash> buckets;
    hash_set<vector<int>, degree_sequence_hash> keys;
    for(list<adjacency_list<> >::iterator i(graphs.begin());i!=graphs.end();++i) {    
      keys.insert(degree_sequence(*i));
      buckets.insert(make_pair(degree_sequence(*i),*i));
    }
    cout << "Partitioned unique graphs into " << keys.size() << " distinct classes using degree sequences." << endl;   

    cout << "-------- CODE STARTS HERE -------- " << endl;
    
    cout << "// THIS CODE WAS AUTOMATICALLY GENERATED" << endl;
    cout << endl;
    cout << "template<class G, class P>" << endl;
    string nm[] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
    cout << "P const &evaluate_simple_" << nm[size] << "(G const &graph) {" << endl << endl;
    cout << "\t// first, compute degree sequence" << endl;
    cout << "\tlong degseq = 0;" << endl;
    cout << "\tfor(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) { " << endl;
    cout << "\t\tdeg[graph.num_edges(*i)]++;" << endl;
    cout << "\t}" << endl;
    cout << endl;
    cout << "\t// now, switch on it!" << endl;
    cout << "\t long 
    
    
    // now, print code for matching graphs!

  } catch(bad_alloc const &e) {
    cout << "error: insufficient memory!" << endl;
  } catch(exception const &e) {
    cout << "error: " << e.what() << endl;
  }
}
