#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart11             */
/*                                            */
 
/*
Precondition: g is a simple graph with seven vertices and 19, 20, or 21 edges
              degseq is 70000, 52000, or 34000
              tutteMat and tutteMatX are arrays with values
              for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte
               poly of this graph

*/
 
void
sevenpart11(struct Graph *g,int degseq,TUTTE tutteMat,TUTTEO tutteMatX)
{
int     /* variables used to calculate degree sequence */
    i,
    deg[VERTEXSIZE],
    vt;
//printf("sevenparty11\n");

switch( degseq )
  {  

     case 70000:/* degree */ 
       {
/*
W1044
*/

/*
(  1,  7) (  1,  5) (  1,  3) (  1,  2) (  4,  5) (  1,  4) (  3,  4) 
(  2,  3) (  2,  6) (  3,  7) (  5,  7) (  2,  4) (  3,  5) (  6,  7) 
(  2,  5) (  4,  7) (  4,  6) (  5,  6) (  3,  6) (  1,  6) (  2,  7) 



VERTICES =      7 EDGES =     21

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0             120     274     225      85      15       1 
I =   1     120     644     721     280      35 
I =   2     490    1225     700     105 
I =   3     945    1330     420      35 
I =   4    1225    1085     210 
I =   5    1260     756      84 
I =   6    1120     469      21 
I =   7     895     245 
I =   8     645     105 
I =   9     420      35 
I =  10     245       7 
I =  11     126 
I =  12      56 
I =  13      21 
I =  14       6 
I =  15       1 
*/
        tutteMat[  0][  1] =     120; 
        tutteMat[  0][  2] =     274; 
        tutteMat[  0][  3] =     225; 
        tutteMat[  0][  4] =      85; 
        tutteMat[  0][  5] =      15; 
        tutteMat[  0][  6] =       1; 
        tutteMat[  1][  0] =     120; 
        tutteMat[  1][  1] =     644; 
        tutteMat[  1][  2] =     721; 
        tutteMat[  1][  3] =     280; 
        tutteMat[  1][  4] =      35; 
        tutteMat[  2][  0] =     490; 
        tutteMat[  2][  1] =    1225; 
        tutteMat[  2][  2] =     700; 
        tutteMat[  2][  3] =     105; 
        tutteMat[  3][  0] =     945; 
        tutteMat[  3][  1] =    1330; 
        tutteMat[  3][  2] =     420; 
        tutteMat[  3][  3] =      35; 
        tutteMat[  4][  0] =    1225; 
        tutteMat[  4][  1] =    1085; 
        tutteMat[  4][  2] =     210; 
        tutteMat[  5][  0] =    1260; 
        tutteMat[  5][  1] =     756; 
        tutteMat[  5][  2] =      84; 
        tutteMat[  6][  0] =    1120; 
        tutteMat[  6][  1] =     469; 
        tutteMat[  6][  2] =      21; 
        tutteMat[  7][  0] =     895; 
        tutteMat[  7][  1] =     245; 
        tutteMat[  8][  0] =     645; 
        tutteMat[  8][  1] =     105; 
        tutteMat[  9][  0] =     420; 
        tutteMat[  9][  1] =      35; 
        tutteMat[ 10][  0] =     245; 
        tutteMat[ 10][  1] =       7; 
        tutteMat[ 11][  0] =     126; 
        tutteMat[ 12][  0] =      56; 
        tutteMat[ 13][  0] =      21; 
        tutteMat[ 14][  0] =       6; 
        tutteMat[ 15][  0] =       1; 
      }  /* end g.e==48 */
      break;

    case 52000: /* degree */
      {  /* G1251 */ /* printf("spt1b\n");*/
/*
W1043
*/
/*
(  1,  5) (  3,  7) (  3,  5) (  1,  7) (  2,  5) (  2,  7) (  6,  7) 
(  1,  6) (  3,  6) (  5,  7) (  1,  4) (  1,  3) (  4,  5) (  3,  4) 
(  4,  6) (  2,  6) (  5,  6) (  4,  7) (  2,  4) (  2,  3) 


VERTICES =      7 EDGES =     20

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              96     224     190      75      14       1 
I =   1      96     508     576     230      30 
I =   2     380     940     545      85 
I =   3     710     990     315      25 
I =   4     890     780     150 
I =   5     884     522      54 
I =   6     756     303      11 
I =   7     575     145 
I =   8     390      55 
I =   9     235      15 
I =  10     124       2 
I =  11      56 
I =  12      21 
I =  13       6 
I =  14       1 
*/
          tutteMat[  0][  1] =      96; 
          tutteMat[  0][  2] =     224; 
          tutteMat[  0][  3] =     190; 
          tutteMat[  0][  4] =      75; 
          tutteMat[  0][  5] =      14; 
          tutteMat[  0][  6] =       1; 
          tutteMat[  1][  0] =      96; 
          tutteMat[  1][  1] =     508; 
          tutteMat[  1][  2] =     576; 
          tutteMat[  1][  3] =     230; 
          tutteMat[  1][  4] =      30; 
          tutteMat[  2][  0] =     380; 
          tutteMat[  2][  1] =     940; 
          tutteMat[  2][  2] =     545; 
          tutteMat[  2][  3] =      85; 
          tutteMat[  3][  0] =     710; 
          tutteMat[  3][  1] =     990; 
          tutteMat[  3][  2] =     315; 
          tutteMat[  3][  3] =      25; 
          tutteMat[  4][  0] =     890; 
          tutteMat[  4][  1] =     780; 
          tutteMat[  4][  2] =     150; 
          tutteMat[  5][  0] =     884; 
          tutteMat[  5][  1] =     522; 
          tutteMat[  5][  2] =      54; 
          tutteMat[  6][  0] =     756; 
          tutteMat[  6][  1] =     303; 
          tutteMat[  6][  2] =      11; 
          tutteMat[  7][  0] =     575; 
          tutteMat[  7][  1] =     145; 
          tutteMat[  8][  0] =     390; 
          tutteMat[  8][  1] =      55; 
          tutteMat[  9][  0] =     235; 
          tutteMat[  9][  1] =      15; 
          tutteMat[ 10][  0] =     124; 
          tutteMat[ 10][  1] =       2; 
          tutteMat[ 11][  0] =      56; 
          tutteMat[ 12][  0] =      21; 
          tutteMat[ 13][  0] =       6; 
          tutteMat[ 14][  0] =       1; 
       }  /* end g.e==46 */
       break;

    case 34000:/* degree */
      {  /* G1250 */ /* printf("spt1c\n");*/
/*
W1042
*/
/*
(  1,  4) (  2,  7) (  1,  5) (  4,  5) (  2,  6) (  1,  3) (  2,  4) 
(  4,  6) (  1,  7) (  1,  6) (  3,  5) (  6,  7) (  3,  7) (  2,  3) 
(  5,  6) (  2,  5) (  4,  7) (  5,  7) (  3,  6) 


VERTICES =      7 EDGES =     19

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              78     185     161      66      13       1 
I =   1      78     406     462     187      25 
I =   2     299     727     420      66 
I =   3     540     736     228      16 
I =   4     652     551      99 
I =   5     621     345      30 
I =   6     505     181       4 
I =   7     360      75 
I =   8     225      23 
I =   9     122       4 
I =  10      56 
I =  11      21 
I =  12       6 
I =  13       1 
*/
         tutteMat[  0][  1] =      78; 
         tutteMat[  0][  2] =     185; 
         tutteMat[  0][  3] =     161; 
         tutteMat[  0][  4] =      66; 
         tutteMat[  0][  5] =      13; 
         tutteMat[  0][  6] =       1; 
         tutteMat[  1][  0] =      78; 
         tutteMat[  1][  1] =     406; 
         tutteMat[  1][  2] =     462; 
         tutteMat[  1][  3] =     187; 
         tutteMat[  1][  4] =      25; 
         tutteMat[  2][  0] =     299; 
         tutteMat[  2][  1] =     727; 
         tutteMat[  2][  2] =     420; 
         tutteMat[  2][  3] =      66; 
         tutteMat[  3][  0] =     540; 
         tutteMat[  3][  1] =     736; 
         tutteMat[  3][  2] =     228; 
         tutteMat[  3][  3] =      16; 
         tutteMat[  4][  0] =     652; 
         tutteMat[  4][  1] =     551; 
         tutteMat[  4][  2] =      99; 
         tutteMat[  5][  0] =     621; 
         tutteMat[  5][  1] =     345; 
         tutteMat[  5][  2] =      30; 
         tutteMat[  6][  0] =     505; 
         tutteMat[  6][  1] =     181; 
         tutteMat[  6][  2] =       4; 
         tutteMat[  7][  0] =     360; 
         tutteMat[  7][  1] =      75; 
         tutteMat[  8][  0] =     225; 
         tutteMat[  8][  1] =      23; 
         tutteMat[  9][  0] =     122; 
         tutteMat[  9][  1] =       4; 
         tutteMat[ 10][  0] =      56; 
         tutteMat[ 11][  0] =      21; 
         tutteMat[ 12][  0] =       6; 
         tutteMat[ 13][  0] =       1; 
      } 
      break;

default:
{
printf("sevenpart11\n");
break;
}

  } /* 1 end switch on degseq */

}  /* end sevenpart11 */

/*                                            */
/*           end of sevenpart11                */
/*                                            */
/**********************************************/





