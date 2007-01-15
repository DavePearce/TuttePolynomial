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

Poly deleteContract(Graph &g) { 

  num_steps++;

  // if the graph is a "loop tree", then we're done.
  if(g.is_looptree()) {
    //    cout << "=== END BRANCH ===" << endl;
    return Poly(g.num_edges()-g.num_loops(),g.num_loops());
  } else {
    term ys(0,g.num_loops());   

    // First, remove any loops and pendant vertices (i.e. vertices of degree one).

    while(g.num_loops() > 0) {
      int l = g.select_loop_edge();
      g.remove_edge(l,l);
    }

    // This could be made more efficient
    // There's a BUG as well when removing a pendant vertex creates another!    

    int num_pendants(0);
    for(Graph::vertex_iterator i(g.begin_verts());i!=g.end_verts();) {
      int j=*(i++);
      if(g.num_edges(j) == 1) { g.remove(j); num_pendants++; }
    }
    
    term xs(num_pendants,0);    

    // Second, check if we've seen this graph before.  
    //
    // Note, the following conversion is not cheap.  It would help to
    // eliminate it whenever possible.  One approach might be, for
    // example, to arrange the graphs such that we can tell no match
    // exists simply by looking at the number of vertices and edges.
    // This could include min, max edge degree?

    unsigned char *key = graph_key(g);
  
    Poly p;
    if(cache.lookup(key,p)) { return p * ys * xs; }

    // Third, perform delete contract 
    pair<int,int> e = g.select_nontree_edge();

    Graph g1(g);  
    g1.remove_edge(e.first,e.second);        
    Graph g2(g1); 
    g2.contract_edge(e.first,e.second); 

    // Fourth, recursively compute the polynomial
    Poly r;
    r = deleteContract(g1) + deleteContract(g2); // perform the recursion

    // Finally, save computed polynomial 
    cache.store(key,r);
    delete [] key;  // free space used by key

    return r * ys * xs;
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
  #define OPT_CACHESIZE 10
  #define OPT_CACHEBUCKETS 11  
  #define OPT_NAUTYWORKSPACE 20

  struct option long_options[]={
    {"help",no_argument,NULL,OPT_HELP},
    {"cache-size",required_argument,NULL,OPT_CACHESIZE},
    {"cache-buckets",required_argument,NULL,OPT_CACHEBUCKETS},
    {"nauty-workspace",required_argument,NULL,OPT_NAUTYWORKSPACE},
    NULL
  };
  
  char *descriptions[]={
    "        --help                    display this information",
    " -c     --cache-size=<amount>     set sizeof cache to allocate, e.g. 700M",
    "        --cache-buckets=<amount>  set number of buckets to use in cache, e.g. 10000",
    "        --nauty-workspace=<amount> set size of nauty workspace, e.g. 10000",
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

    Poly tuttePoly = deleteContract(start_graph);        

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
    cout << "# Buckets of size 0..0: " << cache.count_buckets_sized(0,0) << " (" << (((double)cache.count_buckets_sized(0,0)*100) / cache.num_buckets()) << "%)" << endl;
    cout << "# Buckets of size 1..2: " << cache.count_buckets_sized(1,2) << " (" << (((double)cache.count_buckets_sized(1,2)*100) / cache.num_buckets()) << "%)" << endl;
    cout << "# Buckets of size 3..5: " << cache.count_buckets_sized(3,5) << " (" << (((double)cache.count_buckets_sized(3,5)*100) / cache.num_buckets()) << "%)" << endl;
    cout << "# Buckets of size 6..10: " << cache.count_buckets_sized(6,10) << " (" << (((double)cache.count_buckets_sized(6,10)*100) / cache.num_buckets()) << "%)" << endl;
    cout << "# Buckets of size 11..100: " << cache.count_buckets_sized(11,100) << " (" << (((double)cache.count_buckets_sized(11,100)*100) / cache.num_buckets()) << "%)" << endl;
    cout << "# Buckets of size 101..1000: " << cache.count_buckets_sized(101,1000) << " (" << (((double)cache.count_buckets_sized(101,1000)*100) / cache.num_buckets()) << "%)" << endl;
    // printPoly(tuttePolynomial);
  } catch(bad_alloc const &e) {
    cout << "error: insufficient memory!" << endl;
  } catch(exception const &e) {
    cout << "error: " << e.what() << endl;
  }
}






                                            
