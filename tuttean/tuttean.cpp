// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <set>
#include <vector>
#include <stack>
#include <getopt.h>
#include <cmath>
#include "misc/triple.hpp"

using namespace std;

typedef enum { UNUSED, LEAF, MATCH, NONLEAF } node_t;
typedef vector<triple<unsigned int, unsigned int, unsigned int> > graph_t;

class node {
public:  
  node_t type;
  vector<int> subids;
  graph_t graph;
};

string str(int i) {
  stringstream ss;
  ss << i;
  return ss.str();
}

// ---------------------------------------------------------------
// Simple Input File Parser
// ---------------------------------------------------------------

void match(char c, unsigned int &pos, string const &s, int line_no) {
  if(pos >= s.length() || s[pos] != c) { throw runtime_error(string("syntax error -- expected '") + c + "', got '" + s[pos] + "' at col " + str(pos) + ", line " + str(line_no)); }
  ++pos;
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

graph_t parse_graph(unsigned int &pos, string const &str, int line_no) {
  match('{',pos,str,line_no);
  bool first=true;
  graph_t graph;  

  while(pos < str.length()) {
    if(str[pos] == '}') { return graph; }
    if(!first) { match(',',pos,str,line_no); }
    first=false;

    unsigned int h,t,c=1;
    h = parse_number(pos,str);
    match('-',pos,str,line_no);
    t = parse_number(pos,str);
    if(str[pos] == '(') {
      match('(',pos,str,line_no);
      c = parse_number(pos,str);
      match(')',pos,str,line_no);
    }
    
    graph.push_back(make_triple(h,t,c));
  }
  
  throw runtime_error(string("syntax error"));
}

vector<node> read_input(istream &input) {
  vector<node> data;
  node empty;
  empty.type = UNUSED;
  int line_no=1;

  while(!input.eof()) {
    string line;
    input >> line;
    unsigned int pos(0);
    if(isdigit(line[0])) {
      unsigned int id = parse_number(pos,line);
      if(data.size() <= id) { data.resize(id+1,empty); }
      match('=',pos,line,line_no);
      if(isdigit(line[pos])) {
	// parse subgraphs      
	vector<int> sgs;
	sgs.push_back(parse_number(pos,line));
	while(line[pos] == '+') {	
	  sgs.push_back(parse_number(++pos,line));
	}
	if(sgs.size() == 1 && sgs[0] < id) {
	  data[id].type = MATCH;
	  data[id].subids = sgs;
	} else {
	  // non-leaf tree
	  data[id].type = NONLEAF;
	  data[id].subids = sgs;
	  // now parse solution if there is one
	  if(line[pos] == '=') {
	    pos++;
	    data[id].graph = parse_graph(pos,line,line_no);	  
	  }
	}
      } else {
	data[id].type = LEAF;
	data[id].graph = parse_graph(pos,line,line_no);	  
      }
    } else {
      return data;
    }  
    line_no++;
  }

  return data;
}

// ---------------------------------------------------------------
// Misc helper Methods
// ---------------------------------------------------------------

unsigned int num_vertices(graph_t const &g) {
  std::set<unsigned int> V;
  for(graph_t::const_iterator i(g.begin());i!=g.end();++i) {
    V.insert(i->first);
    V.insert(i->second);
  }
  return V.size();
}

unsigned int num_edges(graph_t const &g) {
  unsigned int e(0);
  for(graph_t::const_iterator i(g.begin());i!=g.end();++i) {
    e += i->third;
  }
  return e;
}

unsigned int degree(int v, graph_t const &g) {
  unsigned int e(0);
  for(graph_t::const_iterator i(g.begin());i!=g.end();++i) {
    if(i->first == v || i->second == v) {
      e += i->third;
    }
  }
  return e;
}

bool is_multigraph(graph_t const &g) {
  for(graph_t::const_iterator i(g.begin());i!=g.end();++i) {
    if(i->third > 1) { return true; }
  }
  return false;
}

double mean(vector<unsigned int> const &data) {
  unsigned long sum(0);
  for(vector<unsigned int>::const_iterator i(data.begin());
      i!=data.end();++i) {
    sum += *i;
  }
  return ((double)sum) / data.size();
}

double sdev(vector<unsigned int> const &data) {
  double x(mean(data));
  double S(0);

  for(vector<unsigned int>::const_iterator i(data.begin());
      i!=data.end();++i) {
    S += (*i - x) * (*i - x);
  }

  S = sqrt(S/data.size());
  return S;
}

// ---------------------------------------------------------------
// Analysis Methods
// ---------------------------------------------------------------

vector<unsigned int> match_v_sizes(vector<node> const &data) {
  vector<unsigned int> sizes;
  // now, perform some simple analysis
  for(unsigned int i=0;i!=data.size();++i) {
    if(data[i].type == MATCH) {
      graph_t const &g(data[i].graph);
      sizes.push_back(num_vertices(g));
    }
  }      
  return sizes;
}

vector<unsigned int> match_e_sizes(vector<node> const &data) {
  vector<unsigned int> sizes;
  // now, perform some simple analysis
  for(unsigned int i=0;i!=data.size();++i) {
    if(data[i].type == MATCH) {
      graph_t const &g(data[i].graph);
      sizes.push_back(num_edges(g));
    }
  }      
  return sizes;
}

unsigned int count(node_t type, vector<node> const &data) {
  unsigned int c(0);
  for(unsigned int i=0;i!=data.size();++i) {
    if(data[i].type == type) { c++; }
  }
  return c;
}

/*
unsigned int count_identical_matches(vector<node> const &data) {
  unsigned int c(0);
  for(unsigned int i=0;i!=data.size();++i) {
    if(data[i].type == MATCH && data[i].graph == data[data[i].match_id].graph) {
      c++; 
    }
  }
  return c;
}
*/


// ---------------------------------------------------------------
// Format Conversion Methods
// ---------------------------------------------------------------

void write_dot(int minv, vector<node> const &data, ostream &out) {
  out << "digraph {" << endl;
  for(unsigned int i=1;i!=data.size();++i) {
    if(data[i].type != MATCH && num_vertices(data[i].graph) >= minv) {
      double size = 1 + num_vertices(data[i].graph);
      size /= 10;    
      out << "\t" << i << " [fontsize=9,width=" << size << ",height=" << size;
      if(is_multigraph(data[i].graph)) {
	out << ",style=filled";
      }
      out << "]" << endl;
    }
  }
  
  for(unsigned int i=0;i!=data.size();++i) {
    if(data[i].type == NONLEAF) {
      for(unsigned int j=0;j!=data[i].subids.size();++j) {
	unsigned int sid = data[i].subids[j];
	if(data[sid].type == MATCH) {
	  sid = data[sid].subids[0];
	}
	if(num_vertices(data[sid].graph) >= minv) {
	  // draw arcs
	  out << "\t" << i << " -> " << sid << endl;
	}
      }
    } 
  }
  out << "}" << endl;  
}

pair<unsigned int, unsigned int> domain(graph_t const &graph) {
  unsigned int b=999999999;
  unsigned int t=0;
  for(unsigned int i=0;i!=graph.size();++i) {
    t = max(t,max(graph[i].first,graph[i].second));
    b = min(b,min(graph[i].first,graph[i].second));    
  }
  return make_pair(b,t);
}

graph_t edges(unsigned int v, graph_t const &graph) {
  graph_t edges;
  for(unsigned int i=0;i!=graph.size();++i) {
    if(graph[i].first == v || graph[i].second == v) {
      edges.push_back(graph[i]);
    }
  }
  return edges;
}

graph_t bfs_layout_graph(graph_t const &graph, unsigned int *limit) {
  // perform a breadth-first search to compute a spanning tree.
  // then, can layout all other edges as we want.


  std::deque<unsigned int> S;
  pair<unsigned int, unsigned int> dom = domain(graph);
  std::vector<bool> visited(dom.second+1,false);

  // one of the most important things is how we choose the first node.
  // I could certainly do more here, but this is a start.
  unsigned int max(0);
  unsigned int start(dom.first);
  for(unsigned int i=dom.first;i!=dom.second;++i) {
    unsigned int es = edges(i,graph).size();
    if(es > max) { start = i; max = es; }
  }

  S.push_back(start);
  visited[start]=true;

  graph_t spanning_tree;

  while(!S.empty()) {
    unsigned int v(S.front());
    S.pop_front();
    graph_t es = edges(v,graph);

    for(unsigned int j=0;j!=es.size();++j) {
      unsigned int w = es[j].first;
      if(w == v) { w = es[j].second; }

      if(!visited[w]) { 
	visited[w] = true;
	S.push_back(w);
	spanning_tree.push_back(es[j]);
      } 
    }
  }
  *limit = spanning_tree.size();
  // ok, this is all rather inefficient ...
  for(unsigned int j=0;j!=graph.size();++j) {
    if(find(spanning_tree.begin(),spanning_tree.end(),graph[j]) == spanning_tree.end()) {
      spanning_tree.push_back(graph[j]);
    }
  }
  return spanning_tree;
}

typedef enum { NONE, BFS } layout_t;

graph_t layout_graph(graph_t const &graph, unsigned int *limit, layout_t mode) {
  if(mode == BFS) { return bfs_layout_graph(graph,limit); }
  else {
    *limit=graph.size();
    return graph;
  }
}

// This method attempts to draw *all* the little graphs
// as well.  It really will only work on small computation 
// trees.

void write_full_dot(int minv, bool labels, vector<node> const &data, layout_t small_mode, ostream &out) {
  out << "graph {" << endl;
  out << "\tcompound=true;" << endl;
  if(labels) {
    out << "\tnodesep=0.5;" << endl;
  } else {
    out << "\tnodesep=0.1;" << endl;
  }
  out << "\tranksep=0.05;" << endl;

  // first, we create the subgraph nodes
  
  vector<int> first(data.size(),-1);
  vector<int> last(data.size(),0);
  unsigned int vindex=0;
  for(unsigned int i=1;i<data.size();++i) {
    if(data[i].type != MATCH && data[i].type != UNUSED && num_vertices(data[i].graph) >= minv) {
      out << "\tsubgraph cluster" << i << " {" << endl;
      if(labels) {
	out << "\t\t" << "label=\"" << i << "\"" << endl;
	out << "\t\t" << "color=white;" << endl;
      } else {
	out << "\t\tstyle=invis" << endl;
      }
      graph_t const &graph(data[i].graph);
      if(labels) {        
	out << "\t\tnode [width=0.05,height=0.05]" << endl;	
	for(int j=vindex;j!=(vindex+domain(graph).second+1);++j) {
	  if(degree(j-vindex,graph) > 0) {
	    out << "\t\t" << j << " [label=\"" << (j-vindex) << "\"]" << endl;
	  }
	}
      } else {
	out << "\t\tnode [label=\"\",width=0.05,height=0.05]" << endl;
      }
      unsigned int l = 0;
      unsigned int f = 100000;
      unsigned int climit;
      graph_t lgraph(layout_graph(graph,&climit,small_mode));
      for(unsigned int j=0;j!=lgraph.size();++j) {	
	out << "\t\t" << (vindex+lgraph[j].first) << "--" << (vindex+lgraph[j].second);
	vector<string> styles;
	// make multi-edges appear in bold
	if(lgraph[j].third > 1) { styles.push_back("style=bold"); }
        // only constrain edges in spanning tree
	if(j >= climit) { styles.push_back("constraint=false"); }
	// now, output styles (if there are any)
	if(styles.size() > 0) {
	  out << " [";
	  for(unsigned int k=0;k!=styles.size();++k) {
	    if(k!=0) { out << ","; }
	    out << styles[k];
	  }
	  out << "]";
	}
	out << ";" << endl;
	l = max(l,max(lgraph[j].first,lgraph[j].second));
	f = min(f,min(lgraph[j].first,lgraph[j].second));
      }
      last[i] = vindex+l;
      if(lgraph.size() > 0) {
	first[i] = vindex+f;
      }
      vindex += l+1;
      out << "\t}" << endl;
    }
  }
  
  // second, we create the edges between subgraphs
  for(unsigned int i=1;i!=data.size();++i) {
    if(data[i].type == NONLEAF) {
      for(unsigned int j=0;j!=data[i].subids.size();++j) {
	unsigned int sid = data[i].subids[j];
	if(data[sid].type == MATCH) {
	  sid = data[sid].subids[0];
	}
	if(num_vertices(data[sid].graph) >= minv) {
	  if(first[sid] != -1) {
	    out << "\t" << last[i] << " -- " << first[sid] << " [minlen=5,ltail=cluster" << i << ",lhead=cluster" << sid << ",arrowhead=normal" << "];" << endl;
	  } 
	}
      }
    }
  }

  out << "}" << endl;  
}

// ---------------------------------------------------------------
// Main Method
// ---------------------------------------------------------------

#define OPT_HELP 0
#define OPT_DOT 1
#define OPT_STATS 2
#define OPT_FULL 10
#define OPT_BFS 20
#define OPT_MINV 30
#define OPT_LABELS 40

struct option long_options[]={
  {"help",no_argument,NULL,OPT_HELP},
  {"dot",no_argument,NULL,OPT_DOT},
  {"stats",no_argument,NULL,OPT_STATS},
  {"full",no_argument,NULL,OPT_FULL},
  {"bfs",no_argument,NULL,OPT_BFS},
  {"labels",no_argument,NULL,OPT_LABELS},
  {"minv",required_argument,NULL,OPT_MINV},
  NULL
};

int main(int argc, char* argv[]) {
  char *descriptions[]={
    "        --help                    display this information",
    " -d     --dot                     convert input tree to dot format",
    " -f     --full                    convert (full) input tree",
    " -s     --stats                   show various stats on tree",
    "        --bfs                     use bfs algorithm for small graph layout",
    " -mX    --minv=X                  ignore graphs where |V| < X",
    " -l     --labels                  show labels on vertices",
    NULL
  };

  unsigned int v;
  unsigned int minv=0;

  unsigned int mode = OPT_HELP;
  unsigned int layout_mode = OPT_HELP;
  bool full_mode=false;
  bool labels = false;

  while((v=getopt_long(argc,argv,"sfdm:l",long_options,NULL)) != -1) {
    switch(v) {      
    case OPT_HELP:
      mode = OPT_HELP;
      break;
    case 'd':
    case OPT_DOT:
      mode = OPT_DOT;
      break;
    case 's':
    case OPT_STATS:
      mode = OPT_STATS;
      break;
    case 'f':
    case OPT_FULL:
      full_mode=true;
      break;
    case OPT_BFS:
      layout_mode=OPT_BFS;
      break;
    case 'l':
    case OPT_LABELS:
      labels=true;
      break;
    case 'm':
    case OPT_MINV:
      minv = atoi(optarg);
      break;
    }
  }
  
  try {
    switch(mode) {
    case OPT_HELP:
      cout << "usage: " << argv[0] << " [options] <input tree file>" << endl;
      cout << "options:" << endl;
      for(char **ptr=descriptions;*ptr != NULL; ptr++) {
	cout << *ptr << endl;
      }    
      exit(1);    
    case OPT_DOT:
      {
	vector<node> data=read_input(cin);
	if(full_mode) {
	  if(layout_mode == OPT_BFS) {
	    write_full_dot(minv,labels,data,BFS,cout);
	  } else {
	    write_full_dot(minv,labels,data,NONE,cout);
	  }
	} else {
	  write_dot(minv,data,cout);
	}
	exit(1);
      }
    case OPT_STATS:
      {
	vector<node> data=read_input(cin);
	unsigned int size(count(NONLEAF,data) + count(LEAF,data));      
	unsigned int V = num_vertices(data[1].graph);
	unsigned int E = num_edges(data[1].graph);
	double msize(pow(2.0,(double) E-V+1));	
	double compaction = (((double) size) / msize) * 100;
	cout << "Tree has " << setprecision(2) << size << " nodes, out of a (rough) maximum of " << msize << " (" << compaction << "%)" <<endl;
	vector<unsigned int> match_vs(match_v_sizes(data));
	vector<unsigned int> match_es(match_e_sizes(data));
	cout << "Average match had " << mean(match_vs) << " vertices (+/-" << sdev(match_vs) << ")";
	cout << ", and " << mean(match_es) << " edges (+/-" << sdev(match_es) << ")." << endl;
	unsigned int nmatches(count(MATCH,data));
	//	unsigned int nisomatches(count_identical_matches(data));
	//	double isoratio = round((((double) nisomatches) / nmatches) * 100);
	//	cout << "There were " << nmatches << " matches, of which " << nisomatches << " (" << isoratio << "%) were identical." << endl;    
      }
    }
  } catch(bad_alloc const &e) {
    cout << "error: insufficient memory!" << endl;
  } catch(exception const &e) {
    cout << "error: " << e.what() << endl;
  }      
}
