#ifndef SYMBOLIC_POLY_HPP
#define SYMBOLIC_POLY_HPP

#include "triple.hpp"

class symbolic_term {
public:
  unsigned int xpower;
  unsigned int ypower;
  std::vector<std::pair<unsigned int, unsigned int> > ypowerends;

  symbolic_term(unsigned int xp, unsigned int yp) 
    : xpower(xp), ypower(yp) {    
  }

  bool operator==(symbolic_term const &t) const {
    return (xpower == t.xpower && ypower == t.ypower && t.ypowerends == ypowerends);
  }
};

class symbolic_X : public symbolic_term {
public:
  symbolic_X(unsigned int xpower) : symbolic_term(xpower,0) {
  }
};

class symbolic_Y : public symbolic_term {
public:
  symbolic_Y(unsigned int ypower, std::pair<unsigned int, unsigned int> const &label) : symbolic_term(0,ypower) {
    if(label.first > label.second) {
      ypowerends.push_back(std::make_pair(label.second,label.first));
    } else {
      ypowerends.push_back(std::make_pair(label.first,label.second));
    }
  }
};

class symbolic_poly {
public:
  typedef symbolic_X X;
  typedef symbolic_Y Y;
private:
  typedef std::pair<biguint,symbolic_term> term_t;
  std::vector<term_t> terms;  
public: 
  symbolic_poly() {}
  
  symbolic_poly(symbolic_term const &term) {
    terms.push_back(term_t(UINT32_C(1),term));
  }

  void operator+=(symbolic_term const &term) {
    for(std::vector<term_t>::iterator i(terms.begin());i!=terms.end();++i) {
      if(i->second == term) {
	i->first += UINT32_C(1);
	return;
      }
    }
    terms.push_back(term_t(UINT32_C(1),term));
    // probably need to sort the terms here I think.
  }

  void operator+=(symbolic_poly const &src) {
    // this can be made more efficient!
    for(std::vector<term_t>::const_iterator i(src.terms.begin());i!=src.terms.end();) {
      for(std::vector<term_t>::iterator j(terms.begin());j!=terms.end();++j) {
	if(j->second == i->second) {
	  j->first += i->first;
	  goto cont;
	}
      }
      terms.push_back(*i);
    cont:
      i++;
    }
  }

  void operator*=(symbolic_term const &term) {
    // do nout for now!
  }

  void operator*=(symbolic_poly const &poly) {
    // do nout for now!
  }
};

#endif
