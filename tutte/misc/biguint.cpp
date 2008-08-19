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

/* =============================== */
/* ========= CONSTRUCTORS ======== */
/* =============================== */

biguint::biguint(unsigned int v, unsigned int depth) { 
  unsigned int padding = depth*2;
  unsigned int *p = aligned_alloc(depth+padding+2);
  p[0]=depth;
  p[1]=padding;
  memset(p+2,0,(depth+padding)*sizeof(unsigned int));
  p[2]=v;
  ptr = BUI_PACK(p);
}

biguint::biguint(unsigned int *p) {
  ptr = BUI_PACK(p);
}
    
/* =============================== */
/* ======== ASSIGNMENT OPS ======= */
/* =============================== */
  
/* =============================== */
/* ======== COMPARISON OPS ======= */
/* =============================== */

bool biguint::operator==(unsigned int v) const {
  if(ptr & BUI_LEFTMOST_BIT) {    
    unsigned int *p = BUI_UNPACK(ptr);
    if(p[2] != v) { return false; }
    unsigned int depth(p[0]);
    for(unsigned int i=3;i<(depth+2);++i) {
      if(p[i] != 0) { return false; }
    }
    return true;
  } else {
    return ptr == v;
  } 
}

bool biguint::operator==(unsigned long v) const {
  if(ptr & BUI_LEFTMOST_BIT) {
    unsigned int *p = BUI_UNPACK(ptr);
    unsigned int depth(p[0]);
    for(unsigned int i=2;i<(depth+2);i++) {
      if(p[i] != (unsigned int) v) { return false; }
      v >>= UINT_WIDTH;
    }    
    if(v != 0) { return false; }
    return true;
  } else {
    return (v <= UINT_MAX) && ptr == v;
  } 
}

bool biguint::operator==(unsigned long long v) const {
  if(ptr & BUI_LEFTMOST_BIT) {
    unsigned int *p = BUI_UNPACK(ptr);
    unsigned int depth(p[0]);
    for(unsigned int i=2;i<(depth+2);i++) {
      if(p[i] != (unsigned int) v) { return false; }
      v >>= UINT_WIDTH;
    }    
    if(v != 0) { return false; }
    return true;
  } else {
    return (v <= UINT_MAX) && ptr == v;
  } 
}

bool biguint::operator==(biguint const &v) const {
  if((ptr & BUI_LEFTMOST_BIT) == 0) {
    return v == ptr;
  } else if((v.ptr & BUI_LEFTMOST_BIT) == 0) {
    return (*this) == v.ptr;
  } else {
    unsigned int *p(BUI_UNPACK(ptr));
    unsigned int *s(BUI_UNPACK(v.ptr));
    unsigned int depth(std::min(p[0],s[0]));
    for(unsigned int i=2;i<(depth+2);i++) {
      if(p[i] != s[i]) { return false; }
    }
    // now, check remaining digits are zero.    
    unsigned int m_depth(p[0]);
    for(unsigned int i=depth+2;i<(m_depth+2);++i) {
      if(p[i] != 0) { return false; }
    }
    unsigned int v_depth(s[0]);
    for(unsigned int i=depth+2;i<(v_depth+2);++i) {
      if(s[i] != 0) { return false; }
    }      
  }
  return true;
}

bool biguint::operator!=(unsigned int v) const { return !((*this) == v); }
bool biguint::operator!=(unsigned long v) const { return !((*this) == v); }
bool biguint::operator!=(unsigned long long v) const { return !((*this) == v); }
bool biguint::operator!=(biguint const &v) const { return !((*this) == v); }

bool biguint::operator<(unsigned int v) const {
  if(ptr & BUI_LEFTMOST_BIT) {    
    unsigned int *p = BUI_UNPACK(ptr);
    if(p[2] >= v) { return false; }
    unsigned int depth(p[0]);
    for(unsigned int i=3;i<(depth+2);++i) {
      if(p[i] != 0) { return false; }
    }
    return true;
  } else {
    return ptr < v;
  } 
}

bool biguint::operator<(unsigned long v) const {
  if(ptr & BUI_LEFTMOST_BIT) {
    unsigned int *p = BUI_UNPACK(ptr);
    unsigned int depth_p(p[0]);
    unsigned int depth_s(BUI_ULONG_SIZE);
    unsigned int depth(max(depth_s,depth_p));

    depth_p += 2;

    for(unsigned int i=(depth+1);i>1;--i) {
      unsigned int w = v >> ((i-2)*UINT_WIDTH);
      if(i >= depth_p) {
	if(w != 0) { return true; }
      } else if(p[i] > w) { return false; }
      else if(p[i] < w) { return true; }
    }    
    return false;
  } else {
    return (v > UINT_MAX) || ptr < v;
  } 
}

bool biguint::operator<(unsigned long long v) const {
  if(ptr & BUI_LEFTMOST_BIT) {
    unsigned int *p = BUI_UNPACK(ptr);
    unsigned int depth_p(p[0]);
    unsigned int depth_s(BUI_ULONGLONG_SIZE);
    unsigned int depth(max(depth_s,depth_p));

    depth_p += 2;
    
    for(unsigned int i=(depth+1);i>1;--i) {
      unsigned int w = v >> ((i-2)*UINT_WIDTH);
      if(i >= depth_p) {
	if(w != 0) { return true; }
      } else if(p[i] > w) { return false; }
      else if(p[i] < w) { return true; }
    }    
    return false;
  } else {
    return (v > UINT_MAX) || ptr < v;
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
  
  unsigned int *p = BUI_UNPACK(ptr);
  unsigned int *s = BUI_UNPACK(v.ptr);

  unsigned int depth_p(p[0]);
  unsigned int depth_s(s[0]);
  unsigned int depth(max(depth_s,depth_p));

  depth_p += 2;
  depth_s += 2;

  for(unsigned int i(depth+1);i>1;--i) {
    if(i >= depth_p) {
      if(s[i] != 0) {
	return true;
      }
    } else if(i >= depth_s) {
      if(p[i] != 0) {
	return false;
      }
    } else {
      unsigned int sw = s[i];
      unsigned int pw = p[i];
      
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

bool biguint::operator<=(unsigned int v) const {
  if(ptr & BUI_LEFTMOST_BIT) {    
    unsigned int *p = BUI_UNPACK(ptr);
    if(p[2] > v) { return false; }
    unsigned int depth(p[0]);
    for(unsigned int i=3;i<(depth+2);++i) {
      if(p[i] != 0) { return false; }
    }
    return true;
  } else {
    return ptr <= v;
  } 
}

bool biguint::operator<=(unsigned long v) const {
  if(ptr & BUI_LEFTMOST_BIT) {
    unsigned int *p = BUI_UNPACK(ptr);
    unsigned int depth_p(p[0]);
    unsigned int depth_s(BUI_ULONG_SIZE);
    unsigned int depth(max(depth_s,depth_p));

    depth_p += 2;

    for(unsigned int i=(depth+1);i>1;--i) {
      unsigned int w = v >> ((i-2)*UINT_WIDTH);
      if(i >= depth_p) {
	if(w != 0) { return true; }
      } else if(p[i] > w) { return false; }
      else if(p[i] < w) { return true; }
    }    
    return true;
  } else {
    return (v > UINT_MAX) || ptr <= v;
  } 
}

bool biguint::operator<=(unsigned long long v) const {
  if(ptr & BUI_LEFTMOST_BIT) {
    unsigned int *p = BUI_UNPACK(ptr);
    unsigned int depth_p(p[0]);
    unsigned int depth_s(BUI_ULONGLONG_SIZE);
    unsigned int depth(max(depth_s,depth_p));

    depth_p += 2;

    for(unsigned int i=(depth+1);i>1;--i) {
      unsigned int w = v >> ((i-2)*UINT_WIDTH);
      if(i >= depth_p) {
	if(w != 0) { return true; }
      } else if(p[i] > w) { return false; }
      else if(p[i] < w) { return true; }
    }    
    return true;
  } else {
    return (v > UINT_MAX) || ptr <= v;
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
  
  unsigned int *p = BUI_UNPACK(ptr);
  unsigned int *s = BUI_UNPACK(v.ptr);

  unsigned int depth_p(p[0]);
  unsigned int depth_s(s[0]);
  unsigned int depth(max(depth_s,depth_p));

  depth_p += 2;
  depth_s += 2;

  for(unsigned int i(depth+1);i>1;--i) {
    if(i >= depth_p) {
      if(s[i] != 0) {
	return true;
      }
    } else  if(i >= depth_s) {
      if(p[i] != 0) {
	return false;
      }
    } else {
      unsigned int sw = s[i];
      unsigned int pw = p[i];
      
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

bool biguint::operator>(unsigned int v) const { return !(*this <= v); }
bool biguint::operator>(unsigned long v) const { return !(*this <= v); }
bool biguint::operator>(unsigned long long v) const { return !(*this <= v); }
bool biguint::operator>(biguint const &v) const { return !(*this <= v); }

bool biguint::operator>=(unsigned int v) const { return !(*this < v); }
bool biguint::operator>=(unsigned long v) const { return !(*this < v); }
bool biguint::operator>=(unsigned long long v) const { return !(*this < v); }
bool biguint::operator>=(biguint const &v) const { return !(*this < v); }

/* =============================== */
/* ======== ARITHMETIC OPS ======= */
/* =============================== */

void biguint::operator+=(unsigned int w) {
  if(ptr & BUI_LEFTMOST_BIT) {    
    unsigned int *p(BUI_UNPACK(ptr));
    unsigned int v = p[2];
    w = v + w;
    p[2] = w;
    if(w < v) { ripple_carry(1); }
  } else {
    unsigned int v = ptr;
    ptr = v + w;
    if(ptr < v) {
      unsigned int *p = aligned_alloc(4); 
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
    unsigned int *s(BUI_UNPACK(src.ptr));
    unsigned int depth = s[0];
    unsigned int *p;
    
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

    unsigned int carry = 0;
    
    for(unsigned int i=2;i<(depth+2);++i) {
      unsigned int v = p[i];
      unsigned int w = s[i];
      
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

biguint biguint::operator+(unsigned int w) const {
  biguint r(*this);
  r += w;
  return r;
}

void biguint::operator-=(unsigned int w) {
  if(ptr & BUI_LEFTMOST_BIT) {    
    unsigned int *p(BUI_UNPACK(ptr));
    unsigned int v = p[2];
    p[2] = v - w;
    if(v < w) { ripple_borrow(1); }
  } else {
    unsigned int v(ptr);
    ptr = v - w;
    if(v < w) { throw std::runtime_error("biguint cannot go negative"); }
  }
}

void biguint::operator-=(biguint const &src) {
  if((src.ptr & BUI_LEFTMOST_BIT) == 0) { 
    (*this) -= src.ptr; 
  } else {
    unsigned int *s(BUI_UNPACK(src.ptr));
    unsigned int depth = s[0];
    unsigned int *p;
    
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

    unsigned int borrow = 0;

    for(unsigned int i=2;i<(depth+2);++i) {
      unsigned int v = p[i];
      unsigned int w = s[i];
      unsigned int r = v - w - borrow;    
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

biguint biguint::operator-(unsigned int w) const {
  biguint r(*this);
  r -= w;
  return r;
}

void biguint::operator*=(unsigned int v) {
  if(ptr & BUI_LEFTMOST_BIT) {    
    // complicated case!
    unsigned int *p(BUI_UNPACK(ptr));
    unsigned int depth(p[0]);
    unsigned int overflow = 0;

    for(unsigned int i=2;i<(depth+2);++i) {
      d_unsigned_int w = p[i];
      w = (w * v) + overflow;
      p[i] = w;
      overflow = w >> UINT_WIDTH;
    }
    
    if(overflow > 0) {
      // need additional space
      expand(depth+1);   
      p = BUI_UNPACK(ptr); 
      p[depth+2] = overflow;
    }
  } else {    
    // easier case!
    d_unsigned_int w = ((d_unsigned_int) ptr) * v;
    if(w >= BUI_LEFTMOST_BIT) { 
      // build new object
      unsigned int *p = aligned_alloc(4);
      ptr = BUI_PACK(p);
      p[0] = 2U;
      p[1] = 0;
      p[2] = w;
      p[3] = w >> UINT_WIDTH;
    } else {
      ptr = w;
    }
  }
}

void biguint::operator*=(unsigned long long v) {
  biguint tmp(v);
  (*this) *= tmp;
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
    unsigned int *s(BUI_UNPACK(src.ptr));
    unsigned int depth = s[0];
    biguint ans(0U,depth);

    for(unsigned int j=0;j<depth;++j) {
      biguint tmp(*this);
      tmp *= s[j+2];

      unsigned int *tp(BUI_UNPACK(tmp.ptr));      
      unsigned int t_depth(tp[0]);
      unsigned int carry = 0;

      ans.expand(j + t_depth); 

      unsigned int *ap(BUI_UNPACK(ans.ptr));      

      // standard add, although slightly modified
      // to give the base shift for free.
      for(unsigned int i=0;i!=t_depth;++i) {
	unsigned int v = ap[j+i+2];
	unsigned int w = tp[i+2];
	
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

biguint biguint::operator*(unsigned int w) const {
  biguint r(*this);
  r *= w;
  return r;
}

biguint biguint::operator*(unsigned long long w) const {
  biguint r(*this);
  r *= w;
  return r;
}

biguint biguint::operator*(biguint const &src) const {
  if((src.ptr & BUI_LEFTMOST_BIT) == 0) { return (*this) * src.ptr; }
  else if((ptr & BUI_LEFTMOST_BIT) == 0) { return src * ptr; }
  else {
    unsigned int *s(BUI_UNPACK(src.ptr));
    unsigned int depth = s[0];
    biguint ans(0U,depth);

    for(unsigned int j=0;j<depth;++j) {
      biguint tmp(*this);
      tmp *= s[j+2];
      
      unsigned int *tp(BUI_UNPACK(tmp.ptr));      
      unsigned int t_depth(tp[0]);
      unsigned int carry = 0;
      
      ans.expand(j + t_depth); 
      unsigned int *ap(BUI_UNPACK(ans.ptr));      

      // standard add, although slightly modified
      // to give the base shift for free.
      for(unsigned int i=0;i!=t_depth;++i) {
	unsigned int v = ap[j+i+2];
	unsigned int w = tp[i+2];

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

void biguint::operator/=(unsigned int v) {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  if(ptr & BUI_LEFTMOST_BIT) {
    unsigned int *p(BUI_UNPACK(ptr));
    unsigned int remainder=0;
    
    for(unsigned int i=p[0]+1;i>1;--i) {
      d_unsigned_int w = remainder;
      w = (w << UINT_WIDTH) + p[i];
      p[i] = w / v;
      remainder = w % v;
    }    
  } else {
    // real easy!
    ptr = ptr / v;
  }
}

biguint biguint::operator/(unsigned int w) const {
  biguint r(*this);
  r /= w;
  return r;
}

void biguint::operator%=(unsigned int v) {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  if(ptr & BUI_LEFTMOST_BIT) {
    unsigned int *p(BUI_UNPACK(ptr));
    unsigned int remainder=0;
    
    for(unsigned int i=p[0]+1;i>1;--i) {
      d_unsigned_int w = remainder;
      w = (w << UINT_WIDTH) + p[i];
      remainder = w % v;
    }    
    clone(remainder);
  } else {
    ptr = ptr % v;
  }
}

unsigned int biguint::operator%(unsigned int v) const {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  if(ptr & BUI_LEFTMOST_BIT) {
    unsigned int *p(BUI_UNPACK(ptr));
    unsigned int remainder=0;
  
   for(unsigned int i=p[0]+1;i>1;--i) {
     d_unsigned_int w = remainder;
     w = (w << UINT_WIDTH) + p[i];
     remainder = w % v;
   }     
   return remainder;
  } else {
    return ptr % v;
  }
}

void biguint::operator^=(unsigned int v) {
  if(v == 0) { (*this) = 1U; }
  else {
    biguint p(*this);
    
    for(unsigned int i=1;i<v;++i) {
      (*this) *= p;
    }
  }
}

biguint biguint::operator^(unsigned int v) const {
  biguint r(*this);
  r ^= v;
  return r;
}

/* =============================== */
/* ======== CONVERSION OPS ======= */
/* =============================== */

unsigned int biguint::c_uint() const {
  if(ptr & BUI_LEFTMOST_BIT) {
    unsigned int *p(BUI_UNPACK(ptr));
    if(p[0] > BUI_UINT_SIZE) { throw runtime_error("biguint too large for unsigned int"); }
    return p[2];
  } else {
    return ptr;
  }
}  

unsigned long biguint::c_ulong() const {
  if(ptr & BUI_LEFTMOST_BIT) {
    unsigned int *p(BUI_UNPACK(ptr));
    if(p[0] > BUI_ULONG_SIZE) { throw runtime_error("biguint too large for unsigned int"); }
    return p[2];
  } else {
    return ptr;
  }
}  

unsigned long long biguint::c_ulonglong() const {
  if(ptr & BUI_LEFTMOST_BIT) {
    unsigned int *p(BUI_UNPACK(ptr));
    unsigned int depth = p[0];
    if(depth > BUI_ULONGLONG_SIZE) { throw runtime_error("biguint too large for unsigned long long"); }
    unsigned long long r=0;
    for(unsigned int i=depth+1;i>1;--i) {
      r <<= UINT_WIDTH;
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
void biguint::expand(unsigned int ndepth) {
  unsigned int *p(BUI_UNPACK(ptr));
  unsigned int depth = p[0];
  unsigned int padding = p[1];
  if(depth >= ndepth) { return; }
  else if((depth+padding) >= ndepth) {
    // no need to expand as we have space in the padding
    p[0] = ndepth;
    p[1] = (depth+padding)-ndepth;
  } else {
    unsigned int *nptr = aligned_alloc((ndepth*2)+2);
    nptr[0]=ndepth;
    nptr[1]=ndepth;
    memset(nptr+depth+2,0,((ndepth*2)-depth)*sizeof(unsigned int));
    memcpy(nptr+2,p+2,depth*sizeof(unsigned int));
    free(p);
    ptr = BUI_PACK(nptr);
  }
}

void biguint::ripple_carry(unsigned int level) {
  unsigned int *p(BUI_UNPACK(ptr));
  unsigned int depth(p[0]);

  for(unsigned int i(level+2);i<(depth+2);++i) {
    unsigned int v = p[i];
    
    if(v == UINT_MAX) { p[i] = 0; } 
    else {
      p[i] = v + 1;
      return;
    }	
  }
  // not enough space to hold answer!
  expand(depth+1);
  BUI_UNPACK(ptr)[depth+2]=1U;  
}

void biguint::ripple_borrow(unsigned int level) {  
  unsigned int *p(BUI_UNPACK(ptr));
  unsigned int depth = p[0];
  for(unsigned int i(level+2);i<(depth+2);++i) {
    unsigned int v = p[i];
    if(v == 0) {
      p[i] = UINT_MAX;
    } else {
      p[i] = v - 1;
      return;
    }	
  }    
  // this is a negative number!
  throw std::runtime_error("biguint cannot go negative"); 
}

unsigned int *biguint::aligned_alloc(unsigned int c) {
  unsigned int *p = (unsigned int*) malloc(c * sizeof(unsigned int));  
  if(((unsigned int)p) & 1) { throw std::runtime_error("Allocated memory not aligned!"); }
  return p;
}

/* =============================== */
/* ======== FRIEND METHODS ======= */
/* =============================== */

std::ostream& operator<<(ostream &out, biguint val) {
  std::string r;

  if(val == 0U) { return out << "0"; }
  
  while(val != 0U) {
    unsigned int digit = val % 10;
    char d = digit + '0'; // YUK
    r = d + r;
    val = val / 10;
  }

  return out << r;
}

biguint pow(biguint const &r, unsigned int power) {
  return r ^ power;
}

bstreambuf &operator<<(bstreambuf &bout, biguint const &src) {
  if(src.ptr & BUI_LEFTMOST_BIT) {
    unsigned int *s(BUI_UNPACK(src.ptr));
    unsigned int depth(s[0]);
    
    bout << depth;
    for(unsigned int i=2;i<(depth+2);++i) { bout << s[i]; }
  } else {
    bout << 1U << src.ptr;
  }
}

bistream &operator>>(bistream &bin, biguint &src) {  
  unsigned int depth;

  bin >> depth;
  if(depth == 1) {
    unsigned int v;
    bin >> v;
    biguint tmp(v);
    src.swap(tmp);
  } else {  
    // inlined align_alloc
    unsigned int *ptr = (unsigned int*) malloc(((2*depth)+2) * sizeof(unsigned int));  
    if(((unsigned int)ptr) & 1) { throw std::runtime_error("Allocated memory not aligned!"); }
    
    ptr[0] = depth;
    ptr[1] = depth;
    // copy data
    for(unsigned int i=2;i<(depth+2);++i) { bin >> ptr[i]; }
    // clear padding zeros
    memset(ptr+2+depth,0,depth*sizeof(unsigned int));

    biguint tmp(ptr);
    src.swap(tmp);
  }

  return bin;
}
