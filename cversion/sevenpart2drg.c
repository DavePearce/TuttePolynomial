#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart2drg           */
/*                                            */
 
/* 

Precondition: g is a seven vertex graph with 16 or 17 edges
              degseq is the degree sequence of g and has value
              4300 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte poly of this graph

*/ 

void
sevenpart2drg(
              struct graph *g,
              TUTTE tutteMat,
              TUTTEO tutteMatX
             )


{
int 
    vt,            /* location on vertex list */
    deg41,         /* location on vertex list of vertex of degree 4 */
    deg42,
    deg43;

printf("sevenpart2drg\n");

/*     case 4300:*/
          vt = firstVertex(g);  
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
                               
          deg43 = nextofdegree(
                               g,
                               &vt,
                               FOUR
                              );
          switch( isadj(deg41,deg42,g)
                       + isadj(deg41,deg43,g)
                              + isadj(deg42,deg43,g) )
            { 
               case TWO:
                 { /* G1232 */  /*printf("sprt225\n"); */    
/*
W1025
*/

/*

******************* reading edge list *************




(  1,  3) (  2,  3) (  2,  4) (  4,  7) (  1,  5) (  4,  6) (  5,  7) 
(  2,  7) (  3,  4) (  1,  6) (  4,  5) (  3,  5) (  5,  6) (  6,  7) 
(  2,  6) (  1,  7) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              38      95      90      42      10       1 
I =   1      38     187     214      90      13 
I =   2     130     294     162      24 
I =   3     205     249      65       3 
I =   4     211     145      17 
I =   5     165      63       2 
I =   6     104      19 
I =   7      53       3 
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
                   tutteMat[  1][  1] =     187; 
                   tutteMat[  1][  2] =     214; 
                   tutteMat[  1][  3] =      90; 
                   tutteMat[  1][  4] =      13; 
                   tutteMat[  2][  0] =     130; 
                   tutteMat[  2][  1] =     294; 
                   tutteMat[  2][  2] =     162; 
                   tutteMat[  2][  3] =      24; 
                   tutteMat[  3][  0] =     205; 
                   tutteMat[  3][  1] =     249; 
                   tutteMat[  3][  2] =      65; 
                   tutteMat[  3][  3] =       3; 
                   tutteMat[  4][  0] =     211; 
                   tutteMat[  4][  1] =     145; 
                   tutteMat[  4][  2] =      17; 
                   tutteMat[  5][  0] =     165; 
                   tutteMat[  5][  1] =      63; 
                   tutteMat[  5][  2] =       2; 
                   tutteMat[  6][  0] =     104; 
                   tutteMat[  6][  1] =      19; 
                   tutteMat[  7][  0] =      53; 
                   tutteMat[  7][  1] =       3; 
                   tutteMat[  8][  0] =      21; 
                   tutteMat[  9][  0] =       6; 
                   tutteMat[ 10][  0] =       1; 
                } /* end case 2 */
                 break;
              case ONE:
                { /* G1231 */ /* printf("sprt226\n");*/     
/*
W1023
*/

/*

******************* reading edge list *************




(  2,  5) (  5,  7) (  3,  6) (  2,  6) (  2,  3) (  1,  6) (  1,  4) 
(  3,  4) (  1,  5) (  1,  7) (  3,  7) (  4,  5) (  4,  7) (  5,  6) 
(  2,  7) (  4,  6) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              36      92      89      42      10       1 
I =   1      36     182     215      92      13 
I =   2     126     295     167      24 
I =   3     203     254      65       2 
I =   4     211     147      16 
I =   5     165      64       1 
I =   6     104      19 
I =   7      53       3 
I =   8      21 
I =   9       6 
I =  10       1 
*/
                   tutteMat[  0][  1] =      36; 
                   tutteMat[  0][  2] =      92; 
                   tutteMat[  0][  3] =      89; 
                   tutteMat[  0][  4] =      42; 
                   tutteMat[  0][  5] =      10; 
                   tutteMat[  0][  6] =       1; 
                   tutteMat[  1][  0] =      36; 
                   tutteMat[  1][  1] =     182; 
                   tutteMat[  1][  2] =     215; 
                   tutteMat[  1][  3] =      92; 
                   tutteMat[  1][  4] =      13; 
                   tutteMat[  2][  0] =     126; 
                   tutteMat[  2][  1] =     295; 
                   tutteMat[  2][  2] =     167; 
                   tutteMat[  2][  3] =      24; 
                   tutteMat[  3][  0] =     203; 
                   tutteMat[  3][  1] =     254; 
                   tutteMat[  3][  2] =      65; 
                   tutteMat[  3][  3] =       2; 
                   tutteMat[  4][  0] =     211; 
                   tutteMat[  4][  1] =     147; 
                   tutteMat[  4][  2] =      16; 
                   tutteMat[  5][  0] =     165; 
                   tutteMat[  5][  1] =      64; 
                   tutteMat[  5][  2] =       1; 
                   tutteMat[  6][  0] =     104; 
                   tutteMat[  6][  1] =      19; 
                   tutteMat[  7][  0] =      53; 
                   tutteMat[  7][  1] =       3; 
                   tutteMat[  8][  0] =      21; 
                   tutteMat[  9][  0] =       6; 
                   tutteMat[ 10][  0] =       1; 
                }  /* end case 1 */
                break;

              case ZERO:
                { /* G1233 */ /*printf("sprt227\n"); */
/*
W1024
*/

/*

******************* reading edge list *************




(  1,  5) (  1,  4) (  1,  6) (  4,  7) (  2,  7) (  2,  5) (  3,  5) 
(  2,  4) (  3,  4) (  5,  6) (  3,  6) (  3,  7) (  1,  7) (  4,  6) 
(  5,  7) (  2,  6) 


VERTICES =      7 EDGES =     16

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              39      98      93      43      10       1 
I =   1      39     191     219      91      12 
I =   2     132     300     168      24 
I =   3     208     256      64 
I =   4     213     147      15 
I =   5     165      65 
I =   6     104      19 
I =   7      53       3 
I =   8      21 
I =   9       6 
I =  10       1 
*/
                   tutteMat[  0][  1] =      39; 
                   tutteMat[  0][  2] =      98; 
                   tutteMat[  0][  3] =      93; 
                   tutteMat[  0][  4] =      43; 
                   tutteMat[  0][  5] =      10; 
                   tutteMat[  0][  6] =       1; 
                   tutteMat[  1][  0] =      39; 
                   tutteMat[  1][  1] =     191; 
                   tutteMat[  1][  2] =     219; 
                   tutteMat[  1][  3] =      91; 
                   tutteMat[  1][  4] =      12; 
                   tutteMat[  2][  0] =     132; 
                   tutteMat[  2][  1] =     300; 
                   tutteMat[  2][  2] =     168; 
                   tutteMat[  2][  3] =      24; 
                   tutteMat[  3][  0] =     208; 
                   tutteMat[  3][  1] =     256; 
                   tutteMat[  3][  2] =      64; 
                   tutteMat[  4][  0] =     213; 
                   tutteMat[  4][  1] =     147; 
                   tutteMat[  4][  2] =      15; 
                   tutteMat[  5][  0] =     165; 
                   tutteMat[  5][  1] =      65; 
                   tutteMat[  6][  0] =     104; 
                   tutteMat[  6][  1] =      19; 
                   tutteMat[  7][  0] =      53; 
                   tutteMat[  7][  1] =       3; 
                   tutteMat[  8][  0] =      21; 
                   tutteMat[  9][  0] =       6; 
                   tutteMat[ 10][  0] =       1; 
                }  /* end case 0 */
                break;
              default:
                {
                   printf("sevenpart2drg\n");
                   break;
                }
            }/* end isadj switch */ 


}  /* end sevenpart2drg */


/*                                            */
/*           end of sevenpart2drg                */
/*                                            */
/**********************************************/


