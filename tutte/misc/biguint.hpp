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
#include <stdint.h>

#include "../../config.h"
#include "bstreambuf.hpp"
#include "bistream.hpp"

#ifndef UINT32_MAX
#define UINT32_MAX UINT_MAX
#endif

#ifndef UINT32_C
#define UINT32_C(x) ((uint32_t)x)
#endif

#if SIZEOF_UNSIGNED_INT_P==4
#define BUI_LEFTMOST_BIT (1U << 31U)
typedef uint32_t uint32_ptr_t;

#elif SIZEOF_UNSIGNED_INT_P==8
typedef uint64_t uint32_ptr_t;
#define BUI_LEFTMOST_BIT (((uint64_t)1U) << 63U)

#else
#error "sizeof(int*) is neither 32bit or 64bit."
#endif

#define BUI_PACK(x) ((((uint32_ptr_t)x) >> 1U) | BUI_LEFTMOST_BIT)
#define BUI_UNPACK(x) ((uint32_t*)(x << 1U))


class biguint {
public:
  uint32_ptr_t ptr;

  friend bstreambuf &operator<<(bstreambuf &, biguint const &);
  friend bistream &operator>>(bistream &, biguint &);

  /* =============================== */
  /* ========= CONSTRUCTORS ======== */
  /* =============================== */

private:
  biguint(uint32_t v, uint32_t d);

public:
  inline biguint() { ptr = 0U; }  
  inline biguint(uint32_t v) { clone(v); }
  inline biguint(uint64_t v) { clone(v); }
  inline biguint(biguint const &src) { clone(src); }  
  inline ~biguint() { if(ptr & BUI_LEFTMOST_BIT) { free(BUI_UNPACK(ptr)); } }


  /* =============================== */
  /* ======== ASSIGNMENT OPS ======= */
  /* =============================== */
  
  inline biguint const &operator=(uint32_t v) {
    if(ptr & BUI_LEFTMOST_BIT) { free(BUI_UNPACK(ptr)); }
    clone(v);
    return *this;
  }
  
  inline biguint const &operator=(uint64_t v) {
    if(ptr & BUI_LEFTMOST_BIT) { free(BUI_UNPACK(ptr)); }
    clone(v);
    return *this;
  }
  
  inline biguint const &operator=(biguint const &src) {    
    if(this != &src) {
      if(src.ptr & BUI_LEFTMOST_BIT) {
	if(ptr & BUI_LEFTMOST_BIT) {
	  uint32_t *s = BUI_UNPACK(src.ptr);
	  uint32_t *p = BUI_UNPACK(ptr);
	  // attempt to reuse memory where possible.
	  uint32_t src_depth = s[0];
	  uint32_t depth = p[0];
	  uint32_t padding = p[1];	
	  	  
	  if(src_depth <= (depth + padding)) {
	    p[0] = src_depth;
	    p[1] = (depth+padding) - src_depth;
	    memcpy(p+2,s+2,(src_depth)*sizeof(uint32_t));
	    memset(p+src_depth+2,0,((depth+padding)-src_depth)*sizeof(uint32_t));
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

  bool operator==(uint32_t v) const;
  bool operator==(uint64_t v) const;
  bool operator==(biguint const &v) const;

  bool operator!=(uint32_t v) const;
  bool operator!=(uint64_t v) const;
  bool operator!=(biguint const &v) const;

  bool operator<(uint32_t v) const;
  bool operator<(uint64_t v) const;
  bool operator<(biguint const &v) const;

  bool operator<=(uint32_t v) const;
  bool operator<=(uint64_t v) const;
  bool operator<=(biguint const &v) const;

  bool operator>(uint32_t v) const;
  bool operator>(uint64_t v) const;
  bool operator>(biguint const &v) const;

  bool operator>=(uint32_t v) const;
  bool operator>=(uint64_t v) const;
  bool operator>=(biguint const &v) const;

  /* =============================== */
  /* ======== ARITHMETIC OPS ======= */
  /* =============================== */

  void operator+=(uint32_t w);
  void operator+=(biguint const &src);

  void operator-=(uint32_t w);
  void operator-=(biguint const &src);

  void operator*=(uint32_t v);
  void operator*=(biguint const &v);

  void operator/=(uint32_t v);
  void operator%=(uint32_t v);
  void operator^=(uint32_t v);   

  biguint operator+(uint32_t w) const;
  biguint operator+(biguint const &w) const;
  biguint operator-(uint32_t w) const;
  biguint operator-(biguint const &w) const;

  biguint operator*(uint32_t w) const;
  biguint operator*(biguint const &w) const;
  biguint operator/(uint32_t w) const;
  uint32_t operator%(uint32_t w) const;
  biguint operator^(uint32_t v) const;

  /* =============================== */
  /* ======== CONVERSION OPS ======= */
  /* =============================== */

  uint32_t c_uint32() const;
  uint64_t c_uint64() const;
  
  /* =============================== */
  /* ======== HELPER METHODS ======= */
  /* =============================== */
  
private:
  inline void clone(uint32_t v) {
    if(v & BUI_LEFTMOST_BIT) {
      uint32_t *p = aligned_alloc(3);
      ptr = BUI_PACK(p);
      p[0] = 1;
      p[1] = 0;
      p[2] = v;
    } else {
      ptr = v;
    }
  }

  inline void clone(uint64_t v) {
    if(v >= BUI_LEFTMOST_BIT) {
      uint32_t *p = aligned_alloc(4);
      ptr = BUI_PACK(p);
      p[0] = 2;
      p[1] = 0;
      p[2] = v;
      p[3] = v >> 32U;
    } else {
      ptr = v;
    }
  }

  inline void clone(biguint const &src) {
    if(src.ptr & BUI_LEFTMOST_BIT) {
      uint32_t *s = BUI_UNPACK(src.ptr);
      uint32_t depth = s[0];
      uint32_t padding = s[1];
      uint32_t *p = aligned_alloc(depth+padding+2);
      memcpy(p,s,(padding+depth+2)*sizeof(uint32_t));
      ptr = BUI_PACK(p);
    } else {
      ptr = src.ptr;
    }
  }

  void expand(uint32_t ndepth);
  uint32_t *aligned_alloc(uint32_t c);

  void ripple_carry(uint32_t level);
  void ripple_borrow(uint32_t level);
};

/* ===================================== */
/* ======== OTHER USEFUL METHODS ======= */
/* ===================================== */

std::ostream& operator<<(std::ostream &out, biguint val);
bstreambuf &operator<<(bstreambuf &, biguint const &);
bistream &operator>>(bistream &, biguint &);
biguint pow(biguint const &r, uint32_t power);

#endif
