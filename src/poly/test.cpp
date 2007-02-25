#include <iostream>
#include "factor_poly.hpp"
#include "algorithms.hpp"

using namespace std;

int main(unsigned int argc, char *argv[]) {
  //  factor_poly fp1(xy_term(1,1,3));
  //  factor_poly fp2(xy_term(1,3,4));
  //  fp1 += fp2;

  factor_poly fp1;

  fp1 += xy_term(0,1,4);

  cout << fp1.str() << endl;

  fp1 *= xy_term(3,1,1);

  cout << fp1.str() << endl;

  for(factor_poly::const_iterator i(fp1.begin());
      i!=fp1.end();++i) {
    cout << (*i).second << (*i).first.str() << " + ";
  }

  cout << endl;

  cout << "NTERMS: " << fp1.nterms() << endl;

  unsigned char *dst = new unsigned char[sizeof_compact_poly(fp1)];
  write_compact_poly(dst,fp1);
  factor_poly fp3 = read_compact_poly<factor_poly>(dst);
  cout << "READ: " << fp3.str() << endl;
  return 0;
}
