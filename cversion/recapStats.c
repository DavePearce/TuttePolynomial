
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
/*                  start of recapStats                   */
/*                                                        */

/*

Precondition: g is a copy of the original graph and the arrays
              tutteMat and tuteMatX hold the tutte poly for the
              graph. the global hashtable is also available

Postcondition: nothing is changed but reports are written 

*/


int
recapStats(
           struct graph *g,
           TUTTE tutteMat,
           TUTTEO tutteMatX
          )
{
  
int byteInfo[1000],
    sum,
    suma,
    ctr, 
    i,                         /* for parameter                              */
    j,
    vertDistributiona[10000], 
    hitDistributiona[10000],
    vertDistributionb[10000],
    hitDistributionb[10000],
    noBytesb[10000],
    noBytesa[10000],
    m,
    vertDistribution[10000],
    hitDistribution[10000];
#if(PROFILING_MODE)
/* get some estimates of how the hash table is used */
printf("Number of graphs put into the hash table: %d number graphs looked up = %d\n\n",
            GraphsInHashTable,noGraphsLookedUp);


/*
printf("origNoVert = %d gvnewMax = %d  stackDepthPop = %d  stackDepthPush = %d\n\n",origNoVert,gvnewMax, 500 - stackDepthPop,stackDepthPush);
*/

/* identities to check but probably need gmp */
/*
if( tutteMat[ONE][ZERO] == tutteMat[ZERO][ONE] )
  printf("TEST: tutteMat[1][0] == tutteMat[0][1] passed\n\n");
else
  printf("????tutteMat[1][0] = %lld  tutteMat[0][1] = %lld\n\n",tutteMat[ONE][ZERO],tutteMat[ZERO][ONE]);

//gmpCode(tutteMat,tutteMatX,TUTTEROWS,TUTTECOLS);



if(tutteMat[2][0]-tutteMat[1][1]+tutteMat[0][2]==tutteMat[1][0])
  printf("TEST: tutteMat[2][0]-tutteMat[1][1]+tutteMat[0][2]==tutteMat[1][0] passed\n");
else
  printf("????tutteMat[2][0]-tutteMat[1][1]+tutteMat[0][2]=%lld  tutteMat[1][0]=%lld\n",
  tutteMat[2][0]-tutteMat[1][1]+tutteMat[0][2],tutteMat[1][-0]);
if(tutteMat[3][0]-tutteMat[2][1]+tutteMat[1][2]-tutteMat[0][3]==tutteMat[1][1]-2*tutteMat[0][2]+tutteMat[1][0])
  printf("TEST: tutteMat[3][0]-tutteMat[2][1]+tutteMat[1][2]-tutteMat[0][3]\n ==tutteMat[1][1] - 2*tutteMat[0][2] +tutteMat[1][0] passed\n");
else
  printf("????tutteMat[3][0]-tutteMat[2][1]+tutteMat[1][2] - tutteMat[0][3]=%lld  tutteMat[1][1]-2*tutteMat[ZERO][TWO]+tutteMat[ONE][ZERO]=%lld\n",
  tutteMat[3][0]-tutteMat[2][1]+tutteMat[1][2]-tutteMat[0][3],tutteMat[1][1]-2*tutteMat[0][2]+tutteMat[1][0]);
*/
#if(PROFILING_MODE)
printf("\nLEGEND\n");
printf("zeroentries = # zero terms hashed in overflow matrix\n");
printf("zeroentries1 = # zero terms hashed in coefficient matrix\n (low order digits) represented as long long int\n");
printf("zeroentries2 = # zero terms hashed in coefficient matrix\n (low order digits) represented as int\n");
printf("zeroentries= %d  zeroentries1= %d  zeroentries2 = %d zeroentries2a=%d\n\n",zeroentries,zeroentries1,zeroentries2,zeroentries2a);
printf("NoNonzeroOverflowMatricesInt = %d  NoNonzeroOverflowMatricesLongLongInt = %d\n",
           NoNonzeroOverflowMatricesInt, NoNonzeroOverflowMatricesLongLongInt);
isoend();
printf("\n\n No. Bytes hashed = sizeof(int) * intcount * 10\n\n");


printf(" intcount / 10     No. Bytes        No. Graphs\n");
printf("-------------------------------------------------\n");
for(i = 0; i< 100 ;i++)
if(noBytes[i]!=ZERO)
printf("%8d        %10d     %12d\n",i,40*i,noBytes[i]);
printf("\n\n");

printf("Count of zero entries is larger than the count of sequences of zeroes\n");
printf("as a sequence of three zeroes should be counted once as a sequence of length\n");
printf("three, but will be counted as three zero entries in the total count.\n");
printf("\n");
for(i=0;i<30;i++)backwards[i]=0;
for(i=28;i>1;i--)
{
if(consecutiveZeroesLL[i]!=0)
backwards[i]=consecutiveZeroesLL[i]-consecutiveZeroesLL[i+1];
}
backwards[1]=consecutiveZeroesLL[1];

for(i=1;i<30;i++)
if(backwards[i]!=0)printf("There were %8d occurrences of %8d consecutive zeroes in a ll array\n",
                                 backwards[i],i);
sum=0;
for(i=0;i<30;i++)
sum+=backwards[i];
if(sum>0)printf("Total number of zero sequences = %6d\n",sum);

sum=0;
for(i=0;i<30;i++)
sum+=consecutiveZeroesLL[i];
if(sum>0)printf("Total number of zero entries   = %6d\n",sum);


for(i=0;i<30;i++)backwardsa[i]=0;
for(i=28;i>1;i--)
{
if(consecutiveZeroesInt[i]!=0)
backwardsa[i]=consecutiveZeroesInt[i]-consecutiveZeroesInt[i+1];
}
backwardsa[1]=consecutiveZeroesInt[1];

for(i=1;i<30;i++)
if(backwardsa[i]!=0)printf("There were %8d occurrences of %8d consecutive zeroes in a int array\n",
                                 backwardsa[i],i);

suma=0;
for(i=0;i<30;i++)
suma+=backwardsa[i];
if(suma>0)printf("Total number of zero sequences = %6d\n",suma);

suma=0;
for(i=0;i<30;i++)
suma+=consecutiveZeroesInt[i];
if(suma>0)printf("Total number of zero entries = %6d\n",suma);
sum=0;


for(i=0;i<10000;i++)
{
hitDistribution[i] = ZERO;
vertDistribution[i]=0;
hitDistributiona[i]=0;
vertDistributiona[i]=0;
hitDistributionb[i]=0;
vertDistributionb[i]=0;
}

for(i=0;i<HASHTABLESIZE;i++)
{
if(NEWHash[i].noHits>1000000)printf("HITS TOO BIG!!\n");
hitDistribution[NEWHash[i].noHits]++;vertDistribution[NEWHash[i].noHits]=NEWHash[i].noOldVertices;
}
ctr=0;
sum=0;
for(i=1;i<10000;i++)
if( hitDistribution[i]!=0){ctr++;
                           sum+=i*hitDistribution[i];
                           printf("%4d had %4d hits", hitDistribution[i],i);
                           if(ctr/4*4==ctr)printf("\n");
                          }

printf("\n sum = %d\n",sum);
ctr=0;
for(j=7;j<numVertices(g);j++)
{
printf("Number of hits for graphs with %2d vertices\n",j);
printf("-------------------------------------------\n");
sum=0;
suma=0;
ctr=0;
for(i=0;i<10000;i++)
{
if(hitDistribution[i]!=0 && vertDistribution[i]==j)
  { ctr++;
   printf("%8d",
      hitDistribution[i],j);
   sum+=hitDistribution[i];
   if(ctr/7*7==ctr)printf("\n");
  }
}
printf("\n");
if(sum!=0)printf("SUM FOR %d vertex graphs is %d\n",j,sum);
}

printf("the first table counts the number of hashed graphs \n");
printf("while the second counts the number of hashed graphs \n");
printf("that were hit. The third table gives information for\n");
printf("graphs that have gv =gvnew\n");
printf("\n");
sum=0;
ctr=0;
for(i=5;i<=origNoVert;i++)
{

for(m=0;m<10000;m++){
                     noBytes[m]=0;
                     noBytesa[m]=0;
                     noBytesb[m]=0;
                    }

for(j=0;j<HASHTABLESIZE;j++)
{


if(NEWHash[j].noOldVertices==i &&NEWHash[j].noHits!=0 &&( NEWHash[j].noOldVertices==NEWHash[j].noNewVertices))
  {
   noBytesb[NEWHash[j].bytesStored]++;
  }
if(NEWHash[j].noHits!=0 && NEWHash[j].noOldVertices==i)
  {
    suma++;
    noBytesa[NEWHash[j].bytesStored]++;
  }
if(NEWHash[j].hash_addr!=0 && NEWHash[j].noOldVertices==i)
  {
  noBytes[NEWHash[j].bytesStored]++;sum++;
  }
} /* end j loop */
printf("\n        hash_addr !=0                 noHits != 0                    gv=gvnew\n");
printf(" RECAP FOR %2d vertices:       RECAP for %2d vertices       RECAP for %2d vertices\n",i,i,i);
printf("Num. Bytes:  Num. Graphs:   Num. Bytes:  Num. Graph:   Num. Bytes:  Num. Graph: \n");
for(m=0;m<10000;m++)
{
if(noBytes[m]>0)
{
printf("%7d %10d ",40*m,noBytes[m]);
}
else
{
if(noBytes[m]==0 &&(noBytesa[m]!=0 || noBytesb[m]!=0))printf("                     ");
}

if(noBytesa[m]>0)
{
printf("         %7d %10d ", 40 * m, noBytesa[m]);
}
else
if((noBytes[m]!=0 || noBytesb[m]!=0) && noBytesa[m]==0)printf("                      ");

if(noBytesb[m]>0)
{
printf("         %7d %10d \n",40*m,noBytesb[m]);
}
else
if(noBytes[m]!=0 || noBytesa[m]!=0)printf("\n");

}/* output looop */

}/* origNoVert loop */
printf("sum = %d : number of graphs in the hash table\n",sum);
printf("sum = %d : number of graphs in the hash table with a hit\n",suma);
#endif





printf("\n\n");
#endif
} /* end main */

/*                                                               */
/*                       end main                                */
/*                                                               */
/*****************************************************************/
/*                                                               */









                                            




