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

void primitive_test(unsigned int count, aop op) {
  for(unsigned int i=0;i!=count;++i) {
    unsigned int w1(random_word());
    unsigned int w2(random_word());
    if(op == SUB && w1 > w2) { swap(w1,w2); }
    biguint r1(w1);
    biguint r2(w2);
    unsigned long long r3(w2);
    if(op == ADD) {
      r2 += r1; // bigint bigint
      r1 += w2; // bigint uint
      r3 += w1;    
    } else if(op == SUB) {
      r2 -= r1; // bigint bigint
      r1 -= w2; // bigint uint
      r3 -= w1;    
    } else if(op == MUL) {

    } else if(op == DIV) {

    }
    /*
    if(r1 != r3) {
      // error
      cout << "ERROR: " << w2 << " " << op2str(op) << " " << w1 << " gives " << r1.c_ulonglong() << ", not " << r3 << endl;
    } 
    
    else 
      */
      if(r2 != r3) {
      // error
      cout << "ERROR: " << w1 << " " << op2str(op) << " " << w2 << " gives " << r2.c_ulonglong() << ", not " << r3 << endl;
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
  primitive_test(count,ADD);
}
