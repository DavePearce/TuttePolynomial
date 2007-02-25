#include <iostream>
#include "factor_poly.hpp"

using namespace std;

int main(unsigned int argc, char *argv[]) {
  factor_poly fp1(xy_term(1,1,3));
  factor_poly fp2(xy_term(1,3,4));
  fp1 += fp2;

  cout << fp1.str() << endl;

  return 0;
}
