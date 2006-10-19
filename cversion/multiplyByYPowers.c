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
/*                         start of matrixspecial                          */
/*                                                                         */

/*

Preconditon: n13 is the power of number of consecutive terms above an 
             entry in tutteMat1 that must be added to the current location 
             arrays tutteMat1 and tutteMat1X are the current state of the 
             computation for some graph

Postcondition: arrays tutteMat1 and tutteMat1X are appropriately augmented

*/

int 
matrixspecial(
              short int n13,
              TUTTE tutteMat1,
              TUTTEO tutteMat1X
             )

{

int i,          /* for parameter and array indices  */
    j,
    m;
TUTTEMATCH sum; /* accumulator of type TUTTEMATCHu  */
//printf("try the other powers\n");
/* DEALS WITH TOTAL NUMBER OF EDGES */

for ( j = TUTTEROWS - ONE; j >= ONE; --j )
for ( i = ZERO; i < TUTTECOLS; ++i )
  {
     sum = ZERO;
     m = j - n13 + ONE; // only difference from matrixspecial1
     if ( m < ZERO )
       {
          m = ZERO;
       }
     for ( ; m < j; ++m )
       sum += tutteMat1[m][i];
     tutteMat1[j][i] = sum;
  }

assert( sum <= testNo );
assert( sum >= ZERO );

for ( i = ZERO; i < TUTTECOLS; ++i )
  tutteMat1[ZERO][i] = ZERO;

}/* end matrixspecial */


/*                                                                         */
/*                         start of matrixspecial                          */
/*                                                                         */
/***************************************************************************/
/*                                                                         */
/*                         start of matrixspecial1                         */
/*                                                                         */


/*
Preconditon: n13 is the power of number of consecutive terms above an 
             entry in tutteMat1 that must be added to the current location 
             nonzerocolumn indicates the last nonzero column in one of the matrices
             while columnBottom indicates the last nonzero entry in a column and
             nonzerorow indicates the last row with a nonzero entry
             arrays tutteMat1 and tutteMat1X are the current state of the 
             computation for some graph--box in the computation

Postcondition: arrays tutteMat1 and tutteMat1X are appropriately augmented

*/

int 
matrixspecial1(
               int nonzeroColumn,
               int columnBottom[],
               int nonzeroRow,
               short int n13,
               TUTTE tutteMat1,
               TUTTEO tutteMat1X
              )
{
int i,             /* for parameter and index for array  */
    j,
    k,
    m;
TUTTEMATCH sum;    /* accumulator of type TUTTEMATCH     */

/* DEALS WITH NUMBER OF MULTIPLE EDGES */
for ( i = ZERO; i <= nonzeroColumn; ++i )
for ( j = nonzeroRow+columnBottom[i]; j >= ONE; --j )
  {
     sum = ZERO;
     m = j - n13;
     if ( m <  ZERO )
       {
          m =  ZERO;
       }
     for ( ; m < j; ++m )
       sum += tutteMat1[m][i];
     tutteMat1[j][i] = sum;
     while( tutteMat1[j][i] >= testNo )
       {
          tutteMat1[j][i] = tutteMat1[j][i] - testNo;
          ++tutteMat1X[j][i];
       }
     assert( tutteMat1[j][i] <= testNo );
  }

for ( k = ZERO; k <= nonzeroColumn; ++k )
  tutteMat1[ZERO][k] = ZERO;


}/* end matrixspecial1 */

/*                                                                         */
/*                         start of matrixspecial1                         */
/*                                                                         */
/***************************************************************************/
/*                                                                         */
/*                         start of matrixspecial1a                        */
/*                                                                         */


/*
Preconditon: n13 is the power of number of consecutive terms above an 
             entry in tutteMat1 that must be added to the current location 
             nonzerocolumn indicates the last nonzero column in one of the matrices
             while columnBottom indicates the last nonzero entry in a column and
             nonzerorow indicates the last row with a nonzero entry
             arrays tutteMat1 and tutteMat1X are the current state of the 
             computation for some graph--box in the comutation

Postcondition: arrays tutteMat1 and tutteMat1X are appropriately augmented

*/



matrixspecial1a(
                int nonzeroColumn,
                int columnBottom[],
                int nonzeroRow,
                short int n13,
                TUTTE tutteMat1,
                TUTTEO tutteMat1X
              )

{
int i,            /* for parameter and array indices         */
    j,
    m;
TUTTEOMATCH sum;  /* accumulator of type TUTTEOMATCH         */
    
for ( i = 0; i <= nonzeroColumn; ++i )
for ( j = nonzeroRow + columnBottom[i]; j >= ONE; --j )
  {
     sum = ZERO;
     m = j - n13;
     if ( m <  ZERO )
       {
          m = ZERO;
       }
     for ( ; m < j; ++m )
       sum += tutteMat1X[m][i];
     tutteMat1X[j][i] = sum;
  }

for ( i = ZERO; i <= nonzeroColumn; ++i )
  tutteMat1X[ZERO][i] = ZERO;

}/* end matrixspecial1a */


/*                                                                         */
/*                         start of matrixspecial1a                        */
/*                                                                         */
/***************************************************************************/






