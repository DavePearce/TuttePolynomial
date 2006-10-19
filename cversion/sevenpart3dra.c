#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3dra           */
/*                                            */
 
 
/* 

Precondition: g is a simple seven vertex graph with 14 or 15 edges 
              degseq is one of 30040, 21130, and 13030
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3dra(
              struct graph *g,
              int degseq,
              TUTTE tutteMat,
              TUTTEO tutteMatX
             )



{

//printf("sevenpart3dra.c\n"); 


switch( degseq )
  {  /* 1 */

     case 30040:/* degree */
       { 
/* G1184 */ /*printf("spt31\n");*/  
/*
W0966
*/
/*printf("30040\n");*/
/*

******************* reading edge list *************




(  2,  5) (  1,  6) (  3,  5) (  1,  7) (  2,  6) (  4,  6) (  3,  6) 
(  1,  5) (  4,  5) (  6,  7) (  5,  6) (  3,  7) (  4,  7) (  5,  7) 
(  2,  7) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              16      48      56      32       9       1 
I =   1      16      77     108      62      13 
I =   2      45     117     102      30 
I =   3      62     115      60       4 
I =   4      61      83      24 
I =   5      48      48       6 
I =   6      32      20 
I =   7      17       4 
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
tutteMat[  1][  1] =      77; 
tutteMat[  1][  2] =     108; 
tutteMat[  1][  3] =      62; 
tutteMat[  1][  4] =      13; 
tutteMat[  2][  0] =      45; 
tutteMat[  2][  1] =     117; 
tutteMat[  2][  2] =     102; 
tutteMat[  2][  3] =      30; 
tutteMat[  3][  0] =      62; 
tutteMat[  3][  1] =     115; 
tutteMat[  3][  2] =      60; 
tutteMat[  3][  3] =       4; 
tutteMat[  4][  0] =      61; 
tutteMat[  4][  1] =      83; 
tutteMat[  4][  2] =      24; 
tutteMat[  5][  0] =      48; 
tutteMat[  5][  1] =      48; 
tutteMat[  5][  2] =       6; 
tutteMat[  6][  0] =      32; 
tutteMat[  6][  1] =      20; 
tutteMat[  7][  0] =      17; 
tutteMat[  7][  1] =       4; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

 } 
break;

case 21130:/* degree */
 { /* G1185 *//* printf("spt32\n");*/
/*
W0969
*//*printf("21130\n");*/

/*

******************* reading edge list *************




(  2,  5) (  1,  7) (  4,  6) (  2,  6) (  3,  7) (  2,  7) (  5,  7) 
(  4,  7) (  1,  5) (  4,  5) (  3,  4) (  6,  7) (  5,  6) (  1,  6) 
(  3,  6) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              16      48      56      32       9       1 
I =   1      16      83     118      66      13 
I =   2      51     135     106      26 
I =   3      76     126      56       4 
I =   4      76      85      20 
I =   5      59      44       4 
I =   6      37      16 
I =   7      18       3 
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
tutteMat[  1][  1] =      83; 
tutteMat[  1][  2] =     118; 
tutteMat[  1][  3] =      66; 
tutteMat[  1][  4] =      13; 
tutteMat[  2][  0] =      51; 
tutteMat[  2][  1] =     135; 
tutteMat[  2][  2] =     106; 
tutteMat[  2][  3] =      26; 
tutteMat[  3][  0] =      76; 
tutteMat[  3][  1] =     126; 
tutteMat[  3][  2] =      56; 
tutteMat[  3][  3] =       4; 
tutteMat[  4][  0] =      76; 
tutteMat[  4][  1] =      85; 
tutteMat[  4][  2] =      20; 
tutteMat[  5][  0] =      59; 
tutteMat[  5][  1] =      44; 
tutteMat[  5][  2] =       4; 
tutteMat[  6][  0] =      37; 
tutteMat[  6][  1] =      16; 
tutteMat[  7][  0] =      18; 
tutteMat[  7][  1] =       3; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

  
 } 
break;

case 13030:/* degree */
 { /* G1186 *//*printf("spt33\n");*/
/*
W0972
*//*printf("13030\n");*/
/*

******************* reading edge list *************




(  4,  7) (  4,  6) (  2,  6) (  2,  4) (  1,  5) (  1,  6) (  3,  7) 
(  5,  7) (  5,  6) (  3,  5) (  2,  7) (  1,  7) (  3,  4) (  6,  7) 
(  4,  5) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              16      48      56      32       9       1 
I =   1      16      86     123      68      13 
I =   2      54     144     108      24 
I =   3      83     131      54       4 
I =   4      83      85      18 
I =   5      63      42       3 
I =   6      38      15 
I =   7      18       3 
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
tutteMat[  1][  1] =      86; 
tutteMat[  1][  2] =     123; 
tutteMat[  1][  3] =      68; 
tutteMat[  1][  4] =      13; 
tutteMat[  2][  0] =      54; 
tutteMat[  2][  1] =     144; 
tutteMat[  2][  2] =     108; 
tutteMat[  2][  3] =      24; 
tutteMat[  3][  0] =      83; 
tutteMat[  3][  1] =     131; 
tutteMat[  3][  2] =      54; 
tutteMat[  3][  3] =       4; 
tutteMat[  4][  0] =      83; 
tutteMat[  4][  1] =      85; 
tutteMat[  4][  2] =      18; 
tutteMat[  5][  0] =      63; 
tutteMat[  5][  1] =      42; 
tutteMat[  5][  2] =       3; 
tutteMat[  6][  0] =      38; 
tutteMat[  6][  1] =      15; 
tutteMat[  7][  0] =      18; 
tutteMat[  7][  1] =       3; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

 
 } 
break;

default:
  {
     printf("sevenpart3dra\n");
     break;
  }


} /*  end switch on degseq */


}  /* end sevenpart3dra */

/*                                            */
/*           end of sevenpart3dra             */
/*                                            */
/**********************************************/




