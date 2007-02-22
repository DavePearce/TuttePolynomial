#include <stdexcept>
#include "factor_poly.hpp"

using namespace std;

// ---------------------------------------------------------------
// YTERMS CODE
// ---------------------------------------------------------------

yterms::yterms() : ptr(NULL) { }

yterms::yterms(unsigned int y_min, unsigned int y_max) {
  unsigned int nyterms = (y_max - y_min) + 1;
  ptr = new unsigned int[nyterms+1];
  unsigned int tmp = (y_max << 16U) + y_min;
  *ptr = tmp;  
  // clear terms
  for(unsigned int i=1;i<(nyterms-1);++i) { 
    ptr[i] = 0; 
  }
}

yterms::yterms(yterms const &src) { clone(src); }
yterms::~yterms() { delete [] ptr; }

yterms const &yterms::operator=(yterms const &src) {
  if(&src != this) {
    delete [] ptr;
    clone(src);
  }
  return *this;
}

bool yterms::is_empty() const { return ptr == NULL; }

unsigned int yterms::size() const {  
  unsigned int ystart = (*ptr) & 0xFFFF;
  unsigned int yend = (*ptr) >> 16U;
  return (yend - ystart)+1;
}

unsigned int yterms::ymax() const {  
 return (*ptr) >> 16U;
}

unsigned int yterms::ymin() const {  
 return (*ptr) & 0xFFFF;
}

void yterms::resize(unsigned int y_min, unsigned int y_max) {
  if(is_empty()) {
    // special case when optr == NULL
    unsigned int nyterms = (y_max - y_min) + 1;
    // create the yterm array
    ptr = new unsigned int[nyterms+1];    
    // set header information
    unsigned int tmp = (y_max << 16U) + y_min;
    *ptr = tmp;
    for(unsigned int i=1;i<=nyterms;++i) { ptr[i] = 0; }    
  } else if(ymax() < y_max) {
    // no, there definitely aren't enough y-terms
    unsigned int ystart = ymin();
    unsigned int yend = ymax();
    unsigned int nystart = min(ystart,y_min); 
    unsigned int nyend = max(yend,y_max);
    unsigned int nyterms = (nyend - nystart)+1;    
    unsigned int *optr = ptr;
    ptr = new unsigned int[nyterms+1];    
    // set header information
    unsigned int tmp = (nyend << 16U) + nystart;
    *ptr = tmp;
    // copy old stuff, whilst initialising new stuff 
    for(unsigned int i=1;i<=(ystart-nystart);++i) { ptr[i] = 0; }
    for(unsigned int i=(ystart-nystart+1);i<=(yend-nystart);++i) { ptr[i] = optr[i-(ystart-nystart)]; }
    for(unsigned int i=yend-nystart+1;i<=(nyend-nystart);++i) { ptr[i] = 0; }
    // free space!
    delete [] optr;
  }
}

void yterms::operator*=(xy_term const &p) {
  // complicated
}

void yterms::operator+=(xy_term const &p) {
  // make sure enough y terms
  resize(p.ypower,p.ypowerend);
  // now, do the addition
  for(unsigned int i=p.ypower+1;i<=p.ypowerend+1;++i) { ptr[i]++; }    
}

unsigned int yterms::operator[](int i) const {
  return ptr[i+1];
}

string yterms::str() const {
  std::stringstream ss;
  ss << "y^{" << ymin() << "-" << ymax() << "}(";
  for(unsigned int i=0;i!=size();++i) {
    if(i != 0) { ss << " + "; }
    ss << (*this)[i];
  }
  ss << ")";
  return ss.str();
}

void yterms::clone(yterms const &src) { 
  unsigned int nyterms = src.size();
  ptr = new unsigned int[nyterms+1];
  memcpy(ptr,src.ptr,(nyterms+1) * sizeof(unsigned int));  
}

// ---------------------------------------------------------------
// FACTOR POLY CODE
// ---------------------------------------------------------------

factor_poly::factor_poly(xy_term const &xyt) {
  nxterms = xyt.xpower;
  // create the xterm array
  xterms = new yterms[nxterms];  
  *this += xyt;
}

factor_poly::factor_poly(factor_poly const &fp) { clone(fp); }
factor_poly::~factor_poly() { destroy(); }

factor_poly const &factor_poly::operator=(factor_poly const &src) {
  if(&src != this) {
    destroy();
    clone(src);
  }
  return *this;
}

void factor_poly::operator+=(factor_poly const &p) {
  // to do
}

void factor_poly::operator+=(xy_term const &p) {
  // make sure enough x terms
  if(p.xpower >= nxterms) { resize_xterms(p.xpower); }
  // now, do the addition
  xterms[p.xpower] += p;
}

void factor_poly::operator*=(xy_term const &p) {
  if(p.xpower != 0) { throw std::runtime_error("factor_poly cannot currently handle multiplication by x^n"); }
  for(unsigned int i=0;i!=nxterms;++i) { xterms[i] *= p; }
}

string factor_poly::str() const {
  return "FACTOR_POLY::STR INCOMPLETE!";
}

double factor_poly::substitute(double x, double y) const {
  return 0.0;
}

void factor_poly::destroy() {
  delete [] xterms; // should invoke yterms destructors 
}

void factor_poly::clone(factor_poly const &p) {
  nxterms = p.nxterms;
  xterms = new yterms[nxterms];
  for(unsigned int i=0;i!=nxterms;++i) {
    xterms[i] = p.xterms[i];
  }
}

void factor_poly::resize_xterms(unsigned int ns) {
  // PRE: ns > nxterms
  yterms *xs = new yterms[ns];
  memcpy(xs,xterms,nxterms*sizeof(yterms*)); 
  delete [] xterms;
  xterms = xs;
}
