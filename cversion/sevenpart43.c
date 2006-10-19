#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart43             */
/*                                            */
 


/* 

Precondition: g is a simple seven vertex graph with 13 edges 
              degseq is 2140 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 


void
sevenpart43(
            struct graph *g,
            TUTTE tutteMat,
            TUTTEO tutteMatX
           )

{
int vt,             /* location of vertex on vertex list                */
    d31,            /* location on vertex list of vertices of degree 3  */
    d32,
    d41,            /* location on vertex list of vertices of degree 4  */
    ne1,            /* location on edge list                            */
    d51,            /* location on vertex list of vertices of degree 5  */
    d52,
    sum,            /* accumulator for degress of sets of vertices       */ 
    sum1,
    sum2;


/*case 2140:*//* case on sum of degrees of neighbors of vertex of degree 4
              CASE 16: case on sum of the degrees of the neighbors
                       of the two vertices of degree 5
                     CASE 36: case on number of common adjacencies of 
                              the degree 5 vertex
                       case 3: are two degree 3 vertices adjacent to 
                               a degree 4 vertex adjacent. if not, use 
                               case on number of common adjacencies for 
                               the two vertices of degree 3 */

vt = firstVertex(g);  //(*g).vrtx[ZERO].nvert;
d41 = nextofdegree(
                   g,
                   &vt,
                   FOUR
                  );
sum = degreesofnhbrs(
                     g,
                     d41
                    );
switch( sum )
  { /* b */
     case 12:
       { /* G1088 */ /* c *//*printf("spt746\n");*/
/*
W0864
*/
/*
W0864

******************* reading edge list *************




(  2,  5) (  2,  6) (  3,  7) (  1,  5) (  1,  6) (  2,  7) (  6,  7) 
(  4,  5) (  1,  7) (  4,  6) (  3,  6) (  4,  7) (  3,  5) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              14      40      44      24       7       1 
I =   1      14      61      72      30       4 
I =   2      35      73      42       6 
I =   3      40      51      10 
I =   4      31      21 
I =   5      17       4 
I =   6       6 
i =   7       1 
*/
          tutteMat[  0][  1] =      14; 
          tutteMat[  0][  2] =      40; 
          tutteMat[  0][  3] =      44; 
          tutteMat[  0][  4] =      24; 
          tutteMat[  0][  5] =       7; 
          tutteMat[  0][  6] =       1; 
          tutteMat[  1][  0] =      14; 
          tutteMat[  1][  1] =      61; 
          tutteMat[  1][  2] =      72; 
          tutteMat[  1][  3] =      30; 
          tutteMat[  1][  4] =       4; 
          tutteMat[  2][  0] =      35; 
          tutteMat[  2][  1] =      73; 
          tutteMat[  2][  2] =      42; 
          tutteMat[  2][  3] =       6; 
          tutteMat[  3][  0] =      40; 
          tutteMat[  3][  1] =      51; 
          tutteMat[  3][  2] =      10; 
          tutteMat[  4][  0] =      31; 
          tutteMat[  4][  1] =      21; 
          tutteMat[  5][  0] =      17; 
          tutteMat[  5][  1] =       4; 
          tutteMat[  6][  0] =       6; 
          tutteMat[  7][  0] =       1; 
       } /* c */
        break;
    
     case 14:
       { /* G1084  */  /* d *//*printf("spt747\n");*/
/*
W0869
*/
/*
W0869

******************* reading edge list *************




(  3,  7) (  1,  7) (  3,  6) (  1,  5) (  2,  6) (  2,  7) (  4,  5) 
(  3,  4) (  2,  5) (  5,  6) (  4,  7) (  6,  7) (  1,  6) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              11      32      37      22       7       1 
I =   1      11      52      67      34       6 
I =   2      31      70      44       7 
I =   3      39      49      12 
I =   4      31      20       1 
I =   5      17       4 
I =   6       6 
I =   7       1 
*/
          tutteMat[  0][  1] =      11; 
          tutteMat[  0][  2] =      32; 
          tutteMat[  0][  3] =      37; 
          tutteMat[  0][  4] =      22; 
          tutteMat[  0][  5] =       7; 
          tutteMat[  0][  6] =       1; 
          tutteMat[  1][  0] =      11; 
          tutteMat[  1][  1] =      52; 
          tutteMat[  1][  2] =      67; 
          tutteMat[  1][  3] =      34; 
          tutteMat[  1][  4] =       6; 
          tutteMat[  2][  0] =      31; 
          tutteMat[  2][  1] =      70; 
          tutteMat[  2][  2] =      44; 
          tutteMat[  2][  3] =       7; 
          tutteMat[  3][  0] =      39; 
          tutteMat[  3][  1] =      49; 
          tutteMat[  3][  2] =      12; 
          tutteMat[  4][  0] =      31; 
          tutteMat[  4][  1] =      20; 
          tutteMat[  4][  2] =       1; 
          tutteMat[  5][  0] =      17; 
          tutteMat[  5][  1] =       4; 
          tutteMat[  6][  0] =       6; 
          tutteMat[  7][  0] =       1; 
       } /* d */
       break;

     case 16:
       {  /* e */
          vt = firstVertex(g);  //(*g).vrtx[ZERO].nvert;
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
          sum1 = degreesofnhbrs(
                                g,
                                d51
                               );
          sum2 = degreesofnhbrs(
                                g,
                                d52
                               );
          switch( sum1 + sum2 )
            {  /* f */
               case 32:
                 { /* G1087 */ /* g *//*printf("spt748\n");*/
/*
W0861
*/
/*
W0861
 
******************* reading edge list *************




(  2,  7) (  3,  4) (  3,  6) (  3,  7) (  2,  6) (  1,  6) (  2,  5) 
(  5,  6) (  1,  5) (  4,  7) (  5,  7) (  4,  6) (  1,  7) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               8      27      35      22       7       1 
I =   1       8      46      70      38       6 
I =   2      27      73      47       5 
I =   3      38      51      11 
I =   4      31      20       1 
I =   5      17       4 
I =   6       6 
I =   7       1 
*/
                   tutteMat[  0][  1] =       8; 
                   tutteMat[  0][  2] =      27; 
                   tutteMat[  0][  3] =      35; 
                   tutteMat[  0][  4] =      22; 
                   tutteMat[  0][  5] =       7; 
                   tutteMat[  0][  6] =       1; 
                   tutteMat[  1][  0] =       8; 
                   tutteMat[  1][  1] =      46; 
                   tutteMat[  1][  2] =      70; 
                   tutteMat[  1][  3] =      38; 
                   tutteMat[  1][  4] =       6; 
                   tutteMat[  2][  0] =      27; 
                   tutteMat[  2][  1] =      73; 
                   tutteMat[  2][  2] =      47; 
                   tutteMat[  2][  3] =       5; 
                   tutteMat[  3][  0] =      38; 
                   tutteMat[  3][  1] =      51; 
                   tutteMat[  3][  2] =      11; 
                   tutteMat[  4][  0] =      31; 
                   tutteMat[  4][  1] =      20; 
                   tutteMat[  4][  2] =       1; 
                   tutteMat[  5][  0] =      17; 
                   tutteMat[  5][  1] =       4; 
                   tutteMat[  6][  0] =       6; 
                   tutteMat[  7][  0] =       1; 
                } /* 7 */ /* g */
                break;

     case 36:
       {/* 1 */
          switch( commonadj(g,d51,d52) )
            {/* 2 */
               case FOUR:
                 { /* G1085  */ /* 3 *//*printf("spt749\n");*/
 /*
W0878
*/
/*
W0878

******************* reading edge list *************




(  3,  4) (  4,  5) (  1,  5) (  2,  4) (  5,  6) (  3,  7) (  1,  6) 
(  2,  7) (  5,  7) (  1,  7) (  6,  7) (  3,  6) (  2,  6) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              12      34      38      22       7       1 
I =   1      12      55      66      31       6 
I =   2      33      69      39       8 
I =   3      40      45      13       1 
I =   4      31      19       2 
I =   5      17       4 
I =   6       6 
I =   7       1 
*/
                    tutteMat[  0][  1] =      12; 
                    tutteMat[  0][  2] =      34; 
                    tutteMat[  0][  3] =      38; 
                    tutteMat[  0][  4] =      22; 
                    tutteMat[  0][  5] =       7; 
                    tutteMat[  0][  6] =       1; 
                    tutteMat[  1][  0] =      12; 
                    tutteMat[  1][  1] =      55; 
                    tutteMat[  1][  2] =      66; 
                    tutteMat[  1][  3] =      31; 
                    tutteMat[  1][  4] =       6; 
                    tutteMat[  2][  0] =      33; 
                    tutteMat[  2][  1] =      69; 
                    tutteMat[  2][  2] =      39; 
                    tutteMat[  2][  3] =       8; 
                    tutteMat[  3][  0] =      40; 
                    tutteMat[  3][  1] =      45; 
                    tutteMat[  3][  2] =      13; 
                    tutteMat[  3][  3] =       1; 
                    tutteMat[  4][  0] =      31; 
                    tutteMat[  4][  1] =      19; 
                    tutteMat[  4][  2] =       2; 
                    tutteMat[  5][  0] =      17; 
                    tutteMat[  5][  1] =       4; 
                    tutteMat[  6][  0] =       6; 
                    tutteMat[  7][  0] =       1; 
                 } /* 10 */ /* 3 */
                  break;

               case THREE:
                 { /* 11 */ /* 4 *//*printf("spt7410\n");*/
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
                      { /* G1086 */ /* 5 */
/*
W0867
*/
/*
W0867

******************* reading edge list *************




(  2,  3) (  5,  6) (  1,  7) (  2,  5) (  4,  6) (  4,  7) (  3,  5) 
(  3,  6) (  1,  4) (  1,  6) (  5,  7) (  2,  7) (  6,  7) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               6      21      29      20       7       1 
I =   1       6      37      60      37       8 
I =   2      22      64      47       9 
I =   3      34      49      14       1 
I =   4      30      20       2 
I =   5      17       4 
I =   6       6 
I =   7       1 
*/
                        tutteMat[  0][  1] =       6; 
                        tutteMat[  0][  2] =      21; 
                        tutteMat[  0][  3] =      29; 
                        tutteMat[  0][  4] =      20; 
                        tutteMat[  0][  5] =       7; 
                        tutteMat[  0][  6] =       1; 
                        tutteMat[  1][  0] =       6; 
                        tutteMat[  1][  1] =      37; 
                        tutteMat[  1][  2] =      60; 
                        tutteMat[  1][  3] =      37; 
                        tutteMat[  1][  4] =       8; 
                        tutteMat[  2][  0] =      22; 
                        tutteMat[  2][  1] =      64; 
                        tutteMat[  2][  2] =      47; 
                        tutteMat[  2][  3] =       9; 
                        tutteMat[  3][  0] =      34; 
                        tutteMat[  3][  1] =      49; 
                        tutteMat[  3][  2] =      14; 
                        tutteMat[  3][  3] =       1; 
                        tutteMat[  4][  0] =      30; 
                        tutteMat[  4][  1] =      20; 
                        tutteMat[  4][  2] =       2; 
                        tutteMat[  5][  0] =      17; 
                        tutteMat[  5][  1] =       4; 
                        tutteMat[  6][  0] =       6; 
                        tutteMat[  7][  0] =       1; 
                     } /* 5 */
                   else
                     { /* 6 */
                        switch( commonadj(g,d31,d32) )
                          { /* 7 */
                             case TWO:
                               { /* G1082 */ /* 8 *//*printf("spt7411\n");*/
/*
W0874
*/
/*
W0874

******************* reading edge list *************




(  2,  6) (  3,  5) (  6,  7) (  2,  4) (  2,  7) (  1,  6) (  3,  4) 
(  1,  5) (  3,  7) (  5,  7) (  1,  7) (  5,  6) (  4,  6) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              10      29      34      21       7       1 
I =   1      10      49      64      34       7 
I =   2      30      68      42       8 
I =   3      39      46      13       1 
I =   4      31      19       2 
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
                                 tutteMat[  1][  1] =      49; 
                                 tutteMat[  1][  2] =      64; 
                                 tutteMat[  1][  3] =      34; 
                                 tutteMat[  1][  4] =       7; 
                                 tutteMat[  2][  0] =      30; 
                                 tutteMat[  2][  1] =      68; 
                                 tutteMat[  2][  2] =      42; 
                                 tutteMat[  2][  3] =       8; 
                                 tutteMat[  3][  0] =      39; 
                                 tutteMat[  3][  1] =      46; 
                                 tutteMat[  3][  2] =      13; 
                                 tutteMat[  3][  3] =       1; 
                                 tutteMat[  4][  0] =      31; 
                                 tutteMat[  4][  1] =      19; 
                                 tutteMat[  4][  2] =       2; 
                                 tutteMat[  5][  0] =      17; 
                                 tutteMat[  5][  1] =       4; 
                                 tutteMat[  6][  0] =       6; 
                                 tutteMat[  7][  0] =       1; 
                              } /* 8 */
                              break;

                            case ONE:
                              { /* G1083 */ /* 9 *//*printf("spt7412\n");*/
/*
W0872
*/
/*
W0872

******************* reading edge list *************




(  1,  6) (  1,  4) (  4,  5) (  2,  7) (  2,  6) (  2,  3) (  4,  6) 
(  5,  6) (  1,  7) (  3,  5) (  6,  7) (  5,  7) (  3,  7) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               9      27      33      21       7       1 
I =   1       9      46      63      35       7 
I =   2      28      67      44       9 
I =   3      38      47      14 
I =   4      31      19       2 
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
                                tutteMat[  1][  1] =      46; 
                                tutteMat[  1][  2] =      63; 
                                tutteMat[  1][  3] =      35; 
                                tutteMat[  1][  4] =       7; 
                                tutteMat[  2][  0] =      28; 
                                tutteMat[  2][  1] =      67; 
                                tutteMat[  2][  2] =      44; 
                                tutteMat[  2][  3] =       9; 
                                tutteMat[  3][  0] =      38; 
                                tutteMat[  3][  1] =      47; 
                                tutteMat[  3][  2] =      14; 
                                tutteMat[  4][  0] =      31; 
                                tutteMat[  4][  1] =      19; 
                                tutteMat[  4][  2] =       2; 
                                tutteMat[  5][  0] =      17; 
                                tutteMat[  5][  1] =       4; 
                                tutteMat[  6][  0] =       6; 
                                tutteMat[  7][  0] =       1; 
                             } /* 9 */
                             break;   
                          } /* 7 */
                     } /* 6 */
                 }   /* 4 CASE THREE  */
        
                 break;
            }  /* 2 */
       }   /* 1 */
    break;
           } /* f */
       } /* e */
break;
default:
{
printf("sevenpart43\n");
}
break; 
  }  /* b */

} /* end sevenpart43 */  

/*                                            */
/*           end of sevenpart43                */
/*                                            */
/**********************************************/


