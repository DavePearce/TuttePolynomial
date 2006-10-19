#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart4              */
/*                                            */
 
/*

Precondition: g is a simple graph with seven vertices and 13 edges
              tutteMat and tutteMatX are arrays with values
              for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte
               poly of this graph

*/

void
sevenpart4(
           struct graph *g,
           TUTTE tutteMat,
           TUTTEO tutteMatX
          )

{
int firstvertex,     /* location of first vertex on vertex list        */
    i,               /* variables used to compute degree sequence      */
    vt,
    deg[VERTEXSIZE],
    degseq;
//printf("sevenpart4\n");

/* use a coding of the degree sequences to distinguish the cases */
/* first digit number of degree three vertices
  second digit number of degree four vertices
   third digit number of degree five vertices
  fourth digit number of degree six digits */

/* find degree sequence */
//vt = firstVertex(g);
for ( i = ZERO; i <=TEN ;++i ) 
  {
    deg[i] = ZERO;
  }
//while ( vt != LIST_END ) 
for(vt = firstVertex(g); vt != LIST_END; vt = nextVertex(g, vt))
  {
     ++deg[vertDegree(g, vt) /*(*g).vrtx[vt].degree*/];
 //    vt = nextVertex(g, vt);  //(*g).vrtx[vt].nvert;
  }

degseq = deg[TWO] + 10 * deg[THREE] + 100 * deg[FOUR] + 1000 * deg[FIVE] + 10000 * deg[SIX];

switch( degseq )
  {
     case 11050:
       {
          sevenpart41(
                      g,
                      tutteMat,
                      tutteMatX
                     );
       }
     break;
     case 10240:
       {
          sevenpart42(
                      g,
                      tutteMat,
                      tutteMatX
                     );
       }
     break;
     case 2140:
       {
          sevenpart43(
                      g,
                      tutteMat,
                      tutteMatX
                     );
       }
     break;
     case 1330:
       {
          sevenpart44(
                      g,
                      tutteMat,
                      tutteMatX
                     );
       }
     break;
     case 520:
       {
          sevenpart45(
                      g,
                      tutteMat,
                      tutteMatX
                     );
       }
     break;


}




} /* end sevenpart4 */  

/*                                            */
/*           end of sevenpart4                */
/*                                            */
/**********************************************/


