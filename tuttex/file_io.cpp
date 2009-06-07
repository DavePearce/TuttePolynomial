#include <sstream>
#include <stdexcept>
#include "file_io.hpp"

using namespace std;

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

void match(char c, unsigned int &pos, string const &str) {
  if(pos >= str.length() || str[pos] != c) { throw runtime_error(string("syntax error -- expected '") + c + "', got '" + str[pos] + "'"); }
  ++pos;
}

void skip(unsigned int &pos, string const &in) {
  while(pos < in.length() && (in[pos] == ' ' || in[pos]=='\t')) {
    pos++;
  } 
}
