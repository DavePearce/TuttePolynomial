#include "core/tutte.h"
#include <memory.h>
/**********************************************/
/*                                            */
/*           start of sevenpart3drd1          */
/*                                            */
 
 
/* 

Precondition: g is a simple seven vertex graph with 5 edges 
              degseq is 3310 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3drd1(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX)

{
int d31,            /* location on vertex list of vertex of degree 3    */
    d41,            /* location on vertex list of vertex of degree 4    */
    d42,
    d43,
    vt,             /* location on vertex list                           */
    sum,            /* accumulators for degress of sets of vertices      */
    sum1,
    sum2,
    sum3;


//printf("sevenpart3drd1\n");
    


//printf("degseq=%d\n",degseq);
switch(degseq)
{  /* 1 */
case 3310:/* calculate the sum of the degrees of the neighbors 
             of the vertex of degree 3. case 15: add the degrees 
             of the neighbors of two of the vertices of degree 4. 
             case 14: determine the values of the sum of the 
             degrees of the neighbors of each of the degree 4 
             vertices */
 { 
/* printf("3310\n");*/  
  vt = firstVertex(g); 
  d41 = nextofdegree(
                     g,
                     &vt,
                     FOUR
                    );
  d42 = nextofdegree(
                     g,
                     &vt,
                     FOUR
                    );
  d43 = nextofdegree(
                     g,
                     &vt,
                     FOUR
                    );
  vt = firstVertex(g);  
  d31 = nextofdegree(
                     g,
                     &vt,
                     THREE 
                    );
  switch( degreesofnhbrs(g,d31) )
   { 
    case 12:
     { /* G1206 *//*printf("spt322\n");*/
 /*
W1000
*/
/*
w1000


******************* reading edge list *************




(  2,  5) (  3,  7) (  3,  5) (  4,  5) (  2,  7) (  3,  6) (  5,  7) 
(  5,  6) (  1,  4) (  1,  2) (  2,  6) (  6,  7) (  4,  6) (  1,  3) 
(  4,  7) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              30      75      72      35       9       1 
I =   1      30     138     150      62      10 
I =   2      93     189      96      18 
I =   3     129     139      42       3 
I =   4     118      77      12 
I =   5      84      30       3 
I =   6      47       8 
I =   7      20       1 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      30; 
tutteMat[  0][  2] =      75; 
tutteMat[  0][  3] =      72; 
tutteMat[  0][  4] =      35; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      30; 
tutteMat[  1][  1] =     138; 
tutteMat[  1][  2] =     150; 
tutteMat[  1][  3] =      62; 
tutteMat[  1][  4] =      10; 
tutteMat[  2][  0] =      93; 
tutteMat[  2][  1] =     189; 
tutteMat[  2][  2] =      96; 
tutteMat[  2][  3] =      18; 
tutteMat[  3][  0] =     129; 
tutteMat[  3][  1] =     139; 
tutteMat[  3][  2] =      42; 
tutteMat[  3][  3] =       3; 
tutteMat[  4][  0] =     118; 
tutteMat[  4][  1] =      77; 
tutteMat[  4][  2] =      12; 
tutteMat[  5][  0] =      84; 
tutteMat[  5][  1] =      30; 
tutteMat[  5][  2] =       3; 
tutteMat[  6][  0] =      47; 
tutteMat[  6][  1] =       8; 
tutteMat[  7][  0] =      20; 
tutteMat[  7][  1] =       1; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

     
     } 
    break;
    case 13:
     { /* G1201 *//* printf("spt323\n");*/
/*
W0998
*/
/*
w0998

******************* reading edge list *************




(  4,  5) (  2,  7) (  1,  7) (  3,  6) (  2,  5) (  2,  6) (  3,  5) 
(  2,  4) (  3,  7) (  1,  4) (  1,  3) (  5,  7) (  5,  6) (  6,  7) 
(  4,  6) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              26      67      67      34       9       1 
I =   1      26     125     146      66      11 
I =   2      84     185     105      18 
I =   3     123     146      42       3 
I =   4     117      80      11 
I =   5      84      31       2 
I =   6      47       8 
I =   7      20       1 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      26; 
tutteMat[  0][  2] =      67; 
tutteMat[  0][  3] =      67; 
tutteMat[  0][  4] =      34; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      26; 
tutteMat[  1][  1] =     125; 
tutteMat[  1][  2] =     146; 
tutteMat[  1][  3] =      66; 
tutteMat[  1][  4] =      11; 
tutteMat[  2][  0] =      84; 
tutteMat[  2][  1] =     185; 
tutteMat[  2][  2] =     105; 
tutteMat[  2][  3] =      18; 
tutteMat[  3][  0] =     123; 
tutteMat[  3][  1] =     146; 
tutteMat[  3][  2] =      42; 
tutteMat[  3][  3] =       3; 
tutteMat[  4][  0] =     117; 
tutteMat[  4][  1] =      80; 
tutteMat[  4][  2] =      11; 
tutteMat[  5][  0] =      84; 
tutteMat[  5][  1] =      31; 
tutteMat[  5][  2] =       2; 
tutteMat[  6][  0] =      47; 
tutteMat[  6][  1] =       8; 
tutteMat[  7][  0] =      20; 
tutteMat[  7][  1] =       1; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

      
     } 
    break;
    case 15:
     { 
      sum = degreesofnhbrs(
                           g,
                           d41
                          );
      sum += degreesofnhbrs(
                            g,
                            d42
                           );
      if( sum == 36 )
       { /* G1205 *//*printf("spt324\n");*/
/*
W0993
*/
/*
w0993

******************* reading edge list *************




(  1,  5) (  1,  7) (  1,  6) (  3,  7) (  4,  6) (  3,  4) (  2,  3) 
(  4,  5) (  3,  5) (  2,  7) (  2,  4) (  2,  6) (  6,  7) (  5,  6) 
(  5,  7) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              22      61      65      34       9       1 
I =   1      22     115     148      70      11 
I =   2      76     187     115      18 
I =   3     119     156      42       1 
I =   4     117      84       9 
I =   5      84      33 
I =   6      47       8 
I =   7      20       1 
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
tutteMat[  1][  1] =     115; 
tutteMat[  1][  2] =     148; 
tutteMat[  1][  3] =      70; 
tutteMat[  1][  4] =      11; 
tutteMat[  2][  0] =      76; 
tutteMat[  2][  1] =     187; 
tutteMat[  2][  2] =     115; 
tutteMat[  2][  3] =      18; 
tutteMat[  3][  0] =     119; 
tutteMat[  3][  1] =     156; 
tutteMat[  3][  2] =      42; 
tutteMat[  3][  3] =       1; 
tutteMat[  4][  0] =     117; 
tutteMat[  4][  1] =      84; 
tutteMat[  4][  2] =       9; 
tutteMat[  5][  0] =      84; 
tutteMat[  5][  1] =      33; 
tutteMat[  6][  0] =      47; 
tutteMat[  6][  1] =       8; 
tutteMat[  7][  0] =      20; 
tutteMat[  7][  1] =       1; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

        
       } 
      else
       if( sum > 36 )
        { /* G1202 *//*printf("spt325\n");*/ 
tutteMat[  0][  1] =      25; 
tutteMat[  0][  2] =      67; 
tutteMat[  0][  3] =      69; 
tutteMat[  0][  4] =      35; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      25; 
tutteMat[  1][  1] =      124; 
tutteMat[  1][  2] =     152; 
tutteMat[  1][  3] =      69; 
tutteMat[  1][  4] =      10; 
tutteMat[  2][  0] =      82; 
tutteMat[  2][  1] =     191; 
tutteMat[  2][  2] =      114; 
tutteMat[  2][  3] =      17; 
tutteMat[  3][  0] =      123; 
tutteMat[  3][  1] =     156; 
tutteMat[  3][  2] =      41; 
tutteMat[  4][  0] =      118; 
tutteMat[  4][  1] =      84; 
tutteMat[  4][  2] =      8; 
tutteMat[  5][  0] =      84; 
tutteMat[  5][  1] =      33; 
tutteMat[  6][  0] =      47; 
tutteMat[  6][  1] =      8; 
tutteMat[  7][  0] =      20; 
tutteMat[  7][  1] =       1; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

    }     
     } 
    break;
    case 14:
     { 
      sum1 = degreesofnhbrs(
                            g,
                            d41
                           );
      sum2 = degreesofnhbrs(
                            g,
                            d42
                           );
      sum3 = degreesofnhbrs(
                            g,
                            d43
                           );
      if( ( sum1 == 16 ) || ( sum2 == 16 ) || ( sum3 == 16 ) )
       { /* G1203 *//* printf("spt326\n");*/
/*
W0997
*/
/*
w0997

******************* reading edge list *************




(  4,  5) (  2,  7) (  3,  6) (  1,  4) (  2,  6) (  2,  4) (  1,  6) 
(  3,  7) (  5,  7) (  1,  7) (  3,  5) (  2,  5) (  6,  7) (  5,  6) 
(  3,  4) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              28      72      71      35       9       1 
I =   1      28     132     151      65      10 
I =   2      88     190     105      17 
I =   3     126     148      41       2 
I =   4     118      81      10 
I =   5      84      32       1 
I =   6      47       8 
I =   7      20       1 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      28; 
tutteMat[  0][  2] =      72; 
tutteMat[  0][  3] =      71; 
tutteMat[  0][  4] =      35; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      28; 
tutteMat[  1][  1] =     132; 
tutteMat[  1][  2] =     151; 
tutteMat[  1][  3] =      65; 
tutteMat[  1][  4] =      10; 
tutteMat[  2][  0] =      88; 
tutteMat[  2][  1] =     190; 
tutteMat[  2][  2] =     105; 
tutteMat[  2][  3] =      17; 
tutteMat[  3][  0] =     126; 
tutteMat[  3][  1] =     148; 
tutteMat[  3][  2] =      41; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =     118; 
tutteMat[  4][  1] =      81; 
tutteMat[  4][  2] =      10; 
tutteMat[  5][  0] =      84; 
tutteMat[  5][  1] =      32; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      47; 
tutteMat[  6][  1] =       8; 
tutteMat[  7][  0] =      20; 
tutteMat[  7][  1] =       1; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

        
       } 
      else
      if( ( sum1 == 17 ) || ( sum2 == 17 ) || ( sum3 == 17 ) )
        { /* G1200 */ /*printf("spt327\n");*/
/*
W0995
*/
/*
w0995

******************* reading edge list *************




(  3,  4) (  2,  3) (  1,  4) (  2,  6) (  2,  5) (  3,  5) (  2,  7) 
(  1,  6) (  4,  5) (  5,  6) (  1,  7) (  6,  7) (  4,  6) (  3,  7) 
(  5,  7) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              24      64      66      34       9       1 
I =   1      24     120     147      68      11 
I =   2      80     186     110      18 
I =   3     121     151      42       2 
I =   4     117      82      10 
I =   5      84      32       1 
I =   6      47       8 
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
tutteMat[  1][  1] =     120; 
tutteMat[  1][  2] =     147; 
tutteMat[  1][  3] =      68; 
tutteMat[  1][  4] =      11; 
tutteMat[  2][  0] =      80; 
tutteMat[  2][  1] =     186; 
tutteMat[  2][  2] =     110; 
tutteMat[  2][  3] =      18; 
tutteMat[  3][  0] =     121; 
tutteMat[  3][  1] =     151; 
tutteMat[  3][  2] =      42; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =     117; 
tutteMat[  4][  1] =      82; 
tutteMat[  4][  2] =      10; 
tutteMat[  5][  0] =      84; 
tutteMat[  5][  1] =      32; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      47; 
tutteMat[  6][  1] =       8; 
tutteMat[  7][  0] =      20; 
tutteMat[  7][  1] =       1; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

         
        } 
       else
        { /* G1204 */ /*printf("spt328\n");*/
/*
W0992
*/
/*
w0992

******************* reading edge list *************




(  1,  7) (  3,  5) (  1,  6) (  4,  7) (  4,  6) (  2,  6) (  1,  4) 
(  2,  3) (  3,  7) (  2,  5) (  5,  7) (  5,  6) (  2,  7) (  4,  5) 
(  3,  6) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              22      61      65      34       9       1 
I =   1      22     115     148      70      11 
I =   2      76     186     113      17 
I =   3     118     154      42       2 
I =   4     116      84       9 
I =   5      84      32       1 
I =   6      47       8 
I =   7      20       1 
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
tutteMat[  1][  1] =     115; 
tutteMat[  1][  2] =     148; 
tutteMat[  1][  3] =      70; 
tutteMat[  1][  4] =      11; 
tutteMat[  2][  0] =      76; 
tutteMat[  2][  1] =     186; 
tutteMat[  2][  2] =     113; 
tutteMat[  2][  3] =      17; 
tutteMat[  3][  0] =     118; 
tutteMat[  3][  1] =     154; 
tutteMat[  3][  2] =      42; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =     116; 
tutteMat[  4][  1] =      84; 
tutteMat[  4][  2] =       9; 
tutteMat[  5][  0] =      84; 
tutteMat[  5][  1] =      32; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      47; 
tutteMat[  6][  1] =       8; 
tutteMat[  7][  0] =      20; 
tutteMat[  7][  1] =       1; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

         
        } 
     } 
    break;
   } 
 } 
break;

default:
  {
     printf("sevenpart3drd\1n");
     break;
  }

} /*  end switch on degseq */



}  /* end sevenpart3drd1 */

/*                                            */
/*           end of sevenpart3drd1            */
/*                                            */
/**********************************************/




