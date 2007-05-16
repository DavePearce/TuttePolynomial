#ifndef BSTREAMBUF_HPP
#define BSTREAMBUF_HPP

#include <iostream>
#include <cstring>
#include <algorithm>

class bstreambuf {
private:
  char *start;
  char *end;
  char *ptr;
public:
  bstreambuf() {
    start = new char[1024];
    end = start + 1024;
    ptr = start;
  }

  bstreambuf(unsigned int max) {
    start = new char[max];
    end = start + max;
    ptr = start;
  }

  bstreambuf(bstreambuf const &src) {
    start = new char[src.max()];
    end = start + src.max();
    ptr = start + src.size();
    memcpy(start,src.start,src.size());
  }

  ~bstreambuf() { delete [] start; }

  bstreambuf const &operator=(bstreambuf const &src) {
    if(this != &src) {
      delete [] start;
      start = new char[src.max()];
      end = start + src.max();
      ptr = start + src.size();
      memcpy(start,src.start,src.size());      
    }
  }

  void write(unsigned int v) {    
    if((size()+sizeof(unsigned int)) > max()) {
      resize(size() + sizeof(unsigned int));      
    } 
    // this line is a bit of a hack
    *((unsigned int*) ptr) = v;
    ptr += sizeof(unsigned int);
  }

  unsigned int size() const { return ptr-start; }
  unsigned int max() const { return end-start; }

private:
  // resize so we have at least min bytes
  void resize(unsigned int min) {
    unsigned int osize = size();
    unsigned int nmax = std::max(min,2*max());
    char *nstart = new char[nmax];
    memcpy(nstart,start,osize);    
    delete [] start;
    start = nstart;
    end = start + nmax;
    ptr = start + osize;    
  }
};

bstreambuf& operator<<(bstreambuf &out, char val);
bstreambuf& operator<<(bstreambuf &out, unsigned char val);
bstreambuf& operator<<(bstreambuf &out, short val);
bstreambuf& operator<<(bstreambuf &out, unsigned short val);
bstreambuf& operator<<(bstreambuf &out, int val);
bstreambuf& operator<<(bstreambuf &out, unsigned int val);
bstreambuf& operator<<(bstreambuf &out, long val);
bstreambuf& operator<<(bstreambuf &out, unsigned long val);

#endif
