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

// a type which is double the size of an unsigned int.
typedef unsigned long long d_unsigned_int;

// Width of unsigned int (in bits)
#define UINT_WIDTH (sizeof(unsigned int)*8U)
#define BUI_LEFTMOST_BIT (1U << (UINT_WIDTH-1))

#define BUI_UINT_SIZE 1
#define BUI_ULONG_SIZE (sizeof(unsigned long) / sizeof(unsigned int))
#define BUI_ULONGLONG_SIZE (sizeof(unsigned long long) / sizeof(unsigned int))

#define BUI_PACK(x) ((((unsigned int)x) >> 1U) | BUI_LEFTMOST_BIT)
#define BUI_UNPACK(x) ((unsigned int*)(x << 1U))

class biguint {
public:
  unsigned int ptr; // either an int or a pointer ...

  friend bstreambuf &operator<<(bstreambuf &, biguint const &);
  friend bistream &operator>>(bistream &, biguint &);
public:
  /* =============================== */
  /* ========= CONSTRUCTORS ======== */
  /* =============================== */

  inline biguint() { ptr = 0U; }  
  inline biguint(unsigned int v) { clone(v); }
  inline biguint(unsigned long v) { clone(v); }
  inline biguint(unsigned long long v) { clone(v); }
  inline biguint(biguint const &src) { clone(src); }
  
  biguint(unsigned int v, unsigned int d);
  biguint(unsigned int *p);
  inline ~biguint() { if(ptr & BUI_LEFTMOST_BIT) { free(BUI_UNPACK(ptr)); } }

  /* =============================== */
  /* ======== ASSIGNMENT OPS ======= */
  /* =============================== */
  
  inline biguint const &operator=(unsigned int v) {
    if(ptr & BUI_LEFTMOST_BIT) { free(BUI_UNPACK(ptr)); }
    clone(v);
    return *this;
  }
  
  inline biguint const &operator=(unsigned long v) {
    if(ptr & BUI_LEFTMOST_BIT) { free(BUI_UNPACK(ptr)); };
    clone(v);
    return *this;
  }

  inline biguint const &operator=(unsigned long long v) {
    if(ptr & BUI_LEFTMOST_BIT) { free(BUI_UNPACK(ptr)); };
    clone(v);
    return *this;
  }
  
  inline biguint const &operator=(biguint const &src) {    
    if(this != &src) {
      if(src.ptr & BUI_LEFTMOST_BIT) {
	if(ptr & BUI_LEFTMOST_BIT) {
	  unsigned int *s = BUI_UNPACK(src.ptr);
	  unsigned int *p = BUI_UNPACK(ptr);
	  // attempt to reuse memory where possible.
	  unsigned int src_depth = s[0];
	  unsigned int depth = p[0];
	  unsigned int padding = p[1];	
	  
	  if(src_depth <= (depth + padding)) {
	    memcpy(p,s,(src_depth+2)*sizeof(unsigned int));
	    memset(p+src_depth+2,0,((depth+padding)-src_depth)*sizeof(unsigned int));
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

  bool operator==(unsigned int v) const;
  bool operator==(unsigned long v) const;
  bool operator==(unsigned long long v) const;
  bool operator==(biguint const &v) const;

  bool operator!=(unsigned int v) const;
  bool operator!=(unsigned long v) const;
  bool operator!=(unsigned long long v) const;
  bool operator!=(biguint const &v) const;

  // need more here

  /* =============================== */
  /* ======== ARITHMETIC OPS ======= */
  /* =============================== */

  void operator+=(unsigned int w);
  void operator+=(biguint const &src);

  void operator-=(unsigned int w);
  void operator-=(biguint const &src);

  void operator*=(unsigned int v);
  void operator*=(unsigned long long v);
  void operator*=(biguint const &v);

  void operator/=(unsigned int v);
  void operator%=(unsigned int v);
  void operator^=(unsigned int v);   

  biguint operator+(unsigned int w) const;
  biguint operator+(biguint const &w) const;
  biguint operator-(unsigned int w) const;
  biguint operator-(biguint const &w) const;

  biguint operator*(unsigned int w) const;
  biguint operator*(unsigned long long w) const;
  biguint operator*(biguint const &w) const;
  biguint operator/(unsigned int w) const;
  unsigned int operator%(unsigned int w) const;
  biguint operator^(unsigned int v) const;

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
  inline void clone(unsigned int v) {
    if(v & BUI_LEFTMOST_BIT) {
      unsigned int *p = aligned_alloc(3);
      ptr = BUI_PACK(p);
      p[0] = 1;
      p[1] = 0;
      p[2] = v;
    } else {
      ptr = v;
    }
  }

  inline void clone(unsigned long v) {
    unsigned int *p = aligned_alloc(2 + sizeof(unsigned long));
    p[0] = 2;
    p[1] = 0;
    
    for(unsigned int i=2;i<=sizeof(unsigned long)+2;i++) {
      p[i] = (unsigned int) v;
      v >>= UINT_WIDTH;
    }    
    ptr = BUI_PACK(p);
  }

  inline void clone(unsigned long long v) {
    unsigned int *p = aligned_alloc(2 + sizeof(unsigned long long));
    p[0] = 2;
    p[1] = 0;
    
    for(unsigned int i=2;i<=sizeof(unsigned long long);i++) {
      p[i] = (unsigned int) v;
      v >>= UINT_WIDTH;
    }    
    ptr = BUI_PACK(p);
  }

  inline void clone(biguint const &src) {
    if(src.ptr & BUI_LEFTMOST_BIT) {
      unsigned int *s = BUI_UNPACK(src.ptr);
      unsigned int depth = s[0];
      unsigned int padding = s[1];
      unsigned int *p = aligned_alloc(depth+padding+2);
      memcpy(p,s,(padding+depth+2)*sizeof(unsigned int));
      ptr = BUI_PACK(p);
    } else {
      ptr = src.ptr;
    }
  }

  void expand(unsigned int ndepth);
  unsigned int *aligned_alloc(unsigned int c);

  void ripple_carry(unsigned int level);
  void ripple_borrow(unsigned int level);
};

/* ===================================== */
/* ======== OTHER USEFUL METHODS ======= */
/* ===================================== */

std::ostream& operator<<(std::ostream &out, biguint val);
bstreambuf &operator<<(bstreambuf &, biguint const &);
bistream &operator>>(bistream &, biguint &);
biguint pow(biguint const &r, unsigned int power);

#endif
