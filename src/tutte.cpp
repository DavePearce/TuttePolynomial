#include <iostream>
#include <fstream>
#include <stack>
#include <stdexcept>
#include <algorithm>
#include <csignal>
#include <ext/hash_map>

#include "config.h"
#include "graph/algorithms.hpp"

using namespace __gnu_cxx; // needed for hash map
using namespace std;

// ---------------------------------------------------------------
// Global Variables
// ---------------------------------------------------------------

unsigned long num_steps = 0;
unsigned long old_num_steps = 0;

// ---------------------------------------------------------------
// Method Bodies
// ---------------------------------------------------------------

hash_map<nauty_graph,Poly,hash_nauty_graph> polystore; // THE hash map
unsigned int store_hits = 0;
unsigned int store_misses = 0;

/**
 * lookup is another important function.  It's job is to 
 * see if we have a stored solution for a particular graph.  If so, 
 * it returns the polynomial.  Otherwise, it returns NULL;
 */

Poly *lookup(Graph const &g) {

  // The following conversion is not cheap.  It would help to
  // eliminate it whenever possible.  One approach might be, for
  // example, to arrange the graphs such that we can tell no match
  // exists simply by looking at the number of vertices and edges.
  // This could include min, max edge degree?
  nauty_graph ng(g); 

  // Ok, now we have the nauty graph we can generate the unique
  // canonical labelling to check whether it's really a match
  hash_map<nauty_graph,Poly,hash_nauty_graph>::iterator i = polystore.find(ng);
  if(i != polystore.end()) {
    store_hits++;
    return &(i->second);
  } else {
    store_misses++;
    return NULL;
  }
}

/**
 * store is another important function.  It's job is to 
 * store a particular solution for a graph in the hash map.
 */

void store(Graph const &g, Poly const &p) {
  nauty_graph ng(g);
  polystore.insert(make_pair(ng,p));
}

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

  num_steps++;
  //   print_graph(cout,g);
  
  // if the graph is a "loop tree", then we're done.
  if(g.is_looptree()) {
    //    cout << "POLY: "  << Poly(g.num_edges()-g.num_loops(),g.num_loops()).str() << endl;
    //    cout << "=== END BRANCH ===" << endl;
    return Poly(g.num_edges()-g.num_loops(),g.num_loops());
  } else {
    term ys(0,g.num_loops());

    // First, remove any loops

    while(g.num_loops() > 0) {
      int l = g.select_loop_edge();
      g.remove_edge(l,l);
    }

    // Second, check if we've seen this graph before
    Poly *p;
    if((p=lookup(g)) != NULL) { return (*p) * ys; }

    // Third, perform delete contract 
    pair<int,int> e = g.select_nontree_edge();

    Graph g1(g);  
    g1.remove_edge(e.first,e.second);        
    Graph g2(g1); 
    g2.contract_edge(e.first,e.second); 

    // Fourth, recursively compute the polynomial
    Poly r = deleteContract(g1) + deleteContract(g2); // perform the recursion

    // Finally, save computed polynomial 
    store(g,r);

    return r * ys;
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
  unsigned int V = 0, pos = 0;
    
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
// Signal Handlers
// ---------------------------------------------------------------

static int status_interval = 5; // in seconds

void timer_handler(int signum) {
  double rate = (num_steps - old_num_steps);
  rate /= status_interval;
  cout << "Complete " << num_steps << " graphs at rate of " << ((int) rate) << "/s" << endl;
  old_num_steps = num_steps;
  alarm(status_interval);
}

// ---------------------------------------------------------------
// Main Method
// ---------------------------------------------------------------

int main(int argc, char *argv[]) {

  // first up, register some signals to help make the environment sane
  struct sigaction sa;
  memset(&sa,0,sizeof(sa));
  sa.sa_handler = &timer_handler;
  if(sigaction(SIGALRM,&sa,NULL)) { perror("sigvtalarm"); }
  alarm(status_interval); // trigger alarm in status_interval seconds

  Graph start_graph(0);
  try {
    ifstream input(argv[1]);
    start_graph = read_graph(input);
  
    cout << "VERTICES = " << start_graph.num_vertices() << ", EDGES = " << start_graph.num_edges() << endl << endl;

    print_graph(cout,start_graph);    

    Poly tuttePoly = deleteContract(start_graph);        

    cout << "Tutte Polynomial is " << tuttePoly.str() << endl;

    cout << "==================" << endl;
    cout << "Total Steps: " << num_steps << endl;
    cout << "Hash Map Hits: " << store_hits << endl;
    cout << "Hash Map Misses: " << store_misses << endl;
    cout << "Hash Map Entries: " << polystore.size() << endl;
    // printPoly(tuttePolynomial);
  } catch(exception const &e) {
    cout << "error: " << e.what() << endl;
  }
}






                                            
