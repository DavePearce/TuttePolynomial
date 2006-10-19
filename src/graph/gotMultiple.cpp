#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "graph.h"


/**********************************************/
/*                                            */
/*            start of gotMultiple            */
/*                                            */

/*
Precondition: C--index into graph array pointing to a graph

Postcondition: graph unchanged

Return: 1 if a multiple edge is found in g[C]
        0 if no multiple eddge found in g[C]

*/

int gotMultiple (struct Graph *g) {

int vertLoc,      /* location of vertex                                  */ 
    edgFIXED,     /* location of edge                                    */
    NoMultEdges,  /* counter of multiple edges encountered               */
    nameToMatch,  /* name of end edge to match to indicate multiple edge */
    edgeCompare;

//printf("gotMultiple\n");

/* number found so far */
NoMultEdges =  0;

for(vertLoc = firstVertex(g); 
          vertLoc != LIST_END; 
                vertLoc = nextVertex(g, vertLoc))
  {
     for(edgFIXED = firstEdge(g, vertLoc); 
                  edgFIXED != LIST_END;
                           edgFIXED = nextEdge(g, edgFIXED)) 
       {
          nameToMatch= nameOtherEnd(g, edgFIXED); 
          for(edgeCompare = nextEdge(g, edgFIXED); 
                          edgeCompare != LIST_END;
                                      edgeCompare = nextEdge(g, edgeCompare))
            { 
               if( nameOtherEnd(g, edgeCompare) == nameToMatch )     
                 {
                   ++NoMultEdges;
                   break;
                 }
            }    
          if(NoMultEdges)
            break;          
       }
    if(NoMultEdges)
      break;
  }
  
  /* end of vert list */

if( NoMultEdges > 0 )
  {
     return 1;
  }
else
  {
     return 0;
  }             

} /* end gotMultiple */


/*                                            */
/*             end of gotMultiple             */
/*                                            */
/**********************************************/




