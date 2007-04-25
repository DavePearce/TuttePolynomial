#include <iostream>
#include "factor_poly.hpp"
#include "../misc/biguint.hpp"
#include "algorithms.hpp"

using namespace std;

unsigned int resize_stats=0;

int main(unsigned int argc, char *argv[]) {
  factor_poly<unsigned int> fp1(xy_term(0,1,1));

  xy_term xys(0,0);
  
  fp1 *= xys;

  cout << fp1.str() << endl;
}
