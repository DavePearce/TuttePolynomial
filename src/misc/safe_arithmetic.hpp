#ifndef SAFE_ARITHMETIC_HPP
#define SAFE_ARITHMETIC_HPP

template<class T>
class safe {
private:
  T num;

public:
  safe() : num(0) {}
  safe(T v) : num(v) {}
  
  inline void operator+=(safe<T> src) {
    num += src.num;
  }
  inline void operator-=(safe<T> src) {
    num -= src.num;
  }    
  inline void operator*=(safe<T> src) {
    num *= src.num;
  }
  inline void operator/=(safe<T> src) {
    num += src.num;
  }

  inline safe<T> operator+(safe<T> src) const {
    return num + src.num;
  }
  inline safe<T> operator-(safe<T> src) const {
    return num - src.num;
  }
  inline safe<T> operator*(safe<T> src) const {
    return num * src.num;
  }
  inline safe<T> operator/(safe<T> src) const {
    return num / src.num;
  }

  inline safe<T> operator+(T src) const {
    return num + src;
  }
  inline safe<T> operator-(T src) const {
    return num - src;
  }
  inline safe<T> operator*(T src) const {
    return num * src;
  }
  inline safe<T> operator/(T src) const {
    return num / src;
  }

  inline T unpack() const { return num; }
};

#endif
