#include <cstring> // for memcpy
#include <stdexcept>

#include "biguint.hpp"

using namespace std;

#define PACK(x) ((((bui_word)x) >> 1U) | BUI_PTR_BIT)
#define UNPACK(x) ((bui_word*)(x << 1U))

/* =============================== */
/* ========= CONSTRUCTORS ======== */
/* =============================== */

biguint::biguint() {
  ptr = 0U;
}

biguint::biguint(bui_word v) { clone(v); }
biguint::biguint(bui_dword v) { clone(v); }
biguint::biguint(biguint const &src) { clone(src); }

biguint::biguint(bui_word v, bui_word depth) { 
  bui_word *p = aligned_alloc(depth+1);
  p[0]=depth;
  memset(p+1,0,depth*sizeof(bui_word));
  ptr = PACK(p);
}


biguint::biguint(bui_word *p) {
  ptr = PACK(p);
}
    
biguint::~biguint() { destroy(); }

/* =============================== */
/* ======== ASSIGNMENT OPS ======= */
/* =============================== */
  
biguint const &biguint::operator=(bui_word v) {
  destroy();
  clone(v);
  return *this;
}

biguint const &biguint::operator=(bui_dword v) {
  destroy();
  clone(v);
  return *this;
}

biguint const &biguint::operator=(biguint const &src) {
  if(this != &src) {
    destroy();
    clone(src);
  }
  return *this;
}

void biguint::swap(biguint &src) {
  std::swap(ptr,src.ptr);
}

/* =============================== */
/* ======== COMPARISON OPS ======= */
/* =============================== */

bool biguint::operator==(bui_word v) const {
  if(ptr & BUI_PTR_BIT) {    
    bui_word *p = UNPACK(ptr);
    if(p[1] != v) { return false; }
    unsigned int depth(p[0]);
    for(unsigned int i=2;i<=depth;++i) {
      if(p[i] != 0) { return false; }
    }
    return true;
  } else {
    return ptr == v;
  } 
}

bool biguint::operator==(bui_dword v) const {
  if(ptr & BUI_PTR_BIT) {
    bui_word *p = UNPACK(ptr);
    bui_word depth(p[0]);
    for(bui_word i=1;i<=depth;i++) {
      if(p[i] != (bui_word) v) { return false; }
      v >>= BUI_WORD_WIDTH;
    }    
    if(v != 0) { return false; }
    return true;
  } else {
    return (v <= BUI_WORD_MAX) && ptr == v;
  } 
}

bool biguint::operator==(biguint const &v) const {
  if((ptr & BUI_PTR_BIT) == 0) {
    return v == ptr;
  } else if((v.ptr & BUI_PTR_BIT) == 0) {
    return (*this) == v.ptr;
  } else {
    bui_word *p(UNPACK(ptr));
    bui_word *s(UNPACK(v.ptr));
    bui_word depth(std::min(p[0],s[0]));
    for(bui_word i=1;i<=depth;i++) {
      if(p[i] != s[i]) { return false; }
    }
    // now, check remaining digits are zero.    
    bui_word m_depth(p[0]);
    for(bui_word i=depth+1;i<m_depth;++i) {
      if(p[i] != 0) { return false; }
    }
    bui_word v_depth(s[0]);
    for(bui_word i=depth+1;i<v_depth;++i) {
      if(s[i] != 0) { return false; }
    }      
  }
  return true;
}

bool biguint::operator!=(bui_word v) const { return !((*this) == v); }
bool biguint::operator!=(bui_dword v) const { return !((*this) == v); }
bool biguint::operator!=(biguint const &v) const { return !((*this) == v); }

/* =============================== */
/* ======== ARITHMETIC OPS ======= */
/* =============================== */

void biguint::operator+=(bui_word w) {
  if(ptr & BUI_PTR_BIT) {    
    bui_word *p(UNPACK(ptr));
    bui_word v = p[1];
    w = v + w;
    p[1] = w;
    if(w < v) { ripple_carry(1); }
  } else {
    bui_word v = ptr;
    ptr = v + w;
    if(ptr < v) {
      bui_word *p = aligned_alloc(3); 
      p[0] = 2U;
      p[1] = ptr;
      p[2] = 1U;
      ptr = PACK(p);
    } else if(ptr & BUI_PTR_BIT) {
      clone(ptr);
    }
  }
}

void biguint::operator+=(biguint const &src) {
  if((src.ptr & BUI_PTR_BIT) == 0) { 
    (*this) += src.ptr; 
  } else {
    bui_word *s(UNPACK(src.ptr));
    bui_word depth = s[0];
    bui_word *p;
    
    if((ptr & BUI_PTR_BIT) == 0) { 
      // assume it needs to go big
      p = aligned_alloc(depth+1);
      p[0] = depth;      
      p[1] = ptr;
      for(int i=2;i<=depth;++i) { p[i] = 0U; }
      ptr = PACK(p);
    } else {
      expand(depth);
      p = UNPACK(ptr);
    }

    unsigned int carry = 0;
    
    for(bui_word i=1;i<=depth;++i) {
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
  if(ptr & BUI_PTR_BIT) {    
    bui_word *p(UNPACK(ptr));
    bui_word v = p[1];
    p[1] = v - w;
    if(v < w) { ripple_borrow(1); }
  } else {
    bui_word v(ptr);
    ptr = v - w;
    if(v < w) {   throw std::runtime_error("biguint cannot go negative"); }
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
      p = aligned_alloc(depth+1);
      p[0] = depth;      
      p[1] = ptr;
      for(int i=2;i<=depth;++i) { p[i] = 0U; }
      ptr = PACK(p);
    } else {
      expand(depth);
      p = UNPACK(ptr);
    }

    unsigned int borrow = 0;

    for(bui_word i=1;i<=depth;++i) {
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
  if(ptr & BUI_PTR_BIT) {    
    // complicated case!
    bui_word *p(UNPACK(ptr));
    bui_word depth(p[0]);
    bui_word overflow = 0;

    for(bui_word i=1;i<=depth;++i) {
      bui_dword w = p[i];
      w = (w * v) + overflow;
      p[i] = w;
      overflow = w >> BUI_WORD_WIDTH;
    }
    
    if(overflow > 0) {
      // need additional space
      expand(depth+1);   
      p = UNPACK(ptr); 
      p[depth+1] = overflow;
    }
  } else {    
    // easier case!
    bui_dword w = ((bui_dword) ptr) * v;
    if(w >= BUI_PTR_BIT) { 
      // build new object
      bui_word *p = aligned_alloc(3);
      ptr = PACK(p);
      p[0] = 2U;
      p[1] = w;
      p[2] = w >> BUI_WORD_WIDTH;
    } else {
      ptr = w;
    }
  }
}

void biguint::operator*=(bui_dword v) {
  biguint tmp(v);
  (*this) *= tmp;
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
    biguint ans(0U,depth);

    for(unsigned int j=0;j<depth;++j) {
      biguint tmp(*this);
      tmp *= s[j+1];

      bui_word *tp(UNPACK(tmp.ptr));      
      unsigned int t_depth(tp[0]);
      unsigned int carry = 0;

      ans.expand(j + t_depth); 

      bui_word *ap(UNPACK(ans.ptr));      

      // standard add, although slightly modified
      // to give the base shift for free.
      for(bui_word i=0;i!=t_depth;++i) {
	bui_word v = ap[j+i+1];
	bui_word w = tp[i+1];
	
	w = v + w + carry;   
	ap[j+i+1] = w;

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

biguint biguint::operator*(bui_dword w) const {
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
      tmp *= s[j+1];
      
      bui_word *tp(UNPACK(tmp.ptr));      
      unsigned int t_depth(tp[0]);
      unsigned int carry = 0;
      
      ans.expand(j + t_depth); 
      bui_word *ap(UNPACK(ans.ptr));      

      // standard add, although slightly modified
      // to give the base shift for free.
      for(bui_word i=0;i!=t_depth;++i) {
	bui_word v = ap[j+i+1];
	bui_word w = tp[i+1];

	w = v + w + carry;   
	ap[j+i+1] = w;
	
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
  if(ptr & BUI_PTR_BIT) {
    bui_word *p(UNPACK(ptr));
    bui_word remainder=0;
    
    for(bui_word i=p[0];i>0;--i) {
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

biguint biguint::operator/(bui_word w) const {
  biguint r(*this);
  r /= w;
  return r;
}

void biguint::operator%=(bui_word v) {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  if(ptr & BUI_PTR_BIT) {
    bui_word *p(UNPACK(ptr));
    bui_word remainder=0;
    
    for(bui_word i=p[0];i>0;--i) {
      bui_dword w = remainder;
      w = (w << BUI_WORD_WIDTH) + p[i];
      remainder = w % v;
    }    
    clone(remainder);
  } else {
    ptr = ptr % v;
  }
}

bui_word biguint::operator%(bui_word v) const {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  if(ptr & BUI_PTR_BIT) {
    bui_word *p(UNPACK(ptr));
    bui_word remainder=0;
  
   for(bui_word i=p[0];i>0;--i) {
     bui_dword w = remainder;
     w = (w << BUI_WORD_WIDTH) + p[i];
     remainder = w % v;
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
    
    for(unsigned int i=1;i<v;++i) {
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
  if(ptr & BUI_PTR_BIT) {
    bui_word *p(UNPACK(ptr));
    if(p[0] > BUI_UINT_SIZE) { throw runtime_error("biguint too large for unsigned int"); }
    return p[1];
  } else {
    return ptr;
  }
}  

unsigned long biguint::c_ulong() const {
  if(ptr & BUI_PTR_BIT) {
    bui_word *p(UNPACK(ptr));
    if(p[0] > BUI_ULONG_SIZE) { throw runtime_error("biguint too large for unsigned int"); }
    return p[1];
  } else {
    return ptr;
  }
}  

unsigned long long biguint::c_ulonglong() const {
  if(ptr & BUI_PTR_BIT) {
    bui_word *p(UNPACK(ptr));
    bui_word depth = p[0];
    if(depth > BUI_ULONGLONG_SIZE) { throw runtime_error("biguint too large for unsigned long long"); }
    unsigned long long r=0;
    for(bui_word i=depth;i>0;--i) {
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

void biguint::destroy() {
  if(ptr & BUI_PTR_BIT) { free(UNPACK(ptr)); }
}  

void biguint::clone(bui_word v) {
  if(v & BUI_PTR_BIT) {
    bui_word *p = aligned_alloc(2);
    ptr = PACK(p);
    p[0] = 1;
    p[1] = v;
  } else {
    ptr = v;
  }
}

void biguint::clone(bui_dword v) {
  bui_word *p = aligned_alloc(3);
  p[0] = 2;
  
  for(unsigned int i=1;i<=2;i++) {
    p[i] = (bui_word) v;
    v >>= BUI_WORD_WIDTH;
  }    
  ptr = PACK(p);
}

void biguint::clone(biguint const &src) {
  if(src.ptr & BUI_PTR_BIT) {
    bui_word *s = UNPACK(src.ptr);
    bui_word depth = s[0];
    bui_word *p = aligned_alloc(depth+1);
    memcpy(p,s,(depth+1)*sizeof(bui_word));
    ptr = PACK(p);
  } else {
    ptr = src.ptr;
  }
}

// Expands the array to depth ndepth.  If ndepth < current depth,
// nothing happens.  
//
// PRE: assumes this in array format
void biguint::expand(bui_word ndepth) {
  bui_word *p(UNPACK(ptr));
  bui_word depth = p[0];
  if(depth >= ndepth) { return; }
  bui_word *nptr = aligned_alloc(ndepth+1);
  nptr[0]=ndepth;
  memset(nptr+depth+1,0,(ndepth-depth)*sizeof(bui_word));
  memcpy(nptr+1,p+1,depth*sizeof(bui_word));
  free(p);
  ptr = PACK(nptr);
}

// Resizes the array to depth ndepth.  If ndepth < current depth, this
// will trim the array; otherwise, it will expand it.  Also, if ndepth
// <= 1, it will revert to word format.
//
// PRE: assumes this in array format
void biguint::resize(bui_word ndepth) {
  bui_word *p(UNPACK(ptr));
  bui_word depth = p[0];
  if(ndepth == 0) {
    // this can happen in some slightly strange cases
    ptr = 0U;
  } else if(ndepth == 1 && !(p[1] & BUI_PTR_BIT)) {
    // resizing to something that fits
    // in the word format
    ptr = p[1];    
  } else {
    bui_word *nptr = aligned_alloc(ndepth+1);
    nptr[0] = ndepth;
    if(ndepth > depth) { 
      memset(nptr+depth+1,0,(ndepth-depth)*sizeof(bui_word)); 
      memcpy(nptr+1,p+1,depth*sizeof(bui_word));
    } else {
      memcpy(nptr+1,p+1,ndepth*sizeof(bui_word));
    }
    ptr = PACK(nptr);
  }
  free(p); // free memory!
}

void biguint::ripple_carry(bui_word level) {
  bui_word *p(UNPACK(ptr));
  unsigned int depth(p[0]);

  for(unsigned int i(level+1);i<=depth;++i) {
    bui_word v = p[i];
    
    if(v == BUI_WORD_MAX) { p[i] = 0; } 
    else {
      p[i] = v + 1;
      return;
    }	
  }
  // not enough space to hold answer!
  expand(depth+1);
  UNPACK(ptr)[depth+1]=1U;  
}

void biguint::ripple_borrow(bui_word level) {  
  bui_word *p(UNPACK(ptr));
  bui_word depth = p[0];
  for(bui_word i(level+1);i<=depth;++i) {
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
    bui_word depth(s[0]);
    
    bout << depth;
    for(bui_word i=1;i<=depth;++i) { bout << s[i]; }
  } else {
    bout << 1U << src.ptr;
  }
}

bistream &operator>>(bistream &bin, biguint &src) {  
  bui_word depth;

  bin >> depth;
  if(depth == 1) {
    unsigned int v;
    bin >> v;
    biguint tmp(v);
    src.swap(tmp);
  } else {  
    bui_word *ptr = new bui_word[depth+1];
    ptr[0] = depth;
    
    for(bui_word i=1;i<=depth;++i) { bin >> ptr[i]; }

    biguint tmp(ptr);
    src.swap(tmp);
  }

  return bin;
}

