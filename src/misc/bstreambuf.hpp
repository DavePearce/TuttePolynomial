#ifndef BSTREAMBUF_HPP
#define BSTREAMBUF_HPP

class bstreambuf {
private:
  char *buffer;
  unsigned int max;
  unsigned int ptr;
public:
  bstreambuf() { this(1024); }

  bstreambuf(unsigned int m) {
    max = m;
    ptr = 0;
    buffer = new char[m];
  }

  bstreambuf(bstreambuf const &src) {
    max = src.max;
    ptr = src.ptr;
    buffer = new char[max];
    memcpy(buffer,src.buffer,max);
  }

  bstream const &operator=(bstreambuf const &src) {

  }
}

#endif
