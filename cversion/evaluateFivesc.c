#include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>


/******************************************************/
/*                                                    */
/*                                                    */
/*          start degse1131triangle                   */
/*                                                    */
/*                                                    */

/*
Precondition: C--index to graph array pointing to graph with degree sequence 131
              that has a triangle with appendages as the underlying graph 
              vertDeg and vertIndex initialized to identify degree and
              canonical label for each vertex
              tutteMat2 and tutteMat2X are arrays with values for the 
              current state of the computation

Postcondition: tutteMat2 and tutteMat2X augmented by the tutte
               poly of this graph

Return: 1 to signify graph needs replacing

*/

int degseq131triangle(
                      int C,
                      int vertDeg[],
                      int vertIndex[],
                      TUTTE tutteMat2,
                      TUTTEO tutteMat2X
                     )
{
int i,                  /* for parameter                                 */
    j,
    k,
    m,
    ne,                 /* location of edge                              */
    xp,                 /* degree of x in monomial                       */
    yp,                 /* degree of y in monomial                       */
    vertRename[10],     /* canonical labelling of vertices               */
    edgeCount[10][10];  /* incidence for vertex [*][] and [][*]          */ 

//printf("evaluateFivesc\n");
for( i = ZERO; i < TEN; i++ )
  vertRename[i] = ZERO;

 j= ZERO;
for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i]== ONE ) 
    {
       ++j;
       vertRename[j] = vertIndex[i];
       break;
  }
vertRename[TWO] = vertListOtherEnd(&g[C], firstEdge(&g[C], vertRename[ONE]));

for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == THREE ) 
    {
       vertRename[THREE] = vertIndex[i];
       break;
    }

j = THREE;
for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == TWO ) && ( vertIndex[i] != vertRename[TWO] ) ) 
    {
       ++j;
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
edgeCount[TWO][THREE] = ZERO;
edgeCount[THREE][FIVE] = ZERO;
edgeCount[THREE][FOUR] = ZERO;
edgeCount[FOUR][FIVE] = ZERO;

for(ne = firstEdge(&g[C], vertRename[THREE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[TWO] )
       ++edgeCount[TWO][THREE];
     else
       if( vertListOtherEnd(&g[C], ne)  == vertRename[FOUR] )
         ++edgeCount[THREE][FOUR];
       else
         if( vertListOtherEnd(&g[C], ne)  == vertRename[FIVE] )
           ++edgeCount[THREE][FIVE];
  }


for(ne = firstEdge(&g[C], vertRename[FIVE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if ( vertListOtherEnd(&g[C], ne)  == vertRename[FOUR] )
       ++edgeCount[FOUR][FIVE];
  }


for(ne = firstEdge(&g[C], vertRename[ONE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[TWO] )
       ++edgeCount[ONE][TWO];
  }

assert( edgeCount[ONE][TWO] > ZERO);
assert( edgeCount[TWO][THREE] > ZERO);
assert( edgeCount[THREE][FOUR] > ZERO);
assert( edgeCount[THREE][FIVE] > ZERO);
assert( edgeCount[FOUR][FIVE] > ZERO);
 
for( i = ZERO; i < edgeCount[FOUR][FIVE]; i++ )
for( j = ZERO; j < edgeCount[THREE][FIVE] ;j++ )
for( k = ZERO; k < edgeCount[TWO][THREE]; k++ )
for( m = ZERO; m < edgeCount[ONE][TWO]; m++ )
  {
     xp=( ( i == ZERO )?ONE:ZERO ) +
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
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }


return( ONE );

} /* end degseq131triangle */

/*                                                    */
/*                                                    */
/*          end  degseq131triangle                    */
/*                                                    */
/******************************************************/
/*                                                    */
/*                                                    */
/*          start degseq212                           */
/*                                                    */
/*                                                    */


/*
Precondition: C--index to graph array pointing to graph with degree sequence 212 
              for the underlying graph
              vertDeg and vertIndex initialized to identify degree and
              canonical label for eaxch vertex
              tutteMat2 and tutteMat2X are arrays with values for the 
              current state of the computation

Postcondition: tutteMat2 and tutteMat2X augmented by the tutte
               poly of this graph

Return: 1 to signify graph needs replacing

*/
int degseq212(
              int C,
              int vertDeg[],
              int vertIndex[],
              TUTTE tutteMat2,
              TUTTEO tutteMat2X
             )
{
int i,                  /* for parameter                                 */
    j,
    k,
    m,
    ne,                 /* location of edge                              */
    xp,                 /* degree of x in monomial                       */
    yp,                 /* degree of y in monomial                       */
    vertRename[10],     /* canonical labelling of vertices               */
    edgeCount[10][10];  /* incidence for vertex [*][] and [][*]          */ 



j = ZERO;
for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == ONE ) 
    {
       ++j;
       vertRename[j] = vertIndex[i];
    }

for( i = ONE; i <= FIVE; i++ )
  if(vertDeg[i]== TWO ) 
    {
       ++j;
       vertRename[j] = vertIndex[i];
    }

for( i = ONE; i <= FIVE; i++ )
  if((  vertDeg[i] == THREE ) && ( isadj(vertIndex[i],vertRename[ONE],&g[C]) ) ) 
    {
       ++j;
       vertRename[j] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE; i++ )
  if( ( vertDeg[i] == THREE ) && ( isadj(vertIndex[i],vertRename[TWO],&g[C]) ) ) 
    {
       ++j;
       vertRename[j] = vertIndex[i];
       break;
    }

assert( vertRename[ONE] > ZERO );
assert( vertRename[TWO] > ZERO );
assert( vertRename[THREE] > ZERO );
assert( vertRename[FOUR] > ZERO );
assert( vertRename[FIVE] > ZERO );


edgeCount[ONE][FOUR] = ZERO;
edgeCount[TWO][FIVE] = ZERO;
edgeCount[FOUR][FIVE] = ZERO; 
edgeCount[THREE][FOUR] = ZERO;
edgeCount[THREE][FIVE] = ZERO;


for(ne = firstEdge(&g[C], vertRename[FOUR]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne) == vertRename[ONE] )
       ++edgeCount[ONE][FOUR];
     else
       if( vertListOtherEnd(&g[C], ne) == vertRename[FIVE] )
         ++edgeCount[FOUR][FIVE];
       else
         if( vertListOtherEnd(&g[C], ne)  == vertRename[THREE] )
           ++edgeCount[THREE][FOUR];
  }


for(ne = firstEdge(&g[C], vertRename[FIVE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[TWO] )
       ++edgeCount[TWO][FIVE];
     else
       if( vertListOtherEnd(&g[C], ne)  == vertRename[THREE] )
         ++edgeCount[THREE][FIVE];
  }
assert( edgeCount[ONE][FOUR] > ZERO );
assert( edgeCount[TWO][FIVE] > ZERO );
assert( edgeCount[THREE][FOUR] > ZERO );
assert( edgeCount[THREE][FIVE] > ZERO );
assert( edgeCount[FOUR][FIVE] > ZERO );

for( i = ZERO; i < edgeCount[ONE][FOUR]; i++ )
for( j = ZERO; j < edgeCount[FOUR][FIVE]; j++ )
for( k = ZERO; k < edgeCount[TWO][FIVE]; k++ )
for( m = ZERO; m < edgeCount[THREE][FIVE]; m++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO ) +
        ( (j == ZERO )?ONE:ZERO ) +
        ( (k == ZERO )?ONE:ZERO ) +
        ( (m == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][FOUR]; i++ )
for( j = ZERO; j < edgeCount[TWO][FIVE]; j++ )
for( k = ZERO; k < edgeCount[THREE][FIVE] + edgeCount[FOUR][FIVE]; k++ )
for( m = ZERO; m < edgeCount[THREE][FOUR]; m++ )
  {
     xp=( ( i == ZERO )?ONE:ZERO ) +
        ( ( j == ZERO )?ONE:ZERO ) +
        ( ( k == ZERO )?ONE:ZERO );
    yp = i + j + k + m;
    tutteMat2[yp][xp]++;
  }


return( ONE );

} /* end degseq212 */

/*                                                    */
/*                                                    */
/*          end degseq212                             */
/*                                                    */
/******************************************************/
/*                                                    */
/*                                                    */
/*          start degseq1022                          */
/*                                                    */
/*                                                    */



/*
Precondition: C--index to graph array pointing to graph with degree sequence 1022 
              for the underlying graph
              vertDeg and vertIndex initialized to identify degree and
              canonical label for each vertex
              tutteMat2 and tutteMat2X are arrays with values for the 
              current state of the computation

Postcondition: tutteMat2 and tutteMat2X augmented by the tutte
               poly of this graph

Return: 1 to signify graph needs replacing

*/



int degseq1022(
               int C,
               int vertDeg[],
               int vertIndex[],
               TUTTE tutteMat2,
               TUTTEO tutteMat2X
              )
{
int i,                  /* for parameter                                 */
    j,
    k,
    m,
    ne,                 /* location of edge                              */
    xp,                 /* degree of x in monomial                       */
    yp,                 /* degree of y in monomial                       */
    vertRename[10],     /* canonical labelling of vertices               */
    edgeCount[10][10];  /* incidence for vertex [*][] and [][*]          */ 

j = ZERO;
for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == ONE ) 
    {
       ++j;
       vertRename[j] = vertIndex[i];
    }

for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == FOUR ) 
    {
       ++j;
       vertRename[j] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == TWO ) 
    {
       ++j;
       vertRename[j] = vertIndex[i];
    }

assert( vertRename[ONE] > ZERO );
assert( vertRename[TWO] > ZERO );
assert( vertRename[THREE] > ZERO );
assert( vertRename[FOUR] > ZERO );
assert( vertRename[FIVE] > ZERO );


edgeCount[ONE][THREE] = ZERO;
edgeCount[TWO][THREE] = ZERO;
edgeCount[THREE][FOUR] = ZERO;
edgeCount[THREE][FIVE] = ZERO;
edgeCount[FOUR][FIVE] = ZERO;



for(ne = firstEdge(&g[C], vertRename[THREE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
//ne = firstEdge(&g[C], vertRename[THREE]);  //g[C].edg[g[C].vrtx[vertRename[THREE]].fedge].front;
//while( ne != LIST_END ) 
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[ONE] )
       ++edgeCount[ONE][THREE];
     else
       if( vertListOtherEnd(&g[C], ne)  == vertRename[TWO])
         ++edgeCount[TWO][THREE];
       else
         if(vertListOtherEnd(&g[C], ne)  == vertRename[FOUR] )
           ++edgeCount[THREE][FOUR];
         else
           if( vertListOtherEnd(&g[C], ne)  == vertRename[FIVE] )
             ++edgeCount[THREE][FIVE];
  }



for(ne = firstEdge(&g[C], vertRename[FOUR]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[FIVE])
       ++edgeCount[FOUR][FIVE];
  }
assert( edgeCount[ONE][THREE] > ZERO );
assert( edgeCount[TWO][THREE] > ZERO );
assert( edgeCount[THREE][FOUR] > ZERO );
assert( edgeCount[THREE][FIVE] > ZERO );
assert( edgeCount[FOUR][FIVE] > ZERO );

for( i = ZERO; i < edgeCount[ONE][THREE]; i++ )
for( j = ZERO; j < edgeCount[TWO][THREE]; j++ )
for( k = ZERO; k < edgeCount[THREE][FOUR]; k++ )
for( m = ZERO; m < edgeCount[THREE][FIVE]; m++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO ) +
        ( ( j == ZERO )?ONE:ZERO ) +
        ( ( k == ZERO )?ONE:ZERO ) +
        ( ( m == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO;i < edgeCount[ONE][THREE]; i++ )
for( j = ZERO;j < edgeCount[TWO][THREE]; j++ )
for( k = ZERO;k < edgeCount[THREE][FIVE] + edgeCount[THREE][FOUR]; k++ )
for( m = ZERO;m < edgeCount[FOUR][FIVE]; m++ )
  {
     xp=( ( i == ZERO )?ONE:ZERO ) +
        ( ( j == ZERO )?ONE:ZERO ) +
        ( ( k == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }


return( ONE );

} /* end degseq1022 */

/*                                                    */
/*                                                    */
/*          end degseq1022                            */
/*                                                    */
/******************************************************/
/*                                                    */
/*                                                    */
/*          start degseq1121                          */
/*                                                    */
/*                                                    */


/*
Precondition: C--index to graph array pointing to graph with degree sequence 1121
              for the underlying graph
              vertDeg and vertIndex initialized to identify degree and
              canonical label for each vertex
              tutteMat2 and tutteMat2X are arrays with values for the 
              current state of the computation

Postcondition: tutteMat2 and tutteMat2X augmented by the tutte
               poly of this graph


Return: 1 to signify graph needs replacing

*/

int degseq1121(
               int C,
               int vertDeg[],
               int vertIndex[],
               TUTTE tutteMat2,
               TUTTEO tutteMat2X
              )
{
int i,                  /* for parameter                                 */
    j,
    k,
    m,
    ne,                 /* location of edge                              */
    xp,                 /* degree of x in monomial                       */
    yp,                 /* degree of y in monomial                       */
    vertRename[10],     /* canonical labelling of vertices               */
    edgeCount[10][10];  /* incidence for vertex [*][] and [][*]          */ 

//printf("GOT INTO 1121\n");
for( i = ONE; i <= FIVE; i++ )
  if (vertDeg[i] == ONE ) 
    {
       vertRename[ONE] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE ;i++ )
  if( vertDeg[i] == FOUR ) 
    {
       vertRename[TWO] = vertIndex[i];
       break;
    }

for( i = ONE; i <= FIVE; i++ )
  if( vertDeg[i] == THREE ) 
    {
       vertRename[THREE] = vertIndex[i];
       break;
    }

j = THREE;
for( i= ONE; i <= FIVE; i++ )
  if( vertDeg[i] == TWO ) 
    {
       ++j;
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
edgeCount[TWO][THREE] = ZERO;
edgeCount[TWO][FOUR] = ZERO;
edgeCount[TWO][FIVE] = ZERO;
edgeCount[THREE][FOUR] = ZERO;
edgeCount[THREE][FIVE] = ZERO;


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
         else
           if( vertListOtherEnd(&g[C], ne) == vertRename[FIVE] )
             ++edgeCount[TWO][FIVE];
  }


for(ne = firstEdge(&g[C], vertRename[FOUR]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[THREE] )
       ++edgeCount[THREE][FOUR];
  }


for(ne = firstEdge(&g[C], vertRename[THREE]); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( vertListOtherEnd(&g[C], ne)  == vertRename[FIVE] )
       ++edgeCount[THREE][FIVE];
  }

assert( edgeCount[ONE][TWO] > ZERO );
assert( edgeCount[TWO][THREE] > ZERO );
assert( edgeCount[TWO][FOUR] > ZERO );
assert( edgeCount[TWO][FIVE] > ZERO );
assert( edgeCount[THREE][FOUR] > ZERO);
assert( edgeCount[THREE][FIVE] > ZERO);


for(i= ZERO;i<edgeCount[ONE][TWO];i++)
for(j= ZERO;j<edgeCount[TWO][FOUR];j++)
for(k= ZERO;k<edgeCount[TWO][FIVE];k++)
for(m= ZERO;m<edgeCount[THREE][FIVE];m++)
  {
     xp=((i== ZERO )?ONE:ZERO)+
        ((j== ZERO )?ONE:ZERO)+
        ((k== ZERO )?ONE:ZERO)+
        ((m== ZERO )?ONE:ZERO);
     yp=i+j+k+m;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][TWO]; i++ )
for( j = ZERO; j < edgeCount[TWO][FOUR]; j++ )
for( k = ZERO; k < edgeCount[TWO][FIVE] + edgeCount[THREE][FIVE] ;k++ )
for( m = ZERO; m < edgeCount[TWO][THREE]; m++ )
  {
     xp=( ( i == ZERO )?ONE:ZERO ) +
        ( ( j == ZERO )?ONE:ZERO ) +
        ( ( k == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][TWO] ;i++ )
for( j = ZERO; j < edgeCount[TWO][FOUR] + edgeCount[TWO][THREE]; j++ )
for( k = ZERO; k < edgeCount[TWO][FIVE]; k++ )
for( m = ZERO; m < edgeCount[THREE][FOUR]; m++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO ) +
        ( ( j == ZERO )?ONE:ZERO ) +
        ( ( k == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }

for( i = ZERO; i < edgeCount[ONE][TWO] ;i++ )
for( j = ZERO; j < edgeCount[TWO][THREE] + edgeCount[TWO][FOUR] + edgeCount[TWO][FIVE]; j++ )
for( k = ZERO; k < edgeCount[THREE][FOUR]; k++ )
for( m = ZERO; m < edgeCount[THREE][FIVE]; m++ )
  {
     xp = ( ( i == ZERO )?ONE:ZERO ) +
        ( ( j == ZERO )?ONE:ZERO );
     yp = i + j + k + m;
     tutteMat2[yp][xp]++;
  }


return( ONE );

} /* end degseq1121 */

/*                                                    */
/*                                                    */
/*          end degseq1121                            */
/*                                                    */
/******************************************************/


