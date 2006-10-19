#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3drb3          */
/*                                            */
 


 
/* 

Precondition: g is a simple seven vertex graph with 15 edges 
              degseq is 4120
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3drb3(
               struct graph *g,
               int degseq,
               TUTTE tutteMat,
               TUTTEO tutteMatX
              )



{
int d31,            /* location on vertex list of vertices of degree 3  */
    d32, 
    d41,            /* location on vertex list of vertex of degree 5    */
    vt;             /* location on vertex list                           */



printf(" sevenpart3drb3 degseq=%d\n",degseq);
switch(degseq)
{  /* 1 */

case 4120:/* check whether the two vertices of degree 3 are
             adjacent. If not, see if the vertex of degree 4
             is adjacent to 0 or 1 vertex of degree 3 */
{/*printf("4120\n"); */
 vt = firstVertex(g);
 d31 = nextofdegree(
                    g,
                    &vt,
                    THREE
                   );
 d32 = nextofdegree(
                    g,
                    &vt,
                    THREE
                   );
 if( isadj(d31,d32,g) )
  { /* G1196 */ /*printf("spt310\n");*/
/*
W0991
*/
/*

******************* reading edge list *************




(  2,  5) (  2,  4) (  3,  5) (  1,  6) (  3,  4) (  1,  7) (  4,  6) 
(  1,  2) (  5,  6) (  3,  7) (  3,  6) (  4,  5) (  6,  7) (  5,  7) 
(  4,  7) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              24      62      63      33       9       1 
I =   1      24     114     134      64      12 
I =   2      76     166      99      21 
I =   3     109     132      46       5 
I =   4     103      77      16 
I =   5      75      33       4 
I =   6      43      10       1 
I =   7      19       2 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      24; 
tutteMat[  0][  2] =      62; 
tutteMat[  0][  3] =      63; 
tutteMat[  0][  4] =      33; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      24; 
tutteMat[  1][  1] =     114; 
tutteMat[  1][  2] =     134; 
tutteMat[  1][  3] =      64; 
tutteMat[  1][  4] =      12; 
tutteMat[  2][  0] =      76; 
tutteMat[  2][  1] =     166; 
tutteMat[  2][  2] =      99; 
tutteMat[  2][  3] =      21; 
tutteMat[  3][  0] =     109; 
tutteMat[  3][  1] =     132; 
tutteMat[  3][  2] =      46; 
tutteMat[  3][  3] =       5; 
tutteMat[  4][  0] =     103; 
tutteMat[  4][  1] =      77; 
tutteMat[  4][  2] =      16; 
tutteMat[  5][  0] =      75; 
tutteMat[  5][  1] =      33; 
tutteMat[  5][  2] =       4; 
tutteMat[  6][  0] =      43; 
tutteMat[  6][  1] =      10; 
tutteMat[  6][  2] =       1; 
tutteMat[  7][  0] =      19; 
tutteMat[  7][  1] =       2; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

   
  } 
 else
  { 
   vt = firstVertex(g);
   d41 = nextofdegree(
                      g,
                      &vt,
                      FOUR
                     );
   if (nodegnadjtov(g,d41,THREE) )
    { /* G1194 */ /*printf("spt311\n");*/
/*
W0987
*//*printf("A\n");*/
/*

******************* reading edge list *************




(  2,  7) (  2,  3) (  1,  7) (  1,  5) (  4,  7) (  5,  6) (  1,  6) 
(  4,  5) (  4,  6) (  3,  4) (  5,  7) (  3,  6) (  3,  5) (  6,  7) 
(  2,  4) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              20      56      61      33       9       1 
I =   1      20     103     135      68      12 
I =   2      67     166     110      21 
I =   3     103     143      47       3 
I =   4     102      83      14 
I =   5      75      36       2 
I =   6      43      11 
I =   7      19       2 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      20; 
tutteMat[  0][  2] =      56; 
tutteMat[  0][  3] =      61; 
tutteMat[  0][  4] =      33; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      20; 
tutteMat[  1][  1] =     103; 
tutteMat[  1][  2] =     135; 
tutteMat[  1][  3] =      68; 
tutteMat[  1][  4] =      12; 
tutteMat[  2][  0] =      67; 
tutteMat[  2][  1] =     166; 
tutteMat[  2][  2] =     110; 
tutteMat[  2][  3] =      21; 
tutteMat[  3][  0] =     103; 
tutteMat[  3][  1] =     143; 
tutteMat[  3][  2] =      47; 
tutteMat[  3][  3] =       3; 
tutteMat[  4][  0] =     102; 
tutteMat[  4][  1] =      83; 
tutteMat[  4][  2] =      14; 
tutteMat[  5][  0] =      75; 
tutteMat[  5][  1] =      36; 
tutteMat[  5][  2] =       2; 
tutteMat[  6][  0] =      43; 
tutteMat[  6][  1] =      11; 
tutteMat[  7][  0] =      19; 
tutteMat[  7][  1] =       2; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

     
    } 
   else
    { /* G1195 *//* printf("spt312\n");*/
/*
W0986
*//*printf("B\n");*/
/*

******************* reading edge list *************




(  1,  5) (  2,  7) (  3,  4) (  2,  6) (  3,  6) (  1,  6) (  1,  7) 
(  2,  4) (  3,  5) (  4,  5) (  4,  6) (  3,  7) (  4,  7) (  5,  6) 
(  5,  7) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              22      61      65      34       9       1 
I =   1      22     111     142      68      11 
I =   2      72     173     110      19 
I =   3     107     145      46       2 
I =   4     103      85      12 
I =   5      75      37       1 
I =   6      43      11 
I =   7      19       2 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      22; 
tutteMat[  0][  2] =      61; 
tutteMat[  0][  3] =      65; 
tutteMat[  0][  4] =      34; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      22; 
tutteMat[  1][  1] =     111; 
tutteMat[  1][  2] =     142; 
tutteMat[  1][  3] =      68; 
tutteMat[  1][  4] =      11; 
tutteMat[  2][  0] =      72; 
tutteMat[  2][  1] =     173; 
tutteMat[  2][  2] =     110; 
tutteMat[  2][  3] =      19; 
tutteMat[  3][  0] =     107; 
tutteMat[  3][  1] =     145; 
tutteMat[  3][  2] =      46; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =     103; 
tutteMat[  4][  1] =      85; 
tutteMat[  4][  2] =      12; 
tutteMat[  5][  0] =      75; 
tutteMat[  5][  1] =      37; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      43; 
tutteMat[  6][  1] =      11; 
tutteMat[  7][  0] =      19; 
tutteMat[  7][  1] =       2; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

     
    } 
  } 
 } 
break;
default:
  {
     printf("sevenpart3drb3\n");
     break;
  }


} /*  end switch on degseq */
}  /* end sevenpart3drb3 */

/*                                            */
/*           end of sevenpart3drb3            */
/*                                            */
/**********************************************/




