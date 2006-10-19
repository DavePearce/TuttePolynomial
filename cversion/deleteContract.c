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

/*                                                              */
/* thresholds decrease as the number of vertices goes from      */
/*   |V| down to bottomThreshold                                */
/* deleteContract enters with |V(G)|>thresholdValueOnEntry      */
/* and continues this call until |V(G)| <=thresholdValueOnEntry */ 
/*                                                              */
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
              && !( gotMultiple(C) ) 
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
                          newthreshold
                         );
                            
       }/* i */ 
     else 
       {/* n */

          /*                                                     */
          /* do the delete and contract operations               */ 
          /*                                                     */    
          doDeleteContract(
                           C,
                           tutteMat,
                           tutteMatX
                          );

     }/* n delete/contract block*/

  }/* end of bigger than five block */

 }/* a  looking for LOCAL_STACK_END */

} /* end deleteContract */

/*                                            */
/*                end of deleteContract       */
/*                                            */
/**********************************************/




