// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include <stdexcept>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <csignal>
#include <getopt.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <ext/hash_map>

#include "graph/adjacency_list.hpp"
#include "graph/spanning_graph.hpp"
#include "poly/simple_poly.hpp"
#include "poly/factor_poly.hpp"
#include "graph/algorithms.hpp"
#include "cache/simple_cache.hpp"
#include "misc/biguint.hpp"
#include "misc/safe_arithmetic.hpp"

#include "reductions.hpp"

#include <set>

using namespace std;

// ---------------------------------------------------------------
// User-Defined Types
// ---------------------------------------------------------------

class my_timer {
private:
  struct timeval _start;
  bool gtod;
public:
  my_timer(bool _gtod = true) : gtod(_gtod) {
    if(gtod) {
      gettimeofday(&_start,NULL);
    } else {
      struct rusage ru;
      getrusage(RUSAGE_SELF,&ru);
      _start = ru.ru_utime; // measure time spent in user space
    }
  }

  double elapsed(void) {
    struct timeval tmp;

    if(gtod) {
      gettimeofday(&tmp,NULL);
    } else {
      struct rusage ru;
      getrusage(RUSAGE_SELF,&ru);
      tmp = ru.ru_utime; 
    }

    double end = tmp.tv_sec + (tmp.tv_usec / 1000000.0);
    double start = _start.tv_sec + (_start.tv_usec / 1000000.0);    
    return end - start;
  }  
};

// ---------------------------------------------------------------
// Global Variables
// ---------------------------------------------------------------

typedef enum { RANDOM, MAXIMISE_DEGREE, MINIMISE_DEGREE, MAXIMISE_MDEGREE, MINIMISE_MDEGREE, MINIMISE_SDEGREE, VERTEX_ORDER } edgesel_t;
typedef enum { V_RANDOM, V_MINIMISE_UNDERLYING_DEGREE,  V_MAXIMISE_UNDERLYING_DEGREE, V_MINIMISE_DEGREE,  V_MAXIMISE_DEGREE, V_NONE } vorder_t;

unsigned int resize_stats = 0;
unsigned long num_steps = 0;
unsigned long num_bicomps = 0;
unsigned long num_cycles = 0;
unsigned long num_disbicomps = 0;
unsigned long num_trees = 0;
unsigned long old_num_steps = 0;
static int current_timeout = 15768000; // one years worth of timeout
static int timeout = 15768000; // one years worth of timeout
static unsigned int small_graph_threshold = 5;
static edgesel_t edge_selection_heuristic = VERTEX_ORDER;
static simple_cache cache(1024*1024,100);
static bool status_flag=false;
static bool verbose=true;
static bool reduce_multicycles=true;
static bool reduce_multiedges=true;
static bool reduce_lines=false;
static bool xml_flag=false;
static unsigned int tree_id = 2;
static bool write_tree=false;
static bool write_full_tree=false;

void print_status();

// ---------------------------------------------------------------
// Method Bodies
// ---------------------------------------------------------------

/* XML output methods.  Currently needed to interface with the visualisation
 * tool being developed by Bennett Thompson.
 */

void write_xml_start() {
  cout << "<object-stream>" << endl;
}

void write_xml_end() {
  cout << "</object-stream>" << endl;
}

template<class G>
void write_xml_graph(G const &graph, ostream &out) {
  out << "<graph>" << endl << "<struct>" << endl;
  for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    for(typename G::edge_iterator j(graph.begin_edges(*i));j!=graph.end_edges(*i);++j) {
      if(*i <= j->first) {	
	out << "<edge>" << endl;
	out << "<sV>" << *i << "</sV>" << endl;
	out << "<fV>" << j->first << "</fV>" << endl;
	out << "<nE>" << j->second << "</nE>" << endl;
	out << "</edge>" << endl;
      } 
    }
  }
  out << "</struct></graph>" << endl;
}

template<class G>
void write_xml_match(unsigned int my_id, unsigned int match_id, G const &graph, ostream &out) {
  out << "<graphnode>" << endl;
  out << "<id>" << my_id << "</id>" << endl;
  out << "<vertices>" << graph.num_vertices() << "</vertices>" << endl;
  out << "<edges>" << graph.num_edges() << "</edges>" << endl;
  out << "<match>" << match_id << "</match>" << endl;
  out << "</graphnode>" << endl;
}

template<class G>
void write_xml_nonleaf(unsigned int my_id, int left_id, int right_id, G const &graph, ostream &out) {
  out << "<graphnode>" << endl;
  out << "<id>" << my_id << "</id>" << endl;
  out << "<vertices>" << graph.num_vertices() << "</vertices>" << endl;
  out << "<edges>" << graph.num_edges() << "</edges>" << endl;
  out << "<left>" << left_id << "</left>" << endl;
  out << "<right>" << right_id << "</right>" << endl;
  write_xml_graph(graph,out);
  out << "</graphnode>" << endl;
}

template<class G>
void write_xml_leaf(unsigned int my_id, G const &graph, ostream &out) {
  out << "<graphnode>" << endl;
  out << "<id>" << my_id << "</id>" << endl;
  out << "<vertices>" << graph.num_vertices() << "</vertices>" << endl;
  out << "<edges>" << graph.num_edges() << "</edges>" << endl;
  write_xml_graph(graph,out);
  out << "</graphnode>" << endl;
}

/* Non-XML output methods
 */

template<class G>
void write_tree_match(unsigned int my_id, unsigned int match_id, G const &graph, ostream &out) {
  if(xml_flag) { write_xml_match(my_id,match_id,graph,out); }
  else {
    out << my_id << "=" << match_id << endl;
  }
}

template<class G>
void write_tree_leaf(unsigned int my_id, G const &graph, ostream &out) {
  if(xml_flag) { 
    write_xml_leaf(my_id,graph,out);
  } else {
    if(write_full_tree) { out << my_id << "=" << graph_str(graph) << endl;; }
  }
}

template<class G>
void write_tree_nonleaf(unsigned int my_id, int start_id, int count, G const &graph, ostream &out) {
  if(xml_flag) { 
    if(count < 2) {
      write_xml_nonleaf(my_id,start_id,-1,graph,out);
    } else {
      write_xml_nonleaf(my_id,start_id,start_id+1,graph,out);
    }
  } else {
    out << my_id << "=";
    for(int i=0;i!=count;++i) {
      if(i != 0) { out << "+"; }
      out << start_id+i; 
    }
    if(write_full_tree) { out <<  "=" << graph_str(graph); }
    out << endl;
  }
}

void write_tree_start(unsigned int tid) {
  if(xml_flag) { write_xml_start(); }  
}

void write_tree_end(unsigned int tid) {
  if(xml_flag) { write_xml_end(); }
  else {
    cout << "=== TREE " << tid << " END ===" << endl;
  }
}

/* This method determines which edge is chosen to delete contract upon.
 * It is key to how the algorithm operates!
 */

template<class G>
typename G::edge_t select_edge(G const &graph) {
  // assumes this graph is NOT a cycle and NOT a tree
  unsigned int best(0);
  unsigned int V(graph.num_vertices());
  unsigned int rcount(0);
  unsigned int rtarget(0);
  typename G::edge_t r(-1,-1,-1);
  
  if(edge_selection_heuristic == RANDOM) {
    unsigned int nedges = graph.num_edges();
    rtarget = (unsigned int) (((double) nedges*rand()) / (1.0+RAND_MAX));
  }

  for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    unsigned int head = *i;
    unsigned int headc(graph.num_underlying_edges(head));
    if(!reduce_lines || headc != 2) {      
      // if we're in lines mode, then we ignore "parts" of lines
      for(typename G::edge_iterator j(graph.begin_edges(*i));
	  j!=graph.end_edges(*i);++j) {	
	unsigned int tail = j->first;
	unsigned int tailc(graph.num_underlying_edges(tail));
	unsigned int count = j->second;
	
	if(head < tail || (reduce_lines && tailc == 2)) { // to avoid duplicates
	  unsigned int cost;
	  switch(edge_selection_heuristic) {
	  case MAXIMISE_DEGREE:
	    cost = headc + tailc;
	    break;
	  case MAXIMISE_MDEGREE:
	    cost = headc * tailc;
	    break;
	  case MINIMISE_DEGREE:
	    cost = 2*V - (headc + tailc);
	    break;
	  case MINIMISE_SDEGREE:
	    cost = V - std::min(headc,tailc);
	    break;
	  case MINIMISE_MDEGREE:
	    cost = V*V - (headc * tailc);
	    break;
	  case VERTEX_ORDER:	    
	    return typename G::edge_t(head,tail,reduce_multiedges ? count : 1);
	    break;
	  case RANDOM:
	    if(rcount == rtarget) {
	      return typename G::edge_t(head,tail,reduce_multiedges ? count : 1);
	    }
	    rcount += count;	    
	  }
	  if(cost > best) {	    
	    r = typename G::edge_t(head,tail,reduce_multiedges ? count : 1);
	    best = cost;
	  }     
	}
      }
    }
  }
  
  if(best == 0) { throw std::runtime_error("internal failure"); }

  return r;
} 

template<class G>
line_t select_line(G const &graph) {
  typename G::edge_t e = select_edge(graph);
  if(reduce_lines) { 
    return trace_line<G>(e.first,e.second,graph); 
  } else {
    return line_t(1,e);
  }
}

/* Given a line x_1--y_1(k_1), ..., x_n--y_n(k_n), this method
 * computes a very strange product for the line ...
 */
template<class G, class P>
P FP(std::vector<typename G::edge_t> const &line) {
  // this one is just a bit on the wierd side
  P xs(X(0));
  P acc(X(0));
  
  for(unsigned int k=0;k<line.size()-1;++k) {
    P tmp(X(1));
    if(line[k].third > 1) { tmp += Y(1,line[k].third-1); }
    if(line[k+1].third > 1) { xs *= Y(0,line[k+1].third-1); }
    acc *= tmp;
    xs += acc;
  }     

  return xs;
}

/* Given a line x_1--y_1(k_1), ..., x_n--y_n(k_n), this method
 * computes the Line Product:
 *
 *  (X^p + Y^1 + ... Y^{k_1-1}) * (X^2 + Y^1 + ... Y^{k_2-1}) ...
 */
template<class G, class P>
P LP(unsigned int p, std::vector<typename G::edge_t> const &line) {
  P r(Y(0));
  for(unsigned int k=0;k<line.size();++k) {
    P tmp = X(p);
    if(line[k].third > 1) { tmp += Y(1,line[k].third-1); }
    r *= tmp;
  }
  return r;
}

/* This is the core algorithm for the tutte computation
 * it reduces a graph to two smaller graphs using a delete operation
 * for one, and a contract operation for the other.
 *
 * The algorithm also uses a number of tricks to prune the computation
 * space.  These include: eliminating small graphs using optimised, 
 * hand-coded decision procedures; storing previously seen graphs
 * in a cache; and, dynamically monitoring the "treeness" of the graph.
 */

template<class G, class P>
P T(G &graph, unsigned int mid) { 
  if(current_timeout <= 0) { return P(X(0)); }
  if(status_flag) { print_status(); }
  num_steps++;

  // === 1. APPLY SIMPLIFICATIONS ===

  // P RF = reduce<G,P>(graph);
  P RF = Y(reduce_loops(graph));

  // === 2. CHECK IN CACHE ===

  unsigned char *key = NULL;
  if(graph.num_vertices() >= small_graph_threshold && !graph.is_multitree()) {      
    key = graph_key(graph); 
    unsigned int match_id;
    P r;
    if(cache.lookup(key,r,match_id)) { 
      if(write_tree) { write_tree_match(mid,match_id,graph,cout); }
      delete [] key; // free space used by key
      return r * RF;
    }
  }

  P poly;

  // === 3. CHECK FOR ARTICULATIONS, DISCONNECTS AND/OR TREES ===

  if(reduce_multicycles && graph.is_multicycle()) {
    num_cycles++;
    poly = reduce_cycle<G,P>(graph);
    if(write_tree) { write_tree_leaf(mid,graph,cout); }
  } else if(!graph.is_biconnected()) {
    vector<G> biconnects;
    G copyg(graph);
    graph.extract_biconnected_components(biconnects);
    poly = reduce_tree<G,P>(graph);
    if(graph.is_multitree()) { num_trees++; }
    if(biconnects.size() > 1) { num_disbicomps++; }
    // figure out how many tree ids I need
    unsigned int tid(tree_id);
    tree_id += biconnects.size();
    if(biconnects.size() > 0 && write_tree) { write_tree_nonleaf(mid,tid,tree_id-tid,copyg,cout); }
    else if(write_tree) { write_tree_leaf(mid,graph,cout); }
    // now, actually do the computation
    for(typename vector<G>::iterator i(biconnects.begin());i!=biconnects.end();++i){
      num_bicomps++;
      if(i->is_multicycle()) {
	// this is actually a cycle!
	num_cycles++;
	poly *= reduce_cycle<G,P>(*i);
	if(write_tree) { write_tree_leaf(tid++,*i,cout); }
      } else {
	poly *= T<G,P>(*i,tid++);      
      }
    }
  } else {

    // TREE OUTPUT STUFF
    unsigned int lid = tree_id;
    unsigned int rid = tree_id+1;
    tree_id = tree_id + 2; // allocate id's now so I know them!
    if(write_tree) { write_tree_nonleaf(mid,lid,2,graph,cout); }
    
    // === 4. PERFORM DELETE / CONTRACT ===
    
    G g2(graph); 
    line_t line = select_line(graph);

    // now, delete/contract on the line's endpoints
    graph.remove_line(line);
    g2.contract_line(line);
    // recursively compute the polynomial   
    poly = (T<G,P>(graph, lid) * FP<G,P>(line)) + (T<G,P>(g2, rid) * LP<G,P>(0,line));
  }

  // Finally, save computed polynomial
  if(key != NULL) {
    // there is, strictly speaking, a bug with using mid
    // here, since the graph being stored is not the same as that
    // at the beginning.
    cache.store(key,poly,mid);
    delete [] key;  // free space used by key
  }    

  return poly * RF;
}

// ---------------------------------------------------------------
// Input File Parser
// ---------------------------------------------------------------

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

template<class G>
G read_graph(std::istream &input) {
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

  if(V == 0) { return G(0); }

  G r(V+1);

  for(vector<pair<unsigned int, unsigned int> >::iterator i(edgelist.begin());
      i!=edgelist.end();++i) {
    r.add_edge(i->first,i->second);
  }

  return r;
}

template<class G, class OP>
class vo_underlying {
private:
  G const &graph;
  OP op;
public:
  vo_underlying(G const &g) : graph(g) {}

  bool operator()(unsigned int v1, unsigned int v2) {
    return op(graph.num_underlying_edges(v1),graph.num_underlying_edges(v2));
  }
};

template<class G, class OP>
class vo_multi {
private:
  G const &graph;
  OP op;
public:
  vo_multi(G const &g) : graph(g) {}

  bool operator()(unsigned int v1, unsigned int v2) {
    return op(graph.num_edges(v1),graph.num_edges(v2));
  }
};

template<class G>
G permute_graph(G const &graph, vorder_t heuristic) {
  vector<unsigned int> order;
  for(unsigned int i=0;i!=graph.num_vertices();++i) {
    order.push_back(i);
  }
  // obtain the new ordering
  switch(heuristic) {
  case V_RANDOM:
    random_shuffle(order.begin(),order.end());
    break;
  case V_MINIMISE_UNDERLYING_DEGREE:
    sort(order.begin(),order.end(),vo_underlying<G,less<unsigned int> >(graph));
    break;
  case V_MAXIMISE_UNDERLYING_DEGREE:
    sort(order.begin(),order.end(),vo_underlying<G,greater<unsigned int> >(graph));
    break;
  case V_MINIMISE_DEGREE:
    sort(order.begin(),order.end(),vo_multi<G,less<unsigned int> >(graph));
    break;
  case V_MAXIMISE_DEGREE:
    sort(order.begin(),order.end(),vo_multi<G,greater<unsigned int> >(graph));
    break;
  default:
    // do nothing
    break;
  }
  // transpose ordering
  vector<unsigned int> iorder(order.size());
  for(unsigned int i=0;i!=graph.num_vertices();++i) {
    iorder[order[i]] = i;
  }
  
  // finally, create new permuted graph
  G r(graph.num_vertices());
  
  for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    for(typename G::edge_iterator j(graph.begin_edges(*i));
	j!=graph.end_edges(*i);++j) {	      
      unsigned int head(*i);
      unsigned int tail(j->first);
      unsigned int count(j->second);
      if(head <= tail) {
	r.add_edge(iorder[head],iorder[tail],count);
      }
    }
  }
  return r;
}

unsigned int parse_amount(char *str) {
  char *endp=NULL;
  long r = strtol(str,&endp,10);
  if(*endp != '\0') {
    if(strcmp(endp,"M") == 0) {
      r = r * 1024 * 1024;
    } else if(strcmp(endp,"K") == 0) {
      r = r * 1024;
    } else if(strcmp(endp,"G") == 0) {
      r = r * 1024 * 1024 * 1024;
    }
  }
  return r;
}

// ---------------------------------------------------------------
// Statistics Printing Methods
// ---------------------------------------------------------------

void write_bucket_lengths(fstream &out) {
  out << "############################" << endl;
  out << "# CACHE BUCKET LENGTH DATA #" << endl;
  out << "############################" << endl;
  out << "# Length\tCount" << endl;
  vector<int> counts;
  // first, count the lengths
  for(int i=0;i!=cache.num_buckets();++i) {
    int len = cache.bucket_length(i);
    if(counts.size() < (len+1)) {
      // need to increase size of count array
      counts.resize(len+1,0);
    }
    counts[len]++;
  }

  // second, print the data!
  for(unsigned int i=0;i!=counts.size();++i) {
    double percentage(((double)counts[i]*100) / cache.num_buckets());
    out << i << "\t" << counts[i] << "\t" << setprecision(2) << percentage << endl;
  }
}

void write_graph_sizes(fstream &out) {
  out << endl << endl;
  out << "#########################" << endl;
  out << "# CACHE GRAPH SIZE DATA #" << endl;
  out << "#########################" << endl;
  out << "# Size\t#Graphs (%)\t#MultiGraphs (%)" << endl;
  vector<int> counts;
  vector<int> mcounts;
  int nmgraphs=0;
  int ngraphs=0;
  // first, count the lengths
  for(simple_cache::iterator i(cache.begin());i!=cache.end();++i) {
    adjacency_list<> g(graph_from_key<adjacency_list<> >(i.key()));
    if(counts.size() < (g.num_vertices()+1)) {
      // need to increase size of count array
      counts.resize(g.num_vertices()+1,0);
    }
    ++ngraphs;
    counts[g.num_vertices()]++;
    if(g.is_multi_graph()) {
      nmgraphs++;
      if(mcounts.size() < (g.num_vertices()+1)) {
	// need to increase size of count array
	mcounts.resize(g.num_vertices()+1,0);
      }
      mcounts[g.num_vertices()]++;      
    }
  }

  // second, print the data!
  for(unsigned int i=0;i!=counts.size();++i) {
    double percentage(((double)counts[i]*100) / ngraphs);
    out << i << "\t" << counts[i] << "\t" << setprecision(2) << percentage;
    percentage = (((double)mcounts[i]*100) / nmgraphs);
    out << "\t" << mcounts[i] << "\t" << setprecision(2) << percentage << endl;
  }
}

void write_hit_counts(fstream &out) {
  std::vector<unsigned int> vcount;
  out << endl << endl;
  out << "##############################" << endl;
  out << "# CACHE GRAPH HIT COUNT DATA #" << endl;
  out << "##############################" << endl;
  out << "# Hit Count\tV" << endl;
  int nmgraphs=0;
  int ngraphs=0;

  for(simple_cache::iterator i(cache.begin());i!=cache.end();++i) {
    adjacency_list<> g(graph_from_key<adjacency_list<> >(i.key()));
    if(vcount.size() < g.num_vertices()) {
      vcount.resize(g.num_vertices(),0);
    }
    vcount[g.num_vertices()] += i.hit_count();
  }
  
  for(unsigned int i=0;i!=vcount.size();++i) {
    out << i << "\t" << vcount[i] << endl;
  }
}

// ---------------------------------------------------------------
// Signal Handlers
// ---------------------------------------------------------------

static int status_interval = 5; // in seconds

void timer_handler(int signum) {
  if(verbose) { status_flag=true; }
  current_timeout -= status_interval;
  alarm(status_interval);
}

void print_status() {
  status_flag=false;
  double rate = (num_steps - old_num_steps);
  double cf = (100*((double)cache.size())) / cache.capacity();
  rate /= status_interval;
  cout << "Completed " << num_steps << " graphs at rate of " << ((int) rate) << "/s, cache is " << setprecision(3) << cf << "% full." << endl;
  old_num_steps = num_steps;  
}

// ---------------------------------------------------------------
// Run Method
// ---------------------------------------------------------------

template<class G, class P>
void run(ifstream &input, unsigned int ngraphs, vorder_t vertex_ordering, boolean info_mode) {
  unsigned int ngraphs_completed=0;  
  while(!input.eof() && ngraphs_completed < ngraphs) {
    // first, reset all stats information
    cache.clear();  
    cache.reset_stats();
    num_steps = 0;
    num_bicomps = 0;
    num_disbicomps = 0;
    num_trees = 0;
    num_cycles = 0;
    current_timeout = timeout;

    // Create graph and then permute it according to 
    // vertex ordering strategy
    G start_graph = read_graph<G>(input);
    start_graph = permute_graph<G>(start_graph,vertex_ordering);

    // remove useless vertices
    for(typename G::vertex_iterator i(start_graph.begin_verts());
	i!=start_graph.end_verts();++i) {
      if(start_graph.num_edges(*i) == 0) { start_graph.remove(*i); }
    }

    unsigned int V(start_graph.num_vertices());
    unsigned int E(start_graph.num_edges());
    if(start_graph.num_vertices() == 0) { break; }

    my_timer timer(false);
    if(write_tree) { write_tree_start(ngraphs_completed); }    

    P tuttePoly = T<G,P>(start_graph,1);        

    if(write_tree) { write_tree_end(ngraphs_completed); }

    if(!verbose) {
      if(info_mode) {
	cout << V << "\t" << E;    
	cout << "\t" << setprecision(3) << timer.elapsed() << "\t" << num_steps << "\t" << num_bicomps << "\t" << num_disbicomps << "\t" << num_cycles << "\t" << num_trees;
	cout << "\t" << tuttePoly.substitute(1,1) << "\t" << tuttePoly.substitute(2,2) << endl;
      }
    } else {
      cout << "TP[" << (ngraphs_completed+1) << "] := " << tuttePoly.str() << " :" << endl;
      if(info_mode) {
	cout << "=======" << endl;
	cout << "V = " << V << ", E = " << E << endl;
	cout << "Size of Computation Tree: " << num_steps << " graphs." << endl;	
	cout << "Number of Biconnected Components Extracted: " << num_bicomps << "." << endl;	
	cout << "Number of Biconnected Components Separated: " << num_disbicomps << "." << endl;	
	cout << "Number of Cycles Terminated: " << num_cycles << "." << endl;	
	cout << "Number of Trees Terminated: " << num_trees << "." << endl;	
	cout << "Time : " << setprecision(3) << timer.elapsed() << "s" << endl;
	cout << "T(1,1) = " << tuttePoly.substitute(1,1) << endl;
	cout << "T(2,2) = " << tuttePoly.substitute(2,2) << " (should be " << pow(biguint(2U),E) << ")" << endl;	
	// The tutte at T(-1,-1) should always give a (positive or
	// negative) power of 2.  Currently, we cannot generate this
	// here, since you cannot pass negative numbers to
	// substitite().
      }
    }
    ++ngraphs_completed;
  }
}

// ---------------------------------------------------------------
// Main Method
// ---------------------------------------------------------------

int main(int argc, char *argv[]) {

  // ------------------------------
  // Process command-line arguments
  // ------------------------------

  #define OPT_HELP 0
  #define OPT_QUIET 1  
  #define OPT_INFO 2
  #define OPT_SMALLGRAPHS 5
  #define OPT_NGRAPHS 6
  #define OPT_TIMEOUT 7
  #define OPT_CACHESIZE 10
  #define OPT_CACHEBUCKETS 11  
  #define OPT_CACHEREPLACEMENT 12
  #define OPT_CACHERANDOM 13
  #define OPT_CACHESTATS 14
  #define OPT_NOCACHE 15
  #define OPT_SIMPLE_POLY 30
  #define OPT_FACTOR_POLY 31
  #define OPT_XML_OUT 32
  #define OPT_TREE_OUT 33
  #define OPT_FULLTREE_OUT 34
  #define OPT_SMALL 40
  #define OPT_MEDIUM 41
  #define OPT_LARGE 42
  #define OPT_WITHLINES 43
  #define OPT_NOMULTICYCLES 44
  #define OPT_NOMULTIEDGES 45
  #define OPT_MAXDEGREE 50
  #define OPT_MAXMDEGREE 51
  #define OPT_MINDEGREE 52
  #define OPT_MINMDEGREE 53
  #define OPT_MINSDEGREE 54
  #define OPT_VERTEXORDER 55
  #define OPT_RANDOM 56
  #define OPT_RANDOM_ORDERING 60
  #define OPT_MINDEG_ORDERING 61
  #define OPT_MAXDEG_ORDERING 62
  #define OPT_MINUDEG_ORDERING 63
  #define OPT_MAXUDEG_ORDERING 64

  
  struct option long_options[]={
    {"help",no_argument,NULL,OPT_HELP},
    {"info",no_argument,NULL,OPT_INFO},
    {"quiet",no_argument,NULL,OPT_QUIET},
    {"timeout",required_argument,NULL,OPT_TIMEOUT},
    {"cache-size",required_argument,NULL,OPT_CACHESIZE},
    {"cache-buckets",required_argument,NULL,OPT_CACHEBUCKETS},
    {"cache-replacement",required_argument,NULL,OPT_CACHEREPLACEMENT},
    {"cache-random",no_argument,NULL,OPT_CACHERANDOM}, 
    {"cache-stats",optional_argument,NULL,OPT_CACHESTATS},   
    {"no-caching",no_argument,NULL,OPT_NOCACHE},
    {"minimise-degree", no_argument,NULL,OPT_MINDEGREE},
    {"minimise-mdegree", no_argument,NULL,OPT_MINMDEGREE},
    {"minimise-sdegree", no_argument,NULL,OPT_MINSDEGREE},
    {"maximise-degree", no_argument,NULL,OPT_MAXDEGREE},
    {"maximise-mdegree", no_argument,NULL,OPT_MAXMDEGREE},
    {"vertex-order", no_argument,NULL,OPT_VERTEXORDER},
    {"random-ordering",no_argument,NULL,OPT_RANDOM_ORDERING},
    {"mindeg-ordering",no_argument,NULL,OPT_MINDEG_ORDERING},
    {"maxdeg-ordering",no_argument,NULL,OPT_MAXDEG_ORDERING},
    {"minudeg-ordering",no_argument,NULL,OPT_MINUDEG_ORDERING},
    {"maxudeg-ordering",no_argument,NULL,OPT_MAXUDEG_ORDERING},
    {"random", no_argument,NULL,OPT_RANDOM},
    {"small-graphs",required_argument,NULL,OPT_SMALLGRAPHS},
    {"simple-poly",no_argument,NULL,OPT_SIMPLE_POLY},
    {"tree",no_argument,NULL,OPT_TREE_OUT},
    {"full-tree",no_argument,NULL,OPT_FULLTREE_OUT},
    {"xml-tree",no_argument,NULL,OPT_XML_OUT},
    {"ngraphs",required_argument,NULL,OPT_NGRAPHS},
    {"small",no_argument,NULL,OPT_SMALL},
    {"medium",no_argument,NULL,OPT_MEDIUM},
    {"large",no_argument,NULL,OPT_LARGE},
    {"with-lines",no_argument,NULL,OPT_WITHLINES},
    {"no-multicycles",no_argument,NULL,OPT_NOMULTICYCLES},
    {"no-multiedges",no_argument,NULL,OPT_NOMULTIEDGES},
    NULL
  };
  
  char *descriptions[]={
    "        --help                    display this information",
    " -i     --info                    output summary information regarding computation",
    " -q     --quiet                   output info summary as single line only (useful for generating data)",
    " -t     --timeout=<x>             timeout after x seconds",
    "        --small-graphs=size       set threshold for small graphs, e.g. 7",
    " -n<x>  --ngraphs=<number>        number of graphs to process from input file",
    "        --tree                    output computation tree",
    "        --full-tree               output full computation tree",
    "        --xml-tree                output computation tree as XML",
    "        --small                   use 32-bit integers only",
    "        --medium                  use 64-bit integers only",
    "        --large                   use unbound integers (default)",
    "        --with-lines              delete-contract on lines, not just edges",
    " \ncache options:",
    " -c<x>  --cache-size=<amount>     set sizeof cache to allocate, e.g. 700M",
    "        --cache-buckets=<amount>  set number of buckets to use in cache, e.g. 10000",
    "        --cache-random            set random replacement policy",
    "        --cache-replacement=<amount> set ratio (between 0 .. 1) of cache to displace when full",
    "        --cache-stats[=<file>]    print cache stats summary, or write detailed stats to file.",
    "        --no-caching              disable caching",
    " \nedge selection heuristics:",
    "        --minimise-degree         minimise endpoint (underlying) degree sum",
    "        --minimise-sdegree        minimise single endpoint (underlying) degree",
    "        --minimise-mdegree        minimise endpoint degree",
    "        --maximise-degree         maximise endpoint (underlying) degree",
    "        --maximise-sdegree        maximise single endpoint (underlying) degree",
    "        --maximise-mdegree        maximise endpoint degree",
    "        --vertex-order            select first available non-tree edge, starting from vertex 0",
    "        --random                  random selection",
    " \nvertex ordering heuristics:",
    "        --random-ordering         use random ordering of vertices",
    "        --mindeg-ordering         sort vertices by degree, with smallest first",
    "        --maxdeg-ordering         sort vertices by degree, with largest first",
    NULL
  };

  unsigned int v;
  unsigned int cache_size(256 * 1024 * 1024); 
  unsigned int cache_buckets(1000000);     // default 1M buckets
  unsigned int poly_rep(OPT_FACTOR_POLY);
  unsigned int ngraphs(UINT_MAX); // default is to do every graph in input file
  unsigned int size = OPT_LARGE;
  bool info_mode=false;
  bool cache_stats=false;
  vorder_t vertex_ordering(V_MAXIMISE_UNDERLYING_DEGREE);
  string cache_stats_file("");

  while((v=getopt_long(argc,argv,"qic:n:t:",long_options,NULL)) != -1) {
    switch(v) {      
    case OPT_HELP:
      cout << "usage: " << argv[0] << " [options] <input graph file>" << endl;
      cout << "options:" << endl;
      for(char **ptr=descriptions;*ptr != NULL; ptr++) {
	cout << *ptr << endl;
      }    
      exit(1);
          
    case 'q':
    case OPT_QUIET:      
      verbose=false;
      break;
    case 't':
    case OPT_TIMEOUT:
      timeout = atoi(optarg);
      break;
    case 'n':
    case OPT_NGRAPHS:
      ngraphs = atoi(optarg);
      break;
    case OPT_XML_OUT:
      write_tree=true;
      xml_flag=true;
      break;
    case 'i':
    case OPT_INFO:
      info_mode=true;
      break;
    case OPT_FULLTREE_OUT:
      write_tree=true;
      write_full_tree=true;
      break;
    case OPT_TREE_OUT:
      write_tree=true;
      break;
    // --- CACHE OPTIONS ---
    case 'c':
    case OPT_CACHESIZE:
      cache_size = parse_amount(optarg);
      break;
    case OPT_CACHEBUCKETS:
      cache_buckets = parse_amount(optarg);
      break;
    case OPT_CACHEREPLACEMENT:
      cache.set_replacement(strtof(optarg,NULL));
      break;
    case OPT_CACHERANDOM:
      cache.set_random_replacement();
      break;
    case OPT_CACHESTATS:
      if(optarg == NULL) {
	cache_stats=true;
      } else {
	cache_stats_file = string(optarg);
      }
      break;
    case OPT_NOCACHE:
      small_graph_threshold = 10000;
      break;
    // --- POLY OPTIONS ---
    case OPT_SIMPLE_POLY:
      poly_rep = OPT_SIMPLE_POLY;
      break;
    // --- HEURISTICS ---
    case OPT_MINDEGREE:
      edge_selection_heuristic = MINIMISE_DEGREE;
      break;
    case OPT_MAXDEGREE:
      edge_selection_heuristic = MAXIMISE_DEGREE;
      break;
    case OPT_MAXMDEGREE:
      edge_selection_heuristic = MAXIMISE_MDEGREE;
      break;
    case OPT_MINMDEGREE:
      edge_selection_heuristic = MINIMISE_MDEGREE;
      break;
    case OPT_MINSDEGREE:
      edge_selection_heuristic = MINIMISE_SDEGREE;
      break;
    case OPT_VERTEXORDER:
      edge_selection_heuristic = VERTEX_ORDER;
      break;
    case OPT_RANDOM:
      edge_selection_heuristic = RANDOM;
      break;
    case OPT_RANDOM_ORDERING:
      vertex_ordering = V_RANDOM;
      break;
    case OPT_MINDEG_ORDERING:
      vertex_ordering = V_MINIMISE_DEGREE;
      break;
    case OPT_MAXDEG_ORDERING:
      vertex_ordering = V_MAXIMISE_DEGREE;
      break;
    case OPT_MINUDEG_ORDERING:
      vertex_ordering = V_MINIMISE_UNDERLYING_DEGREE;
      break;
    case OPT_MAXUDEG_ORDERING:
      vertex_ordering = V_MAXIMISE_UNDERLYING_DEGREE;
      break;
    // --- OTHER OPTIONS ---
    case OPT_SMALLGRAPHS:
      small_graph_threshold = parse_amount(optarg);      
      break;      
    case OPT_SMALL:
    case OPT_MEDIUM:
    case OPT_LARGE:
      size=v;
      break;
    case OPT_WITHLINES:
      reduce_lines=true;
      break;
    case OPT_NOMULTICYCLES:
      reduce_multicycles=false;
      break;
    case OPT_NOMULTIEDGES:
      reduce_multiedges=false;
      break;
    default:
      cout << "Unrecognised parameter!" << endl;
      exit(1);    
    }    
  }

  // Quick sanity check

  if(optind >= argc) {
    cout << "usage: " << argv[0] << " [options] <input graph file>" << endl;
    cout << "options:" << endl;
    for(char **ptr=descriptions;*ptr != NULL; ptr++) {
      cout << *ptr << endl;
    }    
    exit(1);
  }

  // -------------------------------------------------
  // Initialise Cache 
  // -------------------------------------------------
  try {
    cache.resize(cache_size);
    cache.rebucket(cache_buckets);
    
  // -------------------------------------------------
  // Register alarm signal for printing status updates
  // -------------------------------------------------

    struct sigaction sa;
    memset(&sa,0,sizeof(sa));
    sa.sa_handler = &timer_handler;
    if(sigaction(SIGALRM,&sa,NULL)) { perror("sigvtalarm"); }
    alarm(status_interval); // trigger alarm in status_interval seconds
    
    // -----------------------------------
    // Now, begin solving the input graph!
    // -----------------------------------
    
    srand(time(NULL));
        
    ifstream input(argv[optind]);    
    if(poly_rep == OPT_FACTOR_POLY) {
      if(size == OPT_SMALL) {
	run<spanning_graph<adjacency_list<> >,factor_poly<safe<unsigned int> > >(input,ngraphs,vertex_ordering,info_mode);
      } else if(size == OPT_MEDIUM) {       
	run<spanning_graph<adjacency_list<> >,factor_poly<safe<unsigned long long> > >(input,ngraphs,vertex_ordering,info_mode);
      } else {
	run<spanning_graph<adjacency_list<> >,factor_poly<biguint> >(input,ngraphs,vertex_ordering,info_mode);
      }
    } else {
      //      run<spanning_graph<adjacency_list<> >,simple_poly<> >(input,ngraphs,vertex_ordering);
    }    

    if(cache_stats) {
      cout << endl << "Cache stats:" << endl << "------------" << endl;
      cout << "Density: " << (cache.density()*1024*1024) << " graphs/MB" << endl;
      cout << "# Entries: " << cache.num_entries() << endl;
      cout << "# Cache Hits: " << cache.num_hits() << endl;
      cout << "# Cache Misses: " << cache.num_misses() << endl;
      cout << "# Cache Collisions: " << cache.num_collisions() << endl;
      cout << "Min Bucket Length: " << cache.min_bucket_size() << endl;
      cout << "Max Bucket Length: " << cache.max_bucket_size() << endl;
    }

    if(cache_stats_file != "") {
      fstream stats_out(cache_stats_file.c_str(),fstream::out);
      write_bucket_lengths(stats_out);
      write_graph_sizes(stats_out);
      write_hit_counts(stats_out);
    }
  } catch(std::runtime_error &e) {
    cerr << "error: " << e.what() << endl;  
  } catch(std::bad_alloc &e) {
    cerr << "error: insufficient memory!" << endl;
  } catch(std::exception &e) {
    cerr << "error: " << e.what() << endl;
  }
}






                                            
