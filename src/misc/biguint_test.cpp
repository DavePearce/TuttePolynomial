#include <iostream>
#include "biguint.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  unsigned long long v(UINT_MAX);
  v = v + 2;
  biguint v1(v);
  cout << v1.c_ulonglong() << endl;
}
