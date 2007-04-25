#include <iostream>
#include "factor_poly.hpp"
#include "../misc/biguint.hpp"
#include "algorithms.hpp"

using namespace std;

unsigned int resize_stats=0;

int main(unsigned int argc, char *argv[]) {
  factor_poly<unsigned int> fp1(xy_term(1,1,1));

  fp1 += xy_term(1,1,2);
  fp1 += xy_term(2,1,1);

  cout << fp1.str() << endl;
}
