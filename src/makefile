ROOTDIR=..
include ${ROOTDIR}/makefile.config

SUBDIRS=graph cache misc poly

SRCS= tutte.cpp graph/algorithms.cpp graph/hash.c misc/biguint.cpp misc/bstreambuf.cpp misc/bistream.cpp

LDFLAGS += -L../nauty
LIBS = -lnauty -lgmpxx -lgmp

TARGET=tutte

include ${ROOTDIR}/makefile.std






