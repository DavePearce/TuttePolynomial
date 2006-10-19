#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3drc1          */
/*                                            */
 
/* 

Precondition: g is a simple seven vertex graph with 14 edges 
              degseq is 11410 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3drc1(
               struct graph *g,
               int degseq,
               TUTTE tutteMat,
               TUTTEO tutteMatX
              )


{
int d31,            /* location on vertex list of vertices of degree 3  */
    d51,            /* location on vertex list of vertex of degree 5     */
    vt;             /* location on vertex list                           */

printf("sevenpart3drc1\n");

switch( degseq )
{  /* 1 */

case 11410:/* find the number of common adjacencies for the vertex
              of degree 3 and the vertex of degree 5 */
 {/*printf("11410\n"); */
  vt = firstVertex(g);
  d31 = nextofdegree(
                     g,
                     &vt,
                     THREE
                    );
  vt=firstVertex(g);
  d51 = nextofdegree(
                     g,
                     &vt,
                     FIVE 
                    );
  switch( commonadj(g,d31,d51) )
   {
    case ONE:
     { /* G1197 */ /*printf("spt313\n")*/
 /*
W0989
*/

/*

******************* reading edge list *************




(  1,  5) (  2,  5) (  2,  6) (  2,  7) (  1,  6) (  2,  4) (  4,  6) 
(  3,  7) (  6,  7) (  3,  4) (  5,  7) (  1,  7) (  4,  7) (  3,  5) 
(  3,  6) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              24      64      66      34       9       1 
I =   1      24     117     142      66      11 
I =   2      77     176     107      20 
I =   3     113     145      46       2 
I =   4     109      84      12 
I =   5      80      35       1 
I =   6      46       9 
I =   7      20       1 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      24; 
tutteMat[  0][  2] =      64; 
tutteMat[  0][  3] =      66; 
tutteMat[  0][  4] =      34; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      24; 
tutteMat[  1][  1] =     117; 
tutteMat[  1][  2] =     142; 
tutteMat[  1][  3] =      66; 
tutteMat[  1][  4] =      11; 
tutteMat[  2][  0] =      77; 
tutteMat[  2][  1] =     176; 
tutteMat[  2][  2] =     107; 
tutteMat[  2][  3] =      20; 
tutteMat[  3][  0] =     113; 
tutteMat[  3][  1] =     145; 
tutteMat[  3][  2] =      46; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =     109; 
tutteMat[  4][  1] =      84; 
tutteMat[  4][  2] =      12; 
tutteMat[  5][  0] =      80; 
tutteMat[  5][  1] =      35; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      46; 
tutteMat[  6][  1] =       9; 
tutteMat[  7][  0] =      20; 
tutteMat[  7][  1] =       1; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

     
     } 
    break;
    case TWO:
     { /* G1198 *//* printf("spt314\n");*/
/*
W0988
*//*printf("988A\n");*/
/*

******************* reading edge list *************




(  2,  4) (  2,  3) (  4,  7) (  4,  5) (  1,  6) (  3,  4) (  6,  7) 
(  2,  6) (  3,  7) (  3,  6) (  1,  5) (  5,  7) (  2,  7) (  5,  6) 
(  1,  7) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              20      56      61      33       9       1 
I =   1      20     104     137      69      12 
I =   2      68     170     112      20 
I =   3     106     148      47       3 
I =   4     107      86      12 
I =   5      80      35       1 
I =   6      46       9 
I =   7      20       1 
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
tutteMat[  1][  1] =     104; 
tutteMat[  1][  2] =     137; 
tutteMat[  1][  3] =      69; 
tutteMat[  1][  4] =      12; 
tutteMat[  2][  0] =      68; 
tutteMat[  2][  1] =     170; 
tutteMat[  2][  2] =     112; 
tutteMat[  2][  3] =      20; 
tutteMat[  3][  0] =     106; 
tutteMat[  3][  1] =     148; 
tutteMat[  3][  2] =      47; 
tutteMat[  3][  3] =       3; 
tutteMat[  4][  0] =     107; 
tutteMat[  4][  1] =      86; 
tutteMat[  4][  2] =      12; 
tutteMat[  5][  0] =      80; 
tutteMat[  5][  1] =      35; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      46; 
tutteMat[  6][  1] =       9; 
tutteMat[  7][  0] =      20; 
tutteMat[  7][  1] =       1; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

      
     } 
    break;
    case THREE:
     { /* G1199 */ /*printf("spt315\n");*/
 /*
W0990
*//*printf("990\n");*/
/*

******************* reading edge list *************




(  2,  3) (  1,  5) (  2,  6) (  3,  7) (  2,  7) (  1,  7) (  6,  7) 
(  4,  7) (  3,  6) (  1,  4) (  5,  6) (  4,  6) (  2,  5) (  5,  7) 
(  3,  4) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              22      59      62      33       9       1 
I =   1      22     110     137      67      12 
I =   2      73     172     108      21 
I =   3     111     144      46       3 
I =   4     109      82      13 
I =   5      80      34       2 
I =   6      46       9 
I =   7      20       1 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      22; 
tutteMat[  0][  2] =      59; 
tutteMat[  0][  3] =      62; 
tutteMat[  0][  4] =      33; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      22; 
tutteMat[  1][  1] =     110; 
tutteMat[  1][  2] =     137; 
tutteMat[  1][  3] =      67; 
tutteMat[  1][  4] =      12; 
tutteMat[  2][  0] =      73; 
tutteMat[  2][  1] =     172; 
tutteMat[  2][  2] =     108; 
tutteMat[  2][  3] =      21; 
tutteMat[  3][  0] =     111; 
tutteMat[  3][  1] =     144; 
tutteMat[  3][  2] =      46; 
tutteMat[  3][  3] =       3; 
tutteMat[  4][  0] =     109; 
tutteMat[  4][  1] =      82; 
tutteMat[  4][  2] =      13; 
tutteMat[  5][  0] =      80; 
tutteMat[  5][  1] =      34; 
tutteMat[  5][  2] =       2; 
tutteMat[  6][  0] =      46; 
tutteMat[  6][  1] =       9; 
tutteMat[  7][  0] =      20; 
tutteMat[  7][  1] =       1; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

     
     } 
    break;
   } 
 } 
break;

default:
  {
     printf("sevenpart3drc1\n");
     break;
  }


} /*  end switch on degseq */
}  /* end sevenpart3drc1 */

/*                                            */
/*           end of sevenpart3drc1            */
/*                                            */
/**********************************************/




