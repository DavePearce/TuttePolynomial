#include <assert.h>
#include "tutte.h"
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


/***********************************************/
/*                                             */
/*        start popGraphIndex                  */
/*                                             */
/*                                             */
// parameter C is not needed?? eliminate??
int
popGraphIndex(int C, int startused)
{
if( startused != topused(&used) )
  C = popused(&used);
else
  C = MINUSTHREE;

return(C);

} /* end getting new graph index */


/*                                             */
/*                                             */
/*        end popGraphIndex                    */
/*                                             */
/***********************************************/
/*                                             */
/*        start pushAndPopGraphIndex           */
/*                                             */
/*                                             */

int pushAndPopGraphIndex(int C, int startused) {
  pushavail(C, &avail);
  if( startused != topused(&used) )
    C = popused(&used);
  else
    C = MINUSTHREE;
  
  return C;  
} /* end push and pop new graph index */

/*                                             */
/*                                             */
/*        end pushAndPopGraphIndex             */
/*                                             */
/***********************************************/
/*                                             */
/*        start findAndEliminateTriangle       */
/*                                             */
/*                                             */
int
findAndEliminateTriangle( int C)
{
int RET,D;
D = popavail(&avail);
RET = eliminateTriangle(
                        &g[C],
                        &g[D]
                       );
if( RET == ONE )
  {
     putonstack(
                &used,
                D
               );
  }
else
  {
     pushavail(
               D,
               &avail
              );
  }

}  /* end findAndEliminateTriangle */

/*                                             */
/*                                             */
/*          end findAndEliminateTriangle       */
/*                                             */
/***********************************************/
/*                                             */
/*      start doDeleteContract                 */
/*                                             */
/*                                             */
void
doDeleteContract(int C ,TUTTE tutteMat,TUTTEO tutteMatX )
{
int  
    p1,
    e2,
    t2,
    t1,
    D,
    sendback;

          /*                                                     */
          /* do the delete and contract operations               */ 
          /*                                                     */    
          retree(&g[C]);
          detectAndDeleteLoop(&g[C]);
          /* first get a nontree edge */
          /* initialize p1 so assert will work */
          p1 = MINUSONE;
          if( numEdges(&g[C]) != ZERO ) 
            p1 = nontree(&g[C]);
          assert( p1 >= ZERO );

//          e2 = nameOtherEnd(&g[C], p1);  
          t2 = vertListOtherEnd(&g[C], p1);  
          t1 = vertListOtherEnd(&g[C], otherEndEntry(&g[C], p1) ); 
          /* delete                   */
          sendback = deleteEdge(
                             p1,
                             &g[C]
                            );
          /* copy and contract */
          D = popavail(&avail);
          copyGraph(
                    &g[C],
                    &g[D]
                   );
          /* contract t1 and t2 and check to see if the graph
             is a small graph or if it should go on the stack  */
          contractAfterDelete(
                              t1,
                              t2,
                              D,
                              sendback,
                              tutteMat,
                              tutteMatX
                             );

} /* end do delete contract on a real edge */

/*                                            */
/*         end of doDeleteContract            */
/*                                            */
/**********************************************/
/*                                            */
/*         start savedValues                  */
/*                                            */
/*                                            */



void 
savedValues(
            int C,
            int *gv,
            int *gvnew,
            int *ge,
            int *yPower,
            int *gminusone,
            int *gminustwo,
            short int savedmult[],
            TUTTE tutteMat1,
            TUTTEO tutteMat1X
           )
{
int t,
    i,
    j;
         
               /*                                                 */
               /* SAVE FACTORS FOR LATER USE                      */
               /* WANT TO PASS ON A GRAPH WITH NO HISTORY         */ 
               /*                                                 */
               for( i = ZERO; i < TUTTEROWS; ++i )
               for( j = ZERO; j < TUTTECOLS; ++j )
                 {
                    tutteMat1[i][j] = ZERO;
                    tutteMat1X[i][j] = ZERO;
                 }
               t = getMultCount(&g[C], ZERO);
               assert(t<100);
               copyAndZeroMultCount(&g[C], savedmult);
               *gminustwo = triangleDels(&g[C]); 
               setMinustwo(&g[C], ZERO); 
               *gminusone = degOneDels(&g[C]);  
               setMinusone(&g[C], ZERO);  
               *yPower = getYPower(&g[C]);  
               setYPower(&g[C], ZERO);  
               *gvnew = multEdgeGphVert(&g[C]); 
               setVNew(&g[C], numVertices(&g[C])); 
               *gv = numVertices(&g[C]);  
               *ge = numEdges(&g[C]); 
          
} /* end saved values */

/*                                            */
/*                end savedValues             */
/*                                            */
/**********************************************/

int
graphIsoTestHash(int *C,int startused,int thresholdValueOnEntry,int canong[],
   unsigned long int *hash,TUTTE  tutteMat,TUTTEO tutteMatX, int threshtable[],
   int  newthreshold[])
{
int  m1, 
     newthreshnum, 
     bottomRow, 
     gv,
     maxseq1,
     maxseq,         
     gvnew,
     ge,
     i,
     j,   
     yPower,
     gminusone,
     gminustwo;
short int savedmult[100];
TUTTE tutteMat1;
TUTTEO tutteMat1X;

          findDegOne(&g[*C]);    
         /*                                                  */ 
         /* get canonical labeling for graph so you can      */
         /* check for isomorphism to a graph in hash table   */
         /*                                                  */ 
          findInvariant (
                         &g[*C], 
                         &m1,  // passed as address 
                         canong 
                        );

          /*                                     */
          /* check to see if graph in hash table */
          /*                                     */     
                  // hash passed as address
          if(isolookup(&g[*C],canong,hash,tutteMat1,tutteMat1X))

            {/* j */
               /* ROUTINE TO INCORPORATE x^n,y^m,  y + y^2 + y^3 +   */
               multiplyByFactors(
                                 &g[*C],
                                 tutteMat,
                                 tutteMatX,
                                 tutteMat1,
                                 tutteMat1X, 
                                 degOneDels(&g[*C]), 
                                 triangleDels(&g[*C])  
                                );
               pushavail ( 
                          *C, 
                          &avail 
                         );
            }/* j */


          else /* g is not in the hashtable */
            {/* k */
        findDegOne(&g[*C]); 
               /*                                                 */
               /* SAVE FACTORS FOR LATER USE                      */
               /* WANT TO PASS ON A GRAPH WITH NO HISTORY         */ 
               /*                                                 */
               savedValues(
                           *C,
                           &gv,
                           &gvnew,
                           &ge,
                           &yPower,
                           &gminusone,
                           &gminustwo,
                           savedmult,
                           tutteMat1, 
                           tutteMat1X
                          ); 
               /*                                                  */ 
               /* compute threshold value for stripped graph       */
               /* and decide what to do--may skip some thresholds  */
               /* thresholds set in an all or nothing fashion      */
               /* the values are not important-what is important   */
               /* is whether the threshold has been passed that    */
               /* indicates that the graph left should have its    */
               /* tutte poly computed-no more del/cont             */ 
               newthreshnum = newthreshold[gv];
               if (  newthreshnum < ZERO )
                 {/* l */
                    
                       /*                                            */
                       /* means threshold less than computation      */
                       /* triggering point defined at start          */
                       /*                                            */
                       evaluateTutte(
                                     *C,  
                                     tutteMat1,
                                     tutteMat1X
                                    );


if(g[*C].minusone>3)LLLLL++;else LLLLLL++;         
                 }/* l */
               else
                 {/* m */
                    /*                                           */
	            /* not in hashtable and not smaller than th  */
                    /* off to deleteContract recursively with    */
                    /* the newly set threshold to get below with */
                    /* more reductions and del/cont ops          */
                    deleteContract(
                                   *C, 
			           newthreshnum , 
                                   threshtable, 
                                   newthreshold, 
	                           tutteMat1,
                                   tutteMat1X
                                  );
                 }/* m */
               /*                                                */
               /* dropped out of evaluateTutte or returned from  */
               /* deleteContract  -- push done in evaluateTutte? */
               /* add to hash table and contribute to answer     */
               /*                                                */
               

                      bottomRow=0;
                      for(i = TUTTEROWS - 1; i >= ZERO; i-- )
                        {
                           for( j = TUTTECOLS - 1; j >= ZERO; j-- ) 
                             {
                                if(tutteMat1[i][j]!=0)
                                  {
                                     bottomRow=i;
                                     break;
                                  }
                             }
                           if(bottomRow!=ZERO)break;
                        }
                      maxseq1 = ZERO;
                      for( i = ZERO; i <= bottomRow; i++ )
                        { 
                           maxseq=0;
                           for( j = ZERO; j < TUTTECOLS; j++ ) 
                             {
                                if(tutteMat1[i][j]==0)
                                  maxseq=j;
                                else
                                  break;
                             }
                           if( maxseq > maxseq1 )
                             maxseq1 = maxseq;
                        }

               if(maxseq1<3 && (gv>=lowerIsoAddTestLimit && gvnew<=upperIsoAddTestLimit) )
                 {

                isoadd(
                       gv, 
                       gvnew,
                       canong, 
                       *hash, 
                       tutteMat1,
                       tutteMat1X 
                      );
                  }

               /* contribute tutte poly of stripped graph with         */
               /*   original graph parameters restored to final answer */
               setYPower(&g[*C], yPower); 
               setMultCount(&g[*C], savedmult);
               multiplyByFactors(
                                 &g[*C], 
                                 tutteMat,
                                 tutteMatX,
                                 tutteMat1,
                                 tutteMat1X, 
                                 gminusone, 
                                 gminustwo
                                );
          } /* k */
 
          /*                                                            */
          /* get a new graph and see if you are back at the             */
          /* stack location that was on the top of the stack on entry   */
          /*                                                            */
         *C = popGraphIndex(*C, startused);//*C parameter not needed

} /* end  graphInHash */



