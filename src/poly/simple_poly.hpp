#ifndef SIMPLE_POLY_HPP
#define SIMPLE_POLY_HPP

class simple_poly {
  friend simple_poly operator+(simple_poly const&, simple_poly const&);
private:
  int _xpower;
  int _ypower;
public:
  simple_poly() : _xpower(0), _ypower(0) {
  }
  simple_poly(int xs, int ys) {
    _xpower = xs;
    _ypower = ys;
  }
};

// useful methods

simple_poly operator+(simple_poly const &p1, simple_poly const &p2);

#endif
