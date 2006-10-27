#include <iostream>
#include <fstream>
#include <stack>
#include <stdexcept>
#include <algorithm>

#include "config.h"
#include "graph/algorithms.hpp"

using namespace std;

// ---------------------------------------------------------------
// Global Variables
// ---------------------------------------------------------------

stack<Graph> worklist; // the worklist!

// ---------------------------------------------------------------
// Method Bodies
// ---------------------------------------------------------------

/* deleteContract is the core algorithm for the tutte computation
 * it reduces a graph to two smaller graphs using a delete operation
 * for one, and a contract operation for the other.
 *
 * The algorithm also uses a number of tricks to prune the computation
 * space.  These include: eliminating small graphs using optimised, 
 * hand-coded decision procedures; storing previously seen graphs
 * in a cache; and, dynamically monitoring the "treeness" of the graph.
 */

Poly deleteContract() { 
  int start_size = worklist.size(); // size of stack on entry
  
  // keep going until all branches from entry point are explored
  Poly result;

  while(!worklist.empty() && worklist.size() >= start_size) { 
    Graph &g = worklist.top();  // take reference to avoid copying!

    cout << "PROCESSING (#" << worklist.size() << "):" << endl;
    print_graph(cout,worklist.top());
    
    // if the graph is a tree, then we're done.
    if(g.is_tree()) {      
      worklist.pop();
      cout << "=== END BRANCH ===" << endl;
      // MISSING STUFF HERE?
      result.mulByX(g.num_edges());
    } else if (g.is_loop()) {      
      worklist.pop();
      // MISSING STUFF HERE?
      result.mulByY(1);
    } else {

      // at this point, there are several things we can do:
      // 
      // 1) eliminate small graphs using Gary's hard-coded
      //    algorithms.
      //
      // 2) lookup this graph in the cache to see if we've
      //    solved it before.
      //
      // At this stage, I'm not going to do either for 
      // simplicity ...
      
      // now, select the edge to remove
      pair<int,int> e = g.select_nontree_edge();
      cout << "SELECTED: " << e.first << "--" << e.second << " (contract => #" << worklist.size() << ")" << endl;
      // copy the graph
      worklist.push(g);
      g.contract_edge(e.first,e.second);      
      // remove all loops and account for them      
      g.remove_loops(e.first);
      {
	Graph &g2 = worklist.top();
	g2.remove_edge(e.first,e.second);        
      }
      deleteContract(); // what to do with this?
    }    
  }  

  return result;
}

// the following is a really simple file parser

int parse_number(std::istream &input) {
  int r;
  input >> r;
  return r;
}

void parse_comma(std::istream &input) {
  char c;
  input >> c;
}

Graph read_graph(std::istream &input) {
  vector<pair<unsigned int, unsigned int> > edgelist;
  unsigned int V=0;
    
  bool firstTime=true;

  while(!input.eof()) {
    if(!firstTime) { parse_comma(input); }
    if(input.eof()) { break; }
    firstTime=false;
    // just keep on reading!
    unsigned int tail = parse_number(input);
    parse_comma(input);
    unsigned int head = parse_number(input);
    V = max(V,max(head,tail));
    edgelist.push_back(std::make_pair(tail,head));
  }  

  Graph r(V+1);

  for(vector<pair<unsigned int, unsigned int> >::iterator i(edgelist.begin());
      i!=edgelist.end();++i) {
    r.add_edge(i->first,i->second);
  }

  return r;
}

// ---------------------------------------------------------------
// Main Method
// ---------------------------------------------------------------

int main(int argc, char *argv[]) {

  Graph start_graph(0);
  try {
    ifstream input(argv[1]);
    start_graph = read_graph(input);
  
    cout << "VERTICES = " << start_graph.num_vertices() << ", EDGES = " << start_graph.num_edges() << endl << endl;
    
    worklist.push(start_graph);
    Poly tuttePolynomial = deleteContract();
        
    print_graph(cout,start_graph);

    // printPoly(tuttePolynomial);
  } catch(exception const &e) {
    cout << "error: " << e.what() << endl;
  }
}






                                            
