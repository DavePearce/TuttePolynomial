#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart2drh           */
/*                                            */
 
/*

Precondition: g is a seven vertex graph with 16 edges
              degseq is the degree sequence of g and has value
              12400 
              tutteMat and tutteMatX are arrays with
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte poly of this graph

*/

void
sevenpart2drh(
              struct graph *g,
              TUTTE tutteMat,
              TUTTEO tutteMatX
             )


{

int 
    vt,           /* location on vertex list                        */
    deg51,        /* location on vertex list of vertex of degree 5  */
    deg52;

printf("sevenpart2drh\n");

/*     case 12400:*//* are vertices of degree 5 adjacent? if so, case on
              number of common adjacencies for the two vertices 
              of degree 5 */


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
          if(isadj(deg51,deg52,g))
            {
               switch(commonadj(g,deg51,deg52))
                 {
                    case THREE:
                      { /* G1228 */   /*printf("sprt228\n");*/
/*
W1020
*/

/*

******************* reading edge list *************




(  1,  4) (  2,  7) (  4,  5) (  1,  7) (  2,  5) (  1,  6) (  3,  6) 
(  2,  3) (  4,  7) (  6,  7) (  5,  7) (  1,  5) (  3,  7) (  2,  6) 
(  5,  6) (  3,  4) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              34      87      85      41      10       1 
I =   1      34     170     202      90      14 
I =   2     117     273     161      27 
I =   3     186     239      71       4 
I =   4     194     147      21 
I =   5     155      68       3 
I =   6     100      22 
I =   7      52       4 
I =   8      21 
I =   9       6 
I =  10       1 
*/
                         tutteMat[  0][  1] =      34; 
                         tutteMat[  0][  2] =      87; 
                         tutteMat[  0][  3] =      85; 
                         tutteMat[  0][  4] =      41; 
                         tutteMat[  0][  5] =      10; 
                         tutteMat[  0][  6] =       1; 
                         tutteMat[  1][  0] =      34; 
                         tutteMat[  1][  1] =     170; 
                         tutteMat[  1][  2] =     202; 
                         tutteMat[  1][  3] =      90; 
                         tutteMat[  1][  4] =      14; 
                         tutteMat[  2][  0] =     117; 
                         tutteMat[  2][  1] =     273; 
                         tutteMat[  2][  2] =     161; 
                         tutteMat[  2][  3] =      27; 
                         tutteMat[  3][  0] =     186; 
                         tutteMat[  3][  1] =     239; 
                         tutteMat[  3][  2] =      71; 
                         tutteMat[  3][  3] =       4; 
                         tutteMat[  4][  0] =     194; 
                         tutteMat[  4][  1] =     147; 
                         tutteMat[  4][  2] =      21; 
                         tutteMat[  5][  0] =     155; 
                         tutteMat[  5][  1] =      68; 
                         tutteMat[  5][  2] =       3; 
                         tutteMat[  6][  0] =     100; 
                         tutteMat[  6][  1] =      22; 
                         tutteMat[  7][  0] =      52; 
                         tutteMat[  7][  1] =       4; 
                         tutteMat[  8][  0] =      21; 
                         tutteMat[  9][  0] =       6; 
                         tutteMat[ 10][  0] =       1; 
                      }  /* end case 3 */
                       break;
      
                    case FOUR:
                      { /* G1229 */    /*printf("sprt229\n"); */    
/*
W1022
*/

/*

******************* reading edge list *************




(  1,  6) (  3,  7) (  2,  4) (  1,  7) (  1,  5) (  1,  4) (  2,  6) 
(  4,  7) (  5,  6) (  3,  4) (  3,  6) (  2,  5) (  3,  5) (  6,  7) 
(  5,  7) (  2,  7) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              38      95      90      42      10       1 
I =   1      38     183     207      87      13 
I =   2     126     279     156      27 
I =   3     193     236      70       3 
I =   4     196     145      21 
I =   5     155      68       3 
I =   6     100      22 
I =   7      52       4 
I =   8      21 
I =   9       6 
I =  10       1 
*/
                         tutteMat[  0][  1] =      38; 
                         tutteMat[  0][  2] =      95; 
                         tutteMat[  0][  3] =      90; 
                         tutteMat[  0][  4] =      42; 
                         tutteMat[  0][  5] =      10; 
                         tutteMat[  0][  6] =       1; 
                         tutteMat[  1][  0] =      38; 
                         tutteMat[  1][  1] =     183; 
                         tutteMat[  1][  2] =     207; 
                         tutteMat[  1][  3] =      87; 
                         tutteMat[  1][  4] =      13; 
                         tutteMat[  2][  0] =     126; 
                         tutteMat[  2][  1] =     279; 
                         tutteMat[  2][  2] =     156; 
                         tutteMat[  2][  3] =      27; 
                         tutteMat[  3][  0] =     193; 
                         tutteMat[  3][  1] =     236; 
                         tutteMat[  3][  2] =      70; 
                         tutteMat[  3][  3] =       3; 
                         tutteMat[  4][  0] =     196; 
                         tutteMat[  4][  1] =     145; 
                         tutteMat[  4][  2] =      21; 
                         tutteMat[  5][  0] =     155; 
                         tutteMat[  5][  1] =      68; 
                         tutteMat[  5][  2] =       3; 
                         tutteMat[  6][  0] =     100; 
                         tutteMat[  6][  1] =      22; 
                         tutteMat[  7][  0] =      52; 
                         tutteMat[  7][  1] =       4; 
                         tutteMat[  8][  0] =      21; 
                         tutteMat[  9][  0] =       6; 
                         tutteMat[ 10][  0] =       1; 
                      } /* end case 4 */
                     break;
                 }  /* end common switch */
           }        /* end true range */ 
         else
           { /* G1230 */  /*printf("sprt230\n");*/
/*
W1018
*/

/*

******************* reading edge list *************




(  1,  6) (  2,  6) (  1,  7) (  1,  5) (  3,  6) (  4,  5) (  2,  7) 
(  1,  4) (  2,  5) (  2,  3) (  5,  7) (  4,  6) (  4,  7) (  6,  7) 
(  3,  7) (  3,  5) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              32      84      84      41      10       1 
I =   1      32     164     202      92      14 
I =   2     112     271     165      26 
I =   3     181     243      72       4 
I =   4     192     151      20 
I =   5     155      69       2 
I =   6     100      22 
I =   7      52       4 
I =   8      21 
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
              tutteMat[  1][  1] =     164; 
              tutteMat[  1][  2] =     202; 
              tutteMat[  1][  3] =      92; 
              tutteMat[  1][  4] =      14; 
              tutteMat[  2][  0] =     112; 
              tutteMat[  2][  1] =     271; 
              tutteMat[  2][  2] =     165; 
              tutteMat[  2][  3] =      26; 
              tutteMat[  3][  0] =     181; 
              tutteMat[  3][  1] =     243; 
              tutteMat[  3][  2] =      72; 
              tutteMat[  3][  3] =       4; 
              tutteMat[  4][  0] =     192; 
              tutteMat[  4][  1] =     151; 
              tutteMat[  4][  2] =      20; 
              tutteMat[  5][  0] =     155; 
              tutteMat[  5][  1] =      69; 
              tutteMat[  5][  2] =       2; 
              tutteMat[  6][  0] =     100; 
              tutteMat[  6][  1] =      22; 
              tutteMat[  7][  0] =      52; 
              tutteMat[  7][  1] =       4; 
              tutteMat[  8][  0] =      21; 
              tutteMat[  9][  0] =       6; 
              tutteMat[ 10][  0] =       1; 
           }  /* end else */


}  /* end sevenpart2drh */


/*                                            */
/*           end of sevenpart2drh             */
/*                                            */
/**********************************************/


