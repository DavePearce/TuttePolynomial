#include <memory.h>

#include "core/tutte.h"

/**********************************************/
/*                                            */
/*           start of sevenpart1              */
/*                                            */
 
/*

Precondition: g is a simple graph with seven vertices and 18, 19, 20, or 21 edges
              tutteMat and tutteMatX are arrays with values
              for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte
               poly of this graph

*/
 

void
sevenpart1(struct Graph *g, TUTTE tutteMat, TUTTEO tutteMatX)
{
int degseq,          /* variables used to calculate degree sequence */
    i,
    deg[TEN],
    vt;

//printf("sevenpart1\n");

/* calculate the degree sequence */

for ( i = ZERO; i < SEVEN; ++i ) 
   deg[i] = ZERO;

for(vt = firstVertex(g); vt != LIST_END; vt = nextVertex(g, vt))
  {
     ++deg[(*g).vrtx[vt].degree];
  }
degseq = deg[TWO] + 10 * deg[THREE] + 100 * deg[FOUR] + 1000 * deg[FIVE] + 10000 * deg[SIX];

switch( degseq )
  {  
     case 70000:
     case 52000:
     case 34000:
       {
          sevenpart11(g,degseq,tutteMat,tutteMatX);
          break;
       }
     case 42100:
     case 33010:
     case 16000:
       {
          sevenpart12(g,degseq,tutteMat,tutteMatX);
          break;
       }
     case 24100:
     case 32200:
     case 40300:
       {
          sevenpart13(g,degseq,tutteMat,tutteMatX);
          break;
       }
     default:
       {
          printf("sevenpart1\n");
          break;
       }

  } /* 1 end switch on degseq */

}  /* end sevenpart1 */

/*                                            */
/*           end of sevenpart1                */
/*                                            */
/**********************************************/





