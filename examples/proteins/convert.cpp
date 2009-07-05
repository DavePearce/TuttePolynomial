#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

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

void skip(unsigned int &pos, string const &in) {
  while(pos < in.length() && (in[pos] == ' ' || in[pos]=='\t')) {
    pos++;
  } 
}

int main(char* argv[], int argc) {
  
  vector<pair<unsigned int, unsigned int> > edges;

  unsigned int from = 0;
  while(!cin.eof()) {
    std::string line = read_line(cin);
    
    if(line == "") {
      continue;
    }

    unsigned int pos = 0;
    unsigned int to = 0;
    while(pos < line.size()) {
      unsigned int e = parse_number(pos,line);

      if(e == 1 && to >= from) {
	edges.push_back(make_pair(from,to));
      }

      skip(pos,line);
      
      to = to + 1;
    }
    
    from = from + 1;
  }

  for(unsigned int i=0;i!=edges.size();++i) {
    if(i != 0) {
      cout << ", ";
    }
    cout << edges[i].first << "--" << edges[i].second;
  }
  cout << endl;
}
