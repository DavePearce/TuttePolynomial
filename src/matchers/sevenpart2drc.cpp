#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart2              */
/*                                            */
 

 
/* 

Precondition: g is a seven vertex graph with 16 or 17 edges
              degseq is the degree sequence of g and has value
              22300, 14200, or 22201 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte poly of this graph

*/ 



void
sevenpart2drc(struct Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX)

{
int vt,            /* location of vertex on vertex list             */
    deg41,         /* location on vertex list of vertex of degree 4 */
    deg42,
    deg51,         /* location on vertex list of vertex of degree 5 */
    deg52;

printf("sevenpart2drc\n");

switch( degseq )
  { 


     case 22300:/* see if degree 5 vertices are adjacent */
       { 
          vt = firstVertex(g);  
          deg51 = nextofdegree(
                               g,
                               &vt,
                               FIVE
                              );
          deg52 = nextofdegree(
                               g,
                               &vt,
                               FIVE
                              );
          if( isadj(deg51,deg52,g) )
            { /* G1239 *//* printf("sprt27\n");*/
/*
W1031
*/

/*

******************* reading edge list *************




(  5,  7) (  4,  6) (  2,  5) (  2,  7) (  1,  6) (  2,  3) (  4,  7) 
(  3,  7) (  3,  6) (  5,  6) (  1,  7) (  4,  5) (  1,  5) (  2,  6) 
(  3,  4) (  1,  4) (  6,  7) 


VERTICES =      7 EDGES =     17

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              42     107     103      48      11       1 
I =   1      42     216     261     117      18 
I =   2     151     367     226      40 
I =   3     253     347     114       8 
I =   4     281     238      43 
I =   5     243     131      10 
I =   6     175      56       1 
I =   7     106      17 
I =   8      53       3 
I =   9      21 
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
               tutteMat[  1][  1] =     216; 
               tutteMat[  1][  2] =     261; 
               tutteMat[  1][  3] =     117; 
               tutteMat[  1][  4] =      18; 
               tutteMat[  2][  0] =     151; 
               tutteMat[  2][  1] =     367; 
               tutteMat[  2][  2] =     226; 
               tutteMat[  2][  3] =      40; 
               tutteMat[  3][  0] =     253; 
               tutteMat[  3][  1] =     347; 
               tutteMat[  3][  2] =     114; 
               tutteMat[  3][  3] =       8; 
               tutteMat[  4][  0] =     281; 
               tutteMat[  4][  1] =     238; 
               tutteMat[  4][  2] =      43; 
               tutteMat[  5][  0] =     243; 
               tutteMat[  5][  1] =     131; 
               tutteMat[  5][  2] =      10; 
               tutteMat[  6][  0] =     175; 
               tutteMat[  6][  1] =      56; 
               tutteMat[  6][  2] =       1; 
               tutteMat[  7][  0] =     106; 
               tutteMat[  7][  1] =      17; 
               tutteMat[  8][  0] =      53; 
               tutteMat[  8][  1] =       3; 
               tutteMat[  9][  0] =      21; 
               tutteMat[ 10][  0] =       6; 
               tutteMat[ 11][  0] =       1; 
            } 
          else
            { /*  G1240 */  /* printf("sprt28\n");*/ 
/*
W1032
*/

/*

******************* reading edge list *************




(  2,  4) (  1,  4) (  1,  6) (  4,  7) (  3,  6) (  2,  6) (  2,  7) 
(  3,  7) (  6,  7) (  3,  5) (  1,  5) (  2,  5) (  3,  4) (  5,  7) 
(  5,  6) (  1,  7) (  4,  6) 


VERTICES =      7 EDGES =     17

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              46     115     108      49      11       1 
I =   1      46     229     267     115      17 
I =   2     160     375     225      40 
I =   3     261     348     113       6 
I =   4     284     238      42 
I =   5     243     133       9 
I =   6     175      57 
I =   7     106      17 
I =   8      53       3 
I =   9      21 
I =  10       6 
I =  11       1 
*/
               tutteMat[  0][  1] =      46; 
               tutteMat[  0][  2] =     115; 
               tutteMat[  0][  3] =     108; 
               tutteMat[  0][  4] =      49; 
               tutteMat[  0][  5] =      11; 
               tutteMat[  0][  6] =       1; 
               tutteMat[  1][  0] =      46; 
               tutteMat[  1][  1] =     229; 
               tutteMat[  1][  2] =     267; 
               tutteMat[  1][  3] =     115; 
               tutteMat[  1][  4] =      17; 
               tutteMat[  2][  0] =     160; 
               tutteMat[  2][  1] =     375; 
               tutteMat[  2][  2] =     225; 
               tutteMat[  2][  3] =      40; 
               tutteMat[  3][  0] =     261; 
               tutteMat[  3][  1] =     348; 
               tutteMat[  3][  2] =     113; 
               tutteMat[  3][  3] =       6; 
               tutteMat[  4][  0] =     284; 
               tutteMat[  4][  1] =     238; 
               tutteMat[  4][  2] =      42; 
               tutteMat[  5][  0] =     243; 
               tutteMat[  5][  1] =     133; 
               tutteMat[  5][  2] =       9; 
               tutteMat[  6][  0] =     175; 
               tutteMat[  6][  1] =      57; 
               tutteMat[  7][  0] =     106; 
               tutteMat[  7][  1] =      17; 
               tutteMat[  8][  0] =      53; 
               tutteMat[  8][  1] =       3; 
               tutteMat[  9][  0] =      21; 
               tutteMat[ 10][  0] =       6; 
               tutteMat[ 11][  0] =       1; 
            } 
       } 
       break;

     case 14200:/* see if degree 4 vertices are adjacent */
       { 
          vt= firstVertex(g);  
          deg41 = nextofdegree(
                               g,
                               &vt,
                               FOUR
                              );
          deg42 = nextofdegree(
                               g,
                               &vt,
                               FOUR
                              );
          if( isadj(deg41,deg42,g) )
            {/* G1242 */ /* printf("sprt29\n"); */   
/*
W1034
*/

/*

******************* reading edge list *************




(  1,  7) (  4,  6) (  3,  4) (  2,  3) (  1,  6) (  1,  5) (  5,  7) 
(  2,  4) (  4,  7) (  3,  5) (  6,  7) (  2,  7) (  1,  2) (  5,  6) 
(  4,  5) (  3,  7) (  3,  6) 


VERTICES =      7 EDGES =     17

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              48     118     109      49      11       1 
I =   1      48     240     275     116      17 
I =   2     170     394     225      37 
I =   3     280     359     108       7 
I =   4     306     238      38 
I =   5     261     125       8 
I =   6     185      50       1 
I =   7     110      14 
I =   8      54       2 
I =   9      21 
I =  10       6 
I =  11       1 
*/
               tutteMat[  0][  1] =      48; 
               tutteMat[  0][  2] =     118; 
               tutteMat[  0][  3] =     109; 
               tutteMat[  0][  4] =      49; 
               tutteMat[  0][  5] =      11; 
               tutteMat[  0][  6] =       1; 
               tutteMat[  1][  0] =      48; 
               tutteMat[  1][  1] =     240; 
               tutteMat[  1][  2] =     275; 
               tutteMat[  1][  3] =     116; 
               tutteMat[  1][  4] =      17; 
               tutteMat[  2][  0] =     170; 
               tutteMat[  2][  1] =     394; 
               tutteMat[  2][  2] =     225; 
               tutteMat[  2][  3] =      37; 
               tutteMat[  3][  0] =     280; 
               tutteMat[  3][  1] =     359; 
               tutteMat[  3][  2] =     108; 
               tutteMat[  3][  3] =       7; 
               tutteMat[  4][  0] =     306; 
               tutteMat[  4][  1] =     238; 
               tutteMat[  4][  2] =      38; 
               tutteMat[  5][  0] =     261; 
               tutteMat[  5][  1] =     125; 
               tutteMat[  5][  2] =       8; 
               tutteMat[  6][  0] =     185; 
               tutteMat[  6][  1] =      50; 
               tutteMat[  6][  2] =       1; 
               tutteMat[  7][  0] =     110; 
               tutteMat[  7][  1] =      14; 
               tutteMat[  8][  0] =      54; 
               tutteMat[  8][  1] =       2; 
               tutteMat[  9][  0] =      21; 
               tutteMat[ 10][  0] =       6; 
               tutteMat[ 11][  0] =       1; 
            } 
          else
            { /*  G1241 */   /*printf("sprt210\n");*/  
/*
W1033
*/

/*

******************* reading edge list *************




(  1,  4) (  1,  7) (  2,  3) (  2,  7) (  2,  6) (  4,  5) (  3,  7) 
(  1,  5) (  4,  6) (  3,  4) (  6,  7) (  1,  6) (  2,  5) (  4,  7) 
(  3,  6) (  5,  7) (  3,  5) 


VERTICES =      7 EDGES =     17

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              46     115     108      49      11       1 
I =   1      46     234     275     118      17 
I =   2     165     393     231      37 
I =   3     276     365     109       6 
I =   4     305     242      37 
I =   5     261     127       7 
I =   6     185      51 
I =   7     110      14 
I =   8      54       2 
I =   9      21 
I =  10       6 
I =  11       1 
*/
               tutteMat[  0][  1] =      46; 
               tutteMat[  0][  2] =     115; 
               tutteMat[  0][  3] =     108; 
               tutteMat[  0][  4] =      49; 
               tutteMat[  0][  5] =      11; 
               tutteMat[  0][  6] =       1; 
               tutteMat[  1][  0] =      46; 
               tutteMat[  1][  1] =     234; 
               tutteMat[  1][  2] =     275; 
               tutteMat[  1][  3] =     118; 
               tutteMat[  1][  4] =      17; 
               tutteMat[  2][  0] =     165; 
               tutteMat[  2][  1] =     393; 
               tutteMat[  2][  2] =     231; 
               tutteMat[  2][  3] =      37; 
               tutteMat[  3][  0] =     276; 
               tutteMat[  3][  1] =     365; 
               tutteMat[  3][  2] =     109; 
               tutteMat[  3][  3] =       6; 
               tutteMat[  4][  0] =     305; 
               tutteMat[  4][  1] =     242; 
               tutteMat[  4][  2] =      37; 
               tutteMat[  5][  0] =     261; 
               tutteMat[  5][  1] =     127; 
               tutteMat[  5][  2] =       7; 
               tutteMat[  6][  0] =     185; 
               tutteMat[  6][  1] =      51; 
               tutteMat[  7][  0] =     110; 
               tutteMat[  7][  1] =      14; 
               tutteMat[  8][  0] =      54; 
               tutteMat[  8][  1] =       2; 
               tutteMat[  9][  0] =      21; 
               tutteMat[ 10][  0] =       6; 
               tutteMat[ 11][  0] =       1; 
            } 
      }
      break;

    case 22201:/* degree */
      { /* G1214 *//* printf("sprt211\n");*/ 
/*
W1007
*/

/*

******************* reading edge list *************




(  1,  7) (  3,  5) (  4,  6) (  2,  7) (  2,  6) (  3,  4) (  3,  7) 
(  2,  5) (  2,  4) (  1,  6) (  5,  6) (  4,  5) (  3,  6) (  6,  7) 
(  5,  7) (  4,  7) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              18      57      68      38      10       1 
I =   1      18     100     154      89      17 
I =   2      61     178     152      37 
I =   3      96     181      90       9 
I =   4     101     138      41 
I =   5      84      86      12 
I =   6      58      43       2 
I =   7      33      17 
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
         tutteMat[  1][  1] =     100; 
         tutteMat[  1][  2] =     154; 
         tutteMat[  1][  3] =      89; 
         tutteMat[  1][  4] =      17; 
         tutteMat[  2][  0] =      61; 
         tutteMat[  2][  1] =     178; 
         tutteMat[  2][  2] =     152; 
         tutteMat[  2][  3] =      37; 
         tutteMat[  3][  0] =      96; 
         tutteMat[  3][  1] =     181; 
         tutteMat[  3][  2] =      90; 
         tutteMat[  3][  3] =       9; 
         tutteMat[  4][  0] =     101; 
         tutteMat[  4][  1] =     138; 
         tutteMat[  4][  2] =      41; 
         tutteMat[  5][  0] =      84; 
         tutteMat[  5][  1] =      86; 
         tutteMat[  5][  2] =      12; 
         tutteMat[  6][  0] =      58; 
         tutteMat[  6][  1] =      43; 
         tutteMat[  6][  2] =       2; 
         tutteMat[  7][  0] =      33; 
         tutteMat[  7][  1] =      17; 
         tutteMat[  8][  0] =      15; 
         tutteMat[  8][  1] =       5; 
         tutteMat[  9][  0] =       5; 
         tutteMat[  9][  1] =       1; 
         tutteMat[ 10][  0] =       1; 
      } 
      break;
default:
{
printf("sevenpart2drc\n");
}
break;

  } /* end degseq switch */

}/* end sevenpart2drc */


/*                                            */
/*           end of sevenpart2drc             */
/*                                            */
/**********************************************/


