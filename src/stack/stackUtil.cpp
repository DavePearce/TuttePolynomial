#include "core/tutte.h"
#include <assert.h>
/* GLOBALS */

/**********************************************/
/*                                            */
/*           start of pushused                */
/*                                            */

/* 
Precondition: stack not full
   --0 <= C <= GRAPHSIZE - 1

Postcondition: top is advanced one location 
   in array places and C is put in new top of 
   stack location                             
*/
   
int
pushused(int C, struct stack *used)
{

if((*used).Top>GRAPHSIZE-FIVE)
  printf("used stack nearly full(*used).Top=%d\n" ,(*used).Top);

/*version two of the storage story*/
++(*used).Top;
assert((*used).Top<500);

if(stackDepthPush<(*used).Top)
  stackDepthPush=(*used).Top;

(*used).places[(*used).Top]=C;



}/* end pushused */
  
/*                                            */
/*           end of pushused                  */
/*                                            */
/**********************************************/
/**********************************************/
/*                                            */
/*           start of putonstack              */
/*                                            */
/* 
Precondition: 0 <= D <= GRAPHSIZE -1

Postcondition: D sent to pushused to be 
    put on used stack (g[D] saved for later
    processing                                
*/

/* stacking routine for vertex deletion generated graphs */
void 
putonstack(struct stack *used, int D)
{

  pushused(D,used); 

}
  
/*                                            */
/*           end of putonstack                */
/*                                            */
/**********************************************/
/*                                            */
/*           start of initavail               */
/*                                            */


/* 
Precondition: stack avail defined

Postcondition: stack location is initialized 
   to STACKSIZE - 1 -i where
    0 <= i <= STACKSIZE - 1. (Index of 
    available location in g[] for top of stack 
    is STACKSIZE - 1)                          
*/

void 
initavail( struct stack *avail)
{
int i;  /* for parameter   */

(*avail).Top=STACKSIZE - 1;
for(i=0;i< STACKSIZE;++i)
  (*avail).places[i]=STACKSIZE - 1 -i;

}
  
/*                                            */
/*           end of initavail                 */
/*                                            */
/**********************************************/
/*                                            */
/*           start of mtavail                 */
/*                                            */

/* 
Precondition: stack defined and initialized
 
Postcondition: return 1 if stack empty
                      0 if stack not empty  
               stack unchanged                            
*/
 
int 
mtavail( struct stack *avail)
{

if((*avail).Top == MINUSONE )
  {
     printf("Avail mt-Stack of graphs is full--message from mtavail\n");
     return( ONE );
  }
else 
  return( ZERO );

}/* end mtavail */

  
/*                                            */
/*           end of mtavail                   */
/*                                            */
/**********************************************/
/*                                            */
/*           start of pushavail               */
/*                                            */

/* 
Precondition: stack defined and initialized
 
Postcondition: top of stack moved down one
   location in places array and C is put in 
   new location pointed to by top of stack     
*/


void 
pushavail(int C, struct stack *avail)
{

if((*avail).Top>STACKSIZE - 1)
  printf("Problems with avail (*avail).Top=%d\n",(*avail).Top);

++(*avail).Top;
(*avail).places[(*avail).Top]=C;

}/* end pushavail */
  
/*                                            */
/*           end of pushavail                 */
/*                                            */
/**********************************************/
/*                                            */
/*           start of popavail                */
/*                                            */

/* 
Precondition: non-empty stack avail
 
Postcondition: value in location top is 
   returned and top is moved down one location 
   in array places                            
*/
   
int 
popavail( struct stack *avail)
{
/* when an index is popped the places value is reset to the initial 
value
which is zero */
int C;   /* index into graph array  */

if((*avail).Top==MINUSONE)
  printf("Nothing on avail to pop\n");

C=(*avail).places[(*avail).Top];
(*avail).places[(*avail).Top] = MINUSTHREE;

if(stackDepthPop > (*avail).Top)
  stackDepthPop=(*avail).Top;

--(*avail).Top;

return(C);

}/* end popavail */
  
/*                                            */
/*           end of popavail                  */
/*                                            */
/**********************************************/
/*                                            */
/*           start of initused                */
/*                                            */

/* 
Precondition: none
 
Postcondition: top of stack points one 
   position beyond first location in places
   no values put in places array             
 */

void  
initused( struct stack *used)
{

  (*used).Top=MINUSONE;

}/* end initused */
  
/*                                            */
/*           end of initused                  */
/*                                            */
/**********************************************/
/*                                            */
/*           start of fullused                */
/*                                            */

/* 
Precondition: stack defined and initialized
 
Postcondition: return 1 if stack is full
   (top = GRAPHSIZE - 1)
                         0 if stack not full
   (top != GRAPHSIZE - 1)
   stack is unchanged                          
*/

int 
fullused( struct stack *used)
{

if((*used).Top==GRAPHSIZE-1)
  {
     printf("used stack has no room to add a value-trouble\n");
     return( ONE );
  }
else
  return( ZERO );

} /* end fullused */
  
/*                                            */
/*           end of fullused                  */
/*                                            */
/**********************************************/
/*                                            */
/*           start of mtused                  */
/*                                            */

/* 
Precondition: stack defined and initialized
 
Postcondition: return 1 if stack empty (top = -1)
                      0 if stack non-empty (top != -1)
   stack is unchanged                          
*/

int 
mtused( struct stack *used)
{

if((*used).Top==MINUSONE)
  return( ONE );
else 
  return( ZERO );

}/* end mtused */
  
/*                                            */
/*           end of mtused                    */
/*                                            */
/**********************************************/
/*                                            */
/*           start of topused                 */
/*                                            */

/* 
Precondition: stack defined and initialized
 
Postcondition: stack unchanged. location of 
   top of stack in array places is returned   
*/

int 
topused( struct stack *used)
{

return ((*used).Top);

}/* end topused */
  
/*                                            */
/*           end of topused                   */
/*                                            */
/**********************************************/
/*           end of pushused                  */
/*                                            */
/**********************************************/
/*                                            */
/*           start of popused                 */
/*                                            */

/* 
Precondtion: 0 <= C <= GRAPHSIZE - 1 at 
location places[Top]
 
Postcondition: C returned, Top moved down 
   one location in places                     
*/
   
int 
popused( struct stack *used)
{
int C;  /* index into grah array   */

C=(*used).places[(*used).Top];
--(*used).Top;

return(C);

}/* end popused */

  
/*                                            */
/*           end of popused                   */
/*                                            */
/**********************************************/
/*                                            */
/*           start of MAKENULLQ               */
/*                                            */

/*
Precondition:

Postcondition:

*/


/* queue size 300*/ 
int
MAKENULLQ( struct queue *Q1)
{

 (*Q1).front = ONE;
 (*Q1).back = ZERO;

}/* end MAKENULLQ */
  
/*                                            */
/*           end of MAKENULLQ                 */
/*                                            */
/**********************************************/
/*                                            */
/*           start of EMPTYQ                  */
/*                                            */


/*
Precondition:

Postcondition:

*/

int
EMPTYQ( struct queue *Q1)
{

 if((*Q1).front > (*Q1).back)
   return( ONE);
 else
   return(ZERO);

}/* end EMPTYQ */
  
/*                                            */
/*           end of EMPTYQ                    */
/*                                            */
/**********************************************/
/*                                            */
/*           start of ENQUEUE                 */
/*                                            */


/*
Precondition:

Postcondition:

*/

void 
ENQUEUEQ(int placeincolor, struct queue *Q1)
{

 (*Q1).back=(*Q1).back + ONE;
 (*Q1).onqueue[(*Q1).back] = placeincolor;

}/* end ENQUEUE */
  
/*                                            */
/*           end of ENQUEUE                   */
/*                                            */
/**********************************************/
/*                                            */
/*           start of DEQUEUE                 */
/*                                            */


/*
Precondition:

Postcondition:

*/

void  
DEQUEUEQ( struct queue *Q1)
{

 (*Q1).front = (*Q1).front + ONE;

}/* end DEQUEUE */
  
/*                                            */
/*           end of DEQUEUE                   */
/*                                            */
/**********************************************/
/*                                            */
/*           start of FRONTQ                  */
/*                                            */


/*
Precondition:

Postcondition:

*/

int
FRONTQ( struct queue *Q1)
{

 return((*Q1).onqueue[(*Q1).front]);

}/* end FRONTQ */
  
/*                                            */
/*           end of FRONTQ                   */
/*                                            */
/**********************************************/

/* end of queue operations*/
