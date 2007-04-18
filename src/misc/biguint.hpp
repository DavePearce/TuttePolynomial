#ifndef BIGUINT_HPP
#define BIGUINT_HPP

#include <cstring> // for memcpy
#include <climits>
#include <stdexcept>

// this class provides arbitrary sized integers
typedef unsigned int bui_word;
typedef unsigned long long bui_dword;

#define BUI_WORD_WIDTH 32U
#define BUI_DWORD_WIDTH 32U
#define BUI_WORD_MAX UINT_MAX

// problem when wors size > unsigned int ?
#define BUI_UINT_SIZE (sizeof(unsigned int) / sizeof(bui_word))
#define BUI_ULONG_SIZE (sizeof(unsigned long) / sizeof(bui_word))
#define BUI_ULONGLONG_SIZE (sizeof(unsigned long long) / sizeof(bui_word))

class biguint {
private:
  bui_word *ptr;
public:
  /* =============================== */
  /* ========= CONSTRUCTORS ======== */
  /* =============================== */

  biguint(unsigned int v) {
    ptr = new bui_word[BUI_UINT_SIZE];
    ptr[0] = BUI_UINT_SIZE;

    for(unsigned int i=1;i<=BUI_UINT_SIZE;i++) {
      ptr[i] = (bui_word) v;
      v >>= BUI_WORD_WIDTH;
    }    
  }

  biguint(unsigned long v) {
    ptr = new bui_word[BUI_ULONG_SIZE];
    ptr[0] = BUI_ULONG_SIZE;

    for(unsigned int i=1;i<=BUI_ULONG_SIZE;i++) {
      ptr[i] = (bui_word) v;
      v >>= BUI_WORD_WIDTH;
    }    
  }

  biguint(unsigned long long v) {
    ptr = new bui_word[BUI_ULONGLONG_SIZE];
    ptr[0] = BUI_ULONGLONG_SIZE;

    for(unsigned int i=1;i<=BUI_ULONGLONG_SIZE;i++) {
      ptr[i] = (bui_word) v;
      v >>= BUI_WORD_WIDTH;
    }    
  }

  biguint(biguint const &src) {
    bui_word depth = src.ptr[0];
    ptr = new bui_word[depth+1];
    memcpy(ptr,src.ptr,(depth+1)*sizeof(bui_word));
  }
    
  ~biguint() { delete [] ptr; }

  /* =============================== */
  /* ======== ASSIGNMENT OPS ======= */
  /* =============================== */
  
  biguint const &operator=(unsigned int v) {
    delete [] ptr;
    ptr = new bui_word[BUI_UINT_SIZE];
    ptr[0] = BUI_UINT_SIZE;

    for(unsigned int i=1;i<=BUI_UINT_SIZE;i++) {
      ptr[i] = (bui_word) v;
      v >>= BUI_WORD_WIDTH;
    }    
    return *this;
  }

  biguint const &operator=(unsigned long v) {
    delete [] ptr;
    ptr = new bui_word[BUI_ULONG_SIZE];
    ptr[0] = BUI_ULONG_SIZE;

    for(unsigned int i=1;i<=BUI_ULONG_SIZE;i++) {
      ptr[i] = (bui_word) v;
      v >>= BUI_WORD_WIDTH;
    }    
    return *this;
  }

  biguint const &operator=(unsigned long long v) {
    delete [] ptr;
    ptr = new bui_word[BUI_ULONGLONG_SIZE];
    ptr[0] = BUI_ULONGLONG_SIZE;

    for(unsigned int i=1;i<=BUI_ULONGLONG_SIZE;i++) {
      ptr[i] = (bui_word) v;
      v >>= BUI_WORD_WIDTH;
    }    
    return *this;
  }

  biguint const &operator=(biguint const &src) {
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

  bool operator==(unsigned int v) {
    bui_word depth(ptr[0]);
    for(bui_word i=1;i<=depth;i++) {
      if(ptr[i] != (bui_word) v) { return false; }
      v >>= BUI_WORD_WIDTH;
    }    
    if(v != 0) { return false; }
    return true;
  }

  bool operator==(unsigned long v) {
    bui_word depth(ptr[0]);
    for(bui_word i=1;i<=depth;i++) {
      if(ptr[i] != (bui_word) v) { return false; }
      v >>= BUI_WORD_WIDTH;
    }    
    if(v != 0) { return false; }
    return true;
  }

  bool operator==(unsigned long long v) {
    bui_word depth(ptr[0]);
    for(bui_word i=1;i<=depth;i++) {
      if(ptr[i] != (bui_word) v) { return false; }
      v >>= BUI_WORD_WIDTH;
    }    
    if(v != 0) { return false; }
    return true;
  }

  bool operator==(biguint const &v) {
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

  /* =============================== */
  /* ======== ARITHMETIC OPS ======= */
  /* =============================== */

  void operator+=(unsigned int w) {
    unsigned int carry = 0;
    bui_word v = ptr[1];
    
    if((BUI_WORD_MAX-v) < w) {
      // overflow
      ptr[1] = w - 1U - (BUI_WORD_MAX - v);
      // ripple carry
      bui_word depth = ptr[0];
      for(bui_word i=1;i<depth;++i) {
	v = ptr[i+1];
	if(v == BUI_WORD_MAX) {
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
    bui_word depth = src.ptr[0];
    resize(depth);
    unsigned int carry = 0;
    
    for(bui_word i=0;i!=depth;++i) {
      bui_word v = ptr[i+1];
      bui_word w = src.ptr[i+1];

      if(carry == 0) {
	if((BUI_WORD_MAX - v) < w) {
	  // overflow
	  carry = 1;
	  v = w - 1U - (BUI_WORD_MAX - v);
	} else { v = v + w; }
      } else {
	if((BUI_WORD_MAX - v) <= w) {
	  // overflow
	  carry = 1;
	  v = w - (BUI_WORD_MAX - v);
	} else { v = v + w + 1; }
      }
      ptr[i+1] = v;
    }

    if(carry == 1) {      
      // not enough space to hold answer!
      resize(depth+1);
      ptr[depth+1]=1U;
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
    bui_word remainder=0;

    for(bui_word i=ptr[0];i>0;++i) {
      bui_dword w = remainder;
      w = (w << BUI_WORD_WIDTH) + ptr[i];
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
    bui_word depth = ptr[0];
    if(depth > 2) { throw std::runtime_error("biguint too large for unsigned int"); }
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
  
private:
  void resize(bui_word ndepth) {
    bui_word depth = ptr[0];
    if(depth >= ndepth) { return; }
    bui_word *nptr = new bui_word[ndepth+1];        
    nptr[0]=ndepth;
    memset(nptr+depth+1,0,(ndepth-depth)*sizeof(bui_word));
    memcpy(nptr+1,ptr+1,depth*sizeof(bui_word));
    delete [] ptr;
    ptr = nptr;
  }
};

#endif
