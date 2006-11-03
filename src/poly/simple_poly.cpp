#include "simple_poly.hpp"

using namespace std;

const simple_poly operator+(simple_poly const &p1, simple_poly const &p2) {
  // this will not work in the general case!
  simple_poly r(p1);
  
  for(map<term,int>::const_iterator i(p2.terms.begin());i!=p2.terms.end();++i) {      
    map<term,int>::iterator j = r.terms.find(i->first);
    if(j != r.terms.end()) {
      j->second += i->second;
    } else {
      r.terms.insert(std::make_pair(i->first,i->second));
    }
  }

  return r;
}
