#include "tutte.h"
#include <memory.h>

/**************************************************/
/*                                                */
/*                 start of  sixOrFewera          */
/*                                                */

/*

Precondition: g is the location of a simplegraph with six or fewer 
              vertices arrays tutteMat and tutteMatX hold the 
              current status of the computation

Postcondition: the arrays are augmented by the tutte poly
               og the graph at g

*/


void
sixOrFewera(
            int noVert,
            struct graph *g,
            TUTTE  tutteMat,
            TUTTEO tutteMatX
           )

{/* 1 */
int isTreeOrNot,   /* returned value of detectAndComputeTrees      */ 
    i,             /* for parameter                                */
    j,    
    noEdge;        /* number edges in graph--switch parameter      */
TUTTE tutteMat1;
TUTTEO tutteMat1X;

//printf("sixOrFewera\n");


switch(noVert)
{
case 4:
{
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
}
break;
default:
{
printf("sixOrFewera\n");
}
break;
} /* end switch on noVert */

} /*  1 */ /* the end of sixOrFewera */


/*                                                */
/*                 end of  sixOrFewera             */
/*                                                */
/**************************************************/


