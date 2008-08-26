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

biguint::biguint(uint32_t v, uint32_t depth) { 
  uint32_t padding = depth*2;
  uint32_t *p = aligned_alloc(depth+padding+2);
  p[0]=depth;
  p[1]=padding;
  memset(p+2,0,(depth+padding)*sizeof(uint32_t));
  p[2]=v;
  ptr = BUI_PACK(p);
}

/* =============================== */
/* ======== ASSIGNMENT OPS ======= */
/* =============================== */
  
/* =============================== */
/* ======== COMPARISON OPS ======= */
/* =============================== */

bool biguint::operator==(uint32_t v) const {
  if(ptr & BUI_LEFTMOST_BIT) {    
    uint32_t *p = BUI_UNPACK(ptr);
    if(p[2] != v) { return false; }
    uint32_t depth(p[0]);
    for(uint32_t i=3;i<(depth+2);++i) {
      if(p[i] != 0) { return false; }
    }
    return true;
  } else {
    return ptr == v;
  } 
}

bool biguint::operator==(uint64_t v) const {
  if(ptr & BUI_LEFTMOST_BIT) {
    uint32_t *p = BUI_UNPACK(ptr);
    uint32_t depth(p[0]);
    for(uint32_t i=2;i<(depth+2);i++) {
      if(p[i] != (uint32_t) v) { return false; }
      v >>= 32U;
    }    
    if(v != 0) { return false; }
    return true;
  } else {
    return (v <= UINT32_MAX) && ptr == v;
  } 
}

bool biguint::operator==(biguint const &v) const {
  if((ptr & BUI_LEFTMOST_BIT) == 0) {
    return v == ptr;
  } else if((v.ptr & BUI_LEFTMOST_BIT) == 0) {
    return (*this) == v.ptr;
  } else {
    uint32_t *p(BUI_UNPACK(ptr));
    uint32_t *s(BUI_UNPACK(v.ptr));
    uint32_t depth(std::min(p[0],s[0]));
    for(uint32_t i=2;i<(depth+2);i++) {
      if(p[i] != s[i]) { return false; }
    }
    // now, check remaining digits are zero.    
    uint32_t m_depth(p[0]);
    for(uint32_t i=depth+2;i<(m_depth+2);++i) {
      if(p[i] != 0) { return false; }
    }
    uint32_t v_depth(s[0]);
    for(uint32_t i=depth+2;i<(v_depth+2);++i) {
      if(s[i] != 0) { return false; }
    }      
  }
  return true;
}

bool biguint::operator!=(uint32_t v) const { return !((*this) == v); }
bool biguint::operator!=(uint64_t v) const { return !((*this) == v); }
bool biguint::operator!=(biguint const &v) const { return !((*this) == v); }

bool biguint::operator<(uint32_t v) const {
  if(ptr & BUI_LEFTMOST_BIT) {    
    uint32_t *p = BUI_UNPACK(ptr);
    if(p[2] >= v) { return false; }
    uint32_t depth(p[0]);
    for(uint32_t i=3;i<(depth+2);++i) {
      if(p[i] != 0) { return false; }
    }
    return true;
  } else {
    return ptr < v;
  } 
}

bool biguint::operator<(uint64_t v) const {
  if(ptr & BUI_LEFTMOST_BIT) {    
    uint32_t *p = BUI_UNPACK(ptr);
    if(((uint64_t)p[2]) >= v) { return false; }
    uint32_t depth(p[0]);
    if(depth == 1) { return true; }
    uint64_t w = p[3];
    w = (w << 32U) + p[2];    
    if(w >= v) { return false; }
    for(uint32_t i=4;i<(depth+2);++i) {
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
  
  uint32_t *p = BUI_UNPACK(ptr);
  uint32_t *s = BUI_UNPACK(v.ptr);

  uint32_t depth_p(p[0]);
  uint32_t depth_s(s[0]);
  uint32_t depth(max(depth_s,depth_p));

  depth_p += 2;
  depth_s += 2;

  for(uint32_t i(depth+1);i>1;--i) {
    if(i >= depth_p) {
      if(s[i] != 0) {
	return true;
      }
    } else if(i >= depth_s) {
      if(p[i] != 0) {
	return false;
      }
    } else {
      uint32_t sw = s[i];
      uint32_t pw = p[i];
      
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

bool biguint::operator<=(uint32_t v) const {
  if(ptr & BUI_LEFTMOST_BIT) {    
    uint32_t *p = BUI_UNPACK(ptr);
    if(p[2] > v) { return false; }
    uint32_t depth(p[0]);
    for(uint32_t i=3;i<(depth+2);++i) {
      if(p[i] != 0) { return false; }
    }
    return true;
  } else {
    return ptr <= v;
  } 
}

bool biguint::operator<=(uint64_t v) const {
  if(ptr & BUI_LEFTMOST_BIT) {    
    uint32_t *p = BUI_UNPACK(ptr);
    if(((uint64_t)p[2]) > v) { return false; }
    uint32_t depth(p[0]);
    if(depth == 1) { return true; }
    uint64_t w = p[3];
    w = (w << 32U) + p[2];    
    if(w > v) { return false; }
    for(uint32_t i=4;i<(depth+2);++i) {
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
  
  uint32_t *p = BUI_UNPACK(ptr);
  uint32_t *s = BUI_UNPACK(v.ptr);

  uint32_t depth_p(p[0]);
  uint32_t depth_s(s[0]);
  uint32_t depth(max(depth_s,depth_p));

  depth_p += 2;
  depth_s += 2;

  for(uint32_t i(depth+1);i>1;--i) {
    if(i >= depth_p) {
      if(s[i] != 0) {
	return true;
      }
    } else  if(i >= depth_s) {
      if(p[i] != 0) {
	return false;
      }
    } else {
      uint32_t sw = s[i];
      uint32_t pw = p[i];
      
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

bool biguint::operator>(uint32_t v) const { return !(*this <= v); }
bool biguint::operator>(uint64_t v) const { return !(*this <= v); }
bool biguint::operator>(biguint const &v) const { return !(*this <= v); }

bool biguint::operator>=(uint32_t v) const { return !(*this < v); }
bool biguint::operator>=(uint64_t v) const { return !(*this < v); }
bool biguint::operator>=(biguint const &v) const { return !(*this < v); }

/* =============================== */
/* ======== ARITHMETIC OPS ======= */
/* =============================== */

void biguint::operator+=(uint32_t w) {
  if(ptr & BUI_LEFTMOST_BIT) {    
    uint32_t *p(BUI_UNPACK(ptr));
    uint32_t v = p[2];
    w = v + w;
    p[2] = w;
    if(w < v) { ripple_carry(1); }
  } else {
    uint32_t v = ptr;
    ptr = v + w;
    if(ptr < v) {
      uint32_t *p = aligned_alloc(4); 
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
    uint32_t *s(BUI_UNPACK(src.ptr));
    uint32_t depth = s[0];
    uint32_t *p;
    
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

    uint32_t carry = 0;
    
    for(uint32_t i=2;i<(depth+2);++i) {
      uint32_t v = p[i];
      uint32_t w = s[i];
      
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

biguint biguint::operator+(uint32_t w) const {
  biguint r(*this);
  r += w;
  return r;
}

void biguint::operator-=(uint32_t w) {
  if(ptr & BUI_LEFTMOST_BIT) {    
    uint32_t *p(BUI_UNPACK(ptr));
    uint32_t v = p[2];
    p[2] = v - w;
    if(v < w) { ripple_borrow(1); }
  } else {
    uint32_t v(ptr);
    ptr = v - w;
    if(v < w) { throw std::runtime_error("biguint cannot go negative"); }
  }
}

void biguint::operator-=(biguint const &src) {
  if((src.ptr & BUI_LEFTMOST_BIT) == 0) { 
    (*this) -= src.ptr; 
  } else {
    uint32_t *s(BUI_UNPACK(src.ptr));
    uint32_t depth = s[0];
    uint32_t *p;
    
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

    uint32_t borrow = 0;

    for(uint32_t i=2;i<(depth+2);++i) {
      uint32_t v = p[i];
      uint32_t w = s[i];
      uint32_t r = v - w - borrow;    
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

biguint biguint::operator-(uint32_t w) const {
  biguint r(*this);
  r -= w;
  return r;
}

void biguint::operator*=(uint32_t v) {
  if(ptr & BUI_LEFTMOST_BIT) {    
    // complicated case!
    uint32_t *p(BUI_UNPACK(ptr));
    uint32_t depth(p[0]);
    uint32_t overflow = 0;

    for(uint32_t i=2;i<(depth+2);++i) {
      uint64_t w = p[i];
      w = (w * v) + overflow;
      p[i] = w;
      overflow = w >> 32U;
    }
    
    if(overflow > 0) {
      // need additional space
      expand(depth+1);   
      p = BUI_UNPACK(ptr); 
      p[depth+2] = overflow;
    }
  } else {    
    // easier case!
    uint64_t w = ((uint64_t)ptr) * v;
    if(w >= BUI_LEFTMOST_BIT) { 
      // build new object
      uint32_t *p = aligned_alloc(4);
      ptr = BUI_PACK(p);
      p[0] = 2U;
      p[1] = 0;
      p[2] = w;
      p[3] = w >> 32U;
    } else {
      ptr = w;
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
    uint32_t *s(BUI_UNPACK(src.ptr));
    uint32_t depth = s[0];
    biguint ans(0U,depth);

    for(uint32_t j=0;j<depth;++j) {
      biguint tmp(*this);
      tmp *= s[j+2];

      uint32_t *tp(BUI_UNPACK(tmp.ptr));      
      uint32_t t_depth(tp[0]);
      uint32_t carry = 0;

      ans.expand(j + t_depth); 

      uint32_t *ap(BUI_UNPACK(ans.ptr));      

      // standard add, although slightly modified
      // to give the base shift for free.
      for(uint32_t i=0;i!=t_depth;++i) {
	uint32_t v = ap[j+i+2];
	uint32_t w = tp[i+2];
	
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

biguint biguint::operator*(uint32_t w) const {
  biguint r(*this);
  r *= w;
  return r;
}

biguint biguint::operator*(biguint const &src) const {
  if((src.ptr & BUI_LEFTMOST_BIT) == 0) { return (*this) * src.ptr; }
  else if((ptr & BUI_LEFTMOST_BIT) == 0) { return src * ptr; }
  else {
    uint32_t *s(BUI_UNPACK(src.ptr));
    uint32_t depth = s[0];
    biguint ans(0U,depth);

    for(uint32_t j=0;j<depth;++j) {
      biguint tmp(*this);
      tmp *= s[j+2];
      
      uint32_t *tp(BUI_UNPACK(tmp.ptr));      
      uint32_t t_depth(tp[0]);
      uint32_t carry = 0;
      
      ans.expand(j + t_depth); 
      uint32_t *ap(BUI_UNPACK(ans.ptr));      

      // standard add, although slightly modified
      // to give the base shift for free.
      for(uint32_t i=0;i!=t_depth;++i) {
	uint32_t v = ap[j+i+2];
	uint32_t w = tp[i+2];

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

void biguint::operator/=(uint32_t v) {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  if(ptr & BUI_LEFTMOST_BIT) {
    uint32_t *p(BUI_UNPACK(ptr));
    uint32_t remainder=0;
    
    for(uint32_t i=p[0]+1;i>1;--i) {
      uint64_t w = remainder;
      w = (w << 32U) + p[i];
      p[i] = w / v;
      remainder = w % v;
    }    
  } else {
    // real easy!
    ptr = ptr / v;
  }
}

biguint biguint::operator/(uint32_t w) const {
  biguint r(*this);
  r /= w;
  return r;
}

void biguint::operator%=(uint32_t v) {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  if(ptr & BUI_LEFTMOST_BIT) {
    uint32_t *p(BUI_UNPACK(ptr));
    uint32_t remainder=0;
    
    for(uint32_t i=p[0]+1;i>1;--i) {
      uint64_t w = remainder;
      w = (w << 32U) + p[i];
      remainder = w % v;
    }    
    clone(remainder);
  } else {
    ptr = ptr % v;
  }
}

uint32_t biguint::operator%(uint32_t v) const {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  if(ptr & BUI_LEFTMOST_BIT) {
    uint32_t *p(BUI_UNPACK(ptr));
    uint32_t remainder=0;
  
   for(uint32_t i=p[0]+1;i>1;--i) {
     uint64_t w = remainder;
     w = (w << 32U) + p[i];
     remainder = w % v;;
   }     
   return remainder;
  } else {
    return ptr % v;
  }
}

void biguint::operator^=(uint32_t v) {
  if(v == 0) { (*this) = UINT32_C(1); }
  else {
    biguint p(*this);
    
    for(uint32_t i=1;i<v;++i) {
      (*this) *= p;
    }
  }
}

biguint biguint::operator^(uint32_t v) const {
  biguint r(*this);
  r ^= v;
  return r;
}

/* =============================== */
/* ======== CONVERSION OPS ======= */
/* =============================== */

uint32_t biguint::c_uint32() const {
  if(ptr & BUI_LEFTMOST_BIT) {
    uint32_t *p(BUI_UNPACK(ptr));
    if(p[0] > 1U) { throw runtime_error("biguint too large for unsigned int"); }
    return p[2];
  } else {
    return ptr;
  }
}  

uint64_t biguint::c_uint64() const {
  if(ptr & BUI_LEFTMOST_BIT) {
    uint32_t *p(BUI_UNPACK(ptr));
    uint32_t depth = p[0];
    if(depth > 2U) { throw runtime_error("biguint too large for unsigned long long"); }
    uint64_t r=0;
    for(uint32_t i=depth+1;i>1;--i) {
      r <<= 32U;
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
void biguint::expand(uint32_t ndepth) {
  uint32_t *p(BUI_UNPACK(ptr));
  uint32_t depth = p[0];
  uint32_t padding = p[1];
  if(depth >= ndepth) { return; }
  else if((depth+padding) >= ndepth) {
    // no need to expand as we have space in the padding
    p[0] = ndepth;
    p[1] = (depth+padding)-ndepth;
  } else {
    uint32_t *nptr = aligned_alloc((ndepth*2)+2);
    nptr[0]=ndepth;
    nptr[1]=ndepth;
    memset(nptr+depth+2,0,((ndepth*2)-depth)*sizeof(uint32_t));
    memcpy(nptr+2,p+2,depth*sizeof(uint32_t));
    free(p);
    ptr = BUI_PACK(nptr);
  }
}

void biguint::ripple_carry(uint32_t level) {
  uint32_t *p(BUI_UNPACK(ptr));
  uint32_t depth(p[0]);

  for(uint32_t i(level+2);i<(depth+2);++i) {
    uint32_t v = p[i];
    
    if(v == UINT32_MAX) { p[i] = 0; } 
    else {
      p[i] = v + 1;
      return;
    }	
  }
  // not enough space to hold answer!
  expand(depth+1);
  BUI_UNPACK(ptr)[depth+2]=1U;  
}

void biguint::ripple_borrow(uint32_t level) {  
  uint32_t *p(BUI_UNPACK(ptr));
  uint32_t depth = p[0];
  for(uint32_t i(level+2);i<(depth+2);++i) {
    uint32_t v = p[i];
    if(v == 0) {
      p[i] = UINT32_MAX;
    } else {
      p[i] = v - 1;
      return;
    }	
  }    
  // this is a negative number!
  throw std::runtime_error("biguint cannot go negative"); 
}

uint32_t *biguint::aligned_alloc(uint32_t c) {
  uint32_t *p = (uint32_t*) malloc(c * sizeof(uint32_t));  
  if(p == NULL) { throw std::bad_alloc(); }
  if(((uint32_t)p) & 1) { throw std::runtime_error("Allocated memory not aligned!"); }
  return p;
}

/* =============================== */
/* ======== FRIEND METHODS ======= */
/* =============================== */

std::ostream& operator<<(ostream &out, biguint val) {
  std::string r;

  if(val == UINT32_C(0)) { return out << "0"; }
  
  while(val != UINT32_C(0)) {
    uint32_t digit = val % 10;
    char d = digit + '0'; // YUK
    r = d + r;
    val = val / 10;
  }

  return out << r;
}

biguint pow(biguint const &r, uint32_t power) {
  return r ^ power;
}

bstreambuf &operator<<(bstreambuf &bout, biguint const &src) {
  if(src.ptr & BUI_LEFTMOST_BIT) {
    uint32_t *s(BUI_UNPACK(src.ptr));
    uint32_t depth(s[0]);
    
    bout << depth;
    for(uint32_t i=2;i<(depth+2);++i) { bout << s[i]; }
  } else {
    bout << 1U << src.ptr;
  }
}

bistream &operator>>(bistream &bin, biguint &src) {  
  uint32_t depth;

  bin >> depth;
  if(depth == 1) {
    uint32_t v;
    bin >> v;
    biguint tmp(v);
    src.swap(tmp);
  } else {  
    // inlined align_alloc
    uint32_t *ptr = (uint32_t*) malloc(((2*depth)+2) * sizeof(uint32_t));  
    if(ptr == NULL) { throw std::bad_alloc(); }
    if(((uint32_t)ptr) & 1) { throw std::runtime_error("Allocated memory not aligned!"); }
    
    ptr[0] = depth;
    ptr[1] = depth;
    // copy data
    for(uint32_t i=2;i<(depth+2);++i) { bin >> ptr[i]; }
    // clear padding zeros
    memset(ptr+2+depth,0,depth*sizeof(uint32_t));

    biguint tmp;
    tmp.ptr = (uint32_t) ptr;
    src.swap(tmp);
  }

  return bin;
}
