#ifndef BIGWORD_HPP
#define BIGWORD_HPP

#include <stdexcept>
#include "../../config.h"

#define BW_WORD_SIZE (SIZEOF_INT*8U)
#define BW_LEFTMOST_BIT (1U << (BW_WORD_SIZE-1))

// The largest value a WORD_SIZE-1 signed integer can hold
#define BW_SWORD_MAX ((int) (((unsigned int) -1) >> 2U))
// The smallest value a WORD_SIZE-1 signed integer can hold
#define BW_SWORD_MIN ((int) ((((unsigned int) -1) >> 2U) | BW_LEFTMOST_BIT)+1)

typedef struct {
  unsigned sign:1;
  unsigned length:(BW_WORD_SIZE-1);
  unsigned padding;
} bw_header;

// PACK POINTER INTO WORD FORMAT (WITH LEFTMOST BIT = 1)
#define BW_PACK_PTR(x) ((((unsigned int)x) >> 1U) | BW_LEFTMOST_BIT)

// UNPACK POINTER FROM WORD FORMAT (WITH LEFTMOST BIT = 1)
#define BW_UNPACK_PTR(x) ((bw_header*)(x << 1U))

// SIZE OF BW_HEADER STRUCT IN WORDS (NOT BYTES)
#define BW_SIZEOF_HEADER 2U

// PACK INTEGER INTO WORD FORMAT
#define BW_PACK_VALUE(x) (x&~BW_LEFTMOST_BIT)

// UNPACK INTEGER FROM WORD FORMAT (WITH LEFTMOST BIT = 0)
#define BW_UNPACK_VALUE(x) (((int)(x << 1U)) >> 1)

// GET MAGNITUDE OF VALUE
#define BW_ABS_VALUE(x) ((x == INT_MIN) ? ((unsigned int)INT_MAX)+1: abs(x))

class bigword {
private:
  // ptr is either a WORD_SIZE-1 bit int, or a pointer to an array of
  // unsigned int.  So, on a 32-bit machine it is either a 31-bit
  // signed integer, or a pointer to an array of unsigned ints.
  //
  // ======================================================================
  // When in WORD MODE, the leftmost bit is zero.  e.g.
  //
  // bit : 31 |            0
  // -----------------------
  //        0 |   signed int
  //
  // Therefore, to extract the signed integer it must be signed
  // extended first.
  //
  // ======================================================================
  // When in ARRAY MODE, the integer is represented in sign magnitude
  // representation, as follows:
  //
  // Index | Meaning
  // -------------------------------
  // 0     | Length of digits as WORD_SIZE-1 bit unsigned int.  The 
  //       | rightmost bit gives the sign of the whole integer.
  //       |
  // 1     | Padding, as full unsigned int.  This counts the number of available
  //       | unused digits at the end of the array.
  //       |
  // ...   | The digit bits themselves, stored as full unsigned ints in little 
  //       | endian order.
  // 
  unsigned int ptr; 
  
public:
  // Construct a bigword repesenting zero.  This will store the
  // integer in WORD MODE.
  bigword() { bigword(0); }

  // Construct a bigword repesenting the integer value.  If possible
  // it will store the integer in WORD MODE; otherwise, (if the
  // integer is too big) it will use ARRAY MODE.
  bigword(int value) {
    clone(value);
  }
  
  // Construct a clone of the bigword.  This will employ the same
  // representation of the integer.
  bigword(bigword const &value) {
    clone(value);
  }

  inline bigword const &operator=(int v) {
    if(ptr & BW_LEFTMOST_BIT) { free(BW_UNPACK_PTR(ptr)); }
    clone(v);
    return *this;
  }
  
  inline bigword const &operator=(bigword const &src) {    
    if(this != &src) {
      if(src.ptr & BW_LEFTMOST_BIT) {
	if(ptr & BW_LEFTMOST_BIT) {
	  bw_header *s = BW_UNPACK_PTR(src.ptr);
	  bw_header *p = BW_UNPACK_PTR(ptr);
	  // attempt to reuse memory where possible.
	  unsigned int src_length = s->length;
	  unsigned int length = p->length;
	  unsigned int padding = p->padding;	
	  
	  if(src_length <= (length + padding)) {
	    memcpy(p,s,(src_length + BW_SIZEOF_HEADER)*sizeof(unsigned int));
	    memset(((unsigned int*)p) + src_length + sizeof(bw_header),0,((length+padding)-src_length)*sizeof(unsigned int));
	  } else {
	    free(BW_UNPACK_PTR(ptr));
	    clone(src);
	  }
	} else {
	  clone(src);
	}	
      } else {
	if(ptr & BW_LEFTMOST_BIT) { free(BW_UNPACK_PTR(ptr)); };
	ptr = src.ptr;
      }
    }
    return *this;
  }
  
  inline void swap(bigword &src) {
    std::swap(ptr,src.ptr);
  }

  // indicate wether in ARRAY or WORD MODE.
  inline bool is_array() {
    return ptr & BW_LEFTMOST_BIT;
  }

  // Return the length of the digit array.  Note, this operation is
  // meaningless in WORD MODE.
  inline unsigned int length() const {
    return BW_UNPACK_PTR(ptr)->length;
  }
    
  // Expand the length of the digit array to be at least length.  If
  // the array was already longer than length then it is not modified.
  // New digits are filled in with zero.
  inline void expand(unsigned int nlength) {    
    if(ptr & BW_LEFTMOST_BIT) {
      // ARRAY MODE
      bw_header *p(BW_UNPACK_PTR(ptr));
      bool sign(p->sign);
      unsigned int length = p->length;
      unsigned int padding = p->padding;
      if(length >= nlength) { return; }
      else if((length+padding) >= nlength) {
	// no need to expand as we have space in the padding
	p->length = nlength;
	p->padding = (length+padding)-nlength;
      } else {
	bw_header *nptr = aligned_alloc((nlength*2)+BW_SIZEOF_HEADER);
	nptr->sign = sign;
	nptr->length = nlength;
	nptr->padding = nlength;

	memset(((unsigned int*)nptr)+length+BW_SIZEOF_HEADER,0,((nlength*2)-length)*sizeof(unsigned int));
	memcpy(nptr+2,p+2,length*sizeof(unsigned int));
	free(p);
	ptr = BW_PACK_PTR(nptr);
      }
    } else {
      // WORD MODE
      int word = BW_UNPACK_VALUE(ptr);
      bw_header *nptr = aligned_alloc((nlength*2)+BW_SIZEOF_HEADER);
      unsigned int *wptr = ((unsigned int*)nptr)+BW_SIZEOF_HEADER;

      nptr->sign = word < 0 ? 1 : 0;
      nptr->length = nlength;
      nptr->padding = nlength;

      wptr[0] = BW_ABS_VALUE(word);

      // zero padding bits
      memset(wptr+nlength,0,((nlength*2)-nlength)*sizeof(unsigned int));

      ptr = BW_PACK_PTR(nptr);
    }
  }

private:
  
  inline void clone(int v) {
    if((v < BW_SWORD_MIN) || (v > BW_SWORD_MAX)) {
      // In this case, the integer is too large to fit into WORD MODE.
      // Therefore, we must use ARRAY MODE with a single digit.
      bw_header *nptr = aligned_alloc(1+BW_SIZEOF_HEADER);
      unsigned int *wptr = ((unsigned int*)nptr)+BW_SIZEOF_HEADER;

      ptr = BW_PACK_PTR(nptr);
      nptr->sign = v < 0 ? 1 : 0;
      nptr->length = 1;
      nptr->padding = 0;
      
      wptr[0] = BW_ABS_VALUE(v);
    } else {
      ptr = BW_PACK_VALUE(v);
    }
  }

  inline void clone(bigword const &src) {
    if(src.ptr & BW_LEFTMOST_BIT) {
      bw_header *s = BW_UNPACK_PTR(src.ptr);
      unsigned int length = s->length;
      unsigned int padding = s->padding;
      bw_header *p = aligned_alloc(length+padding+BW_SIZEOF_HEADER);
      memcpy(p,s,(padding+length+BW_SIZEOF_HEADER)*sizeof(unsigned int));
      ptr = BW_PACK_PTR(p);
    } else {
      ptr = src.ptr;
    }
  }

  inline bw_header *aligned_alloc(unsigned int c) {
    bw_header *p = (bw_header*) malloc(c * sizeof(unsigned int));  
    if(((unsigned int)p) & 1) { throw std::runtime_error("Allocated memory not aligned!"); }
    return p;
  }
};

#endif
