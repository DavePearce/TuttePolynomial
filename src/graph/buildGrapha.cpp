#define EXTDEFS 1		/* define before including naututil.h */
#include "naututil.h"		/* needed to call readgraph */
#include <memory.h>
#include <cstdio>
//#include <gmp.h>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <cassert>
#include <ctype.h>

#include "graph.h"

/* A set of utility functions that initialize, build, and
 * manipulate a graph structure
 */


#define EDGELISTFILE 0
#define NAUTYFILE 1		/* see readgraph in naututil.c */

int readEdgeList(int edges[][2], int *numberEdges);
int readGraphEdges();




/**********************************************/
/**********************************************/
/*                                            */
/*           start of getFileType             */
/*                                            */

/* getFileType (FILE * inFile) tests a file
   to determine if it contains an edge list */
 
/*
Precondition: access to a file that stores the incidence 
              information of a graph 

Postcondition: the file is identified as to type by parsing some of the first
               record of the file. 

Returns: a code that indicates the type of file found 

CAUTION: the code depends on the file having a fixed form so that it can
         be identified after examioning very little of the file itself
*/

int
getFileType (FILE *inFile)

{
    char buf[4];
    int i,                /* array index                         */ 
        filetype;         /* signal for kind of input file found */ 

    buf[0] = getc(inFile);
    i = 0;
    if (!isdigit(buf[0])) /* if 1st char is not a digit */
        filetype =  NAUTYFILE;
    else 
      {
        do 
          {
             ++i;
             buf[i] = getc(inFile);
          } while (isdigit(buf[i]) && (i < 3));

	/* assume edgelist file begins with a vertex with three or
	   fewer digits followed by a comma */
        if (buf[i]  == ',')
            filetype = EDGELISTFILE;
        //else
         //   filetype = NAUTYFILE;
      }

    while (i >= 0) 
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
              variable and an array of the form [][2]

Modifies: the array loaded with the edge pairs from the nauty graph
          and the variable contains the number of edges in the graph

Postcondition: the graph structure is not altered. the variables
               are initialized 

RATIONALE: easier to convert everyting back to a common format and use all the
           existing code
*/

void
graphToEdges(graph *g,int  edges[][2], int *numberEdges)
{
    set *gv;
    int i,           // for parameters                                       
        j, 
        k = 0;    // array index that changes as a counter of the edges   

    for (i = 0; i < MAXN; ++i) 
      {
         gv = GRAPHROW(g, i, MAXM);
         for (j = i; j < MAXN; ++j)
           if (ISELEMENT(gv, j)) 
             {
                edges[k][0] = i + 1; // edge list start at one 
                edges[k][1] = j + 1;
		++k;
	     }
      }

    *numberEdges = k - 1;
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
Precondition: the array edges[][2 and the variable numberEdges are
              instantiated. standard input has a file that
              represents a graph 

Modifies: the file in standard input is converted to a list of edges
          and the number of edges
  

Postcondition: standard input file has been read and the two variables
               are initialized to represent a graph as a list of edges

SIDEEFFECT: data areas were just sent by address to get filled

*/
void 
enterEdges(int edges[][2],int *numberEdges)

{
    graph tempg[MAXM * MAXN];

    switch (getFileType(stdin)) 
      {
         case EDGELISTFILE:
           //printf("\n");
           //printf("******************* reading edge list *************\n");
           //printf("\n");
           readEdgeList(edges, numberEdges);
           break;
         //case NAUTYFILE:
           //printf("\n");
           //printf("******************* reading nauty file *************\n");
           //printf("\n");
           readgraph(stdin, tempg, FALSE, FALSE, FALSE, 1024, MAXM, MAXN);
           graphToEdges(tempg, edges, numberEdges);
           break;
         default:
           //printf("\n");
           //printf("error - unknown file type-execution stops\n");
           //printf("\n");
           exit(1);
           break;
     }
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
  an array so that this information is accessible to
  graphical routines */
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
               array edges[][2] in entries 0,...,numberEdges - 1 

*/

int
readEdgeList(int edges[][2], int *numberEdges)

{
int j, /* indices for edges [][] */
    i, 
    c; /* input character */ 

/* read in the edges of the graph */
  i = 0;
  *numberEdges = LIST_END;
  do 
    {
       j = 0;
       c= readGraphEdges();
       edges[i][j] = c;
       c = readGraphEdges();
       edges[i][++j]=c;
       ++i;
       ++(*numberEdges);
    } while(c != 0);
  /* decreases by 1 to account for edge in 0 location */  
  --(*numberEdges); 

} /* end of readEdgeList */

/*                                            */
/*           end of readEdgeList              */
/*                                            */
/**********************************************/
/*                                            */
/*           start of readGraphEdges          */
/*                                            */

/*
Precondition: input from the standard input is processed. 
              as a byte string 

Modifies: the bytes of input that form one integer are put together

Postcondition: standard input has been processed

Returns: an integer value constructed one character at a time
*/
 
int readGraphEdges()
{
int c,           /* value of next byte as unsigned char converted to an int    */
    n;           /* value of integer entered built one digit at a time         */
  n = 0;
  for( c = getchar(); c != ',' && c != '\n'; c = getchar()) 
    {
       n = n * 10 + c - '0';
       //c=getchar();
    }
  return(n);

}/* end of readGraphEdges */

/*                                            */
/*           end of readGraphEdges            */
/*                                            */
/**********************************************/
/**********************************************/


