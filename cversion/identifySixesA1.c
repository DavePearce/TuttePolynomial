#include "tutte.h"
#include <memory.h>

/********************************************/
/*                                          */
/*           start of identifySixesA        */
/*                                          */

/*

Preconditon: g points to a graph with six vertices and
             one of tfollowing as degree sequence: 6, 105, 24, 204
             1014, 123, or 42 
           
             tutteMat1 and tutteMat1X are arrays holding the current status of the
             computation of the tutte poly of g

Postcondition: tutteMat1 and tutteMat1X are augmented by the tutte poly of
               g

*/



void
identifySixesA1 (
                 struct graph *g,
                 int degseq,
                 TUTTE tutteMat1,
                 TUTTEO tutteMat1X
                )
{
int 
    nodegtwo,          /* number of degree 2 verteices 
    				adjacent to vertex                     */
    vt,                /* points to location on vertex list            */
    ne,                /* points to location on edge list              */
    sum,               /* accumulator for degrees of sets of vertices  */
    sum1,
    sum2,
    sum3,
    nsave1,            /* location on vertex list                       */
    nsave2,
    deg21,             /* location on vertex list of neighbors 
    				of degree 2 vertex                      */
    deg22,
    deg23,
    deg3,              /* location on vertex list of vertex of degree 3 */
    deg4;              /* location on vertex list of vertex of degree 4 */
//printf("identifySixesA1\n");


switch( degseq )
  {  /* 1 */

     case 6: 
       {  /* s1 g105 h67  2 */
          /*printf("s1\n");*/ 
          tutteMat1[0][1]=1;   
          tutteMat1[0][2]=1;   
          tutteMat1[0][3]=1;   
          tutteMat1[0][4]=1;   
          tutteMat1[0][5]=1;   
          tutteMat1[1][0]=1;   
       }  /* 2  end h.e==17 */
       break;

     case 105:
       { /* s5 g126  h713 */
          tutteMat1[0][2]=1;   
          tutteMat1[0][3]=2;   
          tutteMat1[0][4]=2;   
          tutteMat1[0][5]=1;   
          tutteMat1[1][1]=2;   
          tutteMat1[1][2]=2;   
          tutteMat1[1][3]=1;   
          tutteMat1[2][0]=1;   
       } /* 2 */
       break;

     case 24:
       { /* 3 */
          vt = firstVertex(g);
          deg3 = nextofdegree(
                              g,
                              &vt,
                              THREE
                             );
          nodegtwo = nodegnadjtov(
                                  g,
                                  deg3,
                                  TWO
                                 );
          if( nodegtwo == THREE )
            { /* s4 g129  h77 */ /* not adjacent */
              /*printf("s4\n");*/
               tutteMat1[0][1]=1;   
               tutteMat1[0][2]=3;   
               tutteMat1[0][3]=3;   
               tutteMat1[0][4]=2;   
               tutteMat1[0][5]=1;   
               tutteMat1[1][0]=1;   
               tutteMat1[1][1]=3;   
               tutteMat1[1][2]=1;   
               tutteMat1[2][0]=1;   
            } /* 6 */
          else
            { /* 7 */
               ne = firstEdge(g, deg3); 
               deg21 = nextdegnadjtov(
                                      g,
                                      &ne,
                                      TWO
                                     );
               deg22 = nextdegnadjtov(
                                      g,
                                      &ne,
                                      TWO
                                     );
               if( isadj(deg21,deg22,g) )
                 { /* s6 10 g130  h723 */
                    tutteMat1[0][3]=1;   
                    tutteMat1[0][4]=2;   
                    tutteMat1[0][5]=1;   
                    tutteMat1[1][2]=2;   
                    tutteMat1[1][3]=2;   
                    tutteMat1[2][1]=1;   
                 } /* 10 */
               else
                 { /* 11 */
                    sum = degreesofnhbrs(
                                         g,
                                         deg21
                                        );
                    sum += degreesofnhbrs(
                                          g,
                                          deg22
                                         ); 
                    if( sum == ELEVEN )
                      { /* s3 14 g127  h76 */
                         tutteMat1[0][1]=1;   
                         tutteMat1[0][2]=2;   
                         tutteMat1[0][3]=2;   
                         tutteMat1[0][4]=2;   
                         tutteMat1[0][5]=1;   
                         tutteMat1[1][0]=1;   
                         tutteMat1[1][1]=2;   
                         tutteMat1[1][2]=1;   
                         tutteMat1[1][3]=1;   
                         tutteMat1[2][0]=1;   
                      } /* 14 */
                    else
                      { /* s2 15 g128  h75 */  
                         tutteMat1[0][1]=1;   
                         tutteMat1[0][2]=2;   
                         tutteMat1[0][3]=3;   
                         tutteMat1[0][4]=2;   
                         tutteMat1[0][5]=1;   
                         tutteMat1[1][0]=1;   
                         tutteMat1[1][1]=2;   
                         tutteMat1[1][2]=2;   
                         tutteMat1[2][0]=1;   
                      } /* 15 */
                 } /* 11 */ 
            } /* 7 */
       } /* 3 */
       break;


     case 204:
       {  /* 4 */
          vt = firstVertex(g);
          deg4 = nextofdegree(
                              g,
                              &vt,
                              FOUR
                             );
          sum = degreesofnhbrs(
                               g,
                               deg4
                              );
          if( sum == EIGHT )
            { /* s14 f g146  h815 */
   
               tutteMat1[0][1]=1;   
               tutteMat1[0][2]=4;   
               tutteMat1[0][3]=6;   
               tutteMat1[0][4]=3;   
               tutteMat1[0][5]=1;   
               tutteMat1[1][0]=1;   
               tutteMat1[1][1]=4;   
               tutteMat1[1][2]=6;   
               tutteMat1[2][0]=1;   
               tutteMat1[2][1]=4;   
               tutteMat1[3][0]=1;   

            } /* f */
          else
            {  /* s16 g g145  h821 */ 
   
               tutteMat1[0][1]=1;   
               tutteMat1[0][2]=3;   
               tutteMat1[0][3]=4;   
               tutteMat1[0][4]=3;   
               tutteMat1[0][5]=1;   
               tutteMat1[1][0]=1;   
               tutteMat1[1][1]=3;   
               tutteMat1[1][2]=4;   
               tutteMat1[1][3]=2;   
               tutteMat1[2][0]=1;   
               tutteMat1[2][1]=3;   
               tutteMat1[2][2]=1;   
               tutteMat1[3][0]=1;   

           } /* g */
       }
     break;

     case 1014:
       { /* h */ /* numberdeg3 = 1 */
         /* s7 g144 h81 */

          tutteMat1[0][2]=1;   
          tutteMat1[0][3]=3;   
          tutteMat1[0][4]=3;   
          tutteMat1[0][5]=1;   
          tutteMat1[1][1]=2;   
          tutteMat1[1][2]=5;   
          tutteMat1[1][3]=3;   
          tutteMat1[2][0]=1;   
          tutteMat1[2][1]=3;   
          tutteMat1[2][2]=1;   
          tutteMat1[3][0]=1;   
       } /* h */ /* numberdeg3 = 1 */
       break;

     case 123:
       { /* j  deg[3] =  2 */
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
          deg23 = nextofdegree(
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
          sum3 = degreesofnhbrs(
                                g,
                                deg23
                               );
          // use += above and eliminate a number of variables
          sum = sum1 + sum2 + sum3;
          switch( sum )
            { /* n */
               case EIGHTEEN:
                 { /* o */
                    if( sum1 == sum2 )
                      { /*s13 p  g150 h814 */
       
                         tutteMat1[0][2]=1;
                         tutteMat1[0][3]=3;   
                         tutteMat1[0][4]=3;
                         tutteMat1[0][5]=1;   
                         tutteMat1[1][1]=2;   
                         tutteMat1[1][2]=5;   
                         tutteMat1[1][3]=3;   
                         tutteMat1[2][0]=1;   
                         tutteMat1[2][1]=3;
                         tutteMat1[2][2]=1;   
                         tutteMat1[3][0]=1;   


                      } /* p */ 
                    else
                      {/* r s12 g147  h812 */
      
                         tutteMat1[0][1]=1;   
                         tutteMat1[0][2]=3;
                         tutteMat1[0][3]=4;   
                         tutteMat1[0][4]=3;   
                         tutteMat1[0][5]=1;   
                         tutteMat1[1][0]=1;   
                         tutteMat1[1][1]=4;   
                         tutteMat1[1][2]=4;   
                         tutteMat1[1][3]=2;   
                         tutteMat1[2][0]=2;   
                         tutteMat1[2][1]=2;   
                         tutteMat1[2][2]=1;   
                         tutteMat1[3][0]=1;   

                      } /* r */
                 } /* o  end case 18 for sum */
                 break;
    
               case TWENTY:
                 { /* s15 t g148  h816 */ 
     

                    tutteMat1[0][1]=1;   
                    tutteMat1[0][2]=3;   
                    tutteMat1[0][3]=4;   
                    tutteMat1[0][4]=3;   
                    tutteMat1[0][5]=1;   
                    tutteMat1[1][0]=1;   
                    tutteMat1[1][1]=4;   
                    tutteMat1[1][2]=5;   
                    tutteMat1[1][3]=2;   
                    tutteMat1[2][0]=2;   
                    tutteMat1[2][1]=3;   
                    tutteMat1[3][0]=1;   
                 } /* t  end case 20 for sum */
                 break;
    
               case TWENTYONE:
                 { /*  s11 v g149  h89 */
    

                    tutteMat1[0][1]=1;   
                    tutteMat1[0][2]=4;   
                    tutteMat1[0][3]=5;   
                    tutteMat1[0][4]=3;   
                    tutteMat1[0][5]=1;   
                    tutteMat1[1][0]=1;   
                    tutteMat1[1][1]=5;   
                    tutteMat1[1][2]=5;   
                    tutteMat1[1][3]=1;   
                    tutteMat1[2][0]=2;   
                    tutteMat1[2][1]=3;   
                    tutteMat1[3][0]=1;   
                 } /* v  end case 21 for sum */
                 break;
            } /* n */ /* end switch sum */
       }/* j deg[3] ==  2 */
       break;

     case 42:
       { /* x  deg[3] == 4 */
          vt = firstVertex(g);
          deg21 = nextofdegree(
                               g,
                               &vt,
                               TWO
                              );
          sum = ZERO;
          ne = firstEdge(g, deg21); 
          nsave1 = vertListOtherEnd(g, ne); 
          sum += vertDegree(g, vertListOtherEnd(g, ne));  
          ne = nextEdge(g, ne); 
          nsave2 = vertListOtherEnd(g, ne);  
          sum += vertDegree(g, vertListOtherEnd(g, ne)); 
          switch( sum )
            { /* z */ /* start switch sum */
               case FIVE:
                 {/*  s10 ab g153  h87 */
     

                    tutteMat1[0][1]=2;   
                    tutteMat1[0][2]=4;   
                    tutteMat1[0][3]=4;   
                    tutteMat1[0][4]=3;   
                    tutteMat1[0][5]=1;   
                    tutteMat1[1][0]=2;   
                    tutteMat1[1][1]=5;   
                    tutteMat1[1][2]=3;   
                    tutteMat1[1][3]=2;   
                    tutteMat1[2][0]=3;   
                    tutteMat1[2][1]=1;  
                    tutteMat1[2][2]=1;  
                    tutteMat1[3][0]=1;  
                } /* ab */
                break;
   
              case SIX:
                { /* ac */
                   if(isadj(nsave1,nsave2,g))
                     {/* s8 ae g152  h85 */
     
                        tutteMat1[0][1]=1;   
                        tutteMat1[0][2]=3;   
                        tutteMat1[0][3]=4;   
                        tutteMat1[0][4]=3;   
                        tutteMat1[0][5]=1;   
                        tutteMat1[1][0]=1;   
                        tutteMat1[1][1]=4;   
                        tutteMat1[1][2]=5;   
                        tutteMat1[1][3]=2;   
                        tutteMat1[2][0]=2;   
                        tutteMat1[2][1]=3;   
                        tutteMat1[3][0]=1;   

                     } /* ac */	
                   else
                     { /* af */
                        sum1 = degreesofnhbrs(
                                              g,
                                              nsave1
                                             );
                        sum1 += degreesofnhbrs(
                                               g,
                                               nsave2
                                              );
                        if( sum1 == FIFTEEN )
                          {/* aj */ ent[9]=1;
                           /* s9 g151 h86 */
                             tutteMat1[0][1]=2;   
                             tutteMat1[0][2]=5;   
                             tutteMat1[0][3]=5;   
                             tutteMat1[0][4]=3;   
                             tutteMat1[0][5]=1;   
                             tutteMat1[1][0]=2;   
                             tutteMat1[1][1]=6;   
                             tutteMat1[1][2]=4;   
                             tutteMat1[1][3]=1;   
                             tutteMat1[2][0]=3;   
                             tutteMat1[2][1]=2;   
                             tutteMat1[3][0]=1;   
                          } /* aj */
                        else
                          { /* s17 al  g154 h823 */
                             tutteMat1[0][1]=2;   
                             tutteMat1[0][2]=5;   
                             tutteMat1[0][3]=6;   
                             tutteMat1[0][4]=3;   
                             tutteMat1[0][5]=1;   
                             tutteMat1[1][0]=2;   
                             tutteMat1[1][1]=6;   
                             tutteMat1[1][2]=5;   
                             tutteMat1[2][0]=3;   
                             tutteMat1[2][1]=2;   
                             tutteMat1[3][0]=1;   
                          } /* al */
                     } /* af */
                }/* ac */ /* end case 6 */
                break;

            } /* z  */  /* end switch sum */

       } /* x */
       break;



  default:
    {
       printf("identifySixesA1\n");
       break;
    }


  } /* end case on degseq */

} /* end identifySixesA1 */


/*                                          */
/*           end of identifySixesA1         */
/*                                          */
/********************************************/



