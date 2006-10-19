#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart4              */
/*                                            */
 

/*

Precondition: g is a simple seven vertex graph with 13 edges
              degseq is 10240
              tutteMat and tutteMatX are arrays with
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte
               poly of this graph

*/

void
sevenpart42(struct Graph *g, TUTTE tutteMat,TUTTEO tutteMatX)

{
int d31,             /* location on vertex list of vertices of degree 3 */
    d32,
    d41,            /* location on vertex list of vertices of degree 4  */
    d42,
    vt,             /* location on vertex list                          */ 
    ne1;            /* location on edge list                            */


/*case 10240:*//* start with adjacency or non-adjacency of vertices of degree 4.
              if adjacent, case statement on number of common adjacencies
                CASE 1: are degree 3 vertices adjacent to a degree 4 vertex 
                        adjacent
              */
 /*printf("10240\n"); */
vt = firstVertex(g);  //(*g).vrtx[ZERO].nvert; 
d41 = nextofdegree(
                   g,
                   &vt,
                   FOUR
                  );
d42 = nextofdegree(
                   g,
                   &vt,
                   FOUR
                  );
if( ! isadj(d41,d42,g) )
  { /* G1079  *//*printf("wo858 spt742\n");*/
/*
W0858
*/
/*
w0858
                                                                                              

******************* reading edge list *************




(  1,  5) (  1,  6) (  2,  5) (  1,  7) (  2,  7) (  3,  4) (  2,  6) 
(  3,  6) (  4,  5) (  6,  7) (  4,  7) (  5,  7) (  3,  7) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              10      29      34      21       7       1 
I =   1      10      47      61      33       7 
I =   2      28      64      44      10 
I =   3      36      48      15 
I =   4      30      21       1 
I =   5      17       4 
I =   6       6 
I =   7       1 
*/
     tutteMat[  0][  1] =      10; 
     tutteMat[  0][  2] =      29; 
     tutteMat[  0][  3] =      34; 
     tutteMat[  0][  4] =      21; 
     tutteMat[  0][  5] =       7; 
     tutteMat[  0][  6] =       1; 
     tutteMat[  1][  0] =      10; 
     tutteMat[  1][  1] =      47; 
     tutteMat[  1][  2] =      61; 
     tutteMat[  1][  3] =      33; 
     tutteMat[  1][  4] =       7; 
     tutteMat[  2][  0] =      28; 
     tutteMat[  2][  1] =      64; 
     tutteMat[  2][  2] =      44; 
     tutteMat[  2][  3] =      10; 
     tutteMat[  3][  0] =      36; 
     tutteMat[  3][  1] =      48; 
     tutteMat[  3][  2] =      15; 
     tutteMat[  4][  0] =      30; 
     tutteMat[  4][  1] =      21; 
     tutteMat[  4][  2] =       1; 
     tutteMat[  5][  0] =      17; 
     tutteMat[  5][  1] =       4; 
     tutteMat[  6][  0] =       6; 
     tutteMat[  7][  0] =       1; 
  } 
else
  { 
     switch( commonadj(g,d41,d42) )
       {
          case TWO:
            { /* G1078 *//*printf("spt743\n");*/
/*
W0856
*/
/*
w0856


******************* reading edge list *************




(  2,  7) (  2,  4) (  1,  7) (  3,  7) (  3,  4) (  1,  6) (  3,  5) 
(  5,  7) (  4,  7) (  1,  5) (  6,  7) (  5,  6) (  2,  6) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               8      24      30      20       7       1 
I =   1       8      41      58      35       8 
I =   2      25      62      45      10 
I =   3      35      47      15       1 
I =   4      30      20       2 
I =   5      17       4 
I =   6       6 
I =   7       1 
*/
              tutteMat[  0][  1] =       8; 
              tutteMat[  0][  2] =      24; 
              tutteMat[  0][  3] =      30; 
              tutteMat[  0][  4] =      20; 
              tutteMat[  0][  5] =       7; 
              tutteMat[  0][  6] =       1; 
              tutteMat[  1][  0] =       8; 
              tutteMat[  1][  1] =      41; 
              tutteMat[  1][  2] =      58; 
              tutteMat[  1][  3] =      35; 
              tutteMat[  1][  4] =       8; 
              tutteMat[  2][  0] =      25; 
              tutteMat[  2][  1] =      62; 
              tutteMat[  2][  2] =      45; 
              tutteMat[  2][  3] =      10; 
              tutteMat[  3][  0] =      35; 
              tutteMat[  3][  1] =      47; 
              tutteMat[  3][  2] =      15; 
              tutteMat[  3][  3] =       1; 
              tutteMat[  4][  0] =      30; 
              tutteMat[  4][  1] =      20; 
              tutteMat[  4][  2] =       2; 
              tutteMat[  5][  0] =      17; 
              tutteMat[  5][  1] =       4; 
              tutteMat[  6][  0] =       6; 
              tutteMat[  7][  0] =       1; 
           } 
            break;
         case ONE: 
           { 
              ne1 = firstEdge(g, d41);  //(*g).edg[(*g).vrtx[d41].fedge].front;
              d31 = nextdegnadjtov(
                                   g,
                                   &ne1,
                                   THREE
                                  );
              d32 = nextdegnadjtov(
                                   g,
                                   &ne1,
                                   THREE
                                  );
              if( isadj(d31,d32,g) )
                { /* G1081 *//*printf("spt744\n");*/
/*
W0849
*/
/*
w0849


******************* reading edge list *************




(  1,  7) (  2,  7) (  2,  3) (  1,  4) (  5,  7) (  4,  7) (  5,  6) 
(  3,  7) (  2,  5) (  1,  6) (  6,  7) (  4,  6) (  3,  5) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               4      16      25      19       7       1 
I =   1       4      28      53      38       9 
I =   2      16      56      50      10 
I =   3      28      50      16       2 
I =   4      28      22       2 
I =   5      17       4 
I =   6       6 
I =   7       1 
*/
                  tutteMat[  0][  1] =       4; 
                  tutteMat[  0][  2] =      16; 
                  tutteMat[  0][  3] =      25; 
                  tutteMat[  0][  4] =      19; 
                  tutteMat[  0][  5] =       7; 
                  tutteMat[  0][  6] =       1; 
                  tutteMat[  1][  0] =       4; 
                  tutteMat[  1][  1] =      28; 
                  tutteMat[  1][  2] =      53; 
                  tutteMat[  1][  3] =      38; 
                  tutteMat[  1][  4] =       9; 
                  tutteMat[  2][  0] =      16; 
                  tutteMat[  2][  1] =      56; 
                  tutteMat[  2][  2] =      50; 
                  tutteMat[  2][  3] =      10; 
                  tutteMat[  3][  0] =      28; 
                  tutteMat[  3][  1] =      50; 
                  tutteMat[  3][  2] =      16; 
                  tutteMat[  3][  3] =       2; 
                  tutteMat[  4][  0] =      28; 
                  tutteMat[  4][  1] =      22; 
                  tutteMat[  4][  2] =       2; 
                  tutteMat[  5][  0] =      17; 
                  tutteMat[  5][  1] =       4; 
                  tutteMat[  6][  0] =       6; 
                  tutteMat[  7][  0] =       1; 
               } 
             else 
               { /* G 1080 *//*printf("spt745\n");*/
 /*
W0859
*/
/*
w0859

                                                                                              

******************* reading edge list *************




(  1,  6) (  1,  7) (  2,  3) (  1,  4) (  2,  7) (  3,  5) (  5,  6) 
(  3,  7) (  5,  7) (  4,  7) (  4,  5) (  6,  7) (  2,  6) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               9      27      33      21       7       1 
I =   1       9      45      61      34       7 
I =   2      27      64      43      10 
I =   3      36      46      16 
I =   4      30      20       2 
I =   5      17       4 
I =   6       6 
I =   7       1 
*/
                  tutteMat[  0][  1] =       9; 
                  tutteMat[  0][  2] =      27; 
                  tutteMat[  0][  3] =      33; 
                  tutteMat[  0][  4] =      21; 
                  tutteMat[  0][  5] =       7; 
                  tutteMat[  0][  6] =       1; 
                  tutteMat[  1][  0] =       9; 
                  tutteMat[  1][  1] =      45; 
                  tutteMat[  1][  2] =      61; 
                  tutteMat[  1][  3] =      34; 
                  tutteMat[  1][  4] =       7; 
                  tutteMat[  2][  0] =      27; 
                  tutteMat[  2][  1] =      64; 
                  tutteMat[  2][  2] =      43; 
                  tutteMat[  2][  3] =      10; 
                  tutteMat[  3][  0] =      36; 
                  tutteMat[  3][  1] =      46; 
                  tutteMat[  3][  2] =      16; 
                  tutteMat[  4][  0] =      30; 
                  tutteMat[  4][  1] =      20; 
                  tutteMat[  4][  2] =       2; 
                  tutteMat[  5][  0] =      17; 
                  tutteMat[  5][  1] =       4; 
                  tutteMat[  6][  0] =       6; 
                  tutteMat[  7][  0] =       1; 
               } 
           }
            break;
        } /* end CASE ONE */
  } /* end adjacency else */


} /* end sevenpart42 */  

/*                                            */
/*           end of sevenpart42               */
/*                                            */
/**********************************************/


