// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

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
bistream& operator>>(bistream &out, mpz_class &c) { out.read(c); return out; }
