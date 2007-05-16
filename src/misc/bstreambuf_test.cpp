#include "bstreambuf.hpp"

using namespace std;

int main(int argc, char* args[]) {
  bstreambuf x;
  for(int i=0;i!=2000;++i) {
    x << (unsigned char) i;
    cout << "SIZE = " << x.size() << ", MAX = " << x.max() << endl;
  }

  cout << "========================" << endl;

  for(int i=0;i!=1000;++i) {
    unsigned short c;
    x >> c;
    cout << "SIZE = " << x.size() << ", MAX = " << x.max() << endl;
  }
  
  return 0;
}
