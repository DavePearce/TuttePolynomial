#include "bstreambuf.hpp"
#include "bistream.hpp"

using namespace std;

int main(int argc, char* args[]) {
  bstreambuf x;
  for(int i=0;i!=2000;++i) {
    x << (unsigned char) i;
    cout << "SIZE = " << x.size() << ", MAX = " << x.max() << endl;
  }

  cout << "========================" << endl;

  bistream y(x);

  for(int i=0;i!=1000;++i) {
    unsigned short c;
    y >> c;
    cout << "SIZE = " << y.size() <<  endl;
  }
  
  return 0;
}
