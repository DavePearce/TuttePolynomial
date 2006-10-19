#define EXTDEFS 1		/* define before including naututil.h */
#include "naututil.h"		/* needed to call readgraph */
#include "tutte.h"



/**********************************************/
/*                                            */
/*           start of shuffl                  */
/*                                            */

/*
Precondition: array cards and number of elements in permutation

Postcondition: cards now has a permutation of 0, 1, ... , NCARDS
               in cards[0], cards[1], ... , cards[NCARDS]

*/


/*
Procedures Called:
shuffl(cards,NCARDS);
*/

/* routines to permute edges for more robustness */
void 
permEdges(
          int NCARDS,
          int cards[]
         )
{
short i;  /* for parameter  */
//printf("permEdges\n");
for ( i=ZERO; i <= NCARDS; ++i ) 
  {
     cards[i]=i;
  }
shuffl(cards,NCARDS);

}/* end permEdges */

/*                                            */
/*           end of permEdges                */
/*                                            */
/**********************************************/
/*                                            */
/*           start of shuffl                  */
/*                                            */

/*
Precondition: array deck and number of elements to find-NCARDS

Postcondition: the actual random shuffle takes place

*/

/*Procedures Called:
SYSTEM CALLS:
nfrom()
*/

int
shuffl(
       int deck[],
       int NCARDS
      )
{
short i,  /* for parameter and array indices */
      j,
      t;

/* removed declaration of nfrom */
srand(time(NULL));

for ( i = ZERO; i < NCARDS; ++i ) 
  {
 
     j = nfrom ( i, NCARDS );
     t = deck[j];
     deck[j] = deck[i];
     deck[i] = t;
  }

return(ONE);

}/* end shuffl */

/*                                            */
/*           end of shuffl                    */
/*                                            */
/**********************************************/
/*                                            */
/*           start of nfrom                   */
/*                                            */

/*
Precondition: two integers low and high that give the range for the
              random number

Postcondition: nothing changed

Return: a random integer in the range low--high

*/


/* SYSTEM CALLS:
rand()
*/

short int nfrom(
                short int low, 
                short int high
               )
{
short int nb;  /* range for random number */

nb = high-low+1;
return ( rand() % nb + low );

}/* end nfrom */

/* end of permutation of edges */

/*                                            */
/*           end of nfrom                     */
/*                                            */
/**********************************************/





