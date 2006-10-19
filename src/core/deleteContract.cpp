#include <assert.h>
#include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/***************************************************************************/
/*                                                                         */
/*                         start of deleteContract                         */
/*                                                                         */
/*

Precondition: C--integer value that is an index for a graph array entry
              threshnum--initialized integer variable 
              threshtable--initialized integer array
              newthreshold--initialized integer
              tutteMat--array with low order digits of current
                        form of tutte poly
              tutteMatX--array with high order digits of current 
                         form of tutte poly

Postcondition: graph at C contributes its tutte poly to the final version

Modifies: the process is recursive so each call has new values for the 
          variables except for the array threshtable
          C takes on different values held on a stack, the threshnum and 
          newthreshold change to reflect changes in the number of verices 
          in the graph on entry, and the tutte arrays change each time 
          the computation is finished for a graph 

*/

void 
deleteContract(
               int C,  
               int threshnum, 
               int threshtable[], 
               int newthreshold[], 
               TUTTE tutteMat,
               TUTTEO tutteMatX
              )
{

int treeOrNot,             /* return value from detectAndComputeTrees                   */
    j,                     /* for parameter                              */
    i,
    thresholdValueOnEntry, /* will indicate when threshold changes       */
        /* parameters saved after graph is found graph not in hash table */ 
    startused,             /* top of stack value on entry-used to         */
    sendback,
    canong[1000];           /* holds canonical labelling of findInvariant */
unsigned long  int hash;    /* hash value for graph                       */    

/* thresholds decrease as the number of vertices goes from   */
/*   |V| down to bottomThreshold                             */ 
/*                                                           */
thresholdValueOnEntry = threshtable[threshnum];

/* block the top of the stack during this call to deletecontract   */
/*   this value signifies no more graphs to process for this call  */ 
/*   --no need to have a local stack as this block looks like a    */
/*   LIST_END                                                      */
/*                                                                 */
startused = topused ( &used) ;


/* continues until C is set to LOCAL_STACK_END which      */
/* means the graph index on the top of the stack     */
/* is the same as it was at entry -- kind of a trick */
/* so that every call to the routine will not need   */
/* to instantiate a new stack                        */
/*                                                   */   
while (  C != LOCAL_STACK_END )
  {  /* a */ 

    /*                                       */
    /*       TREES                           */
    /*                                       */
    treeOrNot = ONE;
    while( treeOrNot )
      {
         treeOrNot = detectAndComputeTrees(
                                           &g[C],
                                           tutteMat,
                                           tutteMatX
                                          );
         if( treeOrNot )
           {
              C=pushAndPopGraphIndex(C, startused);
           }
      }
      /* identify and delete vertices of degree one */
     findDegOne(&g[C]);
     
     /* for a small graph removing multiple   */
     /*   edges and will generate smaller     */
     /*   graphs that can be finished off     */
     /*                                       */
     if( numVertices(&g[C]) < bottomThreshold )
       {
          deleteAndContractMultEdge(
                         C, 
                         tutteMat,
                         tutteMatX
                        );
       }


    /*                                                            */
    /* get rid of all multigraphs with five or fewer vertices and */
    /* a simple graphs with seven or fewer vertices               */
    /*                                                            */

    /*                                             */
    /*    SIMPLE GRAPHS WITH |V| <= 7              */
    /*                                             */  
      if( ( C != LOCAL_STACK_END ) 
              && !( gotMultiple(&g[C]) ) 
                 && ( numVertices(&g[C]) <= SEVEN ) )
        {  
          simpleSmallGraphElimination(
                                      &C, 
                                      startused,
                                      tutteMat, 
                                      tutteMatX
                                     );
        }

/*                               */
/*  all graphs with 5 or fewer   */
/*  vertices are identifed and   */
/* evaluated by knowing edge     */
/* multiplicities                */
/*                               */
if(C != LOCAL_STACK_END && numVertices(&g[C]) <= FIVE )
  {
    multEdgeSmallGraphElimination(&C,startused,tutteMat,tutteMatX);
  
  } 


/*                                             */
/*  IF G[C] IS NOT SMALL, REDUCE IT            */
/*                                             */
if( ( C != LOCAL_STACK_END ) && ( numVertices(&g[C]) > FIVE ) )
  { /* start greater than 5 and may not be a simple graph */
    
    /* if threshold equaled or passed, no. vertices less  */
    /* than in graph that entered deleteCOntract          */
    /*                                                    */
     if(numVertices(&g[C])<=thresholdValueOnEntry)
       { /* i */ 
         graphIsoTestHash(
                             &C,
                             startused, 
                             thresholdValueOnEntry,
                             canong,
                             &hash,
                             tutteMat,
                             tutteMatX,
                             threshtable,
                             newthreshold);
                            
       }/* i */ 
     else 
       {/* n */

          /*                                                     */
          /* do the delete and contract operations               */ 
          /*                                                     */    
          doDeleteContract(C,tutteMat,tutteMatX);

     }/* n delete/contract block*/

  }/* end of bigger than five block */

 }/* a  looking for LOCAL_STACK_END */

} /* end deleteContract */

/*                                            */
/*                end of deleteContract       */
/*                                            */
/**********************************************/


/**********************************************/
/*                                            */
/*        start of detectAndComputeTree       */
/*                                            */

 
/*  THIS PROBABLY DOESN'T BELONG HERE --- DAVE

Precondition: a graph and the current state of the tutte polynomial

Postcondition: if the graph is a tree, the current state of the uttte
               polynomial is altered to reflect that fact and a signal
               is returned indicating the graph is a tree    

Return: 0 if the graph is not a tree
        1 if the graph is a tree
*/


/* routine that identifies a graph as a tree and increments
   treecount and otree appropriately by calling mtwo */

int detectAndComputeTrees(struct Graph *g,TUTTE tutteMat, TUTTEO tutteMatX)

{
int i,    /* for parameter */
    j,
    m; 
TUTTE tutteMat1;
TUTTEO tutteMat1X;

if ( numVertices(g) != (( numEdges(g) - numVertices(g) + 1 ) / 2 + 1)) 
  {
      return( 0 );
  }
else
  {   
     /* have to find some nonzero entry location */
     /* to start the multiplication of factors   */
     /* collected along the way                  */ 
     /*                                          */
      /* initialize temp arrays for computing     */
     for( i = 0 ; i < TUTTEROWS; ++i )
     for( j = 0; j < TUTTECOLS; ++j )
       {
          tutteMat1[i][j] = 0;
          tutteMat1X[i][j] = 0;
       }
     /* find a place to put a nonzero entry in the poly matrix */
     if( numVertices(g) <= 1 ) 
       {
 
          if( degOneDels(g)  != 0 )
            {
               tutteMat1[0][degOneDels(g)] = 1;
               setMinusone(g, 0);  
            }
          else
            if( triangleDels(g)  != 0 )
              {
                 tutteMat1[0][0] = 1;
                 tutteMat1[0][1] = 1;
                 incrTriangleDels(g, -1);  
              }
            else
              if( getMultCount(g, 0) != 0 )
                {
                   m = getMultCount(g, getMultCount(g, 0));
                   for( i = 1; i <= m; ++i )
                     tutteMat1[i][0] = 1;
                   removeMultCountValue(g); 
                }
              else 
                {
                   tutteMat1[0][0] = 1;
                } 
          /* contribute to final answer */ 
          multiplyByFactors(
                            g,
                            tutteMat,
                            tutteMatX,
                            tutteMat1,
                            tutteMat1X,
                            degOneDels(g), 
                            triangleDels(g)  
                           );
          return( 1 ); 
       }
     else
       { 
          tutteMat1[0][(*g).v - 1] = 1;
          /* contribute to final answer */
          multiplyByFactors(
                            g,
                            tutteMat,
                            tutteMatX,
                            tutteMat1,
                            tutteMat1X,
                            degOneDels(g), 
                            triangleDels(g)  
                           );
           return(1); 
        }  

  } 

} /* end of detectAndComputeTrees */

  
/*                                            */
/*       end of detectAndComputeTrees         */
/*                                            */
/**********************************************/


/**********************************************/
/*                                            */
/*            start of removeMultEdge         */
/*                                            */

/*
Precondition: C--index into graph array pointing to a graph
              arrays tutteMat and tuteMatX contain the curent status of
              the computation

Postcondition: any multiple edges in the graph are deleted so the graph at C is
               returned as a simple graph

SideEffect: there can be many graphs added to the graph stack as well as the
            value of multCount[] changed a number of times. any small graphs
            will have their tutte poly contribute to the final answer


*/

void
deleteAndContractMultEdge (int C, TUTTE tutteMat,TUTTEO tutteMatX)
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


struct Graph k[6];

detectAndDeleteLoop(&g[C]);
for(vert1=firstVertex(&g[C]);vert1 != EOLIST;vert1=nextVertex(&g[C], vert1)) 
  {
    for( edgFIXED = firstEdge(&g[C], vert1); edgFIXED != EOLIST; edgFIXED=nextEdge(&g[C],edgFIXED)) 
       {
deleteMultEdges(&g[C],&NoMultEdges,edgFIXED);
if(NoMultEdges > 0)
   {recordMultiples(&g[C],NoMultEdges,vert1,edgFIXED,tutteMat,tutteMatX);
          findDegOne(&g[C]);
   }
       } /* while edgFIXED */
  } /* while vert1 */
  
/* end of vert list */

retree(&g[C]);
 

findDegOne(&g[C]);

} /* end removeMultEdge  */

        
int
recordMultiples(struct Graph *h,int NoMultEdges,int vert1,int edgFIXED,
      TUTTE tutteMat,TUTTEO tutteMatX)
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
degEnd1=vertDegree(h,vertListOtherEnd(h,otherEndEntry(h, edgFIXED)));
degEnd2=vertDegree(h, vertListOtherEnd(h, edgFIXED));
            sendback=deleteEdge(
                               edgFIXED,
                               &g[D]
                              );
degEnd1--;
degEnd2--;
if(degEnd1>= ONE && degEnd2 >= ONE)
//              if( sendback == ZERO )
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
                        if( g[D].v <= FIVE )
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
//               if( sendback == ONE )
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
if( (degEnd1 == ZERO && degEnd2 >= ONE) ||  ( degEnd1 >= ONE && degEnd2 == ZERO) ) 
//   if ( sendback == TWO )
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

} /* end removeMultEdge  */


/*                                            */
/*             end of removeMultEdge          */
/*                                            */
/**********************************************/

