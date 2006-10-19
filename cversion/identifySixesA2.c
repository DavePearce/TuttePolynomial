#include "tutte.h"
#include <memory.h>

/********************************************/
/*                                          */
/*           start of identifySixesA2       */
/*                                          */

/*

Preconditon: g points to a graph with six vertces and one of the
             following degree sequences: 303, 2004, 1113, 222, 1032, 141, 60
             tutteMat1 and tutteMat1X are arrays holding the current status of the
             computation of the tutte poly of g

Postcondition: tutteMat1 and tutteMat1X are augmented by the tutte poly of
               g

*/



void
identifySixesA2 (
                 struct graph *g,
                 int degseq,
                 TUTTE tutteMat1,
                 TUTTEO tutteMat1X
                )
{
int ne,                /* location of edge                             */  
    vt,                /* location of vertex                           */
    sum,               /* accumulator for degrees of sets of vertices  */
    sum1,
    sum2,
    deg2,              /* location on vertex list of vertex of degree 5 */
    deg21,             /* location on vertex list of neighbors 
    				of degree 2 vertex                      */
    deg22,
    d31,
    d32,
    deg5,              /* location on vertex list of vertex of degree 5 */
    degtwo5;           /* location on edge list                         */
//printf("identifySixesA\n");


switch( degseq )
  {  /* 1 */




     case 303:   
       { /* 2 */
         /* s30 g163 h918 */

          tutteMat1[0][1]=1;   
          tutteMat1[0][2]=4;   
          tutteMat1[0][3]=6;   
          tutteMat1[0][4]=4;   
          tutteMat1[0][5]=1;   
          tutteMat1[1][0]=1;   
          tutteMat1[1][1]=6;   
          tutteMat1[1][2]=9;   
          tutteMat1[1][3]=4;   
          tutteMat1[2][0]=3;
          tutteMat1[2][1]=6;
          tutteMat1[2][2]=3;
          tutteMat1[3][0]=2;
          tutteMat1[3][1]=3;
          tutteMat1[4][0]=1;   
       } /* 2 */
       break;

     case 2004:
       /* s18 g161 h91 */
       { /* 5 */
  
          tutteMat1[0][1]=1;   
          tutteMat1[0][2]=4;   
          tutteMat1[0][3]=6;   
          tutteMat1[0][4]=4;   
          tutteMat1[0][5]=1;   
          tutteMat1[1][0]=1;   
          tutteMat1[1][1]=4;   
          tutteMat1[1][2]=6;   
          tutteMat1[1][3]=4;   
          tutteMat1[2][0]=1;   
          tutteMat1[2][1]=4;
          tutteMat1[2][2]=6;   
          tutteMat1[3][0]=1;
          tutteMat1[3][1]=4;   
          tutteMat1[4][0]=1;
       } /* 5 */
       break; 

     case 1113: /* degree */
       {  /* 11 */ 
          /* s20 g162 h95 */
 
          tutteMat1[0][1]=1;   
          tutteMat1[0][2]=4;   
          tutteMat1[0][3]=6;   
          tutteMat1[0][4]=4;   
          tutteMat1[0][5]=1;   
          tutteMat1[1][0]=1;   
          tutteMat1[1][1]=5;   
          tutteMat1[1][2]=8;   
          tutteMat1[1][3]=4;   
          tutteMat1[2][0]=2;   
          tutteMat1[2][1]=6;
          tutteMat1[2][2]=4;   
          tutteMat1[3][0]=2;
          tutteMat1[3][1]=3;   
          tutteMat1[4][0]=1;

       } /* 11 */
       break;

     case 222:
       { /* 21 */ 
          vt = firstVertex(g);
          deg21 = nextofdegree(
                               g,
                               &vt,
                               TWO
                              );
          deg22 = nextofdegree(
                               g,
                               &vt,
                               TWO
                              );
          sum1 = degreesofnhbrs(
                                g,
                                deg21
                               );
          sum2 = degreesofnhbrs(
                                g,
                                deg22
                               );
          sum = sum1 + sum2;
          switch( sum )
            { /* 24 */
               case TWELVE:
                 { /* 25 */
                   /* s28 g169 h916 */
                    tutteMat1[0][1]=2;   
                    tutteMat1[0][2]=5;   
                    tutteMat1[0][3]=6;   
                    tutteMat1[0][4]=4;   
                    tutteMat1[0][5]=1;   
                    tutteMat1[1][0]=2;   
                    tutteMat1[1][1]=7;   
                    tutteMat1[1][2]=7;   
                    tutteMat1[1][3]=4;
                    tutteMat1[2][0]=4;   
                    tutteMat1[2][1]=5;   
                    tutteMat1[2][2]=3;   
                    tutteMat1[3][0]=3;   
                    tutteMat1[3][1]=1;   
                    tutteMat1[3][2]=1;   
                    tutteMat1[4][0]=1;   
                 } /* 25 */
                 break;
               case FOURTEEN:
                 {  /* 27 */
                    if(sum1==sum2)
                       /* s26 g167 h911 */
                      { /* 28 */
      
                         tutteMat1[0][1]=1;   
                         tutteMat1[0][2]=4;   
                         tutteMat1[0][3]=6;   
                         tutteMat1[0][4]=4;   
                         tutteMat1[0][5]=1;   
                         tutteMat1[1][0]=1;   
                         tutteMat1[1][1]=6;   
                         tutteMat1[1][2]=9;   
                         tutteMat1[1][3]=4;   
                         tutteMat1[2][0]=3;   
                         tutteMat1[2][1]=7;   
                         tutteMat1[2][2]=3;
                         tutteMat1[3][0]=3;
                         tutteMat1[3][1]=2;
                         tutteMat1[4][0]=1;   
                      } /* 28 */
                    else
                       /* s32 g168 h920 */
                      { /* 29 */
       
                         tutteMat1[0][1]=2;   
                         tutteMat1[0][2]=6;   
                         tutteMat1[0][3]=7;   
                         tutteMat1[0][4]=4;   
                         tutteMat1[0][5]=1;   
                         tutteMat1[1][0]=2;   
                         tutteMat1[1][1]=8;   
                         tutteMat1[1][2]=8;   
                         tutteMat1[1][3]=3;   
                         tutteMat1[2][0]=4;   
                         tutteMat1[2][1]=6;   
                         tutteMat1[2][2]=3;   
                         tutteMat1[3][0]=3;
                         tutteMat1[3][1]=2;
                         tutteMat1[4][0]=1;

                      } /* 29 */
                 } /* 27 */
                 break;
               case FIFTEEN:
                 {  /* 210 */
                    /* s27 g166 h913 */
      

                    tutteMat1[0][1]=2;   
                    tutteMat1[0][2]=6;   
                    tutteMat1[0][3]=7;   
                    tutteMat1[0][4]=4;   
                    tutteMat1[0][5]=1;   
                    tutteMat1[1][0]=2;   
                    tutteMat1[1][1]=8;   
                    tutteMat1[1][2]=9;   
                    tutteMat1[1][3]=3;   
                    tutteMat1[2][0]=4;   
                    tutteMat1[2][1]=7;   
                    tutteMat1[2][2]=2;   
                    tutteMat1[3][0]=3;   
                    tutteMat1[3][1]=2;   
                    tutteMat1[4][0]=1;   
                 } /* 210 */
                 break;
               case SIXTEEN:
                 {   /* 212 */
                    /* s31 g170 h919 */
     

                    tutteMat1[0][1]=2;   
                    tutteMat1[0][2]=7;   
                    tutteMat1[0][3]=8;   
                    tutteMat1[0][4]=4;   
                    tutteMat1[0][5]=1;   
                    tutteMat1[1][0]=2;   
                    tutteMat1[1][1]=9;   
                    tutteMat1[1][2]=10;   
                    tutteMat1[1][3]=2;   
                    tutteMat1[2][0]=4;   
                    tutteMat1[2][1]=8;   
                    tutteMat1[2][2]=1;
                    tutteMat1[3][0]=3;
                    tutteMat1[3][1]=2;
                    tutteMat1[4][0]=1;   

                 } /* 212 */
                 break;
            } /* 24 */   
      } /* 21 */         
      break;
  
    case 1032:
      { /* 31 */ 
         vt = firstVertex(g);
         deg5 = nextofdegree(
                             g,
                             &vt,
                             FIVE
                            );
         ne = firstEdge(g, deg5); 
         degtwo5 = nextdegnadjtov(
                                  g,
                                  &ne,
                                  TWO
                                 );
         sum = degreesofnhbrs(
                              g,
                              degtwo5
                             );
         if( sum == EIGHT ) 
              /*s19  g164 h92 */
           { /* 34 */
  
              tutteMat1[0][1]=1;   
              tutteMat1[0][2]=4;   
              tutteMat1[0][3]=6;   
              tutteMat1[0][4]=4;   
              tutteMat1[0][5]=1;   
              tutteMat1[1][0]=1;   
              tutteMat1[1][1]=6;   
              tutteMat1[1][2]=9;   
              tutteMat1[1][3]=4;   
              tutteMat1[2][0]=3;   
              tutteMat1[2][1]=7;
              tutteMat1[2][2]=3;   
              tutteMat1[3][0]=3;
              tutteMat1[3][1]=2;
              tutteMat1[4][0]=1;
           } /* 34 */
         else 
               /* s21 g165 h96 */
           { /* 35 */
   
              tutteMat1[0][2]=2;   
              tutteMat1[0][3]=5;   
              tutteMat1[0][4]=4;   
              tutteMat1[0][5]=1;   
              tutteMat1[1][1]=4;   
              tutteMat1[1][2]=9;   
              tutteMat1[1][3]=5;   
              tutteMat1[2][0]=2;   
              tutteMat1[2][1]=7;
              tutteMat1[2][2]=3;   
              tutteMat1[3][0]=3;
              tutteMat1[3][1]=1;
              tutteMat1[3][2]=1;   
              tutteMat1[4][0]=1;
           } /* 35 */
      }   /* 31 */ /* end deg3 = 3 */
      break;

    case 141: 
      { /* 41 */ 
         vt = firstVertex(g);
         deg2 = nextofdegree(
                             g,
                             &vt,
                             TWO
                            );
         ne = firstEdge(g, deg2); 
         deg21 = vertListOtherEnd(g, ne);  
         ne = nextEdge(g, ne);  
         deg22 = vertListOtherEnd(g, ne);  
         sum = ZERO;
         sum = sum + vertDegree(g, deg21) 
                + vertDegree(g, deg22);  
         switch( sum )
           { /* 43 */
              case SIX:

                {  /* 44 */ 
                  /* s23 g171 h98 */
     
                   tutteMat1[0][1]=3;   
                   tutteMat1[0][2]=7;   
                   tutteMat1[0][3]=7;   
                   tutteMat1[0][4]=4;   
                   tutteMat1[0][5]=1;   
                   tutteMat1[1][0]=3;   
                   tutteMat1[1][1]=10;   
                   tutteMat1[1][2]=8;   
                   tutteMat1[1][3]=3;   
                   tutteMat1[2][0]=6;   
                   tutteMat1[2][1]=6;
                   tutteMat1[2][2]=2;   
                   tutteMat1[3][0]=4;
                   tutteMat1[3][1]=1;
                   tutteMat1[4][0]=1;   
                } /* 44 */
                break;
              case SEVEN:
                { /* 46 */ 
                   if( isadj(deg21,deg22,g) )
                      /* s24 g172 h99 */
                     { /* 47 */ 
      
                        tutteMat1[0][1]=2;   
                        tutteMat1[0][2]=6;   
                        tutteMat1[0][3]=7;   
                        tutteMat1[0][4]=4;   
                        tutteMat1[0][5]=1;   
                        tutteMat1[1][0]=2;   
                        tutteMat1[1][1]=9;   
                        tutteMat1[1][2]=10;   
                        tutteMat1[1][3]=3;   
                        tutteMat1[2][0]=5;   
                        tutteMat1[2][1]=8;
                        tutteMat1[2][2]=1;   
                        tutteMat1[3][0]=4;
                        tutteMat1[3][1]=1;
                        tutteMat1[4][0]=1;   

                     } /* 47 */
                   else
                      /* s25 h910 */
                     { /* 48 */
                        tutteMat1[0][1]=3;   
                        tutteMat1[0][2]=8;   
                        tutteMat1[0][3]=8;   
                        tutteMat1[0][4]=4;   
                        tutteMat1[0][5]=1;   
                        tutteMat1[1][0]=3;   
                        tutteMat1[1][1]=11;   
                        tutteMat1[1][2]=9;   
                        tutteMat1[1][3]=2;   
                        tutteMat1[2][0]=6;   
                        tutteMat1[2][1]=7;   
                        tutteMat1[2][2]=1;
                        tutteMat1[3][0]=4;
                        tutteMat1[3][1]=1;
                        tutteMat1[4][0]=1;   

                     } /* 48 */
                } /* 46 */
                break; /* end sum=7 case */ 
          } /* 43 *//* end switch sum */ 
      } /* 41 */    
      break;


    case 60:/* is there a triangle */
      { /* 61 */ 
         vt = firstVertex(g);
         deletevrtx(
                    g,
                    vt
                   );/* note that vt has no meaning after deletion*/
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
         if( isadj(d31,d32,g) )
           { /* s22 g174 h97 67 */
  
              tutteMat1[0][1]=4;   
              tutteMat1[0][2]=9;   
              tutteMat1[0][3]=8;   
              tutteMat1[0][4]=4;   
              tutteMat1[0][5]=1;   
              tutteMat1[1][0]=4;   
              tutteMat1[1][1]=13;   
              tutteMat1[1][2]=9;   
              tutteMat1[1][3]=2;   
              tutteMat1[2][0]=8;   
              tutteMat1[2][1]=7;   
              tutteMat1[3][0]=5;
              tutteMat1[4][0]=1;   


           } /* 67 */
         else
           { /* s29 g175 h917  66 */

              tutteMat1[0][1]=5;   
              tutteMat1[0][2]=11;   
              tutteMat1[0][3]=10;   
              tutteMat1[0][4]=4;   
              tutteMat1[0][5]=1;   
              tutteMat1[1][0]=5;   
              tutteMat1[1][1]=15;   
              tutteMat1[1][2]=9;   
              tutteMat1[2][0]=9;   
              tutteMat1[2][1]=6;   
              tutteMat1[3][0]=5;   
              tutteMat1[4][0]=1;   



           } /* 66 */
     } 
     break; /* end case 60 */
  default:
    {
       printf("identifySixesA2\n");
       break;
    }


  } /* end case on degseq */

} /* end identifySixesA2 */


/*                                          */
/*           end of identifySixesA2         */
/*                                          */
/********************************************/



