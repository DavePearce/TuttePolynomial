#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart2dre           */
/*                                            */
 
/* 

Precondition: g is a seven vertex graph with 16 or 17 edges
              degseq is the degree sequence of g and has value
              22120, 5110, or 21310 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte poly of this graph

*/ 


void
sevenpart2dre(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX)

{
int vt,           /* location of vertex on vertex list              */ 
    sum,          /* accumulator for degrees of a set of vertices   */
    deg3;         /* location on vertex list of vertex of degree 3  */

printf("sevenpart2dre\n");

switch( degseq )
  { 


case 22120:/* degree */
 { /* G1218 */ /*printf("sprt215\n");*/
/*
W1008
*/

/*

******************* reading edge list *************




(  2,  7) (  1,  6) (  3,  6) (  3,  4) (  5,  7) (  2,  6) (  3,  5) 
(  1,  5) (  2,  4) (  4,  6) (  3,  7) (  4,  7) (  5,  6) (  6,  7) 
(  1,  7) (  4,  5) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              24      68      74      39      10       1 
I =   1      24     126     171      89      16 
I =   2      82     213     155      34 
I =   3     130     203      84       7 
I =   4     137     143      34 
I =   5     113      81       8 
I =   6      77      35       1 
I =   7      43      11 
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
tutteMat[  1][  1] =     126; 
tutteMat[  1][  2] =     171; 
tutteMat[  1][  3] =      89; 
tutteMat[  1][  4] =      16; 
tutteMat[  2][  0] =      82; 
tutteMat[  2][  1] =     213; 
tutteMat[  2][  2] =     155; 
tutteMat[  2][  3] =      34; 
tutteMat[  3][  0] =     130; 
tutteMat[  3][  1] =     203; 
tutteMat[  3][  2] =      84; 
tutteMat[  3][  3] =       7; 
tutteMat[  4][  0] =     137; 
tutteMat[  4][  1] =     143; 
tutteMat[  4][  2] =      34; 
tutteMat[  5][  0] =     113; 
tutteMat[  5][  1] =      81; 
tutteMat[  5][  2] =       8; 
tutteMat[  6][  0] =      77; 
tutteMat[  6][  1] =      35; 
tutteMat[  6][  2] =       1; 
tutteMat[  7][  0] =      43; 
tutteMat[  7][  1] =      11; 
tutteMat[  8][  0] =      19; 
tutteMat[  8][  1] =       2; 
tutteMat[  9][  0] =       6; 
tutteMat[ 10][  0] =       1; 

  
 } 
break;

case 5110:/* cases based on the sum of the degrees of 
             the neighbors of the vertex of degree 3 */
 {
  vt = firstVertex(g);  
  deg3 = nextofdegree(
                      g,
                      &vt,
                      THREE
                     );
  sum = degreesofnhbrs(
                       g,
                       deg3
                      );
  switch( sum )
   {
    case 15:
     { /* G1225 *//*printf("sprt216\n");*/ 
 /*
W1019
*/
/*

******************* reading edge list *************




(  2,  4) (  3,  7) (  1,  7) (  1,  6) (  2,  6) (  3,  6) (  5,  7) 
(  3,  5) (  4,  7) (  1,  5) (  2,  3) (  4,  5) (  3,  4) (  4,  6) 
(  2,  7) (  5,  6) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              32      84      84      41      10       1 
I =   1      32     163     200      91      14 
I =   2     111     266     162      27 
I =   3     177     235      72       4 
I =   4     184     146      22 
I =   5     146      70       4 
I =   6      94      25 
I =   7      49       6 
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
tutteMat[  1][  1] =     163; 
tutteMat[  1][  2] =     200; 
tutteMat[  1][  3] =      91; 
tutteMat[  1][  4] =      14; 
tutteMat[  2][  0] =     111; 
tutteMat[  2][  1] =     266; 
tutteMat[  2][  2] =     162; 
tutteMat[  2][  3] =      27; 
tutteMat[  3][  0] =     177; 
tutteMat[  3][  1] =     235; 
tutteMat[  3][  2] =      72; 
tutteMat[  3][  3] =       4; 
tutteMat[  4][  0] =     184; 
tutteMat[  4][  1] =     146; 
tutteMat[  4][  2] =      22; 
tutteMat[  5][  0] =     146; 
tutteMat[  5][  1] =      70; 
tutteMat[  5][  2] =       4; 
tutteMat[  6][  0] =      94; 
tutteMat[  6][  1] =      25; 
tutteMat[  7][  0] =      49; 
tutteMat[  7][  1] =       6; 
tutteMat[  8][  0] =      20; 
tutteMat[  8][  1] =       1; 
tutteMat[  9][  0] =       6; 
tutteMat[ 10][  0] =       1; 

    
     } 
    break;
    case 14:
     { /* G1226 *//* printf("sprt217\n");*/  
/*
W1021
*/

/*

******************* reading edge list *************




(  3,  7) (  1,  7) (  3,  6) (  2,  5) (  2,  4) (  2,  3) (  5,  7) 
(  3,  5) (  1,  2) (  1,  6) (  4,  5) (  3,  4) (  4,  6) (  5,  6) 
(  4,  7) (  6,  7) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              36      90      86      41      10       1 
I =   1      36     174     199      87      14 
I =   2     120     266     151      27 
I =   3     183     224      71       6 
I =   4     185     140      24 
I =   5     146      67       6 
I =   6      94      24       1 
I =   7      49       6 
I =   8      20       1 
I =   9       6 
I =  10       1 
*/
tutteMat[  0][  1] =      36; 
tutteMat[  0][  2] =      90; 
tutteMat[  0][  3] =      86; 
tutteMat[  0][  4] =      41; 
tutteMat[  0][  5] =      10; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      36; 
tutteMat[  1][  1] =     174; 
tutteMat[  1][  2] =     199; 
tutteMat[  1][  3] =      87; 
tutteMat[  1][  4] =      14; 
tutteMat[  2][  0] =     120; 
tutteMat[  2][  1] =     266; 
tutteMat[  2][  2] =     151; 
tutteMat[  2][  3] =      27; 
tutteMat[  3][  0] =     183; 
tutteMat[  3][  1] =     224; 
tutteMat[  3][  2] =      71; 
tutteMat[  3][  3] =       6; 
tutteMat[  4][  0] =     185; 
tutteMat[  4][  1] =     140; 
tutteMat[  4][  2] =      24; 
tutteMat[  5][  0] =     146; 
tutteMat[  5][  1] =      67; 
tutteMat[  5][  2] =       6; 
tutteMat[  6][  0] =      94; 
tutteMat[  6][  1] =      24; 
tutteMat[  6][  2] =       1; 
tutteMat[  7][  0] =      49; 
tutteMat[  7][  1] =       6; 
tutteMat[  8][  0] =      20; 
tutteMat[  8][  1] =       1; 
tutteMat[  9][  0] =       6; 
tutteMat[ 10][  0] =       1; 

      
     } 
    break;
   } 
 }
break;

case 21310:/* cases on the sum of the degrees of the 
              neighbors of the vertex of degree 3 */
 { 
  vt = firstVertex(g); 
  deg3 = nextofdegree(
                      g,
                      &vt,
                      THREE
                     );
  sum = degreesofnhbrs(g,deg3);
  switch( sum )
   {
    case 17:
     { /* G1220 */  /* printf("sprt218\n"); */    
/*
W1011
*/
/*

******************* reading edge list *************




(  1,  5) (  2,  6) (  1,  6) (  1,  7) (  4,  6) (  2,  4) (  3,  7) 
(  3,  6) (  2,  5) (  5,  6) (  3,  5) (  3,  4) (  4,  7) (  2,  7) 
(  5,  7) (  6,  7) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              28      76      79      40      10       1 
I =   1      28     143     183      89      15 
I =   2      95     235     158      32 
I =   3     150     217      80       5 
I =   4     157     146      29 
I =   5     128      78       6 
I =   6      86      31 
I =   7      47       8 
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
tutteMat[  1][  1] =     143; 
tutteMat[  1][  2] =     183; 
tutteMat[  1][  3] =      89; 
tutteMat[  1][  4] =      15; 
tutteMat[  2][  0] =      95; 
tutteMat[  2][  1] =     235; 
tutteMat[  2][  2] =     158; 
tutteMat[  2][  3] =      32; 
tutteMat[  3][  0] =     150; 
tutteMat[  3][  1] =     217; 
tutteMat[  3][  2] =      80; 
tutteMat[  3][  3] =       5; 
tutteMat[  4][  0] =     157; 
tutteMat[  4][  1] =     146; 
tutteMat[  4][  2] =      29; 
tutteMat[  5][  0] =     128; 
tutteMat[  5][  1] =      78; 
tutteMat[  5][  2] =       6; 
tutteMat[  6][  0] =      86; 
tutteMat[  6][  1] =      31; 
tutteMat[  7][  0] =      47; 
tutteMat[  7][  1] =       8; 
tutteMat[  8][  0] =      20; 
tutteMat[  8][  1] =       1; 
tutteMat[  9][  0] =       6; 
tutteMat[ 10][  0] =       1; 

    
     } 
    break;
    case 16:
     { /* G1221 */  /*  printf("sprt219\n");*/    
/*
W1010
*/

/*

******************* reading edge list *************




(  1,  4) (  2,  3) (  2,  5) (  1,  6) (  2,  6) (  2,  7) (  1,  7) 
(  3,  6) (  3,  5) (  3,  7) (  5,  6) (  4,  6) (  4,  7) (  6,  7) 
(  5,  7) (  4,  5) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              24      68      74      39      10       1 
I =   1      24     130     177      91      16 
I =   2      86     227     159      32 
I =   3     142     216      81       7 
I =   4     154     146      30 
I =   5     128      76       7 
I =   6      86      30       1 
I =   7      47       8 
I =   8      20       1 
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
tutteMat[  1][  1] =     130; 
tutteMat[  1][  2] =     177; 
tutteMat[  1][  3] =      91; 
tutteMat[  1][  4] =      16; 
tutteMat[  2][  0] =      86; 
tutteMat[  2][  1] =     227; 
tutteMat[  2][  2] =     159; 
tutteMat[  2][  3] =      32; 
tutteMat[  3][  0] =     142; 
tutteMat[  3][  1] =     216; 
tutteMat[  3][  2] =      81; 
tutteMat[  3][  3] =       7; 
tutteMat[  4][  0] =     154; 
tutteMat[  4][  1] =     146; 
tutteMat[  4][  2] =      30; 
tutteMat[  5][  0] =     128; 
tutteMat[  5][  1] =      76; 
tutteMat[  5][  2] =       7; 
tutteMat[  6][  0] =      86; 
tutteMat[  6][  1] =      30; 
tutteMat[  6][  2] =       1; 
tutteMat[  7][  0] =      47; 
tutteMat[  7][  1] =       8; 
tutteMat[  8][  0] =      20; 
tutteMat[  8][  1] =       1; 
tutteMat[  9][  0] =       6; 
tutteMat[ 10][  0] =       1; 

    
     } 
    break;
   } 
 } 
break;


default:
{
printf("sevenpart2dre\n");
}
break;

}/* end switch on degseq */


} /* end sevenpart2dre */

/*                                            */
/*           end of sevenpart2dre             */
/*                                            */
/**********************************************/


