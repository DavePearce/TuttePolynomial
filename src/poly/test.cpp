#include <iostream>
#include "factor_poly.hpp"

using namespace std;

int main(unsigned int argc, char *argv[]) {
  factor_poly fp1(xy_term(1,1,3));
  factor_poly fp2(xy_term(1,3,4));
  fp1 += fp2;
  
  cout << fp1.str() << endl;

  for(factor_poly::const_iterator i(fp1.begin());
      i!=fp1.end();++i) {
    cout << (*i).second << (*i).first.str() << " + ";
  }

  cout << endl;
  return 0;
}
