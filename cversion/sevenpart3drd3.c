#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3drd           */
/*                                            */
 
 
/* 

Precondition: g is a simple seven vertex graph with 14 or 15 edges 
              degseq is 3130 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3drd3(
               struct graph *g,
               int degseq,
               TUTTE tutteMat,
               TUTTEO tutteMatX
              )


{
int d31,            /* location on vertex list of vertices of degree 3  */
    d32, 
    d33,
    vt,             /* location on vertex list                           */
    sum1,            /* accumulators for degress of sets of vertices      */
    sum2,
    sum3;


//printf("sevenpart3drd3\n");
    
switch(degseq)
{  /* 1 */


case 3130:/* sum the sums of the degrees of the
             neighbors of the vertices of degree 3. keep these three 
             sums separate for resolving the case not differentiated 
             by the sum of sums */
 { 
/*printf("3130\n");*/  
  vt= firstVertex(g);  
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
  d33 = nextofdegree(
                     g,
                     &vt,
                     THREE 
                    );
  sum1 = degreesofnhbrs(
                        g,
                        d31
                       );
  sum2 = degreesofnhbrs(
                        g,
                        d32
                       );
  sum3 = degreesofnhbrs(
                        g,
                        d33
                       );
  switch( sum1 + sum2 + sum3 )
   { 
    case 40:
     { 
      if( ( sum1 == 15 ) || ( sum2 == 15 ) || ( sum3 == 15 ) )
       { /* g1147  *//*printf("spt334\n");*/
/*
W0940
*/
/*
w0940

******************* reading edge list *************




(  4,  5) (  1,  6) (  3,  4) (  6,  7) (  1,  5) (  4,  6) (  1,  7) 
(  4,  7) (  2,  6) (  5,  6) (  3,  5) (  2,  3) (  5,  7) (  2,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              16      44      48      27       8       1 
I =   1      16      76      94      47       9 
I =   2      48     107      67      14 
I =   3      65      81      27       2 
I =   4      57      42       7 
I =   5      37      15       1 
I =   6      18       3 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      16; 
tutteMat[  0][  2] =      44; 
tutteMat[  0][  3] =      48; 
tutteMat[  0][  4] =      27; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      16; 
tutteMat[  1][  1] =      76; 
tutteMat[  1][  2] =      94; 
tutteMat[  1][  3] =      47; 
tutteMat[  1][  4] =       9; 
tutteMat[  2][  0] =      48; 
tutteMat[  2][  1] =     107; 
tutteMat[  2][  2] =      67; 
tutteMat[  2][  3] =      14; 
tutteMat[  3][  0] =      65; 
tutteMat[  3][  1] =      81; 
tutteMat[  3][  2] =      27; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =      57; 
tutteMat[  4][  1] =      42; 
tutteMat[  4][  2] =       7; 
tutteMat[  5][  0] =      37; 
tutteMat[  5][  1] =      15; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      18; 
tutteMat[  6][  1] =       3; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

       
       } 
      else
      if( ( sum1 == 14 ) || ( sum2 == 14 ) || ( sum3 == 14 ) )
        { /* g1145 */ /*printf("spt335\n");*/
/*
W0937
*/
/*
w0937

******************* reading edge list *************




(  2,  3) (  4,  6) (  2,  5) (  1,  7) (  1,  6) (  3,  5) (  5,  7) 
(  3,  6) (  6,  7) (  1,  4) (  5,  6) (  2,  7) (  4,  5) (  4,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              12      36      43      26       8       1 
I =   1      12      64      90      50      10 
I =   2      40     103      72      15 
I =   3      60      84      28       2 
I =   4      56      43       7 
I =   5      37      15       1 
I =   6      18       3 
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
tutteMat[  1][  1] =      64; 
tutteMat[  1][  2] =      90; 
tutteMat[  1][  3] =      50; 
tutteMat[  1][  4] =      10; 
tutteMat[  2][  0] =      40; 
tutteMat[  2][  1] =     103; 
tutteMat[  2][  2] =      72; 
tutteMat[  2][  3] =      15; 
tutteMat[  3][  0] =      60; 
tutteMat[  3][  1] =      84; 
tutteMat[  3][  2] =      28; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =      56; 
tutteMat[  4][  1] =      43; 
tutteMat[  4][  2] =       7; 
tutteMat[  5][  0] =      37; 
tutteMat[  5][  1] =      15; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      18; 
tutteMat[  6][  1] =       3; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

         
        } 
     } 
    break;
    case 43:
     { /* g1146 *//*printf("spt336\n");*/
/*
W0936
*/
/*
w0936

******************* reading edge list *************




(  1,  5) (  1,  6) (  3,  4) (  2,  7) (  6,  7) (  1,  7) (  2,  4) 
(  5,  7) (  4,  5) (  2,  6) (  5,  6) (  3,  7) (  4,  6) (  3,  5) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              14      41      47      27       8       1 
I =   1      14      72      97      50       9 
I =   2      45     110      72      13 
I =   3      64      86      27       1 
I =   4      57      45       5 
I =   5      37      16 
I =   6      18       3 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      14; 
tutteMat[  0][  2] =      41; 
tutteMat[  0][  3] =      47; 
tutteMat[  0][  4] =      27; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      14; 
tutteMat[  1][  1] =      72; 
tutteMat[  1][  2] =      97; 
tutteMat[  1][  3] =      50; 
tutteMat[  1][  4] =       9; 
tutteMat[  2][  0] =      45; 
tutteMat[  2][  1] =     110; 
tutteMat[  2][  2] =      72; 
tutteMat[  2][  3] =      13; 
tutteMat[  3][  0] =      64; 
tutteMat[  3][  1] =      86; 
tutteMat[  3][  2] =      27; 
tutteMat[  3][  3] =       1; 
tutteMat[  4][  0] =      57; 
tutteMat[  4][  1] =      45; 
tutteMat[  4][  2] =       5; 
tutteMat[  5][  0] =      37; 
tutteMat[  5][  1] =      16; 
tutteMat[  6][  0] =      18; 
tutteMat[  6][  1] =       3; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

      
     } 
    break;
    case 44:
     { /* g1148 *//*printf("spt337\n");*/
/*
W0934
*/
/*
w0934

******************* reading edge list *************




(  1,  7) (  1,  5) (  2,  5) (  2,  6) (  2,  7) (  1,  6) (  4,  6) 
(  3,  6) (  5,  6) (  4,  5) (  4,  7) (  3,  7) (  5,  7) (  3,  4) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              15      44      50      28       8       1 
I =   1      15      75     100      50       8 
I =   2      46     112      74      12 
I =   3      64      89      26 
I =   4      57      46       4 
I =   5      37      16 
I =   6      18       3 
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
tutteMat[  1][  1] =      75; 
tutteMat[  1][  2] =     100; 
tutteMat[  1][  3] =      50; 
tutteMat[  1][  4] =       8; 
tutteMat[  2][  0] =      46; 
tutteMat[  2][  1] =     112; 
tutteMat[  2][  2] =      74; 
tutteMat[  2][  3] =      12; 
tutteMat[  3][  0] =      64; 
tutteMat[  3][  1] =      89; 
tutteMat[  3][  2] =      26; 
tutteMat[  4][  0] =      57; 
tutteMat[  4][  1] =      46; 
tutteMat[  4][  2] =       4; 
tutteMat[  5][  0] =      37; 
tutteMat[  5][  1] =      16; 
tutteMat[  6][  0] =      18; 
tutteMat[  6][  1] =       3; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

      
     }  
    break;
   } 
 } 
break;
default:
  {
     printf("sevenpart3drd3\n");
     break;
  }

} /*  end switch on degseq */



}  /* end sevenpart3drd3 */

/*                                            */
/*           end of sevenpart3drd3            */
/*                                            */
/**********************************************/




