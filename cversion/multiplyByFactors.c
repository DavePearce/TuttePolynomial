#include <assert.h>
#include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/***********************************************/
/*                                             */
/*             start of mtwo4                  */
/*                                             */

/*
Precondition: a graph at g, the arrays tutteMat and tutteMatX that hold the
              current status of the computation, tutteMat1 and tutteMat1X 
              that hold the comutation of some separately computed tutte
              poly, and two global graph parameters-the number of vertices
              of degrees one and two that have been deleted and must now
              have their contribution made (in some cases these values
              are redundant because of g but in other cases they are not the
              current values for g)

Postcondition: the arrays tutteMat1 and tutteMat1X as well as the parameters
               gminusone and gminustwo are incorporated into tutteMat and
               tutteMatX

*/


void 
multiplyByFactors(
                  struct graph *g,
                  TUTTE tutteMat,
                  TUTTEO tutteMatX,
                  TUTTE tutteMat1,
                  TUTTEO tutteMat1X,
                  int gminusone,
                  int gminustwo
                 )
{
int i,                                   /* for parameter                            */
    j,
    k,
    m,
    x,
    NoSeqs,                              /* number of entries in multCount           */
    lastnonzeroRowinColumn[VERTEXSIZE],  /* array to hold location of last nonzero 
                                            row in a column                          */  
    runup,                               /* column number for adjustment due 
                                            to accumulated multCount values          */
    lastnonzeroColumn,                   /* index of last nonzero column             */    
    lastnonzeroRow,                      /* index for last nonzero row               */ 
    zerosignal2,                         /* indicators about entry in high order 
                                            digit array                              */ 
    zerosignal1,
    zerosignal;
TUTTE 
      tutteMat2;
TUTTEO tutteMat4;

//printf("multiplyByFactors\n");

/*                                            */
/* find out if tutteMat1X has a nonzero entry */
/*                                            */
zerosignal= ZERO;
for( i = ZERO; i < TUTTEROWS; i++ )
  {
     for( j= ZERO; j < TUTTECOLS; j++ )
       {
          if( tutteMat1X[i][j] != ZERO )
            {
               zerosignal = ONE;
               break;
            }
       }
     if( zerosignal )
       {
          break;
       }
  }

/*                                                 */
/* find last row and last column with a nonzero    */
/* entry so that you can avoid adding some zeroes  */
/*                                                 */  
lastnonzeroRow = MINUSONE;
for( i = TUTTEROWS - ONE; i >= ZERO; i-- )
  {
     for( j = TUTTECOLS - ONE; j >= ZERO; j-- )
       {
          if( ( tutteMat1[i][j] != ZERO ) || ( tutteMat1X[i][j] != ZERO ) )
            {   
               lastnonzeroRow = i;
               break;
            }
       }
     if( lastnonzeroRow >= ZERO )
       break;
  }

lastnonzeroColumn = MINUSONE;
for( i = TUTTECOLS - ONE; i >= ZERO; i-- )
  {
     for( j = TUTTEROWS - ONE; j >= ZERO; j-- )
       {
          if( ( tutteMat1[j][i] != ZERO ) || ( tutteMat1X[j][i] != ZERO ) )
            {   
               lastnonzeroColumn = i;
               break;
            }
       }
     if( lastnonzeroColumn >= ZERO )
        {
           break;
        }
  }

/*                                             */
/* multiply current tutte poly by a power of x */
/*                                             */
if( gminusone > ZERO )
  { 
     for ( i = lastnonzeroColumn + gminusone ; i >= gminusone; --i )
     for ( j = ZERO; j <= lastnonzeroRow; ++j )
       {
          tutteMat1[j][i] = tutteMat1[j][i - gminusone];
          tutteMat1X[j][i] = tutteMat1X[j][i - gminusone];
       } 
     /* zero out the columns to the left of column gminusone */ 
     for ( i = gminusone - ONE; i >= ZERO; --i )
     for ( j = ZERO; j <= lastnonzeroRow/* TUTTEROWS*/; ++j )
       {
          tutteMat1[j][i] = ZERO;
          tutteMat1X[j][i] = ZERO;
       }
  }  


/*                                             */
/* multiply current tutte poly by some number  */
/* of powers of y                              */
/*                                             */
if( getYPower(g)  > ZERO)
  {

     /* shift everything down (*g).yPower rows */
     for( j = ZERO; j <= lastnonzeroColumn + gminusone; ++j )
     for( i = lastnonzeroRow + getYPower(g); i >= getYPower(g); --i )
       {
          tutteMat1[i][j] = tutteMat1[i - getYPower(g)][j];
          tutteMat1X[i][j] = tutteMat1X[i - getYPower(g)][j];
       }

     for( j = ZERO; j <= lastnonzeroColumn + gminusone; ++j )
     for( i = ZERO; i < getYPower(g); ++i )
       {
           tutteMat1[i][j] = ZERO;
           tutteMat1X[i][j] = ZERO;
       }
  }

/*                                             */
/* multiply current tutte poly by some number  */
/* of factors of the form (x + 1)              */
/*                                             */
zerosignal1 = ZERO;
if( gminustwo > ZERO )
  {
     for( i = ONE; i <= gminustwo; i++ )
       {
          for( j = lastnonzeroColumn + gminusone + i; j >= ONE; j-- )
          for( k = lastnonzeroRow + getYPower(g); k >= ZERO; k--  )
            {
               tutteMat1X[k][j] += tutteMat1X[k][j - ONE];
               tutteMat1[k][j] += tutteMat1[k][j - ONE];
               while( tutteMat1[k][j] >= testNo )
                 {  
                    tutteMat1[k][j] -= testNo;
                    ++tutteMat1X[k][j];
                    /* need to know if the overflow
                       matrix has a nonzero entry   */
                    zerosignal1 = ONE;
                 }
            }
       }

  }/* end gminustwo if */
/* preset this variable so the final evaluation can be efficient */
runup = ZERO;

/*                                               */
/* multiply tutte poly by some number of factors */
/* of the form x + y + y^2 + y^3 + ... + y^n     */
/*                                               */
if( getMultCount(g, ZERO) > ZERO )
  {

     NoSeqs = getMultCount(g, ZERO);
     /*                                                */
     /* find the last non=zero entry in each column    */
     /* to avoid unnecessary summing of a bunch of 0's */
     /*                                                */ 
     for( i = lastnonzeroColumn + gminusone + gminustwo; i >= ZERO; i-- )
       {
          lastnonzeroRowinColumn[i] = MINUSONE;
          for( j = TUTTEROWS - ONE; j >= ZERO; j-- )
            {
                if( ( tutteMat1[j][i] != ZERO ) || ( tutteMat1X[j][i] != ZERO ) )
                  {
                     lastnonzeroRowinColumn[i] = j;
                     break;
                  }
            }
       }
     runup = ZERO;

     for ( i = ONE; i <= NoSeqs; ++i )
       {
          runup += getMultCount(g, i);
          zerosignal2 = ZERO;

          if( zerosignal || zerosignal1 ) 
            matrixspecial1a(
                            lastnonzeroColumn + gminusone + gminustwo,
                            lastnonzeroRowinColumn,
                            getYPower(g) + runup,     
                            getMultCount(g, i),
                            tutteMat1,
                            tutteMat1X
                           );
 
          matrixspecial1(
                         lastnonzeroColumn + gminusone + gminustwo,
                         lastnonzeroRowinColumn,
                         getYPower(g) + runup,
                         getMultCount(g, i),
                         tutteMat1,
                         tutteMat1X
                        );
           
       } /* end of i loop */
  }/* end of if */

/*                                          */
/* contribute the result of the computation */
/* to the final answer                      */
/*                                          */

if( runup == ZERO )
{
/* need two cases because runup > 0
   incorporates information computed in
   the loop runup = ZERO signifies was
   not entered
*/
for( i = ZERO; i <= lastnonzeroRow + getYPower(g); ++i )
for( j = ZERO; j <= lastnonzeroColumn + gminusone + gminustwo ; ++j )
  {
     if( tutteMat1[i][j] != ZERO )
       tutteMat[i][j] += tutteMat1[i][j];
     if( tutteMat1X[i][j] != ZERO )
       tutteMatX[i][j] += tutteMat1X[i][j];
     while( tutteMat[i][j] >= testNo )
       {
          tutteMat[i][j] -= testNo;
          ++tutteMatX[i][j];
       }
  }
}
else
if( runup > ZERO)

{

for( j = ZERO; j <= lastnonzeroColumn + gminusone + gminustwo; ++j )
for( i = ZERO; i <= lastnonzeroRowinColumn[j] + runup + getYPower(g); ++i )
  {
     if( tutteMat1[i][j] != ZERO )
       tutteMat[i][j] += tutteMat1[i][j];
     if( tutteMat1X[i][j] != ZERO )
       tutteMatX[i][j] += tutteMat1X[i][j];
     while( tutteMat[i][j] >= testNo )
       {
          tutteMat[i][j] -= testNo;
          ++tutteMatX[i][j];
       }

  }

}
} /* end mtwo4 */

/*             end of mtwo4                    */
/*                                             */
/***********************************************/





