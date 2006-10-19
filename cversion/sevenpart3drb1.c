#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3drb1          */
/*                                            */
 


 
/* 

Precondition: g is a simple seven vertex graph with 14 or 15 edges 
              degseq is 20320
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3drb1(
               struct graph *g,
               int degseq,
               TUTTE tutteMat,
               TUTTEO tutteMatX
              )


{

int d31,            /* location on vertex list of vertices of degree 3  */
    d32, 
    vt;             /* location on vertex list                           */


//printf("sevenpart3drb1\n");

switch(degseq)
  {  /* 1 */

     case 20320:/* check whether vertices of degree 3 are adjacent */
       {
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
           { /* G1188 */ /*printf("spt34\n");*/
/*
W0977
*/

/*


******************* reading edge list *************




(  1,  7) (  3,  6) (  2,  6) (  2,  7) (  4,  6) (  3,  4) (  3,  5) 
(  1,  6) (  4,  5) (  6,  7) (  4,  7) (  1,  2) (  5,  7) (  5,  6) 
(  3,  7) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              12      40      51      31       9       1 
I =   1      12      74     118      70      14 
I =   2      46     139     109      24 
I =   3      78     132      54       6 
I =   4      84      85      19 
I =   5      67      39       4 
I =   6      41      12       1 
I =   7      19       2 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      12; 
tutteMat[  0][  2] =      40; 
tutteMat[  0][  3] =      51; 
tutteMat[  0][  4] =      31; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      12; 
tutteMat[  1][  1] =      74; 
tutteMat[  1][  2] =     118; 
tutteMat[  1][  3] =      70; 
tutteMat[  1][  4] =      14; 
tutteMat[  2][  0] =      46; 
tutteMat[  2][  1] =     139; 
tutteMat[  2][  2] =     109; 
tutteMat[  2][  3] =      24; 
tutteMat[  3][  0] =      78; 
tutteMat[  3][  1] =     132; 
tutteMat[  3][  2] =      54; 
tutteMat[  3][  3] =       6; 
tutteMat[  4][  0] =      84; 
tutteMat[  4][  1] =      85; 
tutteMat[  4][  2] =      19; 
tutteMat[  5][  0] =      67; 
tutteMat[  5][  1] =      39; 
tutteMat[  5][  2] =       4; 
tutteMat[  6][  0] =      41; 
tutteMat[  6][  1] =      12; 
tutteMat[  6][  2] =       1; 
tutteMat[  7][  0] =      19; 
tutteMat[  7][  1] =       2; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

    
   } 
  else
   { /* G1187 *//*printf("spt35\n");*/
/*
W0975
*/
/*

******************* reading edge list *************




(  3,  4) (  1,  7) (  2,  7) (  2,  6) (  4,  7) (  3,  5) (  1,  6) 
(  1,  5) (  4,  6) (  3,  7) (  2,  4) (  5,  7) (  3,  6) (  6,  7) 
(  5,  6) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              16      48      56      32       9       1 
I =   1      16      87     124      68      13 
I =   2      55     147     108      24 
I =   3      86     133      53       4 
I =   4      87      85      18 
I =   5      67      41       3 
I =   6      41      13 
I =   7      19       2 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      16; 
tutteMat[  0][  2] =      48; 
tutteMat[  0][  3] =      56; 
tutteMat[  0][  4] =      32; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      16; 
tutteMat[  1][  1] =      87; 
tutteMat[  1][  2] =     124; 
tutteMat[  1][  3] =      68; 
tutteMat[  1][  4] =      13; 
tutteMat[  2][  0] =      55; 
tutteMat[  2][  1] =     147; 
tutteMat[  2][  2] =     108; 
tutteMat[  2][  3] =      24; 
tutteMat[  3][  0] =      86; 
tutteMat[  3][  1] =     133; 
tutteMat[  3][  2] =      53; 
tutteMat[  3][  3] =       4; 
tutteMat[  4][  0] =      87; 
tutteMat[  4][  1] =      85; 
tutteMat[  4][  2] =      18; 
tutteMat[  5][  0] =      67; 
tutteMat[  5][  1] =      41; 
tutteMat[  5][  2] =       3; 
tutteMat[  6][  0] =      41; 
tutteMat[  6][  1] =      13; 
tutteMat[  7][  0] =      19; 
tutteMat[  7][  1] =       2; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

    
   } 
 } 
break;

default:
  {
     printf("sevenpart3drb1\n");
  }
break;


} /*  end switch on degseq */

}  /* end sevenpart3drb1 */

/*                                            */
/*           end of sevenpart3drb1            */
/*                                            */
/**********************************************/




