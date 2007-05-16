#ifndef BSTREAMBUF_HPP
#define BSTREAMBUF_HPP

#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdexcept>

class bstreambuf {
private:
  char *start;
  char *end;
  char *write_ptr;
  char *read_ptr;
public:
  bstreambuf() {
    start = new char[1024];
    end = start + 1024;
    write_ptr = start;    
    read_ptr = start;
  }

  bstreambuf(unsigned int max) {
    start = new char[max];
    end = start + max;
    write_ptr = start;
    read_ptr = start;
  }

  bstreambuf(bstreambuf const &src) {
    start = new char[src.max()];
    end = start + src.max();
    write_ptr = start + src.size();
    read_ptr = start + src.pos();
    memcpy(start,src.start,src.size());
  }

  ~bstreambuf() { delete [] start; }

  bstreambuf const &operator=(bstreambuf const &src) {
    if(this != &src) {
      delete [] start;
      start = new char[src.max()];
      end = start + src.max();
      write_ptr = start + src.size();
      memcpy(start,src.start,src.size());      
    }
  }

  void reset() { 
    write_ptr = start; 
    read_ptr = start; 
  }

  void read(char& v) {    
    if((pos()+sizeof(char)) > size()) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((char*) read_ptr);    
    read_ptr += sizeof(char);   
  }

  void read(unsigned char& v) {    
    if((pos()+sizeof(unsigned char)) > size()) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((unsigned char*) read_ptr);    
    read_ptr += sizeof(unsigned char);   
  }

  void read(short& v) {    
    if((pos()+sizeof(short)) > size()) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((short*) read_ptr);    
    read_ptr += sizeof(short);   
  }

  void read(unsigned short& v) {    
    if((pos()+sizeof(unsigned short)) > size()) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((unsigned short*) read_ptr);    
    read_ptr += sizeof(unsigned short);   
  }

  void read(int& v) {    
    if((pos()+sizeof(int)) > size()) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((int*) read_ptr);    
    read_ptr += sizeof(int);   
  }

  void read(unsigned int& v) {    
    if((pos()+sizeof(unsigned int)) > size()) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((unsigned int*) read_ptr);    
    read_ptr += sizeof(unsigned int);   
  }

  void read(long& v) {    
    if((pos()+sizeof(long)) > size()) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((long*) read_ptr);    
    read_ptr += sizeof(long);   
  }

  void read(unsigned long& v) {    
    if((pos()+sizeof(unsigned long)) > size()) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((unsigned long*) read_ptr);    
    read_ptr += sizeof(unsigned long);     
  }
  
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

  unsigned int pos() const { return read_ptr-start; }
  unsigned int size() const { return write_ptr-start; }
  unsigned int max() const { return end-start; }

private:
  // resize so we have at least min bytes
  void resize(unsigned int min) {
    unsigned int osize = size();
    unsigned int opos = pos();
    unsigned int nmax = std::max(min,2*max());
    char *nstart = new char[nmax];
    memcpy(nstart,start,osize);    
    delete [] start;
    start = nstart;
    end = start + nmax;
    write_ptr = start + osize;    
    read_ptr = start + opos;
  }
};

bstreambuf &operator>>(bstreambuf &out, char&);
bstreambuf &operator>>(bstreambuf &out, unsigned char&);
bstreambuf &operator>>(bstreambuf &out, short&);
bstreambuf &operator>>(bstreambuf &out, unsigned short&);
bstreambuf &operator>>(bstreambuf &out, int&);
bstreambuf &operator>>(bstreambuf &out, unsigned int&);
bstreambuf &operator>>(bstreambuf &out, long&);
bstreambuf &operator>>(bstreambuf &out, unsigned long&);


bstreambuf& operator<<(bstreambuf &out, char val);
bstreambuf& operator<<(bstreambuf &out, unsigned char val);
bstreambuf& operator<<(bstreambuf &out, short val);
bstreambuf& operator<<(bstreambuf &out, unsigned short val);
bstreambuf& operator<<(bstreambuf &out, int val);
bstreambuf& operator<<(bstreambuf &out, unsigned int val);
bstreambuf& operator<<(bstreambuf &out, long val);
bstreambuf& operator<<(bstreambuf &out, unsigned long val);

#endif
