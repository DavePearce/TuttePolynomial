#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3drf           */
/*                                            */
 

 
/* 

Precondition: g is a simple seven vertex graph with 14 or 15 edges 
              degseq is one of 700, 20140, and 2320 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3drf(struct Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX)

{

//printf("sevenpart3drf\n"); 

switch(degseq)
  {  /* 1 */

     case 700:
       {
          sevenpart3drf1(g,degseq,tutteMat,tutteMatX);
       }
     break;

     case 20140:
       {
          sevenpart3drf2(g,degseq,tutteMat,tutteMatX); 
       } 
     break;

     case 2320:
       { 
          sevenpart3drf3(g,degseq,tutteMat,tutteMatX);
       } 
     break;

     default:
       {
          printf("sevenpart3drf\n");
       }
     break;

  } /*  end switch on degseq */


}  /* end sevenpart3drf */

/*                                            */
/*           end of sevenpart3drf             */
/*                                            */
/**********************************************/




