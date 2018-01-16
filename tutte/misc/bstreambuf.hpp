// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#ifndef BSTREAMBUF_HPP
#define BSTREAMBUF_HPP

#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdexcept>

class bstreambuf {
private:
  unsigned char *start;
  unsigned char *end;
  unsigned char *write_ptr;
public:
  bstreambuf() {
    start = new unsigned char[1024];
    end = start + 1024;
    write_ptr = start;    
  }

  bstreambuf(unsigned int max) {
    start = new unsigned char[max];
    end = start + max;
    write_ptr = start;
  }

  bstreambuf(unsigned char *s, unsigned char *e) {
    start = s;
    end = e;
    write_ptr = e;
  }

  bstreambuf(bstreambuf const &src) {
    start = new unsigned char[src.max()];
    end = start + src.max();
    write_ptr = start + src.size();
    memcpy(start,src.start,src.size());
  }

  ~bstreambuf() { delete [] start; }

  bstreambuf const &operator=(bstreambuf const &src) {
    if(this != &src) {
      delete [] start;
      start = new unsigned char[src.max()];
      end = start + src.max();
      write_ptr = start + src.size();
      memcpy(start,src.start,src.size());      
    }
    return *this;
  }

  void reset() { write_ptr = start; }

  void write(unsigned char v) {    
    if((size()+sizeof(unsigned char)) > max()) {
      resize(size() + sizeof(unsigned char));      
    } 
    // this line is a bit of a hack
    *((unsigned char*) write_ptr) = v;
    write_ptr += sizeof(unsigned char);
  }

  void write(char v) {    
    if((size()+sizeof(char)) > max()) {
      resize(size() + sizeof(char));      
    } 
    // this line is a bit of a hack
    *((char*) write_ptr) = v;
    write_ptr += sizeof(char);
  }

  void write(unsigned short v) {    
    if((size()+sizeof(unsigned short)) > max()) {
      resize(size() + sizeof(unsigned short));      
    } 
    // this line is a bit of a hack
    *((unsigned short*) write_ptr) = v;
    write_ptr += sizeof(unsigned short);
  }

  void write(short v) {    
    if((size()+sizeof(short)) > max()) {
      resize(size() + sizeof(short));      
    } 
    // this line is a bit of a hack
    *((short*) write_ptr) = v;
    write_ptr += sizeof(short);
  }

  void write(unsigned int v) {
    if((size()+sizeof(unsigned int)) > max()) {
      resize(size() + sizeof(unsigned int));      
    } 
    // this line is a bit of a hack
    *((unsigned int*) write_ptr) = v;
    write_ptr += sizeof(unsigned int);
  }

  void write(int v) {    
    if((size()+sizeof(int)) > max()) {
      resize(size() + sizeof(int));      
    } 
    // this line is a bit of a hack
    *((int*) write_ptr) = v;
    write_ptr += sizeof(int);
  }

  void write(unsigned long v) {    
    if((size()+sizeof(unsigned long)) > max()) {
      resize(size() + sizeof(unsigned long));      
    } 
    // this line is a bit of a hack
    *((unsigned long*) write_ptr) = v;
    write_ptr += sizeof(unsigned long);
  }

  void write(long v) {    
    if((size()+sizeof(long)) > max()) {
      resize(size() + sizeof(long));      
    } 
    // this line is a bit of a hack
    *((long*) write_ptr) = v;
    write_ptr += sizeof(long);
  }


  void write(unsigned long long v) {    
    if((size()+sizeof(unsigned long long)) > max()) {
      resize(size() + sizeof(unsigned long long));      
    } 
    // this line is a bit of a hack
    *((unsigned long long*) write_ptr) = v;
    write_ptr += sizeof(unsigned long long);
  }

  void write(long long v) {    
    if((size()+sizeof(long long)) > max()) {
      resize(size() + sizeof(long long));      
    } 
    // this line is a bit of a hack
    *((long long*) write_ptr) = v;
    write_ptr += sizeof(long long);
  }

  unsigned int size() const { return write_ptr-start; }
  unsigned int max() const { return end-start; }
  unsigned char const * const c_ptr() const { return start; }

private:
  // resize so we have at least min bytes
  void resize(unsigned int min) {
    unsigned int osize = size();
    unsigned int nmax = std::max(min,2*max());
    unsigned char *nstart = new unsigned char[nmax];
    memcpy(nstart,start,osize);    
    delete [] start;
    start = nstart;
    end = start + nmax;
    write_ptr = start + osize;    
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
bstreambuf& operator<<(bstreambuf &out, long long val);
bstreambuf& operator<<(bstreambuf &out, unsigned long long val);

#endif
