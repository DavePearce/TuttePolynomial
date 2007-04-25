#include <cstring> // for memcpy
#include <stdexcept>

#include "biguint.hpp"

using namespace std;

/* =============================== */
/* ========= CONSTRUCTORS ======== */
/* =============================== */

biguint::biguint() {
  ptr = new bui_word[1];
  ptr[0] = 1;
  ptr[1] = 0U;
}

biguint::biguint(bui_word v) {
  ptr = new bui_word[1];
  ptr[0] = 1;
  ptr[1] = v;
}

biguint::biguint(bui_dword v) {
    ptr = new bui_word[2];
    ptr[0] = 2;

    for(unsigned int i=1;i<=2;i++) {
      ptr[i] = (bui_word) v;
      v >>= BUI_WORD_WIDTH;
    }    
  }

biguint::biguint(biguint const &src) {
    bui_word depth = src.ptr[0];
    ptr = new bui_word[depth+1];
    memcpy(ptr,src.ptr,(depth+1)*sizeof(bui_word));
  }
    
biguint::~biguint() { delete [] ptr; }

/* =============================== */
/* ======== ASSIGNMENT OPS ======= */
/* =============================== */
  
biguint const &biguint::operator=(bui_word v) {
  delete [] ptr;
  ptr = new bui_word[1];
  ptr[0] = 1;
  ptr[1] = v;
  return *this;
}

biguint const &biguint::operator=(bui_dword v) {
  delete [] ptr;
  ptr = new bui_word[BUI_ULONGLONG_SIZE];
  ptr[0] = BUI_ULONGLONG_SIZE;
  
  for(unsigned int i=1;i<=BUI_ULONGLONG_SIZE;i++) {
    ptr[i] = (bui_word) v;
    v >>= BUI_WORD_WIDTH;
  }    
  return *this;
}

biguint const &biguint::operator=(biguint const &src) {
  if(this != &src) {
    delete [] ptr;
    bui_word depth = src.ptr[0];
    ptr = new bui_word[depth+1];
    memcpy(ptr,src.ptr,(depth+1)*sizeof(bui_word));
  }
  return *this;
}

/* =============================== */
/* ======== COMPARISON OPS ======= */
/* =============================== */

bool biguint::operator==(bui_word v) {
  return ptr[1] == v;
}

bool biguint::operator==(bui_dword v) {
  bui_word depth(ptr[0]);
  for(bui_word i=1;i<=depth;i++) {
    if(ptr[i] != (bui_word) v) { return false; }
    v >>= BUI_WORD_WIDTH;
  }    
  if(v != 0) { return false; }
  return true;
}

bool biguint::operator==(biguint const &v) {
  bui_word depth(std::min(ptr[0],v.ptr[0]));
  for(bui_word i=1;i<=depth;i++) {
    if(ptr[i] != v.ptr[i]) { return false; }
  }
  // now, check remaining digits are zero.
  if(depth < ptr[0]) {
    bui_word m_depth(ptr[0]);
    for(bui_word i=depth+1;i<m_depth;++i) {
      if(ptr[i] != 0) { return false; }
    }
  } else {
    bui_word v_depth(ptr[0]);
    for(bui_word i=depth+1;i<v_depth;++i) {
      if(v.ptr[i] != 0) { return false; }
    }      
  }
  return true;
}

bool biguint::operator!=(bui_word v) { return !((*this) == v); }
bool biguint::operator!=(bui_dword v) { return !((*this) == v); }
bool biguint::operator!=(biguint const &v) { return !((*this) == v); }


/* =============================== */
/* ======== ARITHMETIC OPS ======= */
/* =============================== */

void biguint::operator+=(bui_word w) {
  bui_word v = ptr[1];

  ptr[1] = v + w;
  
  if((BUI_WORD_MAX-v) < w) {
    // ripple carry
    bui_word depth = ptr[0];
    for(bui_word i=1;i<depth;++i) {
      v = ptr[i+1];
      if(v == BUI_WORD_MAX) {
	ptr[i+1] = 0;
      } else {
	ptr[i+1] = v + 1;
	return;
      }	
    }
    // if we get here, then we ran out of space!
    resize(depth+1);
    ptr[depth+1]=1U;
  } 
}

void biguint::operator+=(biguint const &src) {
  bui_word depth = src.ptr[0];
  resize(depth);
  unsigned int carry = 0;
  
  for(bui_word i=0;i!=depth;++i) {
    bui_word v = ptr[i+1];
    bui_word w = src.ptr[i+1];

    ptr[i+1] = v + w + carry;   

    if(carry == 0) {
      carry = (BUI_WORD_MAX - v) < w ? 1 : 0;
    } else {
      carry = (BUI_WORD_MAX - v) <= w ? 1 : 0;
    }
  }
  
  if(carry == 1) {      
    // not enough space to hold answer!
    resize(depth+1);
    ptr[depth+1]=1U;
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
  bui_word v = ptr[1];

  ptr[1] = v - w;

  if(v < w) {
    // ripple carry
    bui_word depth = ptr[0];
    for(bui_word i=1;i<depth;++i) {
      v = ptr[i+1];
      if(v == 0) {
	ptr[i+1] = BUI_WORD_MAX;
      } else {
	ptr[i+1] = v - 1;
	return;
      }	
    }    
    // this is a negative number!
    throw std::runtime_error("biguint cannot go negative"); 
  }
}

void biguint::operator-=(biguint const &src) {
  bui_word depth = src.ptr[0];
  resize(depth);
  unsigned int borrow = 0;
  
  for(bui_word i=0;i!=depth;++i) {
    bui_word v = ptr[i+1];
    bui_word w = src.ptr[i+1];

    ptr[i+1] = v - w - borrow;    

    if(borrow == 0) {
      borrow = v < w ? 1 : 0;
    } else {
      borrow = v <= w ? 1 : 0;
    }
  }
  
  if(borrow == 1) {      
    // this is a negative number!
    throw std::runtime_error("biguint cannot go negative"); 
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
  bui_word depth(ptr[0]);
  bui_word overflow = 0;

  for(bui_word i=1;i<=depth;++i) {
    bui_dword w = ptr[i];
    w = (w * v) + overflow;
    ptr[i] = w;
    overflow = w >> BUI_WORD_WIDTH;
  }
  if(overflow > 0) {
    // need additional space
    resize(depth+1);
    ptr[depth+1]=overflow;
  }
}

biguint biguint::operator*(bui_word w) const {
  biguint r(*this);
  r *= w;
  return r;
}

void biguint::operator/=(bui_word v) {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  bui_word remainder=0;
  
  for(bui_word i=ptr[0];i>0;--i) {
    bui_dword w = remainder;
    w = (w << BUI_WORD_WIDTH) + ptr[i];
    ptr[i] = w / v;
    remainder = w % v;
  }    
}

biguint biguint::operator/(bui_word w) const {
  biguint r(*this);
  r /= w;
  return r;
}

void biguint::operator%=(bui_word v) {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  bui_word remainder=0;
  
  for(bui_word i=ptr[0];i>0;--i) {
    bui_dword w = remainder;
    w = (w << BUI_WORD_WIDTH) + ptr[i];
    remainder = w % v;
  }    

  resize(1);
  ptr[1] = remainder;
}

bui_word biguint::operator%(bui_word v) const {
  if(v == 0) { throw new std::runtime_error("divide by zero"); }
  bui_word remainder=0;
  
  for(bui_word i=ptr[0];i>0;--i) {
    bui_dword w = remainder;
    w = (w << BUI_WORD_WIDTH) + ptr[i];
    remainder = w % v;
  }    

  return remainder;
}

/* =============================== */
/* ======== CONVERSION OPS ======= */
/* =============================== */

unsigned int biguint::c_uint() const {
  if(ptr[0] > BUI_UINT_SIZE) { throw runtime_error("biguint too large for unsigned int"); }
  return ptr[1];
}  

unsigned long biguint::c_ulong() const {
  if(ptr[0] > BUI_ULONG_SIZE) { throw runtime_error("biguint too large for unsigned long"); }
  return ptr[1];
}  

unsigned long long biguint::c_ulonglong() const {
  bui_word depth = ptr[0];
  if(depth > BUI_ULONGLONG_SIZE) { throw runtime_error("biguint too large for unsigned long long"); }
  unsigned long long r=0;
  for(bui_word i=depth;i>0;--i) {
    r <<= BUI_WORD_WIDTH;
    r += ptr[i];
  }
  return r;
}  

/* =============================== */
/* ======== HELPER METHODS ======= */
/* =============================== */
  
void biguint::resize(bui_word ndepth) {
  bui_word depth = ptr[0];
  if(depth >= ndepth) { return; }
  bui_word *nptr = new bui_word[ndepth+1];        
  nptr[0]=ndepth;
  memset(nptr+depth+1,0,(ndepth-depth)*sizeof(bui_word));
  memcpy(nptr+1,ptr+1,depth*sizeof(bui_word));
  delete [] ptr;
  ptr = nptr;
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
