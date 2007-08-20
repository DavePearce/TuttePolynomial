// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#ifndef XY_TERM_HPP
#define XY_TERM_HPP

#include <cmath>
#include <string>
#include <sstream>

class xy_term {
public:
  unsigned short xpower;
  unsigned short ypower;
  unsigned short ypowerend;

  xy_term(unsigned short x, unsigned short y) : xpower(x), ypower(y), ypowerend(y) {}
  xy_term(unsigned short x, unsigned short y, unsigned short yend) : xpower(x), ypower(y), ypowerend(yend) {
    if(yend < y) { ypower = 0; ypowerend = 0; }
  }
  
  bool operator<(xy_term const &t) const {
    return (xpower < t.xpower) || 
           (xpower == t.xpower && ypower < t.ypower) || 
           (xpower == t.xpower && ypower == t.ypower && ypowerend < t.ypowerend);
  }

  bool operator==(xy_term const &t) const {
    return (xpower == t.xpower && t.ypower == t.ypower && t.ypowerend == t.ypowerend);
  }

  std::string str() const {
    std::stringstream ss;
    if(xpower > 1) { ss << "x^" << xpower; }
    else if(xpower == 1) { ss << "x"; }

    if(ypower < ypowerend) { ss << "y^" << ypower << "-" << ypowerend; }
    else if(ypower > 1) { ss << "y^" << ypower; }
    else if(ypower == 1) { ss << "y"; }

    return ss.str();
  }

  double substitute(double x, double y) const {
    double r=0;
    for(unsigned int i=ypower;i!=ypowerend;++i) {
      r += pow(x,(double)xpower) * pow(y,(double) i);
    }
    return r;
  }  
};

class Y : public xy_term {
public:
  Y(unsigned int p) : xy_term(0,p) {}
  Y(unsigned int p, unsigned int pend) : xy_term(0,p,pend) {}
};

class X : public xy_term {
public:
  X(unsigned int p) : xy_term(p,0) {}

  xy_term operator*(Y const &yt) const {
    return xy_term(xpower,yt.ypower);
  }  

  X operator*(X const &xt) const {
    return X(xpower * xt.xpower);
  }
};

#endif
