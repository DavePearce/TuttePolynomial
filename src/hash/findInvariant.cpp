#include <stdio.h>
#include "nauty.h"
#include <assert.h>
#include <strings.h>
#define EXTDEFS 1

// left in for the moment, so it at least compiles
#include "core/tutte.h"

   
/*******************************************************************/
/*                                                                 */
/*                        start of findInvariant                   */
/*                                                                 */
   
/*

Precondition: address of graph g2 and instantiated variables
              m1 and array canong

Postcondition: graph unchanged but hash information now in
               m1 and canong (canonical labelling of nauty)

*/


void 
findInvariant(struct Graph *g2,int *m1,int canong[])
{/* 1 */

graph g[MAXN*MAXM];
nvector lab[MAXN], ptn[MAXN],active[MAXN],orbits[MAXN];
struct Graph g1;
int edges[EDGESIZE][TWO], 
    vt,                               /* location on vertex list                            */
    ed,                               /* location on edge list                              */
    edgename,                         /* identifies edge at ed                              */ 
    n,                                /* used as row and column indicators for nauty matrix */
    nv,
    next,
    m,                                /* storage requirements for graph                     */
    i,                                /* loop parameters                                    */
    j,
    k,
    translate[VERTEXSIZE],            /* rename to fit nauty                                */
    maxname,                          /* largest name in current graph                      */
    adjmat[VERTEXSIZE][VERTEXSIZE];   /* adjacency matrix data structure for graph          */
static DEFAULTOPTIONS(options);

/* nauty stuff */
statsblk(stats);
setword workspace[50*MAXM];

/* more nauty stuff */
options.writemarkers = FALSE;
options.getcanon=TRUE;

/* fill in the holes in the names of the vertices-need 0,...,n */
for( i = ZERO; i < VERTEXSIZE; translate[i++] = ZERO );
  maxname = ZERO;
for(vt = firstVertex(g2); vt != LIST_END; vt = nextVertex(g2, vt))
  {
     j = vertName(g2, vt);  /*(*g2).vrtx[vt].vname;*/
     translate[j] = j - ONE;
     if ( j > maxname ) 
       {
          maxname = j;
       }
  }

/* fill in missing vertex names */
if ( maxname > (*g2).v )
  for (i = maxname; i > (*g2).v; i--)
    if ( translate[i] ) 
      {
         for ( j = (*g2).v; translate[j]; j-- );
           translate[i] = j - ONE;
         translate[j] = ONE;   /* mark it---won't be used below */
      }



/* initialize matrix for incidence matrix */
for(i = ZERO; i < VERTEXSIZE; i++ )  /* put in size of vertex set max */
for(j = ZERO; j < VERTEXSIZE; j++ )
  adjmat[i][j] = ZERO;

/* put graph data structure into incidence matrix formal */
for(vt = firstVertex(g2); vt != LIST_END; vt = nextVertex(g2, vt))
  {
     for(ed = firstEdge(g2, vt); ed != LIST_END; ed = nextEdge(g2, ed))
       {/* 3 */
          edgename = translate[nameOtherEnd(g2, ed)];
          /* entries greater than 1 for multiple edges */
          ++adjmat[edgename][translate[vertName(g2, vt)]];
       }
  }

/* creation of new vertices for multiple edge format */
nv =numVertices(g2);
next = nv;
n = nv;
for ( i = ZERO; i < nv; i++ )
for ( j = i + ONE; j < nv; j++ ) 
  if( adjmat[i][j] > ONE ) 
    n += adjmat[i][j];

/* make a nauty friendly representation of the graph */
m = (n - ONE) / WORDSIZE + ONE;
bzero(g, m * n * sizeof(set));
bzero(canong, m * n * sizeof(set));
//assert(m*n*sizeof(set)<1000);
for ( i = ZERO; i < nv; i++ )
for ( j= i + ONE; j < nv; j++ ) 
  {
     if( adjmat[i][j] == ONE ) 
       {
          ADDELEMENT(g + m * i, j);
          ADDELEMENT(g + m * j, i);
       }
     else
       if( adjmat[i][j] > ONE ) 
         {
            for( k = ZERO; k < adjmat[i][j]; k++ ) 
              {
                 ADDELEMENT(g + m * i, next);
                 ADDELEMENT(g + m * j, next);
                 ADDELEMENT(g + m * next, i);
                 ADDELEMENT(g + m * next, j);
                 next = next + ONE;
              }
         }
  }

assert(next == n && n < MAXN);
setVNew(g2, n);

/* statistic being collected */
if( n > gvnewMax )
  gvnewMax = n;

options.defaultptn = FALSE;
for ( i= ZERO; i < n; i++ ) 
  {
     lab[i] = i;
     ptn[i] = ONE;
  }
ptn[nv - ONE] = ZERO;
ptn[n - ONE] = ZERO;
/* canong comes back with the canonical labeling */
nauty(
      g,
      lab,
      ptn,
      NILSET,
      orbits, 
      &options, 
      &stats, 
      workspace, 
      50 * MAXM,
      m,
      n,
      (graph *) canong
     );

}/* end findInvariant  */
   
   
/*                                                                             */
/*                                 end of findInvariant                                 */
/*                                                                             */
/*******************************************************************************/
   
int
computeNumwords(int gv)
{
int m,
    b,
    numbits,
    numwords;

   
/*
numbits = ( gv * (gv -1) ) / 2;
m = ( gv + WORDSIZE - 1 ) / WORDSIZE;
b = m * WORDSIZE;
numwords = ( ( numbits + b - 1 ) / b ) * m;
*/


m = ( gv + WORDSIZE - ONE ) / WORDSIZE;
numwords = m * gv;
return(numwords);
}

void
mywrite(graph *g,int m,int n) 
{

  int i,j;

  printf("Graph with %d vertices (and m=%d)\n",n,m);
  for( i = ZERO; i < n; i++ ) 
    {
       printf("%d: ",i);
       for( j = ZERO; j < WORDSIZE * m; j++ )
         if( ISELEMENT(g + m * i, j)) 
           printf("%d ",j);
       printf("\n");
    }

}

