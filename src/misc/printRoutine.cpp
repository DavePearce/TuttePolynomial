#include "core/tutte.h"
#include<stdio.h>
#include <memory.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
//#include <gmp.h>
FILE *filec;


/*****************************************************************/
/*                                                               */
/*                      start printTutte                         */
/*                                                               */

/* 
Precondition: arrays tutteMat and tutteMatX that hold the reuslt 
              of the computation
         

Postcondition: nothing changed

SideEffect: the tutte poly represented by the values in the arrays is
            displayed using the global dimensions TUTTEROWS and TUTTECOLS

*/

void printTutte(TUTTE tutteMat,TUTTEO tutteMatX)
{


/*mpz_t x6a,x5a,x4a,x1a,x2a,x3a, check1, check2, check3, check4,check5,check6,one,
check1a,check2a,check3a,check4a,check5a,check6a,check7a,check7,
check8,check8a,sumpowers2,exponsum,conversionpowers2,tempsum,
sum1aa,sum1a,sum2a,sum3a,sum4a,sum5a,sum6a,sum8a,sum7a,edges,
constanttwo,totalsuma,totalsum1a,totalsum2a,totalsumb,edgetotwo;
*/
int /*x,
    y,*/
    spot1,
    intsum1a,intsum2a,
    spot2,
    /*stop,
    stop2,*/
    spot,
    i, 
    j;
char *piex;
long long int trial,
              stmax,
              stmax1,
              exponsuma,
              two,
              oneconstant;
TUTTEMATCH st,
           st2,
           x1,
           x2,
           x3,
           x4,
           x5,
           x6,
           x7,
           x8,
           x9,
           x10;
TUTTEOMATCH st1;
//printf("printRoutine\n");
/* doesn't handle printing of (x+y)^n right-leading zeroes--*/
two = TWO;
oneconstant = ONE;
spot = ZERO;
spot2 = ONE;
for( i = TUTTEROWS - ONE; i >= ZERO; i-- )
for( j = TUTTECOLS - ONE; j >= ZERO; j-- )
  if( tutteMat[i][j] != ZERO )
    if( spot2 == ONE )
      {
         spot = i;
         spot2 = ZERO;
      }

spot1 = ONE;

 printf("                                                ");
for( i = ZERO; i <= spot; ++i )
  {/* 1 */
     for ( j = ZERO ;j < TUTTECOLS; ++j )
       {/*2 */
      if( ( tutteMatX[i][j] != ZERO ) || ( tutteMat[i][j] != ZERO) )                 
            {
               ++spot1;
               if( tutteMatX[i][j] == ZERO )
                 {
                   if( ( i == ZERO ) && ( j != ZERO ) )
                     {
                        printf("                 %+18lld * x^%3d         ",
                         tutteMat[i][j],j);
                     }
                   else
                     if( ( i != ZERO ) & ( j == 0 ) )
                       {
                         printf("                 %+18lld *         y^%3d ",
                         tutteMat[i][j],i);
                       }
                     else
                       if( ( i != ZERO ) && ( j !=  ZERO ) )
                         {
                            printf("                 %+18lld * x^%3d * y^%3d ",
                             tutteMat[i][j],j,i);
                         }
                 }
            
else

if( tutteMatX[i][j] != ZERO )
{

if( ( i == ZERO ) && ( j != ZERO ) )
{
                            printf("%+18lld%017lld * x^%3d          ",
                             tutteMatX[i][j],tutteMat[i][j],j);

}
else
if( ( i != ZERO ) &&  ( j == ZERO ) )
{

                            printf("%+18lld%017lld *         y^%3d ",
                             tutteMatX[i][j],tutteMat[i][j],i);

}
else
if( ( i != ZERO ) && ( j != ZERO ) )
{

                            printf("%+18lld%017lld * x^%3d * y^%3d ",
                             tutteMatX[i][j],tutteMat[i][j],j,i);


}
}/* tutteMatX[i][j]!=0 */
}/* tutteMatX[i][j]!=0 || tutteMat[i][j]!=0 */
           if( spot1 == TWO )
             {
               spot1 = ZERO;
               printf("\n");
            }
          
       
       }/* 2*/
         /* if it gets here and only put 1 on line didn't advance from spot1==2 in loop*/
     if( spot1 == ONE )
       {
          spot1 = ZERO;
          printf("\n");
       }
/*     else
      {
        spot1 = ZERO;
        printf("\n");
    } */ 
  }/*i*/

st1 = ZERO;
st2 = ZERO;
st = ZERO;
//printf("testNo=%lld\n",testNo);
for( i = ZERO; i < TUTTEROWS; ++i )
for( j = ZERO; j < TUTTECOLS; ++j )
  {
       st2 += tutteMatX[i][j];
       st += tutteMat[i][j];
     while( st >= testNo )
       { //printf("st=%lld\n",st);
          st -= testNo;
          ++st2;
       }
  }
//printf("st2=%d       st=%lld\n",st2,st);
printf("\n");
if( st2 != ZERO )
  {
     printf("Number of spanning trees:  %20lld%017lld\n",st2,st); 
  }
else
  {
     printf("Number of spanning trees: st = %20lld \n",st);
  }
/*

printf("\n");
if( tutteMat[1][0] == tutteMat[0][1] )
  printf("TEST: tutteMat[1][0]==tutteMat[0][1] passed\n");
else
  printf("????tutteMat[1][0]=%lld  tutteMat[0][1]=%lld\n",tutteMat[ONE][ZERO],tutteMat[ZERO][ONE]);

  if(tutteMat[1][0] == tutteMat[0][1])
printf("TEST: tutteMat[1][0]==tutteMat[0][1] passed\n");
else
  printf("????tutteMat[1][0]=%lld  tutteMat[0][1]=%lld\n",tutteMat[ONE][ZERO],tutteMat[ZERO][ONE]);

if(tutteMat[2][0]-tutteMat[1][1]+tutteMat[0][2]==tutteMat[1][0])
  printf("TEST: tutteMat[2][0]-tutteMat[1][1]+tutteMat[0][2]==tutteMat[1][0] passed\n");
else
  printf("????tutteMat[2][0]-tutteMat[1][1]+tutteMat[0][2]=%lld  tutteMat[1][0]=%lld\n",
  tutteMat[2][0]-tutteMat[1][1]+tutteMat[0][2],tutteMat[1][-0]);

if(tutteMat[3][0]-tutteMat[2][1]+tutteMat[1][2]-tutteMat[0][3]==tutteMat[1][1]-2*tutteMat[0][2]+tutteMat[1][0])
  printf("TEST: tutteMat[3][0]-tutteMat[2][1]+tutteMat[1][2]-tutteMat[0][3]\n        ==tutteMat[1][1] - 2*tutteMat[0][2] +tutteMat[1][0] passed\n");
else
  printf("????tutteMat[3][0]-tutteMat[2][1]+tutteMat[1][2] - tutteMat[0][3]=%lld  tutteMat[1][1]-2*tutteMat[ZERO][TWO]+tutteMat[ONE][ZERO]=%lld\n",
  tutteMat[3][0]-tutteMat[2][1]+tutteMat[1][2]-tutteMat[0][3],tutteMat[1][1]-2*tutteMat[0][2]+tutteMat[1][0]);

printf("\n");
*/
}/* end of printTutte */



/*                                                               */
/*                       end printTutte                          */
/*                                                               */
/*****************************************************************/

















                                            




