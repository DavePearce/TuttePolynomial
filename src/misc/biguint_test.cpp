#include <iostream>
#include <cstdlib>
#include <time.h>

#include "biguint.hpp"

using namespace std;

unsigned int random_word() {
  unsigned int w1 = (unsigned int) (65536.0*rand()/(RAND_MAX+1.0));
  unsigned int w2 = (unsigned int) (65536.0*rand()/(RAND_MAX+1.0));
  return (w1 << 16U) + w2;
}

void add_test(unsigned int count) {
  for(unsigned int i=0;i!=count;++i) {
    unsigned int w1(random_word());
    unsigned int w2(random_word());
    biguint r1(w1);
    biguint r2(w2);
    unsigned long long r3(w1);
    r2 += r1; // bigint bigint
    r1 += w2; // bigint uint
    r3 += w2;    
    cout << "TESTING: " << w1 << " + " << w2 << endl;
    if(r1 != r3) {
      // error
      cout << "ERROR: " << w1 << " + " << w2 << " gives " << r1.c_ulonglong() << ", not " << r3 << endl;
    }
    if(r2 != r3) {
      // error
      cout << "ERROR: " << w1 << " + " << w2 << " gives " << r2.c_ulonglong() << ", not " << r3 << endl;
    }
  }
}

int main(int argc, char *argv[]) {
  // seed random number generator
  srand(time(NULL));  
  add_test(10000);
}
