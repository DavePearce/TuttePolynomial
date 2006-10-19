
#include "tutte.h"
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
main(
     int argc,
     char *argv[]
    )

{
TUTTE tutteMat;
TUTTEO tutteMatX;
  
int C,                         /* index for graph array                      */
    i,                         /* for parameter                              */
    ctr, 
    j,
    threshcount,              /* variable for setting up thresholds          */ 
    threshtable[VERTEXSIZE],
    newthreshold[VERTEXSIZE],
    Numerator;
struct graph h;

if(argc > ONE )
  {
   //printf("argc=%d\n",argc);
   Numerator = atoi(argv[1]);
  }
else
  {
   Numerator = 40;
  }

/*                           */
/* INITIALIZE stat variables */
/* and the hash table        */
/*                           */
isoAndStatSetVars();

/*                         */
/* BUILD THE GRAPH         */
/* set computation needs   */
/*                         */
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
h=g[C];

printf ( "\nVERTICES = %6d EDGES = %6d\n\n",g[C].v, origNoEdge);

/* initialize hash table and associated variables 
   the values needed are in hashinit(), the variables
   currentblock, and intsleft                         */
upperIsoAddTestLimit=Numerator *origNoVert / 20;

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

printf("INTS LEFT FROM 10000000 intsleft  = %d ACTUAL NUMBER INTS USED  = %d\n"
                       ,intsleft,10000000 - intsleft);
#if(PROFILING_MODE)
recapStats(&h,tutteMat,tutteMatX);
#endif
} /* end main */

/*                                                               */
/*                       end main                                */
/*                                                               */
/*****************************************************************/
/*                                                               */









                                            
