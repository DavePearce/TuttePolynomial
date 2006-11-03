#define EXTDEFS 1		/* define before including naututil.h */
#include "naututil.h"		/* needed to call readgraph */
#include "tutte.h"


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

void 
initGraph(
          struct graph *g
         )
     
{

/* initialization */
(*g).v = ZERO;
(*g).multCount[ZERO]=ZERO;
(*g).minustwo = ZERO;
(*g).minusone = ZERO;
(*g).yPower = ZERO;
(*g).vnew=ZERO;
(*g).e = LIST_END; /* LIST_END indicates an empty graph */
/* initialize header on vertex list */
(*g).vrtx[ZERO].vname = MINUSTHREE;
(*g).vrtx[ZERO].degree = ZERO;
(*g).vrtx[ZERO].nvert = LIST_END;
(*g).vrtx[ZERO].visit = ZERO;
(*g).vrtx[ZERO].pvert = MINUSTHREE;
(*g).vrtx[ZERO].fedge = MINUSTHREE;
 }/* end of inittGraph */
  
/*                                            */
/*           end of initGraph                 */
/*                                            */
/**********************************************/
/*                                            */
/*           start of getFileType             */
/*                                            */

/* getFileType (FILE * inFile) tests a file
   to determine if it contains an edge list 
   or a nauty representation of a graph     */
 
/*
Precondition: access to a file that stores the graph 

Postcondition: the file is identified as to type by 
               parsing some of the first record of 
               the file. 

Returns: a code that indicates the type of file found 

CAUTION: the code depends on the file having a fixed form so that it can
         be identified after examining very little of the file itself
*/

int
getFileType (
             FILE * inFile
            )
{
    char buf[FOUR];
    int i,                /* array index                         */ 
        filetype;         /* signal for kind of input file found */ 

    buf[ZERO] = getc(inFile);
    i = ZERO;
    if (!isdigit(buf[ZERO])) /* if 1st char is not a digit */
        filetype =  NAUTYFILE;
    else 
      {
        do 
          {
             ++i;
             buf[i] = getc(inFile);
          } while (isdigit(buf[i]) && (i < THREE));

	/* assume edgelist file begins with a vertex with three or
	   fewer digits followed by a comma */
        if (buf[i]  == ',')
            filetype = EDGELISTFILE;
        else
            filetype = NAUTYFILE;
      }

    while (i >= ZERO) 
      {
	ungetc(buf[i], inFile);
        --i;
      }

    return filetype;
}

/*                                            */
/*           end of getFileType               */
/*                                            */
/**********************************************/
/*                                            */
/*           start of graphToEdges            */
/*                                            */


/*
Precondition: a nauty type representation of a graph and two
              instantiated variables that are an integer
              variable and an array of the form [][TWO]

Modifies: the array loaded with the edge pairs from the nauty graph
          and the variable contains the number of edges in the graph

Postcondition: the graph structure is not altered. the variables
               are initialized 

RATIONALE: easier to convert everyting back to a common format and use all the
           existing code
*/
void
graphToEdges(
             graph *g,
             int edges[][TWO],
             int *numberEdges
            )
{
    set *gv;
    int i,           /* for parameters                                        */ 
        j, 
        k = ZERO;    /* array index that changes as a counter of the edges    */

    for (i = ZERO; i < MAXN; ++i) 
      {
         gv = GRAPHROW(g, i, MAXM);
         for (j = i; j < MAXN; ++j)
           if (ISELEMENT(gv, j)) 
             {
                edges[k][ZERO] = i + ONE; /* edge list start at one */
                edges[k][ONE] = j + ONE;
		++k;
	     }
      }

    *numberEdges = k - ONE;
    return;
}

/*                                            */
/*           end of graphToEdges              */
/*                                            */
/**********************************************/
/*                                            */
/*           start of enterEdges              */
/*                                            */

/* enterEdges determines the file type and stores
   the edges in the edges array */

/*
Precondition: the array edges[][TWO and the variable numberEdges are
              instantiated. standard input has a file that
              represents a graph 

Modifies: the file in standard input is converted to a list of edges
          and the number of edges
  

Postcondition: standard input file has been read and the two variables
               are initialized to represent a graph as a list of edges

SIDE EFFECT: data areas were just sent by address to get filled

*/
void 
enterEdges(
           int edges[][TWO],
           int *numberEdges
          )
{
    graph tempg[MAXM * MAXN];
    readEdgeList(edges, numberEdges);
}

/*                                            */
/*           end of enterEdges                */
/*                                            */
/**********************************************/
/*                                            */
/*           start of readEdgeList            */
/*                                            */



/* readEdgeList(edges,&ve) reads in the edges of the graph.
  the format for the input is a,b,c,d,...,0,0
  where a is adjacent to b, c is adjacent to d, ... ,
  and the sentinel is the pair 0,0.  The edges are stored in
  an array. The array is used to build the graph data structure
  one edge at a time. 
 */
  /* readEdgeList calls readGraphEdges to get the vertices one at a time*/ 

/*
Precondition: an array with a list of edges and the number of entries
              are instantiated. standard input format is identified
              to be of the type handled by this procedure 

Modifies: standard input file of form a,b,c,d,...,.0,0 is put into
          array format
 
Postcondition: the standard input file has been read and the structure 
               created when the data structure format was identified 
               as in the a,b,c,d,...,0,0 format is stored in the 
               array edges[][TWO] in entries 0,...,numberEdges - 1 

*/

int
readEdgeList(
             int edges[][TWO],
             int *numberEdges
            )
{
  int j, /* indices for edges [][] */
    i, 
    c; /* input character */ 
  
  /* read in the edges of the graph */
  i = ZERO;
  *numberEdges = MINUSONE;
  do 
    {
      j = ZERO;
      c = readGraphEdges();
      if(c == EOF) { break; }
      if(getchar() == EOF) { break; }
      printf("GOT %d\n",c);
      edges[i][j] = c;
      c = readGraphEdges();
      printf("GOT %d\n",c);
      edges[i][++j]=c;
      ++i;
      ++(*numberEdges);
    } while(c != EOF);

} /* end of readEdgeList */

// ok, I've made a complete and utter mess of this routine.  But, it works ...

int
readGraphEdges()
{
int c,           /* value of next byte as unsigned char converted to an int    */
    n;           /* value of integer entered built one digit at a time         */
  n = ZERO;
  for( c = getchar(); isdigit(c) ; c = getchar())  {
    n = n * TEN + c - CHARZERO;
  }
  if(c == EOF) { return EOF; } // yucky hack
  while(c=='\n') { c=getchar(); }
  return(n);

}/* end of readGraphEdges */

/*                                            */
/*           end of readGraphEdges            */
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
Precondition: the edges[][TWO] data structure and the number
              of entries (numberEdges) as well as an initialized graph
              g 

Postcondition: the array representation of the graph edges is
               used to form the standard data structure for the
               graph in the structure initialized

Modifies: the graph data structure now includes all the graph
            information needed to start processing 
*/

void 
buildGraphStruct(
                 int edges[][TWO],
                 int numberEdges,
                 struct graph *g
                )
{
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
for(k1 = ZERO; k1 <= numberEdges;++k1) 
  {
   /* for each edge put ends on vertex list and on 
      the appropriate adjacency list */

     k2 = ZERO;
     e1 = edges[k1][k2];
     e2 = edges[k1][++k2];

/* find out if e1 already in structure */
     if((*g).v == ZERO) 
       { /* only header node in graph */
          ++(*g).v;
          (*g).vrtx[(*g).v].vname = e1;
          (*g).vrtx[(*g).v].nvert = LIST_END; 
          (*g).vrtx[(*g).v].degree = ZERO; 
          (*g).vrtx[(*g).v].visit = ZERO; 
          (*g).vrtx[(*g).v].pvert = (*g).v - ONE; 
          (*g).vrtx[(*g).v - ONE].nvert = (*g).v; 
          t1 = (*g).v;
    
          /* header for adjacency list for e1 */
          ++(*g).e;
          (*g).vrtx[(*g).v].fedge = (*g).e;
          (*g).edg[(*g).e].ename = MINUSTHREE;
          (*g).edg[(*g).e].tree = MINUSTHREE;
          (*g).edg[(*g).e].vertlist = MINUSTHREE;
          (*g).edg[(*g).e].side = MINUSTHREE;
          (*g).edg[(*g).e].back = MINUSTHREE;
          (*g).edg[(*g).e].front = LIST_END;
       }
     else 
       {
          t1 = MINUSTHREE; /* search vertex list for e1 */
          t1a = firstVertex(g);  /* points to first nonheader cell */ 
          if ( (*g).vrtx[t1a].vname == e1 ) 
            {
               t1 = t1a;
            }
          else 
            {
               for(t1b = nextVertex(g, t1a); t1b != LIST_END; t1b = nextVertex(g, t1b))
                  {
                    t1a = t1b;
                    if ( (*g).vrtx[t1b].vname == e1 ) 
                      { 
                         t1 = t1b;
                      }
                 }  
            }
          if ( t1 == MINUSTHREE ) 
            { /* e1 not on adjacency list so add at end */
               ++(*g).v; /* always add at the end of the list */
               (*g).vrtx[(*g).v].vname = e1;
               (*g).vrtx[(*g).v].nvert = LIST_END; 
               (*g).vrtx[(*g).v].degree = ZERO; 
               (*g).vrtx[(*g).v].visit = ZERO; 
               (*g).vrtx[(*g).v].pvert = t1a; 
               (*g).vrtx[t1a].nvert = (*g).v; 
               t1 = (*g).v;
    
                /* header for adjacency list for e2 */
                /* edgehdr(g); */
               ++(*g).e;
               (*g).vrtx[(*g).v].fedge = (*g).e;
               (*g).edg[(*g).e].ename = MINUSTHREE;
               (*g).edg[(*g).e].vertlist = MINUSTHREE;
               (*g).edg[(*g).e].tree = MINUSTHREE;
               (*g).edg[(*g).e].side = MINUSTHREE;
               (*g).edg[(*g).e].back = MINUSTHREE;
               (*g).edg[(*g).e].front = LIST_END;
            } 
       }
  {
     t2 = MINUSTHREE;  /* find e2 on vertex list or put at end */
     t2a = firstVertex(g);  /* always points to a next cell */ 
     if ( (*g).vrtx[t2a].vname == e2 ) 
       {
          t2 = t2a;
       } 
     else 
       {
            for(t2b = nextVertex(g, t2a); t2b != LIST_END; t2b = nextVertex(g, t2b))
              {
                t2a = t2b;
                if ( (*g).vrtx[t2b].vname == e2 ) 
                  { 
                     t2 = t2b;
                  }
            }  
       }
     if( t2 == MINUSTHREE ) 
       { /* e2 not on vertex list so add at end */
  
          ++(*g).v; /* cell for e2 on vertex list */
          (*g).vrtx[(*g).v].vname = e2;
          (*g).vrtx[(*g).v].nvert = LIST_END; 
          (*g).vrtx[(*g).v].degree = ZERO; 
          (*g).vrtx[(*g).v].visit = ZERO; 
          (*g).vrtx[(*g).v].pvert = t2a; 
          (*g).vrtx[t2a].nvert = (*g).v; 
          t2 = (*g).v;
           /* edge list header for e2 */
          ++(*g).e;
          (*g).vrtx[(*g).v].fedge = (*g).e;
          (*g).edg[(*g).e].ename = MINUSTHREE;
          (*g).edg[(*g).e].vertlist = MINUSTHREE;
          (*g).edg[(*g).e].tree = MINUSTHREE;
          (*g).edg[(*g).e].side = MINUSTHREE;
          (*g).edg[(*g).e].back = MINUSTHREE;
          (*g).edg[(*g).e].front = LIST_END;
       } 
}

    /* put in edges */
    /* e1 and e2 are the edge ends of concern */
    /* t1 points to the vertex cell for e1 */
    /* t2 points to the vertex cell for e2 */
    /*e1*/
    /* find front end of edge list for e1 */
    { 
    s1 = headEdgeList(g, t1);   /* header cell for edge list */
    s1a = s1; 
    for(s1 = nextEdge(g, s1); s1 != LIST_END; s1 = nextEdge(g, s1))
      {
         s1a = s1;
      }   
    }  
    s2 = ++(*g).e;  /* cell for e1 on edge adjacency list */
    (*g).edg[s1a].front = s2; /* link to new cell */
     /* e2 */
      /* front end of edge list for e2 */
    s3 = headEdgeList(g, t2);  
    s3a = s3; 
     for(s3 = nextEdge(g, s3); s3 != LIST_END; s3 = nextEdge(g, s3))
       {
         s3a = s3;
      }
    incrNoEdges(g, ONE);
    s4 = numEdges(g);   /* cell for e2  on edge adjacency list */
    (*g).edg[s3a].front = s4; /* link to new cell */
     /* e1 goes in cell at s4 and e2 goes in cell at s2 */
    (*g).edg[s4].ename = e1;
    (*g).edg[s2].ename = e2;
    (*g).edg[s4].vertlist = t1;
    (*g).edg[s2].vertlist = t2;
    ++(*g).vrtx[t1].degree;
    ++(*g).vrtx[t2].degree;
    (*g).edg[s4].tree = ZERO;
    (*g).edg[s2].tree = ZERO;
    (*g).edg[s4].side = s2;
    (*g).edg[s2].side = s4;
    (*g).edg[s4].back = s3a;
    (*g).edg[s2].back = s1a;
    (*g).edg[s2].front = LIST_END;
    (*g).edg[s4].front = LIST_END;
  
  } /* for loop end for number of edges (k1) */


} /* end of buildGraphStruct */

/*                                            */
/*           end of buildGraphStruct          */
/*                                            */
/**********************************************/


