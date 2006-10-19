#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3dre3           */
/*                                            */
 
 
/* 

Precondition: g is a simple seven vertex graph with 14 or 15 edges 
              degseq is 10420 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3dre3(
               struct graph *g,
               int degseq,
               TUTTE tutteMat,
               TUTTEO tutteMatX
              )



{
int d31,            /* location on vertex list of vertices of degree 3  */ 
    d32, 
    d41,            /* location on vertex list of vertex of degree 5    */
    d42,
    vt,             /* location on vertex list                           */
    ne1,            /* location on edge list                             */
    no3;            /* number of common adjacencies of two degree
    	            	   3 vertices                                    */

//printf("sevenpart3dre\n");    

switch(degseq)
{  /* 1 */


case 10420:/* see if the vertices of degree 3 are adjacent.
              if not, determine the number of common adjacencies
              for the vertices of degree 3 
              CASE 1: are vertices of degree 4 adjacent to a 
                      vertex of degree 3 adjacent */
 { 
/*printf("10420\n");*/  
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
   { /* g1151  *//*printf("spt344\n");*/
/*
W0942
*/
/*
w0942

******************* reading edge list *************




(  1,  7) (  1,  6) (  3,  4) (  2,  5) (  1,  2) (  2,  7) (  3,  5) 
(  5,  7) (  6,  7) (  4,  5) (  4,  6) (  3,  7) (  4,  7) (  3,  6) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              14      39      44      26       8       1 
I =   1      14      70      91      49      10 
I =   2      45     107      71      15 
I =   3      66      85      27       2 
I =   4      61      42       6 
I =   5      40      13       1 
I =   6      19       2 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      14; 
tutteMat[  0][  2] =      39; 
tutteMat[  0][  3] =      44; 
tutteMat[  0][  4] =      26; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      14; 
tutteMat[  1][  1] =      70; 
tutteMat[  1][  2] =      91; 
tutteMat[  1][  3] =      49; 
tutteMat[  1][  4] =      10; 
tutteMat[  2][  0] =      45; 
tutteMat[  2][  1] =     107; 
tutteMat[  2][  2] =      71; 
tutteMat[  2][  3] =      15; 
tutteMat[  3][  0] =      66; 
tutteMat[  3][  1] =      85; 
tutteMat[  3][  2] =      27; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =      61; 
tutteMat[  4][  1] =      42; 
tutteMat[  4][  2] =       6; 
tutteMat[  5][  0] =      40; 
tutteMat[  5][  1] =      13; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

    
   } 
  else
   { 
    no3 = commonadj(
                    g,
                    d31,
                    d32
                   );
    if( no3 == TWO )
     { /* g1149  *//*printf("spt345\n");*/
/*
W0943
*/
/*
w0943

******************* reading edge list *************




(  1,  5) (  1,  7) (  1,  6) (  3,  4) (  2,  6) (  3,  6) (  2,  4) 
(  3,  5) (  5,  7) (  3,  7) (  4,  5) (  6,  7) (  4,  7) (  2,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              16      44      48      27       8       1 
I =   1      16      77      96      48       9 
I =   2      49     111      70      14 
I =   3      68      86      27       1 
I =   4      61      44       5 
I =   5      40      14 
I =   6      19       2 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      16; 
tutteMat[  0][  2] =      44; 
tutteMat[  0][  3] =      48; 
tutteMat[  0][  4] =      27; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      16; 
tutteMat[  1][  1] =      77; 
tutteMat[  1][  2] =      96; 
tutteMat[  1][  3] =      48; 
tutteMat[  1][  4] =       9; 
tutteMat[  2][  0] =      49; 
tutteMat[  2][  1] =     111; 
tutteMat[  2][  2] =      70; 
tutteMat[  2][  3] =      14; 
tutteMat[  3][  0] =      68; 
tutteMat[  3][  1] =      86; 
tutteMat[  3][  2] =      27; 
tutteMat[  3][  3] =       1; 
tutteMat[  4][  0] =      61; 
tutteMat[  4][  1] =      44; 
tutteMat[  4][  2] =       5; 
tutteMat[  5][  0] =      40; 
tutteMat[  5][  1] =      14; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

      
     }
    else
     if( no3 == ONE )
      { 
       ne1 = firstEdge(g, d31);  
       d41 = nextdegnadjtov(
                            g,
                            &ne1,
                            FOUR
                           );
       d42 = nextdegnadjtov(
                            g,
                            &ne1,
                            FOUR
                           );       
       if( isadj(d41,d42,g) )
        { /* G1150 */ /*printf("spt346\n");*/
 /*
W0938
*/
/*
w0938

******************* reading edge list *************




(  1,  5) (  1,  6) (  5,  6) (  2,  4) (  1,  7) (  4,  5) (  5,  7) 
(  3,  6) (  3,  7) (  3,  4) (  4,  7) (  2,  3) (  2,  7) (  6,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              12      36      43      26       8       1 
I =   1      12      64      91      51      10 
I =   2      40     105      75      14 
I =   3      61      89      28       2 
I =   4      59      46       5 
I =   5      40      14 
I =   6      19       2 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      12; 
tutteMat[  0][  2] =      36; 
tutteMat[  0][  3] =      43; 
tutteMat[  0][  4] =      26; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      12; 
tutteMat[  1][  1] =      64; 
tutteMat[  1][  2] =      91; 
tutteMat[  1][  3] =      51; 
tutteMat[  1][  4] =      10; 
tutteMat[  2][  0] =      40; 
tutteMat[  2][  1] =     105; 
tutteMat[  2][  2] =      75; 
tutteMat[  2][  3] =      14; 
tutteMat[  3][  0] =      61; 
tutteMat[  3][  1] =      89; 
tutteMat[  3][  2] =      28; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =      59; 
tutteMat[  4][  1] =      46; 
tutteMat[  4][  2] =       5; 
tutteMat[  5][  0] =      40; 
tutteMat[  5][  1] =      14; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

        
        } 
       else
        { /* G1152 */ /*printf("spt347\n");*/
/*
W0944
*/
/*
w0944

******************* reading edge list *************




(  1,  7) (  2,  7) (  3,  7) (  4,  6) (  2,  4) (  1,  5) (  4,  5) 
(  2,  3) (  1,  6) (  3,  6) (  3,  5) (  4,  7) (  5,  7) (  6,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              17      47      51      28       8       1 
I =   1      17      81      99      47       8 
I =   2      51     113      68      14 
I =   3      69      85      28 
I =   4      61      44       5 
I =   5      40      14 
I =   6      19       2 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      17; 
tutteMat[  0][  2] =      47; 
tutteMat[  0][  3] =      51; 
tutteMat[  0][  4] =      28; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      17; 
tutteMat[  1][  1] =      81; 
tutteMat[  1][  2] =      99; 
tutteMat[  1][  3] =      47; 
tutteMat[  1][  4] =       8; 
tutteMat[  2][  0] =      51; 
tutteMat[  2][  1] =     113; 
tutteMat[  2][  2] =      68; 
tutteMat[  2][  3] =      14; 
tutteMat[  3][  0] =      69; 
tutteMat[  3][  1] =      85; 
tutteMat[  3][  2] =      28; 
tutteMat[  4][  0] =      61; 
tutteMat[  4][  1] =      44; 
tutteMat[  4][  2] =       5; 
tutteMat[  5][  0] =      40; 
tutteMat[  5][  1] =      14; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

         
        } 
      } 
   } 
 }
break;

default:
  {
     printf("sevenpart3dre3\n");
     break;
  }

} /*  end switch on degseq */

}  /* end sevenpart3dre3 */

/*                                            */
/*           end of sevenpart3dre3            */
/*                                            */
/**********************************************/




