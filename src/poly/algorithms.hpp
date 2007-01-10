#ifndef POLY_ALGORITHMS_HPP
#define POLY_ALGORITHMS_HPP

// -----------------------------------------------------
// ---- METHODS FOR EFFICIENTLY STORING POLYNOMIALS ----
// -----------------------------------------------------
//
// The aim of the game here is to save space.

template<class T>
size_t sizeof_compact_poly(T const &poly) {
  return ((poly.size() * 3) + 1) * sizeof(unsigned int);
}

size_t sizeof_compact_poly(unsigned char *poly) {
  unsigned int *p = (unsigned int *) poly;
  unsigned int size = *p;
  
  return ((size * 3) + 1) * sizeof(unsigned int);
}

template<class T>
void write_compact_poly(unsigned char *dst, T const &poly) {
  unsigned int *p = (unsigned int *) dst;
  *p++ = poly.size();
  typename T::const_iterator iend(poly.end());
  for(typename T::const_iterator i(poly.begin());i!=iend;++i) {
    *p++ = i->second;
    *p++ = i->first.xpower;
    *p++ = i->first.ypower;
  }
}

template<class T>
T read_compact_poly(unsigned char *src) {
  unsigned int *p = (unsigned int *) src;
  unsigned int size = *p++;

  T r;

  for(int i=0;i!=size;++i) {
    unsigned int nterms = *p++;
    unsigned int xpower = *p++;
    unsigned int ypower = *p++;
    r.insert(nterms,term(xpower,ypower));
  }

  return r;
}

#endif

