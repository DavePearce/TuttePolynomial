// THIS CODE WAS AUTOMATICALLY GENERATED ON Tue Jan 16 10:46:14 2007


#ifndef EVALUATE_SIMPLE_FOURS_HPP
#define EVALUATE_SIMPLE_FOURS_HPP

#include <iostream>
#include <stdexcept>
#include "graph/algorithms.hpp"

template<class G, class P>
P const &evaluate_simple_fours(G const &graph) {

	// first, define polynomial solutions
	static P poly_0_0_2_2 = P(1,0,1) + P(1,0,2) + P(1,1,0) + P(2,1,1) + P(2,2,0) + P(1,3,0);
	static P poly_0_0_0_4 = P(2,0,1) + P(3,0,2) + P(1,0,3) + P(2,1,0) + P(4,1,1) + P(3,2,0)
				 + P(1,3,0);
	static P poly_0_0_4_0 = P(1,0,1) + P(1,1,0) + P(1,2,0) + P(1,3,0);

	// second, compute degree sequence
	unsigned long degseq = 0;
	for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) { 
		degseq = degseq + (1U << (graph.num_edges(*i) * 2));
	}

	// third, switch on it!
	switch(degseq) {
		case 160L:
		 // DEGSEQ: 0(0), 1(0), 2(2), 3(2)
		 // GRAPH : 0--1, 0--2, 0--3, 1--2, 1--3
		 return poly_0_0_2_2;
		case 256L:
		 // DEGSEQ: 0(0), 1(0), 2(0), 3(4)
		 // GRAPH : 0--1, 0--2, 0--3, 1--2, 1--3, 2--3
		 return poly_0_0_0_4;
		case 64L:
		 // DEGSEQ: 0(0), 1(0), 2(4), 3(0)
		 // GRAPH : 0--2, 0--3, 1--2, 1--3
		 return poly_0_0_4_0;
		default:
		  std::cout << "*** DEBUG INFO ***" << std::endl;
		  print_graph(std::cout,graph);
		  std::cout << "KEY = " << degseq << std::endl;
		 throw std::runtime_error("unreachable code reached in evaluate_simple_fours!");
	}
	// SHOULD BE UNREACHABLE!
}

#endif
