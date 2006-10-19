#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3drd           */
/*                                            */
 
 
/* 

Precondition: g is a simple seven vertex graph with 14 or 15 edges 
              degseq is one of 3310, 1510, and 3130 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 


void
sevenpart3drd(struct Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX)

{

//printf("sevenpart3drd\n");
    
switch(degseq)
  {  /* 1 */
     case 3310:
       { 
          sevenpart3drd1(g,degseq,tutteMat,tutteMatX);
       } 
     break;

     case 1510:
       {  /* start 1510 */
          sevenpart3drd2(g,degseq,tutteMat,tutteMatX);
       }
     break;

     case 3130:
       { 
          sevenpart3drd3(g,degseq,tutteMat,tutteMatX);
       } 
     break;

     default:
       {
          printf("sevenpart3drd\n");
       }
     break;

  } /*  end switch on degseq */



}  /* end sevenpart3drd */

/*                                            */
/*           end of sevenpart3drd             */
/*                                            */
/**********************************************/




