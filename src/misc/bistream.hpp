#ifndef BISTREAM_HPP
#define BISTREAM_HPP

#include "bstreambuf.hpp"

class bistream {
private:
  unsigned char const *start;
  unsigned char const *end;
  unsigned char const *read_ptr;
public:
    bistream(unsigned char const *s, unsigned int length) {
    start = s;
    end = s + length;
    read_ptr = s;
  }

  bistream(bistream const &src) {
    start = src.start;
    end = src.end;
    read_ptr = src.read_ptr;
  }

  bistream(bstreambuf const &src) {
    start = src.c_ptr();
    end = start + src.size();
    read_ptr = start;
  }

  unsigned int size() { return end - read_ptr; }

  void read(char& v) {    
    if((read_ptr+sizeof(char)) > end) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((char*) read_ptr);    
    read_ptr += sizeof(char);   
  }

  void read(unsigned char& v) {    
    if((read_ptr+sizeof(unsigned char)) > end) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((unsigned char*) read_ptr);    
    read_ptr += sizeof(unsigned char);   
  }

  void read(short& v) {    
    if((read_ptr+sizeof(short)) > end) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((short*) read_ptr);    
    read_ptr += sizeof(short);   
  }

  void read(unsigned short& v) {    
    if((read_ptr+sizeof(unsigned short)) > end) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((unsigned short*) read_ptr);    
    read_ptr += sizeof(unsigned short);   
  }

  void read(int& v) {    
    if((read_ptr+sizeof(int)) > end) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((int*) read_ptr);    
    read_ptr += sizeof(int);   
  }

  void read(unsigned int& v) {    
    if((read_ptr+sizeof(unsigned int)) > end) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((unsigned int*) read_ptr);    
    read_ptr += sizeof(unsigned int);   
  }

  void read(long& v) {    
    if((read_ptr+sizeof(long)) > end) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((long*) read_ptr);    
    read_ptr += sizeof(long);   
  }

  void read(unsigned long& v) {    
    if((read_ptr+sizeof(unsigned long)) > end) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((unsigned long*) read_ptr);    
    read_ptr += sizeof(unsigned long);     
  } 
  
  void read(long long& v) {    
    if((read_ptr+sizeof(long long)) > end) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((long long*) read_ptr);    
    read_ptr += sizeof(long long);   
  }

  void read(unsigned long long& v) {    
    if((read_ptr+sizeof(unsigned long long)) > end) {
      throw std::runtime_error("attempt to read past end of stream!");
    } 
    v = *((unsigned long long*) read_ptr);    
    read_ptr += sizeof(unsigned long long);     
  }  
};

bistream &operator>>(bistream &out, char&);
bistream &operator>>(bistream &out, unsigned char&);
bistream &operator>>(bistream &out, short&);
bistream &operator>>(bistream &out, unsigned short&);
bistream &operator>>(bistream &out, int&);
bistream &operator>>(bistream &out, unsigned int&);
bistream &operator>>(bistream &out, long&);
bistream &operator>>(bistream &out, unsigned long&);
bistream &operator>>(bistream &out, long long&);
bistream &operator>>(bistream &out, unsigned long long&);


#endif
