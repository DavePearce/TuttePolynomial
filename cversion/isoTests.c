#include "tutte.h"

  
/**********************************************/
/*                                            */
/*           start of degreesofnhbrs          */
/*                                            */

/*

Precondition: a graph g and the location of one of its vertices vt

Postcondition: nothing changed

Return: the sum of the degrees of the neighbors of the vertex at vt

*/


int
degreesofnhbrs(
               struct graph *g,
               int vt
              )
{
int sum,
    ne1;

/* initialize the sum and then add the degree of each vertex at the
   other end of an edge incident to vt
*/
 sum = ZERO;
 for(ne1 = firstEdge(g, vt); ne1!= LIST_END; ne1 = nextEdge(g, ne1)) 
   { 
     sum += vertDegree(g, vertListOtherEnd(g, ne1)); 
   }
 return( sum );

}/* end degreesofnhbrs */

  
/*                                            */
/*           end of degreesofnhbrs            */
/*                                            */
/**********************************************/
/*                                            */
/*           start of nextofdegree            */
/*                                            */

/*

Precondition: a graph g, one of its vertices vt, and a target degree value

Postcondition: nothing is changed

Return: the location of the next vertex on the vertex list with degree
        as its degree 

*/


int
nextofdegree(
             struct graph *g,
             int *vt,
             int degree
            )
{
 int vt1;

 vt1 = ZERO;
 while ( *vt != LIST_END && vt1 == ZERO ) 
   {
    if( vertDegree(g, *vt) == degree )
      vt1 =*vt;
    *vt = nextVertex(g, *vt); 
 }
 return( vt1 );

}/* end nextofdegree */
  
/*                                            */
/*           end of nextofdegree              */
/*                                            */
/**********************************************/
/*                                            */
/*           start of nextcommonadj           */
/*                                            */

/*
Precondition: graph g and the location of two of its vertces-v1 and v2

Postcondition: nothing is changed

Return: the location of the last vertex on the vertex list that is
        adjacent to both the vertex at v1 and the vertex at v2 

*/


/* finds the index of the last vertex adjacent to both v1 and v2 */

int
nextcommonadj(
              struct graph *g,
              int v1,
              int v2
             )
{ 
int edgeLoc, 
    found, 
    lookfor, 
    startother;

 found = ZERO;
  for(edgeLoc = firstEdge(g, v1); edgeLoc != LIST_END; edgeLoc = nextEdge(g, edgeLoc))
   {
      lookfor = nameOtherEnd(g, edgeLoc);  
      for(startother = firstEdge(g, v2);
              startother != LIST_END;
                   startother = nextEdge(g, startother))
        {
           if ( nameOtherEnd(g, startother)  == lookfor ) 
             { 
                found = vertListOtherEnd(g, edgeLoc);  
             }
        } 
   }
 

return( found );

} /* end nextcommonadj */


  
/*                                            */
/*           end of nextcommonadj             */
/*                                            */
/**********************************************/
/*                                            */
/*           start of commonadj               */
/*                                            */


/*

Precondition: graph g and the location of two of its vertices
              on the vertex list

Postcondition: nothing changed

Return: the number of common adjacencies for the two vertices at
        v1 and v2

*/

int
commonadj(
          struct graph *g,
          int v1,
          int v2
         )
{ 
int start, 
    found, 
    lookfor, 
    startother;
/* for each edge on the edge list for the vertex at v1
   examine the end of each edge on the edge list for
   the vertex at v2--when other ends match increment
*/
 
 found = ZERO;
 for(start = firstEdge(g, v1); start != LIST_END; start= nextEdge(g, start))
   {
      lookfor = nameOtherEnd(g, start);  
      for(startother = firstEdge(g, v2); startother != LIST_END; startother = nextEdge(g, startother))
        {
           if ( nameOtherEnd(g, startother)  == lookfor ) 
             {
                ++found; 
             }
        } 
   }

return( found );

} /* end commonadj */

  
/*                                            */
/*           end of commonadj                 */
/*                                            */
/**********************************************/
/*                                            */
/*           start of nextdegnadjtov          */
/*                                            */


/*
Precondition: a graph g and the location of an edge on one of
              its edge lists along with a target degree for
              the vertex sought

Postcondition: nothing changed

Return: the location of a vertex of degree equals degree that
        is adjacent to the vertex that is the vertex for
        which ne1 is an edge on its edge list

*/


/* finds next vertex of degree n adjacent to v that follows ne1
   in the adjacency list of v */

int 
nextdegnadjtov(
               struct graph *g,
               int *ne1,
               int degree
              )
{
 int vt;

 vt = ZERO;
 while ( ( *ne1 != LIST_END ) && ( vt == ZERO ) ) 
   {
      if ( vertDegree(g, vertListOtherEnd(g, *ne1)) == degree ) 
        {
           vt = vertListOtherEnd(g, *ne1);  
        }
      *ne1 = nextEdge(g, *ne1);  
   } 
 
return( vt );

}/* end nextdegnadjtov */

  
/*                                            */
/*           end of nextdegnadjtov            */
/*                                            */
/**********************************************/
/*                                            */
/*           start of nodegnadjtov            */
/*                                            */


/*

Precondition: graph g and the location of oneof its vertices
              as well as a target degree-n

Postcondition: nothing changed

Return: the number of vertices of degree n adjacent to the vertex
        at vt

*/


int
nodegnadjtov(
             struct graph *g,
             int vt,
             int n
            )


{
int non,
    ne1;

 non = ZERO;
 for(ne1 = firstEdge(g, vt); ne1 != LIST_END; ne1 = nextEdge(g, ne1))
   { /* 3 */
      if ( vertDegree(g, vertListOtherEnd(g, ne1)) == n) 
        {
           ++non;
        }
   } /* 3 */


return( non );

}/* end nodegnadjtov */
  
/*                                            */
/*           end of nodegnadjtov              */
/*                                            */
/**********************************************/
/*                                            */
/*           start of isadj                   */
/*                                            */

/*

Precondition: a graph g and the location of two of its vertices-vt1 and vt2

Postcondition: nothing changed

Return: 1 if the vertces at vt1 and vt2 are adjacent
        0 if the vertices at vt1 and vt2 are not adjacent

*/


/* determines whether vt1 and vt2 are adjacent or not */

int
isadj(
      int vt1, 
      int vt2,
      struct graph *g
     )
{
int adj,
    ne;

 adj = ZERO;
 ne = firstEdge(g, vt1);  
 while ( ne != LIST_END && adj == ZERO ) 
   {
      if ( vertName(g, vt2)  == nameOtherEnd(g, ne) ) 
        {
           adj=ONE;
        }
      ne = nextEdge(g, ne);  
 } 


 return( adj );

}/* end isadj */
  
/*                                            */
/*                                            */
/*             end of isadj                   */
/*                                            */
/**********************************************/
/*                                            */
/*           start of isadjedgename           */
/*                                            */


/*

Precondition: a graph g and the location of two of its vertices-vt1 and vt2

Postcondition: nothing changed

Return: location of the edge that joins the vertices at vt1 and vt2
        MINUSONE if the vertices are not adjacent 

*/

int
isadjedgename(
              int vt1, 
              int vt2,
              struct graph *g
             )
{
int adj,
    ne;

 adj = MINUSONE;
 ne = firstEdge(g, vt1);  
 while ( ( ne != LIST_END ) && ( adj == MINUSONE ) ) 
   {
      if ( vertName(g, vt2) == nameOtherEnd(g, ne) ) 
        {
           adj = ne;
        }
      ne = nextEdge(g, ne); 
   } 
 
return( adj );

}/* end isadjedgename */
  
/*                                            */
/*           end of isadjedgename             */
/*                                            */
/**********************************************/
/*                                            */
/*           start of nodegn                  */
/*                                            */


/*
Precondition: a graph g and the sought degree-n

Postcondition: nothing changed

Return: the number of degree n vertices in the graph

*/

int
nodegn(
       struct graph *g,
       int n
      )
{
int vt,
    non;

non = ZERO;
 for(vt = firstVertex(g); vt != LIST_END; vt = nextVertex(g, vt))
  {
     if ( vertDegree(g, vt)  == n ) 
       {
          ++non;
       }
  }


return( non );

}/* end nodegn */
  
/*                                            */
/*           end of nodegn                    */
/*                                            */
/**********************************************/
/*                                            */
/*           start of deletevrtx              */
/*                                            */

/*

Precondition: a graph g and the location of a vertex on its vertelist-vt

Postcondition: the graph has the vertex at vt deleted and all the edges
               adjacent to the vertex at vt deleted.

*/


/* deletes the edges adjacent to a vertex--used in recognition
   routines. does not need to remove the vertex from the vertex
   list--really just needs to adjust the degrees */
/* delete puts the edge pointer back up one--so in this case it goes back 
to the header cell */

void 
deletevrtx(
           struct graph *g,
           int vt
          )
{
int ne,
    v1,
    v2;

for(ne = firstEdge(g, vt); ne != LIST_END; ne = nextEdge(g, ne))
  {
     deleteEdge(
             ne,
             g
            );
  }
v1 = nextVertex(g, vt); 
v2 = prevVert(g, vt);  
setNextVertex(g, v2, v1);  
if ( v1 != LIST_END ) 
  {
     setPrevVert(g, v1, v2);  
  }
incrNoVertices(g, MINUSONE); 
incrNoEdges(g, MINUSONE);  

}/* end of deletevrtx */
  
/*                                            */
/*           end of deletevrtx                */
/*                                            */
/**********************************************/





