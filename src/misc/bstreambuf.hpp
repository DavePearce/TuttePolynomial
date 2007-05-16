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

  void write(unsigned char v) {    
    if((size()+sizeof(unsigned char)) > max()) {
      resize(size() + sizeof(unsigned char));      
    } 
    // this line is a bit of a hack
    *((unsigned char*) ptr) = v;
    ptr += sizeof(unsigned char);
  }

  void write(char v) {    
    if((size()+sizeof(char)) > max()) {
      resize(size() + sizeof(char));      
    } 
    // this line is a bit of a hack
    *((char*) ptr) = v;
    ptr += sizeof(char);
  }

  void write(unsigned short v) {    
    if((size()+sizeof(unsigned short)) > max()) {
      resize(size() + sizeof(unsigned short));      
    } 
    // this line is a bit of a hack
    *((unsigned short*) ptr) = v;
    ptr += sizeof(unsigned short);
  }

  void write(short v) {    
    if((size()+sizeof(short)) > max()) {
      resize(size() + sizeof(short));      
    } 
    // this line is a bit of a hack
    *((short*) ptr) = v;
    ptr += sizeof(short);
  }

  void write(unsigned int v) {    
    if((size()+sizeof(unsigned int)) > max()) {
      resize(size() + sizeof(unsigned int));      
    } 
    // this line is a bit of a hack
    *((unsigned int*) ptr) = v;
    ptr += sizeof(unsigned int);
  }

  void write(int v) {    
    if((size()+sizeof(int)) > max()) {
      resize(size() + sizeof(int));      
    } 
    // this line is a bit of a hack
    *((int*) ptr) = v;
    ptr += sizeof(int);
  }

  void write(unsigned long v) {    
    if((size()+sizeof(unsigned long)) > max()) {
      resize(size() + sizeof(unsigned long));      
    } 
    // this line is a bit of a hack
    *((unsigned long*) ptr) = v;
    ptr += sizeof(unsigned long);
  }

  void write(long v) {    
    if((size()+sizeof(long)) > max()) {
      resize(size() + sizeof(long));      
    } 
    // this line is a bit of a hack
    *((long*) ptr) = v;
    ptr += sizeof(long);
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
