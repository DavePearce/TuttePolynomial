#include <assert.h>
#include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/***************************************************************************/
/*                                                                         */
/*                         start of deleteContract                         */
/*                                                                         */
/*

Precondition: C--integer value that is an index for a graph array entry
              tutteMat--array with low order digits of current
                        form of tutte poly
              tutteMatX--array with high order digits of current 
                         form of tutte poly

Postcondition: graph at C contributes its tutte poly to the final version


*/

void 
multEdgeSmallGraphElimination(
               int *C,
               int startused,  
               TUTTE tutteMat,
               TUTTEO tutteMatX
              )
{


/*                               */
/*  all graphs with 5 or fewer   */
/*  vertices are identifed and   */
/* evaluated by knowing edge     */
/* multiplicities                */
/*                               */
while(*C != LOCAL_STACK_END && numVertices(&g[*C]) <= FIVE )
  {
    switch(numVertices(&g[*C]))
      {

        /*                                      */
        /*     MULTIGRAPH WITH |V| = 2          */
        /*                                      */ 
        case TWO:
          {        
             twoMultipleEliminate(C, startused, tutteMat, tutteMatX);
          }
        break;
        /*                                      */
        /*      MULTIGRAPH WITH |V| = 3         */
        /*                                      */ 
        case THREE:
          {
             threeMultipleEliminate(C,startused,tutteMat,tutteMatX);
          }
        break;
        /*                                      */
        /*     MULTIGRAPH WITH |V| = 4          */
        /*                                      */ 
        case FOUR:
          { 
             fourMultipleEliminate(C,startused,tutteMat,tutteMatX);
          }
        break;
        /*                                      */
        /* MULTIGRAPH WITH |V| = 5              */
        /*                                      */ 
        case FIVE:
          {
             fiveMultipleEliminate(C, startused,tutteMat,tutteMatX);
          }
        break;
     } /* end switch for small multiple */
  
  } /* end while for small */
}

/*                                            */
/*   end of multEdgeSDmallGraphElimination    */
/*                                            */
/**********************************************/




