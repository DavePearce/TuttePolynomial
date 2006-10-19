#ifndef GRAPH_HPP
#define GRAPH_HPP

#define VERTEXSIZE 70 	  /* change MAX_INTS_PER_ENTRY if this increases */
#define EDGE_IN_GRAPH 700 
#define LIST_END -1 /* YUK */
#define MINUSONE -1 /* YUK */

typedef struct {
  short int  nvert;  // ?
  short int  pvert;  // ?
  short int  fedge;  // first edge
  short int  vname;  // ?
  short int  degree; // degree
  short int  visit;  // used for DFS?
} vert;

typedef struct {
  short  int side;  // pointer to edge entry for target for this edge
  short  int back;  // ?
  short  int front; // ?
  short  int vertlist; // pointer to edge list of target vertex
  short  int ename; // ?
  short  int tree;  // ?
} edge;

struct Graph 
{
  vert  vrtx[VERTEXSIZE];
  edge  edg[EDGE_IN_GRAPH];

  // what is all this stuff?

  short  int multCount[100],
    v,       // number of vertices
    e,       // number of edges
    minusone, // number of x factors ?
    minustwo, // number of x+1 factors ?
    yPower,
    
    vnew;    // number of edges of simple version of the graph  
};

int nextVertex(struct Graph *g,int  vt);
int prevVert( struct Graph *g, int vt);
int headEdgeList( struct Graph *g, int vt);
int vertVisited( struct Graph *g, int vt);
int vertName( struct Graph *g, int vt);
int vertDegree( struct Graph *g, int vt);
void setNextVertex( struct Graph *g, int vt,int  vt1);
void setPrevVert( struct Graph *g, int vt,int  vt1);
void setVertDegree( struct Graph *g, int vt,int  amt);
void setVertVisited( struct Graph *g, int vt,int amt);
void incrVertDegree( struct Graph *g, int vt,int  amt);
int nextEdge( struct Graph *g, int ne);
int prevEdge( struct Graph *g, int ne);
int vertListOtherEnd( struct Graph *g, int ne);
int edgeInSpTree( struct Graph *g, int ne);
int nameOtherEnd( struct Graph *g, int ne);
int otherEndEntry( struct Graph *g, int ne);
int firstEdge( struct Graph *g, int vt);
void setEdgeInSpTree( struct Graph *g, int ne,int amt);
void setEdgeEndsInSpTree( struct Graph *g, int ne,int  amt);
void setVertListOtherEndEntry( struct Graph *g, int ne,int  vt);
void setNameOtherEnd( struct Graph *g, int ne,int  vt);
void setNextEdge (struct Graph *g,int  ne, int ne1);
void setOtherEndEntry(struct Graph *g,int  ne, int ne1);
void setPrevEdge(struct Graph *g, int ne,int  ne1);
int firstVertex( struct Graph *g);int numVertices( struct Graph *g);
int numEdges( struct Graph *g);
int multEdgeGphVert( struct Graph *g);
void incrYPower(struct Graph *g,int  amt);
void incrNoVertices(struct Graph *g,int  amt);
void incrNoEdges(struct Graph *g,int  amt);
void setNoVertices(struct Graph *g,int  amt);
void setNoEdges(struct Graph *g,int  amt);
void setMinusone(struct Graph *g, int amt);
void setYPower(struct Graph *g, int amt);
void setVNew(struct Graph *g,int  amt);
void setMinustwo(struct Graph *g,int  amt);
void detectAndDeleteLoop( struct Graph *g);
int deleteEdge(int place,struct Graph *g);

// this is the spanning tree stuff ???

void retree( struct Graph *g);
int nontree( struct Graph *g);
int untree(int e2, int t1, struct Graph *g);
int findspan( struct Graph *g);
int dfs(int vertLoc,struct Graph *g);


int gotMultiple (struct Graph *g);


#endif
