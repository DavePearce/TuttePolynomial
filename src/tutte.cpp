#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include <stdexcept>
#include <algorithm>
#include <csignal>
#include <getopt.h>
#include <sys/time.h>

#include "config.h"
#include "eval_simple_fours.hpp" // auto-generated solutions for simple graphs of size 4
#include "eval_simple_fives.hpp" // auto-generated solutions for simple graphs of size 5
#include "cache/simple_cache.hpp"

using namespace std;

// ---------------------------------------------------------------
// User-Defined Types
// ---------------------------------------------------------------

class my_timer {
private:
  struct timeval _start;
public:
  my_timer(void) {
    gettimeofday(&_start,NULL);
  }

  double elapsed(void) {
    struct timeval tmp;
    gettimeofday(&tmp,NULL); 
    double end = tmp.tv_sec + (tmp.tv_usec / 1000000.0);
    double start = _start.tv_sec + (_start.tv_usec / 1000000.0);    
    return end - start;
  }  
};

// ---------------------------------------------------------------
// Global Variables
// ---------------------------------------------------------------

unsigned long num_steps = 0;
unsigned long old_num_steps = 0;
unsigned int small_graph_threshold = 5;
simple_cache<Poly> cache(1024,100);

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

Poly deleteContract(Graph &g, bool cache_enable) { 

  num_steps++;

  // first, eliminate any loops
  unsigned int num_loops = g.remove_loops(); 

  // if the graph is a "loop tree", then we're done.
  if(g.is_tree()) {
    //    cout << "=== END BRANCH ===" << endl;
    return Poly(g.num_edges(),num_loops);
  } else {
    term ys(0,num_loops);  

    // Now, remove any pendant vertices (i.e. vertices of degree one).

    int num_pendants(0);

    while(g.num_pendant_vertices() > 0) {
      int l = g.select_pendant_vertex();
      g.remove(l);
      num_pendants++;
    }

    term xs(num_pendants,0);    

    // Second, break down multi-edges

    // Second, attempt to evaluate small graphs directly.  For big graphs,
    // look them up in the cache.

    unsigned char *key = NULL;
    if(g.num_vertices() < small_graph_threshold) {
      // if this is a small 
      /*
      if(!g.is_multi_graph()) { 
	switch(g.num_vertices()) {
	case 4:
	  return evaluate_simple_fours<Graph,Poly>(g) * ys * xs; 
	case 5:
	  return evaluate_simple_fives<Graph,Poly>(g) * ys * xs; 
	default:
	  break;
	}
      }
      */
    } else {
      key = graph_key(g);      
      Poly p;
      if(cache.lookup(key,p)) { return p * ys * xs; }          
    }

    // third, perform delete contract 
    Graph::edge_t e = g.select_nontree_edge();

    Graph g1(g);  
    g1.remove_edge(e.first,e.second);        
    Graph g2(g1); 
    g2.contract_edge(e.first,e.second); 

    // Fourth, recursively compute the polynomial
    Poly r = deleteContract(g1,false) + deleteContract(g2,true);     

    // Finally, save computed polynomial
    if(key != NULL) {
      cache.store(key,r);
      delete [] key;  // free space used by key
    }
    
    return r * xs * ys;
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
  for(simple_cache<Poly>::iterator i(cache.begin());i!=cache.end();++i) {
    Graph g(graph_from_key<Graph>(i.key()));
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


// ---------------------------------------------------------------
// Signal Handlers
// ---------------------------------------------------------------

static int status_interval = 5; // in seconds

void timer_handler(int signum) {
  double rate = (num_steps - old_num_steps);
  double cf = (100*((double)cache.size())) / cache.capacity();
  rate /= status_interval;
  cout << "Completed " << num_steps << " graphs at rate of " << ((int) rate) << "/s, cache is " << setprecision(3) << cf << "% full." << endl;
  old_num_steps = num_steps;
  alarm(status_interval);
}

// ---------------------------------------------------------------
// Main Method
// ---------------------------------------------------------------

int main(int argc, char *argv[]) {

  // ------------------------------
  // Process command-line arguments
  // ------------------------------

  #define OPT_HELP 0
  #define OPT_SMALLGRAPHS 5
  #define OPT_CACHESIZE 10
  #define OPT_CACHEBUCKETS 11  
  #define OPT_NAUTYWORKSPACE 20

  struct option long_options[]={
    {"help",no_argument,NULL,OPT_HELP},
    {"cache-size",required_argument,NULL,OPT_CACHESIZE},
    {"cache-buckets",required_argument,NULL,OPT_CACHEBUCKETS},
    {"nauty-workspace",required_argument,NULL,OPT_NAUTYWORKSPACE},
    {"small-graphs",required_argument,NULL,OPT_SMALLGRAPHS},
    NULL
  };
  
  char *descriptions[]={
    "        --help                    display this information",
    " -c     --cache-size=<amount>     set sizeof cache to allocate, e.g. 700M",
    "        --cache-buckets=<amount>  set number of buckets to use in cache, e.g. 10000",
    "        --nauty-workspace=<amount> set size of nauty workspace, e.g. 10000",
    "        --small-graphs=size        set threshold for small graphs, e.g. 7",
    NULL
  };

  unsigned int v;
  unsigned int cache_size(50*1024*1024); // detault 50M
  unsigned int cache_buckets(10000);     // default 10,000 buckets

  while((v=getopt_long(argc,argv,"c:",long_options,NULL)) != -1) {
    switch(v) {      
    case OPT_HELP:
      cout << "usage: " << argv[0] << " [options] <input graph file>" << endl;
      cout << "options:" << endl;
      for(char **ptr=descriptions;*ptr != NULL; ptr++) {
	cout << *ptr << endl;
      }    
      exit(1);
          
    // --- CACHE OPTIONS ---
    case 'c':
    case OPT_CACHESIZE:
      cache_size = parse_amount(optarg);
      break;
    case OPT_CACHEBUCKETS:
      cache_buckets = parse_amount(optarg);
      break;
    case OPT_NAUTYWORKSPACE:
      resize_nauty_workspace(parse_amount(optarg));
      break;
    case OPT_SMALLGRAPHS:
      small_graph_threshold = parse_amount(optarg);      
      break;
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

  Graph start_graph(0);
  try {
    ifstream input(argv[optind]);
    start_graph = read_graph(input);

    cout << "VERTICES = " << start_graph.num_vertices() << ", EDGES = " << start_graph.num_edges() << endl << endl;
    
    print_graph(cout,start_graph);    

    my_timer timer;

    Poly tuttePoly = deleteContract(start_graph,false);        

    cout << "Tutte Polynomial: " << tuttePoly.str() << endl << endl;

    cout << "Number of spanning trees: " << (long long) tuttePoly.substitute(1,1) << endl;

    cout << "==================" << endl;
    cout << "Total Steps: " << num_steps << endl;
    cout << "Time : " << setprecision(3) << timer.elapsed() << "s" << endl;
    cout << endl;
    cout << "Cache stats:" << endl << "------------" << endl;
    cout << "Density: " << (cache.density()*1024*1024) << " graphs/MB" << endl;
    cout << "# Entries: " << cache.num_entries() << endl;
    cout << "# Cache Hits: " << cache.num_hits() << endl;
    cout << "# Cache Misses: " << cache.num_misses() << endl;
    cout << "# Cache Collisions: " << cache.num_collisions() << endl;
    cout << "Min Bucket Length: " << cache.min_bucket_size() << endl;
    cout << "Max Bucket Length: " << cache.max_bucket_size() << endl;

    // now, write out stats
    
    fstream stats_out("tutte-stats.dat",fstream::out);
    //    write_bucket_lengths(stats_out);
    // write_graph_sizes(stats_out);
    // printPoly(tuttePolynomial);
  } catch(bad_alloc const &e) {
    cout << "error: insufficient memory!" << endl;
  } catch(exception const &e) {
    cout << "error: " << e.what() << endl;
  }
}






                                            
