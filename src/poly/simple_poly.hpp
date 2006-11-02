#ifndef SIMPLE_POLY_HPP
#define SIMPLE_POLY_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <map>

class simple_poly {
  friend const simple_poly operator+(simple_poly const&, simple_poly const&);
private:
  std::map<int,int> xs;  
  std::map<int,int> ys;
public:
  simple_poly() {}

  simple_poly(int x, int y) {
    if(x > 0) { xs.insert(std::make_pair(x,1)); }
    if(y > 0) { ys.insert(std::make_pair(y,1)); }
  }

  const std::string str() const {
    std::stringstream ss;
    // start with xs
    bool firstTime=true;
    for(std::map<int,int>::const_iterator i(xs.begin());i!=xs.end();++i) {      
      if(!firstTime) { ss << " + "; }
      firstTime=false;
      if(i->second > 2) {
	ss <<  i->second << "x^" << i->first;
      } else {
	ss <<  "x^" << i->first;
      }
    }
    for(std::map<int,int>::const_iterator i(ys.begin());i!=ys.end();++i) {      
      if(!firstTime) { ss << " + "; }
      firstTime=false;
      if(i->second > 2) {
	ss <<  i->second << "y^" << i->first;
      } else {
	ss <<  "y^" << i->first;
      }
    }
    return ss.str();
  }
};

// useful methods

const simple_poly operator+(simple_poly const &p1, simple_poly const &p2);

#endif
