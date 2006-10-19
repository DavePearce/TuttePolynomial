#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart45             */
/*                                            */
 

/* 

Precondition: g is a simple seven vertex graph with 13 edges 
              degseq is 520 
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart45(
            struct graph *g,
            TUTTE tutteMat,
            TUTTEO tutteMatX
           )
{
int vt,              /* location of vertex on vertex list               */  
    d31,             /* location on vertex list of vertices of degree 3 */
    d32,
    d31a,
    d31b,
    ne1;            /* location on edge list                            */




/*case 520:
{*/ /* start 520 */ /*printf("520\n");*/

vt = firstVertex(g);  //(*g).vrtx[ZERO].nvert;
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
  {
     switch( commonadj(g,d31,d32) )
       {
          case ONE:
            {
       /* G1103 *//*printf("spt7424\n");*/
 /*
W0894
*/
/*
w0894

******************* reading edge list *************




(  2,  5) (  1,  6) (  4,  7) (  3,  6) (  2,  7) (  3,  4) (  3,  5) 
(  1,  2) (  1,  7) (  4,  5) (  4,  6) (  3,  7) (  5,  6) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              14      37      39      22       7       1 
I =   1      14      64      73      33       6 
I =   2      41      81      39       5 
I =   3      51      47       8       1 
I =   4      38      15       1 
I =   5      19       2 
I =   6       6 
I =   7       1 
*/
              tutteMat[  0][  1] =      14; 
              tutteMat[  0][  2] =      37; 
              tutteMat[  0][  3] =      39; 
              tutteMat[  0][  4] =      22; 
              tutteMat[  0][  5] =       7; 
              tutteMat[  0][  6] =       1; 
              tutteMat[  1][  0] =      14; 
              tutteMat[  1][  1] =      64; 
              tutteMat[  1][  2] =      73; 
              tutteMat[  1][  3] =      33; 
              tutteMat[  1][  4] =       6; 
              tutteMat[  2][  0] =      41; 
              tutteMat[  2][  1] =      81; 
              tutteMat[  2][  2] =      39; 
              tutteMat[  2][  3] =       5; 
              tutteMat[  3][  0] =      51; 
              tutteMat[  3][  1] =      47; 
              tutteMat[  3][  2] =       8; 
              tutteMat[  3][  3] =       1; 
              tutteMat[  4][  0] =      38; 
              tutteMat[  4][  1] =      15; 
              tutteMat[  4][  2] =       1; 
              tutteMat[  5][  0] =      19; 
              tutteMat[  5][  1] =       2; 
              tutteMat[  6][  0] =       6; 
              tutteMat[  7][  0] =       1; 
           }
          break;

         case ZERO:
           {
              ne1 = firstEdge(
                              g, 
                              d31
                             );  //(*g).edg[(*g).vrtx[d31].fedge].front;
              d31a = nextdegnadjtov(
                                    g,
                                    &ne1,
                                    FOUR
                                   );      
              d31b = nextdegnadjtov(
                                    g,
                                    &ne1,
                                    FOUR
                                   );      
              if( isadj(d31a,d31b,g) ) 
                { /* G1104 */ /*printf("spt7425\n");*/
/*
W0896
*/
/*
w0896

******************* reading edge list *************




(  3,  5) (  1,  2) (  3,  4) (  3,  7) (  5,  6) (  1,  6) (  1,  7) 
(  4,  5) (  3,  6) (  2,  4) (  4,  7) (  2,  5) (  6,  7) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              14      37      39      22       7       1 
I =   1      14      65      74      33       6 
I =   2      42      83      39       6 
I =   3      53      47       8 
I =   4      39      14       1 
I =   5      19       2 
I =   6       6 
I =   7       1 
*/
                  tutteMat[  0][  1] =      14; 
                  tutteMat[  0][  2] =      37; 
                  tutteMat[  0][  3] =      39; 
                  tutteMat[  0][  4] =      22; 
                  tutteMat[  0][  5] =       7; 
                  tutteMat[  0][  6] =       1; 
                  tutteMat[  1][  0] =      14; 
                  tutteMat[  1][  1] =      65; 
                  tutteMat[  1][  2] =      74; 
                  tutteMat[  1][  3] =      33; 
                  tutteMat[  1][  4] =       6; 
                  tutteMat[  2][  0] =      42; 
                  tutteMat[  2][  1] =      83; 
                  tutteMat[  2][  2] =      39; 
                  tutteMat[  2][  3] =       6; 
                  tutteMat[  3][  0] =      53; 
                  tutteMat[  3][  1] =      47; 
                  tutteMat[  3][  2] =       8; 
                  tutteMat[  4][  0] =      39; 
                  tutteMat[  4][  1] =      14; 
                  tutteMat[  4][  2] =       1; 
                  tutteMat[  5][  0] =      19; 
                  tutteMat[  5][  1] =       2; 
                  tutteMat[  6][  0] =       6; 
                  tutteMat[  7][  0] =       1; 
               }
             else     
               { /* G1105 *//*printf("spt7426\n");*/
/*
W0897
*/
/*
w0897

******************* reading edge list *************




(  2,  4) (  3,  6) (  5,  6) (  3,  5) (  1,  6) (  4,  7) (  3,  7) 
(  4,  6) (  2,  5) (  1,  2) (  1,  7) (  5,  7) (  3,  4) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              17      44      45      24       7       1 
I =   1      17      74      78      31       4 
I =   2      47      85      36       4 
I =   3      55      45       8 
I =   4      39      14       1 
I =   5      19       2 
I =   6       6 
I =   7       1 
*/
                  tutteMat[  0][  1] =      17; 
                  tutteMat[  0][  2] =      44; 
                  tutteMat[  0][  3] =      45; 
                  tutteMat[  0][  4] =      24; 
                  tutteMat[  0][  5] =       7; 
                  tutteMat[  0][  6] =       1; 
                  tutteMat[  1][  0] =      17; 
                  tutteMat[  1][  1] =      74; 
                  tutteMat[  1][  2] =      78; 
                  tutteMat[  1][  3] =      31; 
                  tutteMat[  1][  4] =       4; 
                  tutteMat[  2][  0] =      47; 
                  tutteMat[  2][  1] =      85; 
                  tutteMat[  2][  2] =      36; 
                  tutteMat[  2][  3] =       4; 
                  tutteMat[  3][  0] =      55; 
                  tutteMat[  3][  1] =      45; 
                  tutteMat[  3][  2] =       8; 
                  tutteMat[  4][  0] =      39; 
                  tutteMat[  4][  1] =      14; 
                  tutteMat[  4][  2] =       1; 
                  tutteMat[  5][  0] =      19; 
                  tutteMat[  5][  1] =       2; 
                  tutteMat[  6][  0] =       6; 
                  tutteMat[  7][  0] =       1; 
               }
        }
        break;
      } /* switch */
  } /* true if */
else
  {
    switch( commonadj(g,d31,d32) )
      {
         case ONE:
           {  
              if( commonadj(g,d31,nextcommonadj(g,d31,d32)) == ONE )
                { /* G1101 */ /*printf("spt7427\n");*/
/*
W0892
*/
/*
w0892

******************* reading edge list *************




(  2,  7) (  4,  6) (  3,  4) (  4,  5) (  2,  4) (  1,  6) (  3,  7) 
(  1,  5) (  2,  3) (  5,  6) (  3,  6) (  5,  7) (  1,  7) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              12      34      38      22       7       1 
I =   1      12      60      75      35       6 
I =   2      38      84      43       5 
I =   3      51      51       7 
I =   4      39      15 
I =   5      19       2 
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
                   tutteMat[  1][  1] =      60; 
                   tutteMat[  1][  2] =      75; 
                   tutteMat[  1][  3] =      35; 
                   tutteMat[  1][  4] =       6; 
                   tutteMat[  2][  0] =      38; 
                   tutteMat[  2][  1] =      84; 
                   tutteMat[  2][  2] =      43; 
                   tutteMat[  2][  3] =       5; 
                   tutteMat[  3][  0] =      51; 
                   tutteMat[  3][  1] =      51; 
                   tutteMat[  3][  2] =       7; 
                   tutteMat[  4][  0] =      39; 
                   tutteMat[  4][  1] =      15; 
                   tutteMat[  5][  0] =      19; 
                   tutteMat[  5][  1] =       2; 
                   tutteMat[  6][  0] =       6; 
                   tutteMat[  7][  0] =       1; 
                }
              else
                {
                     /* G1102  *//*printf("spt7428\n");*/
/*
W0893
*/
/*
w0893

******************* reading edge list *************




(  2,  4) (  3,  7) (  1,  7) (  3,  5) (  2,  3) (  2,  7) (  3,  6) 
(  4,  7) (  5,  6) (  4,  5) (  1,  6) (  1,  5) (  4,  6) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              14      38      41      23       7       1 
I =   1      14      65      76      34       5 
I =   2      41      84      42       4 
I =   3      52      50       7 
I =   4      39      15 
I =   5      19       2 
I =   6       6 
I =   7       1 
*/
                   tutteMat[  0][  1] =      14; 
                   tutteMat[  0][  2] =      38; 
                   tutteMat[  0][  3] =      41; 
                   tutteMat[  0][  4] =      23; 
                   tutteMat[  0][  5] =       7; 
                   tutteMat[  0][  6] =       1; 
                   tutteMat[  1][  0] =      14; 
                   tutteMat[  1][  1] =      65; 
                   tutteMat[  1][  2] =      76; 
                   tutteMat[  1][  3] =      34; 
                   tutteMat[  1][  4] =       5; 
                   tutteMat[  2][  0] =      41; 
                   tutteMat[  2][  1] =      84; 
                   tutteMat[  2][  2] =      42; 
                   tutteMat[  2][  3] =       4; 
                   tutteMat[  3][  0] =      52; 
                   tutteMat[  3][  1] =      50; 
                   tutteMat[  3][  2] =       7; 
                   tutteMat[  4][  0] =      39; 
                   tutteMat[  4][  1] =      15; 
                   tutteMat[  5][  0] =      19; 
                   tutteMat[  5][  1] =       2; 
                   tutteMat[  6][  0] =       6; 
                   tutteMat[  7][  0] =       1; 
                } 
           }
           break;
         case THREE:
           {     
              /* G1106 *//* printf("spt7429\n");*/
/*
W0898
*/
/*
w0898

******************* reading edge list *************




(  4,  5) (  2,  6) (  2,  7) (  4,  7) (  1,  5) (  1,  6) (  2,  5) 
(  3,  4) (  3,  7) (  3,  5) (  4,  6) (  1,  7) (  3,  6) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              18      47      48      25       7       1 
I =   1      18      77      81      30       3 
I =   2      48      87      36       3 
I =   3      55      47       7 
I =   4      39      15 
I =   5      19       2 
I =   6       6 
I =   7       1 
*/
              tutteMat[  0][  1] =      18; 
              tutteMat[  0][  2] =      47; 
              tutteMat[  0][  3] =      48; 
              tutteMat[  0][  4] =      25; 
              tutteMat[  0][  5] =       7; 
              tutteMat[  0][  6] =       1; 
              tutteMat[  1][  0] =      18; 
              tutteMat[  1][  1] =      77; 
              tutteMat[  1][  2] =      81; 
              tutteMat[  1][  3] =      30; 
              tutteMat[  1][  4] =       3; 
              tutteMat[  2][  0] =      48; 
              tutteMat[  2][  1] =      87; 
              tutteMat[  2][  2] =      36; 
              tutteMat[  2][  3] =       3; 
              tutteMat[  3][  0] =      55; 
              tutteMat[  3][  1] =      47; 
              tutteMat[  3][  2] =       7; 
              tutteMat[  4][  0] =      39; 
              tutteMat[  4][  1] =      15; 
              tutteMat[  5][  0] =      19; 
              tutteMat[  5][  1] =       2; 
              tutteMat[  6][  0] =       6; 
              tutteMat[  7][  0] =       1; 
           }
           break;
         case TWO:
           {
             /* G1100 *//*printf("spt7430\n");*/
/*
W0895
*/
/*
w0895

******************* reading edge list *************




(  1,  6) (  1,  7) (  2,  4) (  1,  5) (  5,  6) (  2,  6) (  3,  4) 
(  3,  5) (  3,  7) (  4,  5) (  2,  7) (  3,  6) (  4,  7) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              15      40      42      23       7       1 
I =   1      15      68      77      33       5 
I =   2      43      85      40       4 
I =   3      53      49       7 
I =   4      39      15 
I =   5      19       2 
I =   6       6 
I =   7       1 
*/
             tutteMat[  0][  1] =      15; 
             tutteMat[  0][  2] =      40; 
             tutteMat[  0][  3] =      42; 
             tutteMat[  0][  4] =      23; 
             tutteMat[  0][  5] =       7; 
             tutteMat[  0][  6] =       1; 
             tutteMat[  1][  0] =      15; 
             tutteMat[  1][  1] =      68; 
             tutteMat[  1][  2] =      77; 
             tutteMat[  1][  3] =      33; 
             tutteMat[  1][  4] =       5; 
             tutteMat[  2][  0] =      43; 
             tutteMat[  2][  1] =      85; 
             tutteMat[  2][  2] =      40; 
             tutteMat[  2][  3] =       4; 
             tutteMat[  3][  0] =      53; 
             tutteMat[  3][  1] =      49; 
             tutteMat[  3][  2] =       7; 
             tutteMat[  4][  0] =      39; 
             tutteMat[  4][  1] =      15; 
             tutteMat[  5][  0] =      19; 
             tutteMat[  5][  1] =       2; 
             tutteMat[  6][  0] =       6; 
             tutteMat[  7][  0] =       1; 
          } 
           break;
       } /*  end switch */

  } /* else */



 /* end 520 case */


 /* end degseq switch */


} /* end sevenpart45 */  

/*                                            */
/*           end of sevenpart45               */
/*                                            */
/**********************************************/


