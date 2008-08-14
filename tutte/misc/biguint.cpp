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

biguint::biguint(bui_word *p) {
  ptr = PACK(p);
}

biguint::biguint(int v, bui_word depth) { 
  bui_word padding = depth*2;
  bui_word *p = aligned_alloc(depth+padding+2);  
  p[0] = PACK_DEPTH(depth,SIGN(v));
  p[1] = padding;
  memset(p+2,0,(depth+padding)*sizeof(bui_word));
  p[2] = ABS_UINT(v);
  ptr = PACK(p);
}
    
/* =============================== */
/* ======== ASSIGNMENT OPS ======= */
/* =============================== */
  
/* =============================== */
/* ======== COMPARISON OPS ======= */
/* =============================== */

bool biguint::operator==(int v) const {
  if(ptr & BUI_PTR_BIT) {    
    bui_word *p = UNPACK(ptr);
    if(p[2] != ABS_UINT(v) || SIGN(p[0]) != SIGN(v)) { return false; }
    unsigned int depth(DEPTH(p[0]));
    for(unsigned int i=3;i<(depth+2);++i) {
      if(p[i] != 0) { return false; }
    }
    return true;
  } else {
    return SIGN_EXTEND(ptr) == true;
  } 
}

bool biguint::operator==(biguint const &v) const {
  if((ptr & BUI_PTR_BIT) == 0) {
    return v == SIGN_EXTEND(ptr);
  } else if((v.ptr & BUI_PTR_BIT) == 0) {
    return (*this) == v.ptr;
  } else {
    bui_word *p(UNPACK(ptr));
    bui_word *s(UNPACK(v.ptr));
    bui_word depth(std::min(DEPTH(p[0]),DEPTH(s[0])));

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
    return SIGN(p[0]) == SIGN(s[0]);
  }
}

bool biguint::operator!=(int v) const { return !((*this) == v); }
bool biguint::operator!=(biguint const &v) const { return !((*this) == v); }

/* =============================== */
/* ======== ARITHMETIC OPS ======= */
/* =============================== */

void biguint::operator+=(int w) {
  cout << "ENTERED +=(int)" << endl;
  if(ptr & BUI_PTR_BIT) {    
    bui_word *p(UNPACK(ptr));
    if(SIGN(w) == SIGN(p[0])) {
      internal_add(p,ABS_UINT(w));
    } else {
      internal_sub(p,ABS_UINT(w));
    }
  } else {
    int v = SIGN_EXTEND(ptr);
    int x = v + w;    
    if(w >= 0 && x < v) {
	// overflow occurred
	bui_word *p = aligned_alloc(3); 
	p[0] = PACK_DEPTH(1U,!SIGN(x));
	p[1] = 0;
	p[2] = (x|BUI_PTR_BIT);
	ptr = PACK(p);
      } else if(w < 0 && x > v) {
      // underflow occurred
      bui_word *p = aligned_alloc(3); 
      p[0] = PACK_DEPTH(1U,!SIGN(x));
      p[1] = 0;
      p[2] = ~(x-1);
      ptr = PACK(p);
    } else {
      clone(x);
    }
  }
  cout << "DONE +=(int)" << endl;
}

void biguint::operator+=(biguint const &src) {
  cout << "ENTERED +=(biguint)" << endl;
  if((src.ptr & BUI_PTR_BIT) == 0) { 
    (*this) += src.ptr; 
  } else {
    bui_word *p;
    bui_word *s(UNPACK(src.ptr));
    bui_word depth = DEPTH(s[0]);

    // Ensure we're in array mode, with at least depth digits.
    if((ptr & BUI_PTR_BIT) == 0) {
      // word mode, so convert.
      int w = SIGN_EXTEND(ptr);
      p = aligned_alloc(depth+2);
      p[0] = PACK_DEPTH(depth,SIGN(w));      
      p[1] = 0;
      p[2] = ABS_UINT(w);

      for(int i=3;i<(depth+2);++i) { p[i] = 0U; }
      ptr = PACK(p);
    } else {
      // array mode, so leave.
      expand(depth);
      p = UNPACK(ptr);
    }

    if(SIGN(s[0]) != SIGN(p[0])) {
      internal_sub(p,s);
    } else {     
      internal_add(p,s);
    }   
  }
  cout << "DONE +=(biguint)" << endl;
}

biguint biguint::operator+(biguint const &w) const {
  biguint r(*this);
  r += w;
  return r;
}

biguint biguint::operator+(int w) const {
  biguint r(*this);
  r += w;
  return r;
}

void biguint::operator-=(int w) {
  if(ptr & BUI_PTR_BIT) {        
    bui_word *p(UNPACK(ptr));
    if(SIGN(w) == SIGN(p[0])) {
      internal_sub(p,ABS_UINT(w));
    } else {
      internal_add(p,ABS_UINT(w));
    }
  } else {
    int v = SIGN_EXTEND(ptr);
    int x = v - w;        
    if(w >= 0 && x > v) {
      // underflow occurred
      bui_word *p = aligned_alloc(3); 
      p[0] = PACK_DEPTH(1U,!SIGN(x));
      p[1] = 0;
      p[2] = ~(x-1);
      ptr = PACK(p);
    } else if(w < 0 && x < v) {
      // overflow occurred
      bui_word *p = aligned_alloc(3); 
      p[0] = PACK_DEPTH(1U,!SIGN(x));
      p[1] = 0;
      p[2] = (x|BUI_PTR_BIT);
      ptr = PACK(p);
    } else {
      clone(x);
    }
  }
}

void biguint::operator-=(biguint const &src) {
  if((src.ptr & BUI_PTR_BIT) == 0) { 
    (*this) -= src.ptr; 
  } else {
    bui_word *s(UNPACK(src.ptr));
    bui_word depth = s[0];
    bui_word *p;
    
    if((ptr & BUI_PTR_BIT) == 0) { 
      // assume it needs to go big
      int w = SIGN_EXTEND(ptr);
      p = aligned_alloc(depth+2);
      p[0] = PACK_DEPTH(depth,SIGN(w));
      p[1] = 0;      
      p[2] = ABS_UINT(w);
      for(int i=3;i<(depth+2);++i) { p[i] = 0U; }
      ptr = PACK(p);
    } else {
      expand(depth);
      p = UNPACK(ptr);
    }

    if(SIGN(s[0]) == SIGN(p[0])) {
      internal_sub(p,s);
    } else {     
      internal_add(p,s);
    }   
  }
}

biguint biguint::operator-(biguint const &w) const {
  biguint r(*this);
  r -= w;
  return r;
}

biguint biguint::operator-(int w) const {
  biguint r(*this);
  r -= w;
  return r;
}

void biguint::operator*=(int v) {
  if(ptr & BUI_PTR_BIT) {    
    // complicated case!
    bui_word *p(UNPACK(ptr));
    bui_word depth(p[0]);
    bui_word overflow = 0;

    for(bui_word i=2;i<(depth+2);++i) {
      bui_dword w = p[i];
      w = (w * v) + overflow;
      p[i] = w;
      overflow = w >> BUI_WORD_WIDTH;
    }
    
    if(overflow > 0) {
      // need additional space
      expand(depth+1);   
      p = UNPACK(ptr); 
      p[depth+2] = overflow;
    }
  } else {    
    // easier case!
    bui_dword w = ((bui_dword) ptr) * v;
    if(w >= BUI_PTR_BIT) { 
      // build new object
      bui_word *p = aligned_alloc(4);
      ptr = PACK(p);
      p[0] = 2U;
      p[1] = 0;
      p[2] = w;
      p[3] = w >> BUI_WORD_WIDTH;
    } else {
      ptr = w;
    }
  }
}

void biguint::operator*=(biguint const &src) {
  // this could probably be optimised ...
  if((src.ptr & BUI_PTR_BIT) == 0) { 
    (*this) *= src.ptr; 
  } else if((ptr & BUI_PTR_BIT) == 0) {
    // could be optimised a little?
    biguint ans(src);
    ans *= ptr;
    swap(ans);
  } else {
    bui_word *s(UNPACK(src.ptr));
    bui_word depth = s[0];
    biguint ans(0,depth);

    for(unsigned int j=0;j<depth;++j) {
      biguint tmp(*this);
      tmp *= s[j+2];

      bui_word *tp(UNPACK(tmp.ptr));      
      unsigned int t_depth(tp[0]);
      unsigned int carry = 0;

      ans.expand(j + t_depth); 

      bui_word *ap(UNPACK(ans.ptr));      

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

biguint biguint::operator*(int w) const {
  biguint r(*this);
  r *= w;
  return r;
}

biguint biguint::operator*(biguint const &src) const {
  if((src.ptr & BUI_PTR_BIT) == 0) { return (*this) * src.ptr; }
  else if((ptr & BUI_PTR_BIT) == 0) { return src * ptr; }
  else {
    bui_word *s(UNPACK(src.ptr));
    bui_word depth = s[0];
    biguint ans(0U,depth);

    for(unsigned int j=0;j<depth;++j) {
      biguint tmp(*this);
      tmp *= s[j+2];
      
      bui_word *tp(UNPACK(tmp.ptr));      
      unsigned int t_depth(tp[0]);
      unsigned int carry = 0;
      
      ans.expand(j + t_depth); 
      bui_word *ap(UNPACK(ans.ptr));      

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

void biguint::operator/=(int v) {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  if(ptr & BUI_PTR_BIT) {
    bui_word *p(UNPACK(ptr));
    bui_word remainder=0;
    
    for(bui_word i=p[0]+1;i>1;--i) {
      bui_dword w = remainder;
      w = (w << BUI_WORD_WIDTH) + p[i];
      p[i] = w / v;
      remainder = w % v;
    }    
  } else {
    // real easy!
    ptr = ptr / v;
  }
}

biguint biguint::operator/(int w) const {
  biguint r(*this);
  r /= w;
  return r;
}

void biguint::operator%=(int v) {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  if(ptr & BUI_PTR_BIT) {
    bui_word *p(UNPACK(ptr));
    bui_word remainder=0;
    
    for(bui_word i=p[0]+1;i>1;--i) {
      bui_dword w = remainder;
      w = (w << BUI_WORD_WIDTH) + p[i];
      remainder = w % v;
    }    
    clone(remainder);
  } else {
    ptr = ptr % v;
  }
}

int biguint::operator%(int v) const {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  if(ptr & BUI_PTR_BIT) {
    bui_word *p(UNPACK(ptr));
    bui_word remainder=0;
  
   for(bui_word i=p[0]+1;i>1;--i) {
     bui_dword w = remainder;
     w = (w << BUI_WORD_WIDTH) + p[i];
     remainder = w % v;
   }     
   return remainder;
  } else {
    return ptr % v;
  }
}

void biguint::operator^=(int v) {
  if(v == 0) { (*this) = 1U; }
  else {
    biguint p(*this);
    
    for(unsigned int i=1;i<v;++i) {
      (*this) *= p;
    }
  }
}

biguint biguint::operator^(int v) const {
  biguint r(*this);
  r ^= v;
  return r;
}

/* =============================== */
/* ======== CONVERSION OPS ======= */
/* =============================== */

int biguint::c_int() const {
  if(ptr & BUI_PTR_BIT) {
    bui_word *p(UNPACK(ptr));
    if(DEPTH(p[0]) > 1) { throw runtime_error("biguint too large for int"); }
    bui_word w = p[2];
    // special case here for INT_MIN
    if((w-1) == INT_MAX && SIGN(p[0])) { return INT_MIN; }
    if(w > INT_MAX) { throw runtime_error("biguint too large for int"); }
    return SIGN(p[0]) ? -w : w;
  } else {
    return SIGN_EXTEND(ptr);
  }
}  

long biguint::c_long() const {
  if(ptr & BUI_PTR_BIT) {
    bui_word *p(UNPACK(ptr));
    if(DEPTH(p[0]) > 1) { throw runtime_error("biguint too large for int"); }
    bui_word w = p[2];
    if(w > INT_MAX) { throw runtime_error("biguint too large for int"); }
    return SIGN(p[0]) ? -w : w;
  } else {
    return SIGN_EXTEND(ptr);
  }
}  
  
long long biguint::c_longlong() const {
  if(ptr & BUI_PTR_BIT) {
    bui_word *p(UNPACK(ptr));
    bui_word depth = DEPTH(p[0]);
    if(depth > (SIZEOF_LONG_LONG/SIZEOF_INT)) { throw runtime_error("biguint too large for unsigned long long"); }
    unsigned long long w=0;
    for(bui_word i=depth+1;i>1;--i) {
      w <<= BUI_WORD_WIDTH;
      w += p[i];
    }
    if(w > LLONG_MAX) { throw runtime_error("biguint too large for long long"); }
    return SIGN(p[0]) ? -w : w;
  } else {
    return SIGN_EXTEND(ptr);
  }
}  

/* =============================== */
/* ======== HELPER METHODS ======= */
/* =============================== */

// Perform unsigned addition of x to p.
void biguint::internal_add(bui_word *p, bui_word x) {
  bui_word v = p[2];  
  bui_word u = v + x; 
  p[2] = u;
  if(u < v) { ripple_carry(1); }
}

// Perform unsigned subtraction of x from p.
void biguint::internal_sub(bui_word *p, bui_word x) {
  bui_word v = p[2];  
  bui_word u = v - x; 
  p[2] = u;
  if(v < u) { ripple_borrow(1); }
}

// Perform unsigned addition of s to p.  
void biguint::internal_add(bui_word *p, bui_word *s) {
  unsigned int carry = 0;
  unsigned int depth(DEPTH(s[0]));

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

void biguint::internal_sub(bui_word *p, bui_word *s) {
  unsigned int borrow = 0;
  unsigned int p_depth(DEPTH(p[0]));
  unsigned int s_depth(DEPTH(s[0]));
  int cmp(internal_cmp(p,s));

  if(cmp < 0) {
    cout << "STAGE 1" << endl;
    // here, p is the smaller.
    // need to swap the sign of p here, since it's flipping around
    p[0] = PACK_DEPTH(p_depth,!SIGN(p[0]));

    // now, we can do the actual subtraction.
    for(bui_word i=2;i<(p_depth+2);++i) {
      bui_word v = s[i];
      bui_word w = p[i];
      bui_word r = v - w - borrow;    
      p[i] = r;
      
      if(borrow == 0) {
	borrow = v < w ? 1 : 0;
      } else {
	borrow = v <= w ? 1 : 0;
      }
    }    

  FIXME: problem here in that drying to ripple, but need from s not p.

    if(borrow == 1) { ripple_borrow(p_depth); }

  } else if(cmp == 0) {
    // they cancel each other out, so set zero.
    p[1] += DEPTH(p[0])-1;
    p[0] = PACK_DEPTH(1,false);
    p[2] = 0;
  } else {
    // here, p is the larger
    cout << "STAGE 2" << endl;
    for(bui_word i=2;i<s_depth+2;++i) {
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
    if(borrow == 1) { ripple_borrow(s_depth); }
  } 
}

// return -1,0,1 if p is less than, equal or greater to s
int biguint::internal_cmp(bui_word *p, bui_word *s) {
  unsigned int depth_s(DEPTH(s[0]));
  unsigned int depth_p(DEPTH(p[0]));
  unsigned int depth(min(depth_s,depth_p));

  for(unsigned int i(depth+1);i>1;--i) {
    if(i >= depth_p) {
      if(s[i] != 0) {
	return -1;
      }
    } else  if(i >= depth_s) {
      if(p[i] != 0) {
	return 1;
      }
    } else {
      int sw = s[i];
      int pw = p[i];
      
      if(sw < pw) {
	return 1;
      } else if(pw < sw) {
	return -1;
      }
    }
  }

  return 0;
}

// Expands the array to depth ndepth.  If ndepth < current depth,
// nothing happens.  
//
// PRE: assumes this in array format
void biguint::expand(bui_word ndepth) {
  bui_word *p(UNPACK(ptr));
  bui_word depth = DEPTH(p[0]);
  bool sign(SIGN(p[0]));
  bui_word padding = p[1];
  if(depth >= ndepth) { return; }
  else if((depth+padding) >= ndepth) {
    // no need to expand as we have space in the padding
    p[0] = PACK_DEPTH(ndepth,sign);
    p[1] = (depth+padding)-ndepth;
  } else {
    bui_word *nptr = aligned_alloc((ndepth*2)+2);
    nptr[0]=PACK_DEPTH(ndepth,sign);
    nptr[1]=ndepth;
    memset(nptr+depth+2,0,((ndepth*2)-depth)*sizeof(bui_word));
    memcpy(nptr+2,p+2,depth*sizeof(bui_word));
    free(p);
    ptr = PACK(nptr);
  }
}

void biguint::ripple_carry(bui_word level) {
  bui_word *p(UNPACK(ptr));
  bui_word depth(DEPTH(p[0]));

  for(unsigned int i(level+2);i<(depth+2);++i) {
    bui_word v = p[i];
    
    if(v == BUI_WORD_MAX) { p[i] = 0; } 
    else {
      p[i] = v + 1;
      return;
    }	
  }

  // not enough space to hold answer!
  expand(depth+1);
  UNPACK(ptr)[depth+2]=1U;  
}

void biguint::ripple_borrow(bui_word level) {  
  bui_word *p(UNPACK(ptr));
  bui_word depth(DEPTH(p[0]));
  bui_word l(level+2);
  
  for(;l<(depth+2);++l) {
    bui_word v = p[l];
    if(v == 0) {
      p[l] = BUI_WORD_MAX;
    } else {
      p[l] = v - 1;
      return;
    }	
  }    
  
}

bui_word *biguint::aligned_alloc(unsigned int c) {
  bui_word *p = (bui_word*) malloc(c * sizeof(bui_word));  
  if(((unsigned int)p) & 1) { throw std::runtime_error("Allocated memory not aligned!"); }
  return p;
}

/* =============================== */
/* ======== FRIEND METHODS ======= */
/* =============================== */

std::ostream& operator<<(ostream &out, biguint val) {
  std::string r;

  if(val == 0U) { return out << "0"; }

  if((val.ptr & BUI_PTR_BIT) && SIGN(UNPACK(val.ptr)[0])) {
    out << "-";
  }

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
  if(src.ptr & BUI_PTR_BIT) {
    bui_word *s(UNPACK(src.ptr));
    bui_word depth(DEPTH(s[0]));
    
    bout << s[0];
    for(bui_word i=2;i<(depth+2);++i) { bout << s[i]; }
  } else {
    bout << 1U << src.ptr;
  }
}

bistream &operator>>(bistream &bin, biguint &src) {  
  bui_word tmp,depth;
  bool sign;

  bin >> tmp;
  depth = DEPTH(tmp);
  sign = SIGN(tmp);

  if(depth == 1) {
    unsigned int v;
    bin >> v;
    biguint tmp(sign ? -v : v);
    src.swap(tmp);
  } else {  
    // inlined align_alloc
    bui_word *ptr = (bui_word*) malloc(((2*depth)+2) * sizeof(bui_word));  
    if(((unsigned int)ptr) & 1) { throw std::runtime_error("Allocated memory not aligned!"); }
    
    ptr[0] = PACK_DEPTH(depth,sign);
    ptr[1] = depth;
    // copy data
    for(bui_word i=2;i<(depth+2);++i) { bin >> ptr[i]; }
    // clear padding zeros
    memset(ptr+2+depth,0,depth*sizeof(bui_word));

    biguint tmp(ptr);
    src.swap(tmp);
  }

  return bin;
}
