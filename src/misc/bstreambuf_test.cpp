#include "bstreambuf.hpp"
#include "bistream.hpp"

using namespace std;

int main(int argc, char* args[]) {
  bstreambuf x;

  mpz_class v;
  try {
    v = 12345678;
    v = v * v * v;
    cout << "V = " << v << endl;
    
    x << v;

    bistream y(x);
    
    y >> v;
    
    cout << "V = " << v << endl;
  } catch(runtime_error &e) {
    cout << "EXCEPTION CAUGHT!" << endl;
  }
       
  return 0;
}
