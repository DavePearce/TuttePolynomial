// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#ifndef SIMPLE_POLY_HPP
#define SIMPLE_POLY_HPP

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "xy_term.hpp"

class simple_poly_term {
public:
  unsigned short xpower;
  unsigned short ypower;

  simple_poly_term(unsigned short x, unsigned short y) : xpower(x), ypower(y) {}
  
  bool operator<(simple_poly_term const &t) const {
    return (xpower < t.xpower) || 
           (xpower == t.xpower && ypower < t.ypower);
  }

  bool operator==(simple_poly_term const &t) const {
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
    return pow(x,(double)xpower) * pow(y,(double) ypower);
  }  
};


template<class MAP = std::map<simple_poly_term,unsigned int> >
class simple_poly {
public:
  typedef typename MAP::iterator iterator;
  typedef typename MAP::const_iterator const_iterator;
private:
  MAP terms;
public:
  simple_poly() {}

  simple_poly(xy_term const &t) {
    if(t.xpower > 0 || t.ypower > 0) { terms.insert(std::make_pair(simple_poly_term(t.xpower,t.ypower),1)); }
  }

  simple_poly(unsigned int n, unsigned int x, unsigned int y) {
    if(x > 0 || y > 0) { terms.insert(std::make_pair(simple_poly_term(x,y),n)); }
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

  void insert(unsigned int n, xy_term const &t) {
    terms.insert(std::make_pair(simple_poly_term(t.xpower,t.ypower),n)); 
  }

  size_t nterms() const { return terms.size(); }

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
  void operator*=(xy_term const &p2) {
    if(p2.ypowerend == p2.ypower) {
      // I don't think the STL strictly would allow this,
      // but it doesn't hurt!      
      for(const_iterator i(terms.begin());i!=terms.end();++i) {      
	simple_poly_term &t((simple_poly_term &)i->first); // ouch ;)
	t.xpower += p2.xpower;
	t.ypower += p2.ypower;
      }
    } else {
      // recursive case (this is an ugly hack)
      simple_poly p(*this);

      for(unsigned int i=p2.ypower;i!=p2.ypowerend-1;++i) {
	*this += p;
	p *= xy_term(0,1);
      }
      
      *this += p;
    }
  }

  const std::string str() const {
    std::stringstream ss;
    // start with xs
    bool firstTime=true;
    for(const_iterator i(terms.begin());i!=terms.end();++i) {      
      if(!firstTime) { ss << " + "; }
      firstTime=false;
      simple_poly_term const &t(i->first);
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
