#include "core/tutte.h"

#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart2drb           */
/*                                            */
 
/* 

Precondition: g is a seven vertex graph with 16 or 17 edges
              degseq is the degree sequence of g and has value
              23110, 30400, or 6100 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte poly of this graph

*/ 


void
sevenpart2drb(struct Graph *g, int degseq, TUTTE tutteMat, TUTTEO tutteMatX)

{

printf("sevenpart2drb\n");

switch( degseq )
  { 


     case 23110:/* degree */
       {/*  G1236 */ /*printf("sprt24\n");*/
/*
W1029
*/
/*

******************* reading edge list *************




(  1,  7) (  4,  5) (  3,  5) (  2,  7) (  4,  7) (  5,  6) (  2,  6) 
(  2,  4) (  1,  6) (  5,  7) (  2,  3) (  4,  6) (  1,  5) (  6,  7) 
(  3,  7) (  3,  6) (  3,  4) 


VERTICES =      7 EDGES =     17

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              36      96      97      47      11       1 
I =   1      36     190     244     117      19 
I =   2     130     332     223      43 
I =   3     219     325     120      10 
I =   4     245     233      50 
I =   5     214     136      14 
I =   6     156      64       2 
I =   7      96      23 
I =   8      49       6 
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
          tutteMat[  1][  1] =     190; 
          tutteMat[  1][  2] =     244; 
          tutteMat[  1][  3] =     117; 
          tutteMat[  1][  4] =      19; 
          tutteMat[  2][  0] =     130; 
          tutteMat[  2][  1] =     332; 
          tutteMat[  2][  2] =     223; 
          tutteMat[  2][  3] =      43; 
          tutteMat[  3][  0] =     219; 
          tutteMat[  3][  1] =     325; 
          tutteMat[  3][  2] =     120; 
          tutteMat[  3][  3] =      10; 
          tutteMat[  4][  0] =     245; 
          tutteMat[  4][  1] =     233; 
          tutteMat[  4][  2] =      50; 
          tutteMat[  5][  0] =     214; 
          tutteMat[  5][  1] =     136; 
          tutteMat[  5][  2] =      14; 
          tutteMat[  6][  0] =     156; 
          tutteMat[  6][  1] =      64; 
          tutteMat[  6][  2] =       2; 
          tutteMat[  7][  0] =      96; 
          tutteMat[  7][  1] =      23; 
          tutteMat[  8][  0] =      49; 
          tutteMat[  8][  1] =       6; 
          tutteMat[  9][  0] =      20; 
          tutteMat[  9][  1] =       1; 
          tutteMat[ 10][  0] =       6; 
          tutteMat[ 11][  0] =       1; 
       }  
       break;

     case 30400:/* degree */
       { /*  G1238 */ /* printf("sprt25\n");*/
/*
W1028
*/

/*

******************* reading edge list *************




(  2,  6) (  2,  5) (  5,  6) (  2,  7) (  4,  5) (  1,  5) (  3,  7) 
(  1,  7) (  3,  6) (  4,  6) (  1,  4) (  3,  5) (  2,  3) (  1,  6) 
(  4,  7) (  5,  7) (  6,  7) 


VERTICES =      7 EDGES =     17

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              36      96      97      47      11       1 
I =   1      36     192     247     118      19 
I =   2     132     339     225      42 
I =   3     225     333     120      10 
I =   4     255     239      48 
I =   5     226     135      12 
I =   6     165      61       2 
I =   7     102      20 
I =   8      52       4 
I =   9      21 
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
          tutteMat[  1][  1] =     192; 
          tutteMat[  1][  2] =     247; 
          tutteMat[  1][  3] =     118; 
          tutteMat[  1][  4] =      19; 
          tutteMat[  2][  0] =     132; 
          tutteMat[  2][  1] =     339; 
          tutteMat[  2][  2] =     225; 
          tutteMat[  2][  3] =      42; 
          tutteMat[  3][  0] =     225; 
          tutteMat[  3][  1] =     333; 
          tutteMat[  3][  2] =     120; 
          tutteMat[  3][  3] =      10; 
          tutteMat[  4][  0] =     255; 
          tutteMat[  4][  1] =     239; 
          tutteMat[  4][  2] =      48; 
          tutteMat[  5][  0] =     226; 
          tutteMat[  5][  1] =     135; 
          tutteMat[  5][  2] =      12; 
          tutteMat[  6][  0] =     165; 
          tutteMat[  6][  1] =      61; 
          tutteMat[  6][  2] =       2; 
          tutteMat[  7][  0] =     102; 
          tutteMat[  7][  1] =      20; 
          tutteMat[  8][  0] =      52; 
          tutteMat[  8][  1] =       4; 
          tutteMat[  9][  0] =      21; 
          tutteMat[ 10][  0] =       6; 
          tutteMat[ 11][  0] =       1; 
       } 
       break;

     case 6100:/* degree */
       { /*  G1243 *//* printf("sprt26\n");*/
/*
W1035
*/

/*

******************* reading edge list *************




(  2,  3) (  1,  4) (  2,  7) (  2,  6) (  2,  4) (  3,  5) (  5,  7) 
(  5,  6) (  3,  4) (  4,  6) (  1,  5) (  2,  5) (  1,  7) (  1,  6) 
(  3,  6) (  3,  7) (  4,  7) 


VERTICES =      7 EDGES =     17

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              50     123     113      50      11       1 
I =   1      50     253     290     119      16 
I =   2     180     422     236      34 
I =   3     302     384     102       4 
I =   4     332     243      31 
I =   5     280     121       4 
I =   6     195      45 
I =   7     114      11 
I =   8      55       1 
I =   9      21 
I =  10       6 
I =  11       1 
*/
          tutteMat[  0][  1] =      50; 
          tutteMat[  0][  2] =     123; 
          tutteMat[  0][  3] =     113; 
          tutteMat[  0][  4] =      50; 
          tutteMat[  0][  5] =      11; 
          tutteMat[  0][  6] =       1; 
          tutteMat[  1][  0] =      50; 
          tutteMat[  1][  1] =     253; 
          tutteMat[  1][  2] =     290; 
          tutteMat[  1][  3] =     119; 
          tutteMat[  1][  4] =      16; 
          tutteMat[  2][  0] =     180; 
          tutteMat[  2][  1] =     422; 
          tutteMat[  2][  2] =     236; 
          tutteMat[  2][  3] =      34; 
          tutteMat[  3][  0] =     302; 
          tutteMat[  3][  1] =     384; 
          tutteMat[  3][  2] =     102; 
          tutteMat[  3][  3] =       4; 
          tutteMat[  4][  0] =     332; 
          tutteMat[  4][  1] =     243; 
          tutteMat[  4][  2] =      31; 
          tutteMat[  5][  0] =     280; 
          tutteMat[  5][  1] =     121; 
          tutteMat[  5][  2] =       4; 
          tutteMat[  6][  0] =     195; 
          tutteMat[  6][  1] =      45; 
          tutteMat[  7][  0] =     114; 
          tutteMat[  7][  1] =      11; 
          tutteMat[  8][  0] =      55; 
          tutteMat[  8][  1] =       1; 
          tutteMat[  9][  0] =      21; 
          tutteMat[ 10][  0] =       6; 
          tutteMat[ 11][  0] =       1; 
        } 
       break;

default:
{
printf("sevenpart2drb\n");
}
break;

  } /* 1 end switch on degseq */


}  /* end sevenpart2drb */


/*                                            */
/*           end of sevenpart2drb             */
/*                                            */
/**********************************************/


