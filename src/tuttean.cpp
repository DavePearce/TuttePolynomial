// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <set>
#include <vector>
#include <getopt.h>
#include "misc/triple.hpp"

using namespace std;

typedef enum { TREE, MATCH, NONTREE } node_t;
typedef vector<triple<unsigned int, unsigned int, unsigned int> > graph_t;

class node {
public:  
  node_t type;
  unsigned int match_id;  
  unsigned int con_id;
  unsigned int del_id;
  graph_t graph;
};

// ---------------------------------------------------------------
// Simple Input File Parser
// ---------------------------------------------------------------

void match(char c, unsigned int &pos, string const &str) {
  if(pos >= str.length() || str[pos] != c) { throw runtime_error(string("syntax error -- expected '") + c + "', got '" + str[pos] + "'"); }
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

graph_t parse_graph(unsigned int &pos, string const &str) {
  match('{',pos,str);
  bool first=true;
  graph_t graph;

  while(pos < str.length()) {
    if(str[pos] == '}') { return graph; }
    if(!first) { match(',',pos,str); }
    first=false;

    unsigned int h,t,c=1;
    h = parse_number(pos,str);
    match('-',pos,str);
    t = parse_number(pos,str);
    if(str[pos] == '(') {
      match('(',pos,str);
      c = parse_number(pos,str);
      match(')',pos,str);
    }
    
    graph.push_back(make_triple(h,t,c));
  }
  
  throw runtime_error(string("syntax error"));
}

vector<node> read_input(istream &input) {
  vector<node> data;
  
  while(!input.eof()) {
    string line;
    input >> line;
    unsigned int pos(0);
    if(isdigit(line[0])) {
      unsigned int id = parse_number(pos,line);
      if(data.size() <= id) { data.resize(id+1); }
      if(line[pos] == '=') {
	match('=',pos,line);
	if(isdigit(line[pos])) {
	  // this is a match node
	  unsigned int match_id = parse_number(pos,line);
	  data[id].type = MATCH;
	  data[id].match_id = match_id;
	} else {
	  data[id].graph = parse_graph(pos,line);	  
	}
      } else if(line[pos] == '-') {
	match('-',pos,line);
	match('e',pos,line);
	match('=',pos,line);
	unsigned int del_id = parse_number(pos,line);
	data[id].type = NONTREE;
	data[id].del_id = del_id;      
      } else if(line[pos] == '/') {
	match('/',pos,line);
	match('e',pos,line);
	match('=',pos,line);
	unsigned int con_id = parse_number(pos,line);
	data[id].type = NONTREE;
	data[id].con_id = con_id;
      } else {
	throw runtime_error(string("syntax error on '") + line[pos] + "'");
      }
    } else {
      return data;
    }
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

double mean(vector<unsigned int> const &data) {
  unsigned long sum(0);
  for(vector<unsigned int>::const_iterator i(data.begin());
      i!=data.end();++i) {
    sum += *i;
  }
  return ((double)sum) / data.size();
}

// ---------------------------------------------------------------
// Analysis Methods
// ---------------------------------------------------------------

vector<unsigned int> match_v_sizes(vector<node> const &data) {
  vector<unsigned int> sizes;
  // now, perform some simple analysis
  for(unsigned int i=0;i!=data.size();++i) {
    if(data[i].type == MATCH) {
      graph_t const &g(data[data[i].match_id].graph);
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
      graph_t const &g(data[data[i].match_id].graph);
      sizes.push_back(num_edges(g));
    }
  }      
  return sizes;
}

// ---------------------------------------------------------------
// Format Conversion Methods
// ---------------------------------------------------------------

void write_dot(vector<node> const &data, ostream &out) {
  out << "digraph {" << endl;
  for(unsigned int i=0;i!=data.size();++i) {
    if(data[i].type == NONTREE) {
      out << i << " -> " << data[i].del_id << endl;
      out << i << " -> " << data[i].con_id << endl;
    } else if(data[i].type == MATCH) {
      out << i << " -> " << data[i].match_id << endl;
    }
  }
  out << "}" << endl;  
}

// ---------------------------------------------------------------
// Main Method
// ---------------------------------------------------------------

#define OPT_HELP 0
#define OPT_DOT 1

struct option long_options[]={
  {"help",no_argument,NULL,OPT_HELP},
  {"dot",no_argument,NULL,OPT_DOT},
  NULL
};

int main(int argc, char* argv[]) {
  char *descriptions[]={
    "        --help                    display this information",
    " -d     --dot                     convert input tree to dot format",
    NULL
  };

  unsigned int v;

  while((v=getopt_long(argc,argv,"d",long_options,NULL)) != -1) {
    switch(v) {      
    case OPT_HELP:
      cout << "usage: " << argv[0] << " [options] <input tree file>" << endl;
      cout << "options:" << endl;
      for(char **ptr=descriptions;*ptr != NULL; ptr++) {
	cout << *ptr << endl;
      }    
      exit(1);
    case 'd':
    case OPT_DOT:
      vector<node> data=read_input(cin);
      write_dot(data,cout);
      exit(1);
    }
  }

  try {
    vector<node> data=read_input(cin);
    cout << "Average match |V|: " << mean(match_v_sizes(data)) << endl;
    cout << "Average match |E|: " << mean(match_e_sizes(data)) << endl;
  } catch(bad_alloc const &e) {
    cout << "error: insufficient memory!" << endl;
  } catch(exception const &e) {
    cout << "error: " << e.what() << endl;
  }

}
