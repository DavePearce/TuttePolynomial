

#include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



/**********************************************************/
/*                                                        */
/*           start of detectAndDeleteLoop                 */
/*                                                        */

/* PreCondition: A graph g that may or may not have a loop
   Postcondition: The graph has had any loop detected removed
                  and recorded by incrementing (*g).yPower
*/

/* the code has to concern itself with whether the two ends of 
   the loop are consecutive in the edge list.  if the two ends 
   are consecutive the deletion process has to be modified so 
   that both ends are deleted and the adjacency list does not 
   end up with one end of the edge as would happen in the 
   normal deletion code */ 


void
detectAndDeleteLoop(
                    struct graph *g
                   )
{/* 1*/
int ne,                   /* edge locations                    */
    nne,
    vt,                   /* vertex location                   */
    edgeBack1,            /* neighbors for edges being deleted */
    edgeFront1,
    edgeBack2,
    edgeFront2,
    vertBack,             /* neighbors for vertex being deleted */
    vertFront;

//printf("detectAndDeleteLoop\n");
for(vt = firstVertex(g); vt != LIST_END; vt = nextVertex(g, vt))
  {/* 2 */
     for(ne = firstEdge(g, vt); ne != LIST_END; ne = nextEdge(g, ne))
       {/* 3 */
          if( (*g).edg[ne].ename == (*g).vrtx[vt].vname )
            {
               nne = otherEndEntry(g, ne);  
               
/* the two ends of the loop are neighbors on the adjacency list */
               if( ( nextEdge(g, ne) == nne ) 
                     && ( nextEdge(g, nne) != ne ) ) 
                 {    

/* link around edge pair */                    
                    edgeBack1  = prevEdge(g, ne); 
                    edgeFront2  = nextEdge(g, nne);  
                    setNextEdge(g, edgeBack1, edgeFront2); 
                    if( edgeFront2 != LIST_END )
                      setPrevEdge(g, edgeFront2, edgeBack1);  

/* increment loop counter and graph values */
                    incrYPower(g, ONE);
                    incrVertDegree(g, vt, MINUSTWO);  
                    incrNoEdges(g, MINUSTWO);  

/* link around vertex that is now of degree 0 */
                    if( ( vertDegree(g, vt)  == ZERO ) 
                            && ( numVertices(g))  > ONE ) 
                      {

/* usual link around entry on linked list */
                         vertBack = prevVert(g, vt);  
                         vertFront = nextVertex(g, vt);  
                         setNextVertex(g, vertBack, vertFront);  
                         if( vertFront != LIST_END )
                           setPrevVert(g, vertFront, vertBack);  
                         incrNoVertices(g, MINUSONE);  
                         incrNoEdges(g, MINUSONE);  

                      }
                    else
                      if( ( vertDegree(g, vt) == ZERO ) && ( numVertices(g) == ONE ) )
                        {

/* DISASTER CONDITION-probably bad data */
                          setNoEdges(g, ZERO);  
                          printf("DID THIS HAPPEN?? LOOPY");
                          return;
                        } 

/* set location on edge list before first deleted edge end */
                      ne = edgeBack1;
                 }
                 else

/* the two ends of the loop are not neighbors on the edge list
   so delete works in the noraml fashion                       */
                   if( ( nextEdge(g, ne) != nne ) 
                          && ( nextEdge(g, nne) != ne ) )
                     {

/* link around each edge  */                    
                        edgeBack1 = prevEdge(g, ne); 
                        edgeFront1 = nextEdge(g, ne);  
                        setNextEdge(g, edgeBack1, edgeFront1);  
                        /* should not happen as other edge end yet to come */
                        if( edgeFront1 != LIST_END )
                          setPrevEdge(g, edgeFront1, edgeBack1); 
                        edgeBack2 = prevEdge(g, nne);  
                        edgeFront2 = nextEdge(g, nne);  
                        setNextEdge(g, edgeBack2, edgeFront2); 
/* could well be the end of the list */                        
                        if( edgeFront2 != LIST_END )
                          setPrevEdge(g, edgeFront2, edgeBack2);  
                        incrYPower(g, ONE);
                        incrVertDegree(g, vt, MINUSTWO); 
                        incrNoEdges(g, MINUSTWO); 
                        /* since neither is directly in front of the other
                           there must be at least one more edge on the list 
                           so the vertex vt does not have to be removed */

/* set location on edge list before first deleted edge end */
                        ne = edgeBack1;         
                     }
            }

       } /* end for loop for vt's edge list */
  
  }  /* end for loop for vertex list */

return;

} /* end detectAndDeleteLoop */


/*                                                        */
/*          end of detectAndDeleteLoop                    */
/*                                                        */
/**********************************************************/
