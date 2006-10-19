#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3drc2          */
/*                                            */

 
/* 

Precondition: g is a simple seven vertex graph with 15 edges 
              degseq is 2500 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3drc2(
               struct graph *g,
               int degseq,
               TUTTE tutteMat,
               TUTTEO tutteMatX
              )


{
int d31,            /* location on vertex list of vertices of degree 3  */
    d32, 
    d51,            /* location on vertex list of vertex of degree 5     */
    d52,
    vt;             /* location on vertex list                           */

//printf("sevenpart3drc2\n");

switch( degseq )
{  /* 1 */


case 2500:
{/*printf("2500 1001\n");*/
 vt = firstVertex(g);  
  d51 = nextofdegree(
                     g,
                     &vt,
                     FIVE 
                    );
  d52 = nextofdegree(
                     g,
                     &vt,
                     FIVE 
                    );
 if( ! isadj(d51,d52,g) )
  { /* G1212 */ /*printf("spt316\n");*/
/*
W1001
*/
/*
w1001

******************* reading edge list *************




(  1,  5) (  3,  4) (  3,  7) (  1,  4) (  1,  7) (  5,  6) (  2,  6) 
(  1,  6) (  2,  3) (  5,  7) (  2,  7) (  4,  7) (  4,  6) (  3,  6) 
(  2,  5) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              26      69      70      35       9       1 
I =   1      26     133     161      70      10 
I =   2      90     210     115      15 
I =   3     140     165      35 
I =   4     135      80       5 
I =   5      94      27 
I =   6      51       5 
I =   7      21 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      26; 
tutteMat[  0][  2] =      69; 
tutteMat[  0][  3] =      70; 
tutteMat[  0][  4] =      35; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      26; 
tutteMat[  1][  1] =     133; 
tutteMat[  1][  2] =     161; 
tutteMat[  1][  3] =      70; 
tutteMat[  1][  4] =      10; 
tutteMat[  2][  0] =      90; 
tutteMat[  2][  1] =     210; 
tutteMat[  2][  2] =     115; 
tutteMat[  2][  3] =      15; 
tutteMat[  3][  0] =     140; 
tutteMat[  3][  1] =     165; 
tutteMat[  3][  2] =      35; 
tutteMat[  4][  0] =     135; 
tutteMat[  4][  1] =      80; 
tutteMat[  4][  2] =       5; 
tutteMat[  5][  0] =      94; 
tutteMat[  5][  1] =      27; 
tutteMat[  6][  0] =      51; 
tutteMat[  6][  1] =       5; 
tutteMat[  7][  0] =      21; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

   
  }
 else
  { /* else 1 */
   deletevrtx(
              g,
              d51
             );
   deletevrtx(
              g,
              d52
            ) ;
   if( nodegn(g,THREE) == ZERO )
    { /* G1211 *//*printf("spt317\n");*/
/*
W1002
*/
/*
w1002

******************* reading edge list *************




(  1,  6) (  1,  7) (  1,  5) (  2,  3) (  2,  5) (  1,  4) (  4,  5) 
(  2,  7) (  3,  5) (  4,  7) (  3,  6) (  3,  7) (  6,  7) (  2,  6) 
(  4,  6) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              28      72      71      35       9       1 
I =   1      28     136     158      68      10 
I =   2      92     205     111      14 
I =   3     138     161      36       2 
I =   4     133      81       6 
I =   5      94      27 
I =   6      51       5 
I =   7      21 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      28; 
tutteMat[  0][  2] =      72; 
tutteMat[  0][  3] =      71; 
tutteMat[  0][  4] =      35; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      28; 
tutteMat[  1][  1] =     136; 
tutteMat[  1][  2] =     158; 
tutteMat[  1][  3] =      68; 
tutteMat[  1][  4] =      10; 
tutteMat[  2][  0] =      92; 
tutteMat[  2][  1] =     205; 
tutteMat[  2][  2] =     111; 
tutteMat[  2][  3] =      14; 
tutteMat[  3][  0] =     138; 
tutteMat[  3][  1] =     161; 
tutteMat[  3][  2] =      36; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =     133; 
tutteMat[  4][  1] =      81; 
tutteMat[  4][  2] =       6; 
tutteMat[  5][  0] =      94; 
tutteMat[  5][  1] =      27; 
tutteMat[  6][  0] =      51; 
tutteMat[  6][  1] =       5; 
tutteMat[  7][  0] =      21; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

     
    } 
   else
    { /* else 2 */
     vt = firstVertex(g); 
     d31 = nextofdegree(
                        g,
                        &vt,
                        THREE 
                       );
     d32 = nextofdegree(
                        g,
                        &vt,
                        THREE 
                       );
     if( isadj(d31,d32,g) )
      { /* G1209 */ /*printf("spt318\n");*/
/*
W1003
*/

/*
w1003

******************* reading edge list *************




(  1,  5) (  1,  6) (  2,  6) (  2,  3) (  1,  7) (  2,  7) (  3,  4) 
(  6,  7) (  1,  4) (  3,  7) (  5,  6) (  2,  5) (  4,  7) (  3,  6) 
(  4,  5) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              28      72      71      35       9       1 
I =   1      28     137     159      68      10 
I =   2      93     207     111      15 
I =   3     140     161      36       1 
I =   4     134      80       6 
I =   5      94      27 
I =   6      51       5 
I =   7      21 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      28; 
tutteMat[  0][  2] =      72; 
tutteMat[  0][  3] =      71; 
tutteMat[  0][  4] =      35; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      28; 
tutteMat[  1][  1] =     137; 
tutteMat[  1][  2] =     159; 
tutteMat[  1][  3] =      68; 
tutteMat[  1][  4] =      10; 
tutteMat[  2][  0] =      93; 
tutteMat[  2][  1] =     207; 
tutteMat[  2][  2] =     111; 
tutteMat[  2][  3] =      15; 
tutteMat[  3][  0] =     140; 
tutteMat[  3][  1] =     161; 
tutteMat[  3][  2] =      36; 
tutteMat[  3][  3] =       1; 
tutteMat[  4][  0] =     134; 
tutteMat[  4][  1] =      80; 
tutteMat[  4][  2] =       6; 
tutteMat[  5][  0] =      94; 
tutteMat[  5][  1] =      27; 
tutteMat[  6][  0] =      51; 
tutteMat[  6][  1] =       5; 
tutteMat[  7][  0] =      21; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

      
      } 
     else
      { /* G1210 */ /*printf("spt319\n");*/
/*
W1004
*/

/*
w1004

******************* reading edge list *************




(  1,  4) (  1,  7) (  2,  4) (  1,  5) (  3,  4) (  6,  7) (  1,  6) 
(  3,  7) (  3,  5) (  2,  6) (  2,  5) (  2,  7) (  3,  6) (  5,  6) 
(  4,  7) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              31      78      75      36       9       1 
I =   1      31     146     162      66       9 
I =   2      99     210     108      15 
I =   3     144     159      36 
I =   4     135      79       6 
I =   5      94      27 
I =   6      51       5 
I =   7      21 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      31; 
tutteMat[  0][  2] =      78; 
tutteMat[  0][  3] =      75; 
tutteMat[  0][  4] =      36; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      31; 
tutteMat[  1][  1] =     146; 
tutteMat[  1][  2] =     162; 
tutteMat[  1][  3] =      66; 
tutteMat[  1][  4] =       9; 
tutteMat[  2][  0] =      99; 
tutteMat[  2][  1] =     210; 
tutteMat[  2][  2] =     108; 
tutteMat[  2][  3] =      15; 
tutteMat[  3][  0] =     144; 
tutteMat[  3][  1] =     159; 
tutteMat[  3][  2] =      36; 
tutteMat[  4][  0] =     135; 
tutteMat[  4][  1] =      79; 
tutteMat[  4][  2] =       6; 
tutteMat[  5][  0] =      94; 
tutteMat[  5][  1] =      27; 
tutteMat[  6][  0] =      51; 
tutteMat[  6][  1] =       5; 
tutteMat[  7][  0] =      21; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

       
      } 
    } /* end else 2 */
  } /* end else 1 */
 }
break; 

default:
  {
     printf("sevenpart3drc2\n");
     break;
  }


} /*  end switch on degseq */
}  /* end sevenpart3drc2 */

/*                                            */
/*           end of sevenpart3drc2            */
/*                                            */
/**********************************************/




