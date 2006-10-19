
#define EXTDEFS 1		/* define before including naututil.h */
#include "naututil.h"		/* needed to call readgraph */
#include "tutte.h"
#include <memory.h>


/**********************************************/
/*                                            */
/*           start of retree                  */
/*                                            */

/*

Precondition: location of a graph g

Postcondition: the graph structure at the location g
               has a spanning tree identified

*/


/* retree takes the result of a degree three or degree
deletion and finds a new spanning tree in the connected graph */

void 
retree(
       struct graph *g
      )

{ /* start retree */
int vertLoc,         /* location of vertex */
    edgeLoc;         /* locations of edge  */
//printf("retree\n");     

/*                                                          */
/* retree finds a new spanning tree in the connected graph  */
/* has to reset visit in the vertex cell and span. tree. in */
/* each edge cell                                           */
/*                                                          */
for(vertLoc = firstVertex(g); 
       vertLoc != LIST_END; 
          vertLoc = nextVertex(g, vertLoc))
  {  /* 1 */

    setVertVisited(g, vertLoc, ZERO);  

    for(edgeLoc = firstEdge(g,vertLoc);
           edgeLoc != LIST_END; 
              edgeLoc = nextEdge(g, edgeLoc ))
     {  /* 2 */ 
        setEdgeInSpTree(g, edgeLoc, ZERO);  
      }  /* 2 */

  }  /* 1 */

/*                       */
/* now we are ready      */
/*                       */ 
findspan( g );

}  /* end of retree */

  
/*                                            */
/*           end of retree                    */
/*                                            */
/**********************************************/
/*                                            */
/*           start of nontree                 */
/*                                            */
/* fix for tutte-first non tree edges could be 
   a loop edge and that is not good!!! */

/*

Precondition: the location of a graph g

Postcondition: Nothing changed 

Return: the graph at g has an edge not
        in its spanning tree identified

*/


int
nontree(
        struct graph *g
       )
{
int vertLoc,               /* location of vetex */ 
    edgeLoc;              /* location of edge  */
//printf("nontree\n");

/* nontree(g) searches the structure represebnting g  */
/*  for an edge that is not in the spanning tree. the */
/*  search always starts with the first vertex        */
/*  the function returns the cell address of the      */
/*  edge that is not in the spanning tree. if         */
/*  an error condition arises the function returns    */
/*  LIST_END. if an error occurs the input data       */
/*                                                    */
for(vertLoc = firstVertex(g); vertLoc != LIST_END; vertLoc = nextVertex(g, vertLoc))
  { /* loop 1 */

     for(edgeLoc =firstEdge(g, vertLoc); edgeLoc !=LIST_END; edgeLoc=nextEdge(g, edgeLoc))
      { /* loop 2 */

         if ( ( edgeInSpTree(g, edgeLoc)  == ZERO ) 
                   && ( nameOtherEnd(g, edgeLoc) != vertName(g, vertLoc ) ) ) 
           { /* true range */
              return( edgeLoc );
           }  /* true range end */

      } /* loop 2 end */

  } /* loop 1 end */

printf("????\n"); 
printf("FOUND NO NON TREE EDGE\n"); 
return(MINUSONE);

} /* end nontree */

/*                                            */
/* end of nontree                             */
/*                                            */
/**********************************************/
/*                                            */
/*           start of detreeForContract       */
/*                                            */


/*
Precondition: a graph location g together with the location
              of a vertex in the graph (t1) and the location
              of an edge in the graph (e2)

Postcondition: the graph redesignates the tree edge that
               would make a cycle with the edge e2 as a nontree
               edge

*/



void 
detreeForContract(
                  int e2,
                  int t1,
                  struct graph *g
                 )
{
int vertLoc;     /* location of vertex */

/*                                                       */ 
/*   detreeForContract(e2,t1,g) starts a dfs at the      */
/*   vertex stored at cell t1. when a spanning tree      */
/*   edge is found that has e2 as its end that edge      */
/*   is designated as not in the spanning tree.          */
/*   this preserves a spanning tree in the               */
/*   contracted graph                                    */
/*   detreeForContract is merely the driver for untree   */
/*   the major task of detreeForContract is to reset the */
/*   visit field in the vertex cells to ZERO             */
/*   so that the dfs can keep track of visited vertices  */
/*                                                       */

/* prepare for depth first search of current spanning tree */
/* by setting the visit field entries back to zero.        */
for( vertLoc = firstVertex(g);vertLoc != LIST_END; vertLoc = nextVertex(g, vertLoc))
  {
     setVertVisited(g, vertLoc, ZERO);  
  }

untree(
       e2,
       t1,
       g
      );


}/* end detreeForContract */


/*                                            */
/*           end of detreeForContract                    */
/*                                            */
/**********************************************/
/*                                            */
/*           start of untree                  */
/*                                            */

/*

Precondition: the location of a graph (g), the location of one of its 
              vertices (t1), and the location of an edge incident
              to t1 (e2)

Postcondition: search on tree edges finds a tree edge that would
               complete a cycle with the edge at e2-this edge is
               redesignated as a nontree edge

*/


/*                                             */
/* search ends when a spanning tree edge with end e2
is found and that edge is designated as not in the
spanning tree */


int 
untree(
       int e2,
       int t1,
       struct graph *g
      )
{
int edgeLoc; /* location of edge */

/*                                                */
/* dfs search ends when a spanning tree edge with */
/* end e2 is found and that edge is designated as */
/* not in the spanning tree                       */
/*                                                */ 

/* code is a bit of a mess but it works for now */
/* a bit scary to redo it without lots of time and thought */

setVertVisited(g, t1, ONE);   /* mark vertex as visited */
edgeLoc = firstEdge(g, t1);  /* find cell with first edge */
while ( edgeLoc != LIST_END ) 
  {
     if ( edgeInSpTree(g, edgeLoc)  == ZERO ) 
       { /* non tree edges are ignored */
          edgeLoc = nextEdge(g, edgeLoc );  
       } /* proceed */
     else
       {/* major else */
          if ( ( edgeInSpTree(g, edgeLoc )  == ONE ) 
                      && ( nameOtherEnd(g, edgeLoc )  == e2 ) ) 
            {
               /* found tree edge that will make a cycle with e2 */
               setEdgeEndsInSpTree(g, edgeLoc, ZERO); 
               break; /* just return ? */
            } 
          else 
            {
               if ( ( edgeInSpTree(g, edgeLoc )  == ONE ) 
                    && ( nameOtherEnd(g, edgeLoc )  != e2 )
	            && ( vertVisited(g, vertListOtherEnd(g, edgeLoc ) ) == ZERO ) )
                 {
	  	    /* need triple condition or (a,b) causes 
	  	        you to go to b from a and then a from b */
                   /* continue dfs on tree edge */
                   untree(
                          e2,
                          vertListOtherEnd(g, edgeLoc ),  
                          g
                         );
                 }
               edgeLoc = nextEdge(g, edgeLoc); /* get next edge */
            }
    
    
       }/* end major else */
  }/* end while */

}/* end untree */

/*                                            */
/*           end of untree                    */
/*                                            */
/**********************************************/
/*                                            */
/*           start of findspan                */
/*                                            */



/*

Precondition: the location of a graph (g)

Postcondition: the graph is searched using a dfs
               approach

*/


int
findspan(
         struct graph *g
        )
{
int edgeLoc,   /* location of edge   */
    vertLoc;   /* location of vertex */

/*                                                */
/* driver for dfs of g. important side effect     */
/* is identifying the edges of a spanning tree    */
/* which allows the algorithm to terminate when   */
/* the graph is just a tree                       */
/*                                                */
for( vertLoc = firstVertex(g); 
        vertLoc != LIST_END; 
           vertLoc = nextVertex(g, vertLoc))
  {
     setVertVisited(g, vertLoc, ZERO);  
  }

for( vertLoc = firstVertex(g); 
        vertLoc != LIST_END; 
           vertLoc = nextVertex(g, vertLoc ))
  {

     if ( vertVisited(g, vertLoc )  == ZERO ) 
       {
          dfs(
              vertLoc,
              g
             );
       }

  } 

}/* end findspan */


/*                                            */
/*           end of findspan                  */
/*                                            */
/**********************************************/
/*                                            */
/*           start of dfs                     */
/*                                            */

/*

Precondition: the location of a graph (g) and 
              the location of a vertex (start)

Postcondition: a dfs is carried out starting at 
               the vertex at start.  dfs tree 
               edges are so designated

*/

/* plain old garden variety depth first search */

int 
dfs(
    int vertLoc,
    struct graph *g
   )
{
int ne;  /* location of edge */

setVertVisited(g, vertLoc, ONE); /* mark visited */
for(ne = firstEdge(g, vertLoc); 
      ne != LIST_END; 
         ne = nextEdge(g, ne))
  { /* loop 1 */ 

     if ( vertVisited(g, vertListOtherEnd(g, ne)) == ZERO ) 
       {
         setEdgeEndsInSpTree(g, ne, ONE); 
         dfs(
             vertListOtherEnd(g, ne), 
             g
            );
       } 

  } /* end loop 1 */

} /*end of dfs*/


/*                                            */
/*           end of dfs                       */
/*                                            */
/**********************************************/
/*                                            */
/*        start of detectAndComputeTree       */
/*                                            */


/* 

Precondition: a graph and the current state of the tutte polynomial

Postcondition: if the graph is a tree, the current state of the uttte
               polynomial is altered to reflect that fact and a signal
               is returned indicating the graph is a tree    

Return: 0 if the graph is not a tree
        1 if the graph is a tree
*/


/* routine that identifies a graph as a tree and increments
   treecount and otree appropriately by calling mtwo */

int detectAndComputeTrees(
                          struct graph *g,
                          TUTTE tutteMat,
                          TUTTEO tutteMatX
                         )

{
int i,    /* for parameter */
    j,
    m; 
TUTTE tutteMat1;
TUTTEO tutteMat1X;

if ( numVertices(g) != (( numEdges(g) - numVertices(g) + ONE ) / TWO + ONE)) 
  {
      return( ZERO );  // not a tree since connected
  }
else
  {  
     //printf("PROCESSING A TREE\n"); 
     /* have to find some nonzero entry location */
     /* to start the multiplication of factors   */
     /* collected along the way                  */ 
     /*                                          */
      /* initialize temp arrays for computing     */
     for( i = ZERO ; i < TUTTEROWS; ++i )
     for( j = ZERO; j < TUTTECOLS; ++j )
       {
          tutteMat1[i][j] = ZERO;
          tutteMat1X[i][j] = ZERO;
       }
     /* find a place to put a nonzero entry in the poly matrix */
     if( numVertices(g) <= ONE ) 
       {
 
          if( degOneDels(g)  != ZERO )
            {
               tutteMat1[ZERO][degOneDels(g)] = ONE;
               setMinusone(g, ZERO);  
            }
          else
            if( triangleDels(g)  != ZERO )
              {
                 tutteMat1[ZERO][ZERO] = ONE;
                 tutteMat1[ZERO][ONE] = ONE;
                 incrTriangleDels(g, MINUSONE);  
              }
            else
              if( getMultCount(g, ZERO) != ZERO )
                {
                   m = getMultCount(g, getMultCount(g, ZERO));
                   for( i = ONE; i <= m; ++i )
                     tutteMat1[i][ZERO] = ONE;
                   removeMultCountValue(g); 
                }
              else 
                {
                   tutteMat1[ZERO][ZERO] = ONE;
                } 
          /* contribute to final answer */ 
       //   multiplyByFactors(
        //                    g,
         //                   tutteMat,
          //                  tutteMatX,
           //                 tutteMat1,
            //                tutteMat1X,
             //               degOneDels(g), 
              //              triangleDels(g)  
               //            );
         // return( ONE ); 
       }
     else
       { 
          tutteMat1[ZERO][(*g).v - ONE] = ONE;
       }
          /* contribute to final answer */
          multiplyByFactors(
                            g,
                            tutteMat,
                            tutteMatX,
                            tutteMat1,
                            tutteMat1X,
                            degOneDels(g), 
                            triangleDels(g)  
                           );
           return(ONE); 
//        }  

  } 

} /* end of detectAndComputeTrees */

  
/*                                            */
/*       end of detectAndComputeTrees         */
/*                                            */
/**********************************************/






