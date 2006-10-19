#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart13             */
/*                                            */
 
/*

Precondition: g is a simple graph with seven vertices and 18 edges
              degseq is 24100, 32200, or 40300 
              tutteMat and tutteMatX are arrays with values
              for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte
               poly of this graph

*/
 
void
sevenpart13(
            struct graph *g,
            int degseq,
            TUTTE tutteMat,
            TUTTEO tutteMatX
           )
{

printf("sevenpart13\n");

switch( degseq )
  {  


    case 24100:/* degree */
      { /* G1247 */  /*printf("spt1g\n");*/
/*
W1039
*/

/*
(  1,  6) (  3,  5) (  3,  7) (  1,  7) (  3,  4) (  5,  6) (  2,  3) 
(  6,  7) (  2,  5) (  1,  4) (  1,  5) (  3,  6) (  2,  7) (  2,  4) 
(  4,  6) (  2,  6) (  4,  7) (  5,  7) 


VERTICES =      7 EDGES =     18

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              60     146     132      57      12       1 
I =   1      60     308     356     149      21 
I =   2     222     533     312      51 
I =   3     385     518     162      11 
I =   4     445     370      65 
I =   5     404     217      17 
I =   6     310     103       2 
I =   7     205      37 
I =   8     116       9 
I =   9      55       1 
I =  10      21 
I =  11       6 
I =  12       1 
*/
         tutteMat[  0][  1] =      60; 
         tutteMat[  0][  2] =     146; 
         tutteMat[  0][  3] =     132; 
         tutteMat[  0][  4] =      57; 
         tutteMat[  0][  5] =      12; 
         tutteMat[  0][  6] =       1; 
         tutteMat[  1][  0] =      60; 
         tutteMat[  1][  1] =     308; 
         tutteMat[  1][  2] =     356; 
         tutteMat[  1][  3] =     149; 
         tutteMat[  1][  4] =      21; 
         tutteMat[  2][  0] =     222; 
         tutteMat[  2][  1] =     533; 
         tutteMat[  2][  2] =     312; 
         tutteMat[  2][  3] =      51; 
         tutteMat[  3][  0] =     385; 
         tutteMat[  3][  1] =     518; 
         tutteMat[  3][  2] =     162; 
         tutteMat[  3][  3] =      11; 
         tutteMat[  4][  0] =     445; 
         tutteMat[  4][  1] =     370; 
         tutteMat[  4][  2] =      65; 
         tutteMat[  5][  0] =     404; 
         tutteMat[  5][  1] =     217; 
         tutteMat[  5][  2] =      17; 
         tutteMat[  6][  0] =     310; 
         tutteMat[  6][  1] =     103; 
         tutteMat[  6][  2] =       2; 
         tutteMat[  7][  0] =     205; 
         tutteMat[  7][  1] =      37; 
         tutteMat[  8][  0] =     116; 
         tutteMat[  8][  1] =       9; 
         tutteMat[  9][  0] =      55; 
         tutteMat[  9][  1] =       1; 
         tutteMat[ 10][  0] =      21; 
         tutteMat[ 11][  0] =       6; 
         tutteMat[ 12][  0] =       1; 

  
      }
      break;

    case 32200:/* degree */
      { /* G1246 */  /*printf("spt1h\n");*/
/*
W1038
*/

/*
(  4,  7) (  2,  7) (  2,  3) (  2,  6) (  1,  5) (  3,  5) (  1,  6) 
(  4,  5) (  3,  7) (  1,  7) (  3,  4) (  5,  6) (  2,  5) (  3,  6) 
(  1,  4) (  6,  7) (  5,  7) (  4,  6) 


VERTICES =      7 EDGES =     18

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              54     135     126      56      12       1 
I =   1      54     282     339     149      22 
I =   2     201     498     309      54 
I =   3     351     496     168      13 
I =   4     409     365      72 
I =   5     375     222      21 
I =   6     291     111       3 
I =   7     195      43 
I =   8     112      12 
I =   9      54       2 
I =  10      21 
I =  11       6 
I =  12       1 
*/
         tutteMat[  0][  1] =      54; 
         tutteMat[  0][  2] =     135; 
         tutteMat[  0][  3] =     126; 
         tutteMat[  0][  4] =      56; 
         tutteMat[  0][  5] =      12; 
         tutteMat[  0][  6] =       1; 
         tutteMat[  1][  0] =      54; 
         tutteMat[  1][  1] =     282; 
         tutteMat[  1][  2] =     339; 
         tutteMat[  1][  3] =     149; 
         tutteMat[  1][  4] =      22; 
         tutteMat[  2][  0] =     201; 
         tutteMat[  2][  1] =     498; 
         tutteMat[  2][  2] =     309; 
         tutteMat[  2][  3] =      54; 
         tutteMat[  3][  0] =     351; 
         tutteMat[  3][  1] =     496; 
         tutteMat[  3][  2] =     168; 
         tutteMat[  3][  3] =      13; 
         tutteMat[  4][  0] =     409; 
         tutteMat[  4][  1] =     365; 
         tutteMat[  4][  2] =      72; 
         tutteMat[  5][  0] =     375; 
         tutteMat[  5][  1] =     222; 
         tutteMat[  5][  2] =      21; 
         tutteMat[  6][  0] =     291; 
         tutteMat[  6][  1] =     111; 
         tutteMat[  6][  2] =       3; 
         tutteMat[  7][  0] =     195; 
         tutteMat[  7][  1] =      43; 
         tutteMat[  8][  0] =     112; 
         tutteMat[  8][  1] =      12; 
         tutteMat[  9][  0] =      54; 
         tutteMat[  9][  1] =       2; 
         tutteMat[ 10][  0] =      21; 
         tutteMat[ 11][  0] =       6; 
         tutteMat[ 12][  0] =       1; 

  
      }
      break;

    case 40300:/* degree */
      { /* G1245 */  /*printf("spt1i\n");*/
/*
W1036
*/


/*
(  4,  5) (  1,  4) (  2,  5) (  2,  4) (  1,  5) (  3,  5) (  2,  7) 
(  2,  6) (  5,  7) (  5,  6) (  3,  7) (  4,  7) (  4,  6) (  1,  7) 
(  6,  7) (  3,  4) (  1,  6) (  3,  6) 


VERTICES =      7 EDGES =     18

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              54     135     126      56      12       1 
I =   1      54     276     330     146      22 
I =   2     195     477     303      57 
I =   3     333     475     171      13 
I =   4     382     356      78 
I =   5     348     228      24 
I =   6     273     119       3 
I =   7     185      49 
I =   8     108      15 
I =   9      53       3 
I =  10      21 
I =  11       6 
I =  12       1 
*/
         tutteMat[  0][  1] =      54; 
         tutteMat[  0][  2] =     135; 
         tutteMat[  0][  3] =     126; 
         tutteMat[  0][  4] =      56; 
         tutteMat[  0][  5] =      12; 
         tutteMat[  0][  6] =       1; 
         tutteMat[  1][  0] =      54; 
         tutteMat[  1][  1] =     276; 
         tutteMat[  1][  2] =     330; 
         tutteMat[  1][  3] =     146; 
         tutteMat[  1][  4] =      22; 
         tutteMat[  2][  0] =     195; 
         tutteMat[  2][  1] =     477; 
         tutteMat[  2][  2] =     303; 
         tutteMat[  2][  3] =      57; 
         tutteMat[  3][  0] =     333; 
         tutteMat[  3][  1] =     475; 
         tutteMat[  3][  2] =     171; 
         tutteMat[  3][  3] =      13; 
         tutteMat[  4][  0] =     382; 
         tutteMat[  4][  1] =     356; 
         tutteMat[  4][  2] =      78; 
         tutteMat[  5][  0] =     348; 
         tutteMat[  5][  1] =     228; 
         tutteMat[  5][  2] =      24; 
         tutteMat[  6][  0] =     273; 
         tutteMat[  6][  1] =     119; 
         tutteMat[  6][  2] =       3; 
         tutteMat[  7][  0] =     185; 
         tutteMat[  7][  1] =      49; 
         tutteMat[  8][  0] =     108; 
         tutteMat[  8][  1] =      15; 
         tutteMat[  9][  0] =      53; 
         tutteMat[  9][  1] =       3; 
         tutteMat[ 10][  0] =      21; 
         tutteMat[ 11][  0] =       6; 
         tutteMat[ 12][  0] =       1; 
      }
      break;
default:
{
printf("sevenpart13\n");
break;
}

  } /* 1 end switch on degseq */

}  /* end sevenpart13 */

/*                                            */
/*           end of sevenpart13               */
/*                                            */
/**********************************************/





