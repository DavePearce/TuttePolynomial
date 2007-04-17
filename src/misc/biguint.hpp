#ifndef BIGUINT_HPP
#define BIGUINT_HPP

// this class provides arbitrary sized integers

class biguint {
private:
  unsigned int *ptr;
public:
  bigint(unsigned int v) {
    ptr = new unsigned int[2];
    ptr[0]=1;
    ptr[1] = v;
  }

  bigint(bigint const &src) {
    unsigned int depth = src.ptr[0];
    ptr = new unsigned int[depth+1];
    memcpy(ptr,src.ptr,(depth+1)*sizeof(unsigned int));
  }
    
  ~bigint() { delete [] ptr; }
  
  bigint const &operator=(bigint const &src) {
    if(this != &src) {
      delete [] ptr;
      unsigned int depth = src.ptr[0];
      ptr = new unsigned int[depth+1];
      memcpy(ptr,src.ptr,(depth+1)*sizeof(unsigned int));
    }
    return *this;
  }

  bigint const &operator=(unsigned int v) {
    if(this != &src) {
      delete [] ptr;
      ptr = new unsigned int[2];
      ptr[0]=1;
      ptr[1] = v;
    }
    return *this;
  }

  /* =============================== */
  /* ======== ARITHMETIC OPS ======= */
  /* =============================== */

  void operator+=(unsigned int w) {
    unsigned int carry = 0;
    unsigned int v = ptr[1];
    
    if((UINT_MAX-v) < w) {
      // overflow
      v = w - (UINT_MAX - v);
      ptr[1] = v;
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
    } else { 
      v = v + w; 
      ptr[1] = v;
    }
  }

  void operator+=(bigint const &src) {
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
  }

  bigint operator+(bigint const &w) const {
    bigint r(*this);
    r += w;
    return r;
  }

  bigint operator+(unsigned int w) const {
    bigint r(*this);
    r += w;
    return r;
  }

  /* =============================== */
  /* ======== CONVERSION OPS ======= */
  /* =============================== */

  
}

#endif
