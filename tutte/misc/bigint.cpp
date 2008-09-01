#include "bigint.hpp"

using namespace std;

uint32_t my_abs(int32_t v) {
  if(v == INT32_MIN) {
    return ((uint32_t) INT32_MAX)+1;
  } else if(v < 0) {
    return -v;    
  } else { 
    return v; 
  }
}

uint64_t my_abs(int64_t v) {
  if(v == INT64_MIN) {
    return ((uint64_t) INT64_MAX)+1;
  } else if(v < 0) {
    return -v;    
  } else { 
    return v; 
  }
}

bigint::bigint(int32_t v) : magnitude(my_abs(v)), sign(v < 0) { }
bigint::bigint(int64_t v) : magnitude(my_abs(v)), sign(v < 0) { }
bigint::bigint(uint32_t v) : magnitude(v), sign(false) { }
bigint::bigint(uint64_t v) : magnitude(v), sign(false) { }
bigint::bigint(bigint const &v) : magnitude(v.magnitude), sign(v.sign) { }
bigint::bigint(biguint const &v) : magnitude(v), sign(false) { }

bool bigint::operator==(int32_t v) const {
  return ((v < 0) == sign) && magnitude == my_abs(v);
}
bool bigint::operator==(int64_t v) const {
  return ((v < 0) == sign) && magnitude == my_abs(v);
}
bool bigint::operator==(bigint const &v) const {
  return (v.sign == sign) && v.magnitude == magnitude;
}

bool bigint::operator!=(int32_t v) const { return !(*this == v); }
bool bigint::operator!=(int64_t v) const { return !(*this == v); }
bool bigint::operator!=(bigint const &v) const { return !(*this == v); }

bool bigint::operator<(int32_t v) const {
  if(v < 0 && !sign) { return false; }
  if(v >= 0 && sign) { return true; }
  else if(v<0 && sign) { return magnitude > my_abs(v); } 
  else { return magnitude < my_abs(v); }
}
bool bigint::operator<(int64_t v) const {
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

bool bigint::operator<=(int32_t v) const {
  if(v < 0 && !sign) { return false; }
  if(v >= 0 && sign) { return true; }
  else if(v<0 && sign) { return magnitude >= my_abs(v); } 
  else { return magnitude <= my_abs(v); }
}
bool bigint::operator<=(int64_t v) const {
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

bool bigint::operator>(int32_t v) const { return !(*this <= v); }
bool bigint::operator>(int64_t v) const { return !(*this <= v); }
bool bigint::operator>(bigint const &v) const { return !(*this <= v); }

bool bigint::operator>=(int32_t v) const { return !(*this < v); }
bool bigint::operator>=(int64_t v) const { return !(*this < v); }
bool bigint::operator>=(bigint const &v) const { return !(*this < v); }

/* ========= OPERATOR + ========== */

void bigint::operator+=(int32_t w) {
  uint32_t w_magnitude = my_abs(w);
  if((w<0) != sign) {
    // neg + pos, pos + neg
    if(magnitude < w_magnitude) {
      // swap sign here
      magnitude = biguint(w_magnitude) - magnitude;
      sign = !sign;
    } else {
      magnitude -= w_magnitude;
      if(magnitude == UINT32_C(0)) { sign = false; }
    }
  } else {
    // neg + neg, pos + pos.
    magnitude += w_magnitude;
  }
}

void bigint::operator+=(uint32_t w) {
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
      if(magnitude == UINT32_C(0)) { sign = false; }
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

bigint bigint::operator+(int32_t w) const {
  bigint r(*this);
  r += w;
  return r;
}
bigint bigint::operator+(uint32_t w) const {
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

void bigint::operator-=(int32_t w) {
  uint32_t w_magnitude = my_abs(w);
  if((w<0) == sign) {
    // neg - neg, pos - pos
    if(magnitude < w_magnitude) {
      // swap sign here
      magnitude = biguint(w_magnitude) - magnitude;
      sign = !sign;
    } else {
      magnitude -= w_magnitude;
      if(magnitude == UINT32_C(0)) { sign = false; }
    }
  } else {
    // neg - pos, pos - neg.
    magnitude += w_magnitude;
  }
}
void bigint::operator-=(uint32_t w) {
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
      if(magnitude == UINT32_C(0)) { sign = false; }
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

bigint bigint::operator-(int32_t w) const {
  bigint r(*this);
  r -= w;
  return r;
}
bigint bigint::operator-(uint32_t w) const {
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

void bigint::operator*=(int32_t w) {
  magnitude *= my_abs(w);
  if(w == UINT32_C(0)) { sign = false; }
  else if(sign != (w < 0)) { sign = true; }
  else if(sign) { sign=false; }
}

void bigint::operator*=(int64_t w) {
  magnitude *= my_abs(w);
  if(w == UINT32_C(0)) { sign = false; }
  else if(sign != (w < 0)) { sign = true; }
  else if(sign) { sign = false; }
}
void bigint::operator*=(uint32_t w) {
  magnitude *= w;
  if(w == UINT32_C(0)) { sign = false; }
}

void bigint::operator*=(uint64_t w) {
  magnitude *= w;
  if(w == UINT32_C(0)) { sign = false; }
}
void bigint::operator*=(bigint const &w) {
  magnitude *= w.magnitude;
  if(magnitude == UINT32_C(0)) { sign = false; }
  else if(sign != w.sign) { sign = true; }
  else if(sign) { sign = false; }
}

void bigint::operator*=(biguint const &w) {
  magnitude *= w;
  if(w == UINT32_C(0)) { sign = false; }
}

bigint bigint::operator*(int32_t w) const {
  bigint r(*this);
  r *= w;
  return r;
}

bigint bigint::operator*(int64_t w) const {
  bigint r(*this);
  r *= w;
  return r;
}
bigint bigint::operator*(uint32_t w) const {
  bigint r(*this);
  r *= w;
  return r;
}

bigint bigint::operator*(uint64_t w) const {
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

void bigint::operator/=(int32_t w) {
  magnitude /= my_abs(w);
  if(magnitude == UINT32_C(0)) { sign = false; }
  else if(sign != (w < 0)) { sign = true; }
  else if(sign) { sign = false; }
}

bigint bigint::operator/(int32_t w) const {
  bigint r(*this);
  r /= w;
  return r;
}

/* ========= OPERATOR % ========== */

void bigint::operator%=(int32_t v) {
  magnitude %= my_abs(v);
  if(magnitude == UINT32_C(0)) { sign = false; }
}
void bigint::operator%=(uint32_t v) {
  magnitude %= v;
  if(magnitude == UINT32_C(0)) { sign = false; }
}
bigint bigint::operator%(int32_t v) const {
  bigint r(*this);
  r %= v;
  return r;
}
bigint bigint::operator%(uint32_t v) const {
  bigint r(*this);
  r %= v;
  return r;
}
/* ========= OPERATOR ^ ========== */

void bigint::operator^=(uint32_t v) {
  if(v == UINT32_C(0)) { (*this) = INT32_C(1); }
  else {
    bigint p(*this);
    
    for(unsigned int i=1;i<v;++i) {
      (*this) *= p;
    }
  }
}

bigint bigint::operator^(uint32_t v) const {
  bigint r(*this);
  r ^= v;
  return r;
}

/* =============================== */
/* ======== CONVERSION OPS ======= */
/* =============================== */

int32_t bigint::c_int32() const {
  uint32_t w = magnitude.c_uint32();
  if((!sign && (w > INT32_MAX)) || w >= INT32_MAX) {
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

  if(val == INT32_C(0)) { return out << "0"; }
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
