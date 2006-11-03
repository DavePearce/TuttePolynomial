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

Poly deleteContract(Graph &g) { 
  
  cout << "PROCESSING:" << endl;
  print_graph(cout,g);
  
  // if the graph is a "loop tree", then we're done.
  if(g.is_looptree()) {
    cout << "POLY: "  << Poly(g.num_edges()-g.num_loops(),g.num_loops()).str() << endl;
    cout << "=== END BRANCH ===" << endl;
    return Poly(g.num_edges()-g.num_loops(),g.num_loops());
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
    cout << "SELECTED: " << e.first << "--" << e.second << endl;
    g.remove_edge(e.first,e.second);        
    Graph cg = g; // copy graph
    cg.contract_edge(e.first,e.second); // contract edge
    return deleteContract(g) + deleteContract(cg); // perform the recursion
  }    
}

// the following is a really simple file parser

int parse_number(unsigned int &pos, string const &str) {
  int s = pos;
  while(pos < str.length() && isdigit(str[pos])) {
    pos = pos + 1;
  }
  stringstream ss(str.substr(s,pos));
  int r;
  ss >> r;
  return r;
}

void match(char c, unsigned int &pos, string const &str) {
  if(pos >= str.length() || str[pos] != c) { throw runtime_error(string("syntax error -- expected '") + c + "', got '" + str[pos] + "'"); }
  ++pos;
}

Graph read_graph(std::istream &input) {
  vector<pair<unsigned int, unsigned int> > edgelist;
  unsigned int V=0, pos = 0;
    
  bool firstTime=true;
  string in;
  input >> in;

  while(pos < in.length()) {
    if(!firstTime) { match(',',pos,in); }
    firstTime=false;
    // just keep on reading!
    unsigned int tail = parse_number(pos,in);
    match('-',pos,in); match('-',pos,in);
    unsigned int head = parse_number(pos,in);
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

    print_graph(cout,start_graph);    

    Poly tuttePoly = deleteContract(start_graph);        

    cout << "Tutte Polynomial is " << tuttePoly.str() << endl;

    // printPoly(tuttePolynomial);
  } catch(exception const &e) {
    cout << "error: " << e.what() << endl;
  }
}






                                            
