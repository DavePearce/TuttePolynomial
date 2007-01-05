#ifndef CONFIG_H
#define CONFIG_H

#include "graph/algorithms.hpp"
#include "graph/adjacency_list.hpp"
#include "graph/spanning_graph.hpp"
#include "graph/tutte_graph.hpp"
#include "poly/simple_poly.hpp"

// set the internal graph representation
typedef tutte_graph<spanning_graph<adjacency_list<> > > Graph;

// set the internal polynomial representation
typedef simple_poly Poly;

// The vertex type dicates the maximum number of
// vertices allowed in a graph.
typedef unsigned short vertex_t;

#endif
