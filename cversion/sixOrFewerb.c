#include "tutte.h"
#include <memory.h>

/**************************************************/
/*                                                */
/*                 start of  sixOrFewerb          */
/*                                                */

/*

Precondition: g is the location of a simplegraph with six or fewer 
              vertices arrays tutteMat and tutteMatX hold the 
              current status of the computation

Postcondition: the arrays are augmented by the tutte poly
               og the graph at g

*/


void
sixOrFewerb (
             int noVert,
             struct graph *g,
             TUTTE  tutteMat,
             TUTTEO tutteMatX
            )

{/* 1 */
int isTreeOrNot,   /* returned value of detectAndComputeTrees      */ 
    i,             /* for parameter                                */
    j,    
    noVert,        /* number vertices in graph--switch parameter   */
    noEdge;        /* number edges in graph--switch parameter      */
TUTTE tutteMat1;
TUTTEO tutteMat1X;

//printf("sixOrFewerb\n");


witch(noVert)
{
case 5:
{
          identifyFives(
                        g, 
                        tutteMat1,
                        tutteMat1X
                       );

     if( noVert == SIX ) 
       {/* 12 *///printf("Y\n");
          identifySixes(
                        g, 
                        tutteMat1,
                        tutteMat1X
                       );
       } /* 12 */ 
     /*                                           */
     /* incorporate tutte poly found with other   */
     /* factors                                   */
     /*                                           */
     multiplyByFactors(
                       g,
                       tutteMat,
                       tutteMatX,
                       tutteMat1,
                       tutteMat1X,
                       degOneDels(g), 
                       triangleDels(g) 
                      );
  
  } /* 3 */

} /*  1 */ /* the end of sixOrFewer  */


/*                                                */
/*                 end of  sixOrFewer             */
/*                                                */
/**************************************************/


