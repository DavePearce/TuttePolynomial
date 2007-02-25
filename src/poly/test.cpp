#include <iostream>
#include "factor_poly.hpp"

using namespace std;

int main(unsigned int argc, char *argv[]) {
  yterms y1s(0,5);
  cout << y1s.str() << endl;
  y1s += xy_term(0,1,2);
  y1s *= xy_term(0,1,1);

  cout << y1s.str() << endl;
  return 0;
}
