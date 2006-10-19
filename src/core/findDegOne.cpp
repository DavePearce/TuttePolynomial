#include "tutte.h"

/**********************************************/
/*                                            */
/*           start of findDegOne              */
/*                                            */


/*

Precondition: g is a multigraph 

Postcondition: g is returned with all vertices of degree one removed
               and gminusone appropriately incremented if any degree
               one vertices found
*/

void findDegOne( struct Graph *g)
{ 
int toggle,        /* switch to allow repeating search 
                      until no degree 1 vertex is found  */ 
    vt,            /* locations on vertex and edge lists */
    place;

/* no edges in graph */
if( numVertices(g) <= ONE )
  {
    return;     
  }       


toggle = ONE;
while( toggle ) 
  { /* 1 */
/*                                                           */
/* set toggle so that the loop is repeated until there is a  */
/* pass through the vertices that does not find a vertex     */
/* of degree 1                                               */
/*                                                           */ 
   toggle = ZERO;
     
     /* check degree for each vertex */
    for(vt = firstVertex(g); vt != LIST_END; vt = nextVertex(g, vt))
      { /* 2 */
          
          /* found a vertex of degree 1 */
          if( vertDegree(g, vt)  == ONE ) 
	    { /* 3 */
               place = firstEdge(g, vt); 
               deleteEdge(
                       place,
                       g
                      );
               toggle = ONE; /* set toggle to go thru vertices again */
	       incrDegOneDels(g, ONE);  
            }  /* 3 */  
         

      } /* 2 */ 
  
  /* if a vertex of degree 1 is found, the deletion may
     create another vertex of degree 1. repeat scan until 
     one scan finds no vertex of degree 1
  */
  }/* 1 */ /* end of repeated searches controlled by toggle */

} /* end findDegOne */
  
/*                                            */
/*           end of findDegOne                */
/**********************************************/






