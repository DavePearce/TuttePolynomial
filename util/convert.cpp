#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

int parse_number(unsigned int &pos, string const &str) {
  int s = pos;
  while(pos < str.length() && isdigit(str[pos])) {
    pos = pos + 1;
  }
  istringstream ss(str.substr(s,pos));
  int r;
  ss >> r;
  return r;
}

void match(char c, unsigned int &pos, string const &str) {
  if(pos >= str.length() || str[pos] != c) { throw runtime_error(string("syntax error -- expected '") + c + "', got '" + str[pos] + "'"); }
  ++pos;
}

vector<pair<unsigned int, unsigned int> > read_graph(std::istream &input) {
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
    match(',',pos,in); 
    unsigned int head = parse_number(pos,in);
    V = max(V,max(head,tail));
    edgelist.push_back(std::make_pair(tail,head));
  }  

  return edgelist;
}

int main(int argc, char *argv[]) {
  bool first_time=true;
  while(!cin.eof()) {
    if(!first_time) { cout << endl; }
    first_time=false;
    vector<pair<unsigned int, unsigned int> > g = read_graph(cin);
    bool firstTime=true;
    for(vector<pair<unsigned int, unsigned int> >::iterator i(g.begin());i!=g.end();++i) {
      if(i->first == 0 && i->second == 0) { break; }
      if(!firstTime) { cout << ","; }
      firstTime=false;
      cout << (i->first-1) << "--" << (i->second-1);
    }
  }
}
