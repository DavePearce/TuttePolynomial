#include <iostream>
#include "factor_poly.hpp"
#include "../misc/biguint.hpp"
#include "algorithms.hpp"

using namespace std;

unsigned int resize_stats=0;

int main(unsigned int argc, char *argv[]) {
  factor_poly<unsigned int> fp1(xy_term(0,1,2));
  bstreambuf bout;
  fp1 += xy_term(0,3,4);
  fp1 += xy_term(2,5,6);
  fp1 *= xy_term(0,2,3);

  cout << fp1.str() << endl;
  bout << fp1;
  cout << "SIZE = " << bout.size() << endl;
  factor_poly<unsigned int> fp2;
  bout >> fp2;
  cout << "GOT: " << fp2.str() << endl;
}
