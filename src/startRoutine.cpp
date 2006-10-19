
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
/*                  start of main                         */
/*                                                        */

/*

Precondition: none

Postcondition: graph entered has its tutte poly computed and displayed

*/


int
main(int argc, char   argv [])
{
TUTTE tutteMat;
TUTTEO tutteMatX;
  
int C,                         /* index for graph array                      */
    i,                         /* for parameter                              */
    ctr, 
RET,    j,
    threshcount,              /* variable for setting up thresholds          */ 
    threshtable[VERTEXSIZE],
    newthreshold[VERTEXSIZE];
struct Graph h;

enterEdgesBuildGraph(&C,&threshcount,threshtable,newthreshold);

/* 
   initialize the matrices that will hold the two parts of the
   coefficients
*/
for( i = ZERO; i < TUTTEROWS; ++i )
for( j = ZERO; j < TUTTECOLS; ++j )
  {
     tutteMat[i][j] = ZERO;
     tutteMatX[i][j] = ZERO;
  }

/*                                          */
/* save original graph for stats at the end */
/*                                          */

copyGraph(&g[C],&h);

printf ( "\nVERTICES = %6d EDGES = %6d\n\n",g[C].v, origNoEdge);

/* initialize hash table and associated variables 
   the values needed are in hashinit(), the variables
   currentblock, and intsleft                         */

isoreset();

upperIsoAddTestLimit=origNoVert*1.7;
lowerIsoAddTestLimit= 7;
printf("upperIsoAddTestLimit = %d   lowerIsoAddTestLimit = %d\n",
           upperIsoAddTestLimit,lowerIsoAddTestLimit);
/* go and do it */
deleteContract(
               C, 
               threshcount - ONE, 
               threshtable, 
               newthreshold,
               tutteMat,
               tutteMatX
              );

/* print the tutte polynomial */

printTutte (
            tutteMat,
            tutteMatX 
           );

//printf("LLLLL=%d  LLLLLL=%d\n",LLLLL,LLLLLL);
printf("BYTES LEFT FROM 100000000 intsleft * 4 = %d ACTUAL NUMBER BYTES = %d\n",4*intsleft,intsleft);
recapStats(&h,tutteMat,tutteMatX);

} /* end main */

/*                                                               */
/*                       end main                                */
/*                                                               */
/*****************************************************************/
/*                                                               */









                                            
