#include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



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

int
gotMultiple (
             int C
            )
{

int vertLoc,      /* location of vertex                                  */ 
    edgFIXED,     /* location of edge                                    */
    NoMultEdges,  /* counter of multiple edges encountered               */
    nameToMatch,  /* name of end edge to match to indicate multiple edge */
    edgeCompare;

//printf("gotMultiple\n");

/* number found so far */
NoMultEdges =  ZERO;

for(vertLoc = firstVertex(&g[C]); 
          vertLoc != LIST_END; 
                vertLoc = nextVertex(&g[C], vertLoc))
  {
     for(edgFIXED = firstEdge(&g[C], vertLoc); 
                  edgFIXED != LIST_END;
                           edgFIXED = nextEdge(&g[C], edgFIXED)) 
       {
          nameToMatch= nameOtherEnd(&g[C], edgFIXED); 
          for(edgeCompare = nextEdge(&g[C], edgFIXED); 
                          edgeCompare != LIST_END;
                                      edgeCompare = nextEdge(&g[C], edgeCompare))
            { 
               if( nameOtherEnd(&g[C], edgeCompare) == nameToMatch )     
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

if( NoMultEdges > ZERO )
  {
     return( ONE );
  }
else
  {
     return( ZERO );
  }             

} /* end gotMultiple */


/*                                            */
/*             end of gotMultiple             */
/*                                            */
/**********************************************/




