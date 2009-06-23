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

#include "../config.h"
#include "file_io.hpp"
#include "adjacency_list.hpp"
#include "nauty_graph.hpp"
#include "computation.hpp"

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

typedef adjacency_list<> graph_t;
typedef pair<unsigned int, unsigned int> edge_t;

// ---------------------------------------------------------------
// Global Variables
// ---------------------------------------------------------------

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
static vector<pair<int,int> > evalpoints;
static unsigned int ngraphs_completed=0;  
static unsigned int cutoff_threshold=0;
static bool quiet_flag=false;
static bool status_flag=false;
static bool verbose_flag=false;

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
  if(verbose_flag) { status_flag=true; }
  alarm(status_interval);
}

void print_status() {
  /*
  status_flag=false;
  double rate = (num_steps - old_num_steps);
  double cf = (100*((double)cache.size())) / cache.capacity();
  rate /= status_interval;
  cerr << "Completed " << ngraphs_completed << " graphs at rate of " << ((int) rate) << "/s, cache is " << setprecision(3) << cf << "% full." << endl;
  old_num_steps = num_steps;  
  */
}

// ------------------------------------------------------------------
// Edge Selection
// ------------------------------------------------------------------

edge_t select_edge(unsigned char const *nauty_graph) {
  unsigned int N = nauty_graph_numverts(nauty_graph);

  for(unsigned int i=0;i!=N;++i) {
    for(unsigned int j=0;j!=N;++j) {
      if(nauty_graph_is_edge(nauty_graph,i,j)) {
	return edge_t(i,j);
      }
    }
  }
  
  throw std::runtime_error("internal failure (select_edge)");
}

// ------------------------------------------------------------------
// Tutte Polynomial
// ------------------------------------------------------------------

void tutte(computation &comp) { 
  
  while(comp.frontier_size() != 0) {
    cout << "GRAPHS: " << comp.frontier_size() << endl;
    for(unsigned int i=0;i!=comp.frontier_size();) {
      unsigned int gindex = comp.frontier_get(i);
      unsigned char *nauty_graph = comp.graph_ptr(gindex);

      if(nauty_graph_numedges(nauty_graph) == 0) {
	comp.frontier_terminate(i);
      } else {
	edge_t edge = select_edge(nauty_graph);
	i += comp.frontier_delcontract(i,edge.first,edge.second);
      }
    }
  }  
}

// ---------------------------------------------------------------
// Run Method
// ---------------------------------------------------------------

void reset_stats(unsigned int V) {
  /*
  cache_hit_sizes.resize(V,0);
  cache.reset_stats();
  cache_hit_sizes.clear();
  num_steps = 0;
  old_num_steps = 0;
  num_bicomps = 0;
  num_disbicomps = 0;
  num_trees = 0;
  num_cycles = 0;    
  */
}

void run(vector<graph_t> const &graphs, unsigned int beg, unsigned int end, uint64_t cache_size, unsigned int cache_buckets) {
  computation comp(cache_size,cache_buckets);

  for(unsigned int i(beg);i<end;++i) {
    comp.clear();
    comp.initialise(graphs[i]);
    reset_stats(graphs[i].num_vertices());
    global_timer = my_timer(false);
    tutte(comp);
  }
}

// ---------------------------------------------------------------
// Misc Helpers Functions
// ---------------------------------------------------------------

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
// Main Method
// ---------------------------------------------------------------

int main(int argc, char *argv[]) {
  
  // ------------------------------
  // Process command-line arguments
  // ------------------------------
  
#define OPT_HELP 0
#define OPT_QUIET 1  
#define OPT_VERBOSE 2  
#define OPT_INFO 3
#define OPT_VERSION 4
#define OPT_SMALLGRAPHS 5
#define OPT_GRAPHS 6
#define OPT_TIMEOUT 7
#define OPT_EVALPOINT 8
#define OPT_CUTOFF 9
#define OPT_CACHESIZE 10
#define OPT_CACHEBUCKETS 11  

  struct option long_options[]={
    {"help",no_argument,NULL,OPT_HELP},
    {"version",no_argument,NULL,OPT_VERSION},
    {"info",no_argument,NULL,OPT_INFO},
    {"quiet",no_argument,NULL,OPT_QUIET},
    {"verbose",no_argument,NULL,OPT_VERBOSE},
    {"cutoff",required_argument,NULL,OPT_CUTOFF},
    {"cache-size",required_argument,NULL,OPT_CACHESIZE},
    {"cache-buckets",required_argument,NULL,OPT_CACHEBUCKETS},
    NULL
  };
  
  char const *descriptions[]={
    "        --help                    display this information",
    "        --version                 display the version number of this program",
    " -i     --info                    output summary information regarding computation",
    " -q     --quiet                   output info summary as single line only (useful for generating data)",
    " -v     --verbose                 display lots of information useful for debugging.",
    " -s<x>  --cutoff=<x>              stop the computation at graphs with fewer than x vertices",
    " -g<x:y>  --graphs=<start:end>    which graphs to process from input file, e.g. 2:10 processes the 2nd to tenth inclusive",
    " \ncache options:",
    " -c<x>  --cache-size=<amount>     set sizeof cache to allocate, e.g. 700M",
    "        --cache-buckets=<amount>  set number of buckets to use in cache, e.g. 10000",
  };

  uint64_t cache_size(256 * 1024 * 1024);   
  unsigned int cache_buckets = 100000;
  unsigned int beg = 0;
  unsigned int end = UINT_MAX-1;
  unsigned int v;
  bool info_mode = false;

  while((v=getopt_long(argc,argv,"qic:g:s:",long_options,NULL)) != -1) {
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
      quiet_flag = true;
      break;
    case 't':
    case OPT_TIMEOUT:
      timeout = atoi(optarg);
      break;
    case 's':
    case OPT_CUTOFF:
      cutoff_threshold = atoi(optarg);
      break;    
    case 'g':
    case OPT_GRAPHS:
      {
	string s(optarg);
	unsigned int pos = 0;
	beg = parse_number(pos,s);
	match(':',pos,s);
	end = parse_number(pos,s);
	break;
      }
    case 'i':
    case OPT_INFO:
      info_mode=true;
      break;    
    // --- CACHE OPTIONS ---
    case 'c':
    case OPT_CACHESIZE:
      cache_size = parse_amount(optarg);
      break;
    case OPT_CACHEBUCKETS:
      cache_buckets = parse_amount(optarg);
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
    // -------------------------------------------------
    // Register alarm signal for printing status updates
    // -------------------------------------------------
    
    if(!quiet_flag) {
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

    ifstream inputfile(argv[optind]);    
    vector<graph_t> graphs = read_file<graph_t>(inputfile);

    run(graphs,beg,std::min(graphs.size(),end+1),cache_size,cache_buckets);

    cout << "Read " << graphs.size() << " graph(s)." << endl;
  } catch(std::runtime_error &e) {
    cerr << "error: " << e.what() << endl;  
  } catch(std::bad_alloc &e) {
    cerr << "error: insufficient memory!" << endl;
  } catch(std::exception &e) {
    cerr << "error: " << e.what() << endl;
  }
}
