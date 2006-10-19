#include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>




/***************************************************************************/
/*                                                                         */
/*                         start of evaluateThreesDriver                   */
/*                                                                         */

/*
Precondition: C--index into graph array pointing to a graph with
                 three vertices
              arrays tuteMat and tutteMat2 contain the current state of
              the computation

Postcondition: arrays tutteMat and tutteMat2 have been augmented by the tutte poly 
               of a three vertex multigraph g[C]

Return: 1 to indicate the need to replace the graph
        0 to indicate trouble
*/

int 
evaluateThreesDriver(
                     int C, 
                     TUTTE tutteMat2,
                     TUTTEO tutteMat2X
                    )


{
int 
    ne,            /* location of edge                      */
    n1,            /* canonical labelling of multiplicities */
    n2,
    findthree,     /* signal three vertex graph processed   */
    noEdges,       /* coding value for switch               */
    x12,           /* i and j are incident or not           */
    x13,
    x23,
    n12,           /* number of edges between i and j       */
    n13,
    n23,
    vt1a,          /* the three vertices                    */
    vt2a,
    vt3a;
//printf("evaluateThrees\n");

vt1a = firstVertex(&g[C]);  //g[C].vrtx[ZERO].nvert;
vt2a = nextVertex(&g[C], vt1a);  //g[C].vrtx[vt1a].nvert;
vt3a = nextVertex(&g[C], vt2a);  //g[C].vrtx[vt2a].nvert;
n12 = ZERO;
n13 = ZERO;
//ne = firstEdge(&g[C], vt1a);  //g[C].edg[g[C].vrtx[vt1a].fedge].front;
//while( ne != LIST_END  )
for(ne = firstEdge(&g[C], vt1a); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( nameOtherEnd(&g[C], ne) /*g[C].edg[ne].ename*/ == vertName(&g[C], vt2a) /*g[C].vrtx[vt2a].vname*/ )
       ++n12;
     else
       if( nameOtherEnd(&g[C], ne) /*g[C].edg[ne].ename*/ == vertName(&g[C], vt3a) /*g[C].vrtx[vt3a].vname*/ )
         ++n13;
   //  ne = nextEdge(&g[C], ne);  //g[C].edg[ne].front;
  }

//ne = firstEdge(&g[C], vt2a);  //g[C].edg[g[C].vrtx[vt2a].fedge].front;
n23 = ZERO;
//while( ne != LIST_END )

for(ne = firstEdge(&g[C], vt2a); ne != LIST_END; ne = nextEdge(&g[C], ne))
  {
     if( nameOtherEnd(&g[C], ne) /*g[C].edg[ne].ename*/ == vertName(&g[C], vt3a) /*g[C].vrtx[vt3a].vname*/ )
       ++n23;
    // ne =nextEdge(&g[C], ne);  // g[C].edg[ne].front;
  }

/* find adjacencies */
x12 = isadj(vt1a,vt2a,&g[C]);
x13 = isadj(vt1a,vt3a,&g[C]);
x23 = isadj(vt2a,vt3a,&g[C]);

noEdges = x12 + x13 + x23;
findthree = ZERO;


if( noEdges == TWO )
  {
     if ( x12 == ZERO )
       {
          n1 = n13;
          n2 = n23;
       }
     else
       if( x13 == ZERO )
         {
            n1 = n12;
            n2 = n23;
         }
       else
         if( x23 == ZERO )
           {
              n1 = n12;
              n2 = n13;
           }
     findthree = fixedthreetree(
                                n1,
                                n2,
                                tutteMat2,
                                tutteMat2X
                               );
  }
else
  if( noEdges == THREE )
    {
       if( n12 == ONE )
         findthree = fixedtriangle(
                                   n23,
                                   n13,
                                   n12,
                                   tutteMat2,
                                   tutteMat2X
                                  );
       else
         if( n13 == ONE )
           findthree = fixedtriangle(
                                     n23,
                                     n12,
                                     n13,
                                     tutteMat2,
                                     tutteMat2X
                                    );
         else
           if( n23 == ONE )
             findthree = fixedtriangle(
                                       n12,
                                       n13,
                                       n23,
                                       tutteMat2,
                                       tutteMat2X
                                      );
           else
             findthree = fixedtriangle(
                                       n12,
                                       n13,
                                       n23,
                                       tutteMat2,
                                       tutteMat2X
                                      );
    }

return( findthree );



}/* end evaluateThreesDriver*/






