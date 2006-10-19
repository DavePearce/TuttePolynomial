#include "core/tutte.h"
#include <memory.h>

/**************************************************/
/*                                                */
/*                 start of  sixOrFewer           */
/*                                                */

/*

Precondition: g is the location of a simplegraph with six or fewer 
              vertices arrays tutteMat and tutteMatX hold the 
              current status of the computation

Postcondition: the arrays are augmented by the tutte poly
               og the graph at g

*/


void
sixOrFewer (struct Graph *g,TUTTE  tutteMat,TUTTEO tutteMatX)

{/* 1 */
int isTreeOrNot,   /* returned value of detectAndComputeTrees      */ 
    i,             /* for parameter                                */
    j,    
    noVert,        /* number vertices in graph--switch parameter   */
    noEdge;        /* number edges in graph--switch parameter      */
TUTTE tutteMat1;
TUTTEO tutteMat1X;

//printf("sixOrFewer\n");


for( i = ZERO; i < TUTTEROWS; ++i )
for (j = ZERO; j < TUTTECOLS; ++j )
  {/* 2 */
     tutteMat1[i][j] = ZERO;
     tutteMat1X[i][j] = ZERO;
  }/* 2*/

noVert = numVertices(g);  
noEdge = ( numEdges(g) - numVertices(g) + ONE ) / TWO;

isTreeOrNot = detectAndComputeTrees(
                     g,
                     tutteMat,
                     tutteMatX
                    );
if( !isTreeOrNot )
  {  /* 3 */ 
     if( ( noVert == ZERO ) || ( noVert == ONE ) )
       {/* 4 */
          printf("SURPRISE sixorfewer\n");
          printGraph(g); 
       } /* 4 */ 
       
     if( noVert == TWO )
       { /* 5 */
          detectAndComputeTrees(
                 g,
                 tutteMat,
                 tutteMatX
                );
       } /* 5 */
        
     if( noVert == THREE )
       {       /* 6 */ 
          tutteMat1[ZERO][ONE] = ONE;
          tutteMat1[ZERO][TWO] = ONE;
          tutteMat1[ONE][ZERO] = ONE;
       }/* 6*/


     if( noVert == FOUR )
       {     /* 7 */      
          if( noEdge == FOUR )
            {/* 8 */
               tutteMat1[ZERO][ONE] = ONE;
               tutteMat1[ZERO][TWO] = ONE;
               tutteMat1[ZERO][THREE] = ONE;
               tutteMat1[ONE][ZERO] = ONE;
            }/* 8 */

          if( noEdge == FIVE )
            {      /* 9 */  
               tutteMat1[ZERO][ONE] = ONE;
               tutteMat1[ZERO][TWO] = TWO;
               tutteMat1[ZERO][THREE] = ONE;
               tutteMat1[ONE][ZERO] = ONE;
               tutteMat1[TWO][ZERO] = ONE;
               tutteMat1[ONE][ONE] = TWO;
            }/* 9 */

          if( noEdge == SIX )
            {      /*10*/       
               tutteMat1[ZERO][ONE] = TWO;
               tutteMat1[ZERO][TWO] = THREE;
               tutteMat1[ZERO][THREE] = ONE;
               tutteMat1[ONE][ZERO] = TWO;
               tutteMat1[TWO][ZERO] = THREE;
               tutteMat1[THREE][ZERO] = ONE;
               tutteMat1[ONE][ONE] = FOUR;
            }/* 10 */
       }/* 7*/   



     if( noVert == FIVE )
       { /* 11 */ //printf("X\n"); 
          identifyFives(
                        g, 
                        tutteMat1,
                        tutteMat1X
                       );
       }/* 11 */

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


