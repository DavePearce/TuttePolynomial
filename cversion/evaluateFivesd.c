 #include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

/****************************************************/
/*                                                  */
/*                                                  */
/*                start degseq311                   */
/*                                                  */
/*                                                  */

/*
Precondition: C--index to graph array pointing to graph with degree sequence 311 
	      for the underlying graph
              vertDeg and vertIndex initialized to identify degree and
              canonical label for each vertex
              tutteMat2 and tutteMat2X are arrays with values for the
	      current state of the computation

Postcondition: tutteMat2 and tutteMat2X augmented by the tutte
               poly of this graph

Return: 1 to signify graph needs replacing

*/



int degseq311(
              int C,
              int vertDeg[],
              int vertIndex[],
              TUTTE tutteMat2,
              TUTTEO tutteMat2X
             ) 
{

int i,                   /* for parameter                                      */
    j,
    k,
    m,
    ne,                  /* location of edge                                    */
    xp,                  /* degree of x in monomial                             */
    yp,                  /* degree of y in monomial                             */
    vertRename[TEN],      /* canonical labelling                                 */
    edgeCount[TEN][TEN];   /* incidence information for vertices [*][] with [][*] */
//printf("evaluateFivesd\n");
for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == ONE ) 
    {
       vertRename[ONE] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == TWO ) 
    {
       vertRename[FIVE] = vertIndex[i];
       break;
    }

j= TWO;
for( i = ONE; i <= FIVE; i++ )
  if(vertDeg[i] == THREE ) 
    {
       if(isadj(vertIndex[i],vertRename[FIVE],&g[C])) 
         {
            j++;
            vertRename[j] = vertIndex[i];
            if(j== FOUR )
              break;
         }
    }

for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == THREE ) 
    {
       if( isadj(vertIndex[i],vertRename[ONE],&g[C]) ) 
         {
            vertRename[TWO] = vertIndex[i];
            break;
         }
    }
assert( vertRename[ONE ] > ZERO );
assert( vertRename[TWO] > ZERO );
assert( vertRename[THREE] > ZERO );
assert( vertRename[FOUR] > ZERO );
assert( vertRename[FIVE] > ZERO );


edgeCount[ONE][TWO] = ZERO;
edgeCount[TWO][THREE] = ZERO;
edgeCount[TWO][FOUR] = ZERO;
edgeCount[THREE][FOUR] = ZERO;
edgeCount[THREE][FIVE] = ZERO;
edgeCount[FOUR][FIVE] = ZERO;

for(ne = firstEdge(&g[C], vertRename[TWO]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[ONE] )
       ++edgeCount[ONE][TWO];
     else
       if( vertListOtherEnd(&g[C], ne)  == vertRename[THREE] )
         ++edgeCount[TWO][THREE];
       else
         if( vertListOtherEnd(&g[C], ne)  == vertRename[FOUR] )
           ++edgeCount[TWO][FOUR];
  }


for(ne = firstEdge(&g[C], vertRename[FOUR]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[THREE] )
       ++edgeCount[THREE][FOUR];
     else
       if( vertListOtherEnd(&g[C], ne)  == vertRename[FIVE] )
         ++edgeCount[FOUR][FIVE];
  }


for(ne = firstEdge(&g[C], vertRename[THREE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[FIVE] )
       ++edgeCount[THREE][FIVE];
  }

assert( edgeCount[ONE][TWO] > ZERO );
assert( edgeCount[TWO][THREE] > ZERO );
assert( edgeCount[TWO][FOUR] > ZERO );
assert( edgeCount[THREE][FOUR] > ZERO );
assert( edgeCount[THREE][FIVE] > ZERO );
assert( edgeCount[FOUR][FIVE] > ZERO );


for( i = ZERO; i < edgeCount[ONE][TWO]; i++ )
for( j = ZERO; j < edgeCount[TWO][THREE]; j++ )
for( k = ZERO; k < edgeCount[THREE][FIVE]; k++ )
for( m = ZERO; m < edgeCount[FOUR][FIVE]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO ) +
       ( ( k == ZERO )?ONE:ZERO ) +
       ( ( m == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][TWO]; i++ )
for( j = ZERO; j < edgeCount[TWO][THREE]; j++ )
for( k = ZERO; k < edgeCount[THREE][FIVE] + edgeCount[FOUR][FIVE]; k++ )
for( m = ZERO; m < edgeCount[THREE][FOUR]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO ) +
       ( ( k == ZERO )?ONE:ZERO );
    yp= i + j + k + m;
    tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][TWO]; i++ )
for( j = ZERO; j < edgeCount[TWO][THREE] + edgeCount[THREE][FOUR]; j++ )
for( k = ZERO; k < edgeCount[THREE][FIVE]; k++ )
for( m = ZERO; m < edgeCount[TWO][FOUR]; m++ )
   {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO ) +
       ( ( k == ZERO )?ONE:ZERO );
    yp= i + j + k + m;
    tutteMat2[yp][xp]++;
  }


for( i = ZERO; i < edgeCount[ONE][TWO]; i++ )
for( j = ZERO; j < edgeCount[TWO][THREE] + edgeCount[THREE][FOUR] + edgeCount[THREE][FIVE]; j++ )
for( k = ZERO; k < edgeCount[TWO][FOUR]; k++ )
for( m = ZERO; m < edgeCount[FOUR][FIVE]; m++ )
   {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }


return( ONE );

} /* end degseq311 */ 


/*                                                  */
/*                                                  */
/*                                                  */
/*                end degseq311                     */
/*                                                  */
/*                                                  */
/****************************************************/
/*                                                  */
/*                                                  */
/*                start degseq2030                  */
/*                                                  */
/*                                                  */


/*
Precondition: C--index to graph array pointing to graph with degree sequence 2030 
	      for the underlying graph
              vertDeg and vertIndex initialized to identify degree and
              canonical lab el for each vertex
	      tutteMat2 and tutteMat2X are arrays with values for the
	      current state of the computation

Postcondition: tutteMat2 and tutteMat2X augmented by the tutte
               poly of this graph

Return: 1 to signify graph needs replacing

*/

int degseq2030(
               int C,
               int vertDeg[],
               int vertIndex[],
               TUTTE tutteMat2,
               TUTTEO tutteMat2X
              )
{

int i,                   /* for parameter                                      */
    j,
    k,
    m,
    ne,                  /* location of edge                                    */
    xp,                  /* degree of x in monomial                             */
    yp,                  /* degree of y in monomial                             */
    vertRename[TEN],      /* canonical labelling                                 */
    edgeCount[TEN][TEN];   /* incidence information for vertices [*][] with [][*] */

//printf("GOT INTO 2030\n");
j = ZERO;
for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == FOUR ) 
    {
       j++;
       vertRename[j] = vertIndex[i];
       if( j == TWO )
         break;
    }
for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == TWO ) 
    {
       j++;
       vertRename[j] = vertIndex[i];
       if( j == FIVE )
         break;
    }
assert( vertRename[ONE] > ZERO );
assert( vertRename[TWO] > ZERO );
assert( vertRename[THREE] > ZERO );
assert( vertRename[FOUR] > ZERO );
assert( vertRename[FIVE] > ZERO );


edgeCount[ONE][TWO] = ZERO;
edgeCount[ONE][THREE] = ZERO;
edgeCount[ONE][FOUR] = ZERO;
edgeCount[ONE][FIVE] = ZERO;
edgeCount[TWO][THREE] = ZERO;
edgeCount[TWO][FOUR] = ZERO;
edgeCount[TWO][FIVE] = ZERO;


for(ne = firstEdge(&g[C], vertRename[ONE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne)  == vertRename[TWO] )
      ++edgeCount[ONE][TWO];
    else
      if( vertListOtherEnd(&g[C], ne)  == vertRename[THREE] )
        ++edgeCount[ONE][THREE];
      else
        if( vertListOtherEnd(&g[C], ne)  == vertRename[FOUR] )
          ++edgeCount[ONE][FOUR];
        else
          if( vertListOtherEnd(&g[C], ne)  == vertRename[FIVE] )
            ++edgeCount[ONE][FIVE];
  }


for(ne = firstEdge(&g[C], vertRename[TWO]); ne != LIST_END; ne = nextEdge(&g[C], ne))
   {
    if( vertListOtherEnd(&g[C], ne)  == vertRename[THREE] )
      ++edgeCount[TWO][THREE];
    else
      if( vertListOtherEnd(&g[C], ne)  == vertRename[FOUR] )
        ++edgeCount[TWO][FOUR];
      else
        if( vertListOtherEnd(&g[C], ne)  == vertRename[FIVE] )
          ++edgeCount[TWO][FIVE];
  }

assert( edgeCount[ONE][TWO] > ZERO );
assert( edgeCount[ONE][THREE] > ZERO );
assert( edgeCount[ONE][FOUR] > ZERO );
assert( edgeCount[ONE][FIVE] > ZERO );
assert( edgeCount[TWO][THREE] > ZERO );
assert( edgeCount[TWO][FOUR] > ZERO );
assert( edgeCount[TWO][FIVE] > ZERO );



for( i = ZERO; i < edgeCount[ONE][THREE]; i++ )
for( j = ZERO; j < edgeCount[ONE][FOUR]; j++ )
for( k = ZERO; k < edgeCount[TWO][FOUR]; k++ )
for( m = ZERO; m < edgeCount[TWO][FIVE]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO ) +
       ( ( k == ZERO )?ONE:ZERO ) +
       ( ( m == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][THREE]; i++ )
for( j = ZERO; j < edgeCount[TWO][FIVE]; j++ )
for( k = ZERO; k < edgeCount[ONE][FOUR]; k++ )
for( m = ZERO; m < edgeCount[ONE][FIVE]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO ) +
       ( ( k == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }



for( i = ZERO; i < edgeCount[ONE][THREE]; i++ )
for( j = ZERO; j < edgeCount[ONE][FOUR] + edgeCount[TWO][FIVE]; j++ )
for( k = ZERO; k < edgeCount[ONE][FIVE]; k++ )
for( m = ZERO; m < edgeCount[TWO][FOUR]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO) +
       ( ( j == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }


for( i = ZERO; i < edgeCount[TWO][FOUR]; i++ )
for( j = ZERO; j < edgeCount[TWO][FIVE]; j++ )
for( k = ZERO; k < edgeCount[ONE][THREE]; k++ )
for( m = ZERO; m < edgeCount[TWO][THREE]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO ) +
       ( ( k == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }



for( i = ZERO; i < edgeCount[TWO][FIVE]; i++ )
for( j = ZERO; j < edgeCount[ONE][THREE]+edgeCount[TWO][FOUR]; j++ )
for( k = ZERO; k < edgeCount[TWO][THREE]; k++ )
for( m = ZERO; m < edgeCount[ONE][FOUR]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[TWO][FOUR]; i++ )
for( j = ZERO; j < edgeCount[ONE][THREE] + edgeCount[TWO][FIVE]; j++ )
for( k = ZERO; k < edgeCount[TWO][THREE]; k++ )
for( m = ZERO; m < edgeCount[ONE][FIVE]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }


for( i = ZERO; i < edgeCount[ONE][THREE] + edgeCount[TWO][FOUR] + edgeCount[TWO][FIVE]; i++ )
for( j = ZERO; j < edgeCount[TWO][THREE]; j++ )
for( k = ZERO; k < edgeCount[ONE][FOUR]; k++ )
for( m = ZERO; m < edgeCount[ONE][FIVE]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }

/* contract (1,2) */
for( i = ZERO; i < edgeCount[ONE][THREE] + edgeCount[TWO][THREE]; i++ )
for( j = ZERO; j < edgeCount[ONE][FOUR] + edgeCount[TWO][FOUR]; j++ )
for( k = ZERO; k < edgeCount[ONE][FIVE] + edgeCount[TWO][FIVE]; k++ )
for( m = ZERO; m < edgeCount[ONE][TWO]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO ) +
       ( ( k == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }



return( ONE );

} /* end degseq2030 */

/*                                                  */
/*                                                  */
/*                end degseq2030                    */
/*                                                  */
/****************************************************/
/*                                                  */
/*                                                  */
/*                start degseq1301                  */
/*                                                  */
/*                                                  */

/*
Precondition: C--index to graph array pointing to graph with degree sequence 1301 
	      for the underlying graph
              vertDeg and vertIndex initialized to identify degree and
              canonical label for each vertex
	      tutteMat2 and tutteMat2X are arrays with values for the
	      current state of the computation

Postcondition: tutteMat2 and tutteMat2X augmented by the tutte
               poly of this graph

Return: 1 to signify graph needs replacing

*/


int degseq1301(
               int C,
               int vertDeg[],
               int vertIndex[],
               TUTTE tutteMat2,
               TUTTEO tutteMat2X
              )
{
int i,                   /* for parameter                                      */
    j,
    ne,                  /* location of edge                                    */
    vertRename[TEN],      /* canonical labelling                                 */
    edgeCount[TEN][TEN];   /* incidence information for vertices [*][] with [][*] */

//printf("K(4) with a tail\n");
for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == ONE ) 
    {
       vertRename[FIVE] = vertIndex[i];
       break;
    }
for( i = ONE ; i <= FIVE ;i++ )
  if( vertDeg[i] == FOUR ) 
    {
       vertRename[ONE] = vertIndex[i];
       break;
    }
j = ONE;
for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == THREE ) 
    {
      ++j;
      vertRename[j] = vertIndex[i];
    }
assert( vertRename[ONE] > ZERO );
assert( vertRename[TWO] > ZERO );
assert( vertRename[THREE] > ZERO );
assert( vertRename[FOUR] > ZERO );
assert( vertRename[FIVE] > ZERO );


edgeCount[ONE][FIVE] = ZERO;
edgeCount[ONE][TWO] = ZERO;
edgeCount[ONE][THREE] = ZERO;
edgeCount[ONE][FOUR] = ZERO;
edgeCount[TWO][THREE] = ZERO;
edgeCount[TWO][FOUR] = ZERO;
edgeCount[THREE][FOUR] = ZERO;


for(ne = firstEdge(&g[C], vertRename[ONE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne)  == vertRename[FIVE] )
      ++edgeCount[ONE][FIVE];
    else
      if( vertListOtherEnd(&g[C], ne)  == vertRename[TWO] )
        ++edgeCount[ONE][TWO];
      else
        if( vertListOtherEnd(&g[C], ne)  == vertRename[THREE] )
          ++edgeCount[ONE][THREE];
        else
          if( vertListOtherEnd(&g[C], ne)  == vertRename[FOUR] )
            ++edgeCount[ONE][FOUR];
  }


for(ne = firstEdge(&g[C], vertRename[THREE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne)  == vertRename[TWO] )
      ++edgeCount[TWO][THREE];
    else
      if ( vertListOtherEnd(&g[C], ne)  == vertRename[FOUR] )
        ++edgeCount[THREE][FOUR];
  }


for(ne = firstEdge(&g[C], vertRename[TWO]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne)  == vertRename[FOUR] )
      ++edgeCount[TWO][FOUR];
  }


assert( edgeCount[ONE][FIVE] > ZERO );
assert( edgeCount[ONE][TWO] > ZERO );
assert( edgeCount[ONE][THREE] > ZERO );
assert( edgeCount[ONE][FOUR] > ZERO );
assert( edgeCount[TWO][THREE] > ZERO );
assert( edgeCount[TWO][FOUR] > ZERO );
assert( edgeCount[THREE][FOUR] > ZERO );




completePolyWithX(edgeCount[1][5],
                  edgeCount[1][2],
                  edgeCount[1][3],
                  edgeCount[1][4],
                  edgeCount[2][3],
                  edgeCount[2][4],
                  edgeCount[3][4],
                  tutteMat2,
                  tutteMat2X);


return( ONE );

} /* end degseq1301 */



/*                                                  */
/*                                                  */
/*                end degseq1301                    */
/*                                                  */
/****************************************************/
/*                                                  */
/*                                                  */
/*               start degseq1220                   */
/*                                                  */
/*                                                  */


/*
Precondition: C--index to graph array pointing to graph with degree sequence 1220 
	      for the underlying graph
              vertDeg and vertIndex initialized to identify degree and
              canonical label for each vertex
	      tutteMat2 and tutteMat2X are arrays with values for the
	      current state of the computation

Postcondition: tutteMat2 and tutteMat2X augmented by the tutte
               poly of this graph

Return: 1 to signify graph needs replacing

*/


int degseq1220(
               int C,
               int vertDeg[],
               int vertIndex[],
               TUTTE tutteMat2,
               TUTTEO tutteMat2X
              )
{
int i,                   /* for parameter                                      */
    j,
    k,
    m,
    ne,                  /* location of edge                                    */
    xp,                  /* degree of x in monomial                             */
    yp,                  /* degree of y in monomial                             */
    vertRename[TEN],      /* canonical labelling                                 */
    edgeCount[TEN][TEN];   /* incidence information for vertices [*][] with [][*] */

//printf("GOT INTO 1220\n");
for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == FOUR ) 
    {
       vertRename[ONE] = vertIndex[i];
       break;
    }
j = TWO;
for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == THREE ) 
    {
      j++;
      vertRename[j] = vertIndex[i];
      if( j == FOUR )
        break;
    }
for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == TWO ) && ( isadj(vertRename[THREE],vertIndex[i],&g[C]) ) ) 
    {
       vertRename[TWO] = vertIndex[i];
       break;
    }
for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == TWO ) && ( isadj(vertRename[FOUR],vertIndex[i],&g[C]) ) ) 
    {
       vertRename[FIVE] = vertIndex[i];
       break;
    }

assert( vertRename[ONE] > ZERO );
assert( vertRename[TWO] > ZERO );
assert( vertRename[THREE] > ZERO );
assert( vertRename[FOUR] > ZERO );
assert( vertRename[FIVE] > ZERO );


edgeCount[ONE][TWO] = ZERO;
edgeCount[TWO][THREE] = ZERO;
edgeCount[THREE][FOUR] = ZERO;
edgeCount[FOUR][FIVE] = ZERO;
edgeCount[ONE][FIVE] = ZERO;
edgeCount[ONE][THREE] = ZERO;
edgeCount[ONE][FOUR] = ZERO;


for(ne = firstEdge(&g[C], vertRename[ONE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne)  == vertRename[TWO] )
      ++edgeCount[ONE][TWO];
    else
      if( vertListOtherEnd(&g[C], ne)  == vertRename[THREE] )
        ++edgeCount[ONE][THREE];
      else
        if( vertListOtherEnd(&g[C], ne)  == vertRename[FOUR] )
          ++edgeCount[ONE][FOUR];
        else
          if( vertListOtherEnd(&g[C], ne)  == vertRename[FIVE] )
            ++edgeCount[ONE][FIVE];
  }


for(ne = firstEdge(&g[C], vertRename[THREE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne)  == vertRename[TWO] )
      ++edgeCount[TWO][THREE];
    else
      if( vertListOtherEnd(&g[C], ne)  == vertRename[FOUR] )
        ++edgeCount[THREE][FOUR];
}


for(ne = firstEdge(&g[C], vertRename[FIVE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
    if( vertListOtherEnd(&g[C], ne)  == vertRename[FOUR] )
      ++edgeCount[FOUR][FIVE];
  }

assert( edgeCount[ONE][TWO] > ZERO );
assert( edgeCount[TWO][THREE] > ZERO );
assert( edgeCount[THREE][FOUR] > ZERO );
assert( edgeCount[FOUR][FIVE] > ZERO );
assert( edgeCount[ONE][FIVE] > ZERO );
assert( edgeCount[ONE][THREE] > ZERO );
assert( edgeCount[ONE][FOUR] > ZERO );

for( i = ZERO; i < edgeCount[TWO][THREE]; i++ )
for( j = ZERO; j < edgeCount[THREE][FOUR]; j++ )
for( k = ZERO; k < edgeCount[FOUR][FIVE]; k++ )
for( m = ZERO; m < edgeCount[ONE][FIVE]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO ) +
       ( ( k == ZERO )?ONE:ZERO ) +
       ( ( m == ZERO )?ONE:ZERO);
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[TWO][THREE]; i++ )
for( j = ZERO; j < edgeCount[THREE][FOUR]; j++ )
for( k = ZERO; k < edgeCount[ONE][FIVE] + edgeCount[FOUR][FIVE]; k++ )
for( m = ZERO; m < edgeCount[ONE][FOUR]; m++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO ) +
       ( ( k == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[THREE][FOUR]; i++ )
for( j = ZERO; j < edgeCount[ONE][FOUR]; j++ )
for( k = ZERO; k < edgeCount[FOUR][FIVE]; k++ )
for( m = ZERO; m < edgeCount[ONE][TWO]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO ) +
       ( ( k == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[THREE][FOUR]; i++ )
for( j = ZERO; j < edgeCount[ONE][FOUR] + edgeCount[FOUR][FIVE]; j++ )
for( k = ZERO; k < edgeCount[ONE][TWO]; k++ )
for( m = ZERO; m < edgeCount[ONE][FIVE]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[FOUR][FIVE]; i++ )
for( j = ZERO; j < edgeCount[ONE][FOUR] + edgeCount[THREE][FOUR]; j++ )
for( k = ZERO; k < edgeCount[TWO][THREE]; k++ )
for( m = ZERO; m < edgeCount[ONE][TWO]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][FOUR] + edgeCount[THREE][FOUR] + edgeCount[FOUR][FIVE]; i++ )
for( j = ZERO; j < edgeCount[ONE][TWO]; j++ )
for( k = ZERO; k < edgeCount[TWO][THREE]; k++ )
for( m = ZERO; m < edgeCount[ONE][FIVE]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO);
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][TWO] + edgeCount[TWO][THREE]; i++ )
for( j = ZERO; j < edgeCount[ONE][FOUR] + edgeCount[THREE][FOUR]; j++ )
for( k = ZERO; k < edgeCount[ONE][FIVE]; k++ )
for( m = ZERO; m < edgeCount[ONE][THREE]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO ) +
       ( ( k == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][FIVE] + edgeCount[ONE][FOUR] + edgeCount[THREE][FOUR]; i++ )
for( j = ZERO; j < edgeCount[ONE][TWO] + edgeCount[TWO][THREE]; j++ )
for( k = ZERO; k < edgeCount[ONE][THREE]; k++ )
for( m = ZERO; m < edgeCount[FOUR][FIVE]; m++ )
  {
    xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }


return( ONE );

} /* end degseq1220 */


/*                                                  */
/*                                                  */
/*                end degseq1220                    */
/*                                                  */
/****************************************************/





