//
// This is the small graph generator, which automatically generates
// code for matching graphs of a particular size.

#include <iostream>
#include <vector>
#include "../graph/adjacency_list.hpp"

using namespace std;

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
void generate_all_graphs(int v, int V, adjacency_list<> graph, vector<adjacency_list<> > &graphs) {  
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

int main(int argc, char *argv[]) {
  bool simple=true;
  long size = strtol(argv[1],NULL,10);
  cout << "Generating code for matching simple graphs of size " << size << endl;

  try {
    
    vector<adjacency_list<> > graphs;
    
    generate_all_graphs(0,size, adjacency_list<>(size), graphs);  
    
    for(int i=0;i!=graphs.size();++i) {
      cout << "GRAPH #" << i << " : { ";
      adjacency_list<> g(graphs[i]);
      for(adjacency_list<>::vertex_iterator i(g.begin_verts());i!=g.end_verts();++i) {
	for(adjacency_list<>::edge_iterator j(g.begin_edges(*i));j!=g.end_edges(*i);++j) {
	  if(*i <= *j) {
	    cout << *i << "--" << *j << " ";
	  } 
	}
      }
      cout << " } " << endl;
    }
  } catch(bad_alloc const &e) {
    cout << "error: insufficient memory!" << endl;
  } catch(exception const &e) {
    cout << "error: " << e.what() << endl;
  }
}
