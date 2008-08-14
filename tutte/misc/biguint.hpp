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

template<class T>
class safe; // forward declaration

// this class provides arbitrary sized integers
typedef unsigned int bui_word;
typedef unsigned long long bui_dword;

#define BUI_WORD_WIDTH (SIZEOF_INT*8U)
#define BUI_PTR_BIT (1U << (BUI_WORD_WIDTH-1))
#define BUI_PTR_MAX ((int) (((unsigned int) -1) >> 2U))
#define BUI_PTR_MIN ((int) ((((unsigned int) -1) >> 2U) | BUI_PTR_BIT)+1)

#define BUI_WORD_MAX UINT_MAX

#define PACK(x) ((((bui_word)x) >> 1U) | BUI_PTR_BIT)
#define UNPACK(x) ((bui_word*)(x << 1U))
#define SIGN(x) ((x&BUI_PTR_BIT) == BUI_PTR_BIT)
#define SIGN_EXTEND(x) (((int)(x << 1U)) >> 1)
#define DEPTH(x) (x&~BUI_PTR_BIT)
#define PACK_DEPTH(x,y) (y ? (x|BUI_PTR_BIT) : x)
#define PACK_VALUE(x) (x&~BUI_PTR_BIT)
#define ABS_UINT(x) ((x == INT_MIN) ? ((unsigned int)INT_MAX)+1: abs(x))

class biguint {
public:
  // ptr is either a 31-bit int, or a pointer to an array of bui_words
  // :. to comparse ptr against another int, it must be first sign-
  // extended.  Note, on a 64-bit machine, it's a 63-bit int etc.
  //
  // when in array mode, we are using sign magnitude representation,
  // as follows:
  //
  // index :          0          |   1     | ...
  // value : highest bit is sign | padding | number bits (as unsigned int)
  //         remainder is length
  //
  bui_word ptr; 

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

#include "safe_arithmetic.hpp"

#endif
