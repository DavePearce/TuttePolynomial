
#include "core/tutte.h"
#include <memory.h>
#include <stdio.h>
//#include <gmp.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>



/**********************************************************/
/*                                                        */
/*             start enterEdgesBuildGraph                 */
/*                                                        */

/*

Precondition: none

Postcondition: graph entered has its tutte poly computed and displayed

*/


void
enterEdgesBuildGraph(int *C,int *threshcount,int threshtable[],int newthreshold[])
{
TUTTE tutteMat;
TUTTEO tutteMatX;
  

int    i,                         /* for parameter                              */
    ctr, 
    j,
    numberEdges,               /* number of elements in input stream         */
    suma,
    sum,  
    edges1[EDGESIZE][TWO],     /* array to hold the edges of the graph       */ 
    edges2[EDGESIZE][TWO], 
    cards[700],               /* array to hold permutation of 1..|E|         */
    t0,                       /* interchange variables for edge permutation  */
    t3,
    edgeCount,                /* line control for printing tree edges        */  
    ne,                       /* location of edge                            */ 
    hitDistribution[10000],
    vt;                       /* location of vertex                          */
struct Graph h;

/* initialization of some values used to gather run time statistics */
gvnewMax = -500;
stackDepthPop = 5000;
stackDepthPush = -5000;
GraphsInHashTable = ZERO;
LLLL = ZERO;
LLL = ZERO;
L = ZERO;
LLLLL = ZERO;
LLLLLL = ZERO;

printf("64-bit compile\n");

enterEdges ( 
            edges1, 
            &numberEdges 
           );

/* assign space for the hash table-can reuse by resetting index to 0
   whereas free does not let the space be reused */
for( i = ZERO; i < 30; i++ )
  {
     block[i]=(int*) malloc(INTS_PER_BLOCK*sizeof(int));
  }
maxCurrentBlock = 28;

/* 
   set upperbound for size of value in tutteMat 
   -- a long long int can handle 10^17 
   first comlete graph with a coefficient larger
   than this is K(19) 
*/
testNo = TEN;
for( i = ONE; i < SEVENTEEN; i++ )
  testNo *= TEN;


/* 
   randomly permutes the edges from the order they were input
   gives a real sense of robustness to the program since
   the order of the edges determines the data structure
   that in turn determines the compuation tree--getting
   the same result using different computation trees is a
   help to believe in correctness of code
*/

/*
permEdges(
          numberEdges,
          cards
         );
for ( i = ZERO; i <= numberEdges; ++i ) 
  {
    t0 = edges1[i][ZERO];
    t3 = edges1[i][ONE];
    edges1[i][ZERO] = edges1[cards[i]][ZERO];
    edges1[i][ONE] = edges1[cards[i]][ONE];
    edges1[cards[i]][ZERO] = t0;
    edges1[cards[i]][ONE] = t3;
  }

//printf("\n\n\n");
*/

for ( i = ZERO; i <= numberEdges; ++i ) 
  {
     printf("(%3d,%3d) ",edges1[i][ZERO],edges1[i][ONE]);
     if ( ZERO == ( i + ONE ) % NINE ) 
       {
          printf("\n");
       }
  }
printf("\n");
assert(EDGE_IN_GRAPH >= TWO * numberEdges); 


/* initialize graph  and stacks for managing graphs */
initavail ( &avail );
initused ( &used );
*C=popavail ( &avail );

/* enter edges and build data structure */
initGraph ( &g[*C] ); /* header node initialization 
                     and edges read*/

/* put the data structure together */
buildGraphStruct ( edges1, numberEdges, &g[*C] );

/* data structure supports k(20) and each edge is on two lists so has two
   entries and there is a header cell for each vertex--the value can be changed in
   the .h file but this is the current restriction
*/
assert(EDGESIZE >= ( TWO * numberEdges + numVertices(&g[*C]) ) );
assert( g[*C].v < VERTEXSIZE );
assert( g[*C].e  < EDGESIZE );


/* 
   Do a depth first search at the indicated start vertex
   and find and mark the tree edges 
*/ 
dfs(firstVertex(&g[*C]), &g[*C]);;
/*

OUTPUT THE TREE EDGES

*/
edgeCount = ZERO;
printf("\n\n LIST OF TREE EDGES\n");
for(vt = firstVertex(&g[*C]); vt != LIST_END; vt = nextVertex(&g[*C], vt))
{
for(ne = firstEdge(&g[*C], vt); ne != LIST_END; ne = nextEdge(&g[*C], ne))
  if( edgeInSpTree(&g[*C], ne) )
    {
      if( vertName(&g[*C], vertListOtherEnd(&g[*C], ne))
                > vertName(&g[*C], vertListOtherEnd(&g[*C],otherEndEntry(&g[*C], ne))))
      { edgeCount++;
        printf(" ( %2d, %2d ) ", vertName(&g[*C],vertListOtherEnd(&g[*C], otherEndEntry(&g[*C], ne))),
                                    vertName(&g[*C],vertListOtherEnd(&g[*C], ne)));
      if(edgeCount / 8 * 8 == edgeCount) printf("\n");
      }
    }
}
printf("\n\n");
/* 
  set limits for rows and columns that are in 
  keeping with the graph being processes 
  otherwise any zeroing of a matrix goes through
  the size allocated to handle any graph--the
  dimensions alllocated are usually much bigger than
  needed so you waste time set useless storage to 0
  or adding up lots of zeros over and over          */
TUTTECOLS = numVertices(&g[*C]) + THREE;
TUTTEROWS = ( numEdges(&g[*C]) - numVertices(&g[*C]) + ONE ) / TWO - numVertices(&g[*C]) +THREE;
assert( TUTTEROWS < EDGESIZE );
assert( TUTTECOLS < VERTEXSIZE );


/* call the threshold routine after setting upper and lower limits  */
topThreshold = numVertices(&g[*C]);
bottomThreshold = SEVEN;
threshinit(
           &g[*C],
           threshcount,
           threshtable,
           newthreshold
          );


/*
for(i=0;i<numVertices(&g[*C]);i++)
  {KE
    printf("threshtable[%d] = %d ",i,threshtable[i]);
    if(i/4*4==i)printf("\n");
  }
for(i=0;i<numVertices(&g[*C]);i++)
  {
    printf("newthreshold[%d] = %d ",i,newthreshold[i]);
    if(i/4*4==i)printf("\n");
  }
*/

/* save original sizes for the print routine */
origNoVert = numVertices(&g[*C]);
origNoEdge = ( numEdges(&g[*C]) - numVertices(&g[*C]) + ONE ) / TWO;
//printf("origNoVert= %d  origNoEdge= %d\n",origNoVert,origNoEdge);
} /* end enterEdgeBuildGraph */

/*                                                               */
/*                  end enterEdgesBuildGraph                     */
/*                                                               */
/*****************************************************************/
/*                                                               */









                                            




