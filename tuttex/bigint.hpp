#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <stdexcept>
#include "biguint.hpp"

#ifndef INT32_MAX
#define INT32_MAX INT_MAX
#endif

#ifndef INT32_MIN
#define INT32_MIN INT_MIN
#endif

#ifndef INT64_MIN
#define	INT64_MIN	(-0x7fffffffffffffffLL-1)
#endif

#ifndef INT64_MAX
#define	INT64_MAX	0x7fffffffffffffffLL
#endif

#ifndef INT32_C
#define INT32_C(x) ((int32_t)x)
#endif

class bigint {
private:
  // Store integer in sign magnitude representation, using biguint.
  // Note, zero is defined as non-negative sign with magnitude zero.  
  // Having negative sign and zero magnitude is "not a number".
  biguint magnitude;
  bool sign; // true = negative  

  friend std::ostream &operator<<(std::ostream &, bigint const &);
public:
  bigint(int32_t v);
  bigint(int64_t v);
  bigint(uint32_t v);
  bigint(uint64_t v);
  bigint(bigint const &v);
  bigint(biguint const &v);

  /* =============================== */
  /* ======== COMPARISON OPS ======= */
  /* =============================== */

  bool operator==(int32_t v) const;
  bool operator==(int64_t v) const;
  bool operator==(uint32_t v) const;
  bool operator==(uint64_t v) const;
  bool operator==(bigint const &v) const;
  bool operator==(biguint const &v) const;

  bool operator!=(int32_t v) const;
  bool operator!=(int64_t v) const;
  bool operator!=(bigint const &v) const;

  bool operator<(int32_t v) const;
  bool operator<(int64_t v) const;
  bool operator<(bigint const &v) const;

  bool operator<=(int32_t v) const;
  bool operator<=(int64_t v) const;
  bool operator<=(bigint const &v) const;

  bool operator>(int32_t v) const;
  bool operator>(int64_t v) const;
  bool operator>(bigint const &v) const;

  bool operator>=(int32_t v) const;
  bool operator>=(int64_t v) const;
  bool operator>=(bigint const &v) const;

  /* =============================== */
  /* ======== ARITHMETIC OPS ======= */
  /* =============================== */

  void operator+=(int32_t w);
  void operator+=(uint32_t w);
  void operator+=(bigint const &src);
  void operator+=(biguint const &src);
  bigint operator+(int32_t w) const;
  bigint operator+(uint32_t w) const;
  bigint operator+(bigint const &w) const;
  bigint operator+(biguint const &w) const;

  void operator-=(int32_t w);
  void operator-=(uint32_t w);
  void operator-=(bigint const &src);
  void operator-=(biguint const &src);
  bigint operator-(int32_t w) const;
  bigint operator-(uint32_t w) const;
  bigint operator-(bigint const &w) const;
  bigint operator-(biguint const &w) const;

  void operator*=(int32_t v);
  void operator*=(int64_t v);
  void operator*=(uint32_t v);
  void operator*=(uint64_t v);
  void operator*=(bigint const &v);
  void operator*=(biguint const &src);
  bigint operator*(int32_t w) const;
  bigint operator*(int64_t w) const;
  bigint operator*(uint32_t w) const;
  bigint operator*(uint64_t w) const;
  bigint operator*(bigint const &w) const;
  bigint operator*(biguint const &w) const;

  void operator/=(int32_t v);
  bigint operator/(int32_t w) const;

  void operator%=(int32_t v);
  void operator%=(uint32_t v);
  bigint operator%(int32_t w) const;
  bigint operator%(uint32_t w) const;

  void operator^=(uint32_t v);   
  bigint operator^(uint32_t v) const;

  /* =============================== */
  /* ======== CONVERSION OPS ======= */
  /* =============================== */

  int32_t c_int32() const;
  int64_t c_int64() const;
};

bigint pow(bigint const &r, uint32_t power);

bigint operator+(biguint const &a, bigint const &b);
bigint operator-(biguint const &a, bigint const &b);
bigint operator*(biguint const &a, bigint const &b);

#endif
