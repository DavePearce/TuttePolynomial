#include "tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart4a             */
/*                                            */
 



/* Procedures Called:


/* 
Precondition: g is a simple graph with seven vertices and 7, 11, or 12 edges
              tutteMat and tutteMatX are arrays with values for the
              current state of this computation 

Postcondition: tutteMat and tutteMatX augmented by the tutte
               poly of this graph

 */
void
sevenpart4a(
            struct graph *g,
            TUTTE tutteMat,
            TUTTEO tutteMatX
           )

{
 int firstvertex,         /* location of first vertex on vertex list      */
     vt,                  /* location on vertex list                      */
     i,                   /* for parameter                                */
     degseq,              /*variables used to compute the degree sequence */
     deg[VERTEXSIZE],
      sum,                /* accumulator for degrees of a set of vertices */
     ne,                  /* locations on edge lists                      */
     ne1,
     deg21,               /* location of vertex of degree 2               */
     deg22,
     deg31,               /* location of vertex of degree 3               */
     deg32,
     deg33,
     d31,
     deg3,
     d41,                 /* location of vertex of degree 4               */
     d51,                 /* location of vertex of degree 5               */
     nodegtwo;            /* number of degree two verte`ices adjacent to 
     				degree 3 vertex                           */
//printf("sevenpart4a\n");
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

/* find degree sequence */
vt = firstVertex(g);
for ( i = ZERO; i < SEVEN; ++i ) 
  deg[i]=ZERO;

while ( vt != LIST_END ) 
  {
     ++deg[(*g).vrtx[vt].degree];
     vt= nextVertex(g, vt);  //(*g).vrtx[vt].nvert;
  }
degseq=deg[2]+10*deg[3]+100*deg[4]+1000*deg[5]+10000*deg[6];
 
switch(degseq)
  {  /* 1 */

     case 340:
       {/*printf("340\n"); */
          sevenpart4b(g,tutteMat,tutteMatX);
       }
       break;

     case 1150:/* are vertices of degree 4 and degree 5 adjacent
             if so, case on number of degree 2 vertices in
             subgraph induced by neighbors of vertex of
             degree 4 */
       {/*printf("1150\n");*/
          vt= firstVertex(g);  //(*g).vrtx[ZERO].nvert;
          d41=nextofdegree(g,&vt,FOUR);
          vt= firstVertex(g);  //(*g).vrtx[ZERO].nvert;
          d51=nextofdegree(g,&vt,FIVE);
          if(!isadj(d41,d51,g))
            { /* g995  *//*printf("sprt4a12\n");*/
 /*
W0774
*/
/*
w0774


******************* reading edge list *************




(  1,  5) (  2,  6) (  2,  5) (  3,  4) (  1,  7) (  4,  6) (  2,  7) 
(  5,  7) (  3,  6) (  1,  6) (  4,  7) (  3,  7) 


VERTICES =      7 EDGES =     12
        J =  0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0      0       6      20      26      17       6       1 
I =   1      6      33      47      24       4 
I =   2     19      46      24       2 
I =   3     24      24       3 
I =   4     16       5 
I =   5      6 
I =   6      1 
*/
 
               tutteMat[  0][  1] =       6;
               tutteMat[  0][  2] =      20;
               tutteMat[  0][  3] =      26;
               tutteMat[  0][  4] =      17;
               tutteMat[  0][  5] =       6;
               tutteMat[  0][  6] =       1;
               tutteMat[  1][  0] =       6;
               tutteMat[  1][  1] =      33;
               tutteMat[  1][  2] =      47;
               tutteMat[  1][  3] =      24;
               tutteMat[  1][  4] =       4;
               tutteMat[  2][  0] =      19;
               tutteMat[  2][  1] =      46;
               tutteMat[  2][  2] =      24;
               tutteMat[  2][  3] =       2;
               tutteMat[  3][  0] =      24;
               tutteMat[  3][  1] =      24;
               tutteMat[  3][  2] =       3;
               tutteMat[  4][  0] =      16;
               tutteMat[  4][  1] =       5;
               tutteMat[  5][  0] =       6;
               tutteMat[  6][  0] =       1;
            }
          else
            {
               deletevrtx(g,d51);/* side effect d51 has no value */
               vt= firstVertex(g);  //(*g).vrtx[ZERO].nvert;
               deg3=nextofdegree(g,&vt,THREE);
               nodegtwo=nodegnadjtov(g,deg3,TWO);
               if(nodegtwo == THREE)
                 { /* g994 *//*printf("sprt4a13\n");*/
 /*
W0787
*/
/*
w0787

******************* reading edge list *************




(  3,  4) (  1,  7) (  2,  5) (  1,  5) (  1,  6) (  3,  7) (  2,  6) 
(  6,  7) (  4,  7) (  4,  5) (  3,  6) (  2,  7) 


VERTICES =      7 EDGES =     12
        J =  0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0      0       9      25      28      17       6       1 
I =   1      9      39      44      20       4 
I =   2     23      43      21       4 
I =   3     25      22       4 
I =   4     16       5 
I =   5      6 
I =   6      1 
*/
                 tutteMat[  0][  1] =       9;
                 tutteMat[  0][  2] =      25;
                 tutteMat[  0][  3] =      28;
                 tutteMat[  0][  4] =      17;
                 tutteMat[  0][  5] =       6;
                 tutteMat[  0][  6] =       1;
                 tutteMat[  1][  0] =       9;
                 tutteMat[  1][  1] =      39;
                 tutteMat[  1][  2] =      44;
                 tutteMat[  1][  3] =      20;
                 tutteMat[  1][  4] =       4;
                 tutteMat[  2][  0] =      23;
                 tutteMat[  2][  1] =      43;
                 tutteMat[  2][  2] =      21;
                 tutteMat[  2][  3] =       4;
                 tutteMat[  3][  0] =      25;
                 tutteMat[  3][  1] =      22;
                 tutteMat[  3][  2] =       4;
                 tutteMat[  4][  0] =      16;
                 tutteMat[  4][  1] =       5;
                 tutteMat[  5][  0] =       6;
                 tutteMat[  6][  0] =       1;
 
     
              }   
            else
              { 
                 ne = firstEdge(g, deg3);  //(*g).edg[(*g).vrtx[deg3].fedge].front;
                 deg21=nextdegnadjtov(g,&ne,TWO);
                 deg22=nextdegnadjtov(g,&ne,TWO);
                 if(isadj(deg21,deg22,g))
                   { /* G996  *//*printf("sprt4a14\n");*/
 /*
W0777
*/
/*
w0777


******************* reading edge list *************




(  1,  6) (  1,  5) (  5,  6) (  2,  4) (  2,  7) (  2,  3) (  3,  4) 
(  5,  7) (  4,  6) (  6,  7) (  3,  7) (  1,  7) 


VERTICES =      7 EDGES =     12
        J =  0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0      0       4      14      20      15       6       1 
I =   1      4      24      39      25       6 
I =   2     14      39      27       4 
I =   3     20      25       4       1 
I =   4     15       6 
I =   5      6 
I =   6      1 
*/
                       tutteMat[  0][  1] =       4;
                       tutteMat[  0][  2] =      14;
                       tutteMat[  0][  3] =      20;
                       tutteMat[  0][  4] =      15;
                       tutteMat[  0][  5] =       6;
                       tutteMat[  0][  6] =       1;
                       tutteMat[  1][  0] =       4;
                       tutteMat[  1][  1] =      24;
                       tutteMat[  1][  2] =      39;
                       tutteMat[  1][  3] =      25;
                       tutteMat[  1][  4] =       6;
                       tutteMat[  2][  0] =      14;
                       tutteMat[  2][  1] =      39;
                       tutteMat[  2][  2] =      27;
                       tutteMat[  2][  3] =       4;
                       tutteMat[  3][  0] =      20;
                       tutteMat[  3][  1] =      25;
                       tutteMat[  3][  2] =       4;
                       tutteMat[  3][  3] =       1;
                       tutteMat[  4][  0] =      15;
                       tutteMat[  4][  1] =       6;
                       tutteMat[  5][  0] =       6;
                       tutteMat[  6][  0] =       1;
                    }   
                  else
                    { 
                       sum=degreesofnhbrs(g,deg21);
                       sum+=degreesofnhbrs(g,deg22); 
                       if(sum==11)
                         { /* g992 *//*printf("sprt4a15\n");*/
 /*
W0784
*/
/*
w0784


******************* reading edge list *************




(  1,  5) (  3,  5) (  2,  4) (  1,  7) (  6,  7) (  3,  4) (  1,  6) 
(  2,  7) (  5,  6) (  3,  7) (  4,  7) (  2,  6) 


VERTICES =      7 EDGES =     12

        J =  0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0      0       7      20      24      16       6       1 
I =   1      7      33      42      23       5 
I =   2     20      42      24       4 
I =   3     24      23       4 
I =   4     16       5 
I =   5      6 
I =   6      1 
*/
                            tutteMat[  0][  1] =       7;
                            tutteMat[  0][  2] =      20;
                            tutteMat[  0][  3] =      24;
                            tutteMat[  0][  4] =      16;
                            tutteMat[  0][  5] =       6;
                            tutteMat[  0][  6] =       1;
                            tutteMat[  1][  0] =       7;
                            tutteMat[  1][  1] =      33;
                            tutteMat[  1][  2] =      42;
                            tutteMat[  1][  3] =      23;
                            tutteMat[  1][  4] =       5;
                            tutteMat[  2][  0] =      20;
                            tutteMat[  2][  1] =      42;
                            tutteMat[  2][  2] =      24;
                            tutteMat[  2][  3] =       4;
                            tutteMat[  3][  0] =      24;
                            tutteMat[  3][  1] =      23;
                            tutteMat[  3][  2] =       4;
                            tutteMat[  4][  0] =      16;
                            tutteMat[  4][  1] =       5;
                            tutteMat[  5][  0] =       6;
                            tutteMat[  6][  0] =       1;
                         } 
                       else
                         { /* G993   *//*printf("sprt4a16\n");*/
 /*
W0788
*/
/*
w0788


******************* reading edge list *************




(  1,  5) (  3,  5) (  2,  4) (  1,  7) (  5,  7) (  3,  4) (  4,  7) 
(  1,  6) (  2,  6) (  6,  7) (  3,  6) (  2,  7) 


VERTICES =      7 EDGES =     12

          J = 0   J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0                8      23      27      17       6       1 
I =   1       8      37      45      22       4 
I =   2      22      44      22       3 
I =   3      25      22       4 
I =   4      16       5 
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
                            tutteMat[  1][  1] =      37; 
                            tutteMat[  1][  2] =      45; 
                            tutteMat[  1][  3] =      22; 
                            tutteMat[  1][  4] =       4; 
                            tutteMat[  2][  0] =      22; 
                            tutteMat[  2][  1] =      44; 
                            tutteMat[  2][  2] =      22; 
                            tutteMat[  2][  3] =       3; 
                            tutteMat[  3][  0] =      25; 
                            tutteMat[  3][  1] =      22; 
                            tutteMat[  3][  2] =       4; 
                            tutteMat[  4][  0] =      16; 
                            tutteMat[  4][  1] =       5; 
                            tutteMat[  5][  0] =       6; 
                            tutteMat[  6][  0] =       1; 

                         }
                    } 
                } 
            }
        } 
        break;






     case 10060:/* are two vertices of degree 3 adjacent to a 
              vertex of degree 3 adjacent */
       {
        /*printf("10060\n");*/
          vt= firstVertex(g);  //(*g).vrtx[ZERO].nvert;
          deg31=nextofdegree(g,&vt,THREE);
          ne1= firstEdge(g, deg31);  //(*g).edg[(*g).vrtx[deg31].fedge].front;
          deg32=nextdegnadjtov(g,&ne1,THREE);
          deg33=nextdegnadjtov(g,&ne1,THREE);
          if(isadj(deg32,deg33,g))
            { /* G1009 *//*printf("sprt4a17\n");*/
 /*
W0741
*/
/*
w0741



******************* reading edge list *************




(  1,  5) (  2,  7) (  1,  7) (  2,  4) (  3,  4) (  4,  7) (  3,  7) 
(  1,  6) (  2,  3) (  5,  7) (  6,  7) (  5,  6) 


VERTICES =      7 EDGES =     12

          J = 0  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               4      12      13       6       1 
I =   1       8      28      28       8 
I =   2       4      28      34       6 
I =   3      12      28       6       2 
I =   4      13       8 
I =   5       6 
I =   6       1
*/ 
               tutteMat[  0][  2] =       4; 
               tutteMat[  0][  3] =      12; 
               tutteMat[  0][  4] =      13; 
               tutteMat[  0][  5] =       6; 
               tutteMat[  0][  6] =       1; 
               tutteMat[  1][  1] =       8; 
               tutteMat[  1][  2] =      28; 
               tutteMat[  1][  3] =      28; 
               tutteMat[  1][  4] =       8; 
               tutteMat[  2][  0] =       4; 
               tutteMat[  2][  1] =      28; 
               tutteMat[  2][  2] =      34; 
               tutteMat[  2][  3] =       6; 
               tutteMat[  3][  0] =      12; 
               tutteMat[  3][  1] =      28; 
               tutteMat[  3][  2] =       6; 
               tutteMat[  3][  3] =       2; 
               tutteMat[  4][  0] =      13; 
               tutteMat[  4][  1] =       8; 
               tutteMat[  5][  0] =       6; 
               tutteMat[  6][  0] =       1; 
            } 
          else
            { /* G1008   *//*printf("sprt4a18\n");*/
 /*
W0746
*/
/*
w0746


******************* reading edge list *************




(  2,  4) (  4,  7) (  1,  7) (  1,  5) (  2,  6) (  3,  5) (  3,  4) 
(  2,  7) (  3,  7) (  6,  7) (  5,  7) (  1,  6) 


VERTICES =      7 EDGES =     12
        J =  0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0      0       5      15      20      15       6       1 
I =   1      5      25      36      24       6 
I =   2     15      36      27       6 
I =   3     20      24       6 
I =   4     15       6 
I =   5      6 
I =   6      1 
*/
               tutteMat[  0][  1] =       5;
               tutteMat[  0][  2] =      15;
               tutteMat[  0][  3] =      20;
               tutteMat[  0][  4] =      15;
               tutteMat[  0][  5] =       6;
               tutteMat[  0][  6] =       1;
               tutteMat[  1][  0] =       5;
               tutteMat[  1][  1] =      25;
               tutteMat[  1][  2] =      36;
               tutteMat[  1][  3] =      24;
               tutteMat[  1][  4] =       6;
               tutteMat[  2][  0] =      15;
               tutteMat[  2][  1] =      36;
               tutteMat[  2][  2] =      27;
               tutteMat[  2][  3] =       6;
               tutteMat[  3][  0] =      20;
               tutteMat[  3][  1] =      24;
               tutteMat[  3][  2] =       6;
               tutteMat[  4][  0] =      15;
               tutteMat[  4][  1] =       6;
               tutteMat[  5][  0] =       6;
               tutteMat[  6][  0] =       1;
            }   
       } 
       break;

     case 160:
       { 
         /*printf("160\n");*/
          vt= firstVertex(g);  //(*g).vrtx[ZERO].nvert;
          d41=nextofdegree(g,&vt,FOUR);
          deletevrtx(g,d41);
          vt= firstVertex(g);  //(*g).vrtx[ZERO].nvert;;
          deg3=nextofdegree(g,&vt,THREE);
          nodegtwo=nodegnadjtov(g,deg3,TWO);
          if(nodegtwo == THREE)
            { /* G876  *//*printf("sprt4a19\n");*/
 /*
W0670
*/
/*
w0670


******************* reading edge list *************




(  2,  7) (  1,  6) (  3,  7) (  1,  5) (  2,  6) (  3,  4) (  2,  5) 
(  4,  5) (  1,  7) (  4,  7) (  3,  6) 


VERTICES =      7 EDGES =     11

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0               8      21      23      14       5       1 
I =   1       8      31      30      11       1 
I =   2      18      25       7 
I =   3      15       6 
I =   4       6 
I =   5       1 
*/
               tutteMat[  0][  1] =       8; 
               tutteMat[  0][  2] =      21; 
               tutteMat[  0][  3] =      23; 
               tutteMat[  0][  4] =      14; 
               tutteMat[  0][  5] =       5; 
               tutteMat[  0][  6] =       1; 
               tutteMat[  1][  0] =       8; 
               tutteMat[  1][  1] =      31; 
               tutteMat[  1][  2] =      30; 
               tutteMat[  1][  3] =      11; 
               tutteMat[  1][  4] =       1; 
               tutteMat[  2][  0] =      18; 
               tutteMat[  2][  1] =      25; 
               tutteMat[  2][  2] =       7; 
               tutteMat[  3][  0] =      15; 
               tutteMat[  3][  1] =       6; 
               tutteMat[  4][  0] =       6; 
               tutteMat[  5][  0] =       1; 

  
            }   
          else
            { 
               ne = firstEdge(g, deg3);  //(*g).edg[(*g).vrtx[deg3].fedge].front;
               deg21=nextdegnadjtov(g,&ne,TWO);
               deg22=nextdegnadjtov(g,&ne,TWO);
               if(isadj(deg21,deg22,g))
                 {/*   G878   *//*printf("sprt4a20\n");*/
 /*
W0667
*/
/*
w0667


******************* reading edge list *************




(  1,  5) (  3,  7) (  5,  6) (  2,  3) (  2,  4) (  4,  6) (  3,  4) 
(  1,  6) (  5,  7) (  1,  7) (  2,  7) 


VERTICES =      7 EDGES =     11
        J =  0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0      0       4      12      15      11       5       1 
I =   1      4      20      26      14       4 
I =   2     12      24      10       2 
I =   3     13       8 
I =   4      6 
I =   5      1 
*/
               tutteMat[  0][  1] =       4;
               tutteMat[  0][  2] =      12;
               tutteMat[  0][  3] =      15;
               tutteMat[  0][  4] =      11;
               tutteMat[  0][  5] =       5;
               tutteMat[  0][  6] =       1;
               tutteMat[  1][  0] =       4;
               tutteMat[  1][  1] =      20;
               tutteMat[  1][  2] =      26;
               tutteMat[  1][  3] =      14;
               tutteMat[  1][  4] =       4;
               tutteMat[  2][  0] =      12;
               tutteMat[  2][  1] =      24;
               tutteMat[  2][  2] =      10;
               tutteMat[  2][  3] =       2;
               tutteMat[  3][  0] =      13;
               tutteMat[  3][  1] =       8;
               tutteMat[  4][  0] =       6;
               tutteMat[  5][  0] =       1;
            }   
          else
            { 
               sum=degreesofnhbrs(g,deg21);
               sum+=degreesofnhbrs(g,deg22); 
               if(sum==11)
                 { /*   G875  *//*printf("sprt4a21\n");*/
 /*
W0668
*/
/*
w0668


******************* reading edge list *************




(  1,  5) (  1,  6) (  2,  4) (  1,  7) (  2,  6) (  3,  4) (  3,  5) 
(  5,  6) (  3,  7) (  4,  7) (  2,  7) 


VERTICES =      7 EDGES =     11
        J =  0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0      0       6      16      18      12       5       1 
I =   1      6      25      27      13       3 
I =   2     15      24       9       1 
I =   3     14       7 
I =   4      6 
I =   5      1 
*/
                   tutteMat[  0][  1] =       6;
                   tutteMat[  0][  2] =      16;
                   tutteMat[  0][  3] =      18;
                   tutteMat[  0][  4] =      12;
                   tutteMat[  0][  5] =       5;
                   tutteMat[  0][  6] =       1;
                   tutteMat[  1][  0] =       6;
                   tutteMat[  1][  1] =      25;
                   tutteMat[  1][  2] =      27;
                   tutteMat[  1][  3] =      13;
                   tutteMat[  1][  4] =       3;
                   tutteMat[  2][  0] =      15;
                   tutteMat[  2][  1] =      24;
                   tutteMat[  2][  2] =       9;
                   tutteMat[  2][  3] =       1;
                   tutteMat[  3][  0] =      14;
                   tutteMat[  3][  1] =       7;
                   tutteMat[  4][  0] =       6;
                   tutteMat[  5][  0] =       1;
 
                }
              else
                { /*  G877   *//*printf("sprt4a22\n");*/
 /*
W0669
*/
/*
w0669


******************* reading edge list *************




(  2,  7) (  2,  4) (  1,  7) (  4,  7) (  5,  7) (  1,  5) (  3,  5) 
(  3,  6) (  3,  4) (  1,  6) (  2,  6) 


VERTICES =      7 EDGES =     11
        J =  0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0      0       7      19      21      13       5       1 
I =   1      7      29      30      12       2 
I =   2     17      26       7 
I =   3     15       6 
I =   4      6 
I =   5      1 
*/
                   tutteMat[  0][  1] =       7;
                   tutteMat[  0][  2] =      19;
                   tutteMat[  0][  3] =      21;
                   tutteMat[  0][  4] =      13;
                   tutteMat[  0][  5] =       5;
                   tutteMat[  0][  6] =       1;
                   tutteMat[  1][  0] =       7;
                   tutteMat[  1][  1] =      29;
                   tutteMat[  1][  2] =      30;
                   tutteMat[  1][  3] =      12;
                   tutteMat[  1][  4] =       2;
                   tutteMat[  2][  0] =      17;
                   tutteMat[  2][  1] =      26;
                   tutteMat[  2][  2] =       7;
                   tutteMat[  3][  0] =      15;
                   tutteMat[  3][  1] =       6;
                   tutteMat[  4][  0] =       6;
                   tutteMat[  5][  0] =       1;
                } 
             } 
         } 
      } 
     break;



     case 7: /* degree */
       { /* G353   *//*printf("sprt4a23\n");*/
        /*printf("7\n");*/ 

/*
W0146
*/
/*
w0146


 
******************* reading edge list *************




(  3,  4) (  6,  7) (  1,  2) (  4,  5) (  5,  6) (  2,  3) (  7,  1) 



VERTICES =      7 EDGES =      7
        J =  0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0      0       1       1       1       1       1       1 
I =   1      1 
*/
         tutteMat[  0][  1] =       1;
         tutteMat[  0][  2] =       1;
         tutteMat[  0][  3] =       1;
         tutteMat[  0][  4] =       1;
         tutteMat[  0][  5] =       1;
         tutteMat[  0][  6] =       1;
         tutteMat[  1][  0] =       1;
      } 
      break;

  } /* 1 end switch on degseq */

//if(tutteMat[0][1]==0&&tutteMat[0][2]==0){printf("sevenpart4a\n");printGraph(g);}
}  /* end sevenpart4a */

/*                                            */
/*           end of sevenpart4a               */
/*                                            */
/**********************************************/


