#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "core/tutte.h"

/****************************************************************/
/*                                                              */
/*                 start degseq2210                             */
/*                                                              */
/*                                                              */

/*
Precondition: C--index to graph array pointing to graph with degseq 2210
              for the underlying graph
              vertDeg and vertIndex initialized to identify degree and 
              canonical label for each vertex
              tutteMat2 and tutteMat2X are arrays with
              values for current state of the computation

Postcondition:  tutteMat2 and tutteMat2X augmented by the tutte 
                poly of this graph


Return: 1 to signfy graph needs replacing

*/


int degseq2210(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X)
{
int vertRename[TEN],        /* canonical naming of vertices                */
    edgeCount[TEN][TEN],    /* numberof edges from [*][] to [][*]          */
    i,                      /* for parameter                               */
    j,
    ne;                     /* location of edge                            */

//printf("K(5) - (2, 4) - (2, 5)\n"); 
//printf("evaluateFivesb-1 rtn\n");

for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == FOUR ) 
    {
       vertRename[ONE] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == FOUR ) && ( vertIndex[i] != vertRename[ONE] ) ) 
    {
       vertRename[ THREE] = vertIndex[i];
    }

for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == TWO ) 
    {
       vertRename[ TWO] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == THREE ) && ( isadj(vertRename[ONE], vertIndex[i],&g[C]) ) ) 
    {
       vertRename[FIVE] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == THREE ) && ( vertIndex[i] != vertRename[FIVE] )
                   && ( isadj(vertRename[THREE], vertIndex[i],&g[C]) ) ) 
    {
       vertRename[FOUR] = vertIndex[i];
       break;
    }


for( i = ZERO; i < TEN; i++ )
for( j = ZERO; j < TEN; j++ )
  edgeCount[i][j] = ZERO;

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
  }


for(ne = firstEdge(&g[C], vertRename[THREE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[FOUR] )
       ++edgeCount[THREE][FOUR];
     else
       if( vertListOtherEnd(&g[C], ne)  == vertRename[FIVE] )
         ++edgeCount[THREE][FIVE];
  }


for(ne = firstEdge(&g[C], vertRename[FOUR]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[FIVE] )
       ++edgeCount[FOUR][FIVE];
  }

completePolyWithNoX(edgeCount[1][2],
                    edgeCount[2][3] + edgeCount[1][3],
                    edgeCount[1][4],
                    edgeCount[1][5],
                    edgeCount[3][4],
                    edgeCount[3][5],
                    edgeCount[4][5],
                    tutteMat2,
                    tutteMat2X);
completePolyWithX(edgeCount[2][3],
                  edgeCount[1][3],
                  edgeCount[1][4],
                  edgeCount[1][5],
                  edgeCount[3][4],
                  edgeCount[3][5],
                  edgeCount[4][5],
                  tutteMat2,
                  tutteMat2X);

return(ONE);

} /* end degseq2210 */

/*                                                              */
/*                                                              */
/*                   end degseq2210                             */
/*                                                              */
/*                                                              */
/****************************************************************/
/*                                                              */
/*                 start degseq50                               */
/*                                                              */
/*                                                              */
/*
Precondition: C--index to graph array pointing to graph with degseq 50 
              for the underlying graph
              vertDeg and vertIndex initialized to identify degree and 
              canonical labels of the vertices
              tutteMat2 and tutteMat2X are arrays with
              values for current state of the computation

Postcondition:  tutteMat2 and tutteMat2X are augmented by the value 
                of the tutte poly of this graph

Return: 1 to signfy graph needs replacing

*/
int degseq50(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X)
{
int i,                     /* for parameter                                    */
    j,
    k,
    m,
    v1,                    /* location of vertex                               */
    xp,                    /* degree in x of term                              */
    yp,                    /* degree in y of term                              */
    ne,                    /* location of edge                                 */ 
    vertRename[TEN],        /* canonical labelling                              */
    edgeCount[TEN][TEN];     /* incidence of [*][] with [][*]                    */

vertRename[ONE] = vertIndex[ONE];
vertRename[TWO] = vertListOtherEnd(&g[C], firstEdge(&g[C], vertRename[ONE])); 


for(ne = firstEdge(&g[C], vertRename[TWO]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     v1 = vertListOtherEnd(&g[C], ne); 
     if( v1 != vertRename[ONE] ) 
       {
          vertRename[THREE] = v1;
          break;
       }
  }


for(ne = firstEdge(&g[C], vertRename[THREE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     v1 = vertListOtherEnd(&g[C], ne);  
     if( v1 != vertRename[TWO] ) 
       {
          vertRename[FOUR] = v1;
          break;
       }
  }



for(ne = firstEdge(&g[C], vertRename[FOUR]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     v1 = vertListOtherEnd(&g[C], ne); 
     if( v1 != vertRename[THREE] ) 
       {
          vertRename[FIVE] = v1;
          break;
       }
  }

assert( vertRename[ONE] > ZERO );
assert( vertRename[TWO] > ZERO );
assert( vertRename[THREE] > ZERO );
assert( vertRename[FOUR] > ZERO );
assert( vertRename[FIVE] > ZERO );

edgeCount[ONE][TWO] = ZERO;
edgeCount[TWO][THREE]= ZERO;
edgeCount[THREE][FOUR]= ZERO;
edgeCount[FOUR][FIVE]= ZERO;
edgeCount[ONE][FIVE]= ZERO;


for(ne = firstEdge(&g[C], vertRename[ONE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[TWO] )
       ++edgeCount[ONE][TWO];
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


for(ne = firstEdge(&g[C], vertRename[FOUR]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[FIVE] )
       ++edgeCount[FOUR][FIVE];
  }

assert( edgeCount[ONE][TWO] > ZERO );
assert( edgeCount[TWO][THREE] > ZERO );
assert( edgeCount[THREE][FOUR] > ZERO );
assert( edgeCount[FOUR][FIVE] > ZERO );
assert( edgeCount[ONE][FIVE] > ZERO );





for( m = ONE; m < edgeCount[ONE][TWO]; m++ )
  {
     for( i = ZERO; i < edgeCount[TWO][THREE]; i++ )
     for( j = ZERO; j < edgeCount[THREE][FOUR]; j++ )
     for( k = ZERO; k < edgeCount[FOUR][FIVE] + edgeCount[ONE][FIVE]; k++ )
       {
       	  xp = ( ( k == ZERO )?ONE:ZERO);
	  yp = i + j + k + m;
	  tutteMat2[yp][xp]++;
       }
     for( i = ZERO; i < edgeCount[TWO][THREE]; i++ )
     for( j = ZERO; j < edgeCount[FOUR][FIVE]; j++ )
     for( k = ZERO; k < edgeCount[ONE][FIVE]; k++ )
       {
     	  xp = ( ( k == ZERO )?ONE:ZERO ) + ( ( j == ZERO )?ONE:ZERO );
    	  yp = i + j + k + m;
    	  tutteMat2[yp][xp]++;
       }
     for( i = ZERO; i < edgeCount[THREE][FOUR]; i++ )
     for( j = ZERO; j < edgeCount[FOUR][FIVE]; j++ )
     for( k = ZERO; k < edgeCount[ONE][FIVE]; k++ )
       {
     	  xp = ( ( i == ZERO )?ONE:ZERO ) + ( ( k == ZERO )?ONE:ZERO ) + ( ( j == ZERO )?ONE:ZERO );
    	  yp = i + j + k + m;
    	  tutteMat2[yp][xp]++;
       }
  }


for( i = ZERO; i < edgeCount[TWO][THREE]; i++ )
for( j = ZERO; j < edgeCount[THREE][FOUR]; j++ )
for( k = ZERO; k < edgeCount[FOUR][FIVE]; k++ )
for( m = ZERO; m < edgeCount[ONE][FIVE]; m++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO ) +
       ( ( j == ZERO )?ONE:ZERO ) +
       ( ( k == ZERO )?ONE:ZERO ) +
       ( ( m == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

fixedfourcycle(edgeCount[TWO][THREE],
               edgeCount[THREE][FOUR],
               edgeCount[FOUR][FIVE],
               edgeCount[ONE][FIVE],
               tutteMat2,
               tutteMat2X);


return( ONE );

} /* end degseq50 */

/*                                                              */
/*                                                              */
/*                 start degseq50                               */
/*                                                              */
/*                                                              */
/****************************************************************/
/*                                                              */
/*                 start degseq230house                         */
/*                                                              */
/*                                                              */

/*
Precondition: C--index to graph array pointing to graph with degseq 230 
             for the underlying graph that is not K(2,3) 
              vertDeg and vertIndex initialized to identify degree and 
              canonical label for each vertex
              tutteMat2 and tutteMat2X are arrays with
              values for current state of the computation

Postcondition:  tutteMat2 and tutteMat2X are augmented by the value of 
                the tutte poly of this graph

Return: 1 to signfy graph needs replacing

*/
int degseq230house(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X)
{
int i,                   /* for paramter                             */
    j,
    k,
    m,
    xp,                  /* degree of x term                         */
    yp,                  /* degree of y term                         */ 
    vertRename[TEN],      /* canonical labelling                      */
    edgeCount[TEN][TEN],   /* incidence of vertex [*][] with [][*]     */
    ne;                  /* location of edge                         */
//printf("HOUSE \n");
//printGraph(&g[C]);

for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == THREE ) 
    {
       vertRename[ONE] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == THREE ) && ( vertIndex[i] != vertRename[ONE] ) ) 
    {
       vertRename[THREE] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE; i++ ) 
  if( ( vertDeg[i] == TWO ) && ( isadj(vertRename[ONE],vertIndex[i],&g[C]) ) 
                   && ( isadj(vertRename[THREE],vertIndex[i],&g[C]) ) ) 
    {
       vertRename[TWO] = vertIndex[i];
       break;
    }
  


for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == TWO ) && ( vertRename[TWO] != vertIndex[i] )
                   && ( isadj(vertRename[ONE],vertIndex[i],&g[C]) ) ) 
    {
       vertRename[FIVE] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == TWO ) && ( vertIndex[i] != vertRename[TWO] ) && ( vertIndex[i] != vertRename[FIVE] ) ) 
    {
       vertRename[FOUR] = vertIndex[i];
       break;
    }



edgeCount[ONE][TWO] = ZERO;
edgeCount[TWO][THREE] = ZERO;
edgeCount[THREE][FOUR] = ZERO;
edgeCount[FOUR][FIVE] = ZERO;
edgeCount[ONE][FIVE] = ZERO;
edgeCount[ONE][THREE] = ZERO;


for(ne = firstEdge(&g[C], vertRename[ONE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[TWO] )
       ++edgeCount[ONE][TWO];
     else
       if( vertListOtherEnd(&g[C], ne)  == vertRename[THREE] )
         ++edgeCount[ONE][THREE];
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


for(ne = firstEdge(&g[C], vertRename[FOUR]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[FIVE] )
       ++edgeCount[FOUR][FIVE];
  }


assert( edgeCount[ONE][TWO] > ZERO );
assert( edgeCount[TWO][THREE] > ZERO );
assert( edgeCount[THREE][FOUR] > ZERO );
assert( edgeCount[FOUR][FIVE] > ZERO );
assert( edgeCount[ONE][FIVE] > ZERO );
assert( edgeCount[ONE][THREE] > ZERO );

for( m = ZERO; m < edgeCount[ONE][TWO]; m++ )
for( i = ZERO; i < edgeCount[TWO][THREE] + edgeCount[ONE][THREE]; i++ )
for( j = ZERO; j < edgeCount[ONE][FIVE]; j++ )
for( k = ZERO; k < edgeCount[THREE][FOUR] + edgeCount[FOUR][FIVE]; k++ )
  {
     xp = ( ( k == ZERO )?ONE:ZERO );
     yp = i + j +  k + m;
     tutteMat2[yp][xp]++;
  }


for( i = ZERO; i < edgeCount[TWO][THREE]; i++ )
for( j = ZERO; j < edgeCount[THREE][FOUR]; j++ )
for( k = ZERO; k < edgeCount[FOUR][FIVE]; k++ )
for( m = ZERO; m < edgeCount[ONE][FIVE]; m++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO ) +
        ( ( j == ZERO )?ONE:ZERO ) +
        ( ( k == ZERO )?ONE:ZERO ) +
        ( ( m == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

for( m = ZERO; m < edgeCount[ONE][TWO]; m++ )
for( i = ZERO; i < edgeCount[TWO][THREE] + edgeCount[ONE][THREE]; i++ )
for( j = ZERO; j < edgeCount[THREE][FOUR]; j++ )
for( k = ZERO; k < edgeCount[FOUR][FIVE]; k++ )
  {
     xp = ( ( j == ZERO )?ONE:ZERO ) +
        ( ( k == ZERO )?ONE:ZERO );
     yp = i + j + k  + m;
     tutteMat2[yp][xp]++;
  }

for( m = ZERO; m < edgeCount[ONE][TWO]; m++ )
for( i = ZERO; i < edgeCount[THREE][FOUR]; i++ )
for( j = ZERO; j < edgeCount[ONE][FIVE]; j++ )
for( k = ZERO; k < edgeCount[FOUR][FIVE]; k++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO ) +
        ( ( j == ZERO )?ONE:ZERO ) +
        ( ( k == ZERO )?ONE:ZERO );
     yp=i+j+k+m;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][THREE]; i++ )
for( j = ZERO; j < edgeCount[TWO][THREE]; j++ )
for( k = ZERO; k < edgeCount[THREE][FOUR]; k++ )
for( m = ZERO; m < edgeCount[FOUR][FIVE]; m++ )
  {
     xp = ( ( j == ZERO )?ONE:ZERO ) +
        ( ( k == ZERO )?ONE:ZERO ) +
        ( ( m == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][THREE]; i++ )
for( j = ZERO; j < edgeCount[ONE][FIVE]; j++ )
for( k = ZERO; k < edgeCount[TWO][THREE]; k++ )
for( m = ZERO; m < edgeCount[THREE][FOUR] + edgeCount[FOUR][FIVE]; m++ )
  {
     xp = ( ( k == ZERO )?ONE:ZERO ) +
        ( ( m == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }


return( ONE );

} /* end degseq230house */

/*                                                              */
/*                                                              */
/*                   end degseq230house                         */
/*                                                              */
/*                                                              */
/****************************************************************/
/*                                                              */
/*                 start degseq230k23                           */
/*                                                              */
/*                                                              */

/*
Precondition: C--index to graph array pointing to graph with degseq 
              230 for the underlying graph that is K(2,3)
              vertDeg and vertIndex initialized to identify degree 
              and canonical label for each vertex 
              tutteMat2 and tutteMat2X are arrays with
              values for current state of the computation

Postcondition: tutteMat2 and tutteMat2X are augmented by the value 
               of the tutte poly of this graph 

Return: 1 to signfy graph needs replacing

*/
int degseq230k23(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X)
{
int i,                    /* for paramter                                    */
    j,
    k,
    m,
    ne,                   /* location of edge                                */
    xp,                   /* degree in x of term                             */
    yp,                   /* degree in y of term                             */
    vertRename[TEN],       /* canonical labelling                             */       
    edgeCount[TEN][TEN];    /* incidence of vertex [*][] with [][*]            */


//printf("K(2,3)\n");


j = ZERO;
for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == THREE ) 
    {
       ++j;
       vertRename[j] = vertIndex[i];
    }

for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == TWO ) 
    {
       ++j;
       vertRename[j] = vertIndex[i];
    }


edgeCount[ONE][THREE] = ZERO;
edgeCount[ONE][FOUR] = ZERO;
edgeCount[ONE][FIVE] = ZERO;
edgeCount[TWO][THREE] = ZERO;
edgeCount[TWO][FOUR] = ZERO;
edgeCount[TWO][FIVE] = ZERO;

for(ne = firstEdge(&g[C], vertRename[ONE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
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


assert( edgeCount[ONE][THREE] > ZERO );
assert( edgeCount[ONE][FOUR] > ZERO );
assert( edgeCount[ONE][FIVE] > ZERO );
assert( edgeCount[TWO][THREE] > ZERO );
assert( edgeCount[TWO][FOUR] > ZERO );
assert( edgeCount[TWO][FIVE] > ZERO );


for( i= ZERO; i< edgeCount[ONE][FOUR]; i++ )
for( j= ZERO; j< edgeCount[TWO][THREE]; j++ )
for( k= ZERO; k< edgeCount[TWO][FOUR]; k++ )
for( m= ZERO; m< edgeCount[TWO][FIVE]; m++ )
  {
     xp = ( ( k == ZERO )?ONE:ZERO ) +
        ( ( i == ZERO )?ONE:ZERO ) +
        ( ( j == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

// had ; insterad of +--test-test-test
for( i= ZERO; i< edgeCount[TWO][THREE]; i++ )
for( j= ZERO; j< edgeCount[TWO][FOUR]; j++ )
for( k= ZERO; k< edgeCount[ONE][FOUR]; k++ )
for( m= ZERO; m< edgeCount[ONE][FIVE]; m++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO ) +
        ( ( j == ZERO )?ONE:ZERO ) +
        ( ( k == ZERO )?ONE:ZERO ) +
        ( ( m == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

for( m = ZERO; m < edgeCount[TWO][THREE]; m++ )
for( i = ZERO; i < edgeCount[ONE][FOUR] + edgeCount[TWO][FOUR]; i++ )
for( j = ZERO; j < edgeCount[ONE][FIVE]; j++ )
for( k = ZERO; k < edgeCount[TWO][FIVE]; k++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO ) +
        ( ( j == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][FOUR]; i++ )
for( j = ZERO; j < edgeCount[ONE][FIVE]; j++ )
for( k = ZERO; k < edgeCount[TWO][FIVE]; k++ )
for( m = ZERO; m < edgeCount[ONE][THREE]; m++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO ) +
        ( ( j == ZERO )?ONE:ZERO ) +
        ( ( k == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][FOUR]; i++)
for( j = ZERO; j < edgeCount[ONE][FIVE] + edgeCount[TWO][FIVE]; j++ )
for( k = ZERO; k < edgeCount[TWO][THREE]; k++ )
for( m = ZERO; m < edgeCount[ONE][THREE]; m++ )
  {
     xp = ( ( j == ZERO )?ONE:ZERO ) +
        ( ( i == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][FIVE]; i++ )
for( j = ZERO; j < edgeCount[TWO][THREE] + edgeCount[ONE][FOUR]; j++ )
for( k = ZERO; k < edgeCount[ONE][THREE]; k++ )
for( m = ZERO; m < edgeCount[TWO][FOUR]; m++ )
  {
     xp = ( ( j == ZERO )?ONE:ZERO ) +
        ( ( i == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }


for( i = ZERO; i < edgeCount[TWO][THREE] + edgeCount[ONE][FOUR] + edgeCount[ONE][FIVE]; i++ )
for( j = ZERO; j < edgeCount[ONE][THREE]; j++ )
for( k = ZERO; k < edgeCount[TWO][FOUR]; k++ )
for( m = ZERO; m < edgeCount[TWO][FIVE]; m++ )
  {
     xp = ( ( i== ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }


return( ONE );

} /* end degseq230k23 */

/*                                                              */
/*                 end degseq230k23                             */
/*                                                              */
/*                                                              */
/*                                                              */
/****************************************************************/
/*                                                              */
/*                 start degseq131c4                            */
/*                                                              */
/*                                                              */

/*
Precondition: C--index to graph array pointing to graph with degseq 131
              for the underlying graph designated as c4 
              vertDeg and vertIndex initialized to identify degree and 
              canonical label for each vertex
              tutteMat2 and tutteMat2X are arrays with
              values for current state of the computation

Postcondition: tutteMat2 and tutteMat2X are augmented by the value 
               of the tutte poly of this graph

Return: 1 to signfy graph needs replacing

*/
int degseq131c4(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X)
{
int i,                           /* for parameter                       */
    k,
    j,
    m,
    xp,                          /* degree of term in x                  */
    yp,                          /* degree of term in y                  */
    ne,                          /* location of edge                     */
    vertRename[TEN],              /* canonical labelling of vertices      */
    edgeCount[TEN][TEN];           /* incidence of vertex [*][] with [][*] */

//printf("degseq131c4\n");
for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == ONE) 
    {
       vertRename[ONE] = vertIndex[i];
       break;
    }

vertRename[TWO] = vertListOtherEnd(&g[C], firstEdge(&g[C], vertRename[ONE])); 

j = TWO;
for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == TWO ) && ( isadj(vertIndex[i],vertRename[TWO],&g[C]) ) ) 
    {
       ++j;
       vertRename[j] = vertIndex[i];
    }

for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == TWO ) && !( isadj(vertIndex[i],vertRename[TWO],&g[C]) ) ) 
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
edgeCount[TWO][FOUR] = ZERO;
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


for(ne = firstEdge(&g[C], vertRename[FIVE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[THREE] )
       ++edgeCount[THREE][FIVE];
     else
       if( vertListOtherEnd(&g[C], ne)  == vertRename[FOUR] )
         ++edgeCount[FOUR][FIVE];
  }

assert( edgeCount[ONE][TWO] > ZERO );
assert( edgeCount[TWO][THREE] > ZERO );
assert( edgeCount[TWO][FOUR] > ZERO );
assert( edgeCount[THREE][FIVE] > ZERO );
assert( edgeCount[FOUR][FIVE] > ZERO );


for( i = ZERO; i < edgeCount[ONE][TWO]; i++ )
for( j = ZERO; j < edgeCount[TWO][FOUR]; j++ )
for( k = ZERO; k < edgeCount[FOUR][FIVE]; k++ )
for( m = ZERO; m < edgeCount[THREE][FIVE]; m++ )
  {
     xp = ( ( j == ZERO )?ONE:ZERO ) +
        ( ( i == ZERO )?ONE:ZERO ) +
        ( ( k == ZERO )?ONE:ZERO ) +
        ( ( m == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }



for( i = ZERO; i < edgeCount[ONE][TWO]; i++ )
for( j = ZERO; j < edgeCount[TWO][FOUR]; j++ )
for( k = ZERO; k < edgeCount[FOUR][FIVE]; k++ )
for( m = ZERO; m < edgeCount[TWO][THREE]; m++ )
  {
     xp = ( ( j == ZERO )?ONE:ZERO ) +
        ( ( i == ZERO )?ONE:ZERO ) +
        ( ( k == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }



for( i = ZERO; i < edgeCount[ONE][TWO]; i++ )
for( j = ZERO; j < edgeCount[TWO][FOUR] + edgeCount[FOUR][FIVE]; j++ )
for( k = ZERO; k < edgeCount[TWO][THREE]; k++ )
for( m = ZERO; m < edgeCount[THREE][FIVE]; m++ )
  {
     xp = ( ( j == ZERO )?ONE:ZERO ) +
        ( ( i == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }



return( ONE );

} /* end degseq131c4 */


/*                                                              */
/*                                                              */
/*                  end degseq131c4                             */
/*                                                              */
/*                                                              */
/****************************************************************/





