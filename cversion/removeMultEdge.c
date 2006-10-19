#include <assert.h>
#include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


/**********************************************/
/*                                            */
/*            start of removeMultEdge         */
/*                                            */
/*                                            */
/*
Precondition: C--index into graph array pointing to a graph
              arrays tutteMat and tuteMatX contain the curent status of
              the computation

Postcondition: any multiple edges in teh graph are deleted so the graph at C is
               returned as a simple graph

SideEffect: there can be many graphs added to the graph stack as well as the
            value of multCount[] changed a number of times. any small graphs
            will have their tutte poly contribute to the final answer


*/

void
deleteAndContractMultEdge(
                          int C, 
                          TUTTE tutteMat,
                          TUTTEO tutteMatX
                         )
{
int 
    t2,
    sendback,           /* indicator of nature of deleted edge     */
    vert1,              /* location of vertex                      */
    edgFIXED,           /* location of edge                        */
    NoMultEdges,        /* counter for multiple edges              */
    nameToMatch,        /* search value--other end of edge         */
    edgeCompare,        /* location of edge                        */
    smallreturn;        /* return value for processing small graph */


struct graph k[6];

detectAndDeleteLoop(&g[C]);
for(vert1=firstVertex(&g[C]);
       vert1 != EOLIST;
          vert1=nextVertex(&g[C], vert1)) 
  {
    for( edgFIXED = firstEdge(&g[C], vert1); 
            edgFIXED != EOLIST; 
               edgFIXED=nextEdge(&g[C],edgFIXED)) 
       {
          deleteMultEdges(&g[C],&NoMultEdges,edgFIXED);
          if(NoMultEdges > 0)
            {
               recordMultiples(&g[C],NoMultEdges,vert1,edgFIXED,tutteMat,tutteMatX);
               findDegOne(&g[C]);
            }
       } /* while edgFIXED */
  } /* while vert1 */
  
/* end of vert list */

retree(&g[C]);
 

findDegOne(&g[C]);

} /* end deleteAndContractMultEdge */
        
/*                                            */
/*                                            */
/*     end deleteAndContractMultEdge          */
/*                                            */
/**********************************************/
/*                                            */
/*            start of recordMultiples        */
/*                                            */
/*                                            */
int
recordMultiples(
                struct graph *h,
                int NoMultEdges,
                int vert1,
                int edgFIXED,
                TUTTE tutteMat,
                TUTTEO tutteMatX
               )
{
int t2,
    sendback,
    smallreturn,
    treeornot,
    degEnd1,
    degEnd2,
    D;

            D = popavail(&avail); 
              copyGraph(
                        h, 
                        &g[D]
                       );

             if( NoMultEdges == ONE )
                {
                   ++g[D].yPower;
                }
             else
                {
                   ++g[D].multCount[ZERO];
                   assert( g[D].multCount[ZERO] < 100 ); 
                   g[D].multCount[g[D].multCount[ZERO]] = NoMultEdges;
                }               
             degEnd1 = vertDegree(h,vertListOtherEnd(h,otherEndEntry(h, edgFIXED)));
             degEnd2 = vertDegree(h, vertListOtherEnd(h, edgFIXED));
             sendback = deleteEdge(
                                  edgFIXED,
                                  &g[D]
                                 );
             degEnd1--;
             degEnd2--;
             if(degEnd1>= ONE && degEnd2 >= ONE)
                {/* sendback==0 */

                   t2 = g[D].edg[edgFIXED].vertlist;
                   contract(
                            vert1,
                            t2,
                            &g[D]
                           );
                
                   treeornot = detectAndComputeTrees(
                                      &g[D], 
                                      tutteMat,
                                      tutteMatX
                                     );
                   if( treeornot )
                     { 
                        pushavail(
                                  D, 
                                  &avail
                                 );
                     }
                   else
                     {
                        if( numVertices(&g[D]) <= FIVE )
                          {
                             smallreturn = evaluateSmallGraphs(
                                                               D,
                                                               tutteMat,
                                                               tutteMatX
                                                              );
                             if( smallreturn )
                               {
                                  pushavail(
                                            D,
                                            &avail
                                           ); 
                               }
                             else
                               { 
                                  findDegOne(&g[D]);
                                  putonstack(
                                             &used,
                                             D
                                            ); 
                               }
                          }
             
                        else
                          {
                             findDegOne(&g[D]);           
                             putonstack(
                                        &used, 
                                        D
                                       );
                          } 
                    }/* end else */ 

               } /* end sendback == 0 */ 
             else
               if(degEnd1 == ZERO && degEnd2 == ZERO)
                 // means that sendback == ONE 
                 {
                    treeornot = detectAndComputeTrees(
                                                      &g[D], 
                                                      tutteMat,
                                                      tutteMatX
                                                     );
                    pushavail(
                              D, 
                              &avail
                             );
                 }
              else
                if( (degEnd1 == ZERO && degEnd2 >= ONE) 
                   ||  ( degEnd1 >= ONE && degEnd2 == ZERO) ) 
                     // this means that sendback == TWO 
                   {
                      treeornot = detectAndComputeTrees(
                                                        &g[D], 
                                                        tutteMat,
                                                        tutteMatX
                                                       );
                      if( treeornot )
                        { 
                           pushavail(
                                     D, 
                                     &avail
                                    );
                        }
                      else
                        {
                           findDegOne(&g[D]);                   
                           putonstack(
                                      &used, 
                                      D
                                     );
                        }
                  }/* end sendback ==2 */

} /* end recordMultiples  */

/*                                            */
/*                                            */
/*             end  recordMultiples           */
/*                                            */
/**********************************************/
/*                                            */
/*            start deleteMultEdges           */
/*                                            */
/*                                            */

/* 
Precondition: a graph g is searched for multiple edges
              in the edge list of a vertex
              the number of multiple edges found is
              returned in NoMultEdges
              edgFIXED is an edge that may have
              multiples
Postcondion: the number of multiple edges for edgFIXED
             is returned. the graph has the multiple edges deleted
*/
 
int
deleteMultEdges
               (
                struct graph *g,
                int *NoMultEdges,
                int edgFIXED
               )
{
int nameToMatch,
    edgeCompare;

  *NoMultEdges = ZERO;
  nameToMatch = (*g).edg[edgFIXED].ename;
  for(edgeCompare=nextEdge(g, edgFIXED); 
        edgeCompare != EOLIST; 
          edgeCompare=nextEdge(g, edgeCompare)) 
            { 
               if( (*g).edg[edgeCompare].ename == nameToMatch )
                 {
                    if( (*g).edg[edgeCompare].tree == ONE )
                      {
                         (*g).edg[edgFIXED].tree = ONE;
                         (*g).edg[(*g).edg[edgFIXED].side].tree = ONE;
                      }

                    deleteEdge(
                            edgeCompare, 
                            g
                           ); 
                    ++(*NoMultEdges);
                 } 
           }          

} /* end deleteMultEdges */


/*                                            */
/*                                            */
/*             end deleteMultEdges            */
/*                                            */
/**********************************************/



