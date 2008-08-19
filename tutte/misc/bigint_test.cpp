#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <time.h>

#include "bigint.hpp"

using namespace std;

typedef enum { ADD, SUB, DIV, MUL, LT, LTEQ, GT, GTEQ, EQ, NEQ } aop;

int random_word() {
  unsigned int w1 = (unsigned int) (65536.0*rand()/(RAND_MAX+1.0));
  unsigned int w2 = (unsigned int) (65536.0*rand()/(RAND_MAX+1.0));
  return (int) ((w1 << 16U) + w2);
}

string op2str(aop op) {
  if(op == ADD) { return "+"; }
  else if(op == SUB) { return "-"; }
  else if(op == MUL) { return "*"; }
  else if(op == DIV) { return "/"; }
  else if(op == EQ) { return "=="; }
  else if(op == NEQ) { return "!="; }
  else if(op == LT) { return "<"; }
  else if(op == LTEQ) { return "<="; }
  else if(op == GT) { return ">"; }
  else if(op == GTEQ) { return ">="; }
}

void comparator_test(unsigned int count, aop op) {
  for(unsigned int i=0;i!=count;++i) {
    int w1(random_word());
    int w2(random_word());

    bigint r1(w1);
    bigint r2(w2);

    if(op == EQ) {
      if(w1 != w2 && (r1 == r2 || r2 == r1 || r1 == w2 || r2 == w1)) {
	cout << "ERROR(1): " << w1 << " " << op2str(op) << " " << w2 << " gives: " << (r1 == r2) << ", " << (r2 == r1) << ", " << (r1 == w2)  << ", " << (r2 == w1) << endl;
      } else if(w1 == w2 && (r1 != r2 || r2 != r1 || r1 != w2 || r2 != w1)) {
	cout << "ERROR(1): " << w1 << " " << op2str(NEQ) << " " << w2 << " gives: " << (r1 != r2) << ", " << (r2 != r1) << ", " << (r1 != w2)  << ", " << (r2 != w1) << endl;
      }
    } else if(op == LT) {
      if(w1 >= w2 && (r1 < r2 || r1 < w2)) {
	cout << "ERROR(1): " << w1 << " " << op2str(LT) << " " << w2 << " gives: " << (r1 < r2) << ", " << (r1 < w2) << endl;
      } else if(w1 < w2 && (r1 >= r2 || r1 >= w2)) {
	cout << "ERROR(1): " << w1 << " " << op2str(GTEQ) << " " << w2 << " gives: " << (r1 >= r2) << ", " << (r1 >= w2) << endl;
      }
    } else if(op == LTEQ) {
      if(w1 > w2 && (r1 <= r2 || r1 <= w2)) {
	cout << "ERROR(1): " << w1 << " " << op2str(LTEQ) << " " << w2 << " gives: " << (r1 <= r2) << ", " << (r1 <= w2) << endl;
      } else if(w1 <= w2 && (r1 > r2 || r1 > w2)) {
	cout << "ERROR(1): " << w1 << " " << op2str(GT) << " " << w2 << " gives: " << (r1 > r2) << ", " << (r1 > w2) << endl;
      }
    }
  }

  for(unsigned int i=0;i!=count;++i) {
    long long w1(random_word());
    long long w2(random_word());
    w1 = w1 * random_word();
    w2 = w2 * random_word();

    bigint r1(w1+1);
    bigint r2(w2);

    if(op == EQ) {
      if(w1 != w2 && (r1 == r2 || r2 == r1 || r1 == w2 || r2 == w1)) {
	cout << "ERROR(1): " << w1 << " " << op2str(op) << " " << w2 << " gives: " << (r1 == r2) << ", " << (r2 == r1) << ", " << (r1 == w2)  << ", " << (r2 == w1) << endl;
      } else if(w1 == w2 && (r1 != r2 || r2 != r1 || r1 != w2 || r2 != w1)) {
	cout << "ERROR(1): " << w1 << " " << op2str(NEQ) << " " << w2 << " gives: " << (r1 != r2) << ", " << (r2 != r1) << ", " << (r1 != w2)  << ", " << (r2 != w1) << endl;
      }
    } else if(op == LT) {
      if(w1 >= w2 && (r1 < r2 || r1 < w2)) {
	cout << "ERROR(1): " << w1 << " " << op2str(LT) << " " << w2 << " gives: " << (r1 < r2) << ", " << (r1 < w2) << endl;
      } else if(w1 < w2 && (r1 >= r2 || r1 >= w2)) {
	cout << "ERROR(1): " << w1 << " " << op2str(GTEQ) << " " << w2 << " gives: " << (r1 >= r2) << ", " << (r1 >= w2) << endl;
      }
    } else if(op == LTEQ) {
      if(w1 > w2 && (r1 <= r2 || r1 <= w2)) {
	cout << "ERROR(1): " << w1 << " " << op2str(LTEQ) << " " << w2 << " gives: " << (r1 <= r2) << ", " << (r1 <= w2) << endl;
      } else if(w1 <= w2 && (r1 > r2 || r1 > w2)) {
	cout << "ERROR(1): " << w1 << " " << op2str(GT) << " " << w2 << " gives: " << (r1 > r2) << ", " << (r1 > w2) << endl;
      }
    }
  }
}

void commutative_mul_test(unsigned int count, unsigned int length) {
  for(unsigned int i=0;i!=count;++i) {
    int ws[length];

    for(unsigned int j=0;j!=length;++j) {
      ws[j] = random_word();
    }

    bigint v(1);
    for(unsigned int j=0;j!=length;++j) {
      v *= ws[j];
    }

    bigint w(v);

    // now for the commutative part
    for(unsigned int j=length;j>0;--j) {
      v /= ws[j-1];
    }
    
    if(v != 1) {
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

void commutative_add_test(unsigned int count, unsigned int length) {

  for(unsigned int i=0;i!=count;++i) {
    cout << "STAGE 1" << endl;
    int ws[length];
    for(unsigned int j=0;j!=length;++j) {
      ws[j] = random_word();
    }

    cout << "STAGE 2" << endl;

    bigint v(0);
    for(unsigned int j=0;j!=length;++j) {
      v += ws[j];
    }

    cout << "STAGE 3" << endl;

    bigint w(v);

    // now for the commutative part
    for(unsigned int j=0;j!=length;++j) {      
      v -= ws[j];
    }

    cout << "STAGE 4" << endl;    

    if(v != 0) {
      // error
      cout << "ERROR: commutative add test failed!" << endl;
      for(unsigned int j=0;j!=length;++j) {
	if(j != 0) { cout << "+"; }
	cout << ws[j];
      }
      cout << " = " << w << endl;
      cout << w;
      for(unsigned int j=length;j!=0;--j) {
	cout << " - " << ws[j-1];
      }
      cout << " = " << v << endl;
    } 

    cout << "STAGE 5" << endl;
  }
}

void primitive_test(unsigned int count, aop op) {
  for(unsigned int i=0;i!=count;++i) {
    int w1(random_word());
    int w2(random_word());
    if((op == SUB || op == DIV) && w1 < w2) { swap(w1,w2); }
    bigint r1(w1);
    bigint r2(w1);
    long long r3(w1);

    if(op == ADD) {
      r1 += bigint(w2); // bigint bigint
      r2 += w2;          // bigint uint
      r3 += w2;    
    } else if(op == SUB) {
      r1 -= bigint(w2); // bigint bigint
      r2 -= w2; // bigint uint
      r3 -= w2;    
    } else if(op == MUL) {
      r1 *= bigint(w2);
      r2 *= w2;
      r3 *= w2;
    } else if(op == DIV) {
      r1 /= w2;
      r2 /= w2;
      r3 /= w2;
    }

    if(r1 != r3) {
      // error
      cout << "ERROR(1): " << w1 << " " << op2str(op) << " " << w2 << " gives " << r1.c_longlong() << ", not " << r3 << endl;
    } else if(r2 != r3) {
      // error
      cout << "ERROR(2): " << w1 << " " << op2str(op) << " " << w2 << " gives " << r2.c_longlong() << ", not " << r3 << endl;
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
  cout << "PRIM MUL DONE" << endl;
  primitive_test(count,DIV);
  cout << "PRIM DIV DONE" << endl;
  commutative_mul_test(count,10);
  comparator_test(count,EQ);
  cout << "COMP ==, != DONE" << endl;
  comparator_test(count,LT);
  cout << "COMP <, >= DONE" << endl;
  comparator_test(count,LTEQ);
  cout << "COMP <=, > DONE" << endl;
}
