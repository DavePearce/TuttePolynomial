#ifndef XY_TERM_HPP
#define XY_TERM_HPP

class xy_term {
public:
  unsigned short xpower;
  unsigned short ypower;
  unsigned short ypowerend;

  xy_term(unsigned short x, unsigned short y) : xpower(x), ypower(y), ypowerend(y) {}
  xy_term(unsigned short x, unsigned short y, unsigned short yend) : xpower(x), ypower(y), ypowerend(yend) {}
  
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

#endif
