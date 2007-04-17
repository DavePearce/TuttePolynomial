#ifndef BIGUINT_HPP
#define BIGUINT_HPP

#include <cstring> // for memcpy
#include <stdexcept>
#include <climits>

// this class provides arbitrary sized integers

class biguint {
private:
  unsigned int *ptr;
public:
  biguint(unsigned int v) {
    ptr = new unsigned int[2];
    ptr[0]=1;
    ptr[1] = v;
  }

  biguint(biguint const &src) {
    unsigned int depth = src.ptr[0];
    ptr = new unsigned int[depth+1];
    memcpy(ptr,src.ptr,(depth+1)*sizeof(unsigned int));
  }
    
  ~biguint() { delete [] ptr; }
  
  biguint const &operator=(biguint const &src) {
    if(this != &src) {
      delete [] ptr;
      unsigned int depth = src.ptr[0];
      ptr = new unsigned int[depth+1];
      memcpy(ptr,src.ptr,(depth+1)*sizeof(unsigned int));
    }
    return *this;
  }

  biguint const &operator=(unsigned int v) {
    delete [] ptr;
    ptr = new unsigned int[2];
    ptr[0]=1;
    ptr[1] = v;
    return *this;
  }

  /* =============================== */
  /* ======== COMPARISON OPS ======= */
  /* =============================== */

  bool operator==(unsigned int v) {
    if(ptr[0] > 1) { return false; }
    return ptr[1] == v;
  }

  /* =============================== */
  /* ======== ARITHMETIC OPS ======= */
  /* =============================== */

  void operator+=(unsigned int w) {
    unsigned int carry = 0;
    unsigned int v = ptr[1];
    
    if((UINT_MAX-v) < w) {
      // overflow
      ptr[1] = w - 1 - (UINT_MAX - v);
      // ripple carry
      unsigned int depth = ptr[0];
      for(unsigned int i=1;i<depth;++i) {
	v = ptr[i+1];
	if(v == UINT_MAX) {
	  carry = 1; v = 0;
	  ptr[i+1] = 0;
	} else {
	  carry = 0;
	  ptr[i+1] = v + 1;
	  return;
	}	
      }
      // if we get here, then we ran out of space!
      resize(depth+1);
      ptr[depth+1]=1U;
    } else { 
      v = v + w; 
      ptr[1] = v;
    }
  }

  void operator+=(biguint const &src) {
    unsigned int depth = src.ptr[0];
    resize(depth);
    unsigned int carry = 0;
    
    for(unsigned int i=0;i!=depth;++i) {
      unsigned int v = ptr[i+1];
      unsigned int w = src.ptr[i+1];
      if(carry == 0) {
	if((UINT_MAX - v) < w) {
	  // overflow
	  carry = 1;
	  v = w - (UINT_MAX - v);
	} else { v = v + w; }
      } else {
	if((UINT_MAX - v) <= w) {
	  // overflow
	  carry = 1;
	  v = 1 + w - (UINT_MAX - v);
	} else { v = v + w + 1; }
      }
      ptr[i+1] = v;
    }
    if(carry == 1) {
      // not enough space to hold answer,
      // so resize again!!
      resize(depth+1);
      ptr[depth+1]=1;
    }
  }

  biguint operator+(biguint const &w) const {
    biguint r(*this);
    r += w;
    return r;
  }

  biguint operator+(unsigned int w) const {
    biguint r(*this);
    r += w;
    return r;
  }

  void operator/=(unsigned int v) {
    if(v == 0) { throw new std::runtime_error("divide by zero"); }
    unsigned int remainder=0;

    for(unsigned int i=ptr[0];i>0;++i) {
      unsigned long long w = remainder; 
      w = (w << 32U) + ptr[i];
      ptr[i] = w / v;
      remainder = w % v;
    }    
  }

  /* =============================== */
  /* ======== CONVERSION OPS ======= */
  /* =============================== */

  unsigned int c_uint() const {
    if(ptr[0] > 1) { throw std::runtime_error("biguint too large for unsigned int"); }
    return ptr[1];
  }  

  unsigned long c_ulong() const {
    if(ptr[0] > 1) { throw std::runtime_error("biguint too large for unsigned int"); }
    return ptr[1];
  }  

  unsigned long long c_ulonglong() const {
    unsigned int depth = ptr[0];
    if(depth > 2) { throw std::runtime_error("biguint too large for unsigned int"); }
    unsigned long long r=0;
    for(unsigned int i=depth;i>0;--i) {
      r <<= 32U;
      r += ptr[i];
    }
    return r;
  }  

  /* =============================== */
  /* ======== HELPER METHODS ======= */
  /* =============================== */
  
private:
  void resize(unsigned int ndepth) {
    unsigned int depth = ptr[0];
    if(depth >= ndepth) { return; }
    unsigned int *nptr = new unsigned int[ndepth+1];        
    nptr[0]=ndepth;
    memset(nptr+depth+1,0,(ndepth-depth)*sizeof(unsigned int));
    memcpy(nptr+1,ptr+1,depth*sizeof(unsigned int));
    delete [] ptr;
    ptr = nptr;
  }
};

#endif
