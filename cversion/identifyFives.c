#include "tutte.h"
#include <memory.h>


/**************************************************/
/*                                                */
/*         start of identifyFives                 */
/*                                                */

/*

Precondition: g is the address of a graph with five vertices
              tutteMat and tutteMatX are arrays holding the current 
              state of the computation 

Postcondition: tutteMat and tutteMatX are augmented by the tutte poly of
               *g.   

*/

void
identifyFives (
               struct graph *g, 
               TUTTE tutteMat,
               TUTTEO tutteMatX
              )
{

int deg3a,      /* location of degree three vertex */
    deg3b,
    degseq,     /* degseq for graph                */ 
    i,          /* for parameter                   */
    vt,         /* location of vertex              */
    vertLoc,
    deg[20];    /* array used to compute degseq	   */

/* graphs with five vertices */
//printf("identifyFives\n");

/*                                    */
/* compute degree sequence            */
/*                                    */  
for ( i = ZERO; i <= FIVE; ++i )  
  {
    deg[i] = ZERO;
  }
for(vertLoc = firstVertex(g); vertLoc != LIST_END; vertLoc = nextVertex(g, vertLoc))
  {
    ++deg[vertDegree(g, vertLoc)] ;
  }
degseq = deg[TWO] + 10 * deg[THREE] + 100 * deg[FOUR];

switch( degseq )
  {
    case FIVE:
      { /* 2 *//*g1 case e=14 start */
        /* g1 *//*printf("g1\n");*/
         tutteMat[0][1]=1;
         tutteMat[0][2]=1;
         tutteMat[0][3]=1;
         tutteMat[0][4]=1;
         tutteMat[1][0]=1;
         break;
      }   /* 2 */          /* case e = 14 end */

    case 104: 
      { /* 7 */ /*g2 degree */   /* threes=0 case start */
        /* g2 *//*printf("g2\n");*/
         tutteMat[0][4]=1;
         tutteMat[0][3]=2;
         tutteMat[0][2]=1;
         tutteMat[1][2]=2;
         tutteMat[1][1]=2;
         tutteMat[2][0]=1;
         break;
      }  /* 7 */    /* threes = 0 case finish */

    case TWENTYTHREE:/* are the two vertices of degree 3 adjacent */
      { /* 10 */
         vt = firstVertex(g);
         deg3a = nextofdegree(
                              g,
                              &vt,
                              THREE
                             );
         deg3b = nextofdegree(
                              g,
                              &vt,
                              THREE
                             );
         if( isadj( deg3a, deg3b, g ) ) 
           { /* 14 g43 *//* start case isadj = 1 */
             /* g3 *//*printf("g3\n")*/
              tutteMat[0][1]=1;
              tutteMat[0][2]=2;
              tutteMat[0][3]=2;
              tutteMat[0][4]=1;
              tutteMat[1][0]=1;
              tutteMat[1][1]=2;
              tutteMat[1][2]=1;
              tutteMat[2][0]=1;
           }  /* 14 */                  /* end case isadj = 1 */
         else
           {  /* 17 g44 */               /* start case isadj = 0 */
              /* g4 *//*printf("g4\n");*/
               tutteMat[0][1]=1;
               tutteMat[0][2]=3;
               tutteMat[0][3]=2;
               tutteMat[0][4]=1;
               tutteMat[1][0]=1;
               tutteMat[1][1]=3;
               tutteMat[2][0]=1;
           }  /* 17 */         /* end case isadj = 0 */
         break;
      } /* 10 */  /* end degree 3 cases */
    case 122: 
      { /*22 g48 */ /* degree */     /* case count2 = 1 */
        /* g5 *//*printf("g5\n");*/
         tutteMat[0][1]=1;
         tutteMat[0][2]=3;
         tutteMat[0][3]=3;
         tutteMat[0][4]=1;
         tutteMat[1][0]=1;
         tutteMat[1][1]=4;
         tutteMat[1][2]=3;
         tutteMat[2][0]=2;
         tutteMat[2][1]=2;
         tutteMat[3][0]=1;
         break;
      }   /* 22 */       /* end case count2 = 1 */
    case 203: /* g46 */
      { /* 25 */ /* degree */     /* case count >= 2 */
        /* g6 *//*printf("g6\n");*/
         tutteMat[0][1]=1;
         tutteMat[0][2]=3;
         tutteMat[0][3]=3;
         tutteMat[0][4]=1;
         tutteMat[1][0]=1;
         tutteMat[1][1]=3;
         tutteMat[1][2]=3;
         tutteMat[2][0]=1;
         tutteMat[2][1]=3;
         tutteMat[3][0]=1;
         break;
      }  /* 25 */   /* end case count2 >= 2 */
    case 41:
      { /* g47 */ /* degree */
        /* g7 *//*printf("g7\n");*/
         tutteMat[0][1]=2;
         tutteMat[0][2]=4;
         tutteMat[0][3]=3;
         tutteMat[0][4]=1; 
         tutteMat[1][0]=2;
         tutteMat[1][1]=5;
         tutteMat[1][2]=2;
         tutteMat[2][0]=3;
         tutteMat[2][1]=1;
         tutteMat[3][0]=1;
         break;     
      }

    case 221: /* g49 */ /* degree */
      { /* 31 */ /* start deg[2] = 1 */
        /* g8 *//*printf("g8\n");*/
         tutteMat[0][1]=2;
         tutteMat[0][2]=5;
         tutteMat[0][3]=4;
         tutteMat[0][4]=1;
         tutteMat[1][0]=2;
         tutteMat[1][1]=7;
         tutteMat[1][2]=5;
         tutteMat[2][0]=4;
         tutteMat[2][1]=5;
         tutteMat[3][0]=3;
         tutteMat[3][1]=1;
         tutteMat[4][0]=1;
         break;     
      } /* 31 */ /* end deg[2] = 1 */

    case 140: /* g50 */ /* degree */
      { /* 34  deg[2] = 0 */
        /* g9 *//*printf("g9\n");*/
         tutteMat[0][1]=3;
         tutteMat[0][2]=6;
         tutteMat[0][3]=4;
         tutteMat[0][4]=1;
         tutteMat[1][0]=3;
         tutteMat[1][1]=9;
         tutteMat[1][2]=4;
         tutteMat[2][0]=6;
         tutteMat[2][1]=4;
         tutteMat[3][0]=4;
         tutteMat[4][0]=1;
         break;
      } /* 34 */ /* end deg[2] = 0 */

    case 320:
      { /* 37  g51  start e = 22 */ /* degree */
        /* g10 *//*printf("g10\n");*/
         tutteMat[0][1]=4;
         tutteMat[0][2]=8;
         tutteMat[0][3]=5;
         tutteMat[0][4]=1;
         tutteMat[1][0]=4;
         tutteMat[1][1]=13;
         tutteMat[1][2]=7;
         tutteMat[2][0]=9;
         tutteMat[2][1]=9;
         tutteMat[3][0]=8;
         tutteMat[3][1]=2;
         tutteMat[4][0]=4;
         tutteMat[5][0]=1;
         break;
      }  /* 37 *//* end e = 22 */

    case 500:
      { /* 40  start e = 24 */ /* degree */
        /* g11 *//*printf("g11\n");*/
         tutteMat[0][1]=6;
         tutteMat[0][2]=11;
         tutteMat[0][3]=6;
         tutteMat[0][4]=1;
         tutteMat[1][0]=6;
         tutteMat[2][0]=15;
         tutteMat[3][0]=15;
         tutteMat[4][0]=10;
         tutteMat[5][0]=4;
         tutteMat[6][0]=1;
         tutteMat[1][1]=20;
         tutteMat[2][1]=15;
         tutteMat[3][1]=5;
         tutteMat[1][2]=10;
         break;
      }  /* 40  end e = 24 */
  

     default:
       {
          printf("identifyFives\n");
       }
     break;
  }/* end switch on degree sequence */


}   /* the end of five vertex graphs */


/*                                                */
/*         end of identifyFives                   */
/*                                                */
/**************************************************/



