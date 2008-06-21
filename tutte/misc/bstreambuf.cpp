// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#include "bstreambuf.hpp"

bstreambuf& operator<<(bstreambuf &out, char val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, unsigned char val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, short val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, unsigned short val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, int val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, unsigned int val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, long val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, unsigned long val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, long long val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, unsigned long long val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, mpz_class const &val) { out.write(val); return out; }
