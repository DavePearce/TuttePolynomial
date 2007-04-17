#include <iostream>
#include "factor_poly.hpp"
#include "algorithms.hpp"

using namespace std;

unsigned int resize_stats=0;

int main(unsigned int argc, char *argv[]) {
  factor_poly fp1;

  fp1 += xy_term(0,2,3);
  fp1 += xy_term(0,2,2);

  cout << fp1.str() << endl;

  factor_poly fp2(xy_term(0,1,4));
  fp1 += fp2;

  cout << fp1.str() << endl;

  fp1 *= xy_term(0,1,6);

  cout << fp1.str() << endl;

  return 0;
}
