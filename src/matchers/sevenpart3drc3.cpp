#include "core/tutte.h"
#include <memory.h>

/**********************************************/

/*                                            */
/*           start of sevenpart3drc3          */
/*                                            */

 
/* 

Precondition: g is a simple seven vertex graph with 15 edges 
              degseq is 10600 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3drc3(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX)

{
int d41,            /* location on vertex list of vertex of degree 5    */
    d41a,
    d41b,
    vt;             /* location on vertex list                           */

printf("sevenpart3drc3\n");

switch( degseq )
{  /* 1 */


case 10600:
{/*printf("10600\n");*/
 vt= firstVertex(g);  
  d41 = nextofdegree(
                     g,
                     &vt,
                     FOUR 
                    );
 deletevrtx(g,d41);
 vt= firstVertex(g);  
  d41a = nextofdegree(
                     g,
                     &vt,
                    FOUR 
                    );
  d41b = nextofdegree(
                     g,
                     &vt,
                   FOUR 
                    );
 if( isadj(d41a,d41b,g) )
  { /* G1207 */ /*printf("spt320\n");*/
/*
W0996
*/
/*
w0996

******************* reading edge list *************




(  2,  7) (  2,  5) (  1,  7) (  2,  6) (  3,  7) (  1,  4) (  4,  5) 
(  1,  5) (  6,  7) (  4,  7) (  3,  4) (  1,  6) (  2,  3) (  5,  7) 
(  3,  6) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              26      67      67      34       9       1 
I =   1      26     126     148      67      11 
I =   2      85     190     109      18 
I =   3     127     153      42       2 
I =   4     123      84       9 
I =   5      90      30 
I =   6      50       6 
I =   7      21 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      26; 
tutteMat[  0][  2] =      67; 
tutteMat[  0][  3] =      67; 
tutteMat[  0][  4] =      34; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      26; 
tutteMat[  1][  1] =     126; 
tutteMat[  1][  2] =     148; 
tutteMat[  1][  3] =      67; 
tutteMat[  1][  4] =      11; 
tutteMat[  2][  0] =      85; 
tutteMat[  2][  1] =     190; 
tutteMat[  2][  2] =     109; 
tutteMat[  2][  3] =      18; 
tutteMat[  3][  0] =     127; 
tutteMat[  3][  1] =     153; 
tutteMat[  3][  2] =      42; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =     123; 
tutteMat[  4][  1] =      84; 
tutteMat[  4][  2] =       9; 
tutteMat[  5][  0] =      90; 
tutteMat[  5][  1] =      30; 
tutteMat[  6][  0] =      50; 
tutteMat[  6][  1] =       6; 
tutteMat[  7][  0] =      21; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

  
  } 
 else
  { /* G1208 *//*printf("spt321\n");*/
/*
W0999
*/
/*
w0999

******************* reading edge list *************




(  2,  7) (  1,  6) (  2,  4) (  1,  4) (  3,  7) (  4,  7) (  3,  5) 
(  1,  5) (  3,  4) (  3,  6) (  5,  7) (  1,  7) (  6,  7) (  2,  5) 
(  2,  6) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              31      78      75      36       9       1 
I =   1      31     143     156      63       9 
I =   2      96     198     102      18 
I =   3     135     149      42 
I =   4     125      82       9 
I =   5      90      30 
I =   6      50       6 
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
tutteMat[  1][  1] =     143; 
tutteMat[  1][  2] =     156; 
tutteMat[  1][  3] =      63; 
tutteMat[  1][  4] =       9; 
tutteMat[  2][  0] =      96; 
tutteMat[  2][  1] =     198; 
tutteMat[  2][  2] =     102; 
tutteMat[  2][  3] =      18; 
tutteMat[  3][  0] =     135; 
tutteMat[  3][  1] =     149; 
tutteMat[  3][  2] =      42; 
tutteMat[  4][  0] =     125; 
tutteMat[  4][  1] =      82; 
tutteMat[  4][  2] =       9; 
tutteMat[  5][  0] =      90; 
tutteMat[  5][  1] =      30; 
tutteMat[  6][  0] =      50; 
tutteMat[  6][  1] =       6; 
tutteMat[  7][  0] =      21; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

   
  } 
}
break;
default:
  {
     printf("sevenpart3drc3\n");
     break;
  }


} /*  end switch on degseq */
}  /* end sevenpart3drc3 */

/*                                            */
/*           end of sevenpart3drc3            */
/*                                            */
/**********************************************/




