#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3drf1           */
/*                                            */
 

 
/* 

Precondition: g is a simple seven vertex graph with 14 edges 
              degseq is 700 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3drf1(
               struct graph *g,
               int degseq,
               TUTTE tutteMat,
               TUTTEO tutteMatX
              )


{
int d41,            /* location on vertex list of vertex of degree 5    */
    d42,
    vt;             /* location on vertex list                           */



    

printf("sevenpart3drf1 degseq =             %d\n",degseq); 

switch(degseq)
{  /* 1 */


case 700:
{ 
/*printf("700\n");*/ 
 vt = firstVertex(g);  
 deletevrtx(g,vt);
 vt = firstVertex(g);  
 d41 = nextofdegree(g,&vt,FOUR);
 d42 = nextofdegree(g,&vt,FOUR);
 deletevrtx(g,d41);
 deletevrtx(g,d42);
 if( nodegn(g,ONE) == TWO )
  { /* g1170 *//*printf("spt348\n");*/
/*
W0962
*/
/*
w0962

******************* reading edge list *************




(  2,  3) (  1,  7) (  2,  7) (  1,  4) (  2,  6) (  4,  7) (  1,  5) 
(  3,  7) (  1,  6) (  2,  5) (  5,  6) (  4,  5) (  3,  4) (  3,  6) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              22      57      57      29       8       1 
I =   1      22     105     119      49       7 
I =   2      70     147      70       7 
I =   3      98      98      14 
I =   4      84      35 
I =   5      49       7 
I =   6      21 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      22; 
tutteMat[  0][  2] =      57; 
tutteMat[  0][  3] =      57; 
tutteMat[  0][  4] =      29; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      22; 
tutteMat[  1][  1] =     105; 
tutteMat[  1][  2] =     119; 
tutteMat[  1][  3] =      49; 
tutteMat[  1][  4] =       7; 
tutteMat[  2][  0] =      70; 
tutteMat[  2][  1] =     147; 
tutteMat[  2][  2] =      70; 
tutteMat[  2][  3] =       7; 
tutteMat[  3][  0] =      98; 
tutteMat[  3][  1] =      98; 
tutteMat[  3][  2] =      14; 
tutteMat[  4][  0] =      84; 
tutteMat[  4][  1] =      35; 
tutteMat[  5][  0] =      49; 
tutteMat[  5][  1] =       7; 
tutteMat[  6][  0] =      21; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

   
  } 
 else
  { /* g1171 */ /*printf("spt349\n");*/
/*
W0963
*/
/*
w0963

******************* reading edge list *************




(  3,  5) (  3,  4) (  1,  6) (  2,  6) (  2,  5) (  1,  4) (  2,  7) 
(  1,  7) (  3,  7) (  2,  4) (  5,  6) (  3,  6) (  4,  7) (  1,  5) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              24      61      60      30       8       1 
I =   1      24     110     120      48       6 
I =   2      73     147      69       6 
I =   3      99      97      14 
I =   4      84      35 
I =   5      49       7 
I =   6      21 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      24; 
tutteMat[  0][  2] =      61; 
tutteMat[  0][  3] =      60; 
tutteMat[  0][  4] =      30; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      24; 
tutteMat[  1][  1] =     110; 
tutteMat[  1][  2] =     120; 
tutteMat[  1][  3] =      48; 
tutteMat[  1][  4] =       6; 
tutteMat[  2][  0] =      73; 
tutteMat[  2][  1] =     147; 
tutteMat[  2][  2] =      69; 
tutteMat[  2][  3] =       6; 
tutteMat[  3][  0] =      99; 
tutteMat[  3][  1] =      97; 
tutteMat[  3][  2] =      14; 
tutteMat[  4][  0] =      84; 
tutteMat[  4][  1] =      35; 
tutteMat[  5][  0] =      49; 
tutteMat[  5][  1] =       7; 
tutteMat[  6][  0] =      21; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

   
  }
}
break;





default:
  {
     printf("sevenpart3drf1\n");
     break;
  }

} /*  end switch on degseq */


}  /* end sevenpart3drf1 */

/*                                            */
/*           end of sevenpart3drf1            */
/*                                            */
/**********************************************/




