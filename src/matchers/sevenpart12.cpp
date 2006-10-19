#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart12             */
/*                                            */
 
/*

Precondition: g is a simple graph with seven vertices and 18 or 19 edges
              degseq is 42100, 33010, or 16000
              tutteMat and tutteMatX are arrays with values
              for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte
               poly of this graph

*/
 

void
sevenpart12(struct Graph *g,int degseq,TUTTE tutteMat,TUTTEO tutteMatX)
{

printf("sevenpart12\n");

switch( degseq )
  {  


    case 42100:/* degree */ 
      {  /* G1249 */  /* printf("spt1d\n");*/
/*
W1041
*/

/*
(  2,  4) (  3,  6) (  4,  7) (  2,  3) (  3,  4) (  1,  6) (  2,  7) 
(  1,  5) (  1,  7) (  1,  4) (  4,  5) (  5,  6) (  4,  6) (  6,  7) 
(  3,  5) (  2,  5) (  5,  7) (  3,  7) (  2,  6) 


VERTICES =      7 EDGES =     19

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              72     174     155      65      13       1 
I =   1      72     378     442     186      26 
I =   2     276     683     412      69 
I =   3     498     701     234      19 
I =   4     602     538     108 
I =   5     576     348      36 
I =   6     472     191       7 
I =   7     340      85 
I =   8     215      29 
I =   9     118       7 
I =  10      55       1 
I =  11      21 
I =  12       6 
I =  13       1 
*/
          tutteMat[  0][  1] =      72; 
          tutteMat[  0][  2] =     174; 
          tutteMat[  0][  3] =     155; 
          tutteMat[  0][  4] =      65; 
          tutteMat[  0][  5] =      13; 
          tutteMat[  0][  6] =       1; 
          tutteMat[  1][  0] =      72; 
          tutteMat[  1][  1] =     378; 
          tutteMat[  1][  2] =     442; 
          tutteMat[  1][  3] =     186; 
          tutteMat[  1][  4] =      26; 
          tutteMat[  2][  0] =     276; 
          tutteMat[  2][  1] =     683; 
          tutteMat[  2][  2] =     412; 
          tutteMat[  2][  3] =      69; 
          tutteMat[  3][  0] =     498; 
          tutteMat[  3][  1] =     701; 
          tutteMat[  3][  2] =     234; 
          tutteMat[  3][  3] =      19; 
          tutteMat[  4][  0] =     602; 
          tutteMat[  4][  1] =     538; 
          tutteMat[  4][  2] =     108; 
          tutteMat[  5][  0] =     576; 
          tutteMat[  5][  1] =     348; 
          tutteMat[  5][  2] =      36; 
          tutteMat[  6][  0] =     472; 
          tutteMat[  6][  1] =     191; 
          tutteMat[  6][  2] =       7; 
          tutteMat[  7][  0] =     340; 
          tutteMat[  7][  1] =      85; 
          tutteMat[  8][  0] =     215; 
          tutteMat[  8][  1] =      29; 
          tutteMat[  9][  0] =     118; 
          tutteMat[  9][  1] =       7; 
          tutteMat[ 10][  0] =      55; 
          tutteMat[ 10][  1] =       1; 
          tutteMat[ 11][  0] =      21; 
          tutteMat[ 12][  0] =       6; 
          tutteMat[ 13][  0] =       1; 
      }   
      break; /* end g.e=44 */

    case 33010:/* degree */
      { /*  G1244 */  /*printf("spt1e\n");*/
/*
W1037
*/

/*

(  3,  4) (  2,  4) (  2,  3) (  1,  5) (  2,  5) (  3,  6) (  5,  7) 
(  2,  7) (  1,  7) (  4,  7) (  1,  6) (  4,  5) (  5,  6) (  4,  6) 
(  3,  5) (  6,  7) (  3,  7) (  2,  6) 


VERTICES =      7 EDGES =     18

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              48     124     120      55      12       1 
I =   1      48     254     319     148      23 
I =   2     178     454     301      57 
I =   3     309     461     174      16 
I =   4     359     352      81 
I =   5     330     225      27 
I =   6     258     121       6 
I =   7     175      53 
I =   8     102      18 
I =   9      50       5 
I =  10      20       1 
I =  11       6 
I =  12       1 
*/
         tutteMat[  0][  1] =      48; 
         tutteMat[  0][  2] =     124; 
         tutteMat[  0][  3] =     120; 
         tutteMat[  0][  4] =      55; 
         tutteMat[  0][  5] =      12; 
         tutteMat[  0][  6] =       1; 
         tutteMat[  1][  0] =      48; 
         tutteMat[  1][  1] =     254; 
         tutteMat[  1][  2] =     319; 
         tutteMat[  1][  3] =     148; 
         tutteMat[  1][  4] =      23; 
         tutteMat[  2][  0] =     178; 
         tutteMat[  2][  1] =     454; 
         tutteMat[  2][  2] =     301; 
         tutteMat[  2][  3] =      57; 
         tutteMat[  3][  0] =     309; 
         tutteMat[  3][  1] =     461; 
         tutteMat[  3][  2] =     174; 
         tutteMat[  3][  3] =      16; 
         tutteMat[  4][  0] =     359; 
         tutteMat[  4][  1] =     352; 
         tutteMat[  4][  2] =      81; 
         tutteMat[  5][  0] =     330; 
         tutteMat[  5][  1] =     225; 
         tutteMat[  5][  2] =      27; 
         tutteMat[  6][  0] =     258; 
         tutteMat[  6][  1] =     121; 
         tutteMat[  6][  2] =       6; 
         tutteMat[  7][  0] =     175; 
         tutteMat[  7][  1] =      53; 
         tutteMat[  8][  0] =     102; 
         tutteMat[  8][  1] =      18; 
         tutteMat[  9][  0] =      50; 
         tutteMat[  9][  1] =       5; 
         tutteMat[ 10][  0] =      20; 
         tutteMat[ 10][  1] =       1; 
         tutteMat[ 11][  0] =       6; 
         tutteMat[ 12][  0] =       1; 

 
      }
      break;

    case 16000:/* degree */
      {  /* G1248 */  /*printf("spt1f\n");*/
/*
W1040
*/

/*
(  1,  3) (  1,  4) (  2,  3) (  3,  5) (  1,  7) (  3,  7) (  2,  4) 
(  4,  6) (  2,  6) (  5,  7) (  1,  6) (  2,  7) (  4,  5) (  1,  5) 
(  4,  7) (  2,  5) (  3,  6) (  6,  7) 


VERTICES =      7 EDGES =     18

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              64     154     137      58      12       1 
I =   1      64     328     373     151      20 
I =   2     238     568     322      48 
I =   3     416     548     156       8 
I =   4     482     379      57 
I =   5     435     213      12 
I =   6     330      95 
I =   7     215      31 
I =   8     120       6 
I =   9      56 
I =  10      21 
I =  11       6 
I =  12       1 
*/
         tutteMat[  0][  1] =      64; 
         tutteMat[  0][  2] =     154; 
         tutteMat[  0][  3] =     137; 
         tutteMat[  0][  4] =      58; 
         tutteMat[  0][  5] =      12; 
         tutteMat[  0][  6] =       1; 
         tutteMat[  1][  0] =      64; 
         tutteMat[  1][  1] =     328; 
         tutteMat[  1][  2] =     373; 
         tutteMat[  1][  3] =     151; 
         tutteMat[  1][  4] =      20; 
         tutteMat[  2][  0] =     238; 
         tutteMat[  2][  1] =     568; 
         tutteMat[  2][  2] =     322; 
         tutteMat[  2][  3] =      48; 
         tutteMat[  3][  0] =     416; 
         tutteMat[  3][  1] =     548; 
         tutteMat[  3][  2] =     156; 
         tutteMat[  3][  3] =       8; 
         tutteMat[  4][  0] =     482; 
         tutteMat[  4][  1] =     379; 
         tutteMat[  4][  2] =      57; 
         tutteMat[  5][  0] =     435; 
         tutteMat[  5][  1] =     213; 
         tutteMat[  5][  2] =      12; 
         tutteMat[  6][  0] =     330; 
         tutteMat[  6][  1] =      95; 
         tutteMat[  7][  0] =     215; 
         tutteMat[  7][  1] =      31; 
         tutteMat[  8][  0] =     120; 
         tutteMat[  8][  1] =       6; 
         tutteMat[  9][  0] =      56; 
         tutteMat[ 10][  0] =      21; 
         tutteMat[ 11][  0] =       6; 
         tutteMat[ 12][  0] =       1; 
 
 
      }
      break;

default:
{
printf("sevenpart12\n");
break;
}

  } /* 1 end switch on degseq */

}  /* end sevenpart12 */

/*                                            */
/*           end of sevenpart12               */
/*                                            */
/**********************************************/





