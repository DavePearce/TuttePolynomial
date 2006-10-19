#include "tutte.h"




/**********************************************/
/*                                            */
/*           start of sevensDriver            */
/*                                            */
 
/* Procedures Called:

*/

void
sevensDriver (
              struct graph *g,
              TUTTE tutteMat,
              TUTTEO tutteMatX
             )
{
TUTTE tutteMat1;
TUTTEO tutteMat1X;
int i,
    j,
    k;
//printf("sevensDriver\n");

 for(i =ZERO;i<TUTTEROWS;++i)
    for (j = ZERO; j<TUTTECOLS;++j)
      {
       tutteMat1[i][j]=ZERO;
       tutteMat1X[i][j]=0;
     }
if( ( numEdges(g)  > 20 ) && ( numEdges(g) < 28 ) )
  printf("IN SEVENS BAD\n");
/* First break-down is by number of edges */
switch( numEdges(g) /*(*g).e*/ )
{
/* sevenPart1 handles |E|=21,20,19,18 */
 case 48:/* |E|=21 */
 case 46:/* |E|=20 */
 case 44:/* |E|=19 */ 
 case 42:/* |E|=18 */ 

  {/*printf("MORE THAN 17 EDGES (*g).e=%d\n",((*g).e-(*g).v+1)/2);*/
   sevenpart1(g,tutteMat1,tutteMat1X);
  }
 break;

/* sevenpart2 handles |E|=17,16 */
 case 40:/* |E|=17 */
 case 38:/* |E|=16 */
  {/*printf("MORE THAN 15 EDGES (*g).e=%d\n",((*g).e-(*g).v+1)/2);*/
   sevenpart2driver(g,tutteMat1,tutteMat1X);
  }
 break;
 
/* sevenpart3 handles |E|=15,14 */
 case 36:/* |E|=15 */
 case 34:/* |E|=14 */
  {/*printf("MORE THAN 13 EDGES (*g).e=%d\n",((*g).e-(*g).v+1)/2);*/
   sevenpart3dr(g,tutteMat1,tutteMat1X);
  }
 break;
 
 /* sevenpart4 handles |E|=13 */
 case 32:/* |E|=13 */
  {/*printf("13 EDGES (*g).e=%d\n",((*g).e-(*g).v+1)/2);*/
   sevenpart4(g,tutteMat1,tutteMat1X);
  }
 break;

/* sevenpart4a handles |E|=12,11,7 */
 case 30:/* |E|=12 */
 case 28:/* |E|=11 */
 case 20:/* |E|=7 */
  {/*printf("7,11,12 EDGES(*g).e=%d\n",((*g).e-(*g).v+1)/2);*/
   sevenpart4a(g,tutteMat1,tutteMat1X);
  }
 break;


default:
{
printGraph(g);printf("BAD SEVEN GRAPH_DEFAULT IN SEVENS\n");
}
break;

}
//printf("GOINT TO MTWO from sevensDriver\n"); 
multiplyByFactors(
      g,
      tutteMat,
      tutteMatX,
      tutteMat1,
      tutteMat1X,
      degOneDels(g),  //(*g).minusone,
      triangleDels(g)  //(*g).minustwo
     );


} /* sevenDriver ends */
  
/*                                            */
/*           end of sevensDriver              */
/*                                            */
/**********************************************/
