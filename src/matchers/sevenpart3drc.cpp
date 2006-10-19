#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3drc           */
/*                                            */
 
 
/* 

Precondition: g is a simple seven vertex graph with 14 or 15 edges 
              degseq is one of 11410, 2500, and 10600 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3drc(struct Graph *g,int degseq, TUTTE tutteMat, TUTTEO tutteMatX)

{

//printf("sevenpart3drc\n");

switch( degseq )
  {  /* 1 */

     case 11410:
       {
          sevenpart3drc1(g,degseq,tutteMat,tutteMatX);
       } 
     break;

     case 2500:
       {
          sevenpart3drc2(g,degseq,tutteMat,tutteMatX);
       }
     break; 

     case 10600:
       {
          sevenpart3drc3(g,degseq,tutteMat,tutteMatX);
       }
     break;

     default:
       {
          printf("sevenpart3drc\n");
       }
     break;


  } /*  end switch on degseq */

}  /* end sevenpart3drc */

/*                                            */
/*           end of sevenpart3drc             */
/*                                            */
/**********************************************/




