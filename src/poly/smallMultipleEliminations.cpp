#include <assert.h>
#include "core/tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


/***********************************************/
/*                                             */
/*                                             */
/*     start  twoMultipleEliminate             */
/*                                             */

/*
Precondition: C--index for graph with two vertices
              startused--stack entry point that 
                indicates no more graphs to reduce
              tutteMat and tutteMatX--current state
                of the computation
Postcondition: C and startused are unchanged
               tutteMat and tuteMatX have been
                 augmented by the tutte poly of g[C]
*/






void
twoMultipleEliminate(int *C, int startused,TUTTE  tutteMat,TUTTEO tutteMatX)
{
int vt,
    ne,
    count12,
    i,
    j;
  /* repeat as long as graph taken from stack has 2 vertices */
  while( ( (*C) != MINUSTHREE ) 
               && ( numVertices(&g[(*C)]) == TWO ) )
  {
     /* determine the number of edges joining the two vertices */
     count12 = ZERO;
     for(ne = firstEdge(&g[(*C)], firstVertex(&g[*C]));
           ne != LIST_END; ne = nextEdge(&g[*C], ne))
       {
          ++count12;
       }
 
     /* initialize array for temp computation */
     for ( i = ZERO; i < TUTTEROWS; ++i )
     for ( j = ZERO; j < TUTTECOLS; ++j )
       {
          tuttey[i][j] = ZERO;
          tuttez[i][j] = ZERO;
       }
     tuttey[ZERO][ONE] = ONE;
     for( i = ONE; i <= count12 - ONE; ++i )
       tuttey[i][ZERO] = ONE;

     /* augment tuteMat and tutteMatX */
     multiplyByFactors(
                       &g[*C],
                       tutteMat,
                       tutteMatX,
                       tuttey,
                       tuttez,
                       degOneDels(&g[*C]),
                       triangleDels(&g[*C])
                      );

    /* push and pop on the graph index stack */ 
    *C=pushAndPopGraphIndex(*C, startused);
  }  


} /* end two multiple graph elimination */

/*                                             */
/*                                             */
/*       end  twoMultipleEliminate             */
/*                                             */
/***********************************************/
/*                                             */
/*        start popGraphIndex                  */
/*                                             */
/*                                             */
/*        start threeMultipleEliminate         */
/*                                             */
/*                                             */
/*
Precondition: C--index for graph with three vertices
              startused--stack entry point that 
                indicates no more graphs to reduce
              tutteMat and tutteMatX--current state
                of the computation
Postcondition: C and startused are unchanged
               tutteMat and tuteMatX have been
                 augmented by the tutte poly of g[C]
*/

void
threeMultipleEliminate(int *C, int startused, TUTTE tutteMat, TUTTEO tutteMatX)
{
int findthree,        /* signal for successful compuation  */
    i,                /* for parameters                    */
    j;

/* repeat as long as graph taken from stack has 3 vertices */
findthree = ONE;
while( ( *C != MINUSTHREE ) 
             &&  ( findthree == ONE ) 
                 && ( numVertices(&g[*C]) == THREE ) )
  {// looking for multigraphs with three vertices
     /* set switch to repeat small graph reduction */

     findthree = ZERO; // don't find
 
     /* initialize array for temp computation */
     for( i = ZERO; i < TUTTEROWS; ++i )
     for( j = ZERO; j < TUTTECOLS; ++j )
       {
          tuttey[i][j] = ZERO;
          tuttez[i][j] = ZERO;
       }

     /* compute tutte poly of g[*C] */ 
     findthree = evaluateThreesDriver(
                                      *C,
                                      tuttey,
                                      tuttez
                                     );
     assert(findthree == ONE );
     if( findthree == ONE )
       { 
          /* put answer in final answer */
          multiplyByFactors(
                            &g[*C],
                            tutteMat,
                            tutteMatX,
                            tuttey,
                            tuttez,
                            degOneDels(&g[*C]),
                            triangleDels(&g[*C])
                           );

          /* push and pop on the graph index stack */ 
          *C = pushAndPopGraphIndex(*C, startused);
       }
  }

} /* end three multiple edge graphs */



/*                                             */
/*                                             */
/*        end threeMultipleEliminate           */
/*                                             */
/***********************************************/
/*                                             */
/*        start fourMultipleEliminate          */
/*                                             */
/*                                             */
/*
Precondition: C--index for graph with four vertices
              startused--stack entry point that 
                indicates no more graphs to reduce
              tutteMat and tutteMatX--current state
                of the computation
Postcondition: C and startused are unchanged
               tutteMat and tuteMatX have been
                 augmented by the tutte poly of g[C]
*/

void
fourMultipleEliminate(int *C, int startused,TUTTE tutteMat, TUTTEO tutteMatX)
{
int findfour,
    i,
    j;
/* repeat as long as graph taken from stack has 4 vertices */
findfour = ONE;
while( ( *C != MINUSTHREE ) && ( numVertices(&g[*C]) == FOUR ) && ( findfour ) )
  {  // looking for multigraphs with four vertices
     findfour = ZERO;
 
     /* initialize array for temp computation */
     for( i = ZERO; i < TUTTEROWS; ++i )
     for( j = ZERO; j < TUTTECOLS; ++j )
       {
          tuttey[i][j] = ZERO;
          tuttez[i][j] = ZERO;
       }

     /* compute tutte poly of g[*C] */ 
     findfour = evaluateFours(
                              *C,
                              tuttey,
                              tuttez
                             );
     if( findfour == ONE )
       {
          /* put answer in final answer */
          multiplyByFactors(
                            &g[*C],
                            tutteMat,
                            tutteMatX,
                            tuttey,
                            tuttez,
                            degOneDels(&g[*C]),  //g[C].minusone,
                            triangleDels(&g[*C])  // g[C].minustwo
                           );

          /* push and pop on the graph index stack */ 
          *C=pushAndPopGraphIndex(*C, startused);
       }
  }

}/* end eliminate fours with multiple edges */

/*                                             */
/*                                             */
/*        end fourEliminateMultiple            */
/*                                             */
/***********************************************/
/*                                             */
/*        start findMultipleEliminate          */
/*                                             */
/*                                             */
/*
Precondition: C--index for graph with five vertices
              startused--stack entry point that 
                indicates no more graphs to reduce
              tutteMat and tutteMatX--current state
                of the computation
Postcondition: C and startused are unchanged
               tutteMat and tuteMatX have been
                 augmented by the tutte poly of g[C]
*/

void
fiveMultipleEliminate(int *C,int startused,TUTTE tutteMat,TUTTEO tutteMatX)
{
int findfive,
    i,
    j;

/* conditions are really for the repetition as they will
   be satisfied on entry or the control would not have
   gotten here
*/
/* repeat as long as graph taken from stack has 5 vertices */
findfive = ONE;
if( ( *C != MINUSTHREE ) && ( numVertices(&g[*C]) == FIVE ) && ( findfive ) )
  {// looking for multigraphs with five vertices
     findfive = ZERO;
 
     /* initialize array for temp computation */
     for( i = ZERO; i < TUTTEROWS; ++i )
     for( j = ZERO; j < TUTTECOLS; ++j )
       {
          tuttey[i][j] = ZERO;
          tuttez[i][j] = ZERO;
       }

     /* compute tutte poly of g[*C] */ 
     findfive = evaluateFivesA(
                               *C,
                               tuttey,
                               tuttez
                              );
     if( findfive == ONE )
       {
          /* put answer in final answer */
          multiplyByFactors(
                            &g[*C],
                            tutteMat,
                            tutteMatX,
                            tuttey,
                            tuttez,
                            degOneDels(&g[*C]),  //g[C].minusone,
                            triangleDels(&g[*C]) //g[C].minustwo
                           );
       

          /* push and pop on the graph index stack */ 
         *C=pushAndPopGraphIndex(*C, startused);
      }
  } /* end evaluating fives */

} /* end of eliminateing 5 vertex multigraphs */

/*                                                       */
/*                                                       */
/*       end of fiveEliminateMultiple                    */
/*                                                       */
/*********************************************************/                                                               



/***********************************************/
/*                                             */
/*     start simpleSmallGraphElimination       */
/*                                             */
/*                                             */     
/*
Precondition: C--index for a simple graph with 
                 no more than 7 vertices
              startused--stack entry point that 
                indicates no more graphs to reduce
              tutteMat and tutteMatX--current state
                of the computation
Postcondition: C and startused are unchanged
               tutteMat and tuteMatX have been
                 augmented by the tutte poly of g[C]
*/
int
simpleSmallGraphElimination(int *C,int  startused, TUTTE tutteMat, TUTTEO tutteMatX)
{
/* replaced if with while-need to monitor and test */

/* repeat as long as next graph off stack has fewer
   than eight vertices and no multiple edges        */
while( ( *C != MINUSTHREE )
              && !( gotMultiple(&g[*C]) )
                 && ( numVertices(&g[*C]) <= SEVEN ) )
        { // looking for small simple graphs
/*                                    */
/* SEE IF THERE ARE ANY TRIANGLES     */
/*                                    */

         /* eliminate ay degree one vertex */
           findDegOne(&g[*C]);
         /* eliminate a triangle, if one found */
           findAndEliminateTriangle(*C);
         /* eliminating a degree 2 vertex can create
             a degree one vertex in the resulting graph
             --check it out                            */         
          findDegOne(&g[*C]);
/*                                          */
/*         SIMPLE GRAPHS WITH |V| <= 7      */
/*                                          */
          if( ( numVertices(&g[*C]) == SEVEN ) 
                  && ( numEdges(&g[*C]) > TWENTY ) 
                     && ( numEdges(&g[*C]) < 38 ) )
             {
                /* special reduction of degree 2 vertex in
                   graph with 7 vertices to eliminate a large
                   number of graphs from being indentified
                   separately                                */
                preSevenFindDeg2(
                                 &g[*C],
                                 tutteMat,
                                 tutteMatX
                                );
             }

         /* now vertex 7 graph has min degree 3 */ 
         if( numVertices(&g[*C]) == SEVEN )
             {
                sevensDriver(
                             &g[*C],
                             tutteMat,
                             tutteMatX
                            );
             }
           else
             /* just simple graphs with fewer than 7 vertices get here */
             if( numVertices(&g[*C]) <= SIX )
               {
                  sixOrFewer(
                             &g[*C],
                             tutteMat,
                             tutteMatX
                            );
               }
/*                                       */
/*   GET NEW GRAPH OFF STACK             */
/*                                       */
            *C=pushAndPopGraphIndex(*C, startused);
         }

} /* end elimination of simple graphs with |V| < 8 */



/*                                             */
/*                                             */
/*      end simpleSmallGraphElimination        */
/*                                             */
/***********************************************/




