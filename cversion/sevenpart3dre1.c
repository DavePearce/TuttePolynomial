#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3dre           */
/*                                            */
 
 
/* 

Precondition: g is a simple seven vertex graph with 14 or 15 edges 
              degseq is one of 11230 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3dre1(
               struct graph *g,
               int degseq,
               TUTTE tutteMat,
               TUTTEO tutteMatX
              )



{
int 
    d31,            /* location on vertex list of vertices of degree 3  */
    d32, 
    d33,
    d41,            /* location on vertex list of vertex of degree 5    */
    d42,
    vt,             /* location on vertex list                           */
    sum,            /* accumulators for degress of sets of vertices      */
    sum1,
    sum2,
    sum3;



//printf("sevenpart3dre\n");    

switch(degseq)
{  /* 1 */



case 11230:/* check of the vertices of degree 4 are not adjacent. 
              if adjacent use the sums of the degrees of the 
              neighbors of the vertices of degree 3 to resolve 
              the other cases */
 { 
  vt = firstVertex(g);  
  d41 = nextofdegree(g,&vt,FOUR);
  d42 = nextofdegree(g,&vt,FOUR);
  if( !isadj(d41,d42,g) )
     { /* g1142 */ /*printf("spt338\n");*/
/*
W0923
*/
/*
w0923

******************* reading edge list *************




(  1,  7) (  1,  6) (  2,  7) (  2,  6) (  3,  7) (  2,  4) (  6,  7) 
(  3,  5) (  1,  5) (  4,  6) (  5,  6) (  5,  7) (  3,  4) (  4,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              12      36      43      26       8       1 
I =   1      12      63      89      50      10 
I =   2      39     100      72      15 
I =   3      57      83      30       2 
I =   4      53      46       7 
I =   5      36      17 
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
tutteMat[  1][  1] =      63; 
tutteMat[  1][  2] =      89; 
tutteMat[  1][  3] =      50; 
tutteMat[  1][  4] =      10; 
tutteMat[  2][  0] =      39; 
tutteMat[  2][  1] =     100; 
tutteMat[  2][  2] =      72; 
tutteMat[  2][  3] =      15; 
tutteMat[  3][  0] =      57; 
tutteMat[  3][  1] =      83; 
tutteMat[  3][  2] =      30; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =      53; 
tutteMat[  4][  1] =      46; 
tutteMat[  4][  2] =       7; 
tutteMat[  5][  0] =      36; 
tutteMat[  5][  1] =      17; 
tutteMat[  6][  0] =      18; 
tutteMat[  6][  1] =       3; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

      
     } 
  else
   { 
    vt=firstVertex(g);
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
    sum = sum1 + sum2 + sum3;
    if( sum == 42 )
     {
      if( sum1 == sum2)     
       {
        /* g1144 */ /*printf("spt339\n");*/
/*
W0922
*/
/*
w0922

******************* reading edge list *************




(  1,  5) (  4,  6) (  5,  6) (  2,  6) (  2,  3) (  3,  6) (  1,  4) 
(  3,  7) (  5,  7) (  2,  7) (  1,  7) (  4,  5) (  4,  7) (  6,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               8      28      38      25       8       1 
I =   1       8      50      83      52      11 
I =   2      30      93      75      16 
I =   3      50      84      31       3 
I =   4      51      46       8 
I =   5      36      16       1 
I =   6      18       3 
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
tutteMat[  1][  1] =      50; 
tutteMat[  1][  2] =      83; 
tutteMat[  1][  3] =      52; 
tutteMat[  1][  4] =      11; 
tutteMat[  2][  0] =      30; 
tutteMat[  2][  1] =      93; 
tutteMat[  2][  2] =      75; 
tutteMat[  2][  3] =      16; 
tutteMat[  3][  0] =      50; 
tutteMat[  3][  1] =      84; 
tutteMat[  3][  2] =      31; 
tutteMat[  3][  3] =       3; 
tutteMat[  4][  0] =      51; 
tutteMat[  4][  1] =      46; 
tutteMat[  4][  2] =       8; 
tutteMat[  5][  0] =      36; 
tutteMat[  5][  1] =      16; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      18; 
tutteMat[  6][  1] =       3; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

        
       } 
      else 
       { /* g1141 *//*printf("spt340\n");*/
/*
W0929
*/
/*
w0929

******************* reading edge list *************




(  1,  6) (  1,  5) (  4,  6) (  2,  6) (  2,  3) (  5,  6) (  1,  7) 
(  5,  7) (  4,  5) (  4,  7) (  3,  4) (  3,  7) (  2,  7) (  6,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              12      36      43      26       8       1 
I =   1      12      63      88      49      10 
I =   2      39      99      70      16 
I =   3      57      81      30       2 
I =   4      53      44       8 
I =   5      36      16       1 
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
tutteMat[  1][  1] =      63; 
tutteMat[  1][  2] =      88; 
tutteMat[  1][  3] =      49; 
tutteMat[  1][  4] =      10; 
tutteMat[  2][  0] =      39; 
tutteMat[  2][  1] =      99; 
tutteMat[  2][  2] =      70; 
tutteMat[  2][  3] =      16; 
tutteMat[  3][  0] =      57; 
tutteMat[  3][  1] =      81; 
tutteMat[  3][  2] =      30; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =      53; 
tutteMat[  4][  1] =      44; 
tutteMat[  4][  2] =       8; 
tutteMat[  5][  0] =      36; 
tutteMat[  5][  1] =      16; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      18; 
tutteMat[  6][  1] =       3; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

        
       } 
     }
    else 
     if( sum == 45 )
      { /* g1143 */ /*printf("spt341\n");*/
/*
W0924
*/
/*
w0924

******************* reading edge list *************




(  1,  7) (  3,  4) (  1,  5) (  2,  5) (  2,  6) (  4,  5) (  4,  6) 
(  5,  7) (  2,  7) (  3,  7) (  1,  6) (  3,  6) (  6,  7) (  4,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              14      41      47      27       8       1 
I =   1      14      69      92      48       9 
I =   2      42     102      71      15 
I =   3      58      84      30       1 
I =   4      53      47       6 
I =   5      36      17 
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
tutteMat[  1][  1] =      69; 
tutteMat[  1][  2] =      92; 
tutteMat[  1][  3] =      48; 
tutteMat[  1][  4] =       9; 
tutteMat[  2][  0] =      42; 
tutteMat[  2][  1] =     102; 
tutteMat[  2][  2] =      71; 
tutteMat[  2][  3] =      15; 
tutteMat[  3][  0] =      58; 
tutteMat[  3][  1] =      84; 
tutteMat[  3][  2] =      30; 
tutteMat[  3][  3] =       1; 
tutteMat[  4][  0] =      53; 
tutteMat[  4][  1] =      47; 
tutteMat[  4][  2] =       6; 
tutteMat[  5][  0] =      36; 
tutteMat[  5][  1] =      17; 
tutteMat[  6][  0] =      18; 
tutteMat[  6][  1] =       3; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

      
      } 
   } 
 } 
break;


default:
  {
     printf("sevenpart3dre1\n");
     break;
  }

} /*  end switch on degseq */

}  /* end sevenpart3dre1 */

/*                                            */
/*           end of sevenpart3dre1            */
/*                                            */
/**********************************************/




