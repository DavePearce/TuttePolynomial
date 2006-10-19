#define EXTDEFS 1		/* define before including naututil.h */
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "graph.h"

/*
A set of utility functions that initialize, build, and
  manipulate a graph structure
*/


/**********************************************/
/*                                            */
/*           start of initGraph               */
/*                                            */

/*
  Precondition: graph data structure instantiated
  Postcondition: the graph structure is defined to be the empty graph
  Modifies: graph is initialized 
*/

void initGraph(struct Graph *g) {
  
  /* initialization */
  (*g).v = 0;
  (*g).multCount[0]=0;
  (*g).minustwo = 0;
  (*g).minusone = 0;
  (*g).yPower = 0;
  (*g).vnew=0;
  (*g).e = LIST_END; /* LIST_END indicates an empty graph */
  /* initialize header on vertex list */
  (*g).vrtx[0].vname = -3;
  (*g).vrtx[0].degree = 0;
  (*g).vrtx[0].nvert = LIST_END;
  (*g).vrtx[0].visit = 0;
  (*g).vrtx[0].pvert = -3;
  (*g).vrtx[0].fedge = -3;
} /* end of inittGraph */

/*                                            */
/*           end of initGraph                 */
/*                                            */
/**********************************************/
/*                                            */
/*           start of buildGraphStruct        */
/*                                            */


/* buildGraphStruct(edges,ve,g) takes the output of initGraph()
   and builds the multi linked structure used
   to represent the graph. The structure is designed
   to make delete, contract, eliminate multiple edges,
   check for loops, and removal of an edge from a
   spanning tree convenient */

/*
Precondition: the edges[][2] data structure and the number
              of entries (numberEdges) as well as an initialized graph
              g 

Postcondition: the array representation of the graph edges is
               used to form the standard data structure for the
               graph in the structure initialized

Modifies: the graph data structure now includes all the graph
            information needed to start processing 
*/

void buildGraphStruct(int edges[][2], int numberEdges, struct Graph *g) {
  
  int k1,                           /* for parameters                          */ 
    k2,  
    e1,                           /* names for ends of edge                  */
    e2,
    s1,                           /* used to find e2 on edge list of e1      */
    s1a, 
    s2,  
    s3,                           /* used to find e1 on edge list of e2      */
    s3a, 
    s4,
    t1,                           /* used to find e1 on vertex list          */
    t1a,
    t1b,
    t2,                           /* used to find e2 on vertex list          */
    t2a,
    t2b,
    vt,
    ans;                          /* switch to indicate a loop in structure  */

/* get edge */ 
for(k1 = 0; k1 <= numberEdges;++k1) 
  {
   /* for each edge put ends on vertex list and on 
      the appropriate adjacency list */

     k2 = 0;
     e1 = edges[k1][k2];
     e2 = edges[k1][++k2];

/* find out if e1 already in structure */
     if((*g).v == 0) 
       { /* only header node in graph */
          ++(*g).v;
          (*g).vrtx[(*g).v].vname = e1;
          (*g).vrtx[(*g).v].nvert = LIST_END; 
          (*g).vrtx[(*g).v].degree = 0; 
          (*g).vrtx[(*g).v].visit = 0; 
          (*g).vrtx[(*g).v].pvert = (*g).v - 1; 
          (*g).vrtx[(*g).v - 1].nvert = (*g).v; 
          t1 = (*g).v;
    
          /* header for adjacency list for e1 */
              /* edgehdr(&(*g)); */
          ++(*g).e;
          (*g).vrtx[(*g).v].fedge = (*g).e;
          (*g).edg[(*g).e].ename = -3;
          (*g).edg[(*g).e].tree = -3;
          (*g).edg[(*g).e].vertlist = -3;
          (*g).edg[(*g).e].side = -3;
          (*g).edg[(*g).e].back = -3;
          (*g).edg[(*g).e].front = LIST_END;
       }
     else 
       {
          t1 = -3; /* search vertex list for e1 */
          t1a = firstVertex(g);  /* points to first nonheader cell */ 
          if ( (*g).vrtx[t1a].vname == e1 ) 
            {
               t1 = t1a;
            }
          else 
            {
               //t1b = nextVertex(g, t1a); 
               //while ( t1b != LIST_END ) 
               for(t1b = nextVertex(g, t1a); t1b != LIST_END; t1b = nextVertex(g, t1b))
                  {
                    t1a = t1b;
                    if ( (*g).vrtx[t1b].vname == e1 ) 
                      { 
                         t1 = t1b;
                      }
                //    t1b = nextVertex(g, t1b); 
                 }  
            }
          if ( t1 == -3 ) 
            { /* e1 not on adjacency list so add at end */
               ++(*g).v; /* always add at the end of the list */
               (*g).vrtx[(*g).v].vname = e1;
               (*g).vrtx[(*g).v].nvert = LIST_END; 
               (*g).vrtx[(*g).v].degree = 0; 
               (*g).vrtx[(*g).v].visit = 0; 
               (*g).vrtx[(*g).v].pvert = t1a; 
               (*g).vrtx[t1a].nvert = (*g).v; 
               t1 = (*g).v;
    
                /* header for adjacency list for e2 */
                /* edgehdr(g); */
               ++(*g).e;
               (*g).vrtx[(*g).v].fedge = (*g).e;
               (*g).edg[(*g).e].ename = -3;
               (*g).edg[(*g).e].vertlist = -3;
               (*g).edg[(*g).e].tree = -3;
               (*g).edg[(*g).e].side = -3;
               (*g).edg[(*g).e].back = -3;
               (*g).edg[(*g).e].front = LIST_END;
            } 
       }
  {
     t2 = -3;  /* find e2 on vertex list or put at end */
     t2a = firstVertex(g);  //(*g).vrtx[0].nvert;/* always points to a next cell */ 
     if ( (*g).vrtx[t2a].vname == e2 ) 
       {
          t2 = t2a;
       } 
     else 
       {
          //t2b = nextVertex(g, t2a);  //(*g).vrtx[t2a].nvert;  
          //while ( t2b != LIST_END ) 
            for(t2b = nextVertex(g, t2a); t2b != LIST_END; t2b = nextVertex(g, t2b))
              {
                t2a = t2b;
                if ( (*g).vrtx[t2b].vname == e2 ) 
                  { 
                     t2 = t2b;
                  }
           //     t2b = nextVertex(g, t2b);  //(*g).vrtx[t2b].nvert;
            }  
       }
     if( t2 == -3 ) 
       { /* e2 not on vertex list so add at end */
  
          ++(*g).v; /* cell for e2 on vertex list */
          (*g).vrtx[(*g).v].vname = e2;
          (*g).vrtx[(*g).v].nvert = LIST_END; 
          (*g).vrtx[(*g).v].degree = 0; 
          (*g).vrtx[(*g).v].visit = 0; 
          (*g).vrtx[(*g).v].pvert = t2a; 
          (*g).vrtx[t2a].nvert = (*g).v; 
          t2 = (*g).v;
           /* edge list header for e2 */
           /* edgehdr(g); */
          ++(*g).e;
          (*g).vrtx[(*g).v].fedge = (*g).e;
          (*g).edg[(*g).e].ename = -3;
          (*g).edg[(*g).e].vertlist = -3;
          (*g).edg[(*g).e].tree = -3;
          (*g).edg[(*g).e].side = -3;
          (*g).edg[(*g).e].back = -3;
          (*g).edg[(*g).e].front = LIST_END;
       } 
}

    /* put in edges */
    /* e1 and e2 are the edge ends of concern */
    /* t1 points to the vertex cell for e1 */
    /* t2 points to the vertex cell for e2 */
    /*e1*/
    /* find front end of edge list for e1 */
    /* s1a = endedg(g); */
    { 
    s1 = headEdgeList(g, t1);  //(*g).vrtx[t1].fedge; /* header cell for edge list */
    s1a = s1; 
    //s1 = nextEdge(g, s1);  //(*g).edg[s1].front; /* first real edge (possibly) */
    //while (s1 != LIST_END ) 
    for(s1 = nextEdge(g, s1); s1 != LIST_END; s1 = nextEdge(g, s1))
      {
         s1a = s1;
 //	s1 = nextEdge(g, s1);  //(*g).edg[s1].front;
      }   
    }  
    s2 = ++(*g).e;  /* cell for e1 on edge adjacency list */
    (*g).edg[s1a].front = s2; /* link to new cell */
     /* e2 */
      /* front end of edge list for e2 */
    s3 = headEdgeList(g, t2);  //(*g).vrtx[t2].fedge;
    s3a = s3; 
   // s3 = nextEdge(g, s3);  //(*g).edg[s3].front;
    //while (s3 != LIST_END ) 
     for(s3 = nextEdge(g, s3); s3 != LIST_END; s3 = nextEdge(g, s3))
       {
         s3a = s3;
     //    s3 = nextEdge(g, s3);  //(*g).edg[s3].front;
      }
    incrNoEdges(g, 1);
    s4 = numEdges(g);  //++(*g).e;  /* cell for e2  on edge adjacency list */
    (*g).edg[s3a].front = s4; /* link to new cell */
     /* e1 goes in cell at s4 and e2 goes in cell at s2 */
    (*g).edg[s4].ename = e1;
    (*g).edg[s2].ename = e2;
    (*g).edg[s4].vertlist = t1;
    (*g).edg[s2].vertlist = t2;
    ++(*g).vrtx[t1].degree;
    ++(*g).vrtx[t2].degree;
    (*g).edg[s4].tree = 0;
    (*g).edg[s2].tree = 0;
    (*g).edg[s4].side = s2;
    (*g).edg[s2].side = s4;
    (*g).edg[s4].back = s3a;
    (*g).edg[s2].back = s1a;
    (*g).edg[s2].front = LIST_END;
    (*g).edg[s4].front = LIST_END;
  
  } /* for loop end for number of edges (k1) */
/* finish graph structure */
/* check to see if input has a loop-an error condition*/
//vt = firstVertex(g);  //(*g).vrtx[0].nvert;
//while ( vt != LIST_END ) 
/*for(vt = firstVertex(g); vt != LIST_END; vt = nextVertex(g, vt))
  {
     ans = loop(vt,g);
     if(ans) 
       {
          printf("LOOP PRESENT CHECK INPUT\n");
          exit(1);
       }
 //    vt= nextVertex(g, vt);  //(*g).vrtx[vt].nvert;
  }*/
      


} /* end of buildGraphStruct */

/*                                            */
/*           end of buildGraphStruct          */
/*                                            */
/**********************************************/


