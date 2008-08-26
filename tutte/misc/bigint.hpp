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
  bigint(unsigned int v);
  bigint(unsigned long v);
  bigint(unsigned long long v);
  bigint(bigint const &v);
  bigint(biguint const &v);

  /* =============================== */
  /* ======== COMPARISON OPS ======= */
  /* =============================== */

  bool operator==(int v) const;
  bool operator==(long v) const;
  bool operator==(long long v) const;
  //  bool operator==(unsigned int v) const;
  //  bool operator==(unsigned long v) const;
  //  bool operator==(unsigned long long v) const;
  bool operator==(bigint const &v) const;
  bool operator==(biguint const &v) const;

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
  void operator+=(unsigned int w);
  void operator+=(bigint const &src);
  void operator+=(biguint const &src);
  bigint operator+(int w) const;
  bigint operator+(unsigned int w) const;
  bigint operator+(bigint const &w) const;
  bigint operator+(biguint const &w) const;

  void operator-=(int w);
  void operator-=(unsigned int w);
  void operator-=(bigint const &src);
  void operator-=(biguint const &src);
  bigint operator-(int w) const;
  bigint operator-(unsigned int w) const;
  bigint operator-(bigint const &w) const;
  bigint operator-(biguint const &w) const;

  void operator*=(int v);
  void operator*=(long long v);
  void operator*=(unsigned int v);
  void operator*=(unsigned long long v);
  void operator*=(bigint const &v);
  void operator*=(biguint const &src);
  bigint operator*(int w) const;
  bigint operator*(long long w) const;
  bigint operator*(unsigned int w) const;
  bigint operator*(unsigned long long w) const;
  bigint operator*(bigint const &w) const;
  bigint operator*(biguint const &w) const;

  void operator/=(int v);
  bigint operator/(int w) const;

  void operator%=(int v);
  void operator%=(unsigned int v);
  bigint operator%(int w) const;
  bigint operator%(unsigned int w) const;

  void operator^=(unsigned int v);   
  bigint operator^(unsigned int v) const;

  /* =============================== */
  /* ======== CONVERSION OPS ======= */
  /* =============================== */

  int c_int() const;
  long c_long() const;
  long long c_longlong() const;
};

bigint pow(bigint const &r, uint32_t power);

bigint operator+(biguint const &a, bigint const &b);
bigint operator-(biguint const &a, bigint const &b);
bigint operator*(biguint const &a, bigint const &b);

#endif
