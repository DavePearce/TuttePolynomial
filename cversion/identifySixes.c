#include "tutte.h"


/*********************************************/
/*                                           */
/*             start of identifySixes        */
/*                                           */

/* 

Precondition: A graph with six vertices and the matrices holding the current status of

                 the Tutte poly of the graph 

Postcondition: The graph has contributed its tutte polynomial to the arrays 
               

STRATEGY: separate the simple six vertices into two sets depending on the
          number of edges in the graph

 */
 
 
void
identifySixes  ( 
                struct graph *g,
                TUTTE tutteMat1,
                TUTTEO tutteMat1X
               )
{
int i,                /* used to compute the degree sequence */
    degseq,
    deg[10],
    vt;

//printf("identifySixes\n");
for(i = ZERO; i<10; i++)
  deg[i] = ZERO;

for(vt=firstVertex(g); vt != LIST_END; vt = nextVertex(g, vt))
{
    ++deg[ (*g).vrtx[vt].degree];
}
degseq = deg[TWO] + 10 * deg[THREE] + 100 * deg[FOUR] + 1000 * deg[FIVE];

switch(degseq)
{
case 6:
case 105:
case 24:
case 204:
case 1014:
case 123:
case 42:
{
identifySixesA1(g, degseq, tutteMat1, tutteMat1X);
}
break;

case 303:
case 2004:
case 1113:
case 222:
case 1032:
case 141:
case 60:
{
identifySixesA2(g, degseq, tutteMat1, tutteMat1X);
}
break;

case 402:
case 1410:
case 2301:
case 2220:
case 3030:
case 3210:
case 2400:
case 4200:
case 6000:
case 1212:
case 2121:
case 2040:
case 1311:
case 501:
{
identifySixesB1(g, degseq,tutteMat1, tutteMat1X);
}
break;

case 2022:
case 1050:
case 1131:
case 321:
case 240:
case 1230:
case 420:
case 600:
{
identifySixesB2(g, degseq, tutteMat1, tutteMat1X);
}
break;

default:
{
printf("identifySixes degseq = %d\n", degseq);
}
break;

} /* end switch on degseq */

} /* end identifySixes */

/*                                           */
/*             end of identifySixes          */
/*                                           */
/*********************************************/



