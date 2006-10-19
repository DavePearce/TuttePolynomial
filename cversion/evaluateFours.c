#include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**************************************************/
/*                                                */
/*                                                */
/*               start fourcomplete               */
/*                                                */
/*                                                */

/*
Precondition: n12, n13, ..., n34 give multiplicities of edges of
              K(4) described in a canonimcal order for the edges
              arrays tutteMat2 and tutteMat2X hold the current
              status of the computation of a tutte poly

Postcondition: arrays tutteMat2 and tutteMat2X are augmented
               by the tutte poly of the K(4) with these 
               nonzero edge multiplicities

Return: 1 to signify the need to replace the graph

*/


int fourcomplete(
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

int i,           /* for parameter                    */
    j,
    k,
    xp,          /* degree of x in monomial          */
    yp;          /* degree of y in monomial          */
//printf("evaluateFours\n");
for( k = ZERO; k < n13; k++ )
  {
     for ( i = ZERO; i < n12 + n23 + n14 + n34; i++ )
     for ( j = ZERO; j < n24; j++ ) 
       {
          xp = ( i == ZERO )?ONE:ZERO;
          yp = i + j + k;
          tutteMat2[yp][xp]++;
       }

  }

for( k = ZERO; k < n13; k++ )
  {
     for ( i = ZERO; i < n12 + n23; i++ )
     for ( j = ZERO; j < n14 + n34; j++ ) 
       {
          xp = (( i == ZERO)?ONE:ZERO) + (( j == ZERO )?ONE:ZERO);
          yp = i + j + k;
          tutteMat2[yp][xp]++;
       }
  }

fixedrandomgraph(n24,n12,n14,n34,n23,
                 tutteMat2,
                 tutteMat2X);

return(ONE);

}/*end fourcomplete*/

/*                                                */
/*                                                */
/*                                                */
/*                 end fourcomplete               */
/*                                                */
/*                                                */
/**************************************************/
/*                                                */
/*                                                */
/*               start fixedrandomgraph           */
/*                                                */
/*                                                */
/*
Precondition: n1, n2, ..., n5 give multiplicities of edges of
              the random graph described in a canonimcal order 
              for the edges
              arrays tutteMat2 and tutteMat2X hold the current
              status of the computation of a tutte poly

Postcondition: arrays tutteMat2 and tutteMat2X are augmented
               by the tutte poly of the random graph
               with these nonzero edge multiplicities

Return: 1 to signify the need to replace the graph

*/

int fixedrandomgraph(
                     int n1,
                     int n2,
                     int n3,
                     int n4,
                     int n5,
                     TUTTE tutteMat2,
                     TUTTEO tutteMat2X
                    )
{
int i,           /* for parameter                    */
    j,
    k,
    xp,          /* degree of x in monomial          */
    yp;          /* degree of y in monomial          */

for( i = ZERO; i < n1; i++ )
for( j = ZERO; j < n2 + n3; j++ )
for( k = ZERO; k < n4 + n5; k++ )
  {
     yp = i + j + k;
     xp = (( j == ZERO )?ONE:ZERO) + (( k == ZERO )?ONE:ZERO);
     tutteMat2[yp][xp]++;
  }
fixedfourcycle(n2,n3,n4,n5,
               tutteMat2,
               tutteMat2X);

return( ONE );

}/* end fixedrandomgraph */

/*                                                */
/*                                                */
/*                                                */
/*         end fixedrandomgraph                   */ 
/*                                                */
/*                                                */
/**************************************************/
/*                                                */
/*                                                */
/*               start randomgraph                */
/*                                                */
/*                                                */
/*
Precondition: n12, n13, ..., n34 give multiplicities of edges of
              K(4) described in a canonimcal order for the edges
              x12, x13, ... , x34 indicate the existence of an
              edge 
              arrays tutteMat2 and tutteMat2X hold the current
              status of the computation of a tutte poly

Postcondition: arrays tutteMat2 and tutteMat2X are augmented
               by the tutte poly of the random graph 
               associated with these nonzero edge multiplicities

Return: 1 to signify the need to replace the graph

*/

int randomgraph(
                int x12,
                int x13,
                int x14,
                int x23,
                int x24,
                int x34,
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

int n1,         /* canonical identification of multiplicities  */
    n2,
    n3,
    n4,
    n5,
    noGraph;    /* hash value for switching purposes           */

noGraph = x12 + 2 * x13 + 4 * x14 + 8 * x23 + 16 * x24 + 32 * x34;
switch( noGraph )
  {
    case 62:
      {
         n1 = n34;
         n2 = n13;
         n3 = n14;
         n4 = n24;
         n5 = n23;
         break;
      }
    case 47:
      {
         n1 = n13;
         n2 = n12;
         n3 = n23;
         n4 = n34;
         n5 = n14;
         break;
      }
    case 59:
      {
         n1 = n23;
         n2 = n12;
         n3 = n13;
         n4 = n34;
         n5 = n24;
         break;
      }
    case 55:
      {
         n1 = n14;
         n2 = n12;
         n3 = n24;
         n4 = n34;
         n5 = n13;
         break;
      }
    case 61:
      {
         n1 = n24;
         n2 = n12;
         n3 = n14;
         n4 = n34;
         n5 = n23;
         break;
      }
    case 31:
      {
         n1 = n12;
         n2 = n13;
         n3 = n23;
         n4 = n24;
         n5 = n14;
         break;
      }
    default:
      {
        printf("randomgraph\n");
        break;
      }

  }/* end switch*/


fixedrandomgraph(n1,n2,n3,n4,n5,
                 tutteMat2,
                 tutteMat2X);

return( ONE );

}/*end randomgraph*/

/*                                                */
/*                                                */
/*                                                */
/*            end randomgraph                     */
/*                                                */
/*                                                */
/**************************************************/
/*                                                */
/*                                                */
/*               start fouredges                  */
/*                                                */
/*                                                */
/*
Precondition: n12, n13, ..., n34 give multiplicities of edges of
              K(4) described in a canonimcal order for the edges
              x12, x13, ... , x34 indicate the existence of an
              edge 
              arrays tutteMat2 and tutteMat2X hold the current
              status of the computation of a tutte poly

Postcondition: arrays tutteMat2 and tutteMat2X are augmented
               by the tutte poly of a four edged graph with 
               the associated nonzero edge multiplicities

Return: 1 to signify the need to replace the graph

*/

int fouredges(
              int x12,
              int x13,
              int x14,
              int x23,
              int x24,
              int x34,
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

if(( ( x12 == ONE ) && ( x13 == ONE ) && ( x14 == ONE ) ) ||
   ( ( x12 == ONE ) && ( x23 == ONE ) && ( x24 == ONE ) ) ||
   ( ( x13 == ONE ) && ( x23 == ONE ) && ( x34 == ONE ) ) ||
   ( ( x14 == ONE ) && ( x24 == ONE ) && ( x34 == ONE ) )  )
  fourtrianglewithatail(x12,x13,x14,x23,x24,x34,
                        n12,n13,n14,n23,n24,n34,
                        tutteMat2,
                        tutteMat2X);
else
  fourcycle(x12,x13,x14,x23,x24,x34,
            n12,n13,n14,n23,n24,n34,
            tutteMat2,
            tutteMat2X);

return( ONE );

} /* end fouredges */


/*                                                */
/*                                                */
/*                                                */
/*               end fouredges                    */
/*                                                */
/*                                                */
/**************************************************/
/*                                                */
/*                                                */
/*            start fourtrianglewithtail          */
/*                                                */
/*                                                */

/*
Precondition: n12, n13, ..., n34 give multiplicities of edges of
              K(4) described in a canonimcal order for the edges
              x12, x13, ... , x34 indicate the existence of an
              edge 
              arrays tutteMat2 and tutteMat2X hold the current
              status of the computation of a tutte poly

Postcondition: arrays tutteMat2 and tutteMat2X are augmented
               by the tutte poly of triangle with a tail 
               associated with the nonzero edge multiplicities

Return: 1 to signify the need to replace the graph

*/

int fourtrianglewithatail(
                          int x12,
                          int x13,
                          int x14,
                          int x23,
                          int x24,
                          int x34,
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
TUTTE   tutteMat4, 
        tutteMat8;
int i,         /* for parameter                          */
    j,
    n1,        /* canonical labelling of multiplicities  */
    n2,
    n3,
    n4,
    noGraph;   /* switch variable                        */

for( i = ZERO; i < TUTTEROWS; ++i )
for( j = ZERO; j < TUTTECOLS; ++j )
  {
     tutteMat4[i][j] = ZERO;
  }

/* code the graph for switch value */
noGraph = x12 + 2 * x13 + 4 * x14 + 8 * x23 + 16 * x24 + 32 * x34;

switch( noGraph )
  {
     case 15:
       {  
          n4 = n23;
          n2 = n12;
          n3 = n13;
          n1 = n14;
          break;
       }
     case 23:
       {  
          n3 = n24;
          n2 = n12;
          n1 = n13;
          n4 = n14;
          break;
       }
     case 27:
       {
          n3 = n13;
          n2 = n12;
          n4 = n23;
          n1 = n24;
          break;
       }
     case 29:
       {
          n3 = n14;
          n2 = n12;
          n4 = n24;
          n1 = n23;
          break;
       }
     case 46:
       {
          n1 = n23;
          n2 = n13;
          n3 = n14;
          n4 = n34;
          break;
       }
     case 39:
       {
          n1 = n12;
          n2 = n13;
          n3 = n34;
          n4 = n14;
          break;
       }
     case 43:
       {
          n1 = n34;
          n2 = n13;
          n3 = n12;
          n4 = n23;
          break;
       }
     case 53:
       {
          n4 = n24;
          n2 = n14;
          n3 = n12;
          n1 = n34;
          break;
       }
     case 54:
       {
          n3 = n13;
          n2 = n14;
          n1 = n24;
          n4 = n34;
          break;
       }
     case 57:
       {
          n3 = n34;
          n1 = n12;
          n4 = n23;
          n2 = n24;
          break;
       }
     case 58:
       {
          n3 = n24;
          n1 = n13;
          n4 = n23;
          n2 = n34;
          break;
       }
     case 60:
       {
          n3 = n23;
          n1 = n14;
          n4 = n24;
          n2 = n34;
          break;
       }
     default:
       {
          printf("fourtrianglewithtail\n");
          break;
       }

  }/*end switch*/



/* addd evaluation of triangle with a tail given that n1 is the tail */
/* build tutte poly of n2-n4 three tree deletion of triangle*/

fixedtriangle(n2,n3,n4,
              tutteMat2,
              tutteMat2X);

for( i = ZERO; i < TUTTEROWS; ++i )
for( j = TUTTECOLS - ONE; j > ZERO; --j )
  tutteMat4[i][j]=tutteMat2[i][j - ONE];

if( n1 > ONE )
  matrixspecial(n1,
                tutteMat2,
                tutteMat2X);

for( i = ZERO; i < TUTTEROWS; ++i )
for( j = ZERO; j < TUTTECOLS; ++j )
  tutteMat2[i][j]+=tutteMat4[i][j];

/* minimized storage since mat2 can be sent to fisxedtriangle-only the
    extra multiplication needs another matrix */

return( ONE );

}/*end fourtrianglewithtail*/

/*                                                */
/*                                                */
/*                                                */
/*       end fourtrianglewithtail                 */
/*                                                */
/*                                                */
/**************************************************/
/*                                                */
/*                                                */
/*               start fourcycle                  */
/*                                                */
/*                                                */
/*
Precondition: n12, n13, ..., n34 give multiplicities of edges of
              K(4) described in a canonimcal order for the edges
              x12, x13, ... , x34 indicate the existence of an
              edge 
              arrays tutteMat2 and tutteMat2X hold the current
              status of the computation of a tutte poly

Postcondition: arrays tutteMat2 and tutteMat2X are augmented
               by the tutte poly of a 4-cycle with these 
               nonzero edge multiplicities


Return: 1 to signify the need to replace the graph

*/

int fourcycle(
              int x12,
              int x13,
              int x14,
              int x23,
              int x24,
              int x34,
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
int noGraph,    /* coding switch for graphs               */ 
    n1,         /* edge multiplicities in canonical order */
    n2,
    n3,
    n4;

/* coding graph for switch */
noGraph = x12 + 2 * x13 + 4 * x14 + 8 * x23 + 16 * x24 + 32 * x34;

switch( noGraph )
{
  case 45:
    {  
       n1 = n12;
       n2 = n23;
       n3 = n34;
       n4 = n14;
       break;
    }
  case 51:
    {  
       n1 = n12;
       n2 = n24;
       n3 = n34;
       n4 = n13;
       break;
    }
  case 30:
    {
       n1 = n13;
       n2 = n23;
       n3 = n24;
       n4 = n14;
       break;
    }
  default:
    {
       printf("fourcycle\n");
       break;
    }


  }/* end switch */

/* evaluate four cycle*/


fixedfourcycle(n1,n2,n3,n4,
               tutteMat2,
               tutteMat2X);


return( ONE );

}/*end fourcycle*/

/*                                                */
/*                                                */
/*                                                */
/*               end fourcycle                    */
/*                                                */
/*                                                */
/**************************************************/
/*                                                */
/*                                                */
/*               start fixedfourcycle             */
/*                                                */
/*                                                */

/*
Precondition: n12, n13, ..., n34 give multiplicities of edges of
              K(4) described in a canonimcal order for the edges
              arrays tutteMat2 and tutteMat2X hold the current
              status of the computation of a tutte poly

Postcondition: arrays tutteMat2 and tutteMat2X are augmented
               by the tutte poly of the specific 4-cycle
               with these nonzero edge multiplicities

Return: 1 to signify the need to replace the graph

*/

int fixedfourcycle(
                   int n1,
                   int n2,
                   int n3,
                   int n4,
                   TUTTE tutteMat2,
                   TUTTEO tutteMat2X
                  )

{
int i,      /* for parameter           */
    j,
    k,
    xp,     /* degree of x in monomial */
    yp;     /* degree of y in monomial */


for( i = ZERO; i < n1; i++ )
for( j = ZERO; j < n2; j++ )
for( k = ZERO; k < n3 + n4; k++ )
  {
     xp = ( k == ZERO )?ONE:ZERO;
     yp = i + j + k;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < n1; i++ )
for( j = ZERO; j < n3; j++ )
for( k = ZERO; k < n4; k++ )
  {
     xp =( ( k == ZERO )?ONE:ZERO ) + ( ( j == ZERO )?ONE:ZERO );
     yp = i + j + k;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < n2; i++ )
for( j = ZERO; j < n3; j++ )
for( k = ZERO; k < n4; k++ )

  {
     xp = ( ( i == ZERO )?ONE:ZERO ) + ( ( k == ZERO )?ONE:ZERO ) + ( ( j == ZERO )?ONE:ZERO );
     yp = i + j + k;
     tutteMat2[yp][xp]++;
  }

return( ONE );


}/* end fixedfourcycle */


/*                                                */
/*                                                */
/*                                                */
/*                 end fixedfourcycle             */
/*                                                */
/*                                                */
/**************************************************/
/*                                                */
/*                                                */
/*               start fourtree                   */
/*                                                */
/*                                                */

/*
Precondition: n12, n13, ..., n34 give multiplicities of edges of
              K(4) described in a canonimcal order for the edges
              x12, x13, ... , x34 indicate the existence of an
              edge 
              arrays tutteMat2 and tutteMat2X hold the current
              status of the computation of a tutte poly

Postcondition: arrays tutteMat2 and tutteMat2X are augmented
               by the tutte poly of the tree on four vertices
               with these nonzero edge multiplicities

Return: 1 to signify the need to replace the graph

*/

int fourtree(
             int x12,
             int x13,
             int x14,
             int x23,
             int x24,
             int x34,
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
int graphNo,  /* coding to identify graph               */
    n1,       /* edge multiplicities in canonical order */
    n2,
    n3;

/* code to identify graph for switch */
graphNo = x12 + 2 * x13 + 4 * x14 + 8 * x23 + 16 * x24 + 32 * x34;

switch( graphNo )
  {
     case 7:
       {
          n1 = n12;
          n2 = n13;
          n3 = n14;
          break;
       }
     case 13:
       {
          n1 = n23;
          n2 = n12;
          n3 = n14;
          break;
       }
     case 14:
       {
          n1 = n23;
          n2 = n13;
          n3 = n14;
          break;
       }

     case 19:
       {
          n1 = n13;
          n2 = n12;
          n3 = n24;
          break;
       }

     case 22:
       {
          n1 = n24;
          n2 = n14;
          n3 = n13;
          break;
       }

     case 25:
       {
          n1 = n12;
          n2 = n23;
          n3 = n24;
          break;
       }

     case 26:
       {
          n1 = n13;
          n2 = n23;
          n3 = n24;
          break;
       }

     case 28:
       {
          n1 = n14;
          n2 = n24;
          n3 = n23;
          break;
       }

     case 35:
       {
          n1 = n12;
          n2 = n13;
          n3 = n34;
          break;
       }

     case 37:
       {
          n1 = n12;
          n2 = n14;
          n3 = n34;
          break;
       }

     case 41:
       {
          n1 = n12;
          n2 = n23;
          n3 = n34;
          break;
       }

     case 42:
       {
          n1 = n13;
          n2 = n23;
          n3 = n34;
          break;
       }
     
     case 44:
       {
          n1 = n14;
          n2 = n34;
          n3 = n23;
          break;
       }

     case 49:
       {
          n1 = n12;
          n2 = n24;
          n3 = n34;
          break;
       }

     case 50:
       {
          n1 = n13;
          n2 = n34;
          n3 = n24;
          break;
       }

     case 52:
       {
          n1 = n14;
          n2 = n24;
          n3 = n34;
          break;
       }
     default:
       {
          printf("fourtree\n");
          break;
       }

}/* end switch */

/* now evaluate for the three case depending on the multiple edge parameters */

fourtreefixed(n1,n2,n3,
              tutteMat2,
              tutteMat2X);

return( ONE );

} /* end fourtree */


/*                                                */
/*                                                */
/*                                                */
/*                 end fourtree                   */
/*                                                */
/*                                                */
/**************************************************/
/*                                                */
/*                                                */
/*               start fourtreefixed              */
/*                                                */
/*                                                */

/*
Precondition: n1, n2, n3 give multiplicities of edges of
              tree on four vertices
              arrays tutteMat2 and tutteMat2X hold the current
              status of the computation of a tutte poly

Postcondition: arrays tutteMat2 and tutteMat2X are augmented
               by the tutte poly of a specific tree on four 
               vertices with these nonzero edge multiplicities

Return: 1 to signify the need to replace the graph

*/

int fourtreefixed(
                  int n1,
                  int n2,
                  int n3,
                  TUTTE tutteMat2,
                  TUTTEO tutteMat2X
                 )

{
int i,    /* for parameter           */
    j,
    k,
    xp,   /* degree of x in monomial */
    yp;   /* degree of y in monomial */


for ( i = ZERO; i < n1; i++ )
for ( j = ZERO; j < n2; j++ )
for ( k = ZERO; k < n3; k++ ) 
  {
     xp = ( ( i == ZERO)?ONE:ZERO ) 
                 + ( ( j == ZERO )?ONE:ZERO )
                          + ( ( k == ZERO )?ONE:ZERO );
     yp = i + j + k;
     tutteMat2[yp][xp]++;
  }

return ( ONE );

}/* end four tree fixed */


/*                                                */
/*                                                */
/*                                                */
/*             end fourtreefixed                  */
/*                                                */
/*                                                */
/**************************************************/
/*                                                */
/*                                                */
/*               start fixedtriangle              */
/*                                                */
/*                                                */

/*
Precondition: n1, n2,n3 give multiplicities of edges of
              a triangle described in a canonimcal order for the edges
              arrays tutteMat2 and tutteMat2X hold the current
              status of the computation of a tutte poly

Postcondition: arrays tutteMat2 and tutteMat2X are augmented
               by the tutte poly of a specific triangle 
               with these nonzero edge multiplicities

Return: 1 to signify the need to replace the graph

*/

int fixedtriangle(
                  int n1,
                  int n2,
                  int n3,
                  TUTTE tutteMat2,
                  TUTTEO tutteMat2X
                 )
{
int i,    /* for parameter           */
    j,
    k,
    xp,   /* degree of x in monomial */
    yp;   /* degree of y in monomial */



for ( i = ZERO; i < n2 + n3; i++ )
for ( j = ZERO; j < n1; j++ ) 
  {
     xp = ( i == ZERO )?ONE:ZERO;
     yp = i + j;
     tutteMat2[yp][xp]++;
  }

fixedthreetree(n2,n3,
               tutteMat2,
               tutteMat2X);

return ( ONE );


}/* end fixed thriangle */

/*                                                */
/*                                                */
/*                                                */
/*             end fixedtriangle                  */
/*                                                */
/*                                                */
/**************************************************/
/*                                                */
/*                                                */
/*               start fixedthreetree             */
/*                                                */
/*                                                */


/*
Precondition: n1 and n2 give multiplicities of edges of
              a tree with three vertices 
              arrays tutteMat2 and tutteMat2X hold the current
              status of the computation of a tutte poly

Postcondition: arrays tutteMat2 and tutteMat2X are augmented
               by the tutte poly of a specific three tree
               with these nonzero edge multiplicities

Return: 1 to signify the need to replace the graph

*/

int fixedthreetree(
                   int n1,
                   int n2,
                   TUTTE tutteMat2,
                   TUTTEO tutteMat2X
                  )
{
int i,     /* for parameter           */
    j,
    xp,    /* degree of x in monomial */
    yp;    /* degree of y in monomial */


for ( i = ZERO; i < n1; i++ )
for ( j = ZERO; j < n2; j++ ) 
  {
     xp = ( ( i == ZERO )?ONE:ZERO ) + ( ( j == ZERO )?ONE:ZERO );
     yp = i + j;
     tutteMat2[yp][xp]++;
  }

return ( ONE );

}/* end fixed three tree */



/*                                                */
/*                                                */
/*                                                */
/*          end fixedthreetree                    */
/*                                                */
/**************************************************/



