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

template<class MAP = std::map<term,unsigned int> >
class simple_poly {
public:
  typedef typename MAP::iterator iterator;
  typedef typename MAP::const_iterator const_iterator;
private:
  MAP terms;
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

  void operator+=(simple_poly const &p1) {    
    for(const_iterator i(p1.terms.begin());i!=p1.terms.end();++i) {      
      iterator j = terms.find(i->first);
      if(j != terms.end()) {
	j->second += i->second;
      } else {
	terms.insert(std::make_pair(i->first,i->second));
      }
    }
  }

  // this is gary's shift operation
  void operator*=(term const &p2) {
    // I don't think the STL strictly would allow this,
    // but it doesn't hurt!
    for(const_iterator i(terms.begin());i!=terms.end();++i) {      
      term &t((term &)i->first); // ouch ;)
      t.xpower += p2.xpower;
      t.ypower += p2.ypower;
    }
  }


  const std::string str() const {
    std::stringstream ss;
    // start with xs
    bool firstTime=true;
    for(const_iterator i(terms.begin());i!=terms.end();++i) {      
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
    for(const_iterator i(terms.begin());i!=terms.end();++i) {   
      val += i->first.substitute(x,y) * i->second;
    }
    return val;
  }
};

#endif
