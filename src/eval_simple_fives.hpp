// THIS CODE WAS AUTOMATICALLY GENERATED ON Tue Jan 16 11:32:43 2007


#ifndef EVALUATE_SIMPLE_FIVES_HPP
#define EVALUATE_SIMPLE_FIVES_HPP

#include <stdexcept>

template<class G, class P>
P const &evaluate_simple_fives(G const &graph) {

	// first, define polynomial solutions
	static P poly_0_0_0_2_3 = P(4,0,1) + P(9,0,2) + P(8,0,3) + P(4,0,4) + P(1,0,5) + P(4,1,0)
				 + P(13,1,1) + P(9,1,2) + P(2,1,3) + P(8,2,0) + P(7,2,1) + P(5,3,0)
				 + P(1,4,0);
	static P poly_0_0_1_2_2 = P(2,0,1) + P(4,0,2) + P(3,0,3) + P(1,0,4) + P(2,1,0) + P(7,1,1)
				 + P(5,1,2) + P(1,1,3) + P(5,2,0) + P(5,2,1) + P(4,3,0) + P(1,4,0);
	static P poly_0_0_3_0_2 = P(1,0,1) + P(1,0,2) + P(1,0,3) + P(1,1,0) + P(3,1,1) + P(3,1,2)
				 + P(3,2,0) + P(3,2,1) + P(3,3,0) + P(1,4,0);
	static P poly_0_0_2_2_1 = P(1,0,1) + P(2,0,2) + P(1,0,3) + P(1,1,0) + P(4,1,1) + P(2,1,2)
				 + P(3,2,0) + P(3,2,1) + P(3,3,0) + P(1,4,0);
	static P poly_0_0_3_2_0 = P(1,0,1) + P(1,0,2) + P(1,1,0) + P(2,1,1) + P(2,2,0) + P(1,2,1)
				 + P(2,3,0) + P(1,4,0);
	static P poly_0_0_0_0_5 = P(6,0,1) + P(15,0,2) + P(15,0,3) + P(10,0,4) + P(4,0,5) + P(1,0,6)
				 + P(6,1,0) + P(20,1,1) + P(15,1,2) + P(5,1,3) + P(11,2,0) + P(10,2,1)
				 + P(6,3,0) + P(1,4,0);
	static P poly_0_0_0_4_1 = P(3,0,1) + P(6,0,2) + P(4,0,3) + P(1,0,4) + P(3,1,0) + P(9,1,1)
				 + P(4,1,2) + P(6,2,0) + P(4,2,1) + P(4,3,0) + P(1,4,0);
	static P poly_0_0_4_0_1 = P(1,0,2) + P(2,1,1) + P(1,2,0) + P(2,2,1) + P(2,3,0) + P(1,4,0);
	static P poly_0_0_1_4_0 = P(2,0,1) + P(3,0,2) + P(1,0,3) + P(2,1,0) + P(5,1,1) + P(1,1,2)
				 + P(4,2,0) + P(2,2,1) + P(3,3,0) + P(1,4,0);
	static P poly_0_0_5_0_0 = P(1,0,1) + P(1,1,0) + P(1,2,0) + P(1,3,0) + P(1,4,0);

	// second, compute degree sequence
	unsigned long degseq = 0;
	for(typename G::vertex_iterator i(graph.begin_verts());i!=graph.end_verts();++i) { 
		degseq = degseq + (1U << (graph.num_edges(*i) * 3));
	}

	// third, switch on it!
	switch(degseq) {
		case 13312L:
		 // DEGSEQ: 0(0), 1(0), 2(0), 3(2), 4(3)
		 // GRAPH : 0--1, 0--2, 0--3, 0--4, 1--2, 1--3, 1--4, 2--3, 2--4
		 return poly_0_0_0_2_3;
		case 9280L:
		 // DEGSEQ: 0(0), 1(0), 2(1), 3(2), 4(2)
		 // GRAPH : 0--1, 0--2, 0--3, 0--4, 1--2, 1--3, 1--4, 2--4
		 return poly_0_0_1_2_2;
		case 8384L:
		 // DEGSEQ: 0(0), 1(0), 2(3), 3(0), 4(2)
		 // GRAPH : 0--1, 0--2, 0--3, 0--4, 1--2, 1--3, 1--4
		 return poly_0_0_3_0_2;
		case 5248L:
		 // DEGSEQ: 0(0), 1(0), 2(2), 3(2), 4(1)
		 // GRAPH : 0--1, 0--2, 0--3, 0--4, 1--3, 1--4, 2--4
		 return poly_0_0_2_2_1;
		case 1216L:
		 // DEGSEQ: 0(0), 1(0), 2(3), 3(2), 4(0)
		 // GRAPH : 0--2, 0--3, 0--4, 1--3, 1--4, 2--4
		 return poly_0_0_3_2_0;
		case 20480L:
		 // DEGSEQ: 0(0), 1(0), 2(0), 3(0), 4(5)
		 // GRAPH : 0--1, 0--2, 0--3, 0--4, 1--2, 1--3, 1--4, 2--3, 2--4, 3--4
		 return poly_0_0_0_0_5;
		case 6144L:
		 // DEGSEQ: 0(0), 1(0), 2(0), 3(4), 4(1)
		 // GRAPH : 0--1, 0--2, 0--3, 0--4, 1--3, 1--4, 2--3, 2--4
		 return poly_0_0_0_4_1;
		case 4352L:
		 // DEGSEQ: 0(0), 1(0), 2(4), 3(0), 4(1)
		 // GRAPH : 0--1, 0--2, 0--3, 0--4, 1--4, 2--3
		 return poly_0_0_4_0_1;
		case 2112L:
		 // DEGSEQ: 0(0), 1(0), 2(1), 3(4), 4(0)
		 // GRAPH : 0--2, 0--3, 0--4, 1--2, 1--3, 1--4, 2--4
		 return poly_0_0_1_4_0;
		case 320L:
		 // DEGSEQ: 0(0), 1(0), 2(5), 3(0), 4(0)
		 // GRAPH : 0--3, 0--4, 1--2, 1--4, 2--3
		 return poly_0_0_5_0_0;
		default:
		 throw std::runtime_error("unreachable code reached in evaluate_simple_fives!");
	}
	// SHOULD BE UNREACHABLE!
}

#endif
