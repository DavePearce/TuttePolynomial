#include "core/tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <assert.h>
/***************************************************************************/
/*                                                                         */
/*          start of evaluateSmallGraphs                                   */
/*                                                                         */

/*
Precondition: C--index into grah array pointing to a graph with
                 2, 3, 4,or 5 vertices and multiple edges
              arrays tutteMat and tutteMatX contain the current status 
              of the computation

Postcondition: tutteMat and tutteMatX have been augmented by the tutte polky of 
               a multigraph with at most five vertices

Return:  1 if smalll graph processed
         0 if got here and do not have small graph

*/

int 
evaluateSmallGraphs(
                    int C, 
                    TUTTE tutteMat,
                    TUTTEO tutteMatX
                   )


{
TUTTE tutteMat2;
TUTTEO tutteMat2X;
int vt,                /* location of vertex                 */ 
    count12,           /* number edges in lune               */
    i,                 /* for parameter                      */
    j,
    ne,                /* location of edge                   */
    findfive,          /* signal five vertex graph processed */
    findfour,          /* signal four vertex graph processed */ 
    returnsmallremove; /* signal small graph processed       */

//printf("evaluateSmallGraphs C=%d  g[C].v=%d\n",C,g[C].v);
/* set return value */
returnsmallremove= ZERO;

if( ( C != MINUSTHREE ) && ( numVertices(&g[C]) == TWO ) )
  {
     vt = firstVertex(&g[C]);  
     count12 = ZERO;
     for(ne = firstEdge(&g[C], vt); ne != LIST_END; ne = nextEdge(&g[C], ne))
       {
          ++count12;
       }

for( i = ZERO; i < TUTTEROWS; ++i )
for( j = ZERO; j < TUTTECOLS; ++j )
  {
     tutteMat2[i][j] = ZERO;
     tutteMat2X[i][j] = ZERO;
  }
tutteMat2[ZERO][ONE] = ONE;

for( i = ONE; i < count12; ++i ) /* <= same as count12 - 1*/
  tutteMat2[i][ZERO] = ONE;
multiplyByFactors(
                  &g[C],
                  tutteMat,
                  tutteMatX,
                  tutteMat2,
                  tutteMat2X,
                  degOneDels(&g[C]), 
                  triangleDels(&g[C]) 
                 );

returnsmallremove = ONE;;

}

if( ( C != MINUSTHREE ) && ( numVertices(&g[C]) == THREE ) )

  { 
     for( i = ZERO; i < TUTTEROWS; ++i )
     for( j = ZERO; j < TUTTECOLS; ++j )
       {
          tutteMat2[i][j] = ZERO;
          tutteMat2X[i][j] = ZERO;
       }

     evaluateThreesDriver(C,tutteMat2,tutteMat2X);
     multiplyByFactors(
                       &g[C],
                       tutteMat,
                       tutteMatX,
                       tutteMat2,
                       tutteMat2X,
                       degOneDels(&g[C]), 
                       triangleDels(&g[C]) 
                      );

returnsmallremove = ONE;
 //    return( ONE );

}


if( ( C != MINUSTHREE ) && ( numVertices(&g[C]) == FOUR ) )
  { 
     for( i = ZERO; i < TUTTEROWS; ++i )
     for( j = ZERO; j < TUTTECOLS; ++j )
       {
          tutteMat2[i][j] = ZERO;
          tutteMat2X[i][j] = ZERO;
       }

     findfour = evaluateFours(
                              C,
                              tutteMat2,
                              tutteMat2X
                             );
     if( findfour == ONE )
       { assert(findfour ==ONE);
          multiplyByFactors(
                            &g[C],
                            tutteMat,
                            tutteMatX,
                            tutteMat2,
                            tutteMat2X,
                            degOneDels(&g[C]),  
                            triangleDels(&g[C]) 
                           );


         returnsmallremove = ONE; 
       }
}

if( ( C != MINUSTHREE ) && ( numVertices(&g[C]) == FIVE ) )

  {
     for( i = ZERO; i < TUTTEROWS; ++i )
     for( j = ZERO; j < TUTTECOLS; ++j )
       {
          tutteMat2[i][j] = ZERO;
          tutteMat2X[i][j] = ZERO;
       }
     returnsmallremove = ZERO; 
     findfive = evaluateFivesA(
                               C,
                               tutteMat2,
                               tutteMat2X
                              );
    if( findfive == ONE )
       {
          multiplyByFactors(
                            &g[C],
                            tutteMat,
                            tutteMatX,
                            tutteMat2,
                            tutteMat2X,
                            degOneDels(&g[C]),  
                            triangleDels(&g[C]) 
                           );

          returnsmallremove = ONE;
       }
} /* end fives */

return( returnsmallremove );

}

/*                                            */
/*        end of evaluateSmallGraphs          */
/*                                            */
/**********************************************/


