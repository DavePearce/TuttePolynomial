#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "biguint.hpp"
#include "computation.hpp"
#include "factor_poly.hpp"
#include "symbolic_poly.hpp"

using namespace std;

typedef factor_poly<biguint> poly_t;
typedef symbolic_poly spoly_t;

// ------------------------------------------------------------------
// Determine symbolic polynomial for a tree
// ------------------------------------------------------------------
spoly_t tutte_tree_poly(unsigned char *nauty_graph) {
  spoly_t poly;
  unsigned int N(nauty_graph_numverts(nauty_graph));
  
  for(unsigned int i=0;i!=N;++i) {
    for(unsigned int j=i+1;j<N;++j) {
      if(nauty_graph_is_edge(nauty_graph,i,j)) {
	spoly_t tmp(spoly_t::X(1));
	tmp += spoly_t::Y(1,make_pair(i,j));
	poly *= tmp; 
      }
    }
  }

  return poly;
}

// ------------------------------------------------------------------
// Tutte Polynomial Evaluation
// ------------------------------------------------------------------
poly_t tutte(computation &comp, vector<unsigned int> const &order) { 
  unsigned int N(comp.size());
  vector<spoly_t> polys(N);

  for(int i=0;i!=N;++i) {
    unsigned int n = order[i];
    tree_node *tnode = comp.get(order[i]);
    
    switch(TREE_TYPE(tnode)) {
    case TREE_CONSTANT:
      {	
	polys[n] = tutte_tree_poly(comp.graph_ptr(n));
	break;
      }   
    case TREE_SUM:
      {
	unsigned int lhs = TREE_CHILD(tnode,0);
	unsigned int rhs = TREE_CHILD(tnode,1);
	// we have to apply substitution to lhs and rhs here.
	polys[n] += polys[lhs];
	polys[n] += polys[rhs];
	break;
      }
    case TREE_PRODUCT:
      {
	//	cout << "P[" << n << "] = ";
	for(unsigned int j=0;j!=TREE_NCHILDREN(tnode);++j) {
	  unsigned int child = TREE_CHILD(tnode,j);
	  if(j == 0) {
	    polys[n] = polys[child];
	  } else {
	    //	    cout << "* ";
	    polys[n] *= polys[child];
	  }
	  //	  cout << "P[" << child << "] ";
	}
	//	cout << "= " << polys[n].str()  << endl;
	//	cout << "G[" << n << "] = " << nauty_graph_str(comp.graph_ptr(n)) << endl;
	break;
      }
    }
  }

  // Now, we need to build the real polynomial.  I'm going to assume
  // the input graph has no multi-edges for now.

  poly_t poly;

  

  return polys[0];
}
