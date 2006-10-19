#define EXTDEFS 1		/* define before including naututil.h */
#include "naututil.h"		/* needed to call readgraph */
#include "tutte.h"


/**********************************************/
/*                                            */
/*           start of contract                */
/*                                            */

/*

Precondition: a graph g and the location in the vertex list of two of its
              vertices t1 and t2

Postcondition: the graph has the vertex t2 eliminated and all its
               adjacencies added to the adjacency list of t1
               any loops generated will be eliminated

*/

/* contract(t1,t2,g) takes the vertices in cells
  t1 and t2 of the vertyex adjacency list and
  appends the edge adjacencies of the t2 list to
  the end of the t1 list. a vertex adjacent to
  t2 will have the name of t2 changed to the name of t1.
*/

void 
contract(
         int t1, 
         int t2,
         struct graph *g
        )
{
int s1,                  /* edge locations for vertex t1              */
    s2,
    s2a,
    s3,                  /* edge locations for vertex t2              */
    s4,
    s4a,
    name1,               /* names of vertices t1 and t2               */
    name2,    
    v2,                  /* vertex list locations for vertex deletion */
    v3;
struct graph h;

//printf("contract\n");
/* t2's list added to t1's list */

incrVertDegree(g, t1, vertDegree(g, t2) );
s2 = firstEdge(g, t1);         
s2a = s2;
name1 = vertName(g, t1); 
name2 = vertName(g, t2);  


for(s2 = firstEdge(g, t1) ; s2 != LIST_END; s2 = nextEdge(g, s2))
  {
     s2a = s2;
  }

s4 = firstEdge(g, t2);      
/* change name from t2's name to t1's name */
s4a = s4;
for(s4a = firstEdge(g, t2) ; s4a != LIST_END; s4a = nextEdge(g, s4a))
  {
    setNameOtherEnd(g, otherEndEntry(g, s4a), vertName(g, t1));
    setVertListOtherEndEntry(g,otherEndEntry(g, s4a), t1); 


    setNameOtherEnd(g,otherEndEntry(g, s4a), vertName(g, t1));  
    setVertListOtherEndEntry(g,otherEndEntry(g, s4a), t1);
   
  }


setNextEdge(g, s2a, s4);  
setPrevEdge(g, s4, s2a); 
/* eliminate t2 from vertex list */

v2 = prevVert(g, t2);  
v3 = nextVertex(g, t2); 
setNextVertex(g, v2, v3);  
if( v3 != LIST_END ) 
  {
     setPrevVert(g, v3, v2);  
  }

/* take away count for other vertex and its edge list header*/ 
incrNoVertices(g, MINUSONE);  
incrNoEdges(g, MINUSONE);  

detectAndDeleteLoop(g);
retree(g);

} /* end of contract */

/*                                            */
/*           end of contract                  */
/*                                            */
/**********************************************/
/*                                            */
/*           start of areMultiple             */
/*                                            */

/*
Precondition: a graph located at g

Postcondition: nothing changed

Return: 1 if there is a multiple edge
        0 if there are no multiple edges

*/


int
areMultiple(
            struct graph *g
           )
{
int vt,             /* location of vertex                      */
    ne,             /* locations of edges                      */
    nne,
    namesDifferent; /* signal that multiple edges exist or not */
/* not currently called in program */

//printf("ENTERED AREMULTIPLE\n");
namesDifferent = ZERO;
for(vt = firstVertex(g); ( vt != LIST_END ) && ! ( namesDifferent ) ;vt = nextVertex(g, vt) ) 
  {
     for(ne = firstEdge(g, vt); ne != LIST_END; ne = nextEdge(g, ne))
       {
          if( nameOtherEnd(g, ne) == nameOtherEnd(g, nne) )
            {
               namesDifferent = ONE;
            }
       } /* end ne loop */
  } /* end vt loop */
 

return( namesDifferent );

}

/*                                            */
/*           end areMultiple                  */
/*                                            */
/**********************************************/
/*                                            */
/*           start of printGraph                */
/*                                            */


/*
Precondition: the location of a graph g

Postcondition: nothing changed

SideEffect: the data structure for the graph is displayed on the screen

*/



/* simple routine to list the multi-linked list 
   representation of the graph */


void
printGraph(
           struct graph *g
          )
{
int vt,   /* location of vertex */
    ed;   /* location of edge   */

printf("(*g).v=%d  (*g).e=%d m-one=%6d m-two=%6d yPower=%6d (*g).vnew=%6d\n",
                 (*g).v,(*g).e,(*g).minusone,(*g).minustwo, (*g).yPower,(*g).vnew);

for(vt = firstVertex(g); vt != LIST_END; vt = nextVertex(g, vt))
  { /* while more vertices */
     printf("vt=%d  vname = %4d nvert = %4d visit = %4d pvert = %4d degree = %4d fedge = %4d\n",
       vt, (*g).vrtx[vt].vname,
       (*g).vrtx[vt].nvert,
       (*g).vrtx[vt].visit,
       (*g).vrtx[vt].pvert,
       (*g).vrtx[vt].degree,
       (*g).vrtx[vt].fedge);
     for( ed = headEdgeList(g, vt); ed != LIST_END; ed = nextEdge(g, ed)) 
       { 
          printf(" ed=%d edgename=%6d vlist=%6d tree=%6d side=%6d back=%6d front=%6d\n",
            ed,
            (*g).edg[ed].ename,
            (*g).edg[ed].vertlist,
            (*g).edg[ed].tree,
            (*g).edg[ed].side,
            (*g).edg[ed].back,
            (*g).edg[ed].front);
       }
     printf("\n\n");
  }


}/* end printGraph */


/*                                            */
/*           end of printGraph                */
/*                                            */
/**********************************************/
/*                                            */
/*           start of loop                    */
/*                                            */

/*                                      */
/*
Precondition: the location of a graph g and the 
              location of one of its vertices-t1

Postcondition: Nothing changed

Return: LIST_END if a loop is found
        ZERO if no loop is found 

*/

/* loop(t1,g) uses the location of a vertex on the
    vertex linked list to check to see if there are
    and loops involving that vertex */
    /* should only use this as a check at the beginning
    of the processing of a graph as the algorithm will not
    generate any loops as a result of intermediate computations */

int 
loop(
     int t1,
     struct graph *g
    )
{
int name,   /* name of vertex that might have a loop incident */ 
    ne;     /* locations of edges on edge list of t1          */

name = vertName(g, t1); 
for(ne = firstEdge(g, t1); ne != LIST_END; ne = nextEdge(g, ne))
  {
     if ( nameOtherEnd(g, ne) == name )  
       {
          return( LIST_END );
       } 
  }

return( ZERO );

} /* end loop */


/*                                            */
/*           end of loop                      */
/*                                            */
/**********************************************/
/*                                            */
/*           start of copyGraph               */
/*                                            */

/*

Precondition: the location of a graph g and the instantiation of
              a second graph at k

Postcondition: the graph at g is copied to be the graph also at k

*/


/* the real time sink-copying a graph */
void 
copyGraph(
          struct graph *g,
          struct graph *k
         )
{
int i,        /* for parameter                              */
    vt,       /* vertex location                            */
    ne,       /* edge location                              */
    temp;     /* number of multiple edge removal operations */


temp = (*g).multCount[0];
for( i = ZERO; i <= temp;+ i++ )
  (*k).multCount[i] = (*g).multCount[i];

(*k).v = (*g).v;
(*k).e = (*g).e;
(*k).minusone = (*g).minusone;
(*k).minustwo = (*g).minustwo;
(*k).yPower = (*g).yPower;
(*k).vnew = (*g).vnew;

(*k).vrtx[ZERO] = (*g).vrtx[ZERO];

for(vt = firstVertex(g); vt != LIST_END; vt = nextVertex(g, vt))
  { 
     (*k).vrtx[vt] = (*g).vrtx[vt];
  } 

for(vt = firstVertex(g); vt != LIST_END; vt = nextVertex(g, vt))
  {
     for(ne = headEdgeList(g, vt); ne!= LIST_END; ne = nextEdge(g, ne))
       {
         (*k).edg[ne] = (*g).edg[ne];
       }
  }

}/* end copyGraph */

/*                                            */
/*           end of copyGraph                 */
/*                                            */
/**********************************************/
/*                                            */
/*           start of deleteEdge              */
/*                                            */
/*                                            */

/*
Precondition: a graph g and the location of an edge in g

Postcondition: the graph now has the edge deleted

Return: the kind of edge deleted-did it have a vertex of degree 1?
        did it have two vertices of degree 1? did it have
        no vertex of degree 1?
*/

int 
deleteEdge(
           int place,
           struct graph *g
          )
{
int t1,   /* parameters to delete entry on edge list */ 
    t2,
    t3,
    t4,
    t5,
    r,     /* vertex locations                               */
    s,   
    v1,    /* vertex locations for the other end of the edge */  
    v2,
    sendback; /* signal returned about kind of edge deleted */

t1 = prevEdge(g, place); 
t2 = nextEdge(g, place);  
t3 = otherEndEntry(g, place); 
t4 = prevEdge(g, t3); 
t5 = nextEdge(g, t3); 

/* other end*/
v1 = vertListOtherEnd(g, place);

/* vertex of place's list */
v2 = vertListOtherEnd(g, (*g).edg[place].side);  

setNextEdge(g, t1, t2);  
if( t2 != LIST_END )
  setPrevEdge(g, t2, t1);

setNextEdge(g, t4, t5);
if( t5 != LIST_END )
  setPrevEdge(g, t5, t4);  

if( ( vertDegree(g, v1) == ONE ) 
             && ( vertDegree(g, v2) == ONE ) )
  {

     setNextVertex(g, firstVertex(g), LIST_END);  
     setNoVertices(g, ONE);  
     setNoEdges(g, ZERO); 
     setVertDegree(g, firstVertex(g), ZERO);  
     sendback = ONE;
  }
else
  if(( vertDegree(g, v1)  == ONE ) 
       && ( vertDegree(g, v2) > ONE ) )
    {
       incrVertDegree(g, v2, MINUSONE);
       incrNoVertices(g, MINUSONE); 
       incrNoEdges(g, MINUSTHREE);  

       r = prevVert(g, v1);
       s = nextVertex(g, v1);
       setNextVertex(g, r, s); 
       if( s != LIST_END )
         setPrevVert(g, s, r);
       /* had nvert instead of pvert at the end 2/17 errorfind */

       sendback = TWO;

    }
  else
    if( ( vertDegree(g, v1)  > ONE ) 
    && ( vertDegree(g, v2)  == ONE ) )
      {
         incrVertDegree(g, v1, MINUSONE);  
         incrNoVertices(g, MINUSONE);
         incrNoEdges(g, MINUSTHREE);  
         r = prevVert(g, v2);
         s = nextVertex(g, v2);  
         setNextVertex(g, r, s);
         if( s != LIST_END )
           setPrevVert(g, s, r); 
          /* had nvert instead of pvert at the end 2/17 errorfind */
         sendback = TWO;
      }
    else
      if( ( vertDegree(g, v1) > ONE ) 
       && ( vertDegree(g, v2) > ONE ) )
        {
           incrNoEdges(g, MINUSTWO);
           incrVertDegree(g, v1, MINUSONE); 
           incrVertDegree(g, v2, MINUSONE);  
           sendback = ZERO;
        }

return( sendback );

}/* end deleteEdge */

/*                                            */
/*           end of deleteEdge                */
/*                                            */
/**********************************************/





