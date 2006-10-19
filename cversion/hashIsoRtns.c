#include <limits.h>
#include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
 /* limits.h defines a very small integer and a very 
small long long integer value
the names are
INT_MIN
LLONG_MIN
these two values are used in the packing routine to 
ize constants for long long
 */
/*
#define LLONG_MIN    (-9223372036854775807LL-1LL)
#define LLONG_MAX    9223372036854775807LL
#define ULLONG_MAX    18446744073709551615ULL
*/



/* Need to consider not opening a file 
in the isolookup
hash routines-open and close
 before deleteContract gets called--
 isoinit seems to be a number of functions-loading 
 after flushing as well as initializing w+ and a+ files
 
/* INT_MIN is a very large negative integer */
/* assuming first zero is the end of a line-probably should use INT_MIN */
/* GLOBALS */



/* hashing code */

/**********************************************/
/*                                            */
/*           start of hashinit                */
/*                                            */

void 
hashinit()



  /*  NEWhash[i] is ZERO if no data 
      hashes to i. otherwise
	it is an index into the array of structures NEWhash  */
{
/* changed to ZERO since a pointer is now stored */

  memset(NEWHash,  ZERO, HASHTABLESIZE * sizeof(NEWHash[0]));


}/* end of hashinit */

/*                                            */
/*           end of hashinit                  */
/*                                            */
/**********************************************/
/*                                            */
/*           start of hashvalue               */
/*                                            */

unsigned int 
hashvalue(
          int *h,/*JUST CNAONG */
          int n
         )
{
  int i;
  int x = 0;
  /* go through array doing rotates (left shift/OR combo) and adds */
  for (i = 0; i < n; ++i)
    if (x < 0)
      x = x + ((x << 1) ^ 1 + h[i]);  /* rotate: left bit was 1 */
    else
      x = (x << 1) + h[i];
      
  return (unsigned int) (x);
} /* end hashvalue */

/*                                            */
/*           end of hashvalue                 */
/*                                            */
/**********************************************/
/*                                            */
/*           start of hashinsert              */
/*                                            */

void 
hashinsert(
           unsigned int *p,
           unsigned long int hash,
           int gv,
           int gvnew, 
           int noByte
          )
{
  int hashindex = hash % HASHTABLESIZE;
  int hashstep;

  int *q;
  int v = ((unsigned  int) p[ZERO]) >> ONE;

  /* assume p is not in hashtable (otherwise will have duplicates) */

  while (NEWHash[hashindex].hash_addr)
    {
      hashstep = hash % 32 + 1; // presumes few collisions 
      hashindex = (hashindex + hashstep) % HASHTABLESIZE;
    }
  NEWHash[hashindex].hash_addr = (unsigned long int) p;

#if(PROFILING_MODE)
NEWHash[hashindex].noNewVertices=gvnew;
NEWHash[hashindex].noOldVertices= gv;
NEWHash[hashindex].bytesStored = noByte;
NEWHash[hashindex].blockNumber = currentblock;
#endif
  return;
} /* end  */


/*                                            */
/*           end of hashinsert                */
/*                                            */
/**********************************************/
/*                                            */
/*           start of hashlookup              */
/*                                            */


int 
* hashlookup(
             int gv,
             int gvnew,
             int canong[],
             unsigned  long int hash,
             int w
            )
{
  int hashstep,i;
  int hashindex = hash % HASHTABLESIZE;
  int *cp;
/* do not look at tutteMat or tutteMatX here-only at canong */
/* canong now starts at cp[FIVE] because of packing and bigSignal */

while(cp = (int *)NEWHash[hashindex].hash_addr)


  {
     if( (gv != ( int) cp[ZERO])||(gvnew!=( int)cp[ONE])
          || (memcmp(&(cp[FIVE]),canong,w*sizeof(int))))
       {
         hashstep = hash % 32 + 1; 
	 hashindex =  
            (hashindex + hashstep) % HASHTABLESIZE;
       }
     else 
       {
NEWHash[hashindex].noHits++;
         return cp;
       }
  } 
  /* Not FOUND */
return ZERO;

} /* end hashlookup */

/*                                            */
/*           end of hashlookup                */
/*                                            */
/**********************************************/
/*                                            */
/*           start of isolookup               */
/*                                            */


int 
isolookup(
          struct graph *h,
          int canong[],
          unsigned long int *hash,
          TUTTE tutteMat,
          TUTTEO tutteMat1
         )
{/* start isolookup */
int gvnew,i,j,k;
  int gv /*= (*h).v*/;
  int w /*= computeNumwords(gvnew)*/; /* words in canong */
  int * cp,x;
TUTTEOMATCH packed[15000],packeda[15000];
TUTTEMATCH packed1[15000];
int packed2[15000];
gv=(*h).v;
gvnew=(*h).vnew;

w=computeNumwords(gvnew);
  *hash = hashvalue(canong, w);

for(i=ZERO;i<TUTTEROWS;i++)
for(j=ZERO;j<TUTTECOLS;j++)
{
tutteMat[i][j]=ZERO;
tutteMat1[i][j]=ZERO;
}
  cp = hashlookup(gv,gvnew, canong, *hash, w);

/* true means found in hash table */
if (cp)
  {
#if(PROFILING_MODE)
noGraphsLookedUp++;
++match[gv];  
  if(gv==gvnew) ++matchcount[gv]; 
  if(gv!=gvnew)++matchcount1[gvnew];
 if (gv!=gvnew)++matchcount2[gv];
gvBYgvnew[gv][gvnew]++;
#endif
if(cp[THREE]> ZERO && cp[FOUR])
      {      
         memcpy(packed,&cp[w+FIVE],cp[THREE]*sizeof(TUTTEOMATCH));
         k=MINUSONE;
         j=ZERO;
           for(i=ZERO;i<cp[THREE];i++)
             {
                if(packed[i]>=ZERO)
                  {
                     tutteMat1[j][++k]=packed[i];
                  }
                else
               if(packed[i]<0 && packed[i]!=LLONG_MIN )
                  {
                     tutteMat1[j][++k]=-packed[i];
                     ++j;
                     k=MINUSONE;
                  }
               else 
                 if (packed[i]==LLONG_MIN)
                 {
                    tutteMat1[j][0]=0;
                    ++j;
                    k=MINUSONE;
                 }
             }
        memcpy(packed1,&cp[w+FIVE+sizeof(TUTTEOMATCH)/sizeof(int)*cp[THREE]],
                       cp[TWO]*sizeof(TUTTEMATCH));
        j=ZERO;
        k=MINUSONE;
        for(i = ZERO; i < cp[TWO]; i++)
          {
            if(packed1[i] >= ZERO)
              {
                 tutteMat[j][++k]=packed1[i];
              }
            else
             if((packed1[i] < ZERO) && (packed1[i] != LLONG_MIN))
              {
                 tutteMat[j][++k]=-packed1[i]; 
                 ++j;
                 k=MINUSONE;
              }

           else
            if(packed1[i]==LLONG_MIN)
            {

                 tutteMat[j][0]=0; 
                 ++j;
                 k=MINUSONE;
            }

          } 
     } 

      if(cp[THREE]>0&&!cp[FOUR])
        {
         memcpy(packed,&cp[w+FIVE],cp[THREE]*sizeof(TUTTEOMATCH));
         k=MINUSONE;
         j=ZERO;
           for(i=ZERO;i<cp[THREE];i++)
             {
                if(packed[i]>=ZERO)
                  {
                     tutteMat1[j][++k]=packed[i];
                  }
                else
               if(packed[i]<0 &&packed[i]!=LLONG_MIN)
                  {
                     tutteMat1[j][++k]=-packed[i];
                     ++j;
                     k=MINUSONE;
                  }
                else if( packed[i]==LLONG_MIN)
                 {
                    tutteMat1[j][0]=0;
                    ++j;
                    k=MINUSONE;
                 }
                
             }
           memcpy(packed2,
                  &cp[w+FIVE+sizeof(TUTTEOMATCH)/sizeof(int)*cp[THREE]],
                  cp[TWO]*sizeof(int));
           j=ZERO;
           k=MINUSONE;
           for(i=ZERO;i<cp[TWO];i++)
             {
                if(packed2[i]>=ZERO)
                  {
                     tutteMat[j][++k]=packed2[i];
                  }
                else
                 if(packed2[i]<0&& packed2[i]!=INT_MIN)
                  {
                     tutteMat[j][++k]= -packed2[i]; 
                     ++j;
                     k=MINUSONE;
                  }
              else
               if(packed2[i]==INT_MIN)
               {

                     tutteMat[j][0]= 0; 
                     ++j;
                     k=MINUSONE;
              }
             } 


        }
if((cp[THREE] == ZERO) && (cp[FOUR]))
      {     
        memcpy(packed1,&cp[w+FIVE],cp[TWO]*sizeof(TUTTEMATCH));
        j=ZERO;
        k=MINUSONE;
        for(i=ZERO;i<cp[TWO];i++)
          {
            if(packed1[i]>=ZERO)
              {
                 tutteMat[j][++k]=packed1[i];
              }
            else
               if(packed1[i]< ZERO && packed1[i]!=LLONG_MIN)
                  {
                     tutteMat[j][++k]=-packed1[i];
                     ++j;
                     k=MINUSONE;
                  }
                else
                   if( packed1[i]==LLONG_MIN)
                 {
                    tutteMat[j][0]=0;
                    ++j;
                    k=MINUSONE;
                 }
      }
   }
      if(cp[THREE] == ZERO && !cp[FOUR])
        {
           memcpy(packed2,&cp[w+FIVE],cp[TWO]*sizeof(int));
           j=ZERO;
           k=MINUSONE;
           for(i=ZERO;i<cp[TWO];i++)
             {
                if(packed2[i]>=ZERO)
                  {
                     tutteMat[j][++k]=packed2[i];
                  }
                else
                  if(packed2[i] < ZERO && packed2[i] != INT_MIN)
                  {
                     tutteMat[j][++k] = -packed2[i]; 
                     ++j;
                     k = MINUSONE;
                  }
               else
                if(packed2[i] == INT_MIN)
                 {
                    tutteMat[j][0] = ZERO;
                    ++j;
                    k = MINUSONE;
                 }
             } 
     } 

    return (ONE);
  }
else
  {
    return (ZERO);
  }
} /* end isolookup */

/*                                            */
/*           end of isolookup                 */
/*                                            */
/**********************************************/
/*                                            */
/*           start of isoadd                  */
/*                                            */

/*
Precondition:

Postcondition:

*/

int 
isoadd(
       int gv,
       int gvnew,
       int canong[],
       unsigned long int hash,
       TUTTE tutteMat,
       TUTTEO tutteMatX
      )
{
     TUTTEOMATCH nonzeroentry[700],packeda[15000],packed[15000];
     TUTTEMATCH biggest,biggest1,packed1[15000];
int packed2[15000];
int i, 
    j, 
    k,
    kROWS,
    kROWS1, 
    noByte,
    entries, 
    zeroSig,
    bigSignal,
    sum,
    bytecount, 
    intcount, 
    totalpacked,
    totalpacked1,
    *cp,
    test,
    m,
    m1;
int L1;

zeroSig = ZERO;
for(i = ZERO; i < TUTTEROWS; ++i)
  {
    for(j = ZERO; j < TUTTECOLS; ++j)
      {
         if(tutteMatX[i][j] != ZERO)
           {
              zeroSig = ONE;
              /*goto L1;*/break;
           }
      }
    if(zeroSig)break;
  }
/*L1:*/

biggest=ZERO;
biggest1=ZERO;
for(i=0;i<TUTTEROWS;++i)
for(j=0;j<TUTTECOLS;++j)
{
  if (tutteMat[i][j]>biggest)
    biggest=tutteMat[i][j];

  if (tutteMatX[i][j]>biggest1)
    biggest1=tutteMatX[i][j];
}
if(biggest>=BILLION)
  bigSignal=1; 
else 
  bigSignal=0;

#if(PROFILING_MODE)
if(biggest1<BILLION&&biggest1!=ZERO)
++NoNonzeroOverflowMatricesInt;
if(biggest1<BILLION&& biggest1> ZERO)

++NoNonzeroOverflowMatricesLongLongInt;
#endif
//if(bigSignal)++K;

/* default value for no of bytes to save from overflow matrix */
totalpacked = ZERO;


if(zeroSig)
  {
    for(i = ZERO; i < TUTTEROWS; i++)
      nonzeroentry[i] = MINUSONE;
    for(i = ZERO; i < TUTTEROWS; i++)
      {
        for(j = TUTTECOLS - ONE; j >= ZERO; j--)   
          if(tutteMatX[i][j] != ZERO)
            {
               nonzeroentry[i] = j;
               break;
            }
      } 
    for(i = TUTTEROWS - ONE;i >= ZERO; i--)
      if( nonzeroentry[i] >= ZERO)
        {
           kROWS = i;
           break;
        }
kROWS1=kROWS;
    /*  long long matrix being packed for overflow */
/* added <=--is this the problem got wrong answer with 17-try old with 17????*/
    k = MINUSONE;
    for(i = ZERO; i <= kROWS; i++)
      {
        for(j = ZERO; j <= nonzeroentry[i]; ++j)
        {
   #if(PROFILING_MODE)
if(tutteMatX[i][j] == ZERO&& j!=nonzeroentry[i]&&!((i==0)&&(j==0)))++zeroentries;
#endif
           packed[++k] = tutteMatX[i][j];
        }

        if(nonzeroentry[i] >= ZERO)
          packed[k] = -packed[k];
        else
     /* put LLONG_MIN to signal an empty row  */
{          
      packed[++k]=LLONG_MIN;
}
      } 
    totalpacked = k + ONE;
}/* so blank lines not printed */
/* collecting information about lower order coefficient matrix */

for(i = ZERO; i < TUTTEROWS; i++)
  nonzeroentry[i] = MINUSONE;
for(i = ZERO; i < TUTTEROWS; i++)
  {
     for(j = TUTTECOLS - ONE; j >= ZERO; j--)
       if(tutteMat[i][j] != ZERO)
         {
            nonzeroentry[i] = j;
            break;
         }
  } 
for(i = TUTTEROWS - ONE; i >= ZERO; i--)
  if( nonzeroentry[i] >= ZERO)
    {
      kROWS = i;
      break;
    }

if(bigSignal)
  {
/*                                                    */
/*  lower order coefficients going into long long int */
/*                                                    */
     k = MINUSONE;
     for(i = ZERO; i <= kROWS; i++)
       {
         for(j = ZERO; j <= nonzeroentry[i]; ++j)
        {

#if(PROFILING_MODE)
         if(tutteMat[i][j] == ZERO&&j!=nonzeroentry[i]
                 &&!(i==0 && j==0))++zeroentries1;
           if( (tutteMat[i][j]==0) &&!((i==0 )&& (j==0) ) )
             {
             llZeroCtr=1;
             m=j+1;
             while(tutteMat[i][m]==0 && m<=nonzeroentry[i])
                {
                 llZeroCtr+=1;
                 m+=1;
                }
             
          consecutiveZeroesLL[llZeroCtr]+=1;
            } 
#endif
            packed1[++k] = tutteMat[i][j];
          }
            /* after packing the nonzeroentry[i] elements
               the last one in the row is made negative */
          if(nonzeroentry[i] >= ZERO) 
            packed1[k] = -packed1[k];
          else
           packed1[++k] = LLONG_MIN;
       } 
     totalpacked1 = k + ONE;
  }
else
  {
/*                                          */
/*  lower order coefficients going into int */
/*                                          */
     k = MINUSONE;
     for(i = ZERO; i <= kROWS; i++)
       {
          for(j = ZERO; j <= nonzeroentry[i]; ++j)
            {
            #if(PROFILING_MODE)
             if(tutteMat[i][j]==ZERO && j!=nonzeroentry[i])
             {
                                zeroentries2+=1;}
            if( (tutteMat[i][j]==0)&&(!((i==0)&&(j==0))) )
             {
             intZeroCtr=1;
             m=j+1;
            while(tutteMat[i][m]==0 && m<=nonzeroentry[i])
                {
                 intZeroCtr+=1;
                 m+=1;
                }
             
             consecutiveZeroesInt[intZeroCtr]+=1;
            }
#endif 
               packed2[++k] = tutteMat[i][j];
               /* after packing the nonzeroentry[i] elements
                  the last one in the row is made negative */
            }
          if(nonzeroentry[i] >= ZERO) 
             packed2[k] = -packed2[k];
           else
             packed2[++k] = INT_MIN;
      } 
    totalpacked1 = k + ONE;
  }/* biggest number is still integer and not long int */    

#if(PROFILING_MODE)
if(gv==gvnew)++graphcount[gv];
if(gv!=gvnew)++graphcount1[gvnew];
assert(gvnew<256); 
#endif  
/* bytes for first int and canong  */
entries = FIVE + computeNumwords(gvnew);
   /* 1 place each for gv and gv and places for canong */
   /* compute size of compressed memory use */

/* added sizeof(int) on 5/12 since counting bytes in other two entries
   and only words in entries  */
if(zeroSig&& bigSignal)
  {
     intcount = entries + 
               totalpacked1*sizeof(TUTTEMATCH)/sizeof(int)
              +totalpacked*sizeof(TUTTEOMATCH)/sizeof(int);
  }
else
  if(zeroSig && !bigSignal)
     {
       intcount = entries + 
                  totalpacked1*sizeof(int)/sizeof(int)
                 +totalpacked*sizeof(TUTTEOMATCH)/sizeof(int);
     }
   else
     if(!zeroSig && bigSignal)
       {
         intcount = entries*sizeof(int)/sizeof(int) + 
                  totalpacked1*sizeof(TUTTEMATCH)/sizeof(int);
       }
     else
       if(!zeroSig && !bigSignal)
         {
           intcount = entries*sizeof(int)/sizeof(int) + 
                  totalpacked1*sizeof(int)/sizeof(int);/* actually packing packed2[]
                                                          that is int */
         }
noByte=intcount/10;
#if(PROFILING_MODE)
noBytes[intcount/10]++;
#endif
if (intsleft < intcount) 
  {
    ++currentblock; 
      if(currentblock>maxCurrentBlock){
                                       hashinit();
                                       currentblock=ZERO;
                                       //GraphsInHashTable = ZERO;
                                     }
printf("currentblock = %2d  no of block used for hashing  intsleft = %d \n",
                   currentblock,intsleft);
     intsleft = INTS_PER_BLOCK;
  }
#if(PROFILING_MODE)
if(currentblock>maxCurrentBlock)
  printf("GraphsInHashTable =%d\n",GraphsInHashTable);
#endif
intsleft -= intcount;
cp = (int *) &(block[currentblock][intsleft]);

 /* store gv in first int */
cp[ZERO]  = gv;
cp[ONE]   = gvnew;
cp[TWO]   = totalpacked1;
cp[THREE] = totalpacked;
cp[FOUR]=bigSignal;

for (i = FIVE; i < entries; ++i)
  {
    cp[i] = canong[i - FIVE];
  }
if(zeroSig && bigSignal)
  {
    memcpy( &(cp[entries]),
            packed, 
            cp[THREE]*sizeof(TUTTEOMATCH));
    memcpy( &(cp[entries+sizeof(TUTTEOMATCH)/sizeof(int)*cp[THREE]]), 
             packed1, 
             cp[TWO]*sizeof(TUTTEMATCH));
  }
else
  if(zeroSig && !bigSignal)
    {
      memcpy( &(cp[entries]), 
             packed, 
             cp[THREE]*sizeof(TUTTEOMATCH));
      memcpy( &(cp[entries+sizeof(TUTTEOMATCH)/sizeof(int)*cp[THREE]]),
              packed2, 
              cp[TWO]*sizeof(int));
    }
  else
    if(!zeroSig && bigSignal)
      {
         memcpy( &(cp[entries]),
                 packed1, 
                 cp[TWO]*sizeof(TUTTEMATCH));
      }     
    else
      if(!zeroSig && !bigSignal)
        {
           memcpy( &(cp[entries]),
                   packed2, 
                   cp[TWO]*sizeof(int));
        }     

hashinsert(cp, hash,gv,gvnew,noByte);
#if(PROFILING_MODE)
GraphsInHashTable++;
#endif

} /* end isoadd */

/*                                            */
/*           end of isoadd                    */
/*                                            */
/**********************************************/
/*                                            */
/*           start of isoend                  */
/*                                            */

/*
Precondition:

Postcondition:

*/
/*
Procedures Called:
printf ("HASHTABLE RESETS: %3d\n", resetcount);
*/ 

void 
isoend()
{
long long int sum;
  int extras, i, j, k,stop,stop1;
  int gsum,mm, msum,msum1,msum2,gsum2;
/*printf("currentblock = %6d\n",currentblock);*/
  gsum=0; msum=0;msum1=0;msum2=0;mm=0;gsum2=0;
#if(PROFILING_MODE)
printf("\n\n EXPLANATION OF HEADINGS\n");
printf("gv:  # vertices in original graph \n");
printf("gvnew: # vertices in graph used to find canonical labeling for graph with multiple edges\n");
printf("----------------------------------------------------------------\n");
printf("threshold: number of vertices in a graph\n");
printf("gv = gvnew means that there are no \n");
printf("           multiple edges in the graph\n");
printf("gv != gvnew means there are multiple edges and the isomorphism was for the gvnew graph\n");
printf("gvnew of gv!=gvnew: number of vertices in a graph looked up based on its multiple edge canon. labeling\n");
printf("gv of gv = gvnew: number of look ups for graphs with no multiple edges \n\n");
  
  gsum=0; msum=0;
  printf("-------------------------------------------------------------------\n");
printf("            ISOMORPHISM CLASSES   NUMBER HASH TABLE HITS\n");
printf("threshold   gv=gvnew   gv!=gvnew  gv of gv=gvnew    (gvnew of gv!=gvnewm)  \n");
  printf("---------------------------------------------------------------------\n");
  for (i=255; i;--i)
    {
      if (graphcount[i]||graphcount1[i])
	{
	  printf("%6d %9d %9d %15d %15d ", i, graphcount[i],graphcount1[i], 
                matchcount[i],matchcount1[i]);
          //if(matchcount[i])
	   //    printf("%7.2f\n", ((double) match[i])/(graphcount[i]+graphcount1[i]));
          //else
              printf("\n");
	  msum += matchcount[i];
	  gsum += graphcount[i];
          msum1+=matchcount1[i];
          mm+=match[i];
          msum2+=matchcount2[i];
          gsum2+=graphcount1[i];
        }
    }
  printf("-----------------------------------------------------------------\n");
  printf("total  %9d %9d  %15d %15d\n", gsum,gsum2,msum,msum1);
printf("no in hash table = %d      total number matched = %d\n\n",gsum+gsum2,msum+msum1);
  printf("-----------------------------------------------------------------\n");
 // if (gsum)
//    printf("   %7.2f",((double) msum)/gsum);
  printf("\n");

 /* if (smallgraphcount)
       printf ("Total number of graphs with < %d vertices: %d\n",
	       DEFAULT_SAVELEVEL, smallgraphcount);*/
stop=0;
for(i=EDGESIZE-1;i>=0;i--)
{

for(j=EDGESIZE-1;j>=0;j--)
{

if(gvBYgvnew[j][i]!=0)
{
stop = i; //last nonzero column
break;
}

}

if(stop)break;
}

stop1=0;
for(i=EDGESIZE-1;i>=0;i--)
{

for(j=EDGESIZE-1;j>=0;j--)
{

if(gvBYgvnew[i][j]!=0)
{
stop1 = i;  // last nonzero row
break;
}

}

if(stop1)break;
}
printf("stop=%d  stop1=%d\n",stop,stop1);
printf("   ");
printf("The table has its row and columns labeled by the number of\n");
printf("vertices in a graph. The labels on the columns represent\n");
printf("the number of vertices in the underlying graphs while the\n");
printf("rows represent the number of vertices in the multi graphs\n");
printf("that are built so nauty can be used.\n");
printf("The row sums, excluding the diagonal elements should match\n");
printf("the numbers on the last column of the table above\n");
printf("\n\n  ");

if( stop1 <=12)
{




printf("   ");
for(i=6;i<=stop1;i++)
printf("%11d ",i);
printf("       SUM  \n    ");
printf("   ");
for(i=6;i<=stop1;i++)
printf("------------");
printf("\n");
/* Now print the table */
for(j=6;j<=stop;j++) // stop is last nonzerocolumn 
{
printf("%3d",j);
for(i=6;i<=stop1;i++) 
{
if(gvBYgvnew[i][j]!=0)printf("%11lld",gvBYgvnew[i][j]); else printf("           ");
}
sum=0;
for(k=6;k<=stop;k++) //stop is last nonzero column
if(j!=k)sum+=gvBYgvnew[k][j];
if(sum!=0)printf(" %11lld\n",sum);else printf("\n");
}
}
else
{

printf("   ");
for(i=7;i<=12;i++)
printf("%7d ",i);
//printf("       SUM  \n    ");
printf("\n");
for(i=7;i<=12;i++)
printf("--------");
printf("\n");
/* Now print the table */
for(j=7;j<=stop;j++) 
{
printf("%3d",j);
for(i=7;i<=12;i++) 
{
if(gvBYgvnew[i][j]!=0)printf("%11lld",gvBYgvnew[i][j]); else printf("           ");
}
printf("\n");
}

printf("\n   ");
for(i=13;i<=stop1;i++)
printf("%7d ",i);
printf("       SUM  \n    ");
printf("   ");
for(i=13;i<=stop1;i++)
printf("-------------");
printf("\n");
/* Now print the table */
for(j=13;j<=stop;j++) // stop is last nonzerocolumn 
{
printf("%3d",j);
for(i=13;i<=stop1;i++)  // stop1 is last row 
{
if(gvBYgvnew[i][j]!=0)printf("%11lld",gvBYgvnew[i][j]); else printf("            ");

}
sum=0;
for(k=7;k<=stop;k++) //stop is last nonzero column
if(j!=k)sum+=gvBYgvnew[k][j];
if(sum!=0)printf(" %11lld\n",sum);else printf("\n");
}

}
#endif

} /* end isoend */


/*                                            */
/*           end of isoend                    */
/*                                            */
/**********************************************/
/*                                            */
/*           start of isoreset                */
/*                                            */
 

void 
isoAndStatSetVars()
{
int i,
     j;

hashinit();
currentblock=MINUSONE;
intsleft = 0;

#if(PROFILING_MODE)
stackDepthPop= 5000;
stackDepthPush = -5000;
GraphsInHashTable = ZERO;
gvnewMax = -500;
zeroentries = ZERO;
printf("zeroentries=%d\n",zeroentries);zeroentries1 = ZERO;
zeroentries2 = ZERO;
zeroentries2a = ZERO;
noGraphsLookedUp = ZERO;
NoNonzeroOverflowMatricesInt = ZERO;
NoNonzeroOverflowMatricesLongLongInt = ZERO;
for (i = ZERO; i < EDGESIZE; ++i) 
  {
    graphcount[i] = ZERO; 
    graphcount1[i]=ZERO;
    matchcount[i] = ZERO;
    match[i]=ZERO;
    matchcount1[i]=ZERO;
    matchcount2[i]=ZERO;
for (j = ZERO; j < EDGESIZE; ++j) 
  {
gvBYgvnew[i][j] = ZERO;
}

  } 

for(i=0;i<30;i++)
{
consecutiveZeroesInt[i]=0;
consecutiveZeroesLL[i]=0;
backwards[i]=0;
}
for( i = ZERO; i <10000; i++ )
  noBytes[i] = ZERO;
#endif

} /* end isoreset */

/*                                            */
/*           end of isoreset                 */
/*                                            */
/**********************************************/

int printT1( 
            TUTTEO t
           )
{
int i,j,k,l;
//if(TUTTECOLS<20)k=TUTTECOLS-1;else k=20;
//if(TUTTEROWS<20)l=TUTTEROWS-1;else l=20;


  printf("Tutte Matrix--type integer\n");
  for (i=0;i<10;i++) {
    for (j=0;j<TUTTECOLS;j++) 
   printf("%d ",t[i][j]);
    printf("\n");
  }

}
int printT( 
           TUTTE t
          )
{
int i,j;

  printf("Tutte Matrix--type long long\n");
  for (i=0;i<15;i++) {
    for (j=0;j<15;j++) 
   printf("%2lld ",t[i][j]);/* have to lld if TUTTE long long int */
    printf("\n");
  }

}
