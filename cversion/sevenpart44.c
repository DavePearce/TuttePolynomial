#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart4              */
/*                                            */
 


/*

Precondition: g is a simple seven vertex graph with 13 edges
              a valid degree sequence is 1330
              tutteMat and tutteMatX are arrays with
              values for current state of this computation  

Postcondition: tutteMat and tutteMatX augmented by the tutte
               poly of this graph

*/

void
sevenpart44(
            struct graph *g,
            TUTTE tutteMat,
            TUTTEO tutteMatX
           )

{
int vt,              /* location of vertex on vertex list               */ 
    no1,             /* number of degree one vertices after deletions   */
    d21,             /* location on vertex list of vertices of degree 2 */
    d22, 
    d31,             /* location on vertex list of vertices of degree 3 */
    d32,
    d33,
    d31a,
    d32b,
    d51,            /* location on vertex list of vertices of degree 5  */
    com1,           /* number of common adjacencies for pairs of 
    			vertices of degree 3                             */
    com2,
    com3,
    com4;

//printf("sevenpart44 from tutte64\n");

vt = firstVertex(g);  //(*g).vrtx[ZERO].nvert;;
d31 = nextofdegree(g,&vt,THREE);
d32 = nextofdegree(g,&vt,THREE);
d33 = nextofdegree(g,&vt,THREE);
com1 = commonadj(g,d31,d32);
com2 = commonadj(g,d31,d33);
com3 = commonadj(g,d32,d33);
com4 = com1 * com1 + com2 * com2 + com3 * com3;

switch( com4 )
  {
     case 17: 
       { /* G1092  *//*printf("spt7413\n");*/
/*
W0882
*/
/*
w0882

                                                                                              
printf("W0882\n") ;                                                                                             

******************* reading edge list *************




(  4,  6) (  1,  6) (  3,  4) (  1,  7) (  2,  6) (  3,  6) (  2,  5) 
(  2,  7) (  3,  7) (  4,  5) (  1,  5) (  5,  7) (  4,  7) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              13      37      41      23       7       1 
I =   1      13      61      74      33       5 
I =   2      37      79      42       5 
I =   3      46      50       9 
I =   4      35      18 
I =   5      18       3 
I =   6       6 
I =   7       1 
*/
         tutteMat[  0][  1] =      13; 
         tutteMat[  0][  2] =      37; 
         tutteMat[  0][  3] =      41; 
         tutteMat[  0][  4] =      23; 
         tutteMat[  0][  5] =       7; 
         tutteMat[  0][  6] =       1; 
         tutteMat[  1][  0] =      13; 
         tutteMat[  1][  1] =      61; 
         tutteMat[  1][  2] =      74; 
         tutteMat[  1][  3] =      33; 
         tutteMat[  1][  4] =       5; 
         tutteMat[  2][  0] =      37; 
         tutteMat[  2][  1] =      79; 
         tutteMat[  2][  2] =      42; 
         tutteMat[  2][  3] =       5; 
         tutteMat[  3][  0] =      46; 
         tutteMat[  3][  1] =      50; 
         tutteMat[  3][  2] =       9; 
         tutteMat[  4][  0] =      35; 
         tutteMat[  4][  1] =      18; 
         tutteMat[  5][  0] =      18; 
         tutteMat[  5][  1] =       3; 
         tutteMat[  6][  0] =       6; 
         tutteMat[  7][  0] =       1; 
      }
      break; 
    case TWO: 
      { /* G1098  *//*printf("spt7414\n");*/
/*
W0888
*/
/*
w0888

******************* reading edge list *************




(  1,  6) (  4,  6) (  1,  3) (  3,  7) (  2,  5) (  6,  7) (  5,  6) 
(  5,  7) (  2,  3) (  2,  4) (  1,  7) (  4,  7) (  4,  5) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              12      32      35      21       7       1 
I =   1      12      55      65      33       7 
I =   2      35      72      41       8 
I =   3      45      46      11       1 
I =   4      35      16       2 
I =   5      18       3 
I =   6       6 
I =   7       1 
*/printf("W0888\n");
         tutteMat[  0][  1] =      12; 
         tutteMat[  0][  2] =      32; 
         tutteMat[  0][  3] =      35; 
         tutteMat[  0][  4] =      21; 
         tutteMat[  0][  5] =       7; 
         tutteMat[  0][  6] =       1; 
         tutteMat[  1][  0] =      12; 
         tutteMat[  1][  1] =      55; 
         tutteMat[  1][  2] =      65; 
         tutteMat[  1][  3] =      33; 
         tutteMat[  1][  4] =       7; 
         tutteMat[  2][  0] =      35; 
         tutteMat[  2][  1] =      72; 
         tutteMat[  2][  2] =      41; 
         tutteMat[  2][  3] =       8; 
         tutteMat[  3][  0] =      45; 
         tutteMat[  3][  1] =      46; 
         tutteMat[  3][  2] =      11; 
         tutteMat[  3][  3] =       1; 
         tutteMat[  4][  0] =      35; 
         tutteMat[  4][  1] =      16; 
         tutteMat[  4][  2] =       2; 
         tutteMat[  5][  0] =      18; 
         tutteMat[  5][  1] =       3; 
         tutteMat[  6][  0] =       6; 
         tutteMat[  7][  0] =       1; 
      }
      break;
    case  FOUR:
      { /* G1096  *//*printf("spt7415\n");*/
/*
W0891
*/
/*
w0891

******************* reading edge list *************




(  1,  3) (  1,  6) (  2,  3) (  2,  7) (  1,  7) (  2,  5) (  3,  4) 
(  4,  5) (  4,  7) (  5,  7) (  5,  6) (  4,  6) (  6,  7) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              14      37      39      22       7       1 
I =   1      14      62      69      31       6 
I =   2      39      75      37       7 
I =   3      47      44      11       1 
I =   4      35      16       2 
I =   5      18       3 
I =   6       6 
I =   7       1 
*/
printf("W0891\n");

         tutteMat[  0][  1] =      14; 
         tutteMat[  0][  2] =      37; 
         tutteMat[  0][  3] =      39; 
         tutteMat[  0][  4] =      22; 
         tutteMat[  0][  5] =       7; 
         tutteMat[  0][  6] =       1; 
         tutteMat[  1][  0] =      14; 
         tutteMat[  1][  1] =      62; 
         tutteMat[  1][  2] =      69; 
         tutteMat[  1][  3] =      31; 
         tutteMat[  1][  4] =       6; 
         tutteMat[  2][  0] =      39; 
         tutteMat[  2][  1] =      75; 
         tutteMat[  2][  2] =      37; 
         tutteMat[  2][  3] =       7; 
         tutteMat[  3][  0] =      47; 
         tutteMat[  3][  1] =      44; 
         tutteMat[  3][  2] =      11; 
         tutteMat[  3][  3] =       1; 
         tutteMat[  4][  0] =      35; 
         tutteMat[  4][  1] =      16; 
         tutteMat[  4][  2] =       2; 
         tutteMat[  5][  0] =      18; 
         tutteMat[  5][  1] =       3; 
         tutteMat[  6][  0] =       6; 
         tutteMat[  7][  0] =       1; 
      }
         break; 
    case 12:
      {
         vt = firstVertex(g);  //(*g).vrtx[ZERO].nvert;
         d51 = nextofdegree(
                            g,
                            &vt,
                            FIVE
                           );
         deletevrtx(
                    g,
                    d51
                   );
         if( nodegn(g,TWO) == TWO )
           { /* G1095 *//*printf("spt7416\n");*/
/*
W0887
*/
/*
w0887

******************* reading edge list *************




(  1,  6) (  3,  6) (  1,  7) (  3,  5) (  1,  5) (  3,  4) (  4,  5) 
(  2,  6) (  2,  4) (  6,  7) (  2,  7) (  5,  7) (  4,  7) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              12      34      38      22       7       1 
I =   1      12      58      72      34       6 
I =   2      36      78      42       6 
I =   3      46      49      10 
I =   4      35      18 
I =   5      18       3 
I =   6       6 
I =   7       1 
*/
/*printf("W0887\n");*/

             tutteMat[  0][  1] =      12; 
             tutteMat[  0][  2] =      34; 
             tutteMat[  0][  3] =      38; 
             tutteMat[  0][  4] =      22; 
             tutteMat[  0][  5] =       7; 
             tutteMat[  0][  6] =       1; 
             tutteMat[  1][  0] =      12; 
             tutteMat[  1][  1] =      58; 
             tutteMat[  1][  2] =      72; 
             tutteMat[  1][  3] =      34; 
             tutteMat[  1][  4] =       6; 
             tutteMat[  2][  0] =      36; 
             tutteMat[  2][  1] =      78; 
             tutteMat[  2][  2] =      42; 
             tutteMat[  2][  3] =       6; 
             tutteMat[  3][  0] =      46; 
             tutteMat[  3][  1] =      49; 
             tutteMat[  3][  2] =      10; 
             tutteMat[  4][  0] =      35; 
             tutteMat[  4][  1] =      18; 
             tutteMat[  5][  0] =      18; 
             tutteMat[  5][  1] =       3; 
             tutteMat[  6][  0] =       6; 
             tutteMat[  7][  0] =       1; 
          }
        else
          { /* G1093 *//*printf("spt7417\n");*/
/*
W0879
*/
/*
w0879


******************* reading edge list *************




(  2,  6) (  1,  5) (  1,  7) (  4,  7) (  2,  7) (  3,  4) (  1,  6) 
(  2,  4) (  4,  6) (  3,  7) (  3,  5) (  5,  6) (  5,  7) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              11      32      37      22       7       1 
I =   1      11      55      72      36       6 
I =   2      34      78      45       5 
I =   3      45      51       9 
I =   4      35      18 
I =   5      18       3 
I =   6       6 
I =   7       1 
*/

/*printf("W0879\n");*/
             tutteMat[  0][  1] =      11; 
             tutteMat[  0][  2] =      32; 
             tutteMat[  0][  3] =      37; 
             tutteMat[  0][  4] =      22; 
             tutteMat[  0][  5] =       7; 
             tutteMat[  0][  6] =       1; 
             tutteMat[  1][  0] =      11; 
             tutteMat[  1][  1] =      55; 
             tutteMat[  1][  2] =      72; 
             tutteMat[  1][  3] =      36; 
             tutteMat[  1][  4] =       6; 
             tutteMat[  2][  0] =      34; 
             tutteMat[  2][  1] =      78; 
             tutteMat[  2][  2] =      45; 
             tutteMat[  2][  3] =       5; 
             tutteMat[  3][  0] =      45; 
             tutteMat[  3][  1] =      51; 
             tutteMat[  3][  2] =       9; 
             tutteMat[  4][  0] =      35; 
             tutteMat[  4][  1] =      18; 
             tutteMat[  5][  0] =      18; 
             tutteMat[  5][  1] =       3; 
             tutteMat[  6][  0] =       6; 
             tutteMat[  7][  0] =       1; 
          } 
      }
      break; 
    case SIX:
      {
         vt = firstVertex(g);  //(*g).vrtx[ZERO].nvert;
         d51 = nextofdegree(
                            g,
                            &vt,
                            FIVE
                           );
         deletevrtx(
                    g,
                    d51
                   );
         vt = firstVertex(g);  //(*g).vrtx[ZERO].nvert;
         d31a = nextofdegree(
                             g,
                             &vt,
                             THREE
                            );
         d32b = nextofdegree(
                             g,
                             &vt,
                             THREE
                            );
         if( commonadj(g,d31a,d32b) == TWO )
           { /* G1099 *//*printf("spt7418\n");*/
/*
W0881
*/
/*
w0881

                                                                                              

******************* reading edge list *************




(  2,  7) (  3,  7) (  3,  4) (  2,  3) (  2,  4) (  1,  5) (  5,  6) 
(  1,  6) (  4,  5) (  5,  7) (  1,  7) (  4,  6) (  6,  7) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               8      26      33      21       7       1 
I =   1       8      46      68      37       7 
I =   2      28      74      46       6 
I =   3      41      51      10       1 
I =   4      34      18       1 
I =   5      18       3 
I =   6       6 
I =   7       1 
*/
/*printf("W0881\n");*/
             tutteMat[  0][  1] =       8; 
             tutteMat[  0][  2] =      26; 
             tutteMat[  0][  3] =      33; 
             tutteMat[  0][  4] =      21; 
             tutteMat[  0][  5] =       7; 
             tutteMat[  0][  6] =       1; 
             tutteMat[  1][  0] =       8; 
             tutteMat[  1][  1] =      46; 
             tutteMat[  1][  2] =      68; 
             tutteMat[  1][  3] =      37; 
             tutteMat[  1][  4] =       7; 
             tutteMat[  2][  0] =      28; 
             tutteMat[  2][  1] =      74; 
             tutteMat[  2][  2] =      46; 
             tutteMat[  2][  3] =       6; 
             tutteMat[  3][  0] =      41; 
             tutteMat[  3][  1] =      51; 
             tutteMat[  3][  2] =      10; 
             tutteMat[  3][  3] =       1; 
             tutteMat[  4][  0] =      34; 
             tutteMat[  4][  1] =      18; 
             tutteMat[  4][  2] =       1; 
             tutteMat[  5][  0] =      18; 
             tutteMat[  5][  1] =       3; 
             tutteMat[  6][  0] =       6; 
             tutteMat[  7][  0] =       1; 
          }  
        else
          { /* G1089 *//*printf("spt7419\n");*/
/*
W0883
*/
/*
w0883
                                                                                              
                                                                                              
                                                                                              

******************* reading edge list *************




(  4,  5) (  2,  7) (  1,  7) (  2,  3) (  2,  6) (  1,  6) (  5,  7) 
(  5,  6) (  1,  5) (  4,  7) (  4,  6) (  3,  7) (  3,  4) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              11      32      37      22       7       1 
I =   1      11      55      71      35       6 
I =   2      34      77      43       6 
I =   3      45      49      10 
I =   4      35      17       1 
I =   5      18       3 
I =   6       6 
I =   7       1 
*/
/*printf("W0883\n");*/
              tutteMat[  0][  1] =      11; 
              tutteMat[  0][  2] =      32; 
              tutteMat[  0][  3] =      37; 
              tutteMat[  0][  4] =      22; 
              tutteMat[  0][  5] =       7; 
              tutteMat[  0][  6] =       1; 
              tutteMat[  1][  0] =      11; 
              tutteMat[  1][  1] =      55; 
              tutteMat[  1][  2] =      71; 
              tutteMat[  1][  3] =      35; 
              tutteMat[  1][  4] =       6; 
              tutteMat[  2][  0] =      34; 
              tutteMat[  2][  1] =      77; 
              tutteMat[  2][  2] =      43; 
              tutteMat[  2][  3] =       6; 
              tutteMat[  3][  0] =      45; 
              tutteMat[  3][  1] =      49; 
              tutteMat[  3][  2] =      10; 
              tutteMat[  4][  0] =      35; 
              tutteMat[  4][  1] =      17; 
              tutteMat[  4][  2] =       1; 
              tutteMat[  5][  0] =      18; 
              tutteMat[  5][  1] =       3; 
              tutteMat[  6][  0] =       6; 
              tutteMat[  7][  0] =       1; 

       
          }
      }
      break;
    case THREE:
      {
         vt = firstVertex(g);  //(*g).vrtx[ZERO].nvert;
         d51 = nextofdegree(
                            g,
                            &vt,
                            FIVE
                           );
         deletevrtx(
                    g,
                    d51
                   );
         vt = firstVertex(g);  //(*g).vrtx[ZERO].nvert;
         d21 = nextofdegree(
                            g,
                            &vt,
                            TWO
                           );
         d22 = nextofdegree(
                            g,
                            &vt,
                            TWO
                           );
         if( isadj( d21, d22, g ) )
           { /* G1097 */ /*printf("spt7420\n");*/
    

/*
W0884
*/
/*
w0884
                                                                                              
                                                                                              
                                                                                              

******************* reading edge list *************




(  1,  4) (  1,  5) (  1,  6) (  4,  5) (  6,  7) (  2,  7) (  4,  6) 
(  3,  7) (  3,  5) (  2,  3) (  4,  7) (  2,  6) (  5,  7) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              10      29      34      21       7       1 
I =   1      10      51      67      35       7 
I =   2      32      74      44       8 
I =   3      44      49      11 
I =   4      35      17       1 
I =   5      18       3 
I =   6       6 
I =   7       1 
*/
/*printf("W0884\n");*/
             tutteMat[  0][  1] =      10; 
             tutteMat[  0][  2] =      29; 
             tutteMat[  0][  3] =      34; 
             tutteMat[  0][  4] =      21; 
             tutteMat[  0][  5] =       7; 
             tutteMat[  0][  6] =       1; 
             tutteMat[  1][  0] =      10; 
             tutteMat[  1][  1] =      51; 
             tutteMat[  1][  2] =      67; 
             tutteMat[  1][  3] =      35; 
             tutteMat[  1][  4] =       7; 
             tutteMat[  2][  0] =      32; 
             tutteMat[  2][  1] =      74; 
             tutteMat[  2][  2] =      44; 
             tutteMat[  2][  3] =       8; 
             tutteMat[  3][  0] =      44; 
             tutteMat[  3][  1] =      49; 
             tutteMat[  3][  2] =      11; 
             tutteMat[  4][  0] =      35; 
             tutteMat[  4][  1] =      17; 
             tutteMat[  4][  2] =       1; 
             tutteMat[  5][  0] =      18; 
             tutteMat[  5][  1] =       3; 
             tutteMat[  6][  0] =       6; 
             tutteMat[  7][  0] =       1; 
          } 
        else
          { /* G1091 *//*printf("spt7421\n");*/

/*
W0886
*/
/*
w0886

******************* reading edge list *************




(  2,  3) (  1,  5) (  2,  4) (  4,  5) (  2,  7) (  3,  6) (  1,  7) 
(  6,  7) (  5,  7) (  3,  4) (  4,  7) (  1,  6) (  5,  6) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              10      29      34      21       7       1 
I =   1      10      50      66      35       7 
I =   2      31      72      44       7 
I =   3      42      49      11       1 
I =   4      34      18       1 
I =   5      18       3 
I =   6       6 
I =   7       1 

printf("W0886\n");*/
             tutteMat[  0][  1] =      10; 
             tutteMat[  0][  2] =      29; 
             tutteMat[  0][  3] =      34; 
             tutteMat[  0][  4] =      21; 
             tutteMat[  0][  5] =       7; 
             tutteMat[  0][  6] =       1; 
             tutteMat[  1][  0] =      10; 
             tutteMat[  1][  1] =      50; 
             tutteMat[  1][  2] =      66;
             tutteMat[  1][  3] =      35; 
             tutteMat[  1][  4] =       7; 
             tutteMat[  2][  0] =      31; 
             tutteMat[  2][  1] =      72; 
             tutteMat[  2][  2] =      44; 
             tutteMat[  2][  3] =       7; 
             tutteMat[  3][  0] =      42; 
             tutteMat[  3][  1] =      49; 
             tutteMat[  3][  2] =      11; 
             tutteMat[  3][  3] =       1; 
             tutteMat[  4][  0] =      34; 
             tutteMat[  4][  1] =      18; 
             tutteMat[  4][  2] =       1; 
             tutteMat[  5][  0] =      18; 
             tutteMat[  5][  1] =       3; 
             tutteMat[  6][  0] =       6; 
             tutteMat[  7][  0] =       1; 
          }   
      }
       break;

    case FIVE:
      {
         vt = firstVertex(g);  //(*g).vrtx[ZERO].nvert;
         d51 = nextofdegree(
                            g,
                            &vt,
                            FIVE
                           );
         deletevrtx(
                    g,
                    d51
                   );
         vt = firstVertex(g);  //(*g).vrtx[ZERO].nvert;
         d21 = nextofdegree(
                            g,
                            &vt,
                            TWO
                           );
         d22 = nextofdegree(
                            g,
                            &vt,
                            TWO
                           );
         deletevrtx(
                    g,
                    d21
                   );        
         deletevrtx(
                    g,
                    d22
                   );        
         no1 = nodegn(
                      g,
                      ONE
                     );
         if( no1 == ZERO )
           { /* G1094  *//*printf("spt7422\n");*/
/*
W0890
*/
/*
w0890

******************* reading edge list *************




(  3,  7) (  4,  5) (  5,  7) (  1,  7) (  2,  6) (  4,  6) (  4,  7) 
(  2,  3) (  6,  7) (  1,  6) (  2,  5) (  1,  5) (  3,  4) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              14      38      41      23       7       1 
I =   1      14      63      72      32       5 
I =   2      39      77      39       6 
I =   3      47      46      11 
I =   4      35      17       1 
I =   5      18       3 
I =   6       6 
I =   7       1 
*/
/*printf("W0890\n");*/
               tutteMat[  0][  1] =      14; 
               tutteMat[  0][  2] =      38; 
               tutteMat[  0][  3] =      41; 
               tutteMat[  0][  4] =      23; 
               tutteMat[  0][  5] =       7; 
               tutteMat[  0][  6] =       1; 
               tutteMat[  1][  0] =      14; 
               tutteMat[  1][  1] =      63; 
               tutteMat[  1][  2] =      72; 
               tutteMat[  1][  3] =      32; 
               tutteMat[  1][  4] =       5; 
               tutteMat[  2][  0] =      39; 
               tutteMat[  2][  1] =      77; 
               tutteMat[  2][  2] =      39; 
               tutteMat[  2][  3] =       6; 
               tutteMat[  3][  0] =      47; 
               tutteMat[  3][  1] =      46; 
               tutteMat[  3][  2] =      11; 
               tutteMat[  4][  0] =      35; 
               tutteMat[  4][  1] =      17; 
               tutteMat[  4][  2] =       1; 
               tutteMat[  5][  0] =      18; 
               tutteMat[  5][  1] =       3; 
               tutteMat[  6][  0] =       6; 
               tutteMat[  7][  0] =       1; 
            } 
          else
            { /* G1090  *//*printf("spt7423\n");*/
/*
W0889
*/
/*
w0889

******************* reading edge list *************




(  1,  6) (  2,  7) (  1,  7) (  2,  3) (  3,  5) (  1,  5) (  4,  6) 
(  2,  6) (  4,  7) (  5,  7) (  6,  7) (  3,  4) (  4,  5) 


VERTICES =      7 EDGES =     13

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              13      35      38      22       7       1 
I =   1      13      59      69      33       6 
I =   2      37      75      41       7 
I =   3      46      47      11 
I =   4      35      17       1 
I =   5      18       3 
I =   6       6 
I =   7       1 
*/
/*printf("W0889\n");*/
               tutteMat[  0][  1] =      13; 
               tutteMat[  0][  2] =      35; 
               tutteMat[  0][  3] =      38; 
               tutteMat[  0][  4] =      22; 
               tutteMat[  0][  5] =       7; 
               tutteMat[  0][  6] =       1; 
               tutteMat[  1][  0] =      13; 
               tutteMat[  1][  1] =      59; 
               tutteMat[  1][  2] =      69; 
               tutteMat[  1][  3] =      33; 
               tutteMat[  1][  4] =       6; 
               tutteMat[  2][  0] =      37; 
               tutteMat[  2][  1] =      75; 
               tutteMat[  2][  2] =      41; 
               tutteMat[  2][  3] =       7; 
               tutteMat[  3][  0] =      46; 
               tutteMat[  3][  1] =      47; 
               tutteMat[  3][  2] =      11; 
               tutteMat[  4][  0] =      35; 
               tutteMat[  4][  1] =      17; 
               tutteMat[  4][  2] =       1; 
               tutteMat[  5][  0] =      18; 
               tutteMat[  5][  1] =       3; 
               tutteMat[  6][  0] =       6; 
               tutteMat[  7][  0] =       1; 
            } 
      } /* end CASE FIVE */
      break;

default:
{
printf("sevenpart44\n");
break;
}
  } /* end switch */


} /* end sevenpart44 */  

/*                                            */
/*           end of sevenpart44               */
/*                                            */
/**********************************************/


