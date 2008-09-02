#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <time.h>

#include "../misc/bigint.hpp"
#include "factor_poly.hpp"

using namespace std;

typedef enum { ADD, MUL, FULLMUL } aop;

uint32_t random_word(unsigned int max) {
  // i've reduced the size of words produce, since this reflects more
  // closely the operation of the tutte computation.
  float m(max);
  unsigned int w1 = (unsigned int) (m*rand()/(RAND_MAX+1.0));
  return (uint32_t) w1;
}

xy_term random_xy_term(unsigned int width) {
  uint32_t rw1(random_word(width));
  uint32_t rw2(random_word(width));
  uint32_t rw3(random_word(width));

  if(rw3 > rw2) {
    return xy_term(rw1,rw2,rw3);
  } else {
    return xy_term(rw1,rw2);
  }
}

factor_poly<biguint> random_poly(unsigned int length, unsigned int width) {
  factor_poly<biguint> r(random_xy_term(width));
  for(unsigned int j=0;j!=length;++j) {
    r += random_xy_term(width);
  }
  return r;
}

void primitive_test(unsigned int count, unsigned int length, unsigned int width, aop op, bool verbose) {
  for(unsigned int i=0;i!=count;++i) {
    factor_poly<biguint> p1(random_poly(length,width)*random_poly(length,width)*random_poly(length,width));
    factor_poly<biguint> p2(random_poly(length,width)*random_poly(length,width)*random_poly(length,width));

    if(op == ADD) {
      bigint sum1_1 = p1.substitute(1,1) + p2.substitute(1,1);
      bigint sum2_2 = p1.substitute(2,2) + p2.substitute(2,2);
      p1 = p1 + p2;
      
      if(p1.substitute(1,1) != sum1_1) {
	cerr << "ERROR(1.1) ********** " << endl;
      } else if(p1.substitute(2,2) != sum2_2) {
	cerr << "ERROR(1.2) ********** " << endl;
      }
    } else if(op == MUL) {
      xy_term xyt = random_xy_term(width);
      p2 = factor_poly<biguint>(xyt);
      bigint sum1_1 = p1.substitute(1,1) * p2.substitute(1,1);
      bigint sum2_2 = p1.substitute(2,2) * p2.substitute(2,2);
      p1 = p1 * xyt;

      if(p1.substitute(1,1) != sum1_1) {
	cerr << "ERROR(2.1) ********** " << endl;
      } else if(p1.substitute(2,2) != sum2_2) {
	cerr << "ERROR(2.2) ********** " << endl;
      }
    } else if(op == FULLMUL) {
      bigint sum1_1 = p1.substitute(1,1) * p2.substitute(1,1);
      bigint sum2_2 = p1.substitute(2,2) * p2.substitute(2,2);
      p1 = p1 * p2;

      if(p1.substitute(1,1) != sum1_1) {
	cerr << "ERROR(3.1) ********** " << endl;
      } else if(p1.substitute(2,2) != sum2_2) {
	cerr << "ERROR(3.2) ********** " << endl;
      }
    }
    if(verbose) {
      cout << "=========== POLYNOMIAL ============" << endl << p1.str() << endl;
    }
  }
}

int main(int argc, char *argv[]) {

  // ------------------------------
  // Process command-line arguments
  // ------------------------------

  #define OPT_HELP 0
  #define OPT_COUNT 1
  #define OPT_LENGTH 2
  #define OPT_WIDTH 3
  #define OPT_VERBOSE 4

  struct option long_options[]={
    {"help",no_argument,NULL,OPT_HELP},
    {"count",required_argument,NULL,OPT_COUNT},
    {"length",required_argument,NULL,OPT_LENGTH},
    {"width",required_argument,NULL,OPT_WIDTH},
    {"verbose",no_argument,NULL,OPT_VERBOSE},
    NULL
  };
  
  char *descriptions[]={
    "        --help                    display this information",
    " -v     --verbose                 display infor on the polynomials being test",
    " -c     --count=<amount>          number of times to repeat each test",
    " -l     --length=<amount>         how long to build the polynomials",
    " -w     --width=<amount>          how wide to build the polynomials",
    NULL
  };

  unsigned int count = 10000;
  unsigned int length = 100;
  unsigned int width = 10;
  unsigned int v;
  bool verbose = false;

  while((v=getopt_long(argc,argv,"c:l:w:v",long_options,NULL)) != -1) {
    switch(v) {      
    case OPT_HELP:
      cout << "usage: " << argv[0] << " [options] <input graph file>" << endl;
      cout << "options:" << endl;
      for(char **ptr=descriptions;*ptr != NULL; ptr++) {
	cout << *ptr << endl;
      }    
      exit(1);

    case 'v':
    case OPT_VERBOSE:
      verbose=true;
      break;          
    case 'c':
    case OPT_COUNT:
      count = atoi(optarg);
      break;
    case 'l':
    case OPT_LENGTH:
      length = atoi(optarg);
      break;
    case 'w':
    case OPT_WIDTH:
      width = atoi(optarg);
      break;
    }
  }

  // seed random number generator
  srand(time(NULL));  
  // do the tests!
  try {
    primitive_test(count,length,width,ADD,verbose);
    cout << "PRIM ADD DONE" << endl;
    primitive_test(count,length,width,MUL,verbose);
    cout << "PRIM MUL DONE" << endl;
    primitive_test(count,length,width,FULLMUL,verbose);
    cout << "PRIM FULLMUL DONE" << endl;
  } catch(exception const &e) {
    cout << "CAUGHT EXCEPTION: " << e.what() << endl;
  }
}
