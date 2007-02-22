#include "factor_poly.hpp"

using namespace std;

yterms::yterms() : ptr(NULL) { }

yterms::yterms(unsigned int y_min, unsigned int y_max) {
  unsigned int nyterms = (y_max - y_min) + 1;
  ptr = new unsigned int[nyterms+1];
  unsigned int tmp = (y_max << 8) + y_min;
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
    destroy();
    clone(src);
  }
  return *this;
}

unsigned int yterms::size() const {  
  unsigned int ystart = (*ptr) & 0xFFFF;
  unsigned int yend = (*ptr) >> 8;
  return (yend - ystart)+1;
}

void yterms::resize(unsigned int y_min, unsigned int y_max) {
  if(is_empty()) {
    // special case when optr == NULL
    unsigned int nyterms = (y_max - y_min) + 1;
    // create the yterm array
    ptr = new unsigned int[nyterms+1];    
    // set header information
    unsigned int tmp = (nyend << 8) + nystart;
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
    unsigned int tmp = (nyend << 8) + nystart;
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
  for(unsigned int i=p.ypower+1;i<=p.ypowerend;++i) { ptr[i]++; }    
}

void yterms::clone(yterm const &src) { 
  unsigned int nyterms = src.size();
  unsigned int *r = new unsigned int[nyterms+1];
  memcpy(r,ts,(nyterms+1) * sizeof(unsigned int));
  return r;
}

factor_poly::factor_poly(xy_term const &xyt) {
  nxterms = xyt.xpower;
  // create the xterm array
  xterms = new unsigned int*[nxterms];
  for(unsigned int i=0;i!=nxterms;++i) {
    xterms[i] = NULL;
  }    
  
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
