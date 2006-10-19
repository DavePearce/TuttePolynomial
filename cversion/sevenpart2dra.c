#include "tutte.h"

#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart2              */
/*                                            */

/* 

Precondition: g is a seven vertex graph with 16 or 17 edges
              degseq is the degree sequence of g and has value
              24001, 31210, or 15010
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte poly of this graph

*/ 


void
sevenpart2dra(
              struct graph *g,
              int degseq,
              TUTTE tutteMat,
              TUTTEO tutteMatX
             )

{

printf("sevenpart2dra\n");

switch( degseq )
  { 

     case 24001:/* degree */
       {/* G1234 *//* printf("sprt21\n");*/
/*
W1026
*/
/*

******************* reading edge list *************




(  2,  5) (  2,  6) (  3,  4) (  1,  6) (  3,  6) (  5,  6) (  3,  5) 
(  2,  4) (  2,  3) (  2,  7) (  4,  5) (  6,  7) (  4,  7) (  1,  7) 
(  3,  7) (  4,  6) (  5,  7) 


VERTICES =      7 EDGES =     17

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              24      74      85      45      11       1 
I =   1      24     136     207     116      21 
I =   2      86     253     212      49 
I =   3     143     268     132      15 
I =   4     159     215      66 
I =   5     140     144      24 
I =   6     104      82       6 
I =   7      66      39 
I =   8      35      15 
I =   9      15       5 
I =  10       5       1 
I =  11       1 
*/
          tutteMat[  0][  1] =      24; 
          tutteMat[  0][  2] =      74; 
          tutteMat[  0][  3] =      85; 
          tutteMat[  0][  4] =      45; 
          tutteMat[  0][  5] =      11; 
          tutteMat[  0][  6] =       1; 
          tutteMat[  1][  0] =      24; 
          tutteMat[  1][  1] =     136; 
          tutteMat[  1][  2] =     207; 
          tutteMat[  1][  3] =     116; 
          tutteMat[  1][  4] =      21; 
          tutteMat[  2][  0] =      86; 
          tutteMat[  2][  1] =     253; 
          tutteMat[  2][  2] =     212; 
          tutteMat[  2][  3] =      49; 
          tutteMat[  3][  0] =     143; 
          tutteMat[  3][  1] =     268; 
          tutteMat[  3][  2] =     132; 
          tutteMat[  3][  3] =      15; 
          tutteMat[  4][  0] =     159; 
          tutteMat[  4][  1] =     215; 
          tutteMat[  4][  2] =      66; 
          tutteMat[  5][  0] =     140; 
          tutteMat[  5][  1] =     144; 
          tutteMat[  5][  2] =      24; 
          tutteMat[  6][  0] =     104; 
          tutteMat[  6][  1] =      82; 
          tutteMat[  6][  2] =       6; 
          tutteMat[  7][  0] =      66; 
          tutteMat[  7][  1] =      39; 
          tutteMat[  8][  0] =      35; 
          tutteMat[  8][  1] =      15; 
          tutteMat[  9][  0] =      15; 
          tutteMat[  9][  1] =       5; 
          tutteMat[ 10][  0] =       5; 
          tutteMat[ 10][  1] =       1; 
          tutteMat[ 11][  0] =       1; 
       } 
       break;

     case 31210:/* degree */
       { /*  G1235 *//*printf("sprt22\n");*/
/*
W1027
*/

 /*

******************* reading edge list *************




(  3,  6) (  1,  5) (  1,  7) (  4,  6) (  2,  5) (  2,  6) (  4,  7) 
(  4,  5) (  3,  5) (  1,  6) (  5,  7) (  3,  4) (  2,  4) (  5,  6) 
(  2,  7) (  3,  7) (  6,  7) 


VERTICES =      7 EDGES =     17

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              36      96      97      47      11       1 
I =   1      36     186     238     115      19 
I =   2     126     318     219      45 
I =   3     207     312     123      10 
I =   4     228     230      54 
I =   5     199     141      15 
I =   6     147      69       2 
I =   7      92      26 
I =   8      48       7 
I =   9      20       1 
I =  10       6 
I =  11       1 
*/
         tutteMat[  0][  1] =      36; 
         tutteMat[  0][  2] =      96; 
         tutteMat[  0][  3] =      97; 
         tutteMat[  0][  4] =      47; 
         tutteMat[  0][  5] =      11; 
         tutteMat[  0][  6] =       1; 
         tutteMat[  1][  0] =      36; 
         tutteMat[  1][  1] =     186; 
         tutteMat[  1][  2] =     238; 
         tutteMat[  1][  3] =     115; 
         tutteMat[  1][  4] =      19; 
         tutteMat[  2][  0] =     126; 
         tutteMat[  2][  1] =     318; 
         tutteMat[  2][  2] =     219; 
         tutteMat[  2][  3] =      45; 
         tutteMat[  3][  0] =     207; 
         tutteMat[  3][  1] =     312; 
         tutteMat[  3][  2] =     123; 
         tutteMat[  3][  3] =      10; 
         tutteMat[  4][  0] =     228; 
         tutteMat[  4][  1] =     230; 
         tutteMat[  4][  2] =      54; 
         tutteMat[  5][  0] =     199; 
         tutteMat[  5][  1] =     141; 
         tutteMat[  5][  2] =      15; 
         tutteMat[  6][  0] =     147; 
         tutteMat[  6][  1] =      69; 
         tutteMat[  6][  2] =       2; 
         tutteMat[  7][  0] =      92; 
         tutteMat[  7][  1] =      26; 
         tutteMat[  8][  0] =      48; 
         tutteMat[  8][  1] =       7; 
         tutteMat[  9][  0] =      20; 
         tutteMat[  9][  1] =       1; 
         tutteMat[ 10][  0] =       6; 
         tutteMat[ 11][  0] =       1; 
      }  
      break;

    case 15010:
      {  /*  G1237 */ /*printf("sprt23\n");*/
/*
W1030
*/

/*

******************* reading edge list *************




(  2,  3) (  2,  7) (  2,  4) (  3,  5) (  1,  7) (  5,  7) (  4,  5) 
(  1,  5) (  3,  4) (  2,  5) (  4,  7) (  6,  7) (  2,  6) (  4,  6) 
(  3,  7) (  1,  6) (  3,  6) 


VERTICES =      7 EDGES =     17

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              42     107     103      48      11       1 
I =   1      42     214     258     116      18 
I =   2     149     358     221      40 
I =   3     245     335     115       9 
I =   4     268     233      45 
I =   5     230     131      12 
I =   6     165      59       2 
I =   7     100      20 
I =   8      50       5 
I =   9      20       1 
I =  10       6 
I =  11       1 
*/
         tutteMat[  0][  1] =      42; 
         tutteMat[  0][  2] =     107; 
         tutteMat[  0][  3] =     103; 
         tutteMat[  0][  4] =      48; 
         tutteMat[  0][  5] =      11; 
         tutteMat[  0][  6] =       1; 
         tutteMat[  1][  0] =      42; 
         tutteMat[  1][  1] =     214; 
         tutteMat[  1][  2] =     258; 
         tutteMat[  1][  3] =     116; 
         tutteMat[  1][  4] =      18; 
         tutteMat[  2][  0] =     149; 
         tutteMat[  2][  1] =     358; 
         tutteMat[  2][  2] =     221; 
         tutteMat[  2][  3] =      40; 
         tutteMat[  3][  0] =     245; 
         tutteMat[  3][  1] =     335; 
         tutteMat[  3][  2] =     115; 
         tutteMat[  3][  3] =       9; 
         tutteMat[  4][  0] =     268; 
         tutteMat[  4][  1] =     233; 
         tutteMat[  4][  2] =      45; 
         tutteMat[  5][  0] =     230; 
         tutteMat[  5][  1] =     131; 
         tutteMat[  5][  2] =      12; 
         tutteMat[  6][  0] =     165; 
         tutteMat[  6][  1] =      59; 
         tutteMat[  6][  2] =       2; 
         tutteMat[  7][  0] =     100; 
         tutteMat[  7][  1] =      20; 
         tutteMat[  8][  0] =      50; 
         tutteMat[  8][  1] =       5; 
         tutteMat[  9][  0] =      20; 
         tutteMat[  9][  1] =       1; 
         tutteMat[ 10][  0] =       6; 
         tutteMat[ 11][  0] =       1; 
 
      }   
      break;
default:
  {
     printf("sevenpart2dra\n");
  }
  break;
  }/* end 24001, 31210, 15010 switch */

} /* end sevenpart2dra */

