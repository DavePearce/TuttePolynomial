// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#ifndef FACTOR_POLY_HPP
#define FACTOR_POLY_HPP

#include <iostream>
#include <string>
#include <utility>
#include "xy_term.hpp"
#include "../misc/biguint.hpp"
#include "../misc/bistream.hpp"
#include "../misc/bstreambuf.hpp"

#define FPOLY_PADDING_FACTOR 1

template<class T>
class yterms {
public:  
  unsigned int ymin;
  unsigned int ymax;

  template<class S> 
  friend bstreambuf &operator<<(bstreambuf &, yterms<S> const &);
  template<class S> 
  friend bistream &operator>>(bistream &, yterms<S> &);
private:  
  unsigned int fpadding;
  unsigned int bpadding;
  T *coefficients;
public:
  /* =============================== */
  /* ========= CONSTRUCTORS ======== */
  /* =============================== */

  yterms() : ymin(1), ymax(0), fpadding(0), bpadding(0), coefficients(NULL) {}

  yterms(unsigned int y_min, unsigned int y_max) {    
    alloc(y_min,y_max);
  }

  yterms(yterms<T> const &src)  { clone(src); }

  ~yterms() { delete [] coefficients; }

  /* =============================== */
  /* ======== ASSIGNMENT OP ======== */
  /* =============================== */

  yterms const &operator=(yterms<T> const &src) {
    if(&src != this) {
      delete [] coefficients;
      clone(src);
    }
    return *this;
  }

  void swap(yterms<T> &src) {
    if(&src != this) {
      std::swap(ymin,src.ymin);
      std::swap(ymax,src.ymax);
      std::swap(fpadding,src.fpadding);
      std::swap(bpadding,src.bpadding);
      std::swap(coefficients,src.coefficients);
    }
  }

  /* =============================== */
  /* ======== ARITHMETIC OPS ======= */
  /* =============================== */

  void operator+=(xy_term const &p) {
    // make sure enough y terms
    resize(p.ypower,p.ypowerend);
    // now, do the addition
    for(unsigned int i=p.ypower;i<=p.ypowerend;++i) { 
      (*this)[i] += 1;
    }    
  }

  void operator+=(yterms<T> const &src) {
    // make sure enough y terms
    resize(src.ymin,src.ymax);
    // now, do the addition
    unsigned int start = src.ymin;
    unsigned int end = src.ymax;
    for(unsigned int i=start;i<=end;++i) { 
      T c(src[i]);
      (*this)[i] += c;
    }
  }

  void operator*=(xy_term const &p) {
    // if this poly is empty do nothing!
    if(is_empty()) { return;}
    // Ok, it's not empty ...
    unsigned int ystart = ymin;
    unsigned int yend = ymax;
    unsigned int ypadding = fpadding;
    unsigned int nystart = ymin + p.ypower;
    unsigned int nyend = ymax + p.ypowerend;
    
    if(p.ypower == p.ypowerend) {
      // easy case, only a shift required
      ymin = nystart;
      ymax = nyend;
    } else {
      // harder case
      
      // The following could use padding, since it currently doesn't!
      T *o_coefficients = coefficients;
      alloc(nystart,nyend);     
      unsigned int depth = (p.ypowerend-p.ypower)+1;
      unsigned int width = (yend-ystart)+1;
      
      // going up the triangle
      T acc = 0U;    
      for(unsigned int i=0;i<std::min(width,depth);++i) {
	acc += o_coefficients[i+ypadding];
	coefficients[i+nystart+fpadding-ymin] = acc;
      }
      // free fall (if there is any)
      for(unsigned int i=width;i<depth;++i) {
	coefficients[i+nystart+fpadding-ymin] = acc;
      }    
      // going along the top (if there is one)
      T sub = 0U;
      for(unsigned int i=depth;i<width;++i) {
	sub += o_coefficients[i+ypadding-depth];
	acc += o_coefficients[i+ypadding];
	coefficients[i+fpadding] = acc - sub;
      }    

      // going down the triangle
      for(unsigned int i=std::max(depth,width);i < (nyend-nystart)+1;++i) {
	sub += o_coefficients[i+ypadding - depth];
	coefficients[i+fpadding] = acc - sub;
      }
      delete [] o_coefficients;
    }
    // and we're done!
  }

  /* The more complicated general case.
   * Big question as to whether this code can 
   * be optimised any more.
   */
  void operator*=(yterms<T> const &p) {
    // if this poly is empty do nothing
    if(is_empty()) { return; }

    if(p.size() == 1) {
      // optimise simple case!
      ymin += p.ymin;
      ymax += p.ymax;
      T const &v(p[p.ymin]);

      for(unsigned int i=ymin;i<=ymax;++i) {
	(*this)[i] *= v;
      }
    } else {    
      yterms<T> r(p.ymin + ymin,p.ymax + ymax);
      
      for(unsigned int i=p.ymin;i<=p.ymax;++i) {
	yterms<T> tmp(*this);
	tmp.ymin += i;
	tmp.ymax += i;
	T const &v(p[i]);

	for(unsigned int j=tmp.ymin;j<=tmp.ymax;++j) {
	  tmp[j] *= v;
	}
	r += tmp;
      }
      
      swap(r); // normal swap trick optimisation
    }
  }
  
  /* ========================== */
  /* ======== OTHER FNS ======= */
  /* ========================== */  

  unsigned int size() const {
    if(coefficients == NULL) { return 0; }
    return (ymax - ymin) + 1;
  }

  bool is_empty() const { return coefficients == NULL; }

  T const &operator[](int i) const { return coefficients[(i + fpadding) - ymin]; }
  T &operator[](int i) { return coefficients[(i + fpadding) - ymin]; }

  biguint substitute(unsigned int y) const {
    if(coefficients != NULL) {
      biguint r(0U);
      biguint p(y);	
      for(unsigned int i=ymin;i<=ymax;++i) {	
	r += pow(p,i) * (*this)[i];
      }
      return r;
    } else {
      return biguint(0U);
    }
  }

  std::string str() const {
    std::stringstream ss;
    if(coefficients == NULL) { 
      return "";
    } else if(ymin != ymax) {
      ss << "y^{" << ymin << ".." << ymax << "}";
    } else if(ymin == 1) {
      ss << "y";
    } else if(ymin != 0) {
      ss << "y^" << ymin;
    } 
    ss << "(";
    for(unsigned int i=ymin;i<=ymax;++i) {
      if(i != ymin) { ss << " + "; }
      ss << (*this)[i];
    }
    ss << ")";
    return ss.str();
  }

  void insert(unsigned int n, xy_term const &p) {   // needs a better name? 
    // make sure enough y terms
    resize(p.ypower,p.ypowerend);
    // now, do the addition
    for(unsigned int i=p.ypower;i<=p.ypowerend;++i) { 
      (*this)[i] += n;
    }    
  }
  
private:  
  /* =============================== */
  /* ======== HELPERS ======= */
  /* =============================== */

  void resize(unsigned int n_ymin, unsigned int n_ymax)  {
    if(is_empty()) {
      alloc(n_ymin,n_ymax);
    } else {
      int d_end = n_ymax - ymax;
      int d_beg = ymin - n_ymin;
      
      if(d_beg <= (int) fpadding && d_end <= (int) bpadding) {
	// in this case, there is enough padding to cover it
	if(d_end > 0) {
	  ymax = n_ymax;      
	  bpadding -= d_end;
	}
	if(d_beg > 0) {
	  ymin = n_ymin;      
	  fpadding -= d_beg;
	}
      } else {
	// no, there definitely aren't enough y-terms
	unsigned int o_ymin = ymin;
	unsigned int o_ymax = ymax;
	unsigned int o_fpadding = fpadding;
	T *o_coefficients = coefficients;	
	alloc(std::min(o_ymin,n_ymin),std::max(o_ymax,n_ymax));
	// copy old stuff over
	for(unsigned int i=o_ymin;i<=o_ymax;++i) { 
	  (*this)[i] = o_coefficients[(i+o_fpadding)-o_ymin];
	}
	// free space!
	delete [] o_coefficients;
      }
    }
  }  

  void clone(yterms<T> const &src) { 
    if(src.is_empty()) { 
      coefficients = NULL; ymin = 1; ymax=0; fpadding = 0; bpadding = 0;}
    else {
      ymin = src.ymin;
      ymax = src.ymax;
      fpadding = src.fpadding;
      bpadding = src.bpadding;

      unsigned int ncoeffs = src.size() + src.fpadding + src.bpadding;
      
      coefficients = new T[ncoeffs];

      // copy old stuff over
      for(unsigned int i=0;i<ncoeffs;++i) { 
	coefficients[i] = src.coefficients[i];
      }
    }
  }

  void alloc(unsigned int _ymin, unsigned int _ymax) {
    unsigned int nyterms = (_ymax-_ymin)+1;    
    bpadding = nyterms * FPOLY_PADDING_FACTOR;
    fpadding = std::min(_ymin,nyterms * FPOLY_PADDING_FACTOR);
    ymin = _ymin;
    ymax = _ymax;
    coefficients = new T[nyterms + bpadding + fpadding];
    // why the following line is needed is just plain
    // wierd.
    for(unsigned int i=0;i<nyterms+fpadding+bpadding;++i) {
      coefficients[i] = 0U;
    }
  }
};

template<class T> 
bstreambuf &operator<<(bstreambuf &bout, yterms<T> const &yt) {
  bout << yt.ymin << yt.ymax;

  for(unsigned int i=yt.ymin;i<=yt.ymax;++i) { bout << yt[i]; }
}

template<class T> 
bistream &operator>>(bistream &bin, yterms<T> &yt) {
  unsigned int ymin, ymax;
  bin >> ymin >> ymax;
  if(ymin > ymax) { 
    yt = yterms<T>(); 
  } else {
    yterms<T> tmp(ymin,ymax);
    for(unsigned int i=tmp.ymin;i<=tmp.ymax;++i) {
      bin >> tmp[i];
    }
    // again, the following trick saves on 
    // assignment
    yt.swap(tmp);
  }
}

template<class T>
class factor_poly {
private:
  yterms<T> *xterms; 
  unsigned int nxterms;
  
  template<class S> 
  friend bstreambuf &operator<<(bstreambuf &,factor_poly<S> const &);
  template<class S> 
  friend bistream &operator>>(bistream &,factor_poly<S> &);
public:
  /* =============================== */
  /* ========= CONSTRUCTORS ======== */
  /* =============================== */

  factor_poly() {
    nxterms = 5; // arbitrary ?
    // create the xterm array
    xterms = new yterms<T>[nxterms];  
  }

  factor_poly(xy_term const &xyt) {
    nxterms = xyt.xpower+1;
    // create the xterm array
    xterms = new yterms<T>[nxterms];  
    *this += xyt;
  }

  factor_poly(factor_poly<T> const &fp) { clone(fp); }

  factor_poly(unsigned int nx, yterms<T> *xts) {
    nxterms = nx;
    xterms = xts;
  }

  ~factor_poly() { destroy(); }

  /* =============================== */
  /* ======== ASSIGNMENT OP ======== */
  /* =============================== */

  factor_poly const &operator=(factor_poly const &src) {
    if(&src != this) {
      destroy();
      clone(src);
    }
    return *this;  
  }

  void swap(factor_poly<T> &src) {
    std::swap(nxterms,src.nxterms);
    std::swap(xterms,src.xterms);
  }

  /* =============================== */
  /* ======== ARITHMETIC OPS ======= */
  /* =============================== */

  void operator+=(factor_poly const &p) {
    // make sure enough x terms
    resize_xterms(p.nxterms); 
    for(unsigned int i=0;i<p.nxterms;++i) {
      if(!p.xterms[i].is_empty()) {
	xterms[i] += p.xterms[i];
      }
    }
  }

  void operator+=(xy_term const &p) {
    // make sure enough x terms
    resize_xterms(p.xpower+1); 
    // now, do the addition
    xterms[p.xpower] += p;
  }

  void operator*=(xy_term const &p) {
    if(p.xpower > 0) { 
      // need to shift the x's
      resize_xterms(p.xpower + nxterms + 1); 
      for(unsigned int i=nxterms;i>p.xpower;--i) {
	xterms[i-1].swap(xterms[i-(p.xpower+1)]);
      }
    }
    for(unsigned int i=0;i<nxterms;++i) { xterms[i] *= p; }
  }  

  /* The more complicated general case
   */
  void operator*=(factor_poly<T> const &p) {
    if(p.nxterms == 1) {
      // optimise simple case
      yterms<T> const &ps(p.xterms[0]);
      for(unsigned int j=0;j!=nxterms;++j) {
	xterms[j] *= ps; 
      }
    } else {
      factor_poly<T> r;
      
      for(unsigned int i=0;i!=p.nxterms;++i) {
	if(p.xterms[i].is_empty()) { continue; }
	factor_poly<T> tmp(*this);
	tmp *= xy_term(i,0);
	yterms<T> const &ps(p.xterms[i]);
	for(unsigned int j=0;j!=tmp.nxterms;++j) {
	  tmp.xterms[j] *= ps; 
	}
	r += tmp;
      }
      
      this->swap(r);
    }
  }

  factor_poly<T> operator+(factor_poly<T> const &p) const {
    factor_poly<T> r(*this);
    r += p;
    return r;
  }

  factor_poly<T> operator*(xy_term const &p) const {
    factor_poly<T> r(*this);
    r *= p;
    return r;
  }

  factor_poly<T> operator*(factor_poly<T> const &p) const {
    factor_poly<T> r(*this);
    r *= p;
    return r;
  }


  /* ========================== */
  /* ======== OTHER OPS ======= */
  /* ========================== */

  void insert(unsigned int n, xy_term const &p) {
    // make sure enough x terms
    resize_xterms(p.xpower+1); 
    // now, do the addition
    xterms[p.xpower].insert(n,p);
  }
  
  std::string compact_str() const {
    std::string r="";
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

  // This method is such an ugly hack!
  template<class X>
  std::string utos(X n) const {
    std::stringstream ss;
    ss << n;
    return ss.str();
  }

  std::string str() const {
    std::string r="";
    bool first_time=true;
    for(unsigned int i=0;i<nxterms;++i) {    
      if(!xterms[i].is_empty()) {
	std::string xs;
	if(i > 1) { xs = "*x^" + utos(i); }
	else if (i == 1) { xs = "*x"; }

	for(unsigned int j=xterms[i].ymin;j<=xterms[i].ymax;++j) {
	  if(!first_time) { r += " + "; }
	  first_time=false;    	
	  std::string ys;
	  if(j > 1) { ys = "*y^" + utos(j); }
	  else if(j == 1) { ys = "*y"; }
	  r += utos(xterms[i][j]) + xs + ys;
	}
      }
    }
    return r;
  }


  biguint substitute(unsigned int x, unsigned int y) const {
    biguint r(0U);
    for(unsigned int i=0;i<nxterms;++i) {
      r += pow(biguint(x),i) * xterms[i].substitute(y);
    }
    return r;
  }

  unsigned int nterms() const {
    unsigned int r=0;
    for(unsigned int i=0;i<nxterms;++i) {
      r += xterms[i].size();
    }
    return r;
  }
private:
  void destroy() {
    delete [] xterms; // will invoke yterms destructors 
  }
  
  void clone(factor_poly const &p) {
    nxterms = p.nxterms;
    xterms = new yterms<T>[nxterms];
    for(unsigned int i=0;i<nxterms;++i) {
      xterms[i] = p.xterms[i];
    }
  }

  void resize_xterms(unsigned int ns) {
    if(ns < nxterms) { return; }  
    yterms<T> *xs = new yterms<T>[ns];
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
};

template<class T> 
bstreambuf &operator<<(bstreambuf &bout, factor_poly<T> const &fp) {
  bout << fp.nxterms;
  for(unsigned int i=0;i<fp.nxterms;++i) {
    bout << fp.xterms[i];
  }
  return bout;
}

template<class T> 
bistream &operator>>(bistream &bin, factor_poly<T> &fp) {
  unsigned int nxterms;
  bin >> nxterms;
  yterms<T> *xterms = new yterms<T>[nxterms];  
  for(unsigned int i=0;i<nxterms;++i) {
    bin >> xterms[i];
  }
  // I do the following swap trick to reduce
  // the number of copy assignments
  factor_poly<T> tmp(nxterms,xterms);
  fp.swap(tmp);
  
  return bin;
}

#endif
