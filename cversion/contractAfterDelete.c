#include <assert.h>
#include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


/**********************************************/
/*                                            */
/*        start of contractAfterDelete        */
/*                                            */
/*                                            */

/*
Precondition: t1 and t2 are the ends of the edge being contracted
              D1 is the index of the graph for which the contract
               operation is being performed
              sendback indicates what the degrees of t1 and t2
               are after the deletion of the edge
              tutteMat and tutteMatX are arrays containing the current
                state of the computation 

Postcondition: g[D1] has vertices t1 and t2 identified
               the graph g[D1] may  be put on the graph stack
                 or its tutte poly is contributed to the arrays
                tuteMat and tutteMatX
*/
int
contractAfterDelete (
                     int t1,
                     int t2,
                     int D1,
                     int sendback, 
                     TUTTE tutteMat,
                     TUTTEO tutteMatX
                    )
{
int smallreturn,
    treeornot;

/*                                           */
/* the degrees of t1 and t2 are both greater */
/* than one after the edge deletion          */
/*                                           */
if( sendback == ZERO )
  {/* sendback==0 */
     contract(
              t1,
              t2,
              &g[D1]
             );
                
     treeornot = detectAndComputeTrees(
                                       &g[D1], 
                                       tutteMat,
                                       tutteMatX
                                      );
     if( treeornot )
       { 
          pushavail(
                    D1, 
                    &avail
                   );
       }
     else
       {
          if( numVertices(&g[D1]) <= FIVE )
            {
               smallreturn = evaluateSmallGraphs(
                                                 D1,
                                                 tutteMat,
                                                 tutteMatX
                                                );
               if( smallreturn )
                 {
                    pushavail(
                              D1,
                              &avail
                             ); 
                 }
               else
                 { 
                    findDegOne(
                               &g[D1]
                              );
                    putonstack(
                               &used,
                               D1
                              ); 
                 }
           }
         else
           {
              findDegOne(
                         &g[D1]
                        );           
              putonstack(
                         &used, 
                         D1
                        );
          } 
      }                
  }/* end sendback==0 */
else           
/*                                           */
/* both t1 and t2 had degree one before the  */
/* edge deletion          */
/*                                           */
  if( sendback == ONE )
    {
       treeornot = detectAndComputeTrees(
                                         &g[D1], 
                                         tutteMat,
                                         tutteMatX
                                        );
       pushavail(
                 D1, 
                 &avail
                );
    }
  else
/*                                           */
/* one of t1 and t2 but not both had degree  */
/* one before the edge deletion              */
/*                                           */
    if( sendback == TWO )
      {
         treeornot = detectAndComputeTrees(
                                           &g[D1], 
                                           tutteMat,
                                           tutteMatX
                                          );
         if( treeornot )
           { 
              pushavail(
                        D1, 
                        &avail
                       );
           }
         else
           {
              findDegOne(
                         &g[D1]
                        );
              retree(
                     &g[D1]
                    );                   
              putonstack(
                         &used, 
                         D1
                        );
           }
     }

} /* end contractAfterDelete  */


/*                                            */
/*        end of contractAfterDelete          */
/*                                            */
/**********************************************/




