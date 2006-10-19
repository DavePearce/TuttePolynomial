#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "core/tutte.h"

/*************************************************/
/*                                               */
/*                                               */
/*             start completePolyWithNoX         */
/*                                               */
/*                                               */


/*
Precondition: the underlying simple graph is K(4) and the values are the
              multiplicities of the edges in canonical order. the additional
              value indicates the multiplicity of a factor consisting of powers 
              of y. the arrays tutteMat2 and tutteMat2X hold the current value 
              of the computation for this graph 

Postcondition: tutteMat2 and tutteMat2X are the current state of the computation
               of this graph 

Return: 1 to signify the graph needs replacing

*/

int completePolyWithNoX(int nx,
                        int n12,
                        int n13,
                        int n14,
                        int n23,
                        int n24,
                        int n34,
                        TUTTE tutteMat2,
                        TUTTEO tutteMat2X
                       )
{
int k,
    k1,
    graphNo,
    i,
    j,
    l,
    xp,
    yp;
//printf("evaluateFives\n");
for( k = ZERO; k < nx; k++ )
  {/* with k there is x term and powers of y */
     for( l = ZERO; l < n13; l++ )
       {
          for ( i = ZERO; i < n12 + n23 + n14 + n34; i++ )
          for ( j = ZERO; j < n24; j++ ) 
            {
               xp = (( i == ZERO )?ONE:ZERO);
               yp = i + j + l + k;
               tutteMat2[yp][xp]++;
            }
       }
  }/* end k loop */

for( k = ZERO; k < nx; k++ )
  {/* k loop */
     for( l = ZERO; l < n13; l++ )
       {
          for ( i = ZERO; i < n12 + n23; i++ )
          for ( j = ZERO; j < n14 + n34 ;j++ ) 
            {
               xp = ( ( i == ZERO )?ONE:ZERO ) + ( ( j == ZERO )?ONE:ZERO );
               yp = i+j+l+k;
               tutteMat2[yp][xp]++;
            }
       }
  }/* end k loop */


/* replace with below */
for( k1 = 0; k1 < nx; k1++ )
  {/* start of k1 loop */
     for( i = ZERO; i < n24; i++ )
     for( j = ZERO; j < n12 + n14; j++ )
     for( k = ZERO; k < n34 + n23; k++ )
       {
          yp = i +  j + k + k1;
          xp = ( ( j == ZERO )?ONE:ZERO ) + ( ( k == ZERO )?ONE:ZERO );
          tutteMat2[yp][xp]++;
       }
  }/* end k1 loop */

/* end fixedrandom code except for fixed four cycle */
/* need replacement below */

for( k1 = ZERO; k1 < nx; k1++ )
  { /* start of k1 loop */
     for( i = ZERO; i < n12; i++ )
     for( j = ZERO; j < n14; j++ )
     for( k = ZERO; k < n34 + n23; k++ )
       {
          xp =( ( k == ZERO )?ONE:ZERO );
          yp = i + j + k + k1;
          tutteMat2[yp][xp]++;
       }
  }

for( k1 = ZERO; k1 < nx; k1++ )
  {
     for( i = ZERO; i < n12; i++ )
     for( j = ZERO; j < n34; j++ )
     for( k = ZERO; k < n23; k++ )
       {
          xp = ( ( k == ZERO )?ONE:ZERO ) + ( ( j == ZERO )?ONE:ZERO );
          yp = i + j + k + k1;
          tutteMat2[yp][xp]++;
       }/*i-j-k loop */
  }/*k1 loop */



for( k1 = ZERO; k1 < nx; k1++ )
  {
     for( i = ZERO; i < n23; i++ )
     for( j = ZERO; j < n34; j++ )
     for( k = ZERO; k < n14; k++ )
       {
          xp=(( i == ZERO )?ONE:ZERO)+(( k == ZERO )?ONE:ZERO)+(( j == ZERO )?ONE:ZERO );
          yp = i + j + k + k1;
          tutteMat2[yp][xp]++;
       }
  }/* end k1 loop */

return( ONE );

}/* end completePolyWithNoX */

/*                                               */
/*                                               */
/*                                               */
/*             end completePolyWithNoX           */
/*                                               */
/*                                               */
/*                                               */
/*************************************************/
/*                                               */
/*                                               */
/*             start completePolyWithX           */
/*                                               */
/*                                               */
/*                                               */

/*
Precondition: the underlying simple graph is K(4) and the values are the
              multiplicities of the edges in canonical order. the additional
              value indicates the multiplicity of a factor with an x term. 
              the arrays tutteMat2 and tutteMat2X hold the current value 
              of the computation for this graph

Postcondition: tutteMat2 and tutteMat2X are the current state of the computation
               for this graph 


Return: 1 to signify the graph needs replacing

*/

int completePolyWithX(int nx,
                      int n12,
                      int n13,
                      int n14,
                      int n23,
                      int n24,
                      int n34,
                      TUTTE tutteMat2,
                      TUTTEO tutteMat2X
                     )
{
int k,
    k1,
    graphNo,
    i,
    j,
    l,
    xp,
    yp;


for( k = 0; k < nx; k++ )
  {/* with k there is x term and powers of y */

     for( l = 0; l < n13; l++ )
       {
          for ( i = 0; i < n12 + n23 + n14 + n34; i++ )
          for ( j = 0; j < n24; j++ ) 
             {
               xp = ( ( i == ZERO )?ONE:ZERO) + ( ( k == ZERO )?ONE:ZERO );
               yp = i + j + l + k;
               tutteMat2[yp][xp]++;
            }
       }
  }/* end k loop */

for( k = 0; k < nx; k++ )
  {/* k loop */
     for( l = 0; l < n13; l++ )
       {
          for ( i = 0; i < n12 + n23; i++ )
          for ( j = 0; j < n14 + n34; j++ ) 
            {
               xp = ( ( i == ZERO )?ONE:ZERO ) + ( ( j == ZERO )?ONE:ZERO ) + ( ( k == ZERO )?ONE:ZERO );
               yp = i+j+l+k;
               tutteMat2[yp][xp]++;
            }
       }
  }/* end k loop */



/* replace with below */
for( k1 = 0; k1 < nx; k1++ )
  {/* start of k1 loop */
     for( i = 0; i < n24; i++ )
     for( j = 0; j < n12 + n14; j++ )
     for( k = 0; k < n34 + n23; k++ )
       {
          yp = i + j + k + k1;
          xp = ( ( j == ZERO )?ONE:ZERO ) + ( ( k == ZERO )?ONE:ZERO ) + ( ( k1 == ZERO )?ONE:ZERO );
          tutteMat2[yp][xp]++;
       }
  }/* end k1 loop */

/* end fixedrandom code except for fixed four cycle */
/* need replacement below */

for( k1 = 0; k1 < nx; k1++ )
  { /* start of k1 loop */
     for( i = 0; i < n12; i++ )
     for( j = 0; j < n14; j++ )
     for( k = 0; k < n34 + n23; k++ )
       {
          xp = ( ( k == ZERO )?ONE:ZERO ) + ( ( k1 == ZERO )?ONE:ZERO );
          yp = i + j + k + k1;
          tutteMat2[yp][xp]++;
       }
  }

for( k1 = 0; k1 < nx; k1++ )
  {
     for( i = 0; i < n12; i++ )
     for( j = 0; j < n34; j++ )
     for( k = 0; k < n23; k++ )

       {
          xp = ( ( k == ZERO )?ONE:ZERO) + ( ( j == ZERO )?ONE:ZERO) + ( ( k1 == ZERO )?ONE:ZERO);
          yp = i + j + k + k1;
          tutteMat2[yp][xp]++;
       }/*i-j-k loop */
  }/*k1 loop */



for(k1=0;k1<nx;k1++)
  {
     for( i = 0; i < n23; i++ )
     for( j = 0; j < n34; j++ )
     for( k = 0; k < n14; k++ )
       {
          xp = ( ( i == ZERO )?ONE:ZERO ) + ( ( k == ZERO )?ONE:ZERO ) + ( ( j == ZERO )?ONE:ZERO ) + ( ( k1 == ZERO )?ONE:ZERO );
          yp = i + j + k + k1;
          tutteMat2[yp][xp]++;
       }
  }/* end k1 loop */

return( ONE );

}/* end completePolyWithX */




/*                                               */
/*                                               */
/*                                               */
/*             start completePolyWithX           */
/*                                               */
/*                                               */
/*                                               */
/*************************************************/


