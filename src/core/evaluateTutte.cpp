#include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


/**********************************************/
/*                                            */
/*            start of evaluateTutte          */
/*                                            */
/* 

Precondition: A graph g[C] and the matrices (with values) 
              for the final value of the Tutte polynomial

Postcondition: The Tutte polynomial of g[C] has been added to the final result.
               The index for the graph--C--will be replaced when the procedure returns
               control to its caller.
*/


void evaluateTutte (int C,  TUTTE tutteMat, TUTTEO tutteMatX)
{
int startused, /* location of top of graph stack on entry to evaluateTutte 
                  obviates the need of a separate stack for use
                  within evaluateTutte                                     */
    RET,       /* return value from fulltwo                                */
    D1,        /* temporary graph pointer used with eliminateTriangle      */
    treeOrNot, /* return value to indicate whether a tree has been found   */      
    p1,        /* delete contract variables */ 
    e2, 
    t1,
    t2,
    goOnce;    /* signal for occurrence of small graph having
                   its polynomial added to final polynomial                */

//printf("evaluateTutte\n");
startused = topused(&used);
goOnce = ONE;
deleteAndContractMultEdge(
               C,
               tutteMat,
               tutteMatX
              );
findDegOne(&g[C]);

treeOrNot = detectAndComputeTrees(
                   &g[C],
                   tutteMat,
                   tutteMatX
                  );
if( treeOrNot )
  { 
C = pushAndPopGraphIndex(C, startused);
   /*
       pushavail(C, 
               &avail
              );
     if( startused != topused(&used) )
       {
          C = popused(&used);
       }
     else
       {
          C = MINUSTHREE;
       }
*/
  }


retree(&g[C]);
//printf("L\n");
while( ! ( C < ZERO ) )
  {   /* 1 */
     findDegOne(&g[C]);
     goOnce = ONE;
     treeOrNot = detectAndComputeTrees(
                        &g[C],  
                        tutteMat,
                        tutteMatX
                       );
     if( treeOrNot )
       {  /* 2 */
          C = pushAndPopGraphIndex(C, startused);
        /*
          pushavail(
                    C, 
                    &avail
                   );
          if( startused != topused(&used) )
            { 
               C = popused(&used);
            } 
          else
            { 
               C = MINUSTHREE;
            }
        */
          goOnce = ZERO; 
       } /* 2 */
     if( C != MINUSTHREE )
       {/* 5 */
          deleteAndContractMultEdge(C,tutteMat,tutteMatX);
       } /* 5 */

     if( ( C != MINUSTHREE ) && ( goOnce == ONE ) )
       { /* 6 */
          if( C != MINUSTHREE )
            { /* 7 */ //printf("O\n");
               RET = ONE;
               while( ( RET == ONE ) ) 
                 { /* 8 */
                    D1 = popavail(&avail);
                    RET = eliminateTriangle(
                                            &g[C],
                                            &g[D1]
                                           );
                    if( RET == ONE )
                      {  /* 9 */
                         findDegOne(&g[D1]); 
                         putonstack(
                                    &used,
                                    D1
                                   );
                      } /* 9 */
                    else
                      {  /* 10 */
                         pushavail(
                                   D1,
                                   &avail
                                  );
                      } /* 10 */
                  } /* 8 */
              } /* 7 */
            findDegOne(&g[C]);

            treeOrNot = detectAndComputeTrees(
                               &g[C],
                               tutteMat,
                               tutteMatX
                              );
            if( treeOrNot )
              {  /* 11 */
                C =  pushAndPopGraphIndex(C, startused);
             /*
                 pushavail(
                           C, 
                           &avail
                          );
                 if( startused != topused(&used) )
                   { 
                      C = popused(&used);
                   } 
                 else
                   { 
                      C = MINUSTHREE;
                   } 
               */
              } /* 11 */
            else
              if( numVertices(&g[C])  <= SEVEN )
                {/* 14 */
                   if( ( numVertices(&g[C])  == SEVEN ) 
                      &&  ( numEdges(&g[C])  > TWENTY ) 
                         && ( numEdges(&g[C])  < 38 ) )
                     { /* 15 */ 
                        preSevenFindDeg2(
                                         &g[C],
                                         tutteMat,
                                         tutteMatX
                                        );
                     }  /* 15 */
                   if( numVertices(&g[C]) == SEVEN )
                     { /* 16 */
                        sevensDriver(
                                     &g[C],
                                     tutteMat,
                                     tutteMatX
                                    );
                     } /* 16 */
                   else
                     { /* 17 */
                        sixOrFewer(
                                   &g[C],
                                   tutteMat,
                                   tutteMatX
                                  );
                     } /* 17 */
                  C = pushAndPopGraphIndex(C, startused);
                  /*
                   pushavail(
                             C, 
                             &avail
                            );
                   if( startused != topused(&used) )
                     { 
                        C = popused(&used);
                     }
                   else
                     { 
                        C = MINUSTHREE;
                     } 
                  */
                } /* 14 */
              else
                { /* 20 *//* check to see if delete and contract can be done normally */
                  /* Operating on simple graphs--use same code as for chromatic polynomial */
                doDeleteContract(C,tutteMat,tutteMatX); 
            /*
                   p1 = nontree(&g[C]);
                   e2 = nameOtherEnd(&g[C], p1);  
                   t2 = vertListOtherEnd(&g[C], p1);  
                   t1 = vertListOtherEnd(&g[C], otherEndEntry(&g[C], p1) );  
                   deleteEdge(
                           p1,
                           &g[C]
                          );       // return value not needed here 
                   D1 = popavail(&avail);
                   copyGraph(
                             &g[C],
                             &g[D1]
                            );
                   contract(
                            t1,
                            t2,
                            &g[D1]
                           );
                   retree(&g[D1]);
                 
                   detectAndDeleteLoop(&g[D1]);
                   findDegOne(&g[D1]); 
                   treeOrNot = detectAndComputeTrees(
                                      &g[D1], 
                                      tutteMat,
                                      tutteMatX
                                     );
                   if( treeOrNot )
                     { 
                        pushavail(D1, 
                                  &avail
                                 );
                     }
                   else
                     { 
                        retree(&g[D1]);
                        putonstack(
                                   &used,
                                   D1
                                  );
                     }
                   treeOrNot = detectAndComputeTrees(
                                      &g[C],
                                      tutteMat,
                                      tutteMatX
                                     );
                   if(treeOrNot)
                     { 
                        C = pushAndPopGraphIndex(C, startused);
          
                      } // 23  the d/c code -- else for v < 7 
*/
                }/* 20 */ /* end of d/c after the small eliminate code */
       } /* 6 *//* end goOnce loop */
  }  /* 1 while ! ( C < 0 ) */

} /* end evaluateTutte */

