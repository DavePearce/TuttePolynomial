#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3dre           */
/*                                            */
 
 
/* 

Precondition: g is a simple seven vertex graph with 14 or 15 edges 
              degseq is one of 11230, 12040, and 10420 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 


void
sevenpart3dre(struct Graph *g,int degseq,TUTTE tutteMat,TUTTEO tutteMatX)

{

//printf("sevenpart3dre\n");    


switch(degseq)
  {  /* 1 */

     case 11230:
       { 
          sevenpart3dre1(g,degseq,tutteMat,tutteMatX); 
       } 
     break;

     case 12040:
       { 
          sevenpart3dre2(g,degseq,tutteMat,tutteMatX);
       } 
     break;

     case 10420:
       { 
          sevenpart3dre3(g,degseq,tutteMat,tutteMatX);
       }
     break;

     default:
       {
          printf("sevenpart3dre\n");
       }
     break;

  } /*  end switch on degseq */

}  /* end sevenpart3dre */

/*                                            */
/*           end of sevenpart3dre             */
/*                                            */
/**********************************************/




