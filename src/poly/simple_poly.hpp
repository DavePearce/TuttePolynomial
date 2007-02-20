#ifndef SIMPLE_POLY_HPP
#define SIMPLE_POLY_HPP

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

class term {
public:
  unsigned short xpower;
  unsigned short ypower;

  term(unsigned short x, unsigned short y) : xpower(x), ypower(y) {}

  bool operator<(term const &t) const {
    return (xpower < t.xpower) || (xpower == t.xpower && ypower < t.ypower);
  }

  bool operator==(term const &t) const {
    return (xpower == t.xpower && t.ypower == t.ypower);
  }

  std::string str() const {
    std::stringstream ss;
    if(xpower > 1) { ss << "x^" << xpower; }
    else if(xpower == 1) { ss << "x"; }
    if(ypower > 1) { ss << "y^" << ypower; }
    else if(ypower == 1) { ss << "y"; }
    return ss.str();
  }

  double substitute(double x, double y) const {
    return pow(x,(double)xpower) * pow(y,(double)ypower);
  }
};

class simple_poly {
public:
  friend const simple_poly operator+(simple_poly const&, simple_poly const&);
  friend const simple_poly operator*(simple_poly const&, term const&);
  
  typedef std::map<term,unsigned int>::iterator iterator;
  typedef std::map<term,unsigned int>::const_iterator const_iterator;
private:
  std::map<term,unsigned int> terms;
public:
  simple_poly() {}

  simple_poly(unsigned int x, unsigned int y) {
    if(x > 0 || y > 0) { terms.insert(std::make_pair(term(x,y),1)); }
  }

  simple_poly(unsigned int n, unsigned int x, unsigned int y) {
    if(x > 0 || y > 0) { terms.insert(std::make_pair(term(x,y),n)); }
  }

  simple_poly(simple_poly const &t) {
    terms = t.terms;
  }

  simple_poly const &operator=(simple_poly const &src) {
    if(&src != this) { 
      terms = src.terms;
    }
    return *this;
  }


  void insert(unsigned int n, term const &t) {
    terms.insert(std::make_pair(t,n)); 
  }


  size_t size() const { return terms.size(); }

  iterator begin() { return terms.begin(); }
  iterator end() { return terms.end(); }

  const_iterator begin() const { return terms.begin(); }
  const_iterator end() const { return terms.end(); }

  bool operator==(simple_poly const &g) const {
    return terms == g.terms;
  }

  bool operator!=(simple_poly const &g) const {
    return terms != g.terms;
  }

  const std::string str() const {
    std::stringstream ss;
    // start with xs
    bool firstTime=true;
    for(std::map<term,unsigned int>::const_iterator i(terms.begin());i!=terms.end();++i) {      
      if(!firstTime) { ss << " + "; }
      firstTime=false;
      term const &t(i->first);
      int count = i->second;
      if(count > 1) { ss << count; }
      ss << i->first.str();
    }
    
    return ss.str(); 
  }

  double substitute(double x, double y) const {
    double val=0;
    for(std::map<term,unsigned int>::const_iterator i(terms.begin());i!=terms.end();++i) {   
      val += i->first.substitute(x,y) * i->second;
    }
    return val;
  }
};

// useful methods

const simple_poly operator+(simple_poly const &p1, simple_poly const &p2);
const simple_poly operator*(simple_poly const &p1, term const &p2);

#endif
