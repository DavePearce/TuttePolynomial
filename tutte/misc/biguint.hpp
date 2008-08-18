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

#define PACK(x) ((((bui_word)x) >> 1U) | BUI_PTR_BIT)
#define UNPACK(x) ((bui_word*)(x << 1U))

class biguint {
public:
  bui_word ptr; // either an int or a pointer ...

  friend bstreambuf &operator<<(bstreambuf &, biguint const &);
  friend bistream &operator>>(bistream &, biguint &);
public:
  /* =============================== */
  /* ========= CONSTRUCTORS ======== */
  /* =============================== */

  inline biguint() { ptr = 0U; }  
  inline biguint(bui_word v) { clone(v); }
  inline biguint(bui_dword v) { clone(v); }
  inline biguint(biguint const &src) { clone(src); }
  
  biguint(bui_word v, bui_word d);
  biguint(bui_word *p);
  inline ~biguint() { if(ptr & BUI_PTR_BIT) { free(UNPACK(ptr)); } }

  /* =============================== */
  /* ======== ASSIGNMENT OPS ======= */
  /* =============================== */
  
  inline biguint const &operator=(bui_word v) {
    if(ptr & BUI_PTR_BIT) { free(UNPACK(ptr)); }
    clone(v);
    return *this;
  }
  
  inline biguint const &operator=(bui_dword v) {
    if(ptr & BUI_PTR_BIT) { free(UNPACK(ptr)); };
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
	  unsigned int src_depth = s[0];
	  unsigned int depth = p[0];
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
  
  /* =============================== */
  /* ======== HELPER METHODS ======= */
  /* =============================== */
  
private:
  inline void clone(bui_word v) {
    if(v & BUI_PTR_BIT) {
      bui_word *p = aligned_alloc(3);
      ptr = PACK(p);
      p[0] = 1;
      p[1] = 0;
      p[2] = v;
    } else {
      ptr = v;
    }
  }

  inline void clone(bui_dword v) {
    bui_word *p = aligned_alloc(4);
    p[0] = 2;
    p[1] = 0;
    
    for(unsigned int i=2;i<=3;i++) {
      p[i] = (bui_word) v;
      v >>= BUI_WORD_WIDTH;
    }    
    ptr = PACK(p);
  }

  inline void clone(biguint const &src) {
    if(src.ptr & BUI_PTR_BIT) {
      bui_word *s = UNPACK(src.ptr);
      bui_word depth = s[0];
      bui_word padding = s[1];
      bui_word *p = aligned_alloc(depth+padding+2);
      memcpy(p,s,(padding+depth+2)*sizeof(bui_word));
      ptr = PACK(p);
    } else {
      ptr = src.ptr;
    }
  }

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
