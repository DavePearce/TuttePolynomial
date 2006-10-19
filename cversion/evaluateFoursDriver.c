#include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>




/***************************************************************************/
/*                                                                         */
/*                         start of evaluateFours                          */
/*                                                                         */

/*
Precondition: C--index to entry in graph array that contains a graph with 
                 four vertices
              arrays tutteMat2 and tutteMat2X hold the current state of the 
              computation for this graph

Postcondition: the arrays tutteMat2 and tutteMat2X have been augmented 
               by the tutte poly of the four vertex graph g[C]

Return: 1 to signify the graph needs replacement

*/

int 
evaluateFours(
              int C,    
              TUTTE tutteMat2,
              TUTTEO tutteMat2X
             )
{

int ne,           /* location of edge                           */
    x12,          /* incidence in simple graph                  */
    x13,
    x14,
    x23,
    x24,
    x34,
    n12,          /* number of edges between * and *            */
    n13,
    n14,
    n23,
    n24,
    n34,
    findfour,     /* signal four vertex processed               */
    noEdges,      /* number edges in simple underlying graph    */
    vt1a,         /* location of vertex                         */
    vt2a,
    vt3a,
    vt4a;


//printf("evaluateFoursDriver\n");
/*                                    */
/* identify the vertices of the graph */
/*                                    */
vt1a = firstVertex(&g[C]);  
vt2a = nextVertex(&g[C], vt1a);  
vt3a = nextVertex(&g[C], vt2a); 
vt4a = nextVertex(&g[C], vt3a);  

/*                                    */
/* compute the multiplicities of each */
/* edge                               */
/*                                    */
n12 = ZERO;
n13 = ZERO;
n14 = ZERO;
for(ne = firstEdge(&g[C], vt1a); ne != LIST_END; ne = nextEdge(&g[C], ne)) 
  {
     if( nameOtherEnd(&g[C], ne)  == vertName(&g[C], vt2a)  )
       ++n12;
     else
       if( nameOtherEnd(&g[C], ne)  == vertName(&g[C], vt3a)  )
         ++n13;
       else
         if( nameOtherEnd(&g[C], ne)  == vertName(&g[C], vt4a)  )
           ++n14;
  }

n23 = ZERO;
n24 = ZERO;
for(ne = firstEdge(&g[C], vt2a); ne != LIST_END; ne = nextEdge(&g[C], ne)) 
  {
     if( nameOtherEnd(&g[C], ne)  == vertName(&g[C], vt3a)  )
       ++n23;
     else
       if( nameOtherEnd(&g[C], ne)  ==vertName(&g[C], vt4a)  )
         ++n24;
  }

n34 = ZERO;
for(ne = firstEdge(&g[C], vt3a); ne != LIST_END; ne = nextEdge(&g[C], ne)) 
  {
     if( nameOtherEnd(&g[C], ne)  == vertName(&g[C], vt4a)  )
       ++n34;
  }

/*                                   */
/* determine the adjacencies in the  */
/* underlying simple graph           */
/*                                   */
x12 = isadj(vt1a,vt2a,&g[C]);
x13 = isadj(vt1a,vt3a,&g[C]);
x14 = isadj(vt1a,vt4a,&g[C]);
x23 = isadj(vt2a,vt3a,&g[C]);
x24 = isadj(vt2a,vt4a,&g[C]);
x34 = isadj(vt3a,vt4a,&g[C]);

/*                                         */
/* number of edges in the underlying graph */
/*                                         */
noEdges = x12 + x13 + x14 + x23 + x24 + x34;

findfour = ZERO;
switch( noEdges )
 {
  case THREE:
    {
       findfour = fourtree(x12,x13,x14,x23,x24,x34,
                           n12,n13,n14,n23,n24,n34,
                           tutteMat2,
                           tutteMat2X);
       break;
    }

  case FOUR:
    {
       findfour = fouredges(x12,x13,x14,x23,x24,x34,
                            n12,n13,n14,n23,n24,n34,
                            tutteMat2,
                            tutteMat2X);
       break;
    }
 
  case FIVE:
    {
       findfour = randomgraph(x12,x13,x14,x23,x24,x34,
                              n12,n13,n14,n23,n24,n34,
                              tutteMat2,
                              tutteMat2X);
       break;
    }
    
  case SIX:
    {
       findfour = fourcomplete(n12,n13,n14,n23,n24,n34,
                               tutteMat2,
                               tutteMat2X);
       break;
    }
  default:
    {
       printf("evaluateFoursDriver\n");
       break;
    }

 } /* end switch on noEdges */


return( findfour );


}/* end evaluateFoursDriver */








