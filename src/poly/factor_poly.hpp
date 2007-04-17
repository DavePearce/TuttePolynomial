#ifndef FACTOR_POLY_HPP
#define FACTOR_POLY_HPP

#include <iostream>
#include <string>
#include <utility>
#include "xy_term.hpp"

class yterms {
private:
  typedef struct header {
    unsigned int ymin;
    unsigned int ymax;
    unsigned int front_padding;
    unsigned int back_padding;
  } header;
public:
  header *ptr; // header first, then front padding, followed by data, then back padding
public:
  yterms();
  yterms(unsigned int y_min, unsigned int y_max);
  yterms(yterms const &src);
  ~yterms();

  void resize(unsigned int y_min, unsigned int y_max);
  void swap(yterms &src);
  unsigned int size() const;
  unsigned int ymin() const { return ptr->ymin; }
  unsigned int ymax() const { return ptr->ymax; }
  bool is_empty() const;  

  yterms const &operator=(yterms const &src);
  void operator+=(xy_term const &p);
  void operator+=(yterms const &src);
  void insert(unsigned int n, xy_term const &p); // needs a better name? 
  void operator*=(xy_term const &p);
  unsigned int operator[](int) const;
  unsigned int nterms() const;

  double substitute(double y) const;
  std::string str() const;
private:  
  void clone(yterms const &src);  
  // low level operations
  unsigned int get(unsigned int y, header *h) const;
  void set(unsigned int y, unsigned int v, header *h);
  void add(unsigned int y, unsigned int v, header *h);
  header *alloc(unsigned int ymin, unsigned int ymax);
};

// This iterator is a temporary structure
class factor_poly_iterator {
private:
  unsigned int x;
  unsigned int x_max;
  unsigned int y;
  yterms *xterms;
public:
  factor_poly_iterator(unsigned int _x, unsigned int xm, yterms *_xterms) 
    : x(_x), x_max(xm), xterms(_xterms) {
    while(x < x_max && xterms[x].is_empty()) { ++x; }      
    if(x >= x_max) { y = 0; }
    else { y = xterms[x].ymin(); }
  }

  void operator++() { 
    if(++y > xterms[x].ymax()) {
      do { ++x; }
      while(x < x_max && xterms[x].is_empty());
      if(x >= x_max) { y = 0; }
      else { y = xterms[x].ymin(); }
    } 
  }

  factor_poly_iterator operator++(int) { 
    factor_poly_iterator tmp(*this);
    ++(*this);
    return tmp;
  }

  // crikey, this is ugly
  std::pair<xy_term, unsigned int> operator*() const {
    return std::make_pair(xy_term(x,y),xterms[x][y-xterms[x].ymin()]);
  }

  std::string str() const {
    std::stringstream ss;
    ss << x << "," << y;
    return ss.str();
  }

  bool operator==(factor_poly_iterator const &o) const {
    return xterms == o.xterms && x == o.x && y == o.y;
  }

  bool operator!=(factor_poly_iterator const &o) const {
    return xterms != o.xterms || x != o.x || y != o.y;
  }
};

class factor_poly {
public:
  typedef factor_poly_iterator const_iterator;
private:
  yterms* xterms; 
  unsigned int nxterms;
public:
  factor_poly();
  factor_poly(xy_term const &t);
  factor_poly(factor_poly const &p);
  ~factor_poly();

  factor_poly const &operator=(factor_poly const &src);

  void operator+=(factor_poly const &p);
  void operator+=(xy_term const &p);
  void operator*=(xy_term const &t);
  void insert(unsigned int n, xy_term const &p);
  std::string str() const;  
  double substitute(double x, double y) const;
  unsigned int nterms() const;
  
  const_iterator begin() const { return factor_poly_iterator(0,nxterms,xterms); }
  const_iterator end() const { return factor_poly_iterator(nxterms,nxterms,xterms); }
private:
  void destroy();
  void clone(factor_poly const &p);
  void resize_xterms(unsigned int ns);
};

#endif
