
#include <memory.h>
#include <stdio.h>
//#include <gmp.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "graph.h"

/* Operations on fields in a vertex cell */


/*
Precondition: a graph g and the location of a vertex on the
              vertex list of g
Postcondition: no change

Return: the location of the next vertex after vt on g's vertex list
*/

int
nextVertex(struct Graph *g,int  vt)
{
return( (*g).vrtx[vt].nvert );
}


/*
Precondition: a graph g and the location of a vertex on the
              vertex list of g
Postcondition: no change

Return: the location of the vertex before vt on g's vertex list
*/
int
prevVert( struct Graph *g, int vt)
{
return( (*g).vrtx[vt].pvert );
}

/*
Precondition: a graph g and the location of a vertex on the
              vertex list of g
Postcondition: no change

Return: the location of theheader cell for the edge list of vt 
*/
int
headEdgeList( struct Graph *g, int vt)
{
return( (*g).vrtx[vt].fedge );
}

/*
Precondition: a graph g and the location of a vertex on the
              vertex list of g
Postcondition: no change

Return: the value in vt's visit field-used in dfs
*/
int vertVisited( struct Graph *g, int vt)
{
return((*g).vrtx[vt].visit);
}

/*
Precondition: a graph g and the location of a vertex on the
              vertex list of g
Postcondition: no change

Return: the name of the vertex at vt 
*/
int
vertName( struct Graph *g, int vt)
{
return((*g).vrtx[vt].vname);
}

/*
Precondition: a graph g and the location of a vertex on the
              vertex list of g
Postcondition: no change

Return: the degree of the vertex at vt 
*/
int
vertDegree( struct Graph *g, int vt)
{
return((*g).vrtx[vt].degree);
}

/*
Precondition: a graph (g), the location of a vertex on the
              vertex list of g (vt), and the value the next
               field of vt should be set to
Postcondition: the next field for vt is set to vt1 

*/
void
setNextVertex( struct Graph *g, int vt,int  vt1)
{
(*g).vrtx[vt].nvert = vt1;
}

/*
Precondition: a graph (g), the location of a vertex on the
              vertex list of g (vt), and the value the next
               field of vt should be set to
Postcondition: the previous vertex field for vt is set to vt1 

*/
void
setPrevVert( struct Graph *g, int vt,int  vt1)
{
(*g).vrtx[vt].pvert = vt1;
}
/*
Precondition: a graph g, the location of a vertex on the
              vertex list of g, and a value to be the degree
              of vt
Postcondition: the degree of the vertex at vt is set to amt 

*/
void
setVertDegree( struct Graph *g, int vt,int  amt)
{
(*g).vrtx[vt].degree = amt;
}


/*
Precondition: a graph g, the location of a vertex on the
              vertex list of g, and a value for the visit
              field of vt
Postcondition: the visit field of vt is set to amt 

*/
void 
setVertVisited( struct Graph *g, int vt,int amt)
{
(*g).vrtx[vt].visit = amt;
}


/*
Precondition: a graph g, the location of a vertex on the
              vertex list of g, and an increment for the degree
              of v=the vertex at vt
Postcondition: the degree of the vertex at vt is incremented by amt 

*/
void
incrVertDegree( struct Graph *g, int vt,int  amt)
{
(*g).vrtx[vt].degree += amt;
}



/* Operations on fields in an edge cell */

/*
Precondition: a graph g and the location of an edge on some 
              edgelist of g
Postcondition: no change

Return: the location of the next edgeafter ne on this edge list
*/
int
nextEdge( struct Graph *g, int ne)
{
return( (*g).edg[ne].front );
}

/*
Precondition: a graph g and the location of an edge on some 
              edge list of g
Postcondition: no change

Return: the location of the edge before ne's edge on 
        this edge list
*/
int
prevEdge( struct Graph *g, int ne)
{ 
return((*g).edg[ne].back);
}


/*
Precondition: a graph g and the location of an edge on some 
              edge list of g
Postcondition: no change

Return: the location of the vertex list that belongs to the vertex
        that is at the other end of the edge pointed to by ne
*/
int
vertListOtherEnd( struct Graph *g, int ne)
{
return( (*g).edg[ne].vertlist );
}

/*
Precondition: a Graph g and the location of an edges on some 
              edge list of g
Postcondition: no change

Return: the value of the tree field at ne 
*/
int
edgeInSpTree( struct Graph *g, int ne)
{
return( (*g).edg[ne].tree );
}


/*
Precondition: a graph g and the location of an edge on some
              edge list of g
Postcondition: no change

Return: the name of the vertex that is at the other end 
        of the edge at ne 
*/
int
nameOtherEnd( struct Graph *g, int ne)
{
return((*g).edg[ne].ename);
}

/*
Precondition: a graph g and the location of an edge on some
              edge list of g
Postcondition: no change

Return: the location of the edge on the edge list of the 
        vertex on the other end of the en dat ne
        
*/
int
otherEndEntry( struct Graph *g, int ne)
{ 
return((*g).edg[ne].side);
}


/*
Precondition: a graph g and the location of a vertex on the
              vertex list of g
Postcondition: no change

Return: the location of the first cell(edge) after the header 
        on g's edge list
*/
int
firstEdge( struct Graph *g, int vt)
{
return( (*g).edg[(*g).vrtx[vt].fedge].front );
}

/*
Precondition: a graph g, the location of an edge on some
              edge list of g, and a value for the tree field
              at ne
Postcondition: the tree field at ne is set to amt 

*/
void
setEdgeInSpTree( struct Graph *g, int ne,int amt)
{
(*g).edg[ne].tree = amt;
}

/*
Precondition: a graph g, the location of an edge on some
              edge list of g, and a value for the tree field
              at ne
Postcondition: the tree field at ne is set to amt 

*/
void
setEdgeEndsInSpTree( struct Graph *g, int ne,int  amt)
{
(*g).edg[ne].tree = amt;
(*g).edg[(*g).edg[ne].side].tree = amt;
}

/*
Precondition: a graph g, the location of an edge on some
              edge list of g, and the location of the vertex 
              list of the vertex at the other end of the edge at ne
Postcondition: the vertlist field at ne is set to vt 

*/
void
setVertListOtherEndEntry( struct Graph *g, int ne,int  vt)
{
(*g).edg[ne].vertlist = vt;
}


/*
Precondition: a graph g, the location of an edge on some 
              edge list of g, and the name of the vertex
              at the other end of the edge at ne
Postcondition: the name field for the other end of the edge
               at ne is set to vt 

*/
void
setNameOtherEnd( struct Graph *g, int ne,int  vt)
{
(*g).edg[ne].ename = vt;
}

/*
Precondition: a graph g, the location of an edge on some 
              edge list of g, and the location of the next edge
              after the edge at ne
Postcondition: the next edge field at ne is set to ne1 

Return: the location of the next vertex after vt on g's vertex list
*/
void
setNextEdge (struct Graph *g,int  ne, int ne1)
{
(*g).edg[ne].front = ne1;
}

/*
Precondition: a graph g, the location of an edge on some 
              edge list of g, and the location of this edge
               on the edge list of the other end of the edge at ne
Postcondition: the location of the other entry for this edge is
               set to ne1 

Return: the location of the next vertex after vt on g's vertex list
*/
void
setOtherEndEntry(struct Graph *g,int  ne, int ne1)
{
(*g).edg[ne].side = ne1;
}

/*
Precondition: a graph g, the location of an edge on some
              edge list of g, and the location of the edge
              just before the dege at ne
Postcondition: the previous edge field at ne is set to ne1 

Return: the location of the next vertex after vt on g's vertex list
*/
void
setPrevEdge(struct Graph *g, int ne,int  ne1)
{
(*g).edg[ne].back = ne1;
}

/* Operations on fields in the graph header cell */


/*
Precondition: a graph g and the location of a vertex on the
              vertex list of g
Postcondition: no change

Return: the location of the next vertex after vt on g's vertex list
        is returned
*/
int
firstVertex( struct Graph *g)
{
return( (*g).vrtx[0].nvert );
}

/*
Precondition: a graph g
Postcondition: no change

Return: the number of vertices in the graph 
*/
int
numVertices( struct Graph *g)
{
return( (*g).v );
}

/*
Precondition: a graph g 
Postcondition: no change

Return: the number of edges in the graph
*/
int
numEdges( struct Graph *g)
{
return( (*g).e );
}

/*
Precondition: a graph g 
Postcondition: no change

Return: the number of vertices in the graph used to find
        the nuty invariant for g 
*/
int
multEdgeGphVert( struct Graph *g)
{
return((*g).vnew);
}

/*
Precondition: a graph g 
Postcondition: no change

Return: number of pendant edges that have been deleted 
*/
int
degOneDels( struct Graph *g)
{
return( (*g).minusone );
}


/*
Precondition: a graph g 
Postcondition: no change

Return: the number of degree two vertices that were in a triangle
        and have been deleted 
*/
int
triangleDels( struct Graph *g)
{
return( (*g).minustwo );
}
/*
Precondition: a graph g 
Postcondition: no change

Return: the number of loops detected and deleted
*/
int
getYPower( struct Graph *g)
{
return((*g).yPower);
}

/*
Precondition: a graph g and the location of the power
              n in x + y + y^2 + ... + y^n generated 
              as a factor in deleting multiple edges 
Postcondition: no change

Return: the power of the last term in the factor
        x + y + y^2 + ... + y^n 
*/
int
getMultCount(struct Graph *g,int  location)
{
return( (*g).multCount[location] );
}

/*
Precondition: a graph g
Postcondition: the number of factors generated by removing
               multiple edges is reduced by 1 

*/
void
removeMultCountValue( struct Graph *g)
{
--(*g).multCount[0];
}

/*
Precondition: a graph g and an array
Postcondition: the multCount array of g is copied into newMC 
               and then multCount is set to an empty stack 
*/
void
copyAndZeroMultCount(struct Graph *g, short int newMC[])
{
short int t;
int i;
t= (*g).multCount[0];
for(i=0; i <= t; i++)
{
  newMC[i] = (*g).multCount[i];
(*g).multCount[i]=0;
}
}


/*
Precondition: a graph g and an array newMC 
Postcondition: the multCount array of g is has its 
               nonzero entries set to the values in
               newMC 

Return: the location of the next vertex after vt on g's vertex list
*/
void
setMultCount(struct Graph *g,short int  newMC[])
{
int i;
short int t;
t=newMC[0];
for(i=0; i <= t; ++i)
  {
   (*g).multCount[i] = newMC[i];
}
}


/*
Precondition: a graph g, and a value amt for the number of
              vertices in g
Postcondition: the number of vertices field in g is set to amty 

Return: the location of the next vertex after vt on g's vertex list
*/
void
setNoVertices(struct Graph *g,int  amt)
{
(*g).v = amt;
}

/*
Precondition: a graph g, and a value amt for the number of
              edges in g
Postcondition: the number of edges field in g is set to amty 

*/
void
setNoEdges(struct Graph *g,int  amt)
{
(*g).e = amt;
}

/*
Precondition: a graph g and a value for the minusone field
Postcondition: the minusone field of g is set to amt 

*/
void
setMinusone(struct Graph *g, int amt)
{
(*g).minusone = amt;
}

/*
Precondition: a graph g and a value for the yPower field
Postcondition: the yPower field of g is set to amt 

*/
void
setYPower(struct Graph *g, int amt)
{
(*g).yPower = amt;
}

/*
Precondition: a graph g and a value for the vnew field
Postcondition: the vnew field of g is set to amt 

Comment: the vnew field is the number of vertices in the
         grpah sent to nauty by g
*/
void
setVNew(struct Graph *g,int  amt)
{
(*g).vnew = amt;
}

/*
Precondition: a graph g and a value for the minustwo field
Postcondition: the minustwo field of g is set to amt 

Comment: the minustwo field records the number of triangle deletions
*/
void 
setMinustwo(struct Graph *g,int  amt)
{
(*g).minustwo = amt;
}

/*
Precondition: a graph g and a value for a new entry 
              on the multCount stack 
Postcondition: value is put on top of the multCount stack 

*/
void
setNewMultCount(struct Graph *g,int  value)
{
(*g).multCount[0]++;
(*g).multCount[(*g).multCount[0]] = value;
}

/*
Precondition: a graph g and a value for incrementing
              the yPower field(no loops detected and 
              deleted)
Postcondition: the yPower field of g is incremented
               by  amt 
*/
void
incrYPower(struct Graph *g,int  amt)
{
(*g).yPower +=amt;
}

/*
Precondition: a graph g and a value for incrementing
              the number of vertices in g
Postcondition: the number of vertices field of g is 
               incremented by amt 
*/
void
incrNoVertices(struct Graph *g,int  amt)
{
(*g).v += amt;
}


/*
Precondition: a graph g and a value for incrementing
              the number of edges in g
Postcondition: the number of edges field of g is 
               incremented by amt 
*/
void
incrNoEdges(struct Graph *g,int  amt)
{
(*g).e += amt;
}


/*
Precondition: a graph g and a value for incrementing
              the minustwo field in g
Postcondition: the minustwo field of g is incremented 
               by amt 
*/
void
incrTriangleDels(struct Graph *g,int  amt)
{
(*g).minustwo += amt;
}


/*
Precondition: a graph g and a value for incrementing
              the minusone field in g
Postcondition: the minusone field of g is incremented 
               by amt 
*/
int
incrDegOneDels(struct Graph *g,int  amt)
{
(*g).minusone += amt;
}













