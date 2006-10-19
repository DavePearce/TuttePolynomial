#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*        start of sevenpart2driver           */
/*                                            */

/*
Precondition: g is a simple graph with seven vertices and either 16 or 17 edges
 
             tutteMat and tutteMatX give the current status of
              this computation

Postcondition: tutteMat and tutteMatX augmented by tutte 
               poly of this graph

*/   


void
sevenpart2driver(
                 struct graph *g,
                 TUTTE tutteMat,
                 TUTTEO tutteMatX
                )


{
int firstvertex,   /* location of first vertex on vertex list       */
    vt,            /* location on vertex list */
    i,             /* variables used to find degree sequence        */
    degseq,
    deg[TEN];

printf("sevenpart2driver\n");

/* find degree sequence */

for( i = ZERO; i < SEVEN; ++i )
  deg[i] = ZERO;
for(vt = firstVertex(g); vt != LIST_END; vt = nextVertex(g, vt))
  {
     ++deg[(*g).vrtx[vt].degree];
  } 

degseq = deg[TWO] + 10 * deg[THREE] + 100 * deg[FOUR] + 1000 * deg[FIVE] + 10000 * deg[SIX];


switch( degseq )
  { 
     case 24001:
     case 31210:
     case 15010:
       {
          sevenpart2dra(
                        g,
                        degseq,
                        tutteMat,
                        tutteMatX
                       );
          break;
       }

     case 23110:
     case 30400:
     case 6100:
       {
          sevenpart2drb(
                        g,
                        degseq,
                        tutteMat,
                        tutteMatX
                       );
          break;
       }

     case 22300:
     case 14200:
     case 22201:
       {
          sevenpart2drc(
                        g,
                        degseq,
                        tutteMat,
                        tutteMatX
                       );
          break;
       }

     case 14101:
     case 6001:
     case 14020:
       {
          sevenpart2drd(
                        g,
                        degseq,
                        tutteMat,
                        tutteMatX
                       );
          break;
       }


     case 22120:
     case 5110:
     case 21310:
       {
          sevenpart2dre(
                        g,
                        degseq,
                        tutteMat,
                        tutteMatX
                       );
          break;
       }

     case 30220:
     case 13210:
     case 20500:
       {
          sevenpart2drf(
                        g,
                        degseq,
                        tutteMat,
                        tutteMatX
                       );
          break;
       }

     case 4300:
       {
          sevenpart2drg(
                        g,
                        tutteMat,
                        tutteMatX
                       );
          break;
       }

     case 12400:
       {
          sevenpart2drh(
                        g,
                        tutteMat,
                        tutteMatX
                       );
          break;
       }
     default:
       {
          printf("sevenpart2driver\n");
          break;
       }
    
  } /* end switch for master driver */

}/* end sevenpart2driver */

