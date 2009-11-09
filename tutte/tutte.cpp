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
#include <sstream>
#include <stack>
#include <list>
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
#include "misc/bigint.hpp"

#include "reductions.hpp"
#include "../config.h"

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

typedef enum { AUTO, RANDOM, CUT, MAXIMISE_DEGREE, MINIMISE_DEGREE, MAXIMISE_MDEGREE, MINIMISE_MDEGREE, MAXIMISE_SDEGREE, MINIMISE_SDEGREE, VERTEX_ORDER } edgesel_t;
typedef enum { V_RANDOM, V_MINIMISE_UNDERLYING_DEGREE,  V_MAXIMISE_UNDERLYING_DEGREE, V_MINIMISE_DEGREE,  V_MAXIMISE_DEGREE, V_NONE } vorder_t;

unsigned int resize_stats = 0;
unsigned long num_steps = 0;
unsigned long num_bicomps = 0;
unsigned long num_cycles = 0;
unsigned long num_disbicomps = 0;
unsigned long num_trees = 0;
unsigned long num_completed = 0;
unsigned long old_num_steps = 0;

// Following is used to time computation, and provide timeout
// facility.
static long timeout = 15768000; // one years worth of timeout (in s)
static my_timer global_timer(false);

static unsigned int small_graph_threshold = 5;
static edgesel_t edge_selection_heuristic = AUTO;
static edgesel_t edge_addition_heuristic = AUTO;
static simple_cache cache(1024*1024,100);
static vector<pair<int,int> > evalpoints;
static vector<unsigned int> cache_hit_sizes;
static unsigned int ngraphs_completed=0;  
static unsigned int split_threshold=0;
static bool status_flag=false;
static bool verbose=true;
static bool reduce_multicycles=true;
static bool reduce_multiedges=true;
static bool use_add_contract=false;
static bool xml_flag=false;
static unsigned int tree_id = 2;
static bool write_tree=false;
static bool write_full_tree=false;

#define MODE_TUTTE 0
#define MODE_CHROMATIC 1
#define MODE_FLOW 2
#define MODE_TUTTE_SPLIT 3
#define MODE_TUTTEX 4
static int mode = MODE_TUTTE;

void print_status();

// ---------------------------------------------------------------
// Tree Output Methods
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

// ---------------------------------------------------------------
// SELECT EDGE
// ---------------------------------------------------------------

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
  edgesel_t heuristic = edge_selection_heuristic;
  typename G::edge_t r(-1,-1,-1);

  if(edge_selection_heuristic == RANDOM) {
    unsigned int nedges = graph.num_edges();
    rtarget = (unsigned int) (((double) nedges*rand()) / (1.0+RAND_MAX));
  } else if(edge_selection_heuristic == CUT) {
    for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
      unsigned int head = *i;
      unsigned int headc(graph.num_underlying_edges(head));
      
      for(typename G::edge_iterator j(graph.begin_edges(*i));
	  j!=graph.end_edges(*i);++j) {	
	unsigned int tail = j->first;
	unsigned int tailc(graph.num_underlying_edges(tail));
	unsigned int count = j->second;
	unsigned int cost = UINT_MAX;

	if(head < tail) { // to avoid duplicates
	  // er, yes this is a tad ott.
	  G g(graph);
	  g.remove_all_edges(head,tail);
	  if(!g.is_biconnected()) {
	    unsigned int start = 0;
	    
	    vector<G> biconnects;
	    g.extract_biconnected_components(biconnects);
	    g.remove_graphs(biconnects);
	    
	    // now, actually do the computation
	    cost = g.num_vertices();
	    for(typename vector<G>::iterator k(biconnects.begin());k!=biconnects.end();++k){
	      cost = std::min<unsigned int>(cost,k->num_vertices());	
	    }
	  }
	  if(cost > 10 && cost > best && cost < UINT_MAX) {	    	    
	    r = typename G::edge_t(head,tail,reduce_multiedges ? count : 1);
	    best = cost;
	  }     
	}
      }
    }    
    if(best != 0) { 
      cout << "BEST = " << best << endl;
      return r; }
    heuristic = VERTEX_ORDER;
  }

  for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    unsigned int head = *i;
    unsigned int headc(graph.num_underlying_edges(head));
    
    for(typename G::edge_iterator j(graph.begin_edges(*i));
	j!=graph.end_edges(*i);++j) {	
      unsigned int tail = j->first;
      unsigned int tailc(graph.num_underlying_edges(tail));
      unsigned int count = j->second;

      if(head < tail) { // to avoid duplicates
	unsigned int cost;
	switch(heuristic) {
	case MAXIMISE_SDEGREE:
	  cost = std::max(headc,tailc);
	  break;
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
	  break;
	case CUT:
	  // er, yes this is a tad ott.
	  G g(graph);
	  g.remove_all_edges(head,tail);
	  if(!g.is_biconnected()) {
	    unsigned int start = 0;
	    
	    vector<G> biconnects;
	    g.extract_biconnected_components(biconnects);
	    g.remove_graphs(biconnects);
	    unsigned int m = g.num_edges();
	    
	    // now, actually do the computation
	    for(typename vector<G>::iterator k(biconnects.begin());k!=biconnects.end();++k){
	      cost = std::max<unsigned int>(cost,k->num_edges());	
	    }
	  }
	}    
	if(cost > best) {	    
	  r = typename G::edge_t(head,tail,reduce_multiedges ? count : 1);
	  best = cost;
	}     
      }
    }
  }
  
  if(best == 0) { throw std::runtime_error("internal failure (select_edge)"); }

  return r;
} 

template<class G>
typename G::edge_t select_missing_edge(G const &graph) {
  unsigned int best(0);
  unsigned int V(graph.num_vertices());
  unsigned int rcount(0);
  unsigned int rtarget(0);
  typename G::edge_t r(-1,-1,-1);
  
  if(edge_addition_heuristic == RANDOM) {
    unsigned int V_Vm1_d2 = (V * (V-1)) / 2;
    unsigned int nedges = V_Vm1_d2 - graph.num_edges();
    rtarget = (unsigned int) (((double) nedges*rand()) / (1.0+RAND_MAX));
  }
  
  // interesting: what heuristics could we do here?
  unsigned int Vm1 = graph.num_vertices()-1;
  
  for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    unsigned int head = *i;
    unsigned int headc(graph.num_underlying_edges(head));

    if(graph.num_edges(head) != Vm1) {
      // now, find the edge
      for(typename G::vertex_iterator j(graph.begin_verts());j!=graph.end_verts();++j) {
	unsigned int tail = *j;
	if(*i!=*j && head < tail && graph.num_edges(head,*j) == 0) {
	  unsigned int tailc(graph.num_underlying_edges(tail));
	  
	  if(head < tail) { // to avoid duplicates
	    unsigned int cost;
	    switch(edge_addition_heuristic) {
	    case MAXIMISE_SDEGREE:
	      cost = std::max(headc,tailc);
	      break;
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
	      return typename G::edge_t(head,tail,1);
	      break;
	    case RANDOM:
	      if(rcount == rtarget) {
		return typename G::edge_t(head,tail,1);
	      }
	      rcount ++;	    
	    }
	    if(cost > best) {	    
	      r = typename G::edge_t(head,tail,1);
	      best = cost;
	    }     	    
	  }	
	}
      }
    }
  }

  if(best == 0) { throw std::runtime_error("internal failure (select_missing_edge)"); }

  return r;
}

// ------------------------------------------------------------------
// Tutte Polynomial
// ------------------------------------------------------------------

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
P tutte(G &graph, unsigned int mid) { 
  if(global_timer.elapsed() >= timeout) { return P(X(0)); }
  if(status_flag) { print_status(); }
  num_steps++;

  // === 1. APPLY SIMPLIFICATIONS ===

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
      cache_hit_sizes[graph.num_vertices()]++;
      return r * RF;
    } 
  }
  
  P poly;

  // === 3. CHECK FOR ARTICULATIONS, DISCONNECTS AND/OR TREES ===

  if(reduce_multicycles && graph.is_multicycle()) {
    num_cycles++;
    poly = reduce_cycle<G,P>(X(1),graph);
    if(write_tree) { write_tree_leaf(mid,graph,cout); }
  } else if(!graph.is_biconnected()) {
    vector<G> biconnects;
    graph.extract_biconnected_components(biconnects);

    // figure out how many tree ids I need
    unsigned int tid(tree_id);
    tree_id += biconnects.size();
    if(biconnects.size() > 0 && write_tree) { write_tree_nonleaf(mid,tid,tree_id-tid,graph,cout); }
    else if(write_tree) { write_tree_leaf(mid,graph,cout); }

    graph.remove_graphs(biconnects);
    if(graph.is_multitree()) { num_trees++; }
    if(biconnects.size() > 1) { num_disbicomps++; }
    poly = reduce_tree<G,P>(X(1),graph);

    // now, actually do the computation
    for(typename vector<G>::iterator i(biconnects.begin());i!=biconnects.end();++i){
      num_bicomps++;
      if(i->is_multicycle()) {
	// this is actually a cycle!
	num_cycles++;
	poly *= reduce_cycle<G,P>(X(1),*i);
	if(write_tree) { write_tree_leaf(tid++,*i,cout); }
      } else {
	poly *= tutte<G,P>(*i,tid++);      
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
    edge_t edge = select_edge(graph);

    // now, delete/contract on the edge's endpoints
    graph.remove_edge(edge);
    g2.contract_edge(edge);

    // recursively compute the polynomial, starting with delete       
    if(edge.third > 1) { 
      poly = tutte<G,P>(graph, lid);
      poly += (tutte<G,P>(g2, rid) * Y(0,edge.third-1));
    } else {
      poly = tutte<G,P>(graph, lid);
      poly += tutte<G,P>(g2, rid);
    }
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

template<class G, class P>
void tutteSearch(G &graph, vector<G> &graphs) { 
  if(status_flag) { print_status(); }

  // === 1. APPLY SIMPLIFICATIONS ===

  P RF = Y(reduce_loops(graph));

  // === 2. CHECK IN CACHE ===

  unsigned char *key = NULL;
  if(graph.num_vertices() >= small_graph_threshold && !graph.is_multitree()) {      
    key = graph_key(graph); 
    unsigned int match_id;
    P r; // unused
    if(cache.lookup(key,r,match_id)) { 
      delete [] key; // free space used by key
      return;
    }
  }

  // === 3. CHECK FOR ARTICULATIONS, DISCONNECTS AND/OR TREES ===

  if(reduce_multicycles && graph.is_multicycle()) {
    // again, do nothing since this graph is reduced as is.
  } else if(!graph.is_biconnected()) {
    vector<G> biconnects;
    graph.extract_biconnected_components(biconnects);
    graph.remove_graphs(biconnects);

    // now, actually do the computation
    for(typename vector<G>::iterator i(biconnects.begin());i!=biconnects.end();++i){
      if(!i->is_multicycle()) {
	tutteSearch<G,P>(*i,graphs);      
      }
    }
  } else {

    if(graph.num_vertices() < split_threshold) {
      graphs.push_back(graph);
      return;
    }

    G g2(graph); 
    edge_t edge = select_edge(graph);

    // now, delete/contract on the edge's endpoints
    graph.remove_edge(edge);
    g2.contract_edge(edge);

    tutteSearch<G,P>(graph,graphs);
    tutteSearch<G,P>(g2,graphs);
  }
  
  // Finally, save computed polynomial
  if(key != NULL) {
    // there is, strictly speaking, a bug with using mid
    // here, since the graph being stored is not the same as that
    // at the beginning.
    unsigned int tmp;
    cache.store(key,P(),tmp);
    delete [] key;  // free space used by key
  }    
}

// ------------------------------------------------------------------
// Flow Polynomial
// ------------------------------------------------------------------

/* This is the core algorithm for the flow polynomial computation it
 * reduces a graph to two smaller graphs using a delete operation for
 * one, and a contract operation for the other.
 *
 * The algorithm also uses a number of tricks to prune the computation
 * space.  These include: eliminating small graphs using optimised, 
 * hand-coded decision procedures; storing previously seen graphs
 * in a cache; and, dynamically monitoring the "treeness" of the graph.
 */
template<class G, class P>
P flow(G &graph, unsigned int mid) { 
  if(global_timer.elapsed() >= timeout) { return P(X(0)); }
  if(status_flag) { print_status(); }
  num_steps++;

  // === 1. APPLY SIMPLIFICATIONS ===

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
      cache_hit_sizes[graph.num_vertices()]++;
      return r * RF;
    }
  }

  P poly;

  // === 3. CHECK FOR ARTICULATIONS, DISCONNECTS AND/OR TREES ===

  if(reduce_multicycles && graph.is_multicycle()) {
    num_cycles++;
    poly = reduce_cycle<G,P>(P(),graph);
    if(write_tree) { write_tree_leaf(mid,graph,cout); }
  } else if(!graph.is_biconnected()) {
    vector<G> biconnects;
    graph.extract_biconnected_components(biconnects);

    // figure out how many tree ids I need
    unsigned int tid(tree_id);
    tree_id += biconnects.size();
    if(biconnects.size() > 0 && write_tree) { write_tree_nonleaf(mid,tid,tree_id-tid,graph,cout); }
    else if(write_tree) { write_tree_leaf(mid,graph,cout); }

    graph.remove_graphs(biconnects);

    // this is a little ugly
    for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
      for(typename G::edge_iterator j(graph.begin_edges(*i));j!=graph.end_edges(*i);++j) {
	if(j->second == 1) {
	  // in the flow polynomial, if there's a single
	  // non-multi-edge then you throw away the whole graph.
	  num_trees++; 
	  if(write_tree) { write_tree_leaf(mid,graph,cout); }
	  // Don't forget ... save computed polynomial!
	  if(key != NULL) {
	    // there is, strictly speaking, a bug with using mid
	    // here, since the graph being stored is not the same as that
	    // at the beginning.
	    cache.store(key,poly,mid);
	    delete [] key;  // free space used by key
	  }    
	  return P(); 
	}
      }
    } 

    if(graph.is_multitree()) { num_trees++; }
    if(biconnects.size() > 1) { num_disbicomps++; }
    poly = reduce_tree<G,P>(P(),graph);

    for(typename vector<G>::iterator i(biconnects.begin());i!=biconnects.end();++i){
      num_bicomps++;
      if(i->is_multicycle()) {
	// this is actually a cycle!
	num_cycles++;
	poly *= reduce_cycle<G,P>(P(),*i);
	if(write_tree) { write_tree_leaf(tid++,*i,cout); }
      } else {
	poly *= flow<G,P>(*i,tid++);      
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
    edge_t edge = select_edge(graph);

    // now, delete/contract on the line's endpoints
    graph.remove_edge(edge);
    g2.contract_edge(edge);
    // recursively compute the polynomial   
    if(edge.third > 1) { 
      poly = flow<G,P>(graph, lid) + (flow<G,P>(g2, rid) * Y(0,edge.third-1));
    } else {
      poly = flow<G,P>(graph, lid) + flow<G,P>(g2, rid);
    }    
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

// ------------------------------------------------------------------
// Chromatic Polynomial
// ------------------------------------------------------------------

/* This is the core algorithm for the chromatic computation it reduces
 * a graph to two smaller graphs using a delete operation for one, and
 * a contract operation for the other.
 *
 * The algorithm also uses a number of tricks to prune the computation
 * space.  These include: eliminating small graphs using optimised, 
 * hand-coded decision procedures; storing previously seen graphs
 * in a cache; and, dynamically monitoring the "treeness" of the graph.
 */
template<class G, class P>
P chromatic(G &graph, unsigned int mid) { 
  if(global_timer.elapsed() >= timeout) { return P(X(0)); }
  if(status_flag) { print_status(); }
  num_steps++;

  // === 1. CHECK IN CACHE ===

  unsigned char *key = NULL;
  if(graph.num_vertices() >= small_graph_threshold) {      
    key = graph_key(graph); 
    unsigned int match_id;
    P r;
    if(cache.lookup(key,r,match_id)) { 
      if(write_tree) { write_tree_match(mid,match_id,graph,cout); }
      delete [] key; // free space used by key
      cache_hit_sizes[graph.num_vertices()]++;
      return r;
    }
  }

  P poly;
  unsigned int V_Vm1 = graph.num_vertices()*(graph.num_vertices()-1);

  if(!graph.is_biconnected()) {
    vector<G> biconnects;
    graph.extract_biconnected_components(biconnects);

    // figure out how many tree ids I need
    unsigned int tid(tree_id);
    tree_id += biconnects.size();
    if(biconnects.size() > 0 && write_tree) { write_tree_nonleaf(mid,tid,tree_id-tid,graph,cout); }
    else if(write_tree) { write_tree_leaf(mid,graph,cout); }

    graph.remove_graphs(biconnects);
    if(graph.is_multitree()) { num_trees++; }
    if(biconnects.size() > 1) { num_disbicomps++; }
    poly = X(graph.num_edges());
    // now, actually do the computation
    for(typename vector<G>::iterator i(biconnects.begin());i!=biconnects.end();++i){
      num_bicomps++;
      poly *= chromatic<G,P>(*i,tid++);      
    } 
  } else if((2*graph.num_edges()) == V_Vm1) {
    // in this case we compute the complete graph directly
    poly = X(1);
    P tmp(X(1));
    for(int i=0;i!=graph.num_vertices()-2;++i) {
      tmp += X(0);
      poly *= tmp;
    }
    num_completed++;
  } else {

    // TREE OUTPUT STUFF
    unsigned int lid = tree_id;
    unsigned int rid = tree_id+1;
    tree_id = tree_id + 2; // allocate id's now so I know them!
    if(write_tree) { write_tree_nonleaf(mid,lid,2,graph,cout); }
    
    G g2(graph); 
    if(use_add_contract && (4*graph.num_edges()) > V_Vm1) {
      // === 3. PERFORM ADD / CONTRACT ===
      
      // Edge density is closer to complete graph than empty graph.
      // So, go upwards instead of downwards!
      
      edge_t edge = select_missing_edge(graph);

      // now, add/contract on the edges endpoints
      graph.add_edge(edge.first,edge.second);
      g2.simple_contract_edge(edge);  
      
      // recursively compute the polynomial   
      poly = chromatic<G,P>(graph, lid) - chromatic<G,P>(g2, rid);
    } else {
      // === 4. PERFORM DELETE / CONTRACT ===
      edge_t edge = select_edge(graph);
      
      // now, delete/contract on the line's endpoints
      graph.remove_edge(edge);
      g2.simple_contract_edge(edge);  
      
      // recursively compute the polynomial   
      poly = chromatic<G,P>(graph, lid) + chromatic<G,P>(g2, rid);
    } 
  }

  // Finally, save computed polynomial
  if(key != NULL) {
    // there is, strictly speaking, a bug with using mid
    // here, since the graph being stored is not the same as that
    // at the beginning.
    cache.store(key,poly,mid);
    delete [] key;  // free space used by key
  }

  return poly;
}

// ------------------------------------------------------------------
// Experimental Tutte Polynomial
// ------------------------------------------------------------------
template<class G, class P>
P tuttex(G &rootgraph) { 
  static std::list<G> graphs;
  graphs.push_back(rootgraph);
  P poly(Y(0));
  int level=0;

  while(graphs.size() != 0) {
    //    cache.clear();
    // First, prune out any isomorphic graphs

    cout << "LEVEL " << level++ << ": " << graphs.size() << endl;

    int gsize = graphs.size();
    typename std::list<G>::iterator iter(graphs.begin());
    for(int i=0;i<gsize;++i) {
      if(status_flag) { print_status(); }
      num_steps++;
      G &graph = *iter;

      P RF = Y(reduce_loops(graph));
      
      unsigned char *key = NULL;   
      if(graph.num_vertices() >= small_graph_threshold && !graph.is_multitree()) {      
	key = graph_key(graph); 
	unsigned int match_id;
	P r; // unused
	if(cache.lookup(key,r,match_id)) { 
	  cache_hit_sizes[graph.num_vertices()]++;
	  iter = graphs.erase(iter);
	  delete [] key;
	  continue; // don't do anything else for this round
	} else {
	  unsigned int tmp;
	  cache.store(key,r,tmp);	  
	}	
	delete [] key;
      } 

      if(reduce_multicycles && graph.is_multicycle()) {
	num_cycles++;
	//	poly += reduce_cycle<G,P>(X(1),graph);
	iter = graphs.erase(iter);	
      } else if(!graph.is_biconnected()) {
	vector<G> biconnects;
	graph.extract_biconnected_components(biconnects);
	
	graph.remove_graphs(biconnects);
	if(graph.is_multitree()) { num_trees++; }
	if(biconnects.size() > 1) { num_disbicomps++; }
	//	poly += reduce_tree<G,P>(X(1),graph);

	graphs.insert(graphs.end(),biconnects.begin(),biconnects.end());
	iter = graphs.erase(iter);
      } else {
	G g2(graph); 
	edge_t edge = select_edge(graph);
	
	// now, delete/contract on the edge's endpoints
	graph.remove_edge(edge);
	g2.contract_edge(edge);
	
	graphs.push_back(g2);
		
	++iter;
      }
    }
  }

  return poly;
}

// ---------------------------------------------------------------
// Input File Parser
// ---------------------------------------------------------------

string read_line(istream &in) {
  char c;
  string str;

  in.get(c); 
  while(!in.eof() && c != '\n') {
    if(c != '\r') {
      str = str + c;
    }
    in.get(c);  
  }

  return str;
}

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

biguint parse_bignumber(unsigned int &pos, string const &str) {
  int s = pos;
  while(pos < str.length() && isdigit(str[pos])) {
    pos = pos + 1;
  }
  biguint r;
  biguint ten = biguint((uint32_t)10);
  for(unsigned int i=0;i!=(pos-s);++i) {
    char c=str[pos-(i+1)];
    uint32_t d = c - '0';
    r += pow(ten,i) * biguint(d);
  }
  return r;
}

void match(char c, unsigned int &pos, string const &str) {
  if(pos >= str.length() || str[pos] != c) { 
    std::ostringstream out;
    out << "syntax error -- expected '" << c << "', got '" << str[pos] << "'";
    throw runtime_error(out.str()); 
  }
  ++pos;
}

void skip(unsigned int &pos, string const &in) {
  while(pos < in.length() && (in[pos] == ' ' || in[pos]=='\t')) {
    pos++;
  } 
}

template<class G>
G read_graph(string in) {
  vector<pair<unsigned int, unsigned int> > edgelist;
  unsigned int V = 0, pos = 0;
    
  bool firstTime=true;

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

template<class G>
G read_init_graph(string in) {
  unsigned int pos = 0;
  match('G',pos,in);
  match('[',pos,in);
  unsigned int id = parse_number(pos,in);
  match(']',pos,in);
  unsigned int s = ' ';
  unsigned int b = in[pos];
  skip(pos,in);
  match(':',pos,in);
  match('=',pos,in);
  skip(pos,in);
  match('{',pos,in);

  vector<pair<unsigned int, unsigned int> > edgelist;
  unsigned int V = 0;
    
  bool firstTime=true;

  while(pos < in.length() && in[pos] != '}') {
    if(!firstTime) { match(',',pos,in); }
    firstTime=false;
    // just keep on reading!
    unsigned int tail = parse_number(pos,in);
    match('-',pos,in); match('-',pos,in);
    unsigned int head = parse_number(pos,in);
    V = max(V,max(head,tail));
    edgelist.push_back(std::make_pair(tail,head));
  }  

  match('}',pos,in);

  if(V == 0) { return G(0); }

  G r(V+1);

  for(vector<pair<unsigned int, unsigned int> >::iterator i(edgelist.begin());
      i!=edgelist.end();++i) {
    r.add_edge(i->first,i->second);
  }

  return r; 
}

template<class P>
P read_polynomial(string in) {
  unsigned int pos = 0;
  P poly;

  match('T',pos,in);
  match('P',pos,in);
  match('[',pos,in);
  unsigned int id = parse_number(pos,in);
  match(']',pos,in);
  skip(pos,in);
  match(':',pos,in);
  match('=',pos,in);
  skip(pos,in);

  while(pos < in.length() && in[pos] != ':') {
    biguint coeff = parse_bignumber(pos,in);
    unsigned int xpow = 0;
    unsigned int ypow = 0;
    match('*',pos,in);
    if(in[pos] == 'x') {
      match('x',pos,in);
      if(in[pos] == '^') {
	match('^',pos,in);
	xpow = parse_number(pos,in);
      } else {
	xpow = 1;
      }
    } 
    if(in[pos] == '*') {
      match('*',pos,in);
    }
    if(in[pos] == 'y') {
      match('y',pos,in);
      if(in[pos] == '^') {
	match('^',pos,in);
	ypow = parse_number(pos,in);
      } else {
	ypow = 1;
      }
    }    

    P term(xy_term(xpow,ypow));
    term *= coeff;
    poly += term;
    while(pos < in.length() && (in[pos] == ' ' || in[pos] == '+')) {
      pos++;
    }
  }

  return poly;
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

/* This method just compacts the vertex space used by the graph so
 * that it is numbered contiguously from 0.  This is done by
 * eliminating any vertices which have no edges.
 */
template<class G>
G compact_graph(G const &graph) {
  vector<unsigned int> labels(graph.num_vertices(),0);
  int counter = 0;

  for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    if(graph.num_edges(*i) > 0) {
      labels[*i] = counter++;
    }
  }
 
  // now, create new permuted graph
  G r(counter);
  
  for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) {
    for(typename G::edge_iterator j(graph.begin_edges(*i));
	j!=graph.end_edges(*i);++j) {	      
      unsigned int head(*i);
      unsigned int tail(j->first);
      unsigned int count(j->second);
      if(head <= tail) {
	r.add_edge(labels[head],labels[tail],count);
      }
    }
  }
  
  return r;  
}

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

pair<int,int> parse_evalpoint(char *str) {
  char *endp=NULL;
  int a = strtol(str,&endp,10);
  int b = strtol(endp+1,&endp,10);
  return make_pair(a,b);
}

uint64_t parse_amount(char *str) {
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

void write_bucket_lengths(ostream &out) {
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

void write_graph_sizes(ostream &out) {
  out << endl << endl;
  out << "#########################" << endl;
  out << "# CACHE GRAPH SIZE DATA #" << endl;
  out << "#########################" << endl;
  out << "# V\t#Graphs (%)\t#MultiGraphs (%)" << endl;
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

void write_hit_counts(ostream &out) {
  out << endl << endl;
  out << "##############################" << endl;
  out << "# CACHE GRAPH HIT COUNT DATA #" << endl;
  out << "##############################" << endl;
  out << "# V\tHit Count" << endl;

  for(int i=0;i!=cache_hit_sizes.size();++i) {
    out << i << "\t" << cache_hit_sizes[i] << endl;
  }  
}

// ---------------------------------------------------------------
// Signal Handlers
// ---------------------------------------------------------------

/*
 * Note, the signal handler causes problems when used in conjunction
 * with Sun's Grid Engine.  Therefore, it's recommended to use "-q"
 * for quiet mode to avoid this.
 */
static int status_interval = 5; // in seconds

void timer_handler(int signum) {
  if(verbose) { status_flag=true; }
  alarm(status_interval);
}

void print_status() {
  status_flag=false;
  double rate = (num_steps - old_num_steps);
  double cf = (100*((double)cache.size())) / cache.capacity();
  rate /= status_interval;
  cerr << "Completed " << ngraphs_completed << " graphs at rate of " << ((int) rate) << "/s, cache is " << setprecision(3) << cf << "% full." << endl;
  old_num_steps = num_steps;  
}

// ---------------------------------------------------------------
// Run Method
// ---------------------------------------------------------------

string search_replace(string from, string to, string text) {
  int pos = 0;
  while((pos = text.find(from,pos)) != string::npos) {
    text.replace(pos,from.length(),to.c_str(),to.length());
    pos -= from.length();
    pos += to.length();
  }
  return text;
}

template<class G, class P>
void run(ifstream &input, unsigned int graphs_beg, unsigned int graphs_end, vorder_t vertex_ordering, boolean info_mode, boolean reset_mode) {
  // if auto heuristic is enabled, then we calculate graph density and
  // select best heuristc based on that.
  unsigned int index = 0;
  unsigned int lineno = 0;
  ngraphs_completed = 0;
  bool auto_heuristic = edge_selection_heuristic == AUTO;
  bool cache_auto_replace_size = cache.replace_size() == UINT_MAX;

  while(!input.eof() && index < graphs_end) {
    string line = read_line(input);
    lineno++;

    if(line == "") {
      break;
    }

    if(line[0] =='G') {
      // this is an initialisation graph
      G init_graph = compact_graph<G>(read_init_graph<G>(line));
      P poly = read_polynomial<P>(read_line(input));
      P p2;
      unsigned char *key = graph_key(init_graph); 
      unsigned int id = 0;
      if(!cache.lookup(key,p2,id)) {
	cache.store(key,poly,id);
      }
      delete [] key;  // free space used by key
      continue;
    } 

    index = index + 1;

    if(index < graphs_beg) {
      // don't compute the polynomial for this graph.
      continue;
    } 

    // Create graph and then permute it according to 
    // vertex ordering strategy
    G start_graph = compact_graph<G>(read_graph<G>(line));
    G perm_graph = permute_graph<G>(start_graph,vertex_ordering);
    // now reset all stats information
    if(reset_mode) { cache.clear(); }
    cache.reset_stats();
    cache_hit_sizes.clear();
    num_steps = 0;
    old_num_steps = 0;
    num_bicomps = 0;
    num_disbicomps = 0;
    num_trees = 0;
    num_cycles = 0;
    unsigned int V(start_graph.num_vertices());
    unsigned int E(start_graph.num_edges());
    unsigned int EP(start_graph.num_underlying_edges());
    unsigned int C(start_graph.num_components());    
    cache_hit_sizes.resize(V+1,0);

    // now determine edge density for auto_heuristic_mode
    if(auto_heuristic) {
      double density = (2.0 * ((double) E)) / (((double) V) * ((double) V-1));
      if(density < 0.5) {
	edge_selection_heuristic = MINIMISE_SDEGREE;
	edge_addition_heuristic = MINIMISE_SDEGREE;
      } else {
	edge_selection_heuristic = VERTEX_ORDER;
	edge_addition_heuristic = VERTEX_ORDER;
      }							      
    }

    global_timer = my_timer(false);
    if(write_tree) { write_tree_start(ngraphs_completed); }    

    // now set the cache replacment size
    if(cache_auto_replace_size) {
      unsigned int size = (unsigned int) (((float)V)*0.75);
      cache.set_replace_size(size);
    }

    P tuttePoly;

    if(mode == MODE_CHROMATIC) {
      tuttePoly = chromatic<G,P>(perm_graph,1);        
    } else if(mode == MODE_FLOW) {
      tuttePoly = flow<G,P>(perm_graph,1);        
    } else if(mode == MODE_TUTTE) {
      tuttePoly = tutte<G,P>(perm_graph,1);        
    } else if(mode == MODE_TUTTEX) {
      tuttePoly = tuttex<G,P>(perm_graph);        
    } else { // MODE_TUTTE_SPLIT
      vector<G> graphs;
      tutteSearch<G,P>(perm_graph,graphs);        
      for(typename vector<G>::const_iterator i(graphs.begin());i!=graphs.end();++i) {      	
	cout << input_graph_str(*i) << endl;
      }
      continue;
    } 

    if(write_tree) { write_tree_end(ngraphs_completed); }

    if(!verbose) {
      for(vector<pair<int,int> >::iterator i(evalpoints.begin());i!=evalpoints.end();++i) {
	cout << tuttePoly.substitute(i->first,i->second) << "\t";
      }
      cout << endl;
	
      if(info_mode) {
	cout << V << "\t" << E << "\t" << EP;    
	cout << "\t" << setprecision(3) << global_timer.elapsed() << "\t" << num_steps << "\t" << num_bicomps << "\t" << num_disbicomps << "\t" << num_cycles << "\t" << num_trees;
	if(mode == MODE_TUTTE) {
	  cout << "\t" << tuttePoly.substitute(1,1) << "\t" << tuttePoly.substitute(2,2);
	}
      } 
    } else {
      string TP = "TP";
      if(global_timer.elapsed() >= timeout) {
	// catch timeout case to avoid confusion.
	cerr << "Timeout!!" << endl;
      } else if(mode == MODE_TUTTE) {	
	cout << "G[" << (ngraphs_completed+1) << "] := {" << input_graph_str(start_graph) << "}" << endl;
	cout << "TP[" << (ngraphs_completed+1) << "] := " << tuttePoly.str() << " :" << endl;
      } else if(mode == MODE_FLOW) {
	cout << "FP[" << (ngraphs_completed+1) << "] := " << pow(bigint(INT32_C(-1)),(E-V)+C) << " * ( ";
	cout << search_replace("y","(1-x)",tuttePoly.str()) << " ) :" << endl;
	TP = "FP";
      } else if(mode == MODE_CHROMATIC) {
  	cout << "CP[" << (ngraphs_completed+1) << "] := " << pow(bigint(INT32_C(-1)),V-C) << " * x * ( ";
	cout << search_replace("x","(1-x)",tuttePoly.str()) << " ) :" << endl;
	TP = "CP";
      }

      for(vector<pair<int,int> >::iterator i(evalpoints.begin());i!=evalpoints.end();++i) {
	cout << TP << "[" << (ngraphs_completed+1) << "](" << i->first << "," << i->second << ") = " << tuttePoly.substitute(i->first,i->second) << endl;
      }

      if(info_mode) {
	cout << "=======" << endl;
	cout << "V = " << V << ", E = " << E << endl;
	cout << "Size of Computation Tree: " << num_steps << " graphs." << endl;	
	cout << "Number of Biconnected Components Extracted: " << num_bicomps << "." << endl;	
	cout << "Number of Biconnected Components Separated: " << num_disbicomps << "." << endl;	
	cout << "Number of Cycles Terminated: " << num_cycles << "." << endl;	
	cout << "Number of Trees Terminated: " << num_trees << "." << endl;	
	cout << "Number of Completed Graphs Terminated: " << num_completed << "." << endl;	
	cout << "Time : " << setprecision(3) << global_timer.elapsed() << "s" << endl;

	if(mode == MODE_TUTTE) {
	  // only print these evaluation points when in tutte mode
	  cout << "T(1,1) = " << tuttePoly.substitute(1,1) << endl;
	  cout << "T(2,2) = " << tuttePoly.substitute(2,2) << " (should be " << pow(biguint(UINT32_C(2)),E) << ")" << endl;	
	  // The tutte at T(-1,-1) should always give a (positive or
	  // negative) power of 2. 
	  bigint Tm1m1 = tuttePoly.substitute(-1,-1);
	  bigint Tm1m1pow = INT32_C(0);

	  while((Tm1m1 % INT32_C(2)) == INT32_C(0)) {
	    Tm1m1 = Tm1m1 / INT32_C(2);
	    Tm1m1pow = Tm1m1pow + INT32_C(1);
	  }
	  if(Tm1m1 == INT32_C(-1)) {
	    cout << "T(-1,-1) = -2^" << Tm1m1pow << endl;
	  } else if(Tm1m1 == INT32_C(1)) {
	    cout << "T(-1,-1) = 2^" << Tm1m1pow << endl;
	  } else {
	    // getting here indicates an error in the computation
	    cout << "T(-1,-1) = 2^" << Tm1m1pow << " * " << Tm1m1 << endl;
	  }
	}
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
  #define OPT_VERSION 4
  #define OPT_SMALLGRAPHS 5
  #define OPT_NGRAPHS 6
  #define OPT_GRAPHS 19
  #define OPT_TIMEOUT 7
  #define OPT_EVALPOINT 8
  #define OPT_SPLIT 9
  #define OPT_CACHESIZE 10
  #define OPT_CACHEBUCKETS 11  
  #define OPT_CACHEREPLACEMENT 12
  #define OPT_CACHERANDOM 13
  #define OPT_CACHESTATS 14
  #define OPT_NOCACHE 15
  #define OPT_CACHERESET 16
  #define OPT_CACHEREPLACESIZE 17
  #define OPT_GMP 20
  #define OPT_CHROMATIC 21
  #define OPT_FLOW 22
  #define OPT_TUTTEX 23
  #define OPT_SIMPLE_POLY 30
  #define OPT_FACTOR_POLY 31
  #define OPT_XML_OUT 32
  #define OPT_TREE_OUT 33
  #define OPT_FULLTREE_OUT 34
  #define OPT_WITHLINES 43
  #define OPT_NOMULTICYCLES 44
  #define OPT_NOMULTIEDGES 45
  #define OPT_MAXSDEGREE 49
  #define OPT_MAXDEGREE 50
  #define OPT_MAXMDEGREE 51
  #define OPT_MINDEGREE 52
  #define OPT_MINMDEGREE 53
  #define OPT_MINSDEGREE 54
  #define OPT_VERTEXORDER 55
  #define OPT_RANDOM 56
  #define OPT_CUT 57
  #define OPT_RANDOM_ORDERING 60
  #define OPT_MINDEG_ORDERING 61
  #define OPT_MAXDEG_ORDERING 62
  #define OPT_MINUDEG_ORDERING 63
  #define OPT_MAXUDEG_ORDERING 64
  #define OPT_USEADDCONTRACT 70
  
  struct option long_options[]={
    {"help",no_argument,NULL,OPT_HELP},
    {"version",no_argument,NULL,OPT_VERSION},
    {"info",no_argument,NULL,OPT_INFO},
    {"quiet",no_argument,NULL,OPT_QUIET},
    {"timeout",required_argument,NULL,OPT_TIMEOUT},
    {"split",required_argument,NULL,OPT_SPLIT},
    {"eval",required_argument,NULL,OPT_EVALPOINT},
    {"chromatic",no_argument,NULL,OPT_CHROMATIC},
    {"flow",no_argument,NULL,OPT_FLOW},
    {"tuttex",no_argument,NULL,OPT_TUTTEX},
    {"cache-size",required_argument,NULL,OPT_CACHESIZE},
    {"cache-buckets",required_argument,NULL,OPT_CACHEBUCKETS},
    {"cache-replacement",required_argument,NULL,OPT_CACHEREPLACEMENT},
    {"cache-random",no_argument,NULL,OPT_CACHERANDOM}, 
    {"cache-stats",optional_argument,NULL,OPT_CACHESTATS},   
    {"cache-reset",no_argument,NULL,OPT_CACHERESET},
    {"cache-replace-size",required_argument,NULL,OPT_CACHEREPLACESIZE},
    {"no-caching",no_argument,NULL,OPT_NOCACHE},
    {"minimise-degree", no_argument,NULL,OPT_MINDEGREE},
    {"minimise-mdegree", no_argument,NULL,OPT_MINMDEGREE},
    {"sparse", no_argument,NULL,OPT_MINSDEGREE},
    {"dense", no_argument,NULL,OPT_VERTEXORDER},
    {"maximise-degree", no_argument,NULL,OPT_MAXDEGREE},
    {"maximise-mdegree", no_argument,NULL,OPT_MAXMDEGREE},
    {"maximise-sdegree", no_argument,NULL,OPT_MAXSDEGREE},
    {"random-ordering",no_argument,NULL,OPT_RANDOM_ORDERING},
    {"mindeg-ordering",no_argument,NULL,OPT_MINDEG_ORDERING},
    {"maxdeg-ordering",no_argument,NULL,OPT_MAXDEG_ORDERING},
    {"minudeg-ordering",no_argument,NULL,OPT_MINUDEG_ORDERING},
    {"maxudeg-ordering",no_argument,NULL,OPT_MAXUDEG_ORDERING},
    {"random", no_argument,NULL,OPT_RANDOM},
    {"cut", no_argument,NULL,OPT_CUT},
    {"small-graphs",required_argument,NULL,OPT_SMALLGRAPHS},
    {"simple-poly",no_argument,NULL,OPT_SIMPLE_POLY},
    {"tree",no_argument,NULL,OPT_TREE_OUT},
    {"full-tree",no_argument,NULL,OPT_FULLTREE_OUT},
    {"xml-tree",no_argument,NULL,OPT_XML_OUT},
    {"ngraphs",required_argument,NULL,OPT_NGRAPHS},
    {"graphs",required_argument,NULL,OPT_GRAPHS},
    {"no-multicycles",no_argument,NULL,OPT_NOMULTICYCLES},
    {"no-multiedges",no_argument,NULL,OPT_NOMULTIEDGES},
    {"add-contract",no_argument,NULL,OPT_USEADDCONTRACT},
    NULL
  };
  
  char const *descriptions[]={
    "        --help                    display this information",
    "        --version                 display the version number of this program",
    " -i     --info                    output summary information regarding computation",
    " -q     --quiet                   output info summary as single line only (useful for generating data)",
    " -t     --timeout=<x>             timeout after x seconds",
    " -s<x>  --split=<x>               split the input graph(s) into a number of smaller graphs with no more than x vertices",
    " -Tx,y  --eval=x,y                evaluate the computed polynomial at x,y",
    "        --small-graphs=size       set threshold for small graphs.  Default is 5.",
    " -n<x>  --ngraphs=<number>        number of graphs to process from input file",
    " -g<x:y>  --graphs=<start:end>    which graphs to process from input file, e.g. 2:10 processes the 2nd to tenth inclusive",
    "        --chromatic               generate chromatic polynomial",
    "        --flow                    generate flow polynomial",
    "        --tuttex                  experimental tutte computation",
    "        --tree                    output computation tree",
    "        --full-tree               output full computation tree",
    "        --xml-tree                output computation tree as XML",
    " \ncache options:",
    " -c<x>  --cache-size=<amount>     set sizeof cache to allocate, e.g. 700M",
    "        --cache-buckets=<amount>  set number of buckets to use in cache, e.g. 10000",
    "        --cache-random            set random replacement policy",
    "        --cache-replacement=<amount> set ratio (between 0 .. 1) of cache to displace when full",
    "        --cache-replace-size=<number> graphs of the given number of vertices will never be displaced from cache",
    "        --cache-stats[=<file>]    print cache stats summary, or write detailed stats to file.",
    "        --cache-reset             reset the cache between graphs in a batch",
    "        --no-caching              disable caching",
    " \nedge selection heuristics:",
    "        --sparse                  use best heuristic for \"sparse\" graphs.",
    "        --dense                   use best heuristic for \"dense\" graphs.",
    "        --random                  use random heuristic",
    " \nother options:",
    "        --no-multiedges           do not reduce multiedges in one go",
    "        --no-multicycles          do not reduce multicycles in one go",
    "        --add-contract            perform add/contract (currently only for chromatic)",
    NULL
  };

  unsigned int v;
  uint64_t cache_size(256 * 1024 * 1024); 
  unsigned int cache_buckets(1000000);     // default 1M buckets
  unsigned int poly_rep(OPT_FACTOR_POLY);
  unsigned int graphs_beg(0); 
  unsigned int graphs_end(UINT_MAX); // default is to do every graph in input file
  bool info_mode=false;
  bool reset_mode=false;
  bool cache_stats=false;
  vorder_t vertex_ordering(V_MAXIMISE_UNDERLYING_DEGREE);
  string cache_stats_file("");

  while((v=getopt_long(argc,argv,"qic:n:t:T:",long_options,NULL)) != -1) {
    switch(v) {      
    case OPT_HELP:
      cout << "usage: " << argv[0] << " [options] <input graph file>" << endl;
      cout << "options:" << endl;
      for(char const **ptr=descriptions;*ptr != NULL; ptr++) {
	cout << *ptr << endl;
      }    
      exit(1);          
    case OPT_VERSION:      
      cout << "Tutte version "  << VERSION << endl;
      cout << "Developed by David J. Pearce, Gary Haggard and Gordon Royle, 2008" << endl;
      exit(0);
      break;
    case 'q':
    case OPT_QUIET:      
      verbose=false;
      break;
    case 't':
    case OPT_TIMEOUT:
      timeout = atoi(optarg);
      break;
    case 's':
    case OPT_SPLIT:
      split_threshold = atoi(optarg);
      mode = MODE_TUTTE_SPLIT;
      break;
    case OPT_TUTTEX:
      mode = MODE_TUTTEX;
      break;
    case 'T':
    case OPT_EVALPOINT:
      evalpoints.push_back(parse_evalpoint(optarg));
      break;
    case 'n':
    case OPT_NGRAPHS:
      graphs_beg = 0;
      graphs_end = atoi(optarg);
      break;
    case 'g':
    case OPT_GRAPHS:
      {
	string s(optarg);
	unsigned int pos = 0;
	graphs_beg = parse_number(pos,s);
	match(':',pos,s);
	graphs_end = parse_number(pos,s);
	break;
      }
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
    case OPT_CHROMATIC:
      mode=MODE_CHROMATIC;
      break;
    case OPT_FLOW:
      mode=MODE_FLOW;
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
    case OPT_CACHEREPLACESIZE:
      cache.set_replace_size(atoi(optarg));
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
    case OPT_CACHERESET:
      reset_mode = true;
      break;
    // --- POLY OPTIONS ---
    case OPT_SIMPLE_POLY:
      poly_rep = OPT_SIMPLE_POLY;
      break;
    // --- HEURISTICS ---
    case OPT_MINDEGREE:
      edge_selection_heuristic = MINIMISE_DEGREE;
      edge_addition_heuristic = MINIMISE_DEGREE;
      break;
    case OPT_MAXDEGREE:
      edge_selection_heuristic = MAXIMISE_DEGREE;
      edge_addition_heuristic = MAXIMISE_DEGREE;
      break;
    case OPT_MAXMDEGREE:
      edge_selection_heuristic = MAXIMISE_MDEGREE;
      edge_addition_heuristic = MAXIMISE_MDEGREE;
      break;
    case OPT_MINMDEGREE:
      edge_selection_heuristic = MINIMISE_MDEGREE;
      edge_addition_heuristic = MINIMISE_MDEGREE;
      break;
    case OPT_MINSDEGREE:
      edge_selection_heuristic = MINIMISE_SDEGREE;
      edge_addition_heuristic = MINIMISE_SDEGREE;
      break;
    case OPT_MAXSDEGREE:
      edge_selection_heuristic = MAXIMISE_SDEGREE;
      edge_addition_heuristic = MAXIMISE_SDEGREE;
      break;
    case OPT_VERTEXORDER:
      edge_selection_heuristic = VERTEX_ORDER;
      edge_addition_heuristic = VERTEX_ORDER;
      break;
    case OPT_RANDOM:
      edge_selection_heuristic = RANDOM;
      edge_addition_heuristic = RANDOM;
      break;
    case OPT_CUT:
      edge_selection_heuristic = CUT;
      edge_addition_heuristic = CUT;
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
    case OPT_NOMULTICYCLES:
      reduce_multicycles=false;
      break;
    case OPT_NOMULTIEDGES:
      reduce_multiedges=false;
      break;
    case OPT_USEADDCONTRACT:
      use_add_contract=true;
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
    for(char const **ptr=descriptions;*ptr != NULL; ptr++) {
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
    
    if(verbose) {
      // Only use the timer handler in verbose mode.
      struct sigaction sa;
      memset(&sa,0,sizeof(sa));
      sa.sa_handler = &timer_handler;
      if(sigaction(SIGALRM,&sa,NULL)) { perror("sigvtalarm"); }
      alarm(status_interval); // trigger alarm in status_interval seconds
    }
    
    // -----------------------------------
    // Now, begin solving the input graph!
    // -----------------------------------
    
    srand(time(NULL));
        
    ifstream input(argv[optind]);    
    if(poly_rep == OPT_FACTOR_POLY) {
      run<spanning_graph<adjacency_list<> >,factor_poly<biguint> >(input,graphs_beg,graphs_end,vertex_ordering,info_mode,reset_mode);
    } else {
      //      run<spanning_graph<adjacency_list<> >,simple_poly<> >(input,ngraphs,vertex_ordering);
    }    

    if(cache_stats) {
      cout << endl << "###############" << "# CACHE STATS #" << endl << "###############" << endl;
      cout << "Size: " << (cache_size/(1024*1024)) << "MB" << endl;
      cout << "Density: " << (cache.density()*1024*1024) << " graphs/MB" << endl;
      cout << "# Entries: " << cache.num_entries() << endl;
      cout << "# Cache Hits: " << cache.num_hits() << endl;
      cout << "# Cache Misses: " << cache.num_misses() << endl;
      cout << "# Cache Collisions: " << cache.num_collisions() << endl;
      cout << "Min Bucket Length: " << cache.min_bucket_size() << endl;
      cout << "Max Bucket Length: " << cache.max_bucket_size() << endl;
      write_hit_counts(cout);
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






                                            
