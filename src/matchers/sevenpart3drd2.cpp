#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3drd           */
/*                                            */
 
 
/* 

Precondition: g is a simple seven vertex graph with 14 or 15 edges 
              degseq is 1510 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 


void
sevenpart3drd2(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX)

{
int  
    d31,            /* location on vertex list of vertices of degree 3  */
    d32, 
    d31a,
    d31b,
    d51,            /* location on vertex list of vertex of degree 5     */
    vt;             /* location on vertex list                           */



//printf("sevenpart3drd2\n");
    
switch(degseq)
{  /* 1 */

case 1510:
{  /* start 1510 */
  vt= firstVertex(g);  
  d31 = nextofdegree(
                     g,
                     &vt,
                     THREE 
                    );
 vt=firstVertex(g);
  d51 = nextofdegree(
                     g,
                     &vt,
                     FIVE 
                    );
 if( isadj(d31,d51,g) )
  { /* isadj d31,d51 */
   switch( commonadj(g,d31,d51) )
    { /* switch common adj d31,d51 */
     case TWO: 
      { /* G1167 *//*printf("spt329\n");*/
/*
W0957
*/
/*
w0957


******************* reading edge list *************




(  2,  4) (  2,  7) (  3,  4) (  2,  6) (  1,  5) (  2,  3) (  1,  7) 
(  4,  6) (  3,  5) (  6,  7) (  4,  5) (  1,  6) (  3,  7) (  5,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              18      49      52      28       8       1 
I =   1      18      90     110      50       8 
I =   2      59     133      72      10 
I =   3      85      94      19 
I =   4      74      39       2 
I =   5      45      10 
I =   6      20       1 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      18; 
tutteMat[  0][  2] =      49; 
tutteMat[  0][  3] =      52; 
tutteMat[  0][  4] =      28; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      18; 
tutteMat[  1][  1] =      90; 
tutteMat[  1][  2] =     110; 
tutteMat[  1][  3] =      50; 
tutteMat[  1][  4] =       8; 
tutteMat[  2][  0] =      59; 
tutteMat[  2][  1] =     133; 
tutteMat[  2][  2] =      72; 
tutteMat[  2][  3] =      10; 
tutteMat[  3][  0] =      85; 
tutteMat[  3][  1] =      94; 
tutteMat[  3][  2] =      19; 
tutteMat[  4][  0] =      74; 
tutteMat[  4][  1] =      39; 
tutteMat[  4][  2] =       2; 
tutteMat[  5][  0] =      45; 
tutteMat[  5][  1] =      10; 
tutteMat[  6][  0] =      20; 
tutteMat[  6][  1] =       1; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

       
      }
     break;
     case ONE:
      { /* case 1 */
       deletevrtx(
                  g,
                  d31
                 );
       vt= firstVertex(g); 
       d31a = nextofdegree(
                           g,
                           &vt,
                           THREE 
                          );
       d31b = nextofdegree(
                           g,
                           &vt,
                           THREE 
                          );
       if( isadj(d31a,d31b,g) ) 
        { /* G1166 *//*printf("spt330\n");*/
/*
W0958
*/
/*
w0958

******************* reading edge list *************




(  2,  3) (  1,  7) (  1,  5) (  2,  7) (  3,  4) (  5,  7) (  3,  6) 
(  2,  6) (  3,  7) (  1,  6) (  2,  4) (  4,  5) (  5,  6) (  4,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              18      49      52      28       8       1 
I =   1      18      89     109      50       8 
I =   2      58     131      72       9 
I =   3      83      94      19       1 
I =   4      73      40       2 
I =   5      45      10 
I =   6      20       1 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      18; 
tutteMat[  0][  2] =      49; 
tutteMat[  0][  3] =      52; 
tutteMat[  0][  4] =      28; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      18; 
tutteMat[  1][  1] =      89; 
tutteMat[  1][  2] =     109; 
tutteMat[  1][  3] =      50; 
tutteMat[  1][  4] =       8; 
tutteMat[  2][  0] =      58; 
tutteMat[  2][  1] =     131; 
tutteMat[  2][  2] =      72; 
tutteMat[  2][  3] =       9; 
tutteMat[  3][  0] =      83; 
tutteMat[  3][  1] =      94; 
tutteMat[  3][  2] =      19; 
tutteMat[  3][  3] =       1; 
tutteMat[  4][  0] =      73; 
tutteMat[  4][  1] =      40; 
tutteMat[  4][  2] =       2; 
tutteMat[  5][  0] =      45; 
tutteMat[  5][  1] =      10; 
tutteMat[  6][  0] =      20; 
tutteMat[  6][  1] =       1; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

        
        }
       else
        { /* G1165 *//*printf("spt331\n");*/
/*
W0960
*/
/*
w0960

******************* reading edge list *************




(  2,  6) (  1,  7) (  3,  6) (  2,  5) (  1,  5) (  3,  4) (  4,  7) 
(  1,  6) (  4,  6) (  2,  4) (  3,  7) (  2,  7) (  3,  5) (  5,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              21      55      56      29       8       1 
I =   1      21      98     112      48       7 
I =   2      64     134      69       9 
I =   3      87      92      19 
I =   4      74      39       2 
I =   5      45      10 
I =   6      20       1 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      21; 
tutteMat[  0][  2] =      55; 
tutteMat[  0][  3] =      56; 
tutteMat[  0][  4] =      29; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      21; 
tutteMat[  1][  1] =      98; 
tutteMat[  1][  2] =     112; 
tutteMat[  1][  3] =      48; 
tutteMat[  1][  4] =       7; 
tutteMat[  2][  0] =      64; 
tutteMat[  2][  1] =     134; 
tutteMat[  2][  2] =      69; 
tutteMat[  2][  3] =       9; 
tutteMat[  3][  0] =      87; 
tutteMat[  3][  1] =      92; 
tutteMat[  3][  2] =      19; 
tutteMat[  4][  0] =      74; 
tutteMat[  4][  1] =      39; 
tutteMat[  4][  2] =       2; 
tutteMat[  5][  0] =      45; 
tutteMat[  5][  1] =      10; 
tutteMat[  6][  0] =      20; 
tutteMat[  6][  1] =       1; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

         
        }
      } /* end case 1 */
     break;
    } /* end switch commonadj d31 d51 */
  } /* adj d31, d51 */
 else
  {
   vt=firstVertex(g);
   d51 = nextofdegree(
                      g,
                      &vt,
                      FIVE 
                     );
   deletevrtx(g,d51);
   vt= firstVertex(g);  
   deletevrtx(g,vt);
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
    { /* G1168 *//*printf("spt332\n");*/
/*
W0959*/

tutteMat[0][1] =     20;
 tutteMat[0][2] =     52;
 tutteMat[0][3] =     53;
 tutteMat[0][4] =     28;
 tutteMat[0][5] =      8;
 tutteMat[0][6] =      1;
 tutteMat[1][0] =     20;
 tutteMat[1][1] =     94;
 tutteMat[1][2] =    108;
 tutteMat[1][3] =     48;
 tutteMat[1][4] =      8;
 tutteMat[2][0] =     62;
 tutteMat[2][1] =    130;
 tutteMat[2][2] =     68;
 tutteMat[2][3] =     10;
 tutteMat[3][0] =     85;
 tutteMat[3][1] =     90;
 tutteMat[3][2] =     20;
 tutteMat[3][3] =      1;
 tutteMat[4][0] =     73;
 tutteMat[4][1] =     39;
 tutteMat[4][2] =      3;
 tutteMat[5][0] =     45;
 tutteMat[5][1] =     10;
 tutteMat[6][0] =     20;
 tutteMat[6][1] =      1;
 tutteMat[7][0] =      6;
 tutteMat[8][0] =      1;
    

}
   else
    { /* G1169 *//*printf("spt333\n");*/
/*
W0961
*/
/*
w0961

******************* reading edge list *************




(  1,  6) (  2,  6) (  3,  7) (  3,  5) (  1,  4) (  5,  7) (  2,  7) 
(  2,  5) (  1,  5) (  3,  6) (  3,  4) (  6,  7) (  4,  7) (  2,  4) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              24      61      60      30       8       1 
I =   1      24     107     114      45       6 
I =   2      70     135      63       9 
I =   3      90      87      20 
I =   4      74      38       3 
I =   5      45      10 
I =   6      20       1 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      24; 
tutteMat[  0][  2] =      61; 
tutteMat[  0][  3] =      60; 
tutteMat[  0][  4] =      30; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      24; 
tutteMat[  1][  1] =     107; 
tutteMat[  1][  2] =     114; 
tutteMat[  1][  3] =      45; 
tutteMat[  1][  4] =       6; 
tutteMat[  2][  0] =      70; 
tutteMat[  2][  1] =     135; 
tutteMat[  2][  2] =      63; 
tutteMat[  2][  3] =       9; 
tutteMat[  3][  0] =      90; 
tutteMat[  3][  1] =      87; 
tutteMat[  3][  2] =      20; 
tutteMat[  4][  0] =      74; 
tutteMat[  4][  1] =      38; 
tutteMat[  4][  2] =       3; 
tutteMat[  5][  0] =      45; 
tutteMat[  5][  1] =      10; 
tutteMat[  6][  0] =      20; 
tutteMat[  6][  1] =       1; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

     
    }
  }
}
break;


default:
  {
     printf("sevenpart3drd2\n");
     break;
  }

} /*  end switch on degseq */



}  /* end sevenpart3drd2 */

/*                                            */
/*           end of sevenpart3drd2            */
/*                                            */
/**********************************************/




