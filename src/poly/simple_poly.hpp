#ifndef SIMPLE_POLY_HPP
#define SIMPLE_POLY_HPP

class simple_poly {
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
  
  void mulByX(int x) { _xpower++; }
  void mulByY(int y) { _ypower++; }
};

#endif
