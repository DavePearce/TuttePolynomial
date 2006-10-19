#include "tutte.h"
#include <memory.h>
/**********************************************/
/*                                            */
/*           start of sevenpart3              */
/*                                            */
 


/* Procedures Called:

*/
/* 
Precondition: g is a simple graph with seven vertices and 14 or 15 edges
              tutteMat and tutteMatX are arrays with values
              for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte
               poly of this graph
*/

void
sevenpart3dr(g,tutteMat,tutteMatX)
struct graph *g;
TUTTE tutteMat;
TUTTEO tutteMatX;

{
int firstvertex,    /* location of first vertex on the vertex list     */
    i,              /* variables used to find the degree sequence      */
    deg[VERTEXSIZE],
    degseq,
    x,
    d21,            /* location on vertex list of vertices of degree 2  */
    d22,
    d31,            /* location on vertex list of vertices of degree 3  */
    d31a,  
    d31b,
    d32, 
    d33,
    d41,            /* location on vertex list of vertex of degree 5    */
    d42,
    d43,
    d41a,
    d41b,
    no51,           /* number of vertices of degree 5 adjacent to 
    			  vertices of degree 3                           */  
    no52,

    d51,            /* location on vertex list of vertex of degree 5     */
    d52,

    vt,             /* location on vertex list                           */
    ne1,            /* location on edge list                             */

    sum,            /* accumulators for degress of sets of vertices      */
    sum1,
    sum2,
    sum3,


    no3,          /* number of common adjacencies of two degree
    			 3 vertices                                    */

    
    a1,           /* number of degree 4 vertices adjacent to a 
    			degree 3 vertex                                 */
    c1,
    b1,           /* number of degree 5 vertices adjacent to a 
    			degree 3 vertex                                 */
    d1,
    e1;           /* code to recognize combinations of values 
    			 of a1, b1, c1, and d1                          */

 
//printf("sevenpart3dr\n");
/* calculate degree sequence */
firstvertex = (*g).vrtx[ZERO].nvert;
vt = firstvertex;
for ( i = ZERO; i <= TEN; ++i ) 
    deg[i]=ZERO;

while ( vt != LIST_END ) 
  { /* 1 */
     ++deg[(*g).vrtx[vt].degree];
     vt=(*g).vrtx[vt].nvert;
  } /* 1 */
degseq = deg[TWO] + 10 * deg[THREE] + 100 * deg[FOUR] + 1000 * deg[FIVE] + 10000 * deg[SIX];

switch( degseq )
  {  /* 1 */
     case 30040:
     case 21130:
     case 13030:
       {
          sevenpart3dra(
                        g,
                        degseq,
                        tutteMat,
                        tutteMatX
                       );
          break;
       }

     case 20320:
     case 12220:
     case 4120:
       {
          sevenpart3drb(
                        g,
                        degseq,
                        tutteMat,
                        tutteMatX
                       );
          break;
       }

     case 11410:
     case 2500:
     case 10600:
       {
          sevenpart3drc(
                        g,
                        degseq,
                        tutteMat,
                        tutteMatX
                       );
          break;
       }

     case 3310:
     case 1510:
     case 3130:
       {
          sevenpart3drd(
                        g,
                        degseq,
                        tutteMat,
                        tutteMatX
                       );
          break;
       }

     case 11230:
     case 12040:
     case 10420:
       {
          sevenpart3dre(
                        g,
                        degseq,
                        tutteMat,
                        tutteMatX
                       );
          break;
       }

     case 700:
     case 20140:
     case 2320:
       {
          sevenpart3drf(
                        g,
                        degseq,
                        tutteMat,
                        tutteMatX
                       );
          break;
       }
     default:
       {
          printf("sevenpart3dr\n");
          break;
       }

  } /*  end switch on degseq */

}  /* end sevenpart3dr */

/*                                            */
/*           end of sevenpart3dr              */
/*                                            */
/**********************************************/




