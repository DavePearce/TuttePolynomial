#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3drb2          */
/*                                            */
 
 
/* 

Precondition: g is a simple seven vertex graph with 15 edges 
              degseq is 12220
              tutteMat and tutteMatX are arrays with 
              values for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte 
               poly of this graph

*/ 

void
sevenpart3drb2(
               struct graph *g,
               int degseq,
               TUTTE tutteMat,
               TUTTEO tutteMatX
              )


{
int d31,            /* location on vertex list of vertices of degree 3  */
    d32, 
    no51,           /* number of vertices of degree 5 adjacent to       */
    no52,           /*			  vertices of degree 3          */  
    vt,             /* location on vertex list                          */
    sum;

//printf("sevenpart3drb2\n");


switch(degseq)
{  /* 1 */

case 12220:/* use the sum of the degrees of the neighbors of
              the two vertices of degree 3. If the test fails,
              find out how many vertices of degree 5 are
              adjacent to each of the vertices of degree 3 */
{/*printf("12220\n"); */
 vt = firstVertex(g);
  d31 = nextofdegree(
                     g,
                     &vt,
                     THREE)
                    ;
  d32 = nextofdegree(
                     g,
                     &vt,
                     THREE)
                    ;
 no51 = nodegnadjtov(
                     g,
                     d31,
                     FIVE
                    );
                    
 no52 = nodegnadjtov(
                     g,
                     d32,
                     FIVE
                    );
 sum = degreesofnhbrs(g,d31) +  degreesofnhbrs(g,d32);
 switch( sum )
  {
   case 28:
    { /* G1192 */ /*printf("spt36\n");*/
/*
W0985
*/
/*

******************* reading edge list *************




(  2,  7) (  1,  2) (  3,  4) (  1,  6) (  3,  5) (  4,  5) (  3,  7) 
(  5,  7) (  4,  7) (  4,  6) (  3,  6) (  2,  5) (  5,  6) (  1,  7) 
(  6,  7) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              18      51      57      32       9       1 
I =   1      18      94     126      67      13 
I =   2      61     153     105      23 
I =   3      94     133      50       5 
I =   4      94      81      17 
I =   5      71      36       4 
I =   6      42      11       1 
I =   7      19       2 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      18; 
tutteMat[  0][  2] =      51; 
tutteMat[  0][  3] =      57; 
tutteMat[  0][  4] =      32; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      18; 
tutteMat[  1][  1] =      94; 
tutteMat[  1][  2] =     126; 
tutteMat[  1][  3] =      67; 
tutteMat[  1][  4] =      13; 
tutteMat[  2][  0] =      61; 
tutteMat[  2][  1] =     153; 
tutteMat[  2][  2] =     105; 
tutteMat[  2][  3] =      23; 
tutteMat[  3][  0] =      94; 
tutteMat[  3][  1] =     133; 
tutteMat[  3][  2] =      50; 
tutteMat[  3][  3] =       5; 
tutteMat[  4][  0] =      94; 
tutteMat[  4][  1] =      81; 
tutteMat[  4][  2] =      17; 
tutteMat[  5][  0] =      71; 
tutteMat[  5][  1] =      36; 
tutteMat[  5][  2] =       4; 
tutteMat[  6][  0] =      42; 
tutteMat[  6][  1] =      11; 
tutteMat[  6][  2] =       1; 
tutteMat[  7][  0] =      19; 
tutteMat[  7][  1] =       2; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

     
    } 
   break;
   case 31:
    { /* G1189 */ /*printf("spt37\n");*/
/*
W0981
*//*printf("A\n");*/
/*

******************* reading edge list *************




(  2,  6) (  4,  5) (  1,  5) (  2,  7) (  1,  7) (  1,  6) (  3,  6) 
(  6,  7) (  3,  5) (  5,  6) (  2,  4) (  3,  7) (  4,  7) (  5,  7) 
(  3,  4) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              20      56      61      33       9       1 
I =   1      20     101     132      67      12 
I =   2      65     159     108      22 
I =   3      97     138      50       3 
I =   4      95      85      15 
I =   5      71      39       2 
I =   6      42      12 
I =   7      19       2 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      20; 
tutteMat[  0][  2] =      56; 
tutteMat[  0][  3] =      61; 
tutteMat[  0][  4] =      33; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      20; 
tutteMat[  1][  1] =     101; 
tutteMat[  1][  2] =     132; 
tutteMat[  1][  3] =      67; 
tutteMat[  1][  4] =      12; 
tutteMat[  2][  0] =      65; 
tutteMat[  2][  1] =     159; 
tutteMat[  2][  2] =     108; 
tutteMat[  2][  3] =      22; 
tutteMat[  3][  0] =      97; 
tutteMat[  3][  1] =     138; 
tutteMat[  3][  2] =      50; 
tutteMat[  3][  3] =       3; 
tutteMat[  4][  0] =      95; 
tutteMat[  4][  1] =      85; 
tutteMat[  4][  2] =      15; 
tutteMat[  5][  0] =      71; 
tutteMat[  5][  1] =      39; 
tutteMat[  5][  2] =       2; 
tutteMat[  6][  0] =      42; 
tutteMat[  6][  1] =      12; 
tutteMat[  7][  0] =      19; 
tutteMat[  7][  1] =       2; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

    
    } 
   break;
   case 32:
    { /* G1193 */ /*printf("spt38\n");*/
/*
W0980
*/
/*printf("B\n");*/
/*

******************* reading edge list *************




(  2,  5) (  2,  7) (  1,  7) (  3,  5) (  2,  6) (  3,  4) (  1,  6) 
(  1,  5) (  3,  7) (  4,  5) (  4,  7) (  3,  6) (  4,  6) (  5,  7) 
(  6,  7) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              22      61      65      34       9       1 
I =   1      22     107     136      66      11 
I =   2      68     162     109      21 
I =   3      98     141      50       2 
I =   4      95      88      13 
I =   5      71      40       1 
I =   6      42      12 
I =   7      19       2 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      22; 
tutteMat[  0][  2] =      61; 
tutteMat[  0][  3] =      65; 
tutteMat[  0][  4] =      34; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      22; 
tutteMat[  1][  1] =     107; 
tutteMat[  1][  2] =     136; 
tutteMat[  1][  3] =      66; 
tutteMat[  1][  4] =      11; 
tutteMat[  2][  0] =      68; 
tutteMat[  2][  1] =     162; 
tutteMat[  2][  2] =     109; 
tutteMat[  2][  3] =      21; 
tutteMat[  3][  0] =      98; 
tutteMat[  3][  1] =     141; 
tutteMat[  3][  2] =      50; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =      95; 
tutteMat[  4][  1] =      88; 
tutteMat[  4][  2] =      13; 
tutteMat[  5][  0] =      71; 
tutteMat[  5][  1] =      40; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      42; 
tutteMat[  6][  1] =      12; 
tutteMat[  7][  0] =      19; 
tutteMat[  7][  1] =       2; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

     
    } 
   break;
   case 30:
    { 
     if( ( no51 == ONE ) && ( no52 == ONE ) )
      { /* G1190 */ /*printf("spt330\n");*/
/*
W0982
*/
/* printf("C\n");*/
/*

******************* reading edge list *************




(  2,  3) (  1,  4) (  4,  5) (  2,  5) (  2,  7) (  4,  7) (  3,  6) 
(  1,  6) (  4,  6) (  5,  6) (  5,  7) (  3,  5) (  6,  7) (  1,  7) 
(  3,  7) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              16      48      56      32       9       1 
I =   1      16      88     126      69      13 
I =   2      56     152     111      23 
I =   3      90     139      51       4 
I =   4      93      85      16 
I =   5      71      38       3 
I =   6      42      12 
I =   7      19       2 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      16; 
tutteMat[  0][  2] =      48; 
tutteMat[  0][  3] =      56; 
tutteMat[  0][  4] =      32; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      16; 
tutteMat[  1][  1] =      88; 
tutteMat[  1][  2] =     126; 
tutteMat[  1][  3] =      69; 
tutteMat[  1][  4] =      13; 
tutteMat[  2][  0] =      56; 
tutteMat[  2][  1] =     152; 
tutteMat[  2][  2] =     111; 
tutteMat[  2][  3] =      23; 
tutteMat[  3][  0] =      90; 
tutteMat[  3][  1] =     139; 
tutteMat[  3][  2] =      51; 
tutteMat[  3][  3] =       4; 
tutteMat[  4][  0] =      93; 
tutteMat[  4][  1] =      85; 
tutteMat[  4][  2] =      16; 
tutteMat[  5][  0] =      71; 
tutteMat[  5][  1] =      38; 
tutteMat[  5][  2] =       3; 
tutteMat[  6][  0] =      42; 
tutteMat[  6][  1] =      12; 
tutteMat[  7][  0] =      19; 
tutteMat[  7][  1] =       2; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

       
      } 
     else     
/* another & instead of && found-may not have used this option */
      if( ( ( no51 == ZERO ) && ( no52 == TWO ) ) 
               || ( ( no51 == TWO ) && ( no52 == ZERO ) ) )
       { /* G1191 */printf("spt31\n");
/*
W0983
*//*printf("D\n");*/
/*

******************* reading edge list *************




(  1,  5) (  2,  3) (  1,  6) (  2,  4) (  3,  6) (  3,  7) (  5,  6) 
(  5,  7) (  4,  5) (  1,  7) (  3,  5) (  4,  6) (  6,  7) (  2,  7) 
(  4,  7) 


VERTICES =      7 EDGES =     15

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              20      56      61      33       9       1 
I =   1      20     101     131      66      12 
I =   2      65     158     106      23 
I =   3      97     136      50       3 
I =   4      95      83      16 
I =   5      71      38       3 
I =   6      42      12 
I =   7      19       2 
I =   8       6 
I =   9       1 
*/
tutteMat[  0][  1] =      20; 
tutteMat[  0][  2] =      56; 
tutteMat[  0][  3] =      61; 
tutteMat[  0][  4] =      33; 
tutteMat[  0][  5] =       9; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      20; 
tutteMat[  1][  1] =     101; 
tutteMat[  1][  2] =     131; 
tutteMat[  1][  3] =      66; 
tutteMat[  1][  4] =      12; 
tutteMat[  2][  0] =      65; 
tutteMat[  2][  1] =     158; 
tutteMat[  2][  2] =     106; 
tutteMat[  2][  3] =      23; 
tutteMat[  3][  0] =      97; 
tutteMat[  3][  1] =     136; 
tutteMat[  3][  2] =      50; 
tutteMat[  3][  3] =       3; 
tutteMat[  4][  0] =      95; 
tutteMat[  4][  1] =      83; 
tutteMat[  4][  2] =      16; 
tutteMat[  5][  0] =      71; 
tutteMat[  5][  1] =      38; 
tutteMat[  5][  2] =       3; 
tutteMat[  6][  0] =      42; 
tutteMat[  6][  1] =      12; 
tutteMat[  7][  0] =      19; 
tutteMat[  7][  1] =       2; 
tutteMat[  8][  0] =       6; 
tutteMat[  9][  0] =       1; 

        
       } 
    } 
   break;
  } 
 } 
break;

default:
  {
     printf("sevenpart3drb2\n");
     break;
  }


} /*  end switch on degseq */
}  /* end sevenpart3drb2 */

/*                                            */
/*           end of sevenpart3drb2            */
/*                                            */
/**********************************************/




