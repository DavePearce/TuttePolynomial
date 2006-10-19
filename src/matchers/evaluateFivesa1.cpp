#include <memory.h>
#include  <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "core/tutte.h"


/*******************************************************/
/*                                                     */
/*      start fiveTreesnew                             */
/*                                                     */
/*                                                     */

/*
Precondition: C--index for graph array pointing to a tree with five 
              vertices as the underlying graph
              vertIndex--array with canonical ordering of vertices
              tutteMat2 and tutteMat2X are arrays with
              values for current state of this computation

Postcondition: tutteMat2 and tutteMat2X augmented by the tutte 
               poly of this graph

Returns: 1 to signal graph needs replacing 
         
*/


int fiveTreesnew(
                 int C,
                 int vertIndex[],
                 TUTTE tutteMat2,
                 TUTTEO tutteMat2X
                )
{
int i,                            /* for parameter              */
    j,
    k,
    m,
    ne,                           /* location of edge           */
    xp,                           /* degree in x of monomial    */
    yp,                           /* degree of y in monomial    */
    edgeCount[TEN][TEN],          /* incidence information      */
    edgesInBranch[TEN];           /* multiplicity information   */
//printf("evaluateFivesa1\n");

for( i = ZERO; i < SIX; i++ ) 
for( j = ZERO; j < SIX; j++ ) 
  edgeCount[i][j] = ZERO;

for(ne = firstEdge(&g[C], vertIndex[ONE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne) == vertIndex[TWO] )
      ++edgeCount[ONE][TWO];
    else
      if( vertListOtherEnd(&g[C], ne) == vertIndex[THREE] )
        ++edgeCount[ONE][THREE];
      else
        if( vertListOtherEnd(&g[C], ne) == vertIndex[FOUR] )
          ++edgeCount[ONE][FOUR];
        else
          if( vertListOtherEnd(&g[C], ne) == vertIndex[FIVE] )
            ++edgeCount[ONE][FIVE];
  }


for(ne = firstEdge(&g[C], vertIndex[TWO]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne) == vertIndex[THREE] )
      ++edgeCount[TWO][THREE];
    else
      if( vertListOtherEnd(&g[C], ne) == vertIndex[FOUR] )
        ++edgeCount[TWO][FOUR];
      else
        if( vertListOtherEnd(&g[C], ne) == vertIndex[FIVE] )
          ++edgeCount[TWO][FIVE];
  }


for(ne = firstEdge(&g[C], vertIndex[THREE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne) == vertIndex[FOUR] )
      ++edgeCount[THREE][FOUR];
    else
      if( vertListOtherEnd(&g[C], ne) == vertIndex[FIVE] )
        ++edgeCount[THREE][FIVE];
  }


for(ne = firstEdge(&g[C], vertIndex[FOUR]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne) == vertIndex[FIVE] )
      ++edgeCount[FOUR][FIVE];
  }

for( i = ZERO; i < SIX; i++ ) 
  edgesInBranch[i] = ZERO;

j = ZERO;
for( i = ONE; i < SIX; i++ )
for( k = ONE; k < SIX; k++ ) {
  if(edgeCount[i][k] > ZERO ) 
    {
      j++;
      edgesInBranch[j] =edgeCount[i][k];
    }
  }
for( i = ZERO; i < edgesInBranch[1]; i++ )
for( j = ZERO; j < edgesInBranch[TWO]; j++ )
for( k = ZERO; k < edgesInBranch[THREE]; k++ )
for( m = ZERO; m < edgesInBranch[FOUR]; m++ ) 
  {
    xp = ( ( i == ZERO )?1:ZERO )+
       ( ( j == ZERO )?1:ZERO )+
       ( ( k == ZERO )?1:ZERO )+
       ( ( m == ZERO )?1:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }



return(ONE);

} /* end fiveTreesnew */

/*                                                     */
/*        end fiveTreesnew                             */
/*                                                     */
/*                                                     */
/*******************************************************/
/*                                                     */
/*      start degseq3200                               */
/*                                                     */
/*                                                     */

/*
Precondition: C--index for graph array pointing to a tree with degseq 3200
              for underlying graph
              vertDeg and vertIndex initialized to identify degree and
              canonical label for each vertex
              tutteMat2 and tutteMat2X are arrays with
              values for current state of this computation

Postcondition: tutteMat2 and tutteMat2X augmented by the tutte 
               poly of this graph

Returns: 1 to signal graph needs replacing 
         
*/

int degseq3200(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X)
{
int i,
    j,
    k,
    ne,
    vertRename[TEN],
    edgeCount[TEN][TEN];

//printf("K(5) - (1,5)\n"); 
j = ZERO;
for( i =1; i <= FIVE; i++ )
  if(vertDeg[i] == THREE ) 
    {
      ++j;
      vertRename[j] = vertIndex[i];
    }

vertRename[FIVE] = vertRename[TWO];
for( i =1; i <= FIVE; i++ )
  if(vertDeg[i] == FOUR ) 
    {
      vertRename[j] = vertIndex[i];
      ++j;
    }
assert(vertRename[ONE] > ZERO );
assert(vertRename[TWO] > ZERO );
assert(vertRename[THREE] > ZERO );
assert(vertRename[FOUR] > ZERO );
assert(vertRename[FIVE] > ZERO );

for( i = ZERO; i < SIX; i++ )
for( j = ZERO; j < SIX; j++ )
  edgeCount[i][j] = ZERO;


for(ne = firstEdge(&g[C], vertRename[ONE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne) == vertRename[TWO] )
      ++edgeCount[ONE][TWO];
    else
      if( vertListOtherEnd(&g[C], ne) == vertRename[THREE] )
        ++edgeCount[ONE][THREE];
      else
        if( vertListOtherEnd(&g[C], ne) == vertRename[FOUR] )
          ++edgeCount[ONE][FOUR];
  }


for(ne = firstEdge(&g[C], vertRename[TWO]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne) == vertRename[THREE] )
      ++edgeCount[TWO][THREE];
    else
      if( vertListOtherEnd(&g[C], ne) == vertRename[FOUR] )
        ++edgeCount[TWO][FOUR];
      else
        if( vertListOtherEnd(&g[C], ne) == vertRename[FIVE] )
          ++edgeCount[TWO][FIVE];
  }


for(ne = firstEdge(&g[C], vertRename[THREE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne) == vertRename[FOUR] )
      ++edgeCount[THREE][FOUR];
    else
      if( vertListOtherEnd(&g[C], ne) == vertRename[FIVE] )
        ++edgeCount[THREE][FIVE];
  }


for(ne = firstEdge(&g[C], vertRename[FOUR]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne) == vertRename[FIVE] )
      ++edgeCount[FOUR][FIVE];
  }

assert(edgeCount[ONE][TWO]  > ZERO );
assert(edgeCount[ONE][THREE] > ZERO );
assert(edgeCount[ONE][FOUR] > ZERO );
assert(edgeCount[TWO][THREE] > ZERO );
assert(edgeCount[TWO][FOUR] > ZERO );
assert(edgeCount[TWO][FIVE] > ZERO );
assert(edgeCount[THREE][FOUR] > ZERO );
assert(edgeCount[THREE][FIVE] > ZERO );
assert(edgeCount[FOUR][FIVE] > ZERO );

completePolyWithNoX(edgeCount[TWO][FIVE],
                    edgeCount[ONE][TWO],
                    edgeCount[ONE][THREE],
                    edgeCount[ONE][FOUR],
                    edgeCount[TWO][THREE]+edgeCount[THREE][FIVE],
                    edgeCount[TWO][FOUR]+edgeCount[FOUR][FIVE],
                    edgeCount[THREE][FOUR],
                    tutteMat2,
                    tutteMat2X);

completePolyWithNoX(edgeCount[THREE][FIVE],
                    edgeCount[ONE][TWO],
                    edgeCount[ONE][THREE],
                    edgeCount[ONE][FOUR],
                    edgeCount[TWO][THREE],
                    edgeCount[TWO][FOUR],
                    edgeCount[THREE][FOUR]+edgeCount[FOUR][FIVE],
                    tutteMat2,
                    tutteMat2X);

completePolyWithX(edgeCount[FOUR][FIVE],
                  edgeCount[ONE][TWO],
                  edgeCount[ONE][THREE],
                  edgeCount[ONE][FOUR],
                  edgeCount[TWO][THREE],
                  edgeCount[TWO][FOUR],
                  edgeCount[THREE][FOUR],
                  tutteMat2,
                  tutteMat2X);


return(ONE);

} /* end degseq3200 */

/*                                                     */
/*      end degseq3200                                 */
/*                                                     */
/*                                                     */
/*******************************************************/
/*                                                     */
/*      start degseq1040                               */
/*                                                     */
/*                                                     */

/*
Precondition: C--index for graph array pointing to a tree with five vertices
              and degseq 1040 for the underlying graph
              vertDeg and vertIndex--arrays initialized to identify degree and
              canonical label for each vertex
              tutteMat2 and tutteMat2X are arrays with
              values for current state of this computation

Postcondition: tutteMat2 and tutteMat2X augmented by the tutte 
               poly of this graph

Returns: 1 to signal graph needs replacing 
         
*/

int degseq1040(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X)
{
int i,                         /* for parameter                     */
    m,
    j,
    k,
    xp,                       /* degree of x in monmial             */
    yp,                       /* degree of y in monomial            */
    ne,                       /* location of edge in graph          */
    vertRename[TEN],           /* array for canonical labeling       */
    edgeCount[TEN][TEN];        /* incidence information about graph  */


for( i = ONE; i <= FIVE; i++ )
  if(vertDeg[i] == FOUR )
    {
       vertRename[ONE] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE; i++ )
  if(vertDeg[i] == TWO )
    {
       vertRename[TWO] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == TWO ) && ( isadj(vertIndex[i],vertRename[TWO],&g[C]) ) )
    {
       vertRename[THREE] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == TWO ) && ( vertIndex[i] != vertRename[TWO] )
                  && ( vertIndex[i] != vertRename[THREE] ) )
    {
       vertRename[FOUR] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == TWO ) && ( isadj(vertIndex[i],vertRename[FOUR],&g[C]) ) )
    {
       vertRename[FIVE] = vertIndex[i];
       break;
    }
edgeCount[ONE][TWO] = ZERO;
edgeCount[ONE][THREE] = ZERO;
edgeCount[ONE][FOUR] = ZERO;
edgeCount[ONE][FIVE] = ZERO;
edgeCount[TWO][THREE] = ZERO;
edgeCount[FOUR][FIVE] = ZERO;

for(ne = firstEdge(&g[C], vertRename[ONE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne) == vertRename[TWO] )
      ++edgeCount[ONE][TWO];
    else
      if( vertListOtherEnd(&g[C], ne) == vertRename[THREE] )
        ++edgeCount[ONE][THREE];
      else
        if( vertListOtherEnd(&g[C], ne) == vertRename[FOUR] )
          ++edgeCount[ONE][FOUR];
        else
          if( vertListOtherEnd(&g[C], ne) == vertRename[FIVE] )
            ++edgeCount[ONE][FIVE];
  }


for(ne = firstEdge(&g[C], vertRename[TWO]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne) == vertRename[THREE] )
      ++edgeCount[TWO][THREE];
  }


for(ne = firstEdge(&g[C], vertRename[FOUR]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne) == vertRename[FIVE] )
      ++edgeCount[FOUR][FIVE];
  }
assert(edgeCount[ONE][TWO] > ZERO );
assert(edgeCount[ONE][THREE] > ZERO );
assert(edgeCount[ONE][FOUR] > ZERO );
assert(edgeCount[ONE][FIVE] > ZERO );
assert(edgeCount[TWO][THREE] > ZERO );
assert(edgeCount[FOUR][FIVE] > ZERO );



for( i = ZERO; i < edgeCount[TWO][THREE]; i++ )
for( j = ZERO; j < edgeCount[ONE][THREE]; j++ )
for( k = ZERO; k < edgeCount[ONE][FOUR]; k++ )
for( m = ZERO; m < edgeCount[FOUR][FIVE]; m++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO )+
       ( ( j == ZERO )?ONE:ZERO )+
       ( ( k == ZERO )?ONE:ZERO )+
       ( ( m == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[TWO][THREE]; i++ )
for( j = ZERO; j < edgeCount[ONE][THREE]; j++ )
for( k = ZERO; k < edgeCount[ONE][FOUR]+edgeCount[FOUR][FIVE];  k++ )
for( m = ZERO; m < edgeCount[ONE][FIVE]; m++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO )+
       ( ( j == ZERO )?ONE:ZERO )+
       ( ( k == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][THREE]+edgeCount[TWO][THREE]; i++ )
for( j = ZERO; j < edgeCount[ONE][FOUR]; j++ )
for( k = ZERO; k < edgeCount[FOUR][FIVE]; k++ )
for( m = ZERO; m < edgeCount[ONE][TWO]; m++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO)+
       ( ( j == ZERO )?ONE:ZERO)+
       ( ( k == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][THREE]+edgeCount[TWO][THREE]; i++ )
for( j = ZERO; j < edgeCount[ONE][FOUR]+edgeCount[FOUR][FIVE]; j++ )
for( k = ZERO; k < edgeCount[ONE][TWO]; k++ )
for( m = ZERO; m < edgeCount[ONE][FIVE]; m++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO )+
       ( ( j == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }


return(ONE);

} /* end degseq1040 */


/*                                                     */
/*                                                     */
/*      end degseq1040                                 */
/*                                                     */
/*                                                     */
/*******************************************************/






