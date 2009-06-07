#ifndef TUTTE_IO_HPP
#define TUTTE_IO_HPP

#include <iostream>
#include <algorithm>
#include <string>

#include "graphs.hpp"

std::string read_line(std::istream &in);
int parse_number(unsigned int &pos, std::string const &str);
void match(char c, unsigned int &pos, std::string const &str);
void skip(unsigned int &pos, std::string const &in);

template<class G>
G read_graph(std::string in) {
  std::vector<std::pair<unsigned int, unsigned int> > edgelist;
  unsigned int V = 0, pos = 0;
    
  bool firstTime=true;

  while(pos < in.length()) {
    if(!firstTime) { match(',',pos,in); }
    firstTime=false;
    // just keep on reading!
    unsigned int tail = parse_number(pos,in);
    match('-',pos,in); match('-',pos,in);
    unsigned int head = parse_number(pos,in);
    V = std::max(V,std::max(head,tail));
    edgelist.push_back(std::make_pair(tail,head));
  }  

  if(V == 0) { return G(0); }

  G r(V+1);

  for(std::vector<std::pair<unsigned int, unsigned int> >::iterator i(edgelist.begin());
      i!=edgelist.end();++i) {
    r.add_edge(i->first,i->second);
  }

  return r;
}

template<class G>
std::pair<int,G> read_indexed_graph(std::string in) {
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

  std::vector<std::pair<unsigned int, unsigned int> > edgelist;
  unsigned int V = 0;
    
  bool firstTime=true;

  while(pos < in.length() && in[pos] != '}') {
    if(!firstTime) { match(',',pos,in); }
    firstTime=false;
    // just keep on reading!
    unsigned int tail = parse_number(pos,in);
    match('-',pos,in); match('-',pos,in);
    unsigned int head = parse_number(pos,in);
    V = std::max(V,std::max(head,tail));
    edgelist.push_back(std::make_pair(tail,head));
  }  

  match('}',pos,in);

  G r(V+1);

  for(std::vector<std::pair<unsigned int, unsigned int> >::iterator i(edgelist.begin());
      i!=edgelist.end();++i) {
    r.add_edge(i->first,i->second);
  }

  return std::pair<int,G>(id,r);
}

template<class G>
std::vector<G> read_file(std::istream &input) {
  std::vector<G> graphs;
  while(!input.eof()) {
    std::string line = read_line(input);
    
    if(line == "") {
      continue;
    }

    if(line[0] =='G') {
      // this is an initialisation graph
      std::pair<int,G> p = read_indexed_graph<G>(line);
      graphs.resize(p.first+1);
      graphs[p.first] = p.second;
    } else {
      graphs.push_back(read_graph<G>(line));
    }
  }

  return graphs;
}

#endif
