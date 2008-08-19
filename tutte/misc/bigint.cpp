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

void bigint::operator*=(bigint const &w) {
  magnitude *= w.magnitude;
  if(magnitude == 0U) { sign = false; }
  else if(sign != w.sign) { sign = true; }
  else if(sign) { sign = false; }
}

void bigint::operator/=(int w) {
  magnitude /= my_abs(w);
  if(magnitude == 0U) { sign = false; }
  else if(sign != (w < 0)) { sign = true; }
  else if(sign) { sign = false; }
}

bigint bigint::operator+(int w) const {
  bigint r(*this);
  r += w;
  return r;
}

bigint bigint::operator+(bigint const &w) const {
  bigint r(*this);
  r += w;
  return r;
}
bigint bigint::operator-(int w) const {
  bigint r(*this);
  r -= w;
  return r;
}
bigint bigint::operator-(bigint const &w) const {
  bigint r(*this);
  r -= w;
  return r;
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
bigint bigint::operator*(bigint const &w) const {
  bigint r(*this);
  r *= w;
  return r;
}

bigint bigint::operator/(int w) const {
  bigint r(*this);
  r /= w;
  return r;
}

/* =============================== */
/* ======== CONVERSION OPS ======= */
/* =============================== */

int bigint::c_int() const {
  unsigned int w = magnitude.c_uint();
  if((!sign && (w > INT_MAX)) || w >= INT_MAX) {
    throw runtime_error("bigint too large for int");
  } 
  if(sign) { return -w; } 
  else { return w; }
}  

long bigint::c_long() const {
  unsigned long w = magnitude.c_ulong();
  if((!sign && (w > LONG_MAX)) || w >= LONG_MAX) {
    throw runtime_error("bigint too large for long");
  } 
  if(sign) { return -w; } 
  else { return w; }
}  

long long bigint::c_longlong() const {
  unsigned long long w = magnitude.c_ulonglong();
  if((!sign && (w > LLONG_MAX)) || w >= LLONG_MAX) {
    throw runtime_error("bigint too large for long long");
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
