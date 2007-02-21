#ifndef SIMPLE_POLY_HPP
#define SIMPLE_POLY_HPP

#include "xy_term.hpp"

class factor_poly {
private:
  typedef struct {
    unsigned short ypower;
    unsigned short ypowerend;
  } y_term;
  
  unsigned int** terms; // first term is y_term
  unsigned int nxterms;
public:
  
  factor_poly(xy_term const &t) {
    nxterms = t.xpower;
    // create the xterm array
    terms = new (unsigned int*)[nxterms];
    for(unsigned int i=0;i!=nxterms;++i) {
      terms[i] = NULL;
    }
    
  }
}

#endif
