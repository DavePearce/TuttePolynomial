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

#include "../../config.h"
#include "bstreambuf.hpp"
#include "bistream.hpp"

#if SIZEOF_LONG>4
#define BUI_64BIT_COMPILE
#endif

#ifdef BUI_64BIT_COMPILE

#define BUI_WORD_MAX ULONG_MAX
typedef unsigned long bui_word;

#else
#define BUI_WORD_MAX UINT_MAX
typedef unsigned int bui_word;
#endif

#define BUI_ONE ((bui_word)1U)
#define BUI_WORD_WIDTH (sizeof(bui_word)*8U)
#define BUI_LEFTMOST_BIT (BUI_ONE << (BUI_WORD_WIDTH-1))

#define BUI_UINT_SIZE 1
#define BUI_ULONG_SIZE (sizeof(unsigned long) / sizeof(bui_word))
#define BUI_ULONGLONG_SIZE (sizeof(unsigned long long) / sizeof(bui_word))

#define BUI_PACK(x) ((((bui_word)x) >> BUI_ONE) | BUI_LEFTMOST_BIT)
#define BUI_UNPACK(x) ((bui_word*)(x << BUI_ONE))

class biguint {
public:
  bui_word ptr; // either an bui_word or a bui_word* ...

  friend bstreambuf &operator<<(bstreambuf &, biguint const &);
  friend bistream &operator>>(bistream &, biguint &);

  /* =============================== */
  /* ========= CONSTRUCTORS ======== */
  /* =============================== */

private:
  biguint(bui_word v, bui_word d);

public:
  inline biguint() { ptr = 0U; }  
  inline biguint(bui_word v) { clone(v); }
  inline biguint(biguint const &src) { clone(src); }  
  inline ~biguint() { if(ptr & BUI_LEFTMOST_BIT) { free(BUI_UNPACK(ptr)); } }


  /* =============================== */
  /* ======== ASSIGNMENT OPS ======= */
  /* =============================== */
  
  inline biguint const &operator=(bui_word v) {
    if(ptr & BUI_LEFTMOST_BIT) { free(BUI_UNPACK(ptr)); }
    clone(v);
    return *this;
  }
  
  inline biguint const &operator=(biguint const &src) {    
    if(this != &src) {
      if(src.ptr & BUI_LEFTMOST_BIT) {
	if(ptr & BUI_LEFTMOST_BIT) {
	  bui_word *s = BUI_UNPACK(src.ptr);
	  bui_word *p = BUI_UNPACK(ptr);
	  // attempt to reuse memory where possible.
	  bui_word src_depth = s[0];
	  bui_word depth = p[0];
	  bui_word padding = p[1];	
	  
	  if(src_depth <= (depth + padding)) {
	    memcpy(p,s,(src_depth+2)*sizeof(bui_word));
	    memset(p+src_depth+2,0,((depth+padding)-src_depth)*sizeof(bui_word));
	  } else {
	    free(BUI_UNPACK(ptr));
	    clone(src);
	  }
	} else {
	  clone(src);
	}	
      } else {
	if(ptr & BUI_LEFTMOST_BIT) { free(BUI_UNPACK(ptr)); };
	ptr = src.ptr;
      }
    }
    return *this;
  }

  inline void swap(biguint &src) {
    std::swap(ptr,src.ptr);
  }

  /* =============================== */
  /* ======== COMPARISON OPS ======= */
  /* =============================== */

  bool operator==(bui_word v) const;
  bool operator==(biguint const &v) const;

  bool operator!=(bui_word v) const;
  bool operator!=(biguint const &v) const;

  bool operator<(bui_word v) const;
  bool operator<(biguint const &v) const;

  bool operator<=(bui_word v) const;
  bool operator<=(biguint const &v) const;

  bool operator>(bui_word v) const;
  bool operator>(biguint const &v) const;

  bool operator>=(bui_word v) const;
  bool operator>=(biguint const &v) const;

  /* =============================== */
  /* ======== ARITHMETIC OPS ======= */
  /* =============================== */

  void operator+=(bui_word w);
  void operator+=(biguint const &src);

  void operator-=(bui_word w);
  void operator-=(biguint const &src);

  void operator*=(bui_word v);
  void operator*=(biguint const &v);

  void operator/=(bui_word v);
  void operator%=(bui_word v);
  void operator^=(bui_word v);   

  biguint operator+(bui_word w) const;
  biguint operator+(biguint const &w) const;
  biguint operator-(bui_word w) const;
  biguint operator-(biguint const &w) const;

  biguint operator*(bui_word w) const;
  biguint operator*(biguint const &w) const;
  biguint operator/(bui_word w) const;
  bui_word operator%(bui_word w) const;
  biguint operator^(bui_word v) const;

  /* =============================== */
  /* ======== CONVERSION OPS ======= */
  /* =============================== */

  unsigned int c_uint() const;
  unsigned long c_ulong() const;
  unsigned long long c_ulonglong() const;
  
  /* =============================== */
  /* ======== HELPER METHODS ======= */
  /* =============================== */
  
private:
  inline void clone(bui_word v) {
    if(v & BUI_LEFTMOST_BIT) {
      bui_word *p = aligned_alloc(3);
      ptr = BUI_PACK(p);
      p[0] = 1;
      p[1] = 0;
      p[2] = v;
    } else {
      ptr = v;
    }
  }

  inline void clone(biguint const &src) {
    if(src.ptr & BUI_LEFTMOST_BIT) {
      bui_word *s = BUI_UNPACK(src.ptr);
      bui_word depth = s[0];
      bui_word padding = s[1];
      bui_word *p = aligned_alloc(depth+padding+2);
      memcpy(p,s,(padding+depth+2)*sizeof(bui_word));
      ptr = BUI_PACK(p);
    } else {
      ptr = src.ptr;
    }
  }

  void expand(bui_word ndepth);
  bui_word *aligned_alloc(bui_word c);

  void ripple_carry(bui_word level);
  void ripple_borrow(bui_word level);
};

/* ===================================== */
/* ======== OTHER USEFUL METHODS ======= */
/* ===================================== */

std::ostream& operator<<(std::ostream &out, biguint val);
bstreambuf &operator<<(bstreambuf &, biguint const &);
bistream &operator>>(bistream &, biguint &);
biguint pow(biguint const &r, bui_word power);

#endif
