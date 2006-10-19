
#include "core/tutte.h"
#include <memory.h>


/********************************************/
/*                                          */
/*           start of identifySixesB        */
/*                                          */


/*
Precondition: g is a graph with six vertices and one of the following degree
              sequences: 402, 1410, 2301, 2121, 2220, 3030, 3210, 2400, 4200,
              6000, 1212, 2040, 1311, or 501 
              tutteMat1 and tutteMat1X are arrays holding the current status 
              of the computation of the tutte poly of g

Postcondition: tutteMat1 and tutteMat1X are augmented by the tutte poly of
		g

*/


void
identifySixesB1 (struct Graph *g,int  degseq,TUTTE   tutteMat1,TUTTEO tutteMat1X)
{
//printf("identifySixesB1\n");

switch( degseq )
  {  /* 1 */
     case 402: /* degree */
        /* s41 g181 h1011 degree */
       { /* 252 */
          tutteMat1[0][1]=2;
          tutteMat1[0][2]=7;
          tutteMat1[0][3]=9;
          tutteMat1[0][4]=5;
          tutteMat1[0][5]=1;
          tutteMat1[1][0]=2;
          tutteMat1[1][1]=10;
          tutteMat1[1][2]=14;
          tutteMat1[1][3]=6;
          tutteMat1[2][0]=5;
          tutteMat1[2][1]=13;
          tutteMat1[2][2]=7;
          tutteMat1[3][0]=6;
          tutteMat1[3][1]=6;
          tutteMat1[3][2]=1;
          tutteMat1[4][0]=3;
          tutteMat1[4][1]=2;
          tutteMat1[5][0]=1;
       } /* 252 */
       break;

     case 1212: /* degree */
         /* s33 g180 h101 degree */
       { /* 253 */
          tutteMat1[0][1]=2;
          tutteMat1[0][2]=7;
          tutteMat1[0][3]=9;
          tutteMat1[0][4]=5;
          tutteMat1[0][5]=1;
          tutteMat1[1][0]=2;
          tutteMat1[1][1]=10;
          tutteMat1[1][2]=14;
          tutteMat1[1][3]=6;
          tutteMat1[2][0]=5;
          tutteMat1[2][1]=12;
          tutteMat1[2][2]=7;
          tutteMat1[3][0]=5;
          tutteMat1[3][1]=7;
          tutteMat1[3][2]=1;
          tutteMat1[4][0]=3;
          tutteMat1[4][1]=2;
          tutteMat1[5][0]=1;
       } /* 253 */
       break;



     case 2121:/* degree */  
       { /* start case 1*/
         /* s45  g192  h111 degree  */
          tutteMat1[0][1]=4;
          tutteMat1[0][2]=12;
          tutteMat1[0][3]=13;
          tutteMat1[0][4]=6;
          tutteMat1[0][5]=1;
          tutteMat1[1][0]=4;
          tutteMat1[1][1]=18;
          tutteMat1[1][2]=22;
          tutteMat1[1][3]=8;
          tutteMat1[2][0]=10;
          tutteMat1[2][1]=22;
          tutteMat1[2][2]=12;
          tutteMat1[3][0]=11;
          tutteMat1[3][1]=15;
          tutteMat1[3][2]=2;
          tutteMat1[4][0]=8;
          tutteMat1[4][1]=6;
          tutteMat1[5][0]=4;
          tutteMat1[5][1]=1;
          tutteMat1[6][0]=1;
       } /* end case 1 */
       break;


     case 2040:/* degree */
       { /* start case 0*/
           /* s46  g195  h112 degree */
          tutteMat1[0][1]=4;
          tutteMat1[0][2]=12;
          tutteMat1[0][3]=13;
          tutteMat1[0][4]=6;
          tutteMat1[0][5]=1;
          tutteMat1[1][0]=4;
          tutteMat1[1][1]=20;
          tutteMat1[1][2]=24;
          tutteMat1[1][3]=8;
          tutteMat1[2][0]=12;
          tutteMat1[2][1]=26;
          tutteMat1[2][2]=10;
          tutteMat1[3][0]=15;
          tutteMat1[3][1]=14;
          tutteMat1[3][2]=2;
          tutteMat1[4][0]=11;
          tutteMat1[4][1]=4;
          tutteMat1[5][0]=5;
          tutteMat1[6][0]=1;
       } /* end case 0 */
       break;


     case 1311:/* degree */
       { /* start case 3*/
          /* s48  g193   h115 degree */
         tutteMat1[0][1]=4;
         tutteMat1[0][2]=12;
         tutteMat1[0][3]=13;
         tutteMat1[0][4]=6;
         tutteMat1[0][5]=1;
         tutteMat1[1][0]=4;
         tutteMat1[1][1]=19;
         tutteMat1[1][2]=23;
         tutteMat1[1][3]=8;
         tutteMat1[2][0]=11;
         tutteMat1[2][1]=24;
         tutteMat1[2][2]=11;
         tutteMat1[3][0]=13;
         tutteMat1[3][1]=14;
         tutteMat1[3][2]=2;
         tutteMat1[4][0]=9;
         tutteMat1[4][1]=5;
         tutteMat1[5][0]=4;
         tutteMat1[5][1]=1;
         tutteMat1[6][0]=1;
 
      } /* end case 3 */
      break;


    case 501:/* degree */
      { /* start case 5*/
         /* s52  g194  h119 degree */
         tutteMat1[0][1]=6;
         tutteMat1[0][2]=15;
         tutteMat1[0][3]=14;
         tutteMat1[0][4]=6;
         tutteMat1[0][5]=1;
         tutteMat1[1][0]=6;
         tutteMat1[1][1]=24;
         tutteMat1[1][2]=23;
         tutteMat1[1][3]=7;
         tutteMat1[2][0]=15;
         tutteMat1[2][1]=24;
         tutteMat1[2][2]=9;
         tutteMat1[3][0]=15;
         tutteMat1[3][1]=13;
         tutteMat1[3][2]=2;
         tutteMat1[4][0]=10;
         tutteMat1[4][1]=4;
         tutteMat1[5][0]=4;
         tutteMat1[5][1]=1;
         tutteMat1[6][0]=1;
      } /* end case 5 */
      break;


     case 1410:/* degree */
       { /* s56 g203 h124 degree */
          tutteMat1[0][1]=10;
          tutteMat1[0][2]=23;
          tutteMat1[0][3]=19;
          tutteMat1[0][4]=7;
          tutteMat1[0][5]=1;
          tutteMat1[1][0]=10;
          tutteMat1[1][1]=41;
          tutteMat1[1][2]=36;
          tutteMat1[1][3]=9;
          tutteMat1[2][0]=28;
          tutteMat1[2][1]=46;
          tutteMat1[2][2]=14;
          tutteMat1[3][0]=34;
          tutteMat1[3][1]=25;
          tutteMat1[3][2]=2;
          tutteMat1[4][0]=26;
          tutteMat1[4][1]=8;
          tutteMat1[5][0]=14;
          tutteMat1[5][1]=1;
          tutteMat1[6][0]=5;
          tutteMat1[7][0]=1;
      }  
       break;


    case 2301:/* degree */
      {  /* s55 g200 h123 degree */ 
         tutteMat1[0][1]=6;
         tutteMat1[0][2]=17;
         tutteMat1[0][3]=17;
         tutteMat1[0][4]=7;
         tutteMat1[0][5]=1;
         tutteMat1[1][0]=6;
         tutteMat1[1][1]=28;
         tutteMat1[1][2]=33;
         tutteMat1[1][3]=11;
         tutteMat1[2][0]=17;
         tutteMat1[2][1]=37;
         tutteMat1[2][2]=18;
         tutteMat1[3][0]=21;
         tutteMat1[3][1]=26;
         tutteMat1[3][2]=5;
         tutteMat1[4][0]=17;
         tutteMat1[4][1]=13;
         tutteMat1[5][0]=10;
         tutteMat1[5][1]=4;
         tutteMat1[6][0]=4;
         tutteMat1[6][1]=1;
         tutteMat1[7][0]=1;
      }
      break;

    case 2220:/* degree */
      { /* s53 g202 h121 degree */ 
         tutteMat1[0][1]=8;
          tutteMat1[0][2]=20;
         tutteMat1[0][3]=18;
         tutteMat1[0][4]=7;
         tutteMat1[0][5]=1;
         tutteMat1[1][0]=8;
         tutteMat1[1][1]=35;
         tutteMat1[1][2]=35;
         tutteMat1[1][3]=10;
         tutteMat1[2][0]=23;
         tutteMat1[2][1]=43;
         tutteMat1[2][2]=16;
         tutteMat1[3][0]=29;
         tutteMat1[3][1]=26;
         tutteMat1[3][2]=3;
         tutteMat1[4][0]=23;
         tutteMat1[4][1]=10;
         tutteMat1[5][0]=13;
         tutteMat1[5][1]=2;
         tutteMat1[6][0]=5;
         tutteMat1[7][0]=1;
      }  
      break;

    case 3030:/* degree */
      { /*  s54 g201 h122 degree */ 
         tutteMat1[0][1]=8;
         tutteMat1[0][2]=20;
         tutteMat1[0][3]=18;
         tutteMat1[0][4]=7;
         tutteMat1[0][5]=1;
         tutteMat1[1][0]=8;
         tutteMat1[1][1]=33;
         tutteMat1[1][2]=33;
         tutteMat1[1][3]=10;
         tutteMat1[2][0]=21;
         tutteMat1[2][1]=39;
         tutteMat1[2][2]=18;
         tutteMat1[3][0]=25;
         tutteMat1[3][1]=27;
         tutteMat1[3][2]=3;
         tutteMat1[4][0]=20;
         tutteMat1[4][1]=12;
         tutteMat1[5][0]=12;
         tutteMat1[5][1]=3;
         tutteMat1[6][0]=5;
         tutteMat1[7][0]=1;
      }
      break;

    case 3210:/* degree */
          /* s58 h131 g205 degree */
      {
          tutteMat1[0][1]=12;
          tutteMat1[0][2]=28;
          tutteMat1[0][3]=23;
          tutteMat1[0][4]=8;
          tutteMat1[0][5]=1;
          tutteMat1[1][0]=12;
          tutteMat1[1][1]=52;
          tutteMat1[1][2]=49;
          tutteMat1[1][3]=13;
          tutteMat1[2][0]=36;
          tutteMat1[2][1]=66;
          tutteMat1[2][2]=24;
          tutteMat1[3][0]=48;
          tutteMat1[3][1]=44;
          tutteMat1[3][2]=6;
          tutteMat1[4][0]=42;
          tutteMat1[4][1]=21;
          tutteMat1[5][0]=28;
          tutteMat1[5][1]=6;
          tutteMat1[6][0]=14;
          tutteMat1[6][1]=1;
          tutteMat1[7][0]=5;
          tutteMat1[8][0]=1;
 
      }
      break;

    case 2400: /* degree */
         /* s59 h132 g206 degree */
      {
          tutteMat1[0][1]=14;
          tutteMat1[0][2]=31;
          tutteMat1[0][3]=24;
          tutteMat1[0][4]=8;
          tutteMat1[0][5]=1;
          tutteMat1[1][0]=14;
          tutteMat1[1][1]=59;
          tutteMat1[1][2]=51;
          tutteMat1[1][3]=12;
          tutteMat1[2][0]=42;
          tutteMat1[2][1]=72;
          tutteMat1[2][2]=22;
          tutteMat1[3][0]=56;
          tutteMat1[3][1]=44;
          tutteMat1[3][2]=4;
          tutteMat1[4][0]=48;
          tutteMat1[4][1]=18;
          tutteMat1[5][0]=31;
          tutteMat1[5][1]=4;
          tutteMat1[6][0]=15;
          tutteMat1[7][0]=5;
          tutteMat1[8][0]=1;
      }
      break;

    case 4200:/* degree */
      {  /* s60 10  g207 degree */
         tutteMat1[0][1]=18;
         tutteMat1[0][2]=39;
         tutteMat1[0][3]=29;
         tutteMat1[0][4]=9;
         tutteMat1[0][5]=1;
         tutteMat1[1][0]=18;
         tutteMat1[1][1]=78;
         tutteMat1[1][2]=68;
         tutteMat1[1][3]=16;
         tutteMat1[2][0]=57;
         tutteMat1[2][1]=102;
         tutteMat1[2][2]=33;
         tutteMat1[3][0]=81;
         tutteMat1[3][1]=70;
         tutteMat1[3][2]=9;
         tutteMat1[4][0]=76;
         tutteMat1[4][1]=36;
         tutteMat1[5][0]=56;
         tutteMat1[5][1]=12;
         tutteMat1[6][0]=33;
         tutteMat1[6][1]=2;
         tutteMat1[7][0]=15;
         tutteMat1[8][0]=5;
         tutteMat1[9][0]=1;
      } 
      break;

    case 6000:/* degree */
      { /* s61 11 g208 degree */
         tutteMat1[0][1]=24;
         tutteMat1[0][2]=50;
         tutteMat1[0][3]=35;
         tutteMat1[0][4]=10;
         tutteMat1[0][5]=1;
         tutteMat1[1][0]=24;
         tutteMat1[1][1]=106;
         tutteMat1[1][2]=90;
         tutteMat1[1][3]=20;
         tutteMat1[2][0]=80;
         tutteMat1[2][1]=145;
         tutteMat1[2][2]=45;
         tutteMat1[3][0]=120;
         tutteMat1[3][1]=105;
         tutteMat1[3][2]=15;
         tutteMat1[4][0]=120;
         tutteMat1[4][1]=60;
         tutteMat1[5][0]=96;
         tutteMat1[5][1]=24;
         tutteMat1[6][0]=64;
         tutteMat1[6][1]=6;
         tutteMat1[7][0]=35;
         tutteMat1[8][0]=15;
         tutteMat1[9][0]=5;
         tutteMat1[10][0]=1;
      } /* 11 */ /* end h.e == 35 */
      break;
    default:
      {
         printf("identifySixesB\n");
         break;
      }


  } /* end case on degseq */

} /* end identifySixesB1 */


/*                                          */
/*           end of identifySixesB1          */
/*                                          */
/********************************************/


