#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3dre2          */
/*                                            */
 
 
/* 

Precondition: g is a simple seven vertex graph with 14 or 15 edges 
              degseq is 12040 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3dre2(struct Graph *g,int degseq,TUTTE tutteMat,TUTTEO tutteMatX)

{
int d51,            /* location on vertex list of vertex of degree 5     */
    d52,
    vt;             /* location on vertex list                           */



//printf("sevenpart3dre2\n");    

switch(degseq)
{  /* 1 */



case 12040:/* are the vertices of degree 5 adjacent? */
 { 
/*printf("12040\n");*/  
  vt = firstVertex(g); 
  d51 = nextofdegree(
                     g,
                     &vt,
                     FIVE
                    );
  d52 = nextofdegree(
                     g,
                     &vt,
                     FIVE
                    );
  if( isadj(d51,d52,g) )
   { /* g1139 */ /*printf("spt342\n");*/
/*
W0917
*/
/*
w0917

******************* reading edge list *************




(  3,  4) (  1,  5) (  1,  7) (  2,  7) (  3,  7) (  6,  7) (  3,  6) 
(  1,  6) (  4,  7) (  2,  5) (  2,  6) (  4,  5) (  5,  7) (  5,  6) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              12      36      43      26       8       1 
I =   1      12      60      84      48      10 
I =   2      36      91      70      17 
I =   3      50      78      32       2 
I =   4      46      46       9 
I =   5      32      19       1 
I =   6      17       4 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      12; 
tutteMat[  0][  2] =      36; 
tutteMat[  0][  3] =      43; 
tutteMat[  0][  4] =      26; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      12; 
tutteMat[  1][  1] =      60; 
tutteMat[  1][  2] =      84; 
tutteMat[  1][  3] =      48; 
tutteMat[  1][  4] =      10; 
tutteMat[  2][  0] =      36; 
tutteMat[  2][  1] =      91; 
tutteMat[  2][  2] =      70; 
tutteMat[  2][  3] =      17; 
tutteMat[  3][  0] =      50; 
tutteMat[  3][  1] =      78; 
tutteMat[  3][  2] =      32; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =      46; 
tutteMat[  4][  1] =      46; 
tutteMat[  4][  2] =       9; 
tutteMat[  5][  0] =      32; 
tutteMat[  5][  1] =      19; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      17; 
tutteMat[  6][  1] =       4; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

   
   } 
  else
   { /* g1140 *//* printf("spt343\n");*/
/*
W0913
*/
/*
w0913

******************* reading edge list *************




(  1,  5) (  3,  6) (  1,  6) (  1,  7) (  2,  7) (  2,  6) (  3,  7) 
(  2,  5) (  4,  7) (  4,  6) (  5,  7) (  3,  5) (  6,  7) (  4,  5) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              15      44      50      28       8       1 
I =   1      15      69      90      46       8 
I =   2      40      95      72      16 
I =   3      51      83      32 
I =   4      46      50       6 
I =   5      32      20 
I =   6      17       4 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      15; 
tutteMat[  0][  2] =      44; 
tutteMat[  0][  3] =      50; 
tutteMat[  0][  4] =      28; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      15; 
tutteMat[  1][  1] =      69; 
tutteMat[  1][  2] =      90; 
tutteMat[  1][  3] =      46; 
tutteMat[  1][  4] =       8; 
tutteMat[  2][  0] =      40; 
tutteMat[  2][  1] =      95; 
tutteMat[  2][  2] =      72; 
tutteMat[  2][  3] =      16; 
tutteMat[  3][  0] =      51; 
tutteMat[  3][  1] =      83; 
tutteMat[  3][  2] =      32; 
tutteMat[  4][  0] =      46; 
tutteMat[  4][  1] =      50; 
tutteMat[  4][  2] =       6; 
tutteMat[  5][  0] =      32; 
tutteMat[  5][  1] =      20; 
tutteMat[  6][  0] =      17; 
tutteMat[  6][  1] =       4; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

    
   } 
 } 
break;


default:
  {
     printf("sevenpart3dre2\n");
     break;
  }

} /*  end switch on degseq */

}  /* end sevenpart3dre2 */

/*                                            */
/*           end of sevenpart3dre2            */
/*                                            */
/**********************************************/




