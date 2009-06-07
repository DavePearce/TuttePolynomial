// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#ifndef NAUTY_GRAPH_HPP
#define NAUTY_GRAPH_HPP

class nauty_graph {
private:
  unsigned char *buffer;
  unsigned int N;    // number of vertices after contractions.
  unsigned int NN;   // number of vertices ignoring contractions.
  unsigned int E;    // number of edges.
  unsigned int *labs; // labels for indicating vertex colour.
  unsigned int *ptn;  // end points for colour classes.
public:
  nauty_graph(unsigned int n = 0);
  nauty_graph(nauty_graph const &);
  ~nauty_graph();

  int num_vertices() const;
  int num_edges() const;

  bool add_edge(unsigned int from, unsigned int to);
  void remove_edge(unsigned int from, unsigned int to);
  void contract_edge(unsigned int from, unsigned int to);  

  nauty_graph &operator=(nauty_graph const &ng);
  bool operator==(nauty_graph const &ng) const;
};

// ----------------------------------
// METHODS FOR INTERFACING WITH NAUTY
// ----------------------------------

// the following is needed for Nauty and determines
// the maximum graph size
#define MAXN 0
#define NAUTY_HEADER_SIZE 2
#include "nauty.h"

bool compare_graph_keys(unsigned char const *_k1, unsigned char const *_k2);
size_t sizeof_graph_key(unsigned char const *key);
unsigned int hash_graph_key(unsigned char const *key);
size_t graph_size(unsigned char *key);

#endif
