#include "tutte.h"
#include <memory.h>
/**********************************************/
/*                                            */
/*           start of sevenpart4b             */
/*                                            */
 
/*
Precondition: g is a simple graph with seven vertices
              and 12 edges and degree sequence 340
              tutteMat and tutteMatX are arrays with values
              for current state of this computation

Postcondition: tutteMat and tutteMatX augmented by the tutte
               poly of this graph

*/                 



void
sevenpart4b( 
            struct graph *g,
            TUTTE tutteMat,
            TUTTEO tutteMatX
           )
{
 int vt,                /* location on vertex list                       */
     v,                 /* sum of common adjacencies of pairs of 
     				degree 4 vertices                        */
     v1,                /* number of comon adjacencies of pairs of 
     				degree 4 vertices                        */
     v2,
     v3,
     s1,                /* no common adjacencies of pairs of 
     				degree 3 vertices                        */
     s2,
     s3,
     s4,
     s5,
     s6, 
     no31,             /* number of degreee 3 vertices adjacent 
     				to degree 4 vertices                     */
     no32,
     no33,
     d31a,             /* degree 3 vertices adjacent to degree 
     				4 vertices                               */
     d31b,
     ne1,
     d31,              /* location of vertex of degree 3                 */
     d32,
     d33,
     d34, 
     d41,              /* location of vertex of degree 4                 */
     d42,
     d43;
    //printf("sevenpart4b\n"); 
/* case on number of adjacencies between pairs of degree 4
            vertices
            CASE 0: how many common adjacencies for a pair of degree
                    4 vertices
            CASE 2: switch on sum of number of common adjacencies for
                    the three pairs of degree 4 vertices

            CASE 5: if all vertices of degree 3 have the same 
                            sum of degrees of neighbors find two vertices 
                            of degree 3 adjacent to one of the vertices 
                            of degree 4 and test for adjacency
            CASE 3: case on sum of number of common adjacencies for
                    pairs of degree 4 vertices
                    CASE 5: three summands equal to 3 else sum of 
                            number of common adjacencies for pairs of 
                            vertices of degree 4
                    CASE 6: number of common adjacencies of one degree 
                            3 vertex with other two degree 3 vertices 
                            is 1 each 
            CASE 1: 1003 */
//printf("got to 4b\n");

  vt = firstVertex(g);  //(*g).vrtx[ZERO].nvert;
  d31 = nextofdegree(g,&vt,THREE);
  d32 = nextofdegree(g,&vt,THREE);
  d33 = nextofdegree(g,&vt,THREE);
  d34 = nextofdegree(g,&vt,THREE);
  vt = firstVertex(g);  //(*g).vrtx[ZERO].nvert;
  d41 = nextofdegree(g,&vt,FOUR);
  d42 = nextofdegree(g,&vt,FOUR);
  d43 = nextofdegree(g,&vt,FOUR);
  switch( isadj(d41,d42,g) +  isadj(d41,d43,g) + isadj(d42,d43,g) )
    { /* 1*/
       case ZERO:
         { /* 2 */
        /* G1007 *//*printf"sprt4a1\n"):*/
 /*
W0801
*/
/*
w0801
         

******************* reading edge list *************




(  1,  5) (  3,  5) (  4,  5) (  2,  5) (  1,  7) (  4,  7) (  3,  7) 
(  3,  6) (  1,  6) (  2,  6) (  2,  7) (  4,  6) 


VERTICES =      7 EDGES =     12

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              13      36      38      21       6       1 
I =   1      13      53      54      18 
I =   2      30      51      18 
I =   3      29      23 
I =   4      17       4 
I =   5       6 
I =   6       1 
*/
tutteMat[  0][  1] =      13; 
tutteMat[  0][  2] =      36; 
tutteMat[  0][  3] =      38; 
tutteMat[  0][  4] =      21; 
tutteMat[  0][  5] =       6; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      13; 
tutteMat[  1][  1] =      53; 
tutteMat[  1][  2] =      54; 
tutteMat[  1][  3] =      18; 
tutteMat[  2][  0] =      30; 
tutteMat[  2][  1] =      51; 
tutteMat[  2][  2] =      18; 
tutteMat[  3][  0] =      29; 
tutteMat[  3][  1] =      23; 
tutteMat[  4][  0] =      17; 
tutteMat[  4][  1] =       4; 
tutteMat[  5][  0] =       6; 
tutteMat[  6][  0] =       1; 


        
         }/* 2 */
       break;
       case ONE:
         { /* 3 */     /* G1003  *//*printf"sprt4a2\n"):*/
 /*
W0794
*/
/*
w0794


******************* reading edge list *************




(  1,  7) (  3,  7) (  3,  4) (  2,  6) (  2,  7) (  4,  5) (  1,  6) 
(  5,  6) (  1,  5) (  4,  7) (  3,  6) (  2,  5) 


VERTICES =      7 EDGES =     12

          J = 0   J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               10      28      31      18       6       1 
I =   1      10      44      50      21       3 
I =   2      26      49      21       1 
I =   3      28      23       1 
I =   4      17       4 
I =   5       6 
I =   6       1 
*/
tutteMat[  0][  1] =      10; 
tutteMat[  0][  2] =      28; 
tutteMat[  0][  3] =      31; 
tutteMat[  0][  4] =      18; 
tutteMat[  0][  5] =       6; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      10; 
tutteMat[  1][  1] =      44; 
tutteMat[  1][  2] =      50; 
tutteMat[  1][  3] =      21; 
tutteMat[  1][  4] =       3; 
tutteMat[  2][  0] =      26; 
tutteMat[  2][  1] =      49; 
tutteMat[  2][  2] =      21; 
tutteMat[  2][  3] =       1; 
tutteMat[  3][  0] =      28; 
tutteMat[  3][  1] =      23; 
tutteMat[  3][  2] =       1; 
tutteMat[  4][  0] =      17; 
tutteMat[  4][  1] =       4; 
tutteMat[  5][  0] =       6; 
tutteMat[  6][  0] =       1; 


       
         } /* 3 */
       break;
       case TWO:
         {/* 4 */
            switch( commonadj(g,d41,d42)
                  + commonadj(g,d41,d43)
                  + commonadj(g,d42,d43) )
              {/* 5 */
                 case SIX:
                   { /* 6 */ 
         
                      if ( ( commonadj(g,d41,d42)==FOUR ) ||
                          ( commonadj(g,d41,d43)==FOUR ) ||
                          ( commonadj(g,d42,d43)==FOUR ) )
          
                         { /* 14   G1004 *//*printf"sprt4a6\n"):*/
                           /* transferred from five case where it did not belong */
  /*
W0799
*/
/*
w0799


******************* reading edge list *************




(  2,  4) (  2,  6) (  1,  5) (  3,  6) (  3,  7) (  2,  7) (  5,  6) 
(  1,  7) (  4,  5) (  5,  7) (  3,  4) (  1,  6) 


VERTICES =      7 EDGES =     12

          J = 0   J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              11      30      33      19       6       1 
I =   1      11      47      51      20       2 
I =   2      28      49      19       1 
I =   3      29      21       2 
I =   4      17       4 
I =   5       6 
I =   6       1 
*/
tutteMat[  0][  1] =      11; 
tutteMat[  0][  2] =      30; 
tutteMat[  0][  3] =      33; 
tutteMat[  0][  4] =      19; 
tutteMat[  0][  5] =       6; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      11; 
tutteMat[  1][  1] =      47; 
tutteMat[  1][  2] =      51; 
tutteMat[  1][  3] =      20; 
tutteMat[  1][  4] =       2; 
tutteMat[  2][  0] =      28; 
tutteMat[  2][  1] =      49; 
tutteMat[  2][  2] =      19; 
tutteMat[  2][  3] =       1; 
tutteMat[  3][  0] =      29; 
tutteMat[  3][  1] =      21; 
tutteMat[  3][  2] =       2; 
tutteMat[  4][  0] =      17; 
tutteMat[  4][  1] =       4; 
tutteMat[  5][  0] =       6; 
tutteMat[  6][  0] =       1; 

            
                      } /* 14 */
                    else
                      {
         
         /* 6 G997   *//*printf"sprt4a3\n"):*/
 /*
W0795
*/
/*
w0795


******************* reading edge list *************




(  1,  7) (  2,  4) (  2,  6) (  1,  5) (  1,  6) (  2,  7) (  3,  4) 
(  4,  6) (  3,  5) (  5,  7) (  5,  6) (  3,  7) 


VERTICES =      7 EDGES =     12

          J = 0   J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0                9      25      28      17       6       1 
I =   1       9      41      48      22       4 
I =   2      25      48      21       2 
I =   3      28      22       2 
I =   4      17       4 
I =   5       6 
I =   6       1 
*/
tutteMat[  0][  1] =       9; 
tutteMat[  0][  2] =      25; 
tutteMat[  0][  3] =      28; 
tutteMat[  0][  4] =      17; 
tutteMat[  0][  5] =       6; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =       9; 
tutteMat[  1][  1] =      41; 
tutteMat[  1][  2] =      48; 
tutteMat[  1][  3] =      22; 
tutteMat[  1][  4] =       4; 
tutteMat[  2][  0] =      25; 
tutteMat[  2][  1] =      48; 
tutteMat[  2][  2] =      21; 
tutteMat[  2][  3] =       2; 
tutteMat[  3][  0] =      28; 
tutteMat[  3][  1] =      22; 
tutteMat[  3][  2] =       2; 
tutteMat[  4][  0] =      17; 
tutteMat[  4][  1] =       4; 
tutteMat[  5][  0] =       6; 
tutteMat[  6][  0] =       1; 


                      }
                   } /* 6  */
                 break;
                 case FIVE:
                   {/* 7 */
                      /*   s1=degreesofnhbrs(g,d31);
                           s2=degreesofnhbrs(g,d32);
                           s3=degreesofnhbrs(g,d33);
                           if(s1==s2&&s2==s3)*/ 
              //{/* 8 */
                      no31 = nodegnadjtov(g,d41,THREE);
                      no32 = nodegnadjtov(g,d42,THREE);
                      no33 = nodegnadjtov(g,d43,THREE);
                      if( no31 == TWO )
                        {/* 9 */
                           ne1 = firstEdge(g, d41);  //(*g).edg[(*g).vrtx[d41].fedge].front;
                           d31a = nextdegnadjtov(g,&ne1,THREE);
                           d31b = nextdegnadjtov(g,&ne1,THREE);
                        }/* 9 */
                      else
                        if( no32 == TWO )
                          {/* 10 */
                             ne1 = firstEdge(g, d42);  //(*g).edg[(*g).vrtx[d42].fedge].front;
                             d31a = nextdegnadjtov(g,&ne1,THREE);
                             d31b = nextdegnadjtov(g,&ne1,THREE);
                          }/* 10 */
                        else
                          if( no33 == TWO )
                            {/* 11 */
                               ne1 = firstEdge(g, d43);  //(*g).edg[(*g).vrtx[d43].fedge].front;
                               d31a = nextdegnadjtov(g,&ne1,THREE);
                               d31b = nextdegnadjtov(g,&ne1,THREE);
                            }/* 11 */
                          if( !isadj(d31a,d31b,g) )
                            { /* 12  G999  *//*printf"sprt4a4\n"):*/
 /*
W0796
*/
/*
w0796


******************* reading edge list *************




(  1,  7) (  5,  7) (  3,  5) (  2,  6) (  1,  6) (  2,  7) (  4,  5) 
(  5,  6) (  1,  4) (  4,  6) (  3,  7) (  2,  3) 


VERTICES =      7 EDGES =     12

          J = 0   J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0                8      23      27      17       6       1 
I =   1       8      38      47      23       4 
I =   2      23      47      23       2 
I =   3      27      23       2 
I =   4      17       4 
I =   5       6 
I =   6       1 
*/
tutteMat[  0][  1] =       8; 
tutteMat[  0][  2] =      23; 
tutteMat[  0][  3] =      27; 
tutteMat[  0][  4] =      17; 
tutteMat[  0][  5] =       6; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =       8; 
tutteMat[  1][  1] =      38; 
tutteMat[  1][  2] =      47; 
tutteMat[  1][  3] =      23; 
tutteMat[  1][  4] =       4; 
tutteMat[  2][  0] =      23; 
tutteMat[  2][  1] =      47; 
tutteMat[  2][  2] =      23; 
tutteMat[  2][  3] =       2; 
tutteMat[  3][  0] =      27; 
tutteMat[  3][  1] =      23; 
tutteMat[  3][  2] =       2; 
tutteMat[  4][  0] =      17; 
tutteMat[  4][  1] =       4; 
tutteMat[  5][  0] =       6; 
tutteMat[  6][  0] =       1; 


                
                            }/* 12 */ 
                          else
                            { /* 13 */ 
                /*  G1002    *//*printf"sprt4a5\n"):*/
 /*
W0791
*/
/*
w0791


******************* reading edge list *************




(  3,  5) (  2,  7) (  4,  6) (  2,  3) (  2,  5) (  1,  4) (  3,  7) 
(  1,  6) (  6,  7) (  4,  5) (  5,  6) (  1,  7) 


VERTICES =      7 EDGES =     12

          J = 0   J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0                6      19      24      16       6       1 
I =   1       6      33      46      24       5 
I =   2      20      47      24       3 
I =   3      26      24       2 
I =   4      17       4 
I =   5       6 
I =   6       1 
*/
tutteMat[  0][  1] =       6; 
tutteMat[  0][  2] =      19; 
tutteMat[  0][  3] =      24; 
tutteMat[  0][  4] =      16; 
tutteMat[  0][  5] =       6; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =       6; 
tutteMat[  1][  1] =      33; 
tutteMat[  1][  2] =      46; 
tutteMat[  1][  3] =      24; 
tutteMat[  1][  4] =       5; 
tutteMat[  2][  0] =      20; 
tutteMat[  2][  1] =      47; 
tutteMat[  2][  2] =      24; 
tutteMat[  2][  3] =       3; 
tutteMat[  3][  0] =      26; 
tutteMat[  3][  1] =      24; 
tutteMat[  3][  2] =       2; 
tutteMat[  4][  0] =      17; 
tutteMat[  4][  1] =       4; 
tutteMat[  5][  0] =       6; 
tutteMat[  6][  0] =       1; 


               
                            }/* 13 */ 
          
                   }/* 7 end case FIVE */
                 break;
              }/* 5 */
         } /* 4 end case 2 */
       break;
       case THREE:
         {   /* 15 */ 
            v1 = commonadj(g,d41,d42);
            v2 = commonadj(g,d41,d43);
            v3 = commonadj(g,d42,d43);
            v = v1 + v2 + v3;
            if( v == FIVE ) 
              {/* 16 */
                 if( ( v1 == THREE ) || ( v2 == THREE ) || ( v3 == THREE ) )
                   { /* 17  G1001  *//*printf"sprt4a7\n"):*/
 /*
W0797
*/
/*
w0797


******************* reading edge list *************




(  1,  6) (  2,  7) (  2,  3) (  1,  7) (  5,  6) (  3,  5) (  5,  7) 
(  1,  4) (  4,  5) (  6,  7) (  3,  4) (  2,  6) 


VERTICES =      7 EDGES =     12

          J = 0   J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               10      26      28      17       6       1 
I =   1      10      42      45      21       4 
I =   2      26      45      21       3 
I =   3      28      21       3 
I =   4      17       4 
I =   5       6 
I =   6       1 
*/
tutteMat[  0][  1] =      10; 
tutteMat[  0][  2] =      26; 
tutteMat[  0][  3] =      28; 
tutteMat[  0][  4] =      17; 
tutteMat[  0][  5] =       6; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      10; 
tutteMat[  1][  1] =      42; 
tutteMat[  1][  2] =      45; 
tutteMat[  1][  3] =      21; 
tutteMat[  1][  4] =       4; 
tutteMat[  2][  0] =      26; 
tutteMat[  2][  1] =      45; 
tutteMat[  2][  2] =      21; 
tutteMat[  2][  3] =       3; 
tutteMat[  3][  0] =      28; 
tutteMat[  3][  1] =      21; 
tutteMat[  3][  2] =       3; 
tutteMat[  4][  0] =      17; 
tutteMat[  4][  1] =       4; 
tutteMat[  5][  0] =       6; 
tutteMat[  6][  0] =       1; 


          
                   } /* 17 */
                 else
                   {/* 18 */
                      s1 = commonadj(g,d31,d32);
                      s2 = commonadj(g,d31,d33);
                      s3 = commonadj(g,d31,d34);
                      s4 = commonadj(g,d32,d33);
                      s5 = commonadj(g,d32,d34);/* s5 and s6 set but not used */
                      s6 = commonadj(g,d33,d34);
                      if( ( s1 == TWO ) || ( s2 == TWO ) 
                                        || ( s3 == TWO ) || ( s4 == TWO ) 
                                        || ( s5 == TWO ) )
                        { /*19 G1000  *//*printf"sprt4a8\n"):*/
 /*
W0800
*/
/*
w0800
                                                                                              

******************* reading edge list *************




(  2,  7) (  3,  6) (  1,  7) (  5,  7) (  5,  6) (  2,  3) (  1,  6) 
(  6,  7) (  4,  5) (  2,  5) (  1,  4) (  3,  4) 


VERTICES =      7 EDGES =     12

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              11      29      31      18       6       1 
I =   1      11      46      48      20       3 
I =   2      28      47      19       2 
I =   3      29      20       3 
I =   4      17       4 
I =   5       6 
I =   6       1 
*/
tutteMat[  0][  1] =      11; 
tutteMat[  0][  2] =      29; 
tutteMat[  0][  3] =      31; 
tutteMat[  0][  4] =      18; 
tutteMat[  0][  5] =       6; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      11; 
tutteMat[  1][  1] =      46; 
tutteMat[  1][  2] =      48; 
tutteMat[  1][  3] =      20; 
tutteMat[  1][  4] =       3; 
tutteMat[  2][  0] =      28; 
tutteMat[  2][  1] =      47; 
tutteMat[  2][  2] =      19; 
tutteMat[  2][  3] =       2; 
tutteMat[  3][  0] =      29; 
tutteMat[  3][  1] =      20; 
tutteMat[  3][  2] =       3; 
tutteMat[  4][  0] =      17; 
tutteMat[  4][  1] =       4; 
tutteMat[  5][  0] =       6; 
tutteMat[  6][  0] =       1; 


            
                       }/* 19 */ 
                     else
                       { /*20  G998   *//*printf"sprt4a9\n"):*/
 /*
W0793
*/
/*
w0793


******************* reading edge list *************




(  1,  4) (  1,  6) (  2,  3) (  2,  7) (  2,  5) (  1,  7) (  4,  6) 
(  5,  7) (  3,  4) (  3,  5) (  6,  7) (  5,  6) 


VERTICES =      7 EDGES =     12

          J = 0   J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0                8      22      25      16       6       1 
I =   1       8      37      44      22       5 
I =   2      23      45      22       4 
I =   3      27      22       3 
I =   4      17       4 
I =   5       6 
I =   6       1 
*/
tutteMat[  0][  1] =       8; 
tutteMat[  0][  2] =      22; 
tutteMat[  0][  3] =      25; 
tutteMat[  0][  4] =      16; 
tutteMat[  0][  5] =       6; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =       8; 
tutteMat[  1][  1] =      37; 
tutteMat[  1][  2] =      44; 
tutteMat[  1][  3] =      22; 
tutteMat[  1][  4] =       5; 
tutteMat[  2][  0] =      23; 
tutteMat[  2][  1] =      45; 
tutteMat[  2][  2] =      22; 
tutteMat[  2][  3] =       4; 
tutteMat[  3][  0] =      27; 
tutteMat[  3][  1] =      22; 
tutteMat[  3][  2] =       3; 
tutteMat[  4][  0] =      17; 
tutteMat[  4][  1] =       4; 
tutteMat[  5][  0] =       6; 
tutteMat[  6][  0] =       1; 


           
                      }/* 20 */ 
                   }/* 18 */
              }/* 16 */
            else
              if( v == SIX )
                {/* 21 */
                   if( ( commonadj(g,d31,d32) == ONE ) && ( commonadj(g,d31,d33) == ONE ) ) 
                     { /*22 G1006  *//*printf"sprt4a10\n"):*/
 /*
W0792
*/
/*
w0792


******************* reading edge list *************




(  4,  5) (  2,  4) (  3,  4) (  1,  5) (  1,  6) (  2,  7) (  2,  3) 
(  5,  6) (  1,  7) (  5,  7) (  6,  7) (  3,  6) 


VERTICES =      7 EDGES =     12

          J = 0   J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0                8      22      25      16       6       1 
I =   1       8      36      43      22       5 
I =   2      22      43      22       3 
I =   3      25      22       3       1 
I =   4      16       5 
I =   5       6 
I =   6       1 
*/
tutteMat[  0][  1] =       8; 
tutteMat[  0][  2] =      22; 
tutteMat[  0][  3] =      25; 
tutteMat[  0][  4] =      16; 
tutteMat[  0][  5] =       6; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =       8; 
tutteMat[  1][  1] =      36; 
tutteMat[  1][  2] =      43; 
tutteMat[  1][  3] =      22; 
tutteMat[  1][  4] =       5; 
tutteMat[  2][  0] =      22; 
tutteMat[  2][  1] =      43; 
tutteMat[  2][  2] =      22; 
tutteMat[  2][  3] =       3; 
tutteMat[  3][  0] =      25; 
tutteMat[  3][  1] =      22; 
tutteMat[  3][  2] =       3; 
tutteMat[  3][  3] =       1; 
tutteMat[  4][  0] =      16; 
tutteMat[  4][  1] =       5; 
tutteMat[  5][  0] =       6; 
tutteMat[  6][  0] =       1; 


          
                     }/* 22 */
                   else     
                     { /* 23  G1005   */ /*printf"sprt4a11\n"):*/
 /*
W0798
*/
/*
w0798
                                                                                              

******************* reading edge list *************




(  1,  4) (  2,  5) (  2,  4) (  1,  7) (  2,  7) (  1,  6) (  5,  6) 
(  3,  5) (  3,  4) (  3,  6) (  6,  7) (  5,  7) 


VERTICES =      7 EDGES =     12

          J = 0   J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               10      27      29      17       6       1 
I =   1      10      44      48      20       4 
I =   2      27      48      18       3 
I =   3      29      20       3 
I =   4      17       4 
I =   5       6 
I =   6       1 
*/
tutteMat[  0][  1] =      10; 
tutteMat[  0][  2] =      27; 
tutteMat[  0][  3] =      29; 
tutteMat[  0][  4] =      17; 
tutteMat[  0][  5] =       6; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      10; 
tutteMat[  1][  1] =      44; 
tutteMat[  1][  2] =      48; 
tutteMat[  1][  3] =      20; 
tutteMat[  1][  4] =       4; 
tutteMat[  2][  0] =      27; 
tutteMat[  2][  1] =      48; 
tutteMat[  2][  2] =      18; 
tutteMat[  2][  3] =       3; 
tutteMat[  3][  0] =      29; 
tutteMat[  3][  1] =      20; 
tutteMat[  3][  2] =       3; 
tutteMat[  4][  0] =      17; 
tutteMat[  4][  1] =       4; 
tutteMat[  5][  0] =       6; 
tutteMat[  6][  0] =       1; 


          
                     }/* 23 */
                }/*21 */
         }/* 15 */
       break;      

       default:
         {
            printf("sevenpart4b\n");
            break;
         }

    } /* 1 */



}  /* end sevenpart4b */

/*                                            */
/*           end of sevenpart4b               */
/*                                            */
/**********************************************/


