#ifndef BSTREAMBUF_HPP
#define BSTREAMBUF_HPP

class bstreambuf {
private:
  char *start;
  char *end;
  char *ptr;
public:
  bstreambuf() { this(1024); }

  bstreambuf(unsigned int m) {
    start = new char[m];
    ptr = start;
    max = start + m;
  }

  bstreambuf(bstreambuf const &src) {
    start = new char[src.max()];
    memcpy(start,src.buffer,src.size());
  }

  bstream const &operator=(bstreambuf const &src) {
    if(this != &src) {
      delete [] start;
      end = src.end;
      ptr = src.ptr;
      start = new char[src.max()];
      memcpy(buffer,src.buffer,src.size());      
    }
  }

  void write(unsigned int v) {
    if((ptr+sizeof(v)) >= end) {
      resize(ptr + sizeof(unsigned int));      
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
    unsigned int nmax = std::max(min,2*max());
    char *nstart = new char[nmax];
    memcpy(nbuf,start,size());
    
    
  }
}

#endif
