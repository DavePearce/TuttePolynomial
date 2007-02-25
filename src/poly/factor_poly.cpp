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
yterms::~yterms() {
  delete [] ptr; 
}

yterms const &yterms::operator=(yterms const &src) {
  if(&src != this) {
    delete [] ptr;
    clone(src);
  }
  return *this;
}

void yterms::swap(yterms &src) {
  if(&src != this) {
    unsigned int *tmp = ptr;
    ptr = src.ptr;
    src.ptr = tmp;
  }
}

bool yterms::is_empty() const { return ptr == NULL; }

unsigned int yterms::size() const {
  if(ptr == NULL) { return 0; }
  unsigned int ystart = (*ptr) & 0xFFFF;
  unsigned int yend = (*ptr) >> 16U;
  return (yend - ystart)+1;
}

unsigned int yterms::ymax() const {  
  if(ptr == NULL) { return 0; }
  else return (*ptr) >> 16U;
}

unsigned int yterms::ymin() const {  
  if(ptr == NULL) { return 0; }
  else return (*ptr) & 0xFFFF;
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
  } else if(ymax() < y_max || ymin() > y_min) {
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
    for(unsigned int i=(ystart-nystart)+1;i<=(yend-nystart)+1;++i) { ptr[i] = optr[i-(ystart-nystart)]; }
    for(unsigned int i=(yend-nystart)+2;i<=(nyend-nystart)+1;++i) { ptr[i] = 0; }
    // free space!
    delete [] optr;
  }
}

void yterms::operator*=(xy_term const &p) {
  // if this poly is empty do nothing!
  if(is_empty()) { ;return;}
  // Ok, it's not empty ...
  unsigned int ystart = ymin();
  unsigned int yend = ymax();
  unsigned int nystart = ystart + p.ypower;
  unsigned int nyend = yend + p.ypowerend;

  if(p.ypower == p.ypowerend) {
    // easy case, only a shift required
    unsigned int tmp = (nyend << 16U) + nystart;
    *ptr = tmp;    
  } else {
    // harder case
    unsigned int nyterms = (nyend - nystart)+1;
    unsigned int *nptr = new unsigned int[nyterms+1];
    unsigned int tmp = (nyend << 16U) + nystart;
    *nptr = tmp;    
    
    // I'm pretty sure it's possible to make a linear
    // verison of this loop
    memset(nptr+1,0,sizeof(unsigned int)*nyterms);  // why is this needed ?
    for(unsigned int j=0;j<=p.ypowerend-p.ypower;++j) {
      for(unsigned int i=1;i<=yend;++i) {
	nptr[i+j] += ptr[i];
      }
    }
    delete [] ptr;
    ptr = nptr;
  }
  // and we're done!
}

void yterms::operator+=(xy_term const &p) {
  // make sure enough y terms
  resize(p.ypower,p.ypowerend);
  // now, do the addition
  unsigned int ystart = p.ypower - ymin();
  unsigned int yend = p.ypowerend - ymin();
  for(unsigned int i=ystart+1;i<=yend+1;++i) { ptr[i]++; }    
}

void yterms::insert(unsigned int n, xy_term const &p) { 
  // make sure enough y terms
  resize(p.ypower,p.ypowerend);
  // now, do the addition
  unsigned int ystart = p.ypower - ymin();
  unsigned int yend = p.ypowerend - ymin();
  for(unsigned int i=ystart+1;i<=yend+1;++i) { ptr[i] += n; }      
}

void yterms::operator+=(yterms const &src) {
  if(src.is_empty()) { return; }
  // make sure enough y terms
  resize(src.ymin(),src.ymax());
  // now, do the addition
  unsigned int ystart = src.ymin() - ymin();
  unsigned int yend = src.ymax() - ymin();
  unsigned int j=1;
  for(unsigned int i=ystart+1;i<=yend+1;++i,++j) { 
    ptr[i] += src.ptr[j]; 
  }    
}

unsigned int yterms::operator[](int i) const {
  return ptr[i+1];
}

string yterms::str() const {
  std::stringstream ss;
  if(ymin() != ymax()) {
    ss << "y^{" << ymin() << "-" << ymax() << "}";
  } else if(ymin() == 1) {
    ss << "y";
  } else if(ymin() != 0) {
    ss << "y^" << ymin();
  } else if(ymin() == 0) {
    return "";
  }
  ss << "(";
  for(unsigned int i=0;i!=size();++i) {
    if(i != 0) { ss << " + "; }
    ss << (*this)[i];
  }
  ss << ")";
  return ss.str();
}

unsigned int yterms::nterms() const {
  if(ptr == NULL) { return 0; }
  return (ymax() - ymin()) + 1;
}

void yterms::clone(yterms const &src) { 
  if(src.is_empty()) { 
    ptr = NULL; 
    return;
  } else {
    unsigned int nyterms = src.size();
    ptr = new unsigned int[nyterms+1];
    memcpy(ptr,src.ptr,(nyterms+1) * sizeof(unsigned int));  
  }
}

// ---------------------------------------------------------------
// FACTOR POLY CODE
// ---------------------------------------------------------------

factor_poly::factor_poly() {
  nxterms = 5; // arbitrary ?
  // create the xterm array
  xterms = new yterms[nxterms];  
}

factor_poly::factor_poly(xy_term const &xyt) {
  nxterms = xyt.xpower+1;
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
  // make sure enough x terms
  if(p.nxterms > nxterms) { resize_xterms(p.nxterms); }
  for(unsigned int i=0;i!=p.nxterms;++i) {
    if(!p.xterms[i].is_empty()) {
      xterms[i] += p.xterms[i];
    }
  }
}

void factor_poly::operator+=(xy_term const &p) {
  // make sure enough x terms
  if(p.xpower >= nxterms) { resize_xterms(p.xpower); }
  // now, do the addition
  xterms[p.xpower] += p;
}

void factor_poly::insert(unsigned int n, xy_term const &p) {
  // make sure enough x terms
  if(p.xpower >= nxterms) { resize_xterms(p.xpower); }
  // now, do the addition
  xterms[p.xpower].insert(n,p);
}

void factor_poly::operator*=(xy_term const &p) {
  if(p.xpower > 0) { 
    // need to shift the x's
    resize_xterms(p.xpower + nxterms); 
    for(unsigned int i=nxterms;i>p.xpower;--i) {
      xterms[i-1].swap(xterms[i-(p.xpower+1)]);
    }
  }
  for(unsigned int i=0;i!=nxterms;++i) { xterms[i] *= p; }
}

unsigned int factor_poly::nterms() const {
  unsigned int r=0;
  for(unsigned int i=0;i!=nxterms;++i) {
    r += xterms[i].nterms();
  }
  return r;
}

string factor_poly::str() const {
  string r="";
  bool first_time=true;
  for(unsigned int i=0;i!=nxterms;++i) {    
    if(!xterms[i].is_empty()) {
      if(!first_time) { r += " + "; }
      first_time=false;    
      if(i > 0) {
	std::stringstream ss;
	ss << i;
	r += "x^" + ss.str();
      }
      r += xterms[i].str();
    }
  }
  return r;
}

double factor_poly::substitute(double x, double y) const {
  return 0.0;
}

void factor_poly::destroy() {
  delete [] xterms; // will invoke yterms destructors 
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
  // need to use swap here, because
  // I don't want the following delete []
  // call to call destructors on my yterms
  for(unsigned int i=0;i!=nxterms;++i) {
    xs[i].swap(xterms[i]);
  }
  delete [] xterms;
  xterms = xs;
  nxterms = ns;  
}
