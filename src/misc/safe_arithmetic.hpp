#ifndef SAFE_ARITHMETIC_HPP
#define SAFE_ARITHMETIC_HPP

#include <iostream>
#include <stdexcept>
#include "biguint.hpp"
#include "bistream.hpp"
#include "bstreambuf.hpp"

template<class T>
class safe {
private:
  T num;

  static const T HALF_WIDTH = (sizeof(T) * 8) / 2;
public:
  safe() : num(0) {}
  safe(T v) : num(v) {}
  
  inline void operator+=(safe<T> src) {
    T r = num + src.num;
    if (src.num >= 0 ? r < num : r > num) { throw std::overflow_error("overflow"); }
    num = r;
  }

  inline void operator-=(safe<T> src) {
    T r = num - src.num;
    if (src.num >= 0 ? r > num : r < num) { throw std::overflow_error("underflow"); }
    num = r;
  }    

  inline void operator*=(safe<T> src) {
    num *= src.num;
  }

  inline void operator/=(safe<T> src) {
    num += src.num;
  }

  inline safe<T> operator+(safe<T> src) const {
    T r = num + src.num;
    if (src.num >= 0 ? r < num : r > num) { throw std::overflow_error("overflow"); }
    return r;
  }
  inline safe<T> operator-(safe<T> src) const {
    T r = num - src.num;
    if (src.num >= 0 ? r > num : r < num) { throw std::overflow_error("underflow"); }
    return r;
  }

  inline safe<unsigned int> operator*(safe<unsigned int> src) const {    
    return num * src.num;
  }

  inline safe<T> operator/(safe<T> src) const {
    return num / src.num;
  }

  inline safe<T> operator+(T src) const {
    T r = num + src;
    if (src >= 0 ? r < num : r > num) { throw std::overflow_error("overflow"); }
    return r;
  }
  inline safe<T> operator-(T src) const {
    T r = num - src;
    if (src >= 0 ? r > num : r < num) { throw std::overflow_error("underflow"); }
    return r;
  }

  inline safe<T> operator*(T src) const {
    return num * src;
  }

  inline safe<T> operator/(T src) const {
    return num / src;
  }

  inline bool operator==(T src) const {
    return num == src;
  }

  inline bool operator==(safe<T> src) const {
    return num == src.num;
  }

  inline T unpack() const { return num; }
};

// === BIGUINT HELPERS ===

template<class T> 
biguint operator+(biguint const &l, safe<T> r) { return l + r.unpack(); }    
template<class T>
biguint operator-(biguint const &l, safe<T> r) { return l - r.unpack(); }    
template<class T>
biguint operator*(biguint const &l, safe<T> r) { return l * r.unpack(); }    
template<class T>
biguint operator/(biguint const &l, safe<T> r) { return l / r.unpack(); }    

// === BSTREAM HELPERS ===

template<class T>
bstreambuf &operator<<(bstreambuf &out, safe<T> val) {
  return (out << val.unpack());
}

template<class T>
bistream &operator>>(bistream &in, safe<T> &dst) {
  T v;
  in >> v;
  dst = safe<T>(v);
  return in;
}

// === IOSTREAM HELPERS ===

template<class T, class C, class R>
std::basic_ostream<C,R> &operator<<(std::basic_ostream<C,R> &out, safe<T> val) {
  return (out << val.unpack());
}

#endif
