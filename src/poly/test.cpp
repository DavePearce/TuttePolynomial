#include <iostream>
#include "factor_poly.hpp"
#include "../misc/biguint.hpp"
#include "algorithms.hpp"

using namespace std;

unsigned int resize_stats=0;

int main(unsigned int argc, char *argv[]) {
  yterms<biguint> fp1(1,2);
  xy_term t1(1,1,3);
  xy_term t2(1,1,1);

  fp1 += t1;
  fp1 += t2;

  xy_term t3(1,1,2);

  fp1 *= t3;;

  cout << fp1.str() << endl;
  
}
