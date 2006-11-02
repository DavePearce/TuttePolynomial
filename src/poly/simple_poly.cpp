#include "simple_poly.hpp"

using namespace std;

const simple_poly operator+(simple_poly const &p1, simple_poly const &p2) {
  // this will not work in the general case!
  simple_poly r(p1);
  
  for(map<int,int>::const_iterator i(p2.xs.begin());i!=p2.xs.end();++i) {      
    map<int,int>::iterator j = r.xs.find(i->first);
    if(j != r.xs.end()) {
      r.xs.insert(std::make_pair(i->first,i->second + j->second));
    } else {
      r.xs.insert(std::make_pair(i->first,i->second));
    }
  }
  
  for(map<int,int>::const_iterator i(p2.ys.begin());i!=p2.ys.end();++i) {      
    map<int,int>::iterator j = r.ys.find(i->first);
    if(j != r.ys.end()) {
      r.ys.insert(std::make_pair(i->first,i->second + j->second));
    } else {
      r.ys.insert(std::make_pair(i->first,i->second));
    }
  }
  return r;
}
