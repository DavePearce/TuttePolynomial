bin_PROGRAMS = tutte

AM_CPPFLAGS = -I$(top_srcdir)/nauty

tutte_SOURCES = tutte.cpp graph/algorithms.cpp graph/hash.c misc/biguint.cpp misc/bistream.cpp misc/bstreambuf.cpp 
tutte_LDADD = -lgmpxx -lgmp ../nauty/libnauty.a
