#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <stdexcept>
#include "biguint.hpp"

class bigint {
private:
  // Store integer in sign magnitude representation, using biguint.
  // Note, zero is defined as non-negative sign with magnitude zero.  
  // Having negative sign and zero magnitude is "not a number".
  biguint magnitude;
  bool sign; // true = negative  

  friend std::ostream &operator<<(std::ostream &, bigint const &);
public:
  bigint(int v);
  bigint(long v);
  bigint(long long v);
  bigint(biguint const &v);

  /* =============================== */
  /* ======== COMPARISON OPS ======= */
  /* =============================== */

  bool operator==(int v) const;
  bool operator==(long v) const;
  bool operator==(long long v) const;
  bool operator==(bigint const &v) const;

  bool operator!=(int v) const;
  bool operator!=(long v) const;
  bool operator!=(long long v) const;
  bool operator!=(bigint const &v) const;

  bool operator<(int v) const;
  bool operator<(long v) const;
  bool operator<(long long v) const;
  bool operator<(bigint const &v) const;

  bool operator<=(int v) const;
  bool operator<=(long v) const;
  bool operator<=(long long v) const;
  bool operator<=(bigint const &v) const;

  bool operator>(int v) const;
  bool operator>(long v) const;
  bool operator>(long long v) const;
  bool operator>(bigint const &v) const;

  bool operator>=(int v) const;
  bool operator>=(long v) const;
  bool operator>=(long long v) const;
  bool operator>=(bigint const &v) const;

  /* =============================== */
  /* ======== ARITHMETIC OPS ======= */
  /* =============================== */

  void operator+=(int w);
  void operator+=(bigint const &src);

  void operator-=(int w);
  void operator-=(bigint const &src);

  void operator*=(int v);
  void operator*=(long long v);
  void operator*=(bigint const &v);

  void operator/=(int v);
  void operator%=(int v);
  void operator^=(int v);   

  bigint operator+(int w) const;
  bigint operator+(bigint const &w) const;
  bigint operator-(int w) const;
  bigint operator-(bigint const &w) const;

  bigint operator*(int w) const;
  bigint operator*(long long w) const;
  bigint operator*(bigint const &w) const;
  bigint operator/(int w) const;
  int operator%(int w) const;
  bigint operator^(int v) const;

  /* =============================== */
  /* ======== CONVERSION OPS ======= */
  /* =============================== */

  int c_int() const;
  long c_long() const;
  long long c_longlong() const;
};

#endif
