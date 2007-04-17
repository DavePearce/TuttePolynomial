#include <iostream>
#include "factor_poly.hpp"
#include "algorithms.hpp"

using namespace std;

unsigned int resize_stats=0;

int main(unsigned int argc, char *argv[]) {
  //  factor_poly fp1(xy_term(1,1,3));
  //  factor_poly fp2(xy_term(1,3,4));
  //  fp1 += fp2;

  factor_poly fp1;

  fp1 += xy_term(0,1,3);
  cout << fp1.str() << endl;
  fp1 += xy_term(0,1,2);

  cout << fp1.str() << endl;

  //  fp1 *= xy_term(0,1,6);

  //  cout << fp1.str() << endl;

  return 0;
}
