#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <stdexcept>
#include "../../config.h"

#define BI_WORD_SIZE (SIZEOF_INT*8U)
#define BI_LEFTMOST_BIT (1U << (BI_WORD_SIZE-1))

// The largest value a WORD_SIZE-1 signed integer can hold
#define BI_SWORD_MAX ((int) (((unsigned int) -1) >> 2U))
// The smallest value a WORD_SIZE-1 signed integer can hold
#define BI_SWORD_MIN ((int) ((((unsigned int) -1) >> 2U) | BI_LEFTMOST_BIT)+1)

typedef struct {
  unsigned sign:1;
  unsigned length:(BI_WORD_SIZE-1);
  unsigned padding;
} bw_header;

// PACK POINTER INTO WORD FORMAT (WITH LEFTMOST BIT = 1)
#define BI_PACK_PTR(x) ((((unsigned int)x) >> 1U) | BI_LEFTMOST_BIT)

// UNPACK POINTER FROM WORD FORMAT (WITH LEFTMOST BIT = 1)
#define BI_UNPACK_PTR(x) ((bw_header*)(x << 1U))

// SIZE OF BI_HEADER STRUCT IN WORDS (NOT BYTES)
#define BI_SIZEOF_HEADER 2U

// PACK INTEGER INTO WORD FORMAT
#define BI_PACK_VALUE(x) (x&~BI_LEFTMOST_BIT)

// UNPACK INTEGER FROM WORD FORMAT (WITH LEFTMOST BIT = 0)
#define BI_UNPACK_VALUE(x) (((int)(x << 1U)) >> 1)

// GET MAGNITUDE OF VALUE
#define BI_ABS_VALUE(x) ((x == INT_MIN) ? ((unsigned int)INT_MAX)+1: abs(x))

class bigint {
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
  // Construct a bigint repesenting zero.  This will store the
  // integer in WORD MODE.
  bigint() { bigint(0); }

  // Construct a bigint repesenting the integer value.  If possible
  // it will store the integer in WORD MODE; otherwise, (if the
  // integer is too big) it will use ARRAY MODE.
  bigint(int value) {
    clone(value);
  }
  
  // Construct a clone of the bigint.  This will employ the same
  // representation of the integer.
  bigint(bigint const &value) {
    clone(value);
  }

  inline ~biguint() { if(ptr & BI_LEFTMOST_BIT) { free(BI_UNPACK_PTR(ptr)); } }

  inline bigint const &operator=(int v) {
    if(ptr & BI_LEFTMOST_BIT) { free(BI_UNPACK_PTR(ptr)); }
    clone(v);
    return *this;
  }
  
  inline bigint const &operator=(bigint const &src) {    
    if(this != &src) {
      if(src.ptr & BI_LEFTMOST_BIT) {
	if(ptr & BI_LEFTMOST_BIT) {
	  bw_header *s = BI_UNPACK_PTR(src.ptr);
	  bw_header *p = BI_UNPACK_PTR(ptr);
	  // attempt to reuse memory where possible.
	  unsigned int src_length = s->length;
	  unsigned int length = p->length;
	  unsigned int padding = p->padding;	
	  
	  if(src_length <= (length + padding)) {
	    memcpy(p,s,(src_length + BI_SIZEOF_HEADER)*sizeof(unsigned int));
	    memset(((unsigned int*)p) + src_length + sizeof(bw_header),0,((length+padding)-src_length)*sizeof(unsigned int));
	  } else {
	    free(BI_UNPACK_PTR(ptr));
	    clone(src);
	  }
	} else {
	  clone(src);
	}	
      } else {
	if(ptr & BI_LEFTMOST_BIT) { free(BI_UNPACK_PTR(ptr)); };
	ptr = src.ptr;
      }
    }
    return *this;
  }
  
  inline void swap(bigint &src) {
    std::swap(ptr,src.ptr);
  }


  /* =============================== */
  /* ======== COMPARISON OPS ======= */
  /* =============================== */

  bool operator==(int v) const;
  bool operator==(biguint const &v) const;

  bool operator!=(int v) const;
  bool operator!=(biguint const &v) const;

  /* =============================== */
  /* ======== ARITHMETIC OPS ======= */
  /* =============================== */

  void operator+=(int w);
  void operator+=(biguint const &src);
  void operator-=(int w);
  void operator-=(biguint const &src);

  void operator*=(int v);
  void operator*=(biguint const &v);
  void operator/=(int v);
  void operator%=(int v);
  void operator^=(int v);   

  biguint operator+(int w) const;
  biguint operator+(biguint const &w) const;
  biguint operator-(int w) const;
  biguint operator-(biguint const &w) const;

  biguint operator*(int w) const;
  biguint operator*(biguint const &w) const;
  biguint operator/(int w) const;
  int operator%(int w) const;
  biguint operator^(int v) const;

  /* =============================== */
  /* ======== CONVERSION OPS ======= */
  /* =============================== */

  int c_int() const;
  long c_long() const;
  long long c_longlong() const;

  /* =============================== */
  /* ======== HELPER METHODS ======= */
  /* =============================== */

private:
  
  inline void clone(int v) {
    if((v < BI_SWORD_MIN) || (v > BI_SWORD_MAX)) {
      // In this case, the integer is too large to fit into WORD MODE.
      // Therefore, we must use ARRAY MODE with a single digit.
      bw_header *nptr = aligned_alloc(1+BI_SIZEOF_HEADER);
      unsigned int *wptr = ((unsigned int*)nptr)+BI_SIZEOF_HEADER;

      ptr = BI_PACK_PTR(nptr);
      nptr->sign = v < 0 ? 1 : 0;
      nptr->length = 1;
      nptr->padding = 0;
      
      wptr[0] = BI_ABS_VALUE(v);
    } else {
      ptr = BI_PACK_VALUE(v);
    }
  }

  inline void clone(bigint const &src) {
    if(src.ptr & BI_LEFTMOST_BIT) {
      bw_header *s = BI_UNPACK_PTR(src.ptr);
      unsigned int length = s->length;
      unsigned int padding = s->padding;
      bw_header *p = aligned_alloc(length+padding+BI_SIZEOF_HEADER);
      memcpy(p,s,(padding+length+BI_SIZEOF_HEADER)*sizeof(unsigned int));
      ptr = BI_PACK_PTR(p);
    } else {
      ptr = src.ptr;
    }
  }

  void internal_add(bw_header *p, bw_header x);
  void internal_add(bw_header *p, bw_header *s);
  void internal_sub(bw_header *p, bw_header x);
  void internal_sub(bw_header *p, bw_header *s);
  int internal_cmp(bw_header *p, bw_header *s);

  void expand(unsigned int ndepth);
  bw_header *aligned_alloc(unsigned int c);

  void ripple_carry(unsigned int level);
  void ripple_borrow(unsigned int level);

  inline bw_header *aligned_alloc(unsigned int c) {
    bw_header *p = (bw_header*) malloc(c * sizeof(unsigned int));  
    if(((unsigned int)p) & 1) { throw std::runtime_error("Allocated memory not aligned!"); }
    return p;
  }
};

/* ===================================== */
/* ======== OTHER USEFUL METHODS ======= */
/* ===================================== */

std::ostream& operator<<(std::ostream &out, biguint val);
bstreambuf &operator<<(bstreambuf &, biguint const &);
bistream &operator>>(bistream &, biguint &);
biguint pow(biguint const &r, unsigned int power);

#endif
