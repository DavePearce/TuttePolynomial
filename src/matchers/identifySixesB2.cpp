
#include "core/tutte.h"
#include <memory.h>


/********************************************/
/*                                          */
/*           start of identifySixesB2       */
/*                                          */


/*
Precondition: g is a graph with six vertices and one fo the following 
              degree sequences: 2022, 1050, 1131, 321, 240, 1230, 420, 
              or 600
              tutteMat1 and tutteMat1X are arrays holding the current 
              status of the computation of the tutte poly of g

Postcondition: tutteMat1 and tutteMat1X are augmented by the tutte poly of
		g

*/


void
identifySixesB2 ( struct Graph *g,int degseq,TUTTE   tutteMat1,TUTTEO tutteMat1X)
{
int 
    vt,                /* location of vertex                            */
    d21,               /* location on vertex list of vertex of degree 2 */
    deg2,
    d31,               /* location on vertex list of vertex of degree 3 */
    d41,               /* location on vertex list of vertex of degree 4 */
    d42,
    ne,                /*location on edge list                          */
    sum1;              /* accumulator for sets of degrees of vertices   */
//printf("identifySixesB\n");

switch( degseq )
  {  /* 1 */

     case 2022:/* degree */
        /* s37 g179 h105 degree */
       { /* 254 */
          tutteMat1[0][1]=2;
          tutteMat1[0][2]=7;
          tutteMat1[0][3]=9;
          tutteMat1[0][4]=5;
          tutteMat1[0][5]=1;
          tutteMat1[1][0]=2;
          tutteMat1[1][1]=9;
          tutteMat1[1][2]=13;
          tutteMat1[1][3]=6;
          tutteMat1[2][0]=4;
          tutteMat1[2][1]=11;
          tutteMat1[2][2]=8;
          tutteMat1[3][0]=4;
          tutteMat1[3][1]=8;
          tutteMat1[3][2]=1;
          tutteMat1[4][0]=3;
          tutteMat1[4][1]=2;
          tutteMat1[5][0]=1;
       } /* 254 */
        break;

     case 1050:/* degree */
        /* s34 g187 h102 degree */
       { /* 255 */
          tutteMat1[0][1]=4;
          tutteMat1[0][2]=10;
          tutteMat1[0][3]=10;
          tutteMat1[0][4]=5;
          tutteMat1[0][5]=1;
          tutteMat1[1][0]=4;
          tutteMat1[1][1]=16;
          tutteMat1[1][2]=15;
          tutteMat1[1][3]=5;
          tutteMat1[2][0]=10;
          tutteMat1[2][1]=15;
          tutteMat1[2][2]=5;
          tutteMat1[3][0]=10;
          tutteMat1[3][1]=5;
          tutteMat1[4][0]=5;
          tutteMat1[5][0]=1;
       } /* 255 */
        break;

     case 1131:/* case on sum of degrees of neighbors of degree 2 vertex */
       { /* 256 */
          vt = firstVertex(g);
          deg2 = nextofdegree(
                              g,
                              &vt,
                              TWO
                             );
          switch( degreesofnhbrs(g,deg2) )
            {
               case NINE:
                /* s35 g182 h103 */
                 { /* 258 */
                    tutteMat1[0][1]=3;
                    tutteMat1[0][2]=9;
                    tutteMat1[0][3]=10;
                    tutteMat1[0][4]=5;
                    tutteMat1[0][5]=1;
                    tutteMat1[1][0]=3;
                    tutteMat1[1][1]=13;
                    tutteMat1[1][2]=15;
                    tutteMat1[1][3]=5;
                    tutteMat1[2][0]=7;
                    tutteMat1[2][1]=14;
                    tutteMat1[2][2]=6;
                    tutteMat1[3][0]=7;
                    tutteMat1[3][1]=7;
                    tutteMat1[4][0]=4;
                    tutteMat1[4][1]=1;
                    tutteMat1[5][0]=1;
                 } /* 258 */
                 break;

               case EIGHT:
                   /* s36 g183 h104 */
                 { /* 259 */
                    tutteMat1[0][1]=2;
                    tutteMat1[0][2]=7;
                    tutteMat1[0][3]=9;
                    tutteMat1[0][4]=5;
                    tutteMat1[0][5]=1;
                    tutteMat1[1][0]=2;
                    tutteMat1[1][1]=11;
                    tutteMat1[1][2]=15;
                    tutteMat1[1][3]=6;
                    tutteMat1[2][0]=6;
                    tutteMat1[2][1]=14;
                    tutteMat1[2][2]=6;
                    tutteMat1[3][0]=7;
                    tutteMat1[3][1]=6;
                    tutteMat1[3][2]=1;
                    tutteMat1[4][0]=4;
                    tutteMat1[4][1]=1;
                    tutteMat1[5][0]=1;
                 } /* 259 */
                 break;
            }
       } /* 256  end 1131 case */
       break;

     case 321:/* sum of sums of degrees of neighbors of vertex 
               adjacent to vertex of degree 2 */
       { /*2510 */
          vt = firstVertex(g);
          d21 = nextofdegree(
                             g,
                             &vt,
                             TWO
                            );
          ne = firstEdge(g, d21);  
          sum1 = ZERO;
          while( ne != LIST_END )
            { 
               sum1 += degreesofnhbrs(
                                      g,
                                      vertListOtherEnd(g, ne)  
                                     ); 
               ne = nextEdge(g, ne);  
            }
          switch( sum1 )
            { /* 2514 */
               case TWENTYTHREE:
                  /* s39 g185 h108 */
                 { /* 2515 */
                    tutteMat1[0][1]=4;
                    tutteMat1[0][2]=10;
                    tutteMat1[0][3]=10;
                    tutteMat1[0][4]=5;
                    tutteMat1[0][5]=1;
                    tutteMat1[1][0]=4;
                    tutteMat1[1][1]=15;
                    tutteMat1[1][2]=14;
                    tutteMat1[1][3]=5;
                    tutteMat1[2][0]=9;
                    tutteMat1[2][1]=13;
                    tutteMat1[2][2]=5;
                    tutteMat1[3][0]=8;
                    tutteMat1[3][1]=5;
                    tutteMat1[3][2]=1;
                    tutteMat1[4][0]=4;
                    tutteMat1[4][1]=1;
                    tutteMat1[5][0]=1;
                 } /* 2515 */
                 break;

               case TWENTYSIX:
                  /* s40 g184 h1010 */
                   /* 2516 */
                 {
                    tutteMat1[0][1]=3;
                    tutteMat1[0][2]=9;
                    tutteMat1[0][3]=10;
                    tutteMat1[0][4]=5;
                    tutteMat1[0][5]=1;
                    tutteMat1[1][0]=3;
                    tutteMat1[1][1]=14;
                    tutteMat1[1][2]=16;
                    tutteMat1[1][3]=5;
                    tutteMat1[2][0]=8;
                    tutteMat1[2][1]=15;
                    tutteMat1[2][2]=5;
                    tutteMat1[3][0]=8;
                    tutteMat1[3][1]=6;
                    tutteMat1[4][0]=4;
                    tutteMat1[4][1]=1;
                    tutteMat1[5][0]=1;
                 } /* 2516 */
                 break;

               case TWENTYFOUR:
                 /* s44 g186 h1015 */
                 { /* 2517 */
                    tutteMat1[0][1]=4;
                    tutteMat1[0][2]=11;
                    tutteMat1[0][3]=11;
                    tutteMat1[0][4]=5;
                    tutteMat1[0][5]=1;
                    tutteMat1[1][0]=4;
                    tutteMat1[1][1]=16;
                    tutteMat1[1][2]=16;
                    tutteMat1[1][3]=4;
                    tutteMat1[2][0]=9;
                    tutteMat1[2][1]=15;
                    tutteMat1[2][2]=4;
                    tutteMat1[3][0]=8;
                    tutteMat1[3][1]=6;
                    tutteMat1[4][0]=4;
                    tutteMat1[4][1]=1;
                    tutteMat1[5][0]=1;
                 }/* 2517 */
                 break;
            }/* 2514 */ /* end switch sum1 */
       } /* 2510   */
       break;

     case 240:
       {  
          vt= firstVertex(g);
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
          deletevrtx(
                     g,
                     d41
                    );
          deletevrtx(
                     g,
                     d42
                    );
          switch( nodegn(g,ONE) )
            {
               case TWO: 
                 /* s38 g188 h107 */
                 {
                    tutteMat1[0][1]=5;
                    tutteMat1[0][2]=12;
                    tutteMat1[0][3]=11;
                    tutteMat1[0][4]=5;
                    tutteMat1[0][5]=1;
                    tutteMat1[1][0]=5;
                    tutteMat1[1][1]=19;
                    tutteMat1[1][2]=16;
                    tutteMat1[1][3]=4;
                    tutteMat1[2][0]=12;
                    tutteMat1[2][1]=16;
                    tutteMat1[2][2]=3;
                    tutteMat1[3][0]=11;
                    tutteMat1[3][1]=4;
                    tutteMat1[4][0]=5;
                    tutteMat1[5][0]=1;
                 }  
                  break;
               case THREE:
                 {/* s42 g189  h1012 */
                    tutteMat1[0][1]=6;
                    tutteMat1[0][2]=14;
                    tutteMat1[0][3]=12;
                    tutteMat1[0][4]=5;
                    tutteMat1[0][5]=1;
                    tutteMat1[1][0]=6;
                    tutteMat1[1][1]=21;
                    tutteMat1[1][2]=15;
                    tutteMat1[1][3]=3;
                    tutteMat1[2][0]=13;
                    tutteMat1[2][1]=15;
                    tutteMat1[2][2]=3;
                    tutteMat1[3][0]=11;
                    tutteMat1[3][1]=4;
                    tutteMat1[4][0]=5;
                    tutteMat1[5][0]=1;
                 } 
                 break;
               case FOUR: 
                  /* s43 g190 h1014 */
                 { 
                    tutteMat1[0][1]=4;
                    tutteMat1[0][2]=11;
                    tutteMat1[0][3]=11;
                    tutteMat1[0][4]=5;
                    tutteMat1[0][5]=1;
                    tutteMat1[1][0]=4;
                    tutteMat1[1][1]=18;
                    tutteMat1[1][2]=18;
                    tutteMat1[1][3]=4;
                    tutteMat1[2][0]=11;
                    tutteMat1[2][1]=18;
                    tutteMat1[2][2]=2;
                    tutteMat1[3][0]=11;
                    tutteMat1[3][1]=4;
                    tutteMat1[4][0]=5;
                    tutteMat1[5][0]=1;
                 } 
                 break;
            } /* end switch */
       } /* 2518  */
       break;





    case 1230: /* sum of degrees of neighbors of vertex of degree 4 */
      { 
         vt = firstVertex(g);
         d41 = nextofdegree(
                            g,
                            &vt,
                            FOUR
                           );
         switch( degreesofnhbrs(g,d41) )
           {
              case FOURTEEN:
                { /* s49 g197  h116 */ 
                   tutteMat1[0][1]=7;
                   tutteMat1[0][2]=17;
                   tutteMat1[0][3]=15;
                   tutteMat1[0][4]=6;
                   tutteMat1[0][5]=1;
                   tutteMat1[1][0]=7;
                   tutteMat1[1][1]=27;
                   tutteMat1[1][2]=24;
                   tutteMat1[1][3]=6;
                   tutteMat1[2][0]=17;
                   tutteMat1[2][1]=27;
                   tutteMat1[2][2]=9;
                   tutteMat1[3][0]=18;
                   tutteMat1[3][1]=14;
                   tutteMat1[4][0]=12;
                   tutteMat1[4][1]=3;
                   tutteMat1[5][0]=5;
                   tutteMat1[6][0]=1;
                }
                break;
              case FIFTEEN:
                {/* s47 g196  h113 */ 
                   tutteMat1[0][1]=6;
                   tutteMat1[0][2]=15;
                   tutteMat1[0][3]=14;
                   tutteMat1[0][4]=6;
                   tutteMat1[0][5]=1;
                   tutteMat1[1][0]=6;
                   tutteMat1[1][1]=25;
                   tutteMat1[1][2]=24;
                   tutteMat1[1][3]=7;
                   tutteMat1[2][0]=16;
                   tutteMat1[2][1]=27;
                   tutteMat1[2][2]=9;
                   tutteMat1[3][0]=18;
                   tutteMat1[3][1]=13;
                   tutteMat1[3][2]=1;
                   tutteMat1[4][0]=12;
                   tutteMat1[4][1]=3;
                   tutteMat1[5][0]=5;
                   tutteMat1[6][0]=1;
                }
                break;
           }
      } 
       break;


    case 420:/* sum of degrees of neighbors of a degree 3 vertex */
      { 
         vt = firstVertex(g);
         d31 = nextofdegree(
                            g,
                            &vt,
                            THREE
                           );
         switch( degreesofnhbrs(g,d31) )
           {
              case TWELVE:
                { /* s51 g198 h118 */ 
                   tutteMat1[0][1]=7;
                   tutteMat1[0][2]=17;
                   tutteMat1[0][3]=15;
                   tutteMat1[0][4]=6;
                   tutteMat1[0][5]=1;
                   tutteMat1[1][0]=7;
                   tutteMat1[1][1]=29;
                   tutteMat1[1][2]=26;
                   tutteMat1[1][3]=6;
                   tutteMat1[2][0]=19;
                   tutteMat1[2][1]=30;
                   tutteMat1[2][2]=7;
                   tutteMat1[3][0]=21;
                   tutteMat1[3][1]=12;
                   tutteMat1[4][0]=13;
                   tutteMat1[4][1]=2;
                   tutteMat1[5][0]=5;
                   tutteMat1[6][0]=1;
                }
                break;
              case ELEVEN:
                {/* s50 g199 h117 */ 
                   tutteMat1[0][1]=8;
                   tutteMat1[0][2]=18;
                   tutteMat1[0][3]=15;
                   tutteMat1[0][4]=6;
                   tutteMat1[0][5]=1;
                   tutteMat1[1][0]=8;
                   tutteMat1[1][1]=30;
                   tutteMat1[1][2]=24;
                   tutteMat1[1][3]=6;
                   tutteMat1[2][0]=20;
                   tutteMat1[2][1]=28;
                   tutteMat1[2][2]=7;
                   tutteMat1[3][0]=21;
                   tutteMat1[3][1]=11;
                   tutteMat1[3][2]=1;
                   tutteMat1[4][0]=13;
                   tutteMat1[4][1]=2;
                   tutteMat1[5][0]=5;
                   tutteMat1[6][0]=1;
                }
                break;
           }
       }
       break;

     case 600:/* degree */
       { /* s57 g204 h125 degree */
          tutteMat1[0][1]=11;
          tutteMat1[0][2]=25;
          tutteMat1[0][3]=20;
          tutteMat1[0][4]=7;
          tutteMat1[0][5]=1;
          tutteMat1[1][0]=11;
          tutteMat1[1][1]=46;
          tutteMat1[1][2]=39;
          tutteMat1[1][3]=8;
          tutteMat1[2][0]=32;
          tutteMat1[2][1]=52;
          tutteMat1[2][2]=12;
          tutteMat1[3][0]=40;
          tutteMat1[3][1]=24;
          tutteMat1[4][0]=29;
          tutteMat1[4][1]=6;
          tutteMat1[5][0]=15;
          tutteMat1[6][0]=5;
          tutteMat1[7][0]=1;
       }
       break;

    default:
      {
         printf("identifySixesB\2n");
         break;
      }


  } /* end case on degseq */

} /* end identifySixesB2 */


/*                                          */
/*           end of identifySixesB2         */
/*                                          */
/********************************************/


