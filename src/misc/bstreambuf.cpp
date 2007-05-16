#include "bstreambuf.hpp"

bstreambuf& operator>>(bstreambuf &out, char &c) { out.read(c); return out; }
bstreambuf& operator>>(bstreambuf &out, unsigned char &c) { out.read(c); return out; }
bstreambuf& operator>>(bstreambuf &out, short &c) { out.read(c); return out; }
bstreambuf& operator>>(bstreambuf &out, unsigned short &c) { out.read(c); return out; }
bstreambuf& operator>>(bstreambuf &out, int &c) { out.read(c); return out; }
bstreambuf& operator>>(bstreambuf &out, unsigned int &c) { out.read(c); return out; }
bstreambuf& operator>>(bstreambuf &out, long &c) { out.read(c); return out; }
bstreambuf& operator>>(bstreambuf &out, unsigned long &c) { out.read(c); return out; }


bstreambuf& operator<<(bstreambuf &out, char val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, unsigned char val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, short val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, unsigned short val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, int val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, unsigned int val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, long val) { out.write(val); return out; }
bstreambuf& operator<<(bstreambuf &out, unsigned long val) { out.write(val); return out; }
