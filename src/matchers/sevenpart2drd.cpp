#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart2drd           */
/*                                            */
 
/* 

Precondition: g is a seven vertex graph with 16 or 17 edges
              degseq is the degree sequence of g and has value
              14101, 6001, or 14020 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte poly of this graph

*/ 



void
sevenpart2drd(struct Graph *g, int degseq, TUTTE tutteMat, TUTTEO tutteMatX)

{

printf("sevenpart2drd\n");

switch( degseq )
  { 


     case 14101:/* degree */
       { /* G1215 */ /* printf("sprt212\n");*/
/*
W1009
*/
/*

******************* reading edge list *************




(  1,  7) (  2,  4) (  2,  3) (  3,  5) (  1,  6) (  2,  7) (  3,  4) 
(  2,  5) (  5,  7) (  4,  5) (  5,  6) (  4,  6) (  4,  7) (  3,  6) 
(  6,  7) (  3,  7) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              18      57      68      38      10       1 
I =   1      18     102     157      90      17 
I =   2      63     185     154      36 
I =   3     102     187      88       9 
I =   4     109     138      39 
I =   5      90      83      12 
I =   6      61      41       2 
I =   7      34      16 
I =   8      15       5 
I =   9       5       1 
I =  10       1 
*/
          tutteMat[  0][  1] =      18; 
          tutteMat[  0][  2] =      57; 
          tutteMat[  0][  3] =      68; 
          tutteMat[  0][  4] =      38; 
          tutteMat[  0][  5] =      10; 
          tutteMat[  0][  6] =       1; 
          tutteMat[  1][  0] =      18; 
          tutteMat[  1][  1] =     102; 
          tutteMat[  1][  2] =     157; 
          tutteMat[  1][  3] =      90; 
          tutteMat[  1][  4] =      17; 
          tutteMat[  2][  0] =      63; 
          tutteMat[  2][  1] =     185; 
          tutteMat[  2][  2] =     154; 
          tutteMat[  2][  3] =      36; 
          tutteMat[  3][  0] =     102; 
          tutteMat[  3][  1] =     187; 
          tutteMat[  3][  2] =      88; 
          tutteMat[  3][  3] =       9; 
          tutteMat[  4][  0] =     109; 
          tutteMat[  4][  1] =     138; 
          tutteMat[  4][  2] =      39; 
          tutteMat[  5][  0] =      90; 
          tutteMat[  5][  1] =      83; 
          tutteMat[  5][  2] =      12; 
          tutteMat[  6][  0] =      61; 
          tutteMat[  6][  1] =      41; 
          tutteMat[  6][  2] =       2; 
          tutteMat[  7][  0] =      34; 
          tutteMat[  7][  1] =      16; 
          tutteMat[  8][  0] =      15; 
          tutteMat[  8][  1] =       5; 
          tutteMat[  9][  0] =       5; 
          tutteMat[  9][  1] =       1; 
          tutteMat[ 10][  0] =       1; 
       }  
       break;

     case 6001:/* degree */
       { /* G1216 */  /*printf("sprt213\n");*/
/*
W1012
*/

/*

******************* reading edge list *************




(  3,  4) (  2,  4) (  1,  6) (  2,  7) (  3,  5) (  3,  7) (  2,  3) 
(  1,  7) (  5,  7) (  4,  5) (  2,  5) (  4,  6) (  4,  7) (  5,  6) 
(  2,  6) (  3,  6) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              24      68      74      39      10       1 
I =   1      24     124     168      88      16 
I =   2      80     202     147      33 
I =   3     120     186      85       9 
I =   4     120     136      36 
I =   5      96      80      12 
I =   6      64      39       2 
I =   7      35      15 
I =   8      15       5 
I =   9       5       1 
I =  10       1 
*/
          tutteMat[  0][  1] =      24; 
          tutteMat[  0][  2] =      68; 
          tutteMat[  0][  3] =      74; 
          tutteMat[  0][  4] =      39; 
          tutteMat[  0][  5] =      10; 
          tutteMat[  0][  6] =       1; 
          tutteMat[  1][  0] =      24; 
          tutteMat[  1][  1] =     124; 
          tutteMat[  1][  2] =     168; 
          tutteMat[  1][  3] =      88; 
          tutteMat[  1][  4] =      16; 
          tutteMat[  2][  0] =      80; 
          tutteMat[  2][  1] =     202; 
          tutteMat[  2][  2] =     147; 
          tutteMat[  2][  3] =      33; 
          tutteMat[  3][  0] =     120; 
          tutteMat[  3][  1] =     186; 
          tutteMat[  3][  2] =      85; 
          tutteMat[  3][  3] =       9; 
          tutteMat[  4][  0] =     120; 
          tutteMat[  4][  1] =     136; 
          tutteMat[  4][  2] =      36; 
          tutteMat[  5][  0] =      96; 
          tutteMat[  5][  1] =      80; 
          tutteMat[  5][  2] =      12; 
          tutteMat[  6][  0] =      64; 
          tutteMat[  6][  1] =      39; 
          tutteMat[  6][  2] =       2; 
          tutteMat[  7][  0] =      35; 
          tutteMat[  7][  1] =      15; 
          tutteMat[  8][  0] =      15; 
          tutteMat[  8][  1] =       5; 
          tutteMat[  9][  0] =       5; 
          tutteMat[  9][  1] =       1; 
          tutteMat[ 10][  0] =       1; 
       } 
       break;

     case 14020:/* degree */
       { /* G1219 */  /* printf("sprt214\n");*/
/*
W1013
*/


/*


******************* reading edge list *************




(  2,  4) (  4,  6) (  1,  6) (  3,  6) (  4,  7) (  1,  7) (  3,  4) 
(  2,  3) (  5,  7) (  5,  6) (  4,  5) (  2,  7) (  1,  5) (  3,  7) 
(  3,  5) (  6,  7) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              24      68      74      39      10       1 
I =   1      24     128     174      90      16 
I =   2      84     221     158      33 
I =   3     137     211      81       7 
I =   4     147     143      32 
I =   5     121      77       8 
I =   6      81      32       1 
I =   7      44      10 
I =   8      19       2 
I =   9       6 
I =  10       1 
*/
          tutteMat[  0][  1] =      24; 
          tutteMat[  0][  2] =      68; 
          tutteMat[  0][  3] =      74; 
          tutteMat[  0][  4] =      39; 
          tutteMat[  0][  5] =      10; 
          tutteMat[  0][  6] =       1; 
          tutteMat[  1][  0] =      24; 
          tutteMat[  1][  1] =     128; 
          tutteMat[  1][  2] =     174; 
          tutteMat[  1][  3] =      90; 
          tutteMat[  1][  4] =      16; 
          tutteMat[  2][  0] =      84; 
          tutteMat[  2][  1] =     221; 
          tutteMat[  2][  2] =     158; 
          tutteMat[  2][  3] =      33; 
          tutteMat[  3][  0] =     137; 
          tutteMat[  3][  1] =     211; 
          tutteMat[  3][  2] =      81; 
          tutteMat[  3][  3] =       7; 
          tutteMat[  4][  0] =     147; 
          tutteMat[  4][  1] =     143; 
          tutteMat[  4][  2] =      32; 
          tutteMat[  5][  0] =     121; 
          tutteMat[  5][  1] =      77; 
          tutteMat[  5][  2] =       8; 
          tutteMat[  6][  0] =      81; 
          tutteMat[  6][  1] =      32; 
          tutteMat[  6][  2] =       1; 
          tutteMat[  7][  0] =      44; 
          tutteMat[  7][  1] =      10; 
          tutteMat[  8][  0] =      19; 
          tutteMat[  8][  1] =       2; 
          tutteMat[  9][  0] =       6; 
          tutteMat[ 10][  0] =       1; 
       } 
       break;

default:
{
printf("sevenpart2drd\n");
}
break;

  }/* end switch on degseq */


}  /* end sevenpart2drd */


/*                                            */
/*           end of sevenpart2drd             */
/*                                            */
/**********************************************/


