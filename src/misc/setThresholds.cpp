#include "core/tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/***********************************************/
/*                                             */
/*            start of threshinit              */
/*                                             */

/*

Precondition: graph has been built with g.v vertices and threshold 
                tables are defined but unitialized 

Postcondition: graph is unaltered but the threshold tables are filled 
                in

*/


void 
threshinit ( struct Graph *g, int *threshcount,int  threshtable[],int  newthreshold[] )

{
int i,                /* loop parameter      */
    vert;             /* loop paramteter     */
//printf("setThresholds\n");

if ( numVertices(g)  >= bottomThreshold ) 
  {
     *threshcount = topThreshold - bottomThreshold + ONE;
  
     for ( i = bottomThreshold; i <= bottomThreshold + *threshcount; ++i ) 
       {
          threshtable[i- bottomThreshold ] = i;
       }
  } 
else 
  {
     *threshcount = ONE;
     threshtable[ZERO] = 39;
  }

threshtable[*threshcount] = MINUSONE;

/* second table so that skipped values do not cause confusion */
vert = ZERO;
i = ZERO;
while ( vert <= threshtable[*threshcount - ONE] ) 
  {
     if ( vert <= threshtable[i] ) 
       {
          newthreshold[vert] = i - ONE;
          ++vert;
       } 
     else 
       {
	   ++i;
       }
  }

	    
} /* end of threshinit */ 

/*                                             */
/*            end of threshinit                */
/*                                             */
/***********************************************/
/*                                             */
/*            start of threshinitb             */
/*                                             */

/*

Precondition: graph has been built with g.v vertices and threshold 
                tables are defined but unitialized 

Postcondition: graph is unaltered but the threshold tables are filled 
                in
*/


void 
threshinitb (struct Graph *g, int *threshcount,int  threshtable[],int  newthreshold[])

{
int i,                /* loop parameter      */
    vert;             /* loop paramteter     */


if ( numVertices(g) >= smallestThreshold  ) 
  { 
     *threshcount = numVertices(g)  - smallestThreshold + ONE;


     for ( i = smallestThreshold; i <= numVertices(g); ++i ) 
       {
          threshtable[i - smallestThreshold] = i;
       }
  } 
else 
  {
     *threshcount = ONE;
     threshtable[ZERO] = 39;
  }

threshtable[*threshcount]=MINUSONE;

/* second table so that skipped values do not cause confusion */
vert = ZERO;
i = ZERO;
while ( vert <= threshtable[*threshcount - ONE] ) 
  {
     if ( vert <= threshtable[i] ) 
       {
          newthreshold[vert] = i - ONE;
          ++vert;
       } 
     else 
       {
	   ++i;
       }
  }

} /* end of threshinitb */ 

/*                                             */
/*            end of threshinitb               */
/*                                             */
/***********************************************/
