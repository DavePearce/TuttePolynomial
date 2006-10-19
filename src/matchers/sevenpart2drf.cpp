#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart2drf           */
/*                                            */
 

/* 

Precondition: g is a seven vertex graph with 16 or 17 edges
              degseq is the degree sequence of g and has value
              30220, 13210, or 20500 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte poly of this graph

*/ 


void
sevenpart2drf(struct Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX)

{
int vt,            /* location on vertex list */
    deg41,         /* location on vertex list of vertex of degree 4 */
    deg42;

printf("sevenpart2drf\n");

switch( degseq )
  { 


case 30220:/* degree */
 { /* G1217 */  /*printf("sprt220\n");*/
/*
W1006
*/

/*

******************* reading edge list *************




(  2,  5) (  3,  7) (  3,  4) (  1,  6) (  2,  6) (  2,  7) (  4,  5) 
(  3,  5) (  6,  7) (  1,  5) (  4,  6) (  3,  6) (  5,  7) (  5,  6) 
(  4,  7) (  1,  7) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              24      68      74      39      10       1 
I =   1      24     122     165      87      16 
I =   2      78     201     153      36 
I =   3     120     196      87       7 
I =   4     126     143      36 
I =   5     105      84       9 
I =   6      73      38       1 
I =   7      42      12 
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
tutteMat[  1][  1] =     122; 
tutteMat[  1][  2] =     165; 
tutteMat[  1][  3] =      87; 
tutteMat[  1][  4] =      16; 
tutteMat[  2][  0] =      78; 
tutteMat[  2][  1] =     201; 
tutteMat[  2][  2] =     153; 
tutteMat[  2][  3] =      36; 
tutteMat[  3][  0] =     120; 
tutteMat[  3][  1] =     196; 
tutteMat[  3][  2] =      87; 
tutteMat[  3][  3] =       7; 
tutteMat[  4][  0] =     126; 
tutteMat[  4][  1] =     143; 
tutteMat[  4][  2] =      36; 
tutteMat[  5][  0] =     105; 
tutteMat[  5][  1] =      84; 
tutteMat[  5][  2] =       9; 
tutteMat[  6][  0] =      73; 
tutteMat[  6][  1] =      38; 
tutteMat[  6][  2] =       1; 
tutteMat[  7][  0] =      42; 
tutteMat[  7][  1] =      12; 
tutteMat[  8][  0] =      19; 
tutteMat[  8][  1] =       2; 
tutteMat[  9][  0] =       6; 
tutteMat[ 10][  0] =       1; 

 
 } 
break;

case 13210:/* are vertices of degree 4 adjacent?
              if not, then determine the number of
              common adjacencies for the vertices
              of degree 4 */
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
   { /* G1222 */    /* printf("sprt221\n");*/ 
/*
W1014
*/

/*

******************* reading edge list *************




(  1,  5) (  2,  7) (  2,  6) (  2,  3) (  2,  4) (  4,  5) (  3,  4) 
(  1,  6) (  5,  6) (  3,  5) (  4,  7) (  4,  6) (  1,  7) (  3,  7) 
(  5,  7) (  6,  7) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              28      76      79      40      10       1 
I =   1      28     146     188      91      15 
I =   2      98     246     162      30 
I =   3     159     227      77       5 
I =   4     169     147      26 
I =   5     137      74       5 
I =   6      90      28 
I =   7      48       7 
I =   8      20       1 
I =   9       6 
I =  10       1 
*/
tutteMat[  0][  1] =      28; 
tutteMat[  0][  2] =      76; 
tutteMat[  0][  3] =      79; 
tutteMat[  0][  4] =      40; 
tutteMat[  0][  5] =      10; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      28; 
tutteMat[  1][  1] =     146; 
tutteMat[  1][  2] =     188; 
tutteMat[  1][  3] =      91; 
tutteMat[  1][  4] =      15; 
tutteMat[  2][  0] =      98; 
tutteMat[  2][  1] =     246; 
tutteMat[  2][  2] =     162; 
tutteMat[  2][  3] =      30; 
tutteMat[  3][  0] =     159; 
tutteMat[  3][  1] =     227; 
tutteMat[  3][  2] =      77; 
tutteMat[  3][  3] =       5; 
tutteMat[  4][  0] =     169; 
tutteMat[  4][  1] =     147; 
tutteMat[  4][  2] =      26; 
tutteMat[  5][  0] =     137; 
tutteMat[  5][  1] =      74; 
tutteMat[  5][  2] =       5; 
tutteMat[  6][  0] =      90;  
tutteMat[  6][  1] =      28;  
tutteMat[  7][  0] =      48;  
tutteMat[  7][  1] =       7;  
tutteMat[  8][  0] =      20;  
tutteMat[  8][  1] =       1; 
tutteMat[  9][  0] =       6;  
tutteMat[ 10][  0] =       1; 

    
   } 
  else
   {
    switch( commonadj(g,deg41,deg42) )
     {
      case THREE:
       { /* G1223 */ /* printf("sprt222\n");*/ 
/*
W1017
*/

/*

******************* reading edge list *************




(  1,  6) (  1,  7) (  1,  3) (  3,  7) (  2,  6) (  2,  7) (  4,  6) 
(  6,  7) (  4,  5) (  3,  4) (  4,  7) (  5,  6) (  5,  7) (  2,  5) 
(  3,  5) (  2,  4) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              30      79      80      40      10       1 
I =   1      30     152     188      89      15 
I =   2     103     247     156      30 
I =   3     163     221      76       6 
I =   4     170     143      27 
I =   5     137      72       6 
I =   6      90      27       1 
I =   7      48       7 
I =   8      20       1 
I =   9       6 
I =  10       1 
*/
tutteMat[  0][  1] =      30; 
tutteMat[  0][  2] =      79; 
tutteMat[  0][  3] =      80; 
tutteMat[  0][  4] =      40; 
tutteMat[  0][  5] =      10; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      30; 
tutteMat[  1][  1] =     152; 
tutteMat[  1][  2] =     188; 
tutteMat[  1][  3] =      89; 
tutteMat[  1][  4] =      15; 
tutteMat[  2][  0] =     103; 
tutteMat[  2][  1] =     247; 
tutteMat[  2][  2] =     156; 
tutteMat[  2][  3] =      30; 
tutteMat[  3][  0] =     163; 
tutteMat[  3][  1] =     221; 
tutteMat[  3][  2] =      76; 
tutteMat[  3][  3] =       6; 
tutteMat[  4][  0] =     170; 
tutteMat[  4][  1] =     143; 
tutteMat[  4][  2] =      27; 
tutteMat[  5][  0] =     137; 
tutteMat[  5][  1] =      72; 
tutteMat[  5][  2] =       6; 
tutteMat[  6][  0] =      90; 
tutteMat[  6][  1] =      27; 
tutteMat[  6][  2] =       1; 
tutteMat[  7][  0] =      48; 
tutteMat[  7][  1] =       7; 
tutteMat[  8][  0] =      20; 
tutteMat[  8][  1] =       1; 
tutteMat[  9][  0] =       6; 
tutteMat[ 10][  0] =       1; 

       
       }
      break;
      case FOUR: 
       { /* g1224 */ /*  printf("sprt223\n"); */     
/*
W1015
*/

/*


******************* reading edge list *************




(  2,  7) (  2,  5) (  1,  6) (  2,  4) (  1,  5) (  1,  7) (  3,  5) 
(  5,  7) (  2,  6) (  6,  7) (  4,  6) (  3,  6) (  3,  4) (  4,  7) 
(  4,  5) (  3,  7) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              32      84      84      41      10       1 
I =   1      32     159     194      89      14 
I =   2     107     253     159      29 
I =   3     166     226      76       4 
I =   4     171     147      25 
I =   5     137      75       4 
I =   6      90      28 
I =   7      48       7 
I =   8      20       1 
I =   9       6 
I =  10       1 
*/
tutteMat[  0][  1] =      32; 
tutteMat[  0][  2] =      84; 
tutteMat[  0][  3] =      84; 
tutteMat[  0][  4] =      41; 
tutteMat[  0][  5] =      10; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      32; 
tutteMat[  1][  1] =     159; 
tutteMat[  1][  2] =     194; 
tutteMat[  1][  3] =      89; 
tutteMat[  1][  4] =      14; 
tutteMat[  2][  0] =     107; 
tutteMat[  2][  1] =     253; 
tutteMat[  2][  2] =     159; 
tutteMat[  2][  3] =      29; 
tutteMat[  3][  0] =     166; 
tutteMat[  3][  1] =     226; 
tutteMat[  3][  2] =      76; 
tutteMat[  3][  3] =       4; 
tutteMat[  4][  0] =     171; 
tutteMat[  4][  1] =     147; 
tutteMat[  4][  2] =      25; 
tutteMat[  5][  0] =     137; 
tutteMat[  5][  1] =      75; 
tutteMat[  5][  2] =       4; 
tutteMat[  6][  0] =      90; 
tutteMat[  6][  1] =      28; 
tutteMat[  7][  0] =      48; 
tutteMat[  7][  1] =       7; 
tutteMat[  8][  0] =      20; 
tutteMat[  8][  1] =       1; 
tutteMat[  9][  0] =       6; 
tutteMat[ 10][  0] =       1; 

       
       }
      break;
     } 
   }
 } 
break;

case 20500:/* degree */
 { /* G1227 *//* printf("sprt224\n");*/
/*
W1016
*/

/*

******************* reading edge list *************




(  1,  4) (  1,  7) (  2,  7) (  2,  3) (  3,  4) (  1,  5) (  4,  7) 
(  1,  6) (  2,  5) (  3,  6) (  2,  6) (  4,  6) (  5,  7) (  5,  6) 
(  6,  7) (  3,  7) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              30      79      80      40      10       1 
I =   1      30     154     191      90      15 
I =   2     105     255     160      30 
I =   3     170     230      75       5 
I =   4     180     145      25 
I =   5     145      72       5 
I =   6      96      25 
I =   7      51       5 
I =   8      21 
I =   9       6 
I =  10       1 
*/
tutteMat[  0][  1] =      30; 
tutteMat[  0][  2] =      79; 
tutteMat[  0][  3] =      80; 
tutteMat[  0][  4] =      40; 
tutteMat[  0][  5] =      10; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      30; 
tutteMat[  1][  1] =     154; 
tutteMat[  1][  2] =     191; 
tutteMat[  1][  3] =      90; 
tutteMat[  1][  4] =      15; 
tutteMat[  2][  0] =     105; 
tutteMat[  2][  1] =     255; 
tutteMat[  2][  2] =     160; 
tutteMat[  2][  3] =      30; 
tutteMat[  3][  0] =     170; 
tutteMat[  3][  1] =     230; 
tutteMat[  3][  2] =      75; 
tutteMat[  3][  3] =       5; 
tutteMat[  4][  0] =     180; 
tutteMat[  4][  1] =     145; 
tutteMat[  4][  2] =      25; 
tutteMat[  5][  0] =     145; 
tutteMat[  5][  1] =      72; 
tutteMat[  5][  2] =       5; 
tutteMat[  6][  0] =      96; 
tutteMat[  6][  1] =      25; 
tutteMat[  7][  0] =      51; 
tutteMat[  7][  1] =       5; 
tutteMat[  8][  0] =      21; 
tutteMat[  9][  0] =       6; 
tutteMat[ 10][  0] =       1; 

  
 } 
break;

default:
{
printf("sevenpart2drf\n");
}
break;

}/* end switch on degseq */

}  /* end sevenpart2drf */


/*                                            */
/*           end of sevenpart2drf             */
/*                                            */
/**********************************************/


