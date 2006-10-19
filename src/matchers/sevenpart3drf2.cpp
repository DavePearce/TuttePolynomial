#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3drf2          */
/*                                            */
 

 
/* 

Precondition: g is a simple seven vertex graph with 14 edges 
              degseq is 20140 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3drf2(struct Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX)

{
    

printf("sevenpart3drf2 \n",degseq); 

switch(degseq)
{  /* 1 */


case 20140:
 {
/*
w0912

******************* reading edge list *************




(  2,  5) (  5,  6) (  2,  7) (  1,  5) (  3,  7) (  4,  7) (  3,  4) 
(  4,  6) (  2,  6) (  1,  6) (  5,  7) (  3,  6) (  6,  7) (  1,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               8      28      38      25       8       1 
I =   1       8      48      79      50      11 
I =   2      28      84      70      18 
I =   3      43      75      35       3 
I =   4      42      47      11 
I =   5      31      20       1 
I =   6      17       4 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =       8; 
tutteMat[  0][  2] =      28; 
tutteMat[  0][  3] =      38; 
tutteMat[  0][  4] =      25; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =       8; 
tutteMat[  1][  1] =      48; 
tutteMat[  1][  2] =      79; 
tutteMat[  1][  3] =      50; 
tutteMat[  1][  4] =      11; 
tutteMat[  2][  0] =      28; 
tutteMat[  2][  1] =      84; 
tutteMat[  2][  2] =      70; 
tutteMat[  2][  3] =      18; 
tutteMat[  3][  0] =      43; 
tutteMat[  3][  1] =      75; 
tutteMat[  3][  2] =      35; 
tutteMat[  3][  3] =       3; 
tutteMat[  4][  0] =      42; 
tutteMat[  4][  1] =      47; 
tutteMat[  4][  2] =      11; 
tutteMat[  5][  0] =      31; 
tutteMat[  5][  1] =      20; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      17; 
tutteMat[  6][  1] =       4; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

 
 } 
break;


default:
  {
     printf("sevenpart3drf2\n");
     break;
  }

} /*  end switch on degseq */


}  /* end sevenpart3drf2 */

/*                                            */
/*           end of sevenpart3drf2            */
/*                                            */
/**********************************************/




