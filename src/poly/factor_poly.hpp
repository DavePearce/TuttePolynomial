#ifndef SIMPLE_POLY_HPP
#define SIMPLE_POLY_HPP

#include <iostream>
#include "xy_term.hpp"

class yterms {
private:
  unsigned int *ptr; // first 2 bytes = start, second 2 = end, remainder are actual terms
public:
  yterms(unsigned int y_min, unsigned int y_max);
  yterms(yterms const &src);
  ~yterms();

  void resize(unsigned int y_min, unsigned int y_max);
  unsigned int size() const;
  unsigned int ymin() const;
  unsigned int ymax() const;

  void operator+=(xy_term const &p);
private:  
  void clone(yterm const &src);
  
}

class factor_poly {
private:
  yterms* xterms; 
  unsigned int nxterms;
public:
  factor_poly(xy_term const &t);
  factor_poly(factor_poly const &p);
  ~factor_poly();

  factor_poly const &operator=(factor_poly const &src);

  void operator+=(factor_poly const &p);
  void operator+=(xy_term const &p);
  void operator*=(xy_term const &t);
  std::string str() const;  
  double substitute(double x, double y) const;

private:
  void destroy();
  void clone(factor_poly const &p);
  void resize_xterms(unsigned int ns);
};

#endif
