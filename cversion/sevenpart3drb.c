#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3drb           */
/*                                            */


/* 

Precondition: g is a simple seven vertex graph with 15 edges
              degseq is one of 20320, 12220, or 4120 for valid input
              tutteMat and tutteMatX are arrays with
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte
               poly of this graph

*/

void
sevenpart3drb(
              struct graph *g,
              int degseq,
              TUTTE tutteMat,
              TUTTEO tutteMatX
             )


{

//printf("sevenpart3drb\n");


switch(degseq)
  {  /* 1 */

     case 20320:
       {
          sevenpart3drb1(g,degseq,tutteMat,tutteMatX);
       } 
     break;
     
     case 12220:
       {
          sevenpart3drb2(g,degseq,tutteMat,tutteMatX);
       } 
     break;

     case 4120:
       {
          sevenpart3drb3(g,degseq,tutteMat,tutteMatX);
       } 
     break;

     default:
       {
          printf("sevenpart3drb\n");
       }
     break;


  } /*  end switch on degseq */

}  /* end sevenpart3drb */

/*                                            */
/*           end of sevenpart3drb             */
/*                                            */
/**********************************************/




