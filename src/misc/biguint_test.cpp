#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <time.h>

#include "biguint.hpp"

using namespace std;

typedef enum { ADD, SUB, DIV, MUL } aop;

unsigned int random_word() {
  unsigned int w1 = (unsigned int) (65536.0*rand()/(RAND_MAX+1.0));
  unsigned int w2 = (unsigned int) (65536.0*rand()/(RAND_MAX+1.0));
  return (w1 << 16U) + w2;
}

string op2str(aop op) {
  if(op == ADD) { return "+"; }
  else if(op == SUB) { return "-"; }
  else if(op == MUL) { return "*"; }
  else { return "/"; }
}

/*
void commutative_mul_test(unsigned int count, unsigned int length) {
  for(unsigned int i=0;i!=count;++i) {
    unsigned int ws[length];
    for(unsigned int j=0;j!=length;++j) {
      ws[j] = random_word();
    }

    biguint v(1U);
    for(unsigned int j=0;j!=length;++j) {
      v *= ws[j];
    }

    biguint w(v);

    // now for the commutative part
    for(unsigned int j=length;j>0;--j) {
      v /= ws[j-1];
    }
    
    if(v != 1U) {
      // error
      cout << "ERROR: commutative mul test failed! " << endl;
      for(unsigned int j=0;j!=length;++j) {
	if(j != 0) { cout << "*"; }
	cout << ws[j];
      }
      cout << " = " << w << endl;
      cout << w;
      for(unsigned int j=length;j!=0;--j) {
	cout << " / " << ws[j-1];
      }
      cout << " = " << v << endl;
    } 
  }
}
*/
void commutative_add_test(unsigned int count, unsigned int length) {
  for(unsigned int i=0;i!=count;++i) {
    unsigned int ws[length];
    for(unsigned int j=0;j!=length;++j) {
      ws[j] = random_word();
    }

    biguint v(0U);
    for(unsigned int j=0;j!=length;++j) {
      v += ws[j];
    }
    
    // now for the commutative part
    for(unsigned int j=0;j!=length;++j) {      
      v -= ws[j];
    }
    
    if(v != 0U) {
      // error
      cout << "ERROR: commutative add test failed!" << endl;
    } 
  }
}

void primitive_test(unsigned int count, aop op) {
  for(unsigned int i=0;i!=count;++i) {
    unsigned int w1(random_word());
    unsigned int w2(random_word());
    if((op == SUB || op == DIV) && w1 < w2) { swap(w1,w2); }
    biguint r1(w1);
    biguint r2(w1);
    unsigned long long r3(w1);

    if(op == ADD) {
      r1 += biguint(w2); // bigint bigint
      r2 += w2;          // bigint uint
      r3 += w2;    
    } else if(op == SUB) {
      r1 -= biguint(w2); // bigint bigint
      r2 -= w2; // bigint uint
      r3 -= w2;    
    } else if(op == MUL) {
      cout << "STAGE 1" << endl;
      r1 *= biguint(w2);
      cout << "STAGE 2" << endl;
      r2 *= w2;
      cout << "STAGE 3" << endl;
      r3 *= w2;
      cout << "STAGE 4" << endl;
    } else if(op == DIV) {
      cout << "STAGE 5" << endl;
      r1 /= w2;
      cout << "STAGE 6" << endl;
      r2 /= w2;
      cout << "STAGE 7" << endl;
      r3 /= w2;
    }

    if(r1 != r3) {
      // error
      cout << "ERROR(1): " << w1 << " " << op2str(op) << " " << w2 << " gives " << r1.c_ulonglong() << ", not " << r3 << endl;
    } else if(r2 != r3) {
      // error
      cout << "ERROR(2): " << w1 << " " << op2str(op) << " " << w2 << " gives " << r2.c_ulonglong() << ", not " << r3 << endl;
    } 
  }
}

int main(int argc, char *argv[]) {

  // ------------------------------
  // Process command-line arguments
  // ------------------------------

  #define OPT_HELP 0
  #define OPT_COUNT 1

  struct option long_options[]={
    {"help",no_argument,NULL,OPT_HELP},
    {"count",required_argument,NULL,OPT_COUNT},
    NULL
  };
  
  char *descriptions[]={
    "        --help                    display this information",
    " -c     --count=<amount>          number of times to repeat each test",
    NULL
  };

  unsigned int count = 10000;
  unsigned int v;

  while((v=getopt_long(argc,argv,"c:",long_options,NULL)) != -1) {
    switch(v) {      
    case OPT_HELP:
      cout << "usage: " << argv[0] << " [options] <input graph file>" << endl;
      cout << "options:" << endl;
      for(char **ptr=descriptions;*ptr != NULL; ptr++) {
	cout << *ptr << endl;
      }    
      exit(1);
          
    case 'c':
    case OPT_COUNT:
      count = atoi(optarg);
    }
  }

  // seed random number generator
  srand(time(NULL));  
  // do the tests!
  primitive_test(count,ADD);
  cout << "PRIM ADD DONE" << endl;
  primitive_test(count,SUB);
  cout << "PRIM SUB DONE" << endl;
  commutative_add_test(count,10);
  primitive_test(count,MUL);
  // primitive_test(count,DIV);
  //  commutative_mul_test(count,10);
}
