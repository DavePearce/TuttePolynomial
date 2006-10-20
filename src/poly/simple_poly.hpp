#ifndef SIMPLE_POLY_HPP
#define SIMPLE_POLY_HPP

class simple_poly {
private:
  int _xpower;
  int _ypower;
public:
  void mulByX() { _xpower++; }
  void mulByY() { _ypower++; }
};

#endif
