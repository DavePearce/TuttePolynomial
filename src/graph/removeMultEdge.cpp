#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "graph.h"


int deleteMultEdges(struct Graph *g,int *NoMultEdges,int edgFIXED) {
  int nameToMatch,edgeCompare;
  
  *NoMultEdges = 0;
  nameToMatch = (*g).edg[edgFIXED].ename;
  for(edgeCompare=nextEdge(g, edgFIXED); edgeCompare != LIST_END; edgeCompare=nextEdge(g, edgeCompare)) { 
    // ?
    if( (*g).edg[edgeCompare].ename == nameToMatch ) {
      // ?
      if( (*g).edg[edgeCompare].tree == 1 ) {
	(*g).edg[edgFIXED].tree = 1;
	(*g).edg[(*g).edg[edgFIXED].side].tree = 1;
      }
      
      deleteEdge(edgeCompare, g); 
      ++(*NoMultEdges);
    } 
    //  edgeCompare = (*g).edg[edgeCompare].front;
  }            
}



