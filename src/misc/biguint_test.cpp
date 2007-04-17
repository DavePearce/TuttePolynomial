#include <iostream>
#include "biguint.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  unsigned long long v2(UINT_MAX-2);
  biguint v1(UINT_MAX-2);
  v1 += 4;
  v2 += 4;
  cout << v1.c_ulonglong() << " == " << v2 << endl;
}
