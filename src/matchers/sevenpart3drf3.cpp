#include "core/tutte.h"
#include <memory.h>

/**********************************************/
/*                                            */
/*           start of sevenpart3drf3          */
/*                                            */
 
void
sevenpart3drf3(struct Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX)

{

int spec3,         /* location of vertex of degree 3               */
    common3,       /* number of common adj of vertices of degree 3 */
    tri1,          /* location of vertex list                      */
    tri2,
    tri3,
    d31,           /* location of vertex of degree 3               */
    d32,
    d51,           /* location of vertex of degree 5               */
    d52,
    d31nhbrs,      /* degrees of nhbrs of vertex of degree 3       */
    d32nhbrs,
    vt,            /* location of vertex                           */
    ne; 

switch(degseq)
{  /* 1 */

case 2320:
  { /* start switch 2320 */
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
     d31nhbrs = degreesofnhbrs(
                               g,
                               d31
                              );
     d32nhbrs = degreesofnhbrs(
                               g,
                               d32
                              );
     vt = firstVertex(g); 
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
     common3 = commonadj(
                         g,
                         d31,
                         d32
                        );


     if( ( d31nhbrs == 12 ) && ( d32nhbrs == 12 ) )
       {

//57

/*   W57
w0955

******************* reading edge list *************




(  1,  7) (  4,  7) (  4,  6) (  2,  4) (  2,  6) (  3,  4) (  3,  6) 
(  5,  6) (  3,  7) (  1,  5) (  1,  2) (  6,  7) (  5,  7) (  3,  5) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              18      47      49      27       8       1 
I =   1      18      84      98      47       9 
I =   2      55     116      66      13 
I =   3      75      83      24       2 
I =   4      65      39       6 
I =   5      41      12       1 
I =   6      19       2 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      18; 
tutteMat[  0][  2] =      47; 
tutteMat[  0][  3] =      49; 
tutteMat[  0][  4] =      27; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      18; 
tutteMat[  1][  1] =      84; 
tutteMat[  1][  2] =      98; 
tutteMat[  1][  3] =      47; 
tutteMat[  1][  4] =       9; 
tutteMat[  2][  0] =      55; 
tutteMat[  2][  1] =     116; 
tutteMat[  2][  2] =      66; 
tutteMat[  2][  3] =      13; 
tutteMat[  3][  0] =      75; 
tutteMat[  3][  1] =      83; 
tutteMat[  3][  2] =      24; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =      65; 
tutteMat[  4][  1] =      39; 
tutteMat[  4][  2] =       6; 
tutteMat[  5][  0] =      41; 
tutteMat[  5][  1] =      12; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

     
       }
     else

       if( ( ( d31nhbrs == 13 ) && ( d32nhbrs == 11 ) )
            || ( ( d31nhbrs == 11 )  && ( d32nhbrs == 13 ) ) )
         {

//58
/*   W58
w0956

******************* reading edge list *************




(  1,  2) (  2,  4) (  4,  6) (  3,  5) (  3,  6) (  3,  7) (  3,  4) 
(  4,  7) (  1,  6) (  5,  6) (  6,  7) (  5,  7) (  1,  7) (  2,  5) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              20      52      53      28       8       1 
I =   1      20      91     102      45       8 
I =   2      59     119      62      12 
I =   3      77      81      24       2 
I =   4      65      39       6 
I =   5      41      12       1 
I =   6      19       2 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      20; 
tutteMat[  0][  2] =      52; 
tutteMat[  0][  3] =      53; 
tutteMat[  0][  4] =      28; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      20; 
tutteMat[  1][  1] =      91; 
tutteMat[  1][  2] =     102; 
tutteMat[  1][  3] =      45; 
tutteMat[  1][  4] =       8; 
tutteMat[  2][  0] =      59; 
tutteMat[  2][  1] =     119; 
tutteMat[  2][  2] =      62; 
tutteMat[  2][  3] =      12; 
tutteMat[  3][  0] =      77; 
tutteMat[  3][  1] =      81; 
tutteMat[  3][  2] =      24; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =      65; 
tutteMat[  4][  1] =      39; 
tutteMat[  4][  2] =       6; 
tutteMat[  5][  0] =      41; 
tutteMat[  5][  1] =      12; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

     
         }

       else

       if( ( ( d31nhbrs == 13 ) && ( d32nhbrs == 12 ) )
            || ( ( d31nhbrs == 12 )  && ( d32nhbrs == 13 ) ) )
           {

//51
/*
w0949  W 51

******************* reading edge list *************




(  1,  7) (  2,  5) (  2,  7) (  1,  2) (  4,  7) (  3,  4) (  3,  7) 
(  3,  5) (  4,  5) (  5,  6) (  4,  6) (  1,  6) (  6,  7) (  3,  6) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              16      44      48      27       8       1 
I =   1      16      79      99      49       9 
I =   2      51     116      69      12 
I =   3      72      86      24       2 
I =   4      64      41       5 
I =   5      41      12       1 
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
tutteMat[  1][  1] =      79; 
tutteMat[  1][  2] =      99; 
tutteMat[  1][  3] =      49; 
tutteMat[  1][  4] =       9; 
tutteMat[  2][  0] =      51; 
tutteMat[  2][  1] =     116; 
tutteMat[  2][  2] =      69; 
tutteMat[  2][  3] =      12; 
tutteMat[  3][  0] =      72; 
tutteMat[  3][  1] =      86; 
tutteMat[  3][  2] =      24; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =      64; 
tutteMat[  4][  1] =      41; 
tutteMat[  4][  2] =       5; 
tutteMat[  5][  0] =      41; 
tutteMat[  5][  1] =      12; 
tutteMat[  5][  2] =       1; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

     

           }
         else

       if( ( ( d31nhbrs == 14 ) && ( d32nhbrs == 12 ) )
            || ( ( d31nhbrs == 12 )  && ( d32nhbrs == 14 ) ) )
             {

//56
/*
w0954  W56

******************* reading edge list *************




(  3,  6) (  4,  6) (  2,  5) (  1,  5) (  2,  4) (  1,  7) (  2,  3) 
(  3,  4) (  3,  7) (  1,  6) (  6,  7) (  4,  7) (  5,  7) (  5,  6) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              16      44      48      27       8       1 
I =   1      16      78      98      49       9 
I =   2      50     115      71      12 
I =   3      71      88      24       2 
I =   4      64      42       5 
I =   5      41      13 
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
tutteMat[  1][  1] =      78; 
tutteMat[  1][  2] =      98; 
tutteMat[  1][  3] =      49; 
tutteMat[  1][  4] =       9; 
tutteMat[  2][  0] =      50; 
tutteMat[  2][  1] =     115; 
tutteMat[  2][  2] =      71; 
tutteMat[  2][  3] =      12; 
tutteMat[  3][  0] =      71; 
tutteMat[  3][  1] =      88; 
tutteMat[  3][  2] =      24; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =      64; 
tutteMat[  4][  1] =      42; 
tutteMat[  4][  2] =       5; 
tutteMat[  5][  0] =      41; 
tutteMat[  5][  1] =      13; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

    

             }


           else

             if( ( ( d31nhbrs == 14 )  && ( d32nhbrs == 14 ) ) )
               {

//47--50--53
                 if(!isadj(d51,d52,g))
                   {/* not isadj case */

//47
/*  W47
w0945

******************* reading edge list *************




(  1,  5) (  2,  7) (  2,  4) (  1,  7) (  2,  6) (  1,  6) (  3,  4) 
(  4,  6) (  3,  7) (  4,  7) (  3,  5) (  3,  6) (  5,  6) (  5,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              15      44      50      28       8       1 
I =   1      15      79     106      52       8 
I =   2      50     123      75      10 
I =   3      73      93      22 
I =   4      65      43       3 
I =   5      41      13 
I =   6      19       2 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      15; 
tutteMat[  0][  2] =      44; 
tutteMat[  0][  3] =      50; 
tutteMat[  0][  4] =      28; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      15; 
tutteMat[  1][  1] =      79; 
tutteMat[  1][  2] =     106; 
tutteMat[  1][  3] =      52; 
tutteMat[  1][  4] =       8; 
tutteMat[  2][  0] =      50; 
tutteMat[  2][  1] =     123; 
tutteMat[  2][  2] =      75; 
tutteMat[  2][  3] =      10; 
tutteMat[  3][  0] =      73; 
tutteMat[  3][  1] =      93; 
tutteMat[  3][  2] =      22; 
tutteMat[  4][  0] =      65; 
tutteMat[  4][  1] =      43; 
tutteMat[  4][  2] =       3; 
tutteMat[  5][  0] =      41; 
tutteMat[  5][  1] =      13; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

       

                   }
                 else
                   {/* isadj case */
                      if(common3==TWO)
                        {

//50
/*  W50
w0952

******************* reading edge list *************




(  1,  7) (  3,  7) (  2,  7) (  6,  7) (  4,  7) (  2,  5) (  3,  6) 
(  5,  6) (  4,  6) (  1,  5) (  2,  4) (  1,  6) (  3,  4) (  3,  5) 


VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              17      47      51      28       8       1 
I =   1      17      83     104      50       8 
I =   2      53     121      73      11 
I =   3      74      91      23        
I =   4      65      43       3 
I =   5      41      13 
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
tutteMat[  1][  1] =      83; 
tutteMat[  1][  2] =     104; 
tutteMat[  1][  3] =      50; 
tutteMat[  1][  4] =       8; 
tutteMat[  2][  0] =      53; 
tutteMat[  2][  1] =     121; 
tutteMat[  2][  2] =      73; 
tutteMat[  2][  3] =      11; 
tutteMat[  3][  0] =      74; 
tutteMat[  3][  1] =      91; 
tutteMat[  3][  2] =      23; 
tutteMat[  4][  0] =      65; 
tutteMat[  4][  1] =      43; 
tutteMat[  4][  2] =       3;
tutteMat[  5][  0] =      41; 
tutteMat[  5][  1] =      13; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

          
           

                        }
                      else
                        {

//53  
/*  W53
w0951

******************* reading edge list *************




(  3,  6) (  1,  6) (  1,  7) (  2,  5) (  1,  5) (  2,  7) (  2,  6) 
(  4,  5) (  3,  4) (  3,  7) (  6,  7) (  4,  6) (  4,  7) (  3,  5) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              20      54      56      29       8       1 
I =   1      20      92     107      46       7 
I =   2      58     123      68      10 
I =   3      76      89      22       1 
I =   4      65      43       3 
I =   5      41      13 
I =   6      19       2 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      20; 
tutteMat[  0][  2] =      54; 
tutteMat[  0][  3] =      56; 
tutteMat[  0][  4] =      29; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      20; 
tutteMat[  1][  1] =      92; 
tutteMat[  1][  2] =     107; 
tutteMat[  1][  3] =      46; 
tutteMat[  1][  4] =       7; 
tutteMat[  2][  0] =      58; 
tutteMat[  2][  1] =     123; 
tutteMat[  2][  2] =      68; 
tutteMat[  2][  3] =      10; 
tutteMat[  3][  0] =      76; 
tutteMat[  3][  1] =      89; 
tutteMat[  3][  2] =      22; 
tutteMat[  3][  3] =       1; 
tutteMat[  4][  0] =      65; 
tutteMat[  4][  1] =      43; 
tutteMat[  4][  2] =       3; 
tutteMat[  5][  0] =      41; 
tutteMat[  5][  1] =      13; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 
                        }/* common3 */


                  }/* isadj */

               }/* 14-14*/


             else

       if( ( ( d31nhbrs == 14 ) && ( d32nhbrs == 13 ) )
            || ( ( d31nhbrs == 13)  && ( d32nhbrs == 14 ) ) )
                 {

//49--54--55
                    if(common3==TWO)
                      {

//54
         /* W54 */ 
tutteMat[  0][  1] =      18; 
tutteMat[  0][  2] =      49; 
tutteMat[  0][  3] =      52; 
tutteMat[  0][  4] =      28; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      18; 
tutteMat[  1][  1] =      86; 
tutteMat[  1][  2] =     104; 
tutteMat[  1][  3] =      48; 
tutteMat[  1][  4] =       8; 
tutteMat[  2][  0] =      55; 
tutteMat[  2][  1] =     121; 
tutteMat[  2][  2] =      69; 
tutteMat[  2][  3] =      11; 
tutteMat[  3][  0] =      75; 
tutteMat[  3][  1] =      88; 
tutteMat[  3][  2] =      23; 
tutteMat[  3][  3] =       1; 
tutteMat[  4][  0] =      65; 
tutteMat[  4][  1] =      42;
tutteMat[  4][  2]=        4; 
tutteMat[  5][  0] =      41; 
tutteMat[  5][  1] =      13; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

          

                      }
                    else
                      {

//49--55
                         if(nodegnadjtov(g,d31,FIVE)==TWO)
                           {
                              spec3=d31;
                           }
                         else
                           {
                              spec3=d32;
                           }
                         ne = firstEdge(g, spec3); 
                         tri1 = vertListOtherEnd(g, ne);  
                         ne = nextEdge(g, ne); 
                         tri2 = vertListOtherEnd(g, ne);  
                         ne = nextEdge(g, ne);  
                         tri3 = vertListOtherEnd(g, ne);  
                         if(isadj(tri1,tri2,g) && isadj(tri1,tri3,g) && isadj(tri2,tri3,g))
                            {

//49
/*   W49
w0947

******************* reading edge list *************




(  1,  5) (  1,  6) (  1,  7) (  2,  4) (  2,  3) (  2,  7) (  3,  4) 
(  3,  7) (  4,  6) (  4,  5) (  3,  6) (  5,  6) (  5,  7) (  6,  7) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              14      41      47      27       8       1 
I =   1      14      74     100      51       9 
I =   2      47     117      74      12 
I =   3      70      91      24       1 
I =   4      64      43       4 
I =   5      41      13 
I =   6      19       2 
I =   7       6 
I =   8       1 
*/
tutteMat[  0][  1] =      14; 
tutteMat[  0][  2] =      41; 
tutteMat[  0][  3] =      47; 
tutteMat[  0][  4] =      27; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      14; 
tutteMat[  1][  1] =      74; 
tutteMat[  1][  2] =     100; 
tutteMat[  1][  3] =      51; 
tutteMat[  1][  4] =       9; 
tutteMat[  2][  0] =      47; 
tutteMat[  2][  1] =     117; 
tutteMat[  2][  2] =      74; 
tutteMat[  2][  3] =      12; 
tutteMat[  3][  0] =      70; 
tutteMat[  3][  1] =      91; 
tutteMat[  3][  2] =      24; 
tutteMat[  3][  3] =       1; 
tutteMat[  4][  0] =      64; 
tutteMat[  4][  1] =      43; 
tutteMat[  4][  2] =       4; 
tutteMat[  5][  0] =      41; 
tutteMat[  5][  1] =      13; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 


                             }
                             else
                            {

//55
/*   W55
w0953

******************* reading edge list *************




(  2,  7) (  1,  6) (  3,  5) (  2,  3) (  3,  7) (  1,  7) (  2,  4) 
(  4,  6) (  1,  5) (  5,  6) (  6,  7) (  4,  7) (  3,  6) (  4,  5) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              17      47      51      28       8       1 
I =   1      17      83     103      49       8 
I =   2      53     120      71      12 
I =   3      74      89      24 
I =   4      65      42       4 
I =   5      41      13 
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
tutteMat[  1][  1] =      83; 
tutteMat[  1][  2] =     103; 
tutteMat[  1][  3] =      49; 
tutteMat[  1][  4] =       8; 
tutteMat[  2][  0] =      53; 
tutteMat[  2][  1] =     120; 
tutteMat[  2][  2] =      71; 
tutteMat[  2][  3] =      12; 
tutteMat[  3][  0] =      74; 
tutteMat[  3][  1] =      89; 
tutteMat[  3][  2] =      24; 
tutteMat[  4][  0] =      65; 
tutteMat[  4][  1] =      42; 
tutteMat[  4][  2] =       4; 
tutteMat[  5][  0] =      41; 
tutteMat[  5][  1] =      13; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

          
}

                      }/* common3 not equal TWO */
                 }/* case 13-14 */

               else

                 if( ( d31nhbrs == 13 ) && ( d32nhbrs == 13 ) )
                   {

//48--52
                      if(isadj(d51,d52,g))
                        {
  
//52
/*   W52
w0950

******************* reading edge list *************




(  2,  3) (  3,  6) (  1,  4) (  1,  7) (  3,  4) (  2,  5) (  4,  7) 
(  1,  5) (  5,  6) (  6,  7) (  4,  6) (  5,  7) (  3,  7) (  2,  6) 



VERTICES =      7 EDGES =     14

          J = 0  J =  1  J =  2  J =  3  J =  4  J =  5  J =  6 
I =   0              16      44      48      27       8       1 
I =   1      16      79      99      49       9 
I =   2      51     117      71      13 
I =   3      73      88      24       1 
I =   4      65      41       5 
I =   5      41      13 
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
tutteMat[  1][  1] =      79; 
tutteMat[  1][  2] =      99; 
tutteMat[  1][  3] =      49; 
tutteMat[  1][  4] =       9; 
tutteMat[  2][  0] =      51; 
tutteMat[  2][  1] =     117; 
tutteMat[  2][  2] =      71; 
tutteMat[  2][  3] =      13; 
tutteMat[  3][  0] =      73; 
tutteMat[  3][  1] =      88; 
tutteMat[  3][  2] =      24; 
tutteMat[  3][  3] =       1; 
tutteMat[  4][  0] =      65; 
tutteMat[  4][  1] =      41; 
tutteMat[  4][  2] =       5; 
tutteMat[  5][  0] =      41; 
tutteMat[  5][  1] =      13; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 

     

                        }
                      else
                        {

//48
/*W48*/
tutteMat[  0][  1] =      12; 
tutteMat[  0][  2] =      38; 
tutteMat[  0][  3] =      46; 
tutteMat[  0][  4] =      27; 
tutteMat[  0][  5] =       8; 
tutteMat[  0][  6] =       1; 
tutteMat[  1][  0] =      12; 
tutteMat[  1][  1] =      70; 
tutteMat[  1][  2] =     102; 
tutteMat[  1][  3] =      53; 
tutteMat[  1][  4] =       9; 
tutteMat[  2][  0] =      44; 
tutteMat[  2][  1] =     118; 
tutteMat[  2][  2] =      74; 
tutteMat[  2][  3] =      10; 
tutteMat[  3][  0] =      68; 
tutteMat[  3][  1] =      91; 
tutteMat[  3][  2] =      23; 
tutteMat[  3][  3] =       2; 
tutteMat[  4][  0] =      63; 
tutteMat[  4][  1] =      43; 
tutteMat[  4][  2] =       4; 
tutteMat[  5][  0] =      41; 
tutteMat[  5][  1] =      12;
tutteMat[  5][  2]=        1; 
tutteMat[  6][  0] =      19; 
tutteMat[  6][  1] =       2; 
tutteMat[  7][  0] =       6; 
tutteMat[  8][  0] =       1; 


                        }

                  }


  } /* end switch for 2320 */
break;

default:
  {
     printf("sevenpart3drf3\n");
     break;
  }

} /*  end switch on degseq */


}  /* end sevenpart3drf3 */

/*                                            */
/*           end of sevenpart3drf3            */
/*                                            */
/**********************************************/







