#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "core/tutte.h"


/***************************************************************************/
/*                                                                         */
/*                         start of evaluateFivesA                         */
/*                                                                         */
/* 
Precondition: A graph g[C] with five vertices and possible multiple edges
              the current version of the final answer for this  graph
              is stored in tutteMat2 and tutteMat2X

Postcondition: g[C] has contributed its tutte polynomial to tutteMat2 and tutteaMat2X
 
Return: 1 so that g[C] gets replaced if g[C] is a subgraph of k(5) w/multiple edges
        0 if g[C] is not a five vertex graph 
*/

int 
evaluateFivesA(
               int C, 
               TUTTE tutteMat2,
               TUTTEO tutteMat2X
              )

{
TUTTE tutteMat3;
int x12,       /* incidence information for vertices 1 - 2 */
    x13,
    x14,
    x15,
    x23,
    x24,
    x25,
    x34,
    x35,
    x45,
    noEdges,        /* number of edges in underlying simple graph      */
    findfive,       /* switch to indicate vertex five graph processed  */
    i,              /* for paramter                                    */
    j,
    k,
    v[10],          /* array for identifying house graph               */
    degseq,         /* degseq for switching purposes                   */
    noOfDeg[10],    /* number vertices of different degrees            */
    vertDeg[20],    /* vertex degree array for underlying simple graph */
    vertIndex[10];  /* location of the vertices                        */
struct Graph w;

//printf("evaluateFivesa\n");
/* find the five vertices and find the underlying graph
   that is a subgraph of k(5) as a simple graph
*/ 
vertIndex[1] = firstVertex(&g[C]);  
vertIndex[2] = nextVertex(&g[C], vertIndex[ONE]);  
vertIndex[3] = nextVertex(&g[C], vertIndex[TWO]);  
vertIndex[4] = nextVertex(&g[C], vertIndex[THREE]);  
vertIndex[5] = nextVertex(&g[C], vertIndex[FOUR]);  
x12 = isadj(vertIndex[1],vertIndex[2],&g[C]);
x13 = isadj(vertIndex[1],vertIndex[3],&g[C]);
x14 = isadj(vertIndex[1],vertIndex[4],&g[C]);
x15 = isadj(vertIndex[1],vertIndex[5],&g[C]);
x23 = isadj(vertIndex[2],vertIndex[3],&g[C]);
x24 = isadj(vertIndex[2],vertIndex[4],&g[C]);
x25 = isadj(vertIndex[2],vertIndex[5],&g[C]);
x34 = isadj(vertIndex[3],vertIndex[4],&g[C]);
x35 = isadj(vertIndex[3],vertIndex[5],&g[C]);
x45 = isadj(vertIndex[4],vertIndex[5],&g[C]);

noEdges = x12 + x13 + x14 + x23 + x24 + x34 + x15 + x25 + x35 + x45;

findfive = ZERO;

vertDeg[1] = x12 + x13 + x14 + x15;
vertDeg[2] = x12 + x23 + x24 + x25;
vertDeg[3] = x13 + x23 + x34 + x35;
vertDeg[4] = x14 + x24 + x34 + x45;
vertDeg[5] = x15 + x25 + x35 + x45;

for( i = ONE; i <= FIVE ;i++ ) 
  {
     noOfDeg[i] = ZERO;;
  }

for( i = ONE; i <= FIVE; i++ ) 
  {
     ++noOfDeg[vertDeg[i]];
  }

degseq = noOfDeg[ONE] + 10 * noOfDeg[TWO] 
          + 100 * noOfDeg[THREE] + 1000 * noOfDeg[FOUR];
switch( degseq )
  {

     case 212:
       {
          findfive = degseq212(
                               C,
                               vertDeg,
                               vertIndex,
                               tutteMat2,
                               tutteMat2X
                              );
          break;
       }

     case 1040:
       {
          findfive = degseq1040(
                                C,
                                vertDeg,
                                vertIndex,
                                tutteMat2,
                                tutteMat2X
                               );
          break;
       }


     case 1121:
       {
          findfive = degseq1121(
                                C,
                                vertDeg,
                                vertIndex,
                                tutteMat2,
                                tutteMat2X
                               );
          break;
       }

     case 311:
       {
          findfive = degseq311(
                               C,
                               vertDeg,
                               vertIndex,
                               tutteMat2,
                               tutteMat2X
                              );
          break;
       }

     case 1220:
       {
          findfive = degseq1220(
                                C,
                                vertDeg,
                                vertIndex,
                                tutteMat2,
                                tutteMat2X
                               );
          break;
       }

     case 2030:
       {
          findfive = degseq2030(
                                C,
                                vertDeg,
                                vertIndex,
                                tutteMat2,
                                tutteMat2X
                               );
          break;
       }

     case 1301:
       {
          findfive = degseq1301(
                                C,
                                vertDeg,
                                vertIndex,
                                tutteMat2,
                                tutteMat2X
                               );
          break;
       }

     case 410:
       {
          findfive = degseq410(
                               C,
                               vertDeg,
                               vertIndex,
                               tutteMat2,
                               tutteMat2X
                              );
          break;
       }

     case 1400:
       {
          findfive = degseq1400(
                                C,
                                vertDeg,
                                vertIndex,
                                tutteMat2,
                                tutteMat2X
                               );
          break;
       }

     case 113:
     case 1004:
     case 32:
       {
          findfive = fiveTreesnew(
                                  C,
                                  vertIndex,
                                  tutteMat2,
                                  tutteMat2X
                                 );
          break;
       }

     case 3200:
       {
          findfive = degseq3200(
                                C,
                                vertDeg,
                                vertIndex,
                                tutteMat2,
                                tutteMat2X
                               );
          break;
       }

     case 5000:
       {
          findfive = degseq5000(
                                C,
                                vertDeg,
                                vertIndex,
                                tutteMat2,
                                tutteMat2X
                               );
          break;
       }

     case 230:
       {
// figure out whether it is k(2,3) or the house 
          for( i = ONE; i <= FIVE; i++ )//found i=i and changed it
            v[i]=0;
          j = ZERO;
          for( i = ONE; i <= FIVE; i++ )
            if( vertDeg[i] == TWO ) 
              {
                 ++j;
                 v[j] = vertIndex[i];
              }
          if( isadj(v[1],v[2],&g[C]) 
                  + isadj(v[1],v[3],&g[C]) 
                        + isadj(v[2],v[3],&g[C]) == ONE ) 
            {
               findfive = degseq230house(
                                         C,
                                         vertDeg,
                                         vertIndex,
                                         tutteMat2,
                                         tutteMat2X
                                        );
            }
          else
            {
               findfive = degseq230k23(
                                       C,
                                       vertDeg,
                                       vertIndex,
                                       tutteMat2,
                                       tutteMat2X
                                      );
            }
          break;
       }



     case 131:
       {  
          for( i= ONE ; i <= FIVE; i++ )
          if( vertDeg[i] == ONE ) 
            {
               j = i;
               v[ONE] = vertIndex[i];
               break;
            }
          for( i = ONE; i <= FIVE; i++ )
            if( ( vertIndex[i] != v[ONE] ) && ( isadj(v[1],vertIndex[i],&g[C]) ) ) 
              {
                  k = i;
                  break;
              }

         if( vertDeg[k] == TWO ) 
           {
              findfive = degseq131triangle(
                                           C,
                                           vertDeg,
                                           vertIndex,
                                           tutteMat2,
                                           tutteMat2X
                                          );
           }
         else
           {
              findfive = degseq131c4(
                                     C,
                                     vertDeg,
                                     vertIndex,
                                     tutteMat2,
                                     tutteMat2X
                                    );
           }

         break;
      }

     case 1022:
       {
          findfive = degseq1022(
                                C,
                                vertDeg,
                                vertIndex,
                                tutteMat2,
                                tutteMat2X
                               );
          break;
       }

     case 50:
       {
          findfive = degseq50(
                              C,
                              vertDeg,
                              vertIndex,
                              tutteMat2,
                              tutteMat2X
                             );
          break;
       }

     case 2210:
       {
          findfive = degseq2210(
                                C,
                                vertDeg,
                                vertIndex,
                                tutteMat2,
                                tutteMat2X
                               );
          break;
       }
     default:
       {
          printf("evaluateFivesA\n");
          break;
       }

  } /* end switch on degseq */

return(findfive);

} /* end evaluateFivesA */








