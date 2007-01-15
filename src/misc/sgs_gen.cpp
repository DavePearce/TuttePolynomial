// This is the Small Graph Solution Generator, which automatically generates
// code for matching graphs of a particular size.

#include "nauty.h"
#include <iostream>
#include <vector>
#include <string>
#include <ext/hash_map>
#include <ext/hash_set>
#include <cmath>
#include "../graph/adjacency_list.hpp"
#include "../graph/spanning_graph.hpp"
#include "../graph/algorithms.hpp"
#include "../poly/simple_poly.hpp"

using namespace std;
using namespace __gnu_cxx;

typedef adjacency_list<> graph_t;
typedef spanning_graph<adjacency_list<> > sgraph_t;
typedef simple_poly poly_t;

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
void generate_all_graphs(int v, int V, graph_t graph, list<graph_t> &graphs) {  
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
	graph_t g(graph);
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

vector<int> degree_sequence(graph_t const &graph) {
  vector<int> r(graph.num_vertices());
  for(int i=0;i!=r.size();++i) { r[i] = 0; }

  for(int i=0;i!=r.size();++i) { 
    r[graph.num_edges(i)]++;
  }

  return r;
}

unsigned long degree_sequence_key(graph_t const &graph, int shift) {
  unsigned long key = 0;

  for(int i=0;i!=graph.num_vertices();++i) { 
    key += 1U << (graph.num_edges(i)*shift);
  }

  return key;
}

bool two_connected(graph_t const &g) {
  for(int i=0;i!=g.num_vertices();++i) {
    if(g.num_edges(i) < 2) {
      return false;
    }
  }
  return true;
}


// a simple tutte polynomial solver which doesn't do anything fancy
poly_t delete_contract(sgraph_t &g) { 
  if(g.is_looptree()) {
    return poly_t(g.num_edges()-g.num_loops(),g.num_loops());
  } else {
    // Perform delete contract 
    pair<int,int> e = g.select_nontree_edge();

    sgraph_t g1(g);  
    g1.remove_edge(e.first,e.second);        
    sgraph_t g2(g1); 
    g2.contract_edge(e.first,e.second); 

    // Fourth, recursively compute the polynomial
    return delete_contract(g1) + delete_contract(g2); // perform the recursion
  }    
}

void print_graph_poly(graph_t const &graph) {
  // this function has got to compute the solution for the given small
  // graph and then print it as as a series of polynomial constructs.
  
  // first, construct solution
  sgraph_t g(graph);
  poly_t r = delete_contract(g);
  
  // second, print it!
  int count=0;
  for(poly_t::const_iterator i(r.begin());i!=r.end();++i,++count) {
    if(count == 6) { cout << endl << "\t\t\t\t"; count = 0; }
    if(i!=r.begin()) { cout << " + "; }
    cout << "P(" << i->second << "," << i->first.xpower << "," << i->first.ypower << ")";
  }
}

int main(int argc, char *argv[]) {
  bool simple=true;
  long size = strtol(argv[1],NULL,10);
  cerr << "Generating code for matching simple graphs of size " << size << endl;

  try {
    
    // First, we generate the set of all unique graphs
    list<graph_t> graphs;
    generate_all_graphs(0,size, graph_t(size), graphs);  

    // Second, remove graphs with pendant edges
    for(list<graph_t>::iterator i(graphs.begin());i!=graphs.end();) {
      if(!two_connected(*i)) { graphs.erase(i++); }
      else { i++; }
    }

    // Third, remove isomorphic graphs (this could be made more efficient)
    unsigned int ngraphs_generated(graphs.size());
    for(list<graph_t>::iterator i(graphs.begin());i!=graphs.end();) {
      boolean unique(true);
      unsigned char *k1 = graph_key(*i);
      list<graph_t>::iterator j(i);
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

    cerr << "Generated " << ngraphs_generated << " graphs, of which " << graphs.size() << " are unique." << endl;

    // Second, we bucket this list according to edge degree sequence
    hash_map<vector<int>, graph_t, degree_sequence_hash> buckets;
    hash_set<vector<int>, degree_sequence_hash> keys;
    for(list<graph_t>::iterator i(graphs.begin());i!=graphs.end();++i) {    
      keys.insert(degree_sequence(*i));
      buckets.insert(make_pair(degree_sequence(*i),*i));
    }
    cerr << "Partitioned unique graphs into " << keys.size() << " distinct classes using degree sequences." << endl;   
    time_t ct = time(NULL);
    cout << "// THIS CODE WAS AUTOMATICALLY GENERATED ON " << ctime(&ct) << endl;
    cout << endl;
    string cnm[] = {"ZERO","ONE","TWO","THREE","FOUR","FIVE","SIX","SEVEN","EIGHT","NINE"};
    cout << "#ifndef EVALUATE_SIMPLE_" << cnm[size] << "_HPP" << endl;
    cout << "#define EVALUATE_SIMPLE_" << cnm[size] << "_HPP" << endl;
    cout << endl << "#include <stdexcept>" << endl;
    cout << endl;
    cout << "template<class G, class P>" << endl;
    string nm[] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
    cout << "P const &evaluate_simple_" << nm[size] << "(G const &graph) {" << endl << endl;
    cout << "\t// first, define polynomial solutions" << endl;
    for(hash_set<vector<int>,  degree_sequence_hash>::iterator i(keys.begin());i!=keys.end();++i) {
      graph_t const &graph = buckets.find(*i)->second;
      cout << "\tstatic P poly";
      for(vector<int>::const_iterator j(i->begin());j!=i->end();++j) {
	cout << "_" << *j;
      }
      cout << " = "; 
      print_graph_poly(graph);
      cout << ";" << endl;
    }
    cout << endl << "\t// second, compute degree sequence" << endl;
    cout << "\tunsigned long degseq = 0;" << endl;
    unsigned int shift = (unsigned int) ceil(log2((double) size));
    cout << "\tfor(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) { " << endl;
    cout << "\t\tdegseq = degseq + (1U << (graph.num_edges(*i) * " << shift << "));" << endl;
    cout << "\t}" << endl;
    cout << endl;
    cout << "\t// third, switch on it!" << endl;
    cout << "\tswitch(degseq) {" << endl;
    
    // now, go through the keys and put in the answer for each
    for(hash_set<vector<int>,  degree_sequence_hash>::iterator i(keys.begin());i!=keys.end();++i) {
      graph_t const &graph = buckets.find(*i)->second;
      unsigned long k = degree_sequence_key(graph,shift);
      vector<int> ds = degree_sequence(graph);
      cout << "\t\tcase " << k << "L:" << endl;
      cout << "\t\t // DEGSEQ: ";
      // print degree sequence
      int deg=0;
      for(vector<int>::iterator j(ds.begin());j!=ds.end();++j, ++deg) {
	if(j!=ds.begin()) { cout << ", "; }
	cout << deg << "(" << *j << ")";
      }
      // print graph
      cout << endl << "\t\t // GRAPH : ";
      bool first_time(true);
      for(unsigned int j=0;j!=graph.num_vertices();++j) {
	for(graph_t::edge_iterator k(graph.begin_edges(j));
	    k!=graph.end_edges(j);++k) {
	  if(j <= *k) {
	    if(!first_time) { cout << ", "; }
	    first_time=false;
	    cout << j << "--" << *k;
	  }
	}
      }
      cout << endl << "\t\t return poly";
      for(vector<int>::iterator j(ds.begin());j!=ds.end();++j) {
	cout << "_" << *j;
      }
      cout << ";" << endl;
    }
    cout << "\t\tdefault:" << endl;
    cout << "\t\t throw std::runtime_error(\"unreachable code reached!\");" << endl;
    cout << "\t}" << endl;
    cout << "\t// SHOULD BE UNREACHABLE!" << endl;
    cout << "}" << endl;
    cout << endl << "#endif" << endl;
    // now, print code for matching graphs!

  } catch(bad_alloc const &e) {
    cout << "error: insufficient memory!" << endl;
  } catch(exception const &e) {
    cout << "error: " << e.what() << endl;
  }
}
