#include <stdexcept>
#include <cassert>
#include <algorithm>
#include "factor_poly.hpp"

using namespace std;

extern unsigned int resize_stats;

#define FPOLY_PADDING_FACTOR 1

// ---------------------------------------------------------------
// YTERMS CODE
// ---------------------------------------------------------------

yterms::yterms() : ptr(NULL) { }

yterms::yterms(unsigned int y_min, unsigned int y_max) {
  ptr = alloc(y_min,y_max);
}

yterms::yterms(yterms const &src) { clone(src); }
yterms::~yterms() {
  unalloc(ptr); 
}

yterms const &yterms::operator=(yterms const &src) {
  if(&src != this) {
    unalloc(ptr);
    clone(src);
  }
  return *this;
}

void yterms::swap(yterms &src) {
  if(&src != this) {
    header *tmp = ptr;
    ptr = src.ptr;
    src.ptr = tmp;
  }
}

bool yterms::is_empty() const { return ptr == NULL; }

unsigned int yterms::size() const {
  if(ptr == NULL) { return 0; }
  return (ptr->ymax - ptr->ymin)+1;
}

void yterms::resize(unsigned int y_min, unsigned int y_max) {
  if(is_empty()) {
    // special case when optr == NULL
    ptr = alloc(y_min,y_max);
  } else {
    int d_end = y_max - ptr->ymax;
    int d_beg = ptr->ymin - y_min;

    if(d_beg <= (int) ptr->front_padding && d_end <= (int) ptr->back_padding) {
      // in this case, there is enough padding to cover it
      if(d_end > 0) {
	ptr->ymax = y_max;      
	ptr->back_padding -= d_end;
      }
      if(d_beg > 0) {
	ptr->ymin = y_min;      
	ptr->front_padding -= d_beg;
      }
    } else {
      resize_stats++;
      // no, there definitely aren't enough y-terms
      unsigned int ystart = ptr->ymin;
      unsigned int yend = ptr->ymax;
      header *optr = ptr;
      ptr = alloc(min(ystart,y_min),max(yend,y_max));
      // copy old stuff over
      for(unsigned int i=ystart;i<=yend;++i) { set(i,get(i,optr),ptr); }
      // free space!
      unalloc(optr);
    }
  }
}

void yterms::operator*=(xy_term const &p) {
  // if this poly is empty do nothing!
  if(is_empty()) { return;}
  // Ok, it's not empty ...
  unsigned int ystart = ptr->ymin;
  unsigned int yend = ptr->ymax;
  unsigned int nystart = ystart + p.ypower;
  unsigned int nyend = yend + p.ypowerend;

  if(p.ypower == p.ypowerend) {
    // easy case, only a shift required
    ptr->ymin = nystart;
    ptr->ymax = nyend;
  } else {
    // harder case
    header *nptr = alloc(nystart,nyend);     // COULD MAKE USE OF PADDING!!!
    unsigned int depth = (p.ypowerend-p.ypower)+1;
    unsigned int width = (yend-ystart)+1;

    // going up the triangle
    unsigned int acc = 0;    
    for(unsigned int i=0;i<min(width,depth);++i) {
      acc += get(i+ystart,ptr);
      set(i+nystart,acc,nptr);
    }
    // free fall (if there is any)
    for(unsigned int i=width;i<depth;++i) {
      set(i+nystart,acc,nptr);      
    }    
    // going along the top (if there is one)
    unsigned int sub = 0;
    for(unsigned int i=depth;i<width;++i) {
      sub += get(i+ystart-depth,ptr);
      acc += get(i+ystart,ptr);
      set(i+nystart,acc - sub,nptr);
    }    
    // going down the triangle
    for(unsigned int i=max(depth,width);i < (nyend-nystart)+1;++i) {
      sub += get((i + ystart) - depth,ptr);
      set(i+nystart,acc - sub,nptr);    
    }
    unalloc(ptr);
    ptr = nptr;
  }
  // and we're done!
}

void yterms::operator+=(xy_term const &p) {
  // make sure enough y terms
  resize(p.ypower,p.ypowerend);
  // now, do the addition
  for(unsigned int i=p.ypower;i<=p.ypowerend;++i) { 
    add(i,1,ptr);
  }    
}

void yterms::insert(unsigned int n, xy_term const &p) { 
  // make sure enough y terms
  resize(p.ypower,p.ypowerend);
  // now, do the addition
  for(unsigned int i=p.ypower;i<=p.ypowerend;++i) { 
    add(i,n,ptr);
  }    
}

void yterms::operator+=(yterms const &src) {
  // make sure enough y terms
  resize(src.ptr->ymin,src.ptr->ymax);
  assert(ptr->ymin <= src.ptr->ymin && ptr->ymax >= src.ptr->ymax);
  // now, do the addition
  unsigned int start = src.ptr->ymin;
  unsigned int end = src.ptr->ymax;
  for(unsigned int i=start;i<=end;++i) { 
    add(i,get(i,src.ptr),ptr);
  }
}

unsigned int yterms::operator[](int i) const { return get(i,ptr); }

double yterms::substitute(double y) const {
  if(ptr != NULL) {
    double r = 0.0;
    for(unsigned int i=ptr->ymin;i<=ptr->ymax;++i) {
      r += pow(y,(double)i) * get(i,ptr);
    }
    return r;
  } else {
    return 0.0;
  }
}

string yterms::str() const {
  std::stringstream ss;
  if(ptr->ymin != ptr->ymax) {
    ss << "y^{" << ptr->ymin << ".." << ptr->ymax << "}";
  } else if(ptr->ymin == 1) {
    ss << "y";
  } else if(ptr->ymin != 0) {
    ss << "y^" << ptr->ymin;
  } else if(ptr->ymin == 0) {
    return "";
  }
  ss << "(";
  for(unsigned int i=ptr->ymin;i<=ptr->ymax;++i) {
    if(i != ptr->ymin) { ss << " + "; }
    ss << get(i,ptr);
  }
  ss << ")";
  return ss.str();
}

unsigned int yterms::nterms() const {
  if(ptr == NULL) { return 0; }
  return (ptr->ymax - ptr->ymin) + 1;
}

void yterms::clone(yterms const &src) { 
  if(src.is_empty()) { ptr = NULL; }
  else {
    unsigned int nints = (src.ptr->ymax-src.ptr->ymin)+1;
    nints += src.ptr->front_padding + src.ptr->back_padding;    
    ptr = (header*) malloc((nints*sizeof(unsigned int)) + sizeof(header));
    memcpy(ptr,src.ptr,(nints*sizeof(unsigned int)) + sizeof(header));  
  }
}

void yterms::set(unsigned int y, unsigned int v, header *h) {
  assert(y >= h->ymin && y<=h->ymax);
  unsigned int *p = (unsigned int *) (h+1);
  p[(y - h->ymin) + h->front_padding] = v;
}

void yterms::add(unsigned int y, unsigned int v, header *h) {
  assert(y >= h->ymin && y <= h->ymax);
  unsigned int *p = (unsigned int *) (h+1);
  p[(y - h->ymin) + h->front_padding] += v;
}

unsigned int yterms::get(unsigned int y, header *h) const {
  assert(y >= h->ymin && y <= h->ymax);
  unsigned int *p = (unsigned int *) (h+1);
  return p[(y - h->ymin) + h->front_padding];
}

yterms::header *yterms::alloc(unsigned int ymin, unsigned int ymax) {
  unsigned int nyterms = (ymax-ymin)+1;
  unsigned int back_padding = nyterms * FPOLY_PADDING_FACTOR;
  unsigned int front_padding = min(ymin,nyterms * FPOLY_PADDING_FACTOR);
  header *p = (header*) malloc(((front_padding+nyterms+back_padding)*sizeof(unsigned int)) + sizeof(header));
  // initialise all elements
  memset(p,0,((front_padding+nyterms+back_padding)*sizeof(unsigned int)) + sizeof(header)); // why is this needed?
  // initialise header
  p->back_padding = back_padding;
  p->front_padding = front_padding;
  p->ymin = ymin;
  p->ymax = ymax;
  return p;
}

void yterms::unalloc(header *ptr) {
  free(ptr);
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
  resize_xterms(p.nxterms); 
  for(unsigned int i=0;i<p.nxterms;++i) {
    if(!p.xterms[i].is_empty()) {
      xterms[i] += p.xterms[i];
    }
  }
}

void factor_poly::operator+=(xy_term const &p) {
  // make sure enough x terms
  resize_xterms(p.xpower+1); 
  // now, do the addition
  xterms[p.xpower] += p;
}

void factor_poly::insert(unsigned int n, xy_term const &p) {
  // make sure enough x terms
  resize_xterms(p.xpower+1); 
  // now, do the addition
  xterms[p.xpower].insert(n,p);
}

void factor_poly::operator*=(xy_term const &p) {
  if(p.xpower > 0) { 
    // need to shift the x's
    resize_xterms(p.xpower + nxterms + 1); 
    for(unsigned int i=nxterms;i>p.xpower;--i) {
      xterms[i-1].swap(xterms[i-(p.xpower+1)]);
    }
  }
  for(unsigned int i=0;i<nxterms;++i) { xterms[i] *= p; }
}

unsigned int factor_poly::nterms() const {
  unsigned int r=0;
  for(unsigned int i=0;i<nxterms;++i) {
    r += xterms[i].nterms();
  }
  return r;
}

string factor_poly::str() const {
  string r="";
  bool first_time=true;
  for(unsigned int i=0;i<nxterms;++i) {    
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
  double r = 0.0;
  for(unsigned int i=0;i<nxterms;++i) {
    r += pow(x,(double)i) * xterms[i].substitute(y);
  }
  return r;
}

void factor_poly::destroy() {
  delete [] xterms; // will invoke yterms destructors 
}

void factor_poly::clone(factor_poly const &p) {
  nxterms = p.nxterms;
  xterms = new yterms[nxterms];
  for(unsigned int i=0;i<nxterms;++i) {
    xterms[i] = p.xterms[i];
  }
}

void factor_poly::resize_xterms(unsigned int ns) {
  if(ns < nxterms) { return; }  
  yterms *xs = new yterms[ns];
  // need to use swap here, because
  // I don't want the following delete []
  // call to call destructors on my yterms
  for(unsigned int i=0;i<nxterms;++i) {
    xs[i].swap(xterms[i]);
  }
  delete [] xterms;
  xterms = xs;
  nxterms = ns;  
}
