#include "bigint.hpp"

// Expand the length of the digit array to be at least length.  If
// the array was already longer than length then it is not modified.
// New digits are filled in with zero.
void bigint::expand(unsigned int nlength) {    
  // ARRAY MODE
  bw_header *p(BI_UNPACK_PTR(ptr));
  bool sign(p->sign);
  unsigned int length = p->length;
  unsigned int padding = p->padding;
  if(length >= nlength) { return; }
  else if((length+padding) >= nlength) {
    // no need to expand as we have space in the padding
    p->length = nlength;
    p->padding = (length+padding)-nlength;
  } else {
    bw_header *nptr = aligned_alloc((nlength*2)+BI_SIZEOF_HEADER);
    nptr->sign = sign;
    nptr->length = nlength;
    nptr->padding = nlength;
    
    memset(((unsigned int*)nptr)+length+BI_SIZEOF_HEADER,0,((nlength*2)-length)*sizeof(unsigned int));
    memcpy(nptr+2,p+2,length*sizeof(unsigned int));
    free(p);
    ptr = BI_PACK_PTR(nptr);
  }
}
