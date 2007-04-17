include ../makefile.config

SUBDIRS=core graph cache misc poly

SRCS= tutte.cpp graph/algorithms.cpp graph/hash.c poly/factor_poly.cpp

LDFLAGS += -L../nauty
# CXXFLAGS += -DNDEBUG
LIBS = -lnauty

TARGET=tutte

include ../makefile.std






