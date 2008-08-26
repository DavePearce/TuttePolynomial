// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#include <cstring> // for memcpy
#include <stdexcept>

#include "biguint.hpp"

using namespace std;

/**
 * the following is needed for * and / operators
 */

#if BUI_64BIT_COMPILE

typedef struct { bui_word high; bui_word low; } bui_dword;

#define BUI_HIGH_MASK (BUI_WORD_MAX << (BUI_WORD_WIDTH/2))
#define BUI_DWORD(x,y) bui_dword(x,y)
#define BUI_DWORD_LOW(x) (x.low)
#define BUI_DWORD_HIGH(x) (x.high)
#define BUI_DWORD_MUL(x,y) bui_dword_mul(x,y)
#define BUI_DWORD_ADD(x,y) bui_dword_add(x,y)

bui_dword bui_dword_add(bui_dword r, bui_word y) {
  r.low += y;
  if(r.low < low) { r.high++; } // overflow
  return r;
}

bui_dword bui_dword_mul(bui_word x, bui_word y) {
  bui_word lx = (x & BUI_HIGH_MASK) >> (BUI_WORD_WIDTH/2);
  bui_word ly = (y & BUI_HIGH_MASK) >> (BUI_WORD_WIDTH/2);
  bui_word hx = x >> (BUI_WORD_WIDTH/2);
  bui_word hy = y >> (BUI_WORD_WIDTH/2);
  
  bui_word low = lx * ly;
  bui_word high = hx * hy;
  bui_word lxhy = lx * hy;
  bui_word hxly = hx * ly;

  bui_dword r;
  r.low = low;
  r.high = high;
  
  r.low += (lxhy) << (BUI_WORD_WITH/2);
  if(r.low < low) { r.high++; } // overflow
  r.low += (hxly) << (BUI_WORD_WITH/2);
  if(r.low < low) { r.high++; } // overflow

  r.high += lxhy >> (BUI_WORD_WIDTH/2);
  r.high += hxly >> (BUI_WORD_WIDTH/2);

  return r;
}

#else

typedef unsigned long long bui_dword;
#define BUI_DWORD(x,y) ((((bui_dword) x)<<BUI_WORD_WIDTH)+y)
#define BUI_DWORD_LOW(x) ((bui_word) x)
#define BUI_DWORD_HIGH(x) ((bui_word)(x>>BUI_WORD_WIDTH))
#define BUI_DWORD_MUL(x,y) (((bui_dword)x)*y)
#define BUI_DWORD_ADD(x,y) (((bui_dword)x)+y)
#define BUI_DWORD_DIV(x,y) (((bui_dword)x)/y)
#define BUI_DWORD_MOD(x,y) (((bui_dword)x)%y)

#endif

/* =============================== */
/* ========= CONSTRUCTORS ======== */
/* =============================== */

biguint::biguint(bui_word v, bui_word depth) { 
  bui_word padding = depth*2;
  bui_word *p = aligned_alloc(depth+padding+2);
  p[0]=depth;
  p[1]=padding;
  memset(p+2,0,(depth+padding)*sizeof(bui_word));
  p[2]=v;
  ptr = BUI_PACK(p);
}

/* =============================== */
/* ======== ASSIGNMENT OPS ======= */
/* =============================== */
  
/* =============================== */
/* ======== COMPARISON OPS ======= */
/* =============================== */

bool biguint::operator==(bui_word v) const {
  if(ptr & BUI_LEFTMOST_BIT) {    
    bui_word *p = BUI_UNPACK(ptr);
    if(p[2] != v) { return false; }
    bui_word depth(p[0]);
    for(bui_word i=3;i<(depth+2);++i) {
      if(p[i] != 0) { return false; }
    }
    return true;
  } else {
    return ptr == v;
  } 
}

bool biguint::operator==(biguint const &v) const {
  if((ptr & BUI_LEFTMOST_BIT) == 0) {
    return v == ptr;
  } else if((v.ptr & BUI_LEFTMOST_BIT) == 0) {
    return (*this) == v.ptr;
  } else {
    bui_word *p(BUI_UNPACK(ptr));
    bui_word *s(BUI_UNPACK(v.ptr));
    bui_word depth(std::min(p[0],s[0]));
    for(bui_word i=2;i<(depth+2);i++) {
      if(p[i] != s[i]) { return false; }
    }
    // now, check remaining digits are zero.    
    bui_word m_depth(p[0]);
    for(bui_word i=depth+2;i<(m_depth+2);++i) {
      if(p[i] != 0) { return false; }
    }
    bui_word v_depth(s[0]);
    for(bui_word i=depth+2;i<(v_depth+2);++i) {
      if(s[i] != 0) { return false; }
    }      
  }
  return true;
}

bool biguint::operator!=(bui_word v) const { return !((*this) == v); }
bool biguint::operator!=(biguint const &v) const { return !((*this) == v); }

bool biguint::operator<(bui_word v) const {
  if(ptr & BUI_LEFTMOST_BIT) {    
    bui_word *p = BUI_UNPACK(ptr);
    if(p[2] >= v) { return false; }
    bui_word depth(p[0]);
    for(bui_word i=3;i<(depth+2);++i) {
      if(p[i] != 0) { return false; }
    }
    return true;
  } else {
    return ptr < v;
  } 
}

bool biguint::operator<(biguint const &v) const {
  if((ptr & BUI_LEFTMOST_BIT) == 0) {
    if((v.ptr & BUI_LEFTMOST_BIT) == 0) {      
      return ptr < v.ptr;
    } else {
      return !(v <= ptr);
    }
  } else if((v.ptr & BUI_LEFTMOST_BIT) == 0) {
    return (*this < v.ptr);
  }
  
  bui_word *p = BUI_UNPACK(ptr);
  bui_word *s = BUI_UNPACK(v.ptr);

  bui_word depth_p(p[0]);
  bui_word depth_s(s[0]);
  bui_word depth(max(depth_s,depth_p));

  depth_p += 2;
  depth_s += 2;

  for(bui_word i(depth+1);i>1;--i) {
    if(i >= depth_p) {
      if(s[i] != 0) {
	return true;
      }
    } else if(i >= depth_s) {
      if(p[i] != 0) {
	return false;
      }
    } else {
      bui_word sw = s[i];
      bui_word pw = p[i];
      
      if(sw < pw) {
	return false;
      } else if(pw < sw) {
	return true;
      }
    }
  }

  // here, they are equal
  return false;
}

bool biguint::operator<=(bui_word v) const {
  if(ptr & BUI_LEFTMOST_BIT) {    
    bui_word *p = BUI_UNPACK(ptr);
    if(p[2] > v) { return false; }
    bui_word depth(p[0]);
    for(bui_word i=3;i<(depth+2);++i) {
      if(p[i] != 0) { return false; }
    }
    return true;
  } else {
    return ptr <= v;
  } 
}

bool biguint::operator<=(biguint const &v) const {
  if((ptr & BUI_LEFTMOST_BIT) == 0) {
    if((v.ptr & BUI_LEFTMOST_BIT) == 0) {
      return ptr <= v.ptr;
    } else {
      return !(v < ptr);
    }
  } else if((v.ptr & BUI_LEFTMOST_BIT) == 0) {
    return (*this <= v.ptr);
  }
  
  bui_word *p = BUI_UNPACK(ptr);
  bui_word *s = BUI_UNPACK(v.ptr);

  bui_word depth_p(p[0]);
  bui_word depth_s(s[0]);
  bui_word depth(max(depth_s,depth_p));

  depth_p += 2;
  depth_s += 2;

  for(bui_word i(depth+1);i>1;--i) {
    if(i >= depth_p) {
      if(s[i] != 0) {
	return true;
      }
    } else  if(i >= depth_s) {
      if(p[i] != 0) {
	return false;
      }
    } else {
      bui_word sw = s[i];
      bui_word pw = p[i];
      
      if(sw < pw) {
	return false;
      } else if(pw < sw) {
	return true;
      }
    }
  }

  // here, they are equal
  return true;
}

bool biguint::operator>(bui_word v) const { return !(*this <= v); }
bool biguint::operator>(biguint const &v) const { return !(*this <= v); }

bool biguint::operator>=(bui_word v) const { return !(*this < v); }
bool biguint::operator>=(biguint const &v) const { return !(*this < v); }

/* =============================== */
/* ======== ARITHMETIC OPS ======= */
/* =============================== */

void biguint::operator+=(bui_word w) {
  if(ptr & BUI_LEFTMOST_BIT) {    
    bui_word *p(BUI_UNPACK(ptr));
    bui_word v = p[2];
    w = v + w;
    p[2] = w;
    if(w < v) { ripple_carry(1); }
  } else {
    bui_word v = ptr;
    ptr = v + w;
    if(ptr < v) {
      bui_word *p = aligned_alloc(4); 
      p[0] = 2U;
      p[1] = 0;
      p[2] = ptr;
      p[3] = 1U;
      ptr = BUI_PACK(p);
    } else if(ptr & BUI_LEFTMOST_BIT) {
      clone(ptr);
    }
  }
}

void biguint::operator+=(biguint const &src) {
  if((src.ptr & BUI_LEFTMOST_BIT) == 0) { 
    (*this) += src.ptr; 
  } else {
    bui_word *s(BUI_UNPACK(src.ptr));
    bui_word depth = s[0];
    bui_word *p;
    
    if((ptr & BUI_LEFTMOST_BIT) == 0) { 
      // assume it needs to go big
      p = aligned_alloc(depth+2);
      p[0] = depth;      
      p[1] = 0;
      p[2] = ptr;
      for(int i=3;i<(depth+2);++i) { p[i] = 0U; }
      ptr = BUI_PACK(p);
    } else {
      expand(depth);
      p = BUI_UNPACK(ptr);
    }

    bui_word carry = 0;
    
    for(bui_word i=2;i<(depth+2);++i) {
      bui_word v = p[i];
      bui_word w = s[i];
      
      w = v + w + carry;   
      p[i] = w;
      
      if(carry == 0) {
	carry = w < v ? 1 : 0;
      } else {
	carry = w <= v ? 1 : 0;
      }
    }
    if(carry == 1) { ripple_carry(depth); }
  }   
}

biguint biguint::operator+(biguint const &w) const {
  biguint r(*this);
  r += w;
  return r;
}

biguint biguint::operator+(bui_word w) const {
  biguint r(*this);
  r += w;
  return r;
}

void biguint::operator-=(bui_word w) {
  if(ptr & BUI_LEFTMOST_BIT) {    
    bui_word *p(BUI_UNPACK(ptr));
    bui_word v = p[2];
    p[2] = v - w;
    if(v < w) { ripple_borrow(1); }
  } else {
    bui_word v(ptr);
    ptr = v - w;
    if(v < w) { throw std::runtime_error("biguint cannot go negative"); }
  }
}

void biguint::operator-=(biguint const &src) {
  if((src.ptr & BUI_LEFTMOST_BIT) == 0) { 
    (*this) -= src.ptr; 
  } else {
    bui_word *s(BUI_UNPACK(src.ptr));
    bui_word depth = s[0];
    bui_word *p;
    
    if((ptr & BUI_LEFTMOST_BIT) == 0) { 
      // assume it needs to go big
      p = aligned_alloc(depth+2);
      p[0] = depth;      
      p[1] = depth;      
      p[2] = ptr;
      for(int i=3;i<(depth+2);++i) { p[i] = 0U; }
      ptr = BUI_PACK(p);
    } else {
      expand(depth);
      p = BUI_UNPACK(ptr);
    }

    bui_word borrow = 0;

    for(bui_word i=2;i<(depth+2);++i) {
      bui_word v = p[i];
      bui_word w = s[i];
      bui_word r = v - w - borrow;    
      p[i] = r;
      
      if(borrow == 0) {
	borrow = v < w ? 1 : 0;
      } else {
	borrow = v <= w ? 1 : 0;
      }
    }
    
    if(borrow == 1) { ripple_borrow(depth); }
  }
}

biguint biguint::operator-(biguint const &w) const {
  biguint r(*this);
  r -= w;
  return r;
}

biguint biguint::operator-(bui_word w) const {
  biguint r(*this);
  r -= w;
  return r;
}

void biguint::operator*=(bui_word v) {
  if(ptr & BUI_LEFTMOST_BIT) {    
    // complicated case!
    bui_word *p(BUI_UNPACK(ptr));
    bui_word depth(p[0]);
    bui_word overflow = 0;

    for(bui_word i=2;i<(depth+2);++i) {
      bui_dword w = BUI_DWORD_MUL(p[i],v);
      w = BUI_DWORD_ADD(w,overflow);
      p[i] = BUI_DWORD_LOW(w);
      overflow = BUI_DWORD_HIGH(w);
    }
    
    if(overflow > 0) {
      // need additional space
      expand(depth+1);   
      p = BUI_UNPACK(ptr); 
      p[depth+2] = overflow;
    }
  } else {    
    // easier case!
    bui_dword w = BUI_DWORD_MUL(ptr,v);
    if(BUI_DWORD_HIGH(w) > 0 || BUI_DWORD_LOW(w) >= BUI_LEFTMOST_BIT) { 
      // build new object
      bui_word *p = aligned_alloc(4);
      ptr = BUI_PACK(p);
      p[0] = 2U;
      p[1] = 0;
      p[2] = BUI_DWORD_LOW(w);
      p[3] = BUI_DWORD_HIGH(w);
    } else {
      ptr = BUI_DWORD_LOW(w);
    }
  }
}

void biguint::operator*=(biguint const &src) {
  // this could probably be optimised ...
  if((src.ptr & BUI_LEFTMOST_BIT) == 0) { 
    (*this) *= src.ptr; 
  } else if((ptr & BUI_LEFTMOST_BIT) == 0) {
    // could be optimised a little?
    biguint ans(src);
    ans *= ptr;
    swap(ans);
  } else {
    bui_word *s(BUI_UNPACK(src.ptr));
    bui_word depth = s[0];
    biguint ans(0U,depth);

    for(bui_word j=0;j<depth;++j) {
      biguint tmp(*this);
      tmp *= s[j+2];

      bui_word *tp(BUI_UNPACK(tmp.ptr));      
      bui_word t_depth(tp[0]);
      bui_word carry = 0;

      ans.expand(j + t_depth); 

      bui_word *ap(BUI_UNPACK(ans.ptr));      

      // standard add, although slightly modified
      // to give the base shift for free.
      for(bui_word i=0;i!=t_depth;++i) {
	bui_word v = ap[j+i+2];
	bui_word w = tp[i+2];
	
	w = v + w + carry;   
	ap[j+i+2] = w;

	if(carry == 0) { carry = w < v ? 1 : 0; } 
	else { carry = w <= v ? 1 : 0; }
      }

      if(carry == 1) { ans.ripple_carry(t_depth+j); }     
    }
    swap(ans);
  }
}

biguint biguint::operator*(bui_word w) const {
  biguint r(*this);
  r *= w;
  return r;
}

biguint biguint::operator*(biguint const &src) const {
  if((src.ptr & BUI_LEFTMOST_BIT) == 0) { return (*this) * src.ptr; }
  else if((ptr & BUI_LEFTMOST_BIT) == 0) { return src * ptr; }
  else {
    bui_word *s(BUI_UNPACK(src.ptr));
    bui_word depth = s[0];
    biguint ans(0U,depth);

    for(bui_word j=0;j<depth;++j) {
      biguint tmp(*this);
      tmp *= s[j+2];
      
      bui_word *tp(BUI_UNPACK(tmp.ptr));      
      bui_word t_depth(tp[0]);
      bui_word carry = 0;
      
      ans.expand(j + t_depth); 
      bui_word *ap(BUI_UNPACK(ans.ptr));      

      // standard add, although slightly modified
      // to give the base shift for free.
      for(bui_word i=0;i!=t_depth;++i) {
	bui_word v = ap[j+i+2];
	bui_word w = tp[i+2];

	w = v + w + carry;   
	ap[j+i+2] = w;
	
	if(carry == 0) { carry = w < v ? 1 : 0; }
	else { carry = w <= v ? 1 : 0; }
      }
      
      if(carry == 1) { ans.ripple_carry(t_depth+j); }     
    }
    return ans;
  }
}

void biguint::operator/=(bui_word v) {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  if(ptr & BUI_LEFTMOST_BIT) {
    bui_word *p(BUI_UNPACK(ptr));
    bui_word remainder=0;
    
    for(bui_word i=p[0]+1;i>1;--i) {
      bui_dword w = BUI_DWORD(remainder,p[i]);
      p[i] = BUI_DWORD_DIV(w,v);
      remainder = BUI_DWORD_MOD(w,v);
    }    
  } else {
    // real easy!
    ptr = ptr / v;
  }
}

biguint biguint::operator/(bui_word w) const {
  biguint r(*this);
  r /= w;
  return r;
}

void biguint::operator%=(bui_word v) {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  if(ptr & BUI_LEFTMOST_BIT) {
    bui_word *p(BUI_UNPACK(ptr));
    bui_word remainder=0;
    
    for(bui_word i=p[0]+1;i>1;--i) {
      bui_dword w = BUI_DWORD(remainder,p[i]);
      remainder = BUI_DWORD_MOD(w,v);
    }    
    clone(remainder);
  } else {
    ptr = ptr % v;
  }
}

bui_word biguint::operator%(bui_word v) const {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  if(ptr & BUI_LEFTMOST_BIT) {
    bui_word *p(BUI_UNPACK(ptr));
    bui_word remainder=0;
  
   for(bui_word i=p[0]+1;i>1;--i) {
     bui_dword w = BUI_DWORD(remainder,p[i]);
     remainder = BUI_DWORD_MOD(w,v);
   }     
   return remainder;
  } else {
    return ptr % v;
  }
}

void biguint::operator^=(bui_word v) {
  if(v == 0) { (*this) = 1U; }
  else {
    biguint p(*this);
    
    for(bui_word i=1;i<v;++i) {
      (*this) *= p;
    }
  }
}

biguint biguint::operator^(bui_word v) const {
  biguint r(*this);
  r ^= v;
  return r;
}

/* =============================== */
/* ======== CONVERSION OPS ======= */
/* =============================== */

unsigned int biguint::c_uint() const {
  if(ptr & BUI_LEFTMOST_BIT) {
    bui_word *p(BUI_UNPACK(ptr));
    if(p[0] > BUI_UINT_SIZE) { throw runtime_error("biguint too large for unsigned int"); }
    return p[2];
  } else {
    return ptr;
  }
}  

unsigned long biguint::c_ulong() const {
  if(ptr & BUI_LEFTMOST_BIT) {
    bui_word *p(BUI_UNPACK(ptr));
    if(p[0] > BUI_ULONG_SIZE) { throw runtime_error("biguint too large for unsigned long"); }
    return p[2];
  } else {
    return ptr;
  }
}  

unsigned long long biguint::c_ulonglong() const {
  if(ptr & BUI_LEFTMOST_BIT) {
    bui_word *p(BUI_UNPACK(ptr));
    bui_word depth = p[0];
    if(depth > BUI_ULONGLONG_SIZE) { throw runtime_error("biguint too large for unsigned long long"); }
    unsigned long long r=0;
    for(bui_word i=depth+1;i>1;--i) {
      r <<= BUI_WORD_WIDTH;
      r += p[i];
    }
    return r;
  } else {
    return ptr;
  }
}  

/* =============================== */
/* ======== HELPER METHODS ======= */
/* =============================== */

// Expands the array to depth ndepth.  If ndepth < current depth,
// nothing happens.  
//
// PRE: assumes this in array format
void biguint::expand(bui_word ndepth) {
  bui_word *p(BUI_UNPACK(ptr));
  bui_word depth = p[0];
  bui_word padding = p[1];
  if(depth >= ndepth) { return; }
  else if((depth+padding) >= ndepth) {
    // no need to expand as we have space in the padding
    p[0] = ndepth;
    p[1] = (depth+padding)-ndepth;
  } else {
    bui_word *nptr = aligned_alloc((ndepth*2)+2);
    nptr[0]=ndepth;
    nptr[1]=ndepth;
    memset(nptr+depth+2,0,((ndepth*2)-depth)*sizeof(bui_word));
    memcpy(nptr+2,p+2,depth*sizeof(bui_word));
    free(p);
    ptr = BUI_PACK(nptr);
  }
}

void biguint::ripple_carry(bui_word level) {
  bui_word *p(BUI_UNPACK(ptr));
  bui_word depth(p[0]);

  for(bui_word i(level+2);i<(depth+2);++i) {
    bui_word v = p[i];
    
    if(v == BUI_WORD_MAX) { p[i] = 0; } 
    else {
      p[i] = v + 1;
      return;
    }	
  }
  // not enough space to hold answer!
  expand(depth+1);
  BUI_UNPACK(ptr)[depth+2]=1U;  
}

void biguint::ripple_borrow(bui_word level) {  
  bui_word *p(BUI_UNPACK(ptr));
  bui_word depth = p[0];
  for(bui_word i(level+2);i<(depth+2);++i) {
    bui_word v = p[i];
    if(v == 0) {
      p[i] = BUI_WORD_MAX;
    } else {
      p[i] = v - 1;
      return;
    }	
  }    
  // this is a negative number!
  throw std::runtime_error("biguint cannot go negative"); 
}

bui_word *biguint::aligned_alloc(bui_word c) {
  bui_word *p = (bui_word*) malloc(c * sizeof(bui_word));  
  if(p == NULL) { throw std::bad_alloc(); }
  if(((bui_word)p) & 1) { throw std::runtime_error("Allocated memory not aligned!"); }
  return p;
}

/* =============================== */
/* ======== FRIEND METHODS ======= */
/* =============================== */

std::ostream& operator<<(ostream &out, biguint val) {
  std::string r;

  if(val == 0U) { return out << "0"; }
  
  while(val != 0U) {
    bui_word digit = val % 10;
    char d = digit + '0'; // YUK
    r = d + r;
    val = val / 10;
  }

  return out << r;
}

biguint pow(biguint const &r, bui_word power) {
  return r ^ power;
}

bstreambuf &operator<<(bstreambuf &bout, biguint const &src) {
  if(src.ptr & BUI_LEFTMOST_BIT) {
    bui_word *s(BUI_UNPACK(src.ptr));
    bui_word depth(s[0]);
    
    bout << depth;
    for(bui_word i=2;i<(depth+2);++i) { bout << s[i]; }
  } else {
    bout << 1U << src.ptr;
  }
}

bistream &operator>>(bistream &bin, biguint &src) {  
  bui_word depth;

  bin >> depth;
  if(depth == 1) {
    bui_word v;
    bin >> v;
    biguint tmp(v);
    src.swap(tmp);
  } else {  
    // inlined align_alloc
    bui_word *ptr = (bui_word*) malloc(((2*depth)+2) * sizeof(bui_word));  
    if(ptr == NULL) { throw std::bad_alloc(); }
    if(((bui_word)ptr) & 1) { throw std::runtime_error("Allocated memory not aligned!"); }
    
    ptr[0] = depth;
    ptr[1] = depth;
    // copy data
    for(bui_word i=2;i<(depth+2);++i) { bin >> ptr[i]; }
    // clear padding zeros
    memset(ptr+2+depth,0,depth*sizeof(bui_word));

    biguint tmp;
    tmp.ptr = (bui_word) ptr;
    src.swap(tmp);
  }

  return bin;
}
