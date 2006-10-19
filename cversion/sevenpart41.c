#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart4              */
/*                                            */
 

/*

Precondition: g is a simple seven vertex graph with 13 edges
              the degree sequence of a valid graph here is 11050
              tutteMat and tutteMatX are arrays with
              values for current state of this computation 

Postcondition: tutteMat and tutteMatX augmented by the tutte
               poly of this graph

*/

void
sevenpart41(
            struct graph *g,
            TUTTE tutteMat,
            TUTTEO tutteMatX
           )

{

printf("sevenpart41\n");
/* this is case 11050: since there is only one graph we do not have 
   to compute the degree sequence but can just enter the tutte polynomial */
/*
W0836
*/
/*
w0836


******************* reading edge list *************




(  1,  6) (  2,  6) (  3,  4) (  2,  7) (  1,  5) (  1,  7) (  2,  5) 
(  5,  7) (  4,  6) (  4,  7) (  3,  6) (  3,  7) (  6,  7) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               6      21      29      20       7       1 
I =   1       6      35      56      35       8 
I =   2      20      57      44      11 
I =   3      29      45      18       1 
I =   4      26      22       3 
I =   5      16       5 
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
tutteMat[  1][  1] =      35; 
tutteMat[  1][  2] =      56; 
tutteMat[  1][  3] =      35; 
tutteMat[  1][  4] =       8; 
tutteMat[  2][  0] =      20; 
tutteMat[  2][  1] =      57; 
tutteMat[  2][  2] =      44; 
tutteMat[  2][  3] =      11; 
tutteMat[  3][  0] =      29; 
tutteMat[  3][  1] =      45; 
tutteMat[  3][  2] =      18; 
tutteMat[  3][  3] =       1; 
tutteMat[  4][  0] =      26; 
tutteMat[  4][  1] =      22; 
tutteMat[  4][  2] =       3; 
tutteMat[  5][  0] =      16; 
tutteMat[  5][  1] =       5; 
tutteMat[  6][  0] =       6; 
tutteMat[  7][  0] =       1; 



} /* end sevenpart41.c */  

/*                                            */
/*           end of sevenpart41               */
/*                                            */
/**********************************************/


