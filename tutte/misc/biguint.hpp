// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#ifndef BIGUINT_HPP
#define BIGUINT_HPP

#include <iostream>
#include <climits>
#include <gmpxx.h>
#include "bstreambuf.hpp"
#include "bistream.hpp"

template<class T>
class safe; // forward declaration

// this class provides arbitrary sized integers
typedef unsigned int bui_word;
typedef unsigned long long bui_dword;

#define BUI_WORD_WIDTH 32U
// 2147483648U
#define BUI_PTR_BIT (1U << (BUI_WORD_WIDTH-1))
#define BUI_WORD_MAX UINT_MAX

// problem when wors size > unsigned int ?
#define BUI_UINT_SIZE (sizeof(unsigned int) / sizeof(bui_word))
#define BUI_ULONG_SIZE (sizeof(unsigned long) / sizeof(bui_word))
#define BUI_ULONGLONG_SIZE (sizeof(unsigned long long) / sizeof(bui_word))

class biguint {
public:
  bui_word ptr; // either an int or a pointer ...

  friend bstreambuf &operator<<(bstreambuf &, biguint const &);
  friend bistream &operator>>(bistream &, biguint &);
public:
  /* =============================== */
  /* ========= CONSTRUCTORS ======== */
  /* =============================== */

  biguint();
  biguint(bui_word v);
  biguint(bui_dword v);

  template<class T>
  biguint(safe<T> v) { clone(v); }

  biguint(biguint const &src);
  biguint(bui_word v, bui_word d);
  biguint(bui_word *p);
  ~biguint();  

  /* =============================== */
  /* ======== ASSIGNMENT OPS ======= */
  /* =============================== */
  
  biguint const &operator=(bui_word v);
  biguint const &operator=(bui_dword v);
  biguint const &operator=(biguint const &src);

  void swap(biguint &v);

  /* =============================== */
  /* ======== COMPARISON OPS ======= */
  /* =============================== */

  bool operator==(bui_word v) const;
  bool operator==(bui_dword v) const;
  bool operator==(biguint const &v) const;

  bool operator!=(bui_word v) const;
  bool operator!=(bui_dword v) const;
  bool operator!=(biguint const &v) const;

  /* =============================== */
  /* ======== ARITHMETIC OPS ======= */
  /* =============================== */

  void operator+=(bui_word w);
  void operator+=(biguint const &src);
  void operator-=(bui_word w);
  void operator-=(biguint const &src);

  void operator*=(bui_word v);
  void operator*=(bui_dword v);
  void operator*=(biguint const &v);
  void operator/=(bui_word v);
  void operator%=(bui_word v);
  void operator^=(bui_word v);   

  biguint operator+(bui_word w) const;
  biguint operator+(biguint const &w) const;
  biguint operator-(bui_word w) const;
  biguint operator-(biguint const &w) const;

  biguint operator*(bui_word w) const;
  biguint operator*(bui_dword w) const;
  biguint operator*(biguint const &w) const;
  biguint operator/(bui_word w) const;
  bui_word operator%(bui_word w) const;
  biguint operator^(bui_word v) const;

  /* =============================== */
  /* ======== CONVERSION OPS ======= */
  /* =============================== */

  unsigned int c_uint() const;
  unsigned long c_ulong() const;
  bui_dword c_ulonglong() const;
  mpz_class get_mpz_t() const; // for the GMP library
  
  /* =============================== */
  /* ======== HELPER METHODS ======= */
  /* =============================== */
  
private:
  void destroy();
  void clone(bui_word w);
  void clone(bui_dword w);
  void clone(biguint const &w);
  void resize(bui_word ndepth);
  void expand(bui_word ndepth);
  bui_word *aligned_alloc(unsigned int c);

  void ripple_carry(bui_word level);
  void ripple_borrow(bui_word level);
};

/* ===================================== */
/* ======== OTHER USEFUL METHODS ======= */
/* ===================================== */

std::ostream& operator<<(std::ostream &out, biguint val);
bstreambuf &operator<<(bstreambuf &, biguint const &);
bistream &operator>>(bistream &, biguint &);
biguint pow(biguint const &r, unsigned int power);

// needed for interoperability with GMP
mpz_class operator*(mpz_class const &x, biguint const &y);

#include "safe_arithmetic.hpp"

#endif
