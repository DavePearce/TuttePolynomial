#include "bigint.hpp"

using namespace std;

unsigned int my_abs(int v) {
  if(v == INT_MIN) {
    return ((unsigned int) INT_MAX)+1;
  } else if(v < 0) {
    return -v;    
  } else { 
    return v; 
  }
}

unsigned long my_abs(long v) {
  if(v == LONG_MIN) {
    return ((unsigned long) LONG_MAX)+1;
  } else if(v < 0) {
    return -v;    
  } else { 
    return v; 
  }
}

unsigned long long my_abs(long long v) {
  if(v == LLONG_MIN) {
    return ((unsigned long long) LLONG_MAX)+1;
  } else if(v < 0) {
    return -v;    
  } else { 
    return v; 
  }
}

bigint::bigint(int v) : magnitude(my_abs(v)), sign(v < 0) { }
bigint::bigint(long v) : magnitude(my_abs(v)), sign(v < 0) { }
bigint::bigint(long long v) : magnitude(my_abs(v)), sign(v < 0) { }
bigint::bigint(unsigned int v) : magnitude(v), sign(false) { }
bigint::bigint(unsigned long v) : magnitude(v), sign(false) { }
bigint::bigint(unsigned long long v) : magnitude(v), sign(false) { }
bigint::bigint(bigint const &v) : magnitude(v.magnitude), sign(v.sign) { }
bigint::bigint(biguint const &v) : magnitude(v), sign(false) { }

bool bigint::operator==(int v) const {
  return ((v < 0) == sign) && magnitude == my_abs(v);
}
bool bigint::operator==(long v) const {
  return ((v < 0) == sign) && magnitude == my_abs(v);
}
bool bigint::operator==(long long v) const {
  return ((v < 0) == sign) && magnitude == my_abs(v);
}
bool bigint::operator==(bigint const &v) const {
  return (v.sign == sign) && v.magnitude == magnitude;
}

bool bigint::operator!=(int v) const { return !(*this == v); }
bool bigint::operator!=(long v) const { return !(*this == v); }
bool bigint::operator!=(long long v) const { return !(*this == v); }
bool bigint::operator!=(bigint const &v) const { return !(*this == v); }

bool bigint::operator<(int v) const {
  if(v < 0 && !sign) { return false; }
  if(v >= 0 && sign) { return true; }
  else if(v<0 && sign) { return magnitude > my_abs(v); } 
  else { return magnitude < my_abs(v); }
}
bool bigint::operator<(long v) const {
  if(v < 0 && !sign) { return false; }
  if(v >= 0 && sign) { return true; }
  else if(v<0 && sign) { return magnitude > my_abs(v); } 
  else { return magnitude < my_abs(v); }
}
bool bigint::operator<(long long v) const {
  if(v < 0 && !sign) { return false; }
  if(v >= 0 && sign) { return true; }
  else if(v<0 && sign) { return magnitude > my_abs(v); } 
  else { return magnitude < my_abs(v); }
}
bool bigint::operator<(bigint const &v) const {
  if(v.sign && !sign) { return false; }
  if(!v.sign && sign) { return true; }
  else if(v.sign && sign) { return magnitude > v.magnitude; } 
  else { return magnitude < v.magnitude; }
}

bool bigint::operator<=(int v) const {
  if(v < 0 && !sign) { return false; }
  if(v >= 0 && sign) { return true; }
  else if(v<0 && sign) { return magnitude >= my_abs(v); } 
  else { return magnitude <= my_abs(v); }
}
bool bigint::operator<=(long v) const {
  if(v < 0 && !sign) { return false; }
  if(v >= 0 && sign) { return true; }
  else if(v < 0 && sign) { return magnitude >= my_abs(v); } 
  else { return magnitude <= my_abs(v); }
}
bool bigint::operator<=(long long v) const {
  if(v < 0 && !sign) { return false; }
  if(v >= 0 && sign) { return true; }
  else if(v<0 && sign) { return magnitude >= my_abs(v); } 
  else { return magnitude <= my_abs(v); }
}
bool bigint::operator<=(bigint const &v) const {
  if(v.sign && !sign) { return false; }
  if(!v.sign && sign) { return true; }
  else if(v.sign && sign) { return magnitude >= v.magnitude; } 
  else { return magnitude <= v.magnitude; }
}

bool bigint::operator>(int v) const { return !(*this <= v); }
bool bigint::operator>(long v) const { return !(*this <= v); }
bool bigint::operator>(long long v) const { return !(*this <= v); }
bool bigint::operator>(bigint const &v) const { return !(*this <= v); }

bool bigint::operator>=(int v) const { return !(*this < v); }
bool bigint::operator>=(long v) const { return !(*this < v); }
bool bigint::operator>=(long long v) const { return !(*this < v); }
bool bigint::operator>=(bigint const &v) const { return !(*this < v); }

/* ========= OPERATOR + ========== */

void bigint::operator+=(int w) {
  unsigned int w_magnitude = my_abs(w);
  if((w<0) != sign) {
    // neg + pos, pos + neg
    if(magnitude < w_magnitude) {
      // swap sign here
      magnitude = biguint(w_magnitude) - magnitude;
      sign = !sign;
    } else {
      magnitude -= w_magnitude;
      if(magnitude == 0U) { sign = false; }
    }
  } else {
    // neg + neg, pos + pos.
    magnitude += w_magnitude;
  }
}

void bigint::operator+=(unsigned int w) {
  if(sign) {
    if(magnitude <= w) {
      // swap sign here
      magnitude = biguint(w) - magnitude;
      sign = false;
    } else {
      magnitude -= w;
    }
  } else {
    magnitude += w;
  }
}

void bigint::operator+=(bigint const &w) {
  if(w.sign != sign) {
    // neg + pos, pos + neg
    if(magnitude < w.magnitude) {
      // swap sign here
      magnitude = w.magnitude - magnitude;
      sign = !sign;
    } else {
      magnitude -= w.magnitude;
      if(magnitude == 0U) { sign = false; }
    }
  } else {
    // neg + neg, pos + pos.
    magnitude += w.magnitude;
  }
}

void bigint::operator+=(biguint const &w) {
  if(sign) {
    if(magnitude <= w) {
      // swap sign here
      magnitude = w - magnitude;
      sign = false;
    } else {
      magnitude -= w;
    }
  } else {
    magnitude += w;
  }
}

bigint bigint::operator+(int w) const {
  bigint r(*this);
  r += w;
  return r;
}
bigint bigint::operator+(unsigned int w) const {
  bigint r(*this);
  r += w;
  return r;
}
bigint bigint::operator+(bigint const &w) const {
  bigint r(*this);
  r += w;
  return r;
}
bigint bigint::operator+(biguint const &w) const {
  bigint r(*this);
  r += w;
  return r;
}

/* ========= OPERATOR - ========== */

void bigint::operator-=(int w) {
  unsigned int w_magnitude = my_abs(w);
  if((w<0) == sign) {
    // neg - neg, pos - pos
    if(magnitude < w_magnitude) {
      // swap sign here
      magnitude = biguint(w_magnitude) - magnitude;
      sign = !sign;
    } else {
      magnitude -= w_magnitude;
      if(magnitude == 0U) { sign = false; }
    }
  } else {
    // neg - pos, pos - neg.
    magnitude += w_magnitude;
  }
}

void bigint::operator-=(unsigned int w) {
  if(!sign) {
    if(magnitude < w) {
      // swap sign here
      magnitude = biguint(w) - magnitude;
      sign = true;
    } else {
      magnitude -= w;
    }
  } else {
    magnitude += w;
  }
}

void bigint::operator-=(bigint const &w) {
  if(w.sign == sign) {
    // neg + pos, pos + neg
    if(magnitude < w.magnitude) {
      // swap sign here
      magnitude = w.magnitude - magnitude;
      sign = !sign;
    } else {
      magnitude -= w.magnitude;
      if(magnitude == 0U) { sign = false; }
    }
  } else {
    // neg + neg, pos + pos.
    magnitude += w.magnitude;
  }
}

void bigint::operator-=(biguint const &w) {
  if(!sign) {
    if(magnitude < w) {
      // swap sign here
      magnitude = w - magnitude;
      sign = true;
    } else {
      magnitude -= w;
    }
  } else {
    magnitude += w;
  }
}

bigint bigint::operator-(int w) const {
  bigint r(*this);
  r -= w;
  return r;
}

bigint bigint::operator-(unsigned int w) const {
  bigint r(*this);
  r -= w;
  return r;
}

bigint bigint::operator-(bigint const &w) const {
  bigint r(*this);
  r -= w;
  return r;
}

bigint bigint::operator-(biguint const &w) const {
  bigint r(*this);
  r -= w;
  return r;
}

/* ========= OPERATOR * ========== */

void bigint::operator*=(int w) {
  magnitude *= my_abs(w);
  if(w == 0U) { sign = false; }
  else if(sign != (w < 0)) { sign = true; }
  else if(sign) { sign=false; }
}

void bigint::operator*=(long long w) {
  magnitude *= my_abs(w);
  if(w == 0U) { sign = false; }
  else if(sign != (w < 0)) { sign = true; }
  else if(sign) { sign = false; }
}

void bigint::operator*=(unsigned int w) {
  magnitude *= w;
  if(w == 0U) { sign = false; }
}

void bigint::operator*=(unsigned long long w) {
  magnitude *= w;
  if(w == 0U) { sign = false; }
}

void bigint::operator*=(bigint const &w) {
  magnitude *= w.magnitude;
  if(magnitude == 0U) { sign = false; }
  else if(sign != w.sign) { sign = true; }
  else if(sign) { sign = false; }
}

void bigint::operator*=(biguint const &w) {
  magnitude *= w;
  if(w == 0U) { sign = false; }
}

bigint bigint::operator*(int w) const {
  bigint r(*this);
  r *= w;
  return r;
}

bigint bigint::operator*(long long w) const {
  bigint r(*this);
  r *= w;
  return r;
}

bigint bigint::operator*(unsigned int w) const {
  bigint r(*this);
  r *= w;
  return r;
}

bigint bigint::operator*(unsigned long long w) const {
  bigint r(*this);
  r *= w;
  return r;
}

bigint bigint::operator*(bigint const &w) const {
  bigint r(*this);
  r *= w;
  return r;
}

bigint bigint::operator*(biguint const &w) const {
  bigint r(*this);
  r *= w;
  return r;
}

/* ========= OPERATOR / ========== */

void bigint::operator/=(int w) {
  magnitude /= my_abs(w);
  if(magnitude == 0U) { sign = false; }
  else if(sign != (w < 0)) { sign = true; }
  else if(sign) { sign = false; }
}

bigint bigint::operator/(int w) const {
  bigint r(*this);
  r /= w;
  return r;
}

/* ========= OPERATOR % ========== */

void bigint::operator%=(int v) {
  magnitude %= my_abs(v);
  if(magnitude == 0U) { sign = false; }
}

void bigint::operator%=(unsigned int v) {
  magnitude %= v;
  if(magnitude == 0U) { sign = false; }
}

bigint bigint::operator%(int v) const {
  bigint r(*this);
  r %= v;
  return r;
}

bigint bigint::operator%(unsigned int v) const {
  bigint r(*this);
  r %= v;
  return r;
}

/* ========= OPERATOR ^ ========== */

void bigint::operator^=(unsigned int v) {
  if(v == 0) { (*this) = 1; }
  else {
    bigint p(*this);
    
    for(unsigned int i=1;i<v;++i) {
      (*this) *= p;
    }
  }
}

bigint bigint::operator^(unsigned int v) const {
  bigint r(*this);
  r ^= v;
  return r;
}

/* =============================== */
/* ======== CONVERSION OPS ======= */
/* =============================== */

int bigint::c_int() const {
  unsigned int w = magnitude.c_uint32();
  if((!sign && (w > INT_MAX)) || w >= INT_MAX) {
    throw runtime_error("bigint too large for int");
  } 
  if(sign) { return -w; } 
  else { return w; }
}  

/* =============================== */
/* ======== FRIEND METHODS ======= */
/* =============================== */

std::ostream& operator<<(ostream &out, bigint const &val) {
  std::string r;

  if(val == 0) { return out << "0"; }
  else if(val.sign) { return out << "-" << val.magnitude; }
  else {
    return out << val.magnitude;
  }
}

/* =============================== */
/* ======== OTHER METHODS ======= */
/* =============================== */

bigint pow(bigint const &r, uint32_t power) {
  return r ^ power;
}

bigint operator+(biguint const &a, bigint const &b) {
  return b + a;
}
bigint operator-(biguint const &a, bigint const &b) {
  return bigint(a) - b;
}
bigint operator*(biguint const &a, bigint const &b) {
  return b * a;
}
