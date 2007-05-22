#include "bistream.hpp"

bistream& operator>>(bistream &out, char &c) { out.read(c); return out; }
bistream& operator>>(bistream &out, unsigned char &c) { out.read(c); return out; }
bistream& operator>>(bistream &out, short &c) { out.read(c); return out; }
bistream& operator>>(bistream &out, unsigned short &c) { out.read(c); return out; }
bistream& operator>>(bistream &out, int &c) { out.read(c); return out; }
bistream& operator>>(bistream &out, unsigned int &c) { out.read(c); return out; }
bistream& operator>>(bistream &out, long &c) { out.read(c); return out; }
bistream& operator>>(bistream &out, unsigned long &c) { out.read(c); return out; }
bistream& operator>>(bistream &out, long long &c) { out.read(c); return out; }
bistream& operator>>(bistream &out, unsigned long long &c) { out.read(c); return out; }

