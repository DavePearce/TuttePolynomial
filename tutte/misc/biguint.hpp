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
#include "bstreambuf.hpp"
#include "bistream.hpp"

#include "../../config.h"

class biguint {
public:
  bigword word;

  friend bstreambuf &operator<<(bstreambuf &, biguint const &);
  friend bistream &operator>>(bistream &, biguint &);
public:
  /* =============================== */
  /* ========= CONSTRUCTORS ======== */
  /* =============================== */

  inline biguint() { ptr = 0U; }  
  inline biguint(int v) { clone(v); }  
  inline biguint(biguint const &src) { clone(src); }
  
  template<class T>
  biguint(safe<T> v) { clone(v); }

  biguint(int v, bui_word depth);
  biguint(bui_word *p);
  inline ~biguint() { if(ptr & BUI_PTR_BIT) { free(UNPACK(ptr)); } }

  /* =============================== */
  /* ======== ASSIGNMENT OPS ======= */
  /* =============================== */
  
  inline biguint const &operator=(int v) {
    if(ptr & BUI_PTR_BIT) { free(UNPACK(ptr)); }
    clone(v);
    return *this;
  }
  
  inline biguint const &operator=(biguint const &src) {    
    if(this != &src) {
      if(src.ptr & BUI_PTR_BIT) {
	if(ptr & BUI_PTR_BIT) {
	  bui_word *s = UNPACK(src.ptr);
	  bui_word *p = UNPACK(ptr);
	  // attempt to reuse memory where possible.
	  unsigned int src_depth = DEPTH(s[0]);
	  unsigned int depth = DEPTH(p[0]);
	  unsigned int padding = p[1];	
	  
	  if(src_depth <= (depth + padding)) {
	    memcpy(p,s,(src_depth+2)*sizeof(bui_word));
	    memset(p+src_depth+2,0,((depth+padding)-src_depth)*sizeof(bui_word));
	  } else {
	    free(UNPACK(ptr));
	    clone(src);
	  }
	} else {
	  clone(src);
	}	
      } else {
	if(ptr & BUI_PTR_BIT) { free(UNPACK(ptr)); };
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

  bool operator==(int v) const;
  bool operator==(biguint const &v) const;

  bool operator!=(int v) const;
  bool operator!=(biguint const &v) const;

  /* =============================== */
  /* ======== ARITHMETIC OPS ======= */
  /* =============================== */

  void operator+=(int w);
  void operator+=(biguint const &src);
  void operator-=(int w);
  void operator-=(biguint const &src);

  void operator*=(int v);
  void operator*=(biguint const &v);
  void operator/=(int v);
  void operator%=(int v);
  void operator^=(int v);   

  biguint operator+(int w) const;
  biguint operator+(biguint const &w) const;
  biguint operator-(int w) const;
  biguint operator-(biguint const &w) const;

  biguint operator*(int w) const;
  biguint operator*(biguint const &w) const;
  biguint operator/(int w) const;
  int operator%(int w) const;
  biguint operator^(int v) const;

  /* =============================== */
  /* ======== CONVERSION OPS ======= */
  /* =============================== */

  int c_int() const;
  long c_long() const;
  long long c_longlong() const;

  /* =============================== */
  /* ======== HELPER METHODS ======= */
  /* =============================== */
  
private:
  inline void clone(int v) {
    if((v < BUI_PTR_MIN) || (v > BUI_PTR_MAX)) {
      bui_word *p = aligned_alloc(3);
      ptr = PACK(p);
      p[0] = PACK_DEPTH(1,SIGN(v)); // convert to sign magnitude
      p[1] = 0;
      p[2] = ABS_UINT(v);
    } else {
      ptr = PACK_VALUE(v);
    }
  }

  inline void clone(biguint const &src) {
    if(src.ptr & BUI_PTR_BIT) {
      bui_word *s = UNPACK(src.ptr);
      bui_word depth = DEPTH(s[0]);
      bui_word padding = s[1];
      bui_word *p = aligned_alloc(depth+padding+2);
      memcpy(p,s,(padding+depth+2)*sizeof(bui_word));
      ptr = PACK(p);
    } else {
      ptr = src.ptr;
    }
  }

  void internal_add(bui_word *p, bui_word x);
  void internal_add(bui_word *p, bui_word *s);
  void internal_sub(bui_word *p, bui_word x);
  void internal_sub(bui_word *p, bui_word *s);
  int internal_cmp(bui_word *p, bui_word *s);

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

#endif
