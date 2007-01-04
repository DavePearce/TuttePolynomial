#include <stdio.h>

/* input file types--required by nauty */
#define EDGELISTFILE 0
#define NAUTYFILE 1		/* see readgraph in naututil.c */

#define PROFILING_MODE ZERO 


/* variables related to the size of the graph data structure */
/* see users manual to understand how these variables were   */
/* set and how to change them for special cases              */ 
#define VERTEXSIZE 70 	  
#define EDGESIZE 250
#define GRAPHSIZE 100
#define STACKSIZE 100 
int origNoVert, origNoEdge;
/* variables that determine hash table size */
#define MAX_BLOCKS 5  
#define INTS_PER_BLOCK 100000  // was 10000000

/* arrays to hold tutte polynomials */
typedef long long int TUTTEMATCH;
typedef long long int TUTTEOMATCH;
typedef TUTTEMATCH TUTTE[( EDGESIZE - VERTEXSIZE ) / 2][VERTEXSIZE];
typedef  TUTTEOMATCH TUTTEO[( EDGESIZE - VERTEXSIZE ) / 2][VERTEXSIZE];

/* limits for thresholds */
int smallestThreshold;
int bottomThreshold ;
int topThreshold; 

/* some variables are just convenient if they are 
   seen everywhere and do not have to be passed
   for the various uses
*/
int origNoVert, origNoEdge;
long long int testNo;
int TUTTECOLS , 
    TUTTEROWS; 
TUTTE tuttey;
TUTTEO tuttez;
/* limits for thresholds */
int smallestThreshold;
int bottomThreshold ;
int topThreshold; 


/* variables to set limits on adding 
   graphs to hashtable */
int upperIsoAddTestLimit,
    lowerIsoAddTestLimit;

/* variables related to hashing and the hashtable */
//#define MAX_BLOCKS 15  
//#define INTS_PER_BLOCK 10000000
int * block[MAX_BLOCKS];
int maxCurrentBlock;
int currentblock;
int intsleft;
//#define HASHTABLESIZE 1500113 
#define HASHTABLESIZE 5003101
//#define HASHTABLESIZE 45000287
struct hashinfo
{
unsigned long int hash_addr;
#ifdef PROFILING_MODE
int noOldVertices;
int noNewVertices;
int noHits;
int blockNumber;
int bytesStored;
#endif
};
struct hashinfo NEWHash[HASHTABLESIZE];

/* variables for recap statistics */
#if (PROFILING_MODE)
int backwards[30],backwardsa[30];
int NoNonzeroOverflowMatricesLongLongInt, 
    NoNonzeroOverflowMatricesInt;
int gvnewMax;
int GraphsInHashTable;
int stackDepthPush,stackDepthPop;
int zeroentries;
int zeroentries1;
int zeroentries2,zeroentries2a;
int noBytes[10000];
int noGraphsLookedUp;
int intZeroCtr,
    llZeroCtr,
    consecutiveZeroesLL[30],
    consecutiveZeroesInt[30];
int matchcount1[EDGESIZE],
    matchcount2[EDGESIZE],
    graphcount[EDGESIZE],
    graphcount1[EDGESIZE],
    match[EDGESIZE],
    matchcount[EDGESIZE];
long long int    gvBYgvnew[EDGESIZE][EDGESIZE];
#endif


#define WORDSIZE 32

/* STRUCTURES */
typedef struct
{short int  nvert,
            pvert,
            fedge,
            vname,
            degree,
            visit;
} vert;
typedef struct 
{short  int  side, 
             back, 
             front,
             vertlist,
             ename,
             tree;
} edge;
struct graph 
{
  vert  vrtx[VERTEXSIZE];
  edge  edg[EDGESIZE];
  
short  int multCount[100],
           v,
           e,
           minusone,
           minustwo,
           yPower,
           vnew;

};
struct graph g[GRAPHSIZE];
int ent[STACKSIZE];
struct queue
 {
  int front,back;
  int onqueue[STACKSIZE];
 };
struct wrqueue
 {
  int front, back;
  int onwrqueue[GRAPHSIZE];
 };
struct stack
{
int Top;
int places[STACKSIZE];
int NOPLACESUSED;
};
struct stack used, avail;

/*  DEFINED CONSTANTS */
#define CHARZERO '0'
#define MINUSONE -1
#define MINUSTWO -2
#define MINUSTHREE -3
#define EOLIST -1
#define LOCAL_STACK_END -3
#define LIST_END -1
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7 
#define EIGHT 8
#define NINE 9 
#define TEN 10
#define ELEVEN 11
#define TWELVE 12 
#define THIRTEEN 13
#define FOURTEEN 14 
#define FIFTEEN 15 
#define SIXTEEN 16 
#define SEVENTEEN 17 
#define EIGHTEEN 18
#define NINETEEN 19 
#define TWENTY 20
#define TWENTYONE 21 
#define TWENTYTWO 22
#define TWENTYTHREE 23 
#define TWENTYFOUR 24
#define TWENTYFIVE 25
#define TWENTYSIX 26
#define TWENTYSEVEN 27
#define TWENTYEIGHT 28
#define TWENTYNINE 29
#define THIRTY 30
#define THIRTYONE 31
#define THIRTYTWO 32
#define THIRTYTHREE 33
#define THIRTYFOUR 34
#define THIRTYFIVE 35
#define HUNDRED 100
#define BILLION 1000000000
#define BILLION2 500000000
#define BILLION3 333333333
#define COMMA ','
#define EOLN '\n'



int ent[STACKSIZE];

/*                                      */
/*                                      */
/*     PROTOTYPES                       */
/*                                      */
/*                                      */
void initGraph(struct graph *g);
int getFileType (FILE * inFile);
void enterEdges(int edges[][TWO],int *numberEdges);
int readEdgeList(int edges[][TWO], int *numberEdges);
int readGraphEdges();
void buildGraphStruct(int edges[][TWO], int numberEdges,struct graph *g);
int contractAfterDelete (int t1,int t2,int D1,int sendback, TUTTE tutteMat, TUTTEO tutteMatX);
void threshinit ( struct graph *g, int *threshcount, int threshtable[], int newthreshold[]);
void threshinitb ( struct graph *g, int *threshcount, int threshtable[], int newthreshold[]);
int nextVertex(struct graph *g,int  vt);
int prevVert( struct graph *g, int vt);
int headEdgeList( struct graph *g, int vt);
int vertVisited( struct graph *g, int vt);
int vertName( struct graph *g, int vt);
int vertDegree( struct graph *g, int vt);
void setNextVertex( struct graph *g, int vt,int  vt1);
void setPrevVert( struct graph *g, int vt,int  vt1);
void setVertDegree( struct graph *g, int vt,int  amt);
void setVertVisited( struct graph *g, int vt,int amt);
void incrVertDegree( struct graph *g, int vt,int  amt);
int nextEdge( struct graph *g, int ne);
int prevEdge( struct graph *g, int ne);
int vertListOtherEnd( struct graph *g, int ne);
int edgeInSpTree( struct graph *g, int ne);
int nameOtherEnd( struct graph *g, int ne);
int otherEndEntry( struct graph *g, int ne);
int firstEdge( struct graph *g, int vt);
void setEdgeInSpTree( struct graph *g, int ne,int amt);
void setEdgeEndsInSpTree( struct graph *g, int ne,int  amt);
void setNameOtherEnd( struct graph *g, int ne,int  vt);
void setNextEdge (struct graph *g,int  ne, int ne1);
void setVertListOtherEndEntry(struct graph *g, int ne, int vt);
void setOtherEndEntry(struct graph *g,int  ne, int ne1);
void setPrevEdge(struct graph *g, int ne,int  ne1);
int firstVertex( struct graph *g);
int numVertices( struct graph *g);
int numEdges( struct graph *g);
int multEdgeGphVert( struct graph *g);
int degOneDels( struct graph *g);
int triangleDels( struct graph *g);
int getYPower( struct graph *g);
int getMultCount(struct graph *g,int  location);
void removeMultCountValue( struct graph *g);
void copyAndZeroMultCount(struct graph *g, short int newMC[]);
void setMultCount(struct graph *g,short int  newMC[]);
void setNoVertices(struct graph *g,int  amt);
void setNoEdges(struct graph *g,int  amt);
void setMinusone(struct graph *g, int amt);
void setYPower(struct graph *g, int amt);
void setVNew(struct graph *g,int  amt);
void setMinustwo(struct graph *g,int  amt);
void setNewMultCount(struct graph *g,int  value);
void incrYPower(struct graph *g,int  amt);
void incrNoVertices(struct graph *g,int  amt); 
void incrNoEdges(struct graph *g,int  amt);
void incrTriangleDels(struct graph *g,int  amt);
int incrDegOneDels(struct graph *g,int  amt);
void deleteContract( int C, int threshnum, int threshtable[], int newthreshold[], TUTTE tutteMat, TUTTEO tutteMatX);
void detectAndDeleteLoop( struct graph *g);
int eliminateTriangle( struct graph *g,struct graph *k);
int deleteAndContractTriangle( struct graph *g, struct graph *k, int vertex1, int vertex2, int vertex3, int edge12, int edge13, int edge23);
int identifyTriangle( struct graph *g, int *vertex1, int *vertex2, int *vertex3, int *edge12, int *edge13, int *edge23, int *switch5);
void enterEdgesBuildGraph(int *C,int *threshcount,int threshtable[],int newthreshold[]);
int fiveTreesnew( int C, int vertIndex[], TUTTE tutteMat2, TUTTEO tutteMat2X);
int evaluateFivesA( int C, TUTTE tutteMat2, TUTTEO tutteMat2X);
int degseq3200(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq1040(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq2210(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq131triangle(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq311(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq410(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq50(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq230house(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq230k23(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq131c4(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq212(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq1022(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq1121(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq2030(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq1301(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq1220(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq5000(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int degseq1400(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X);
int completePolyWithNoX(int nx, int n12, int n13, int n14, int n23, int n24, int n34, TUTTE tutteMat2, TUTTEO tutteMat2X);
int completePolyWithX(int nx, int n12, int n13, int n14, int n23, int n24, int n34, TUTTE tutteMat2, TUTTEO tutteMat2X);
int fourcomplete(int n12,int n13,int n14,int n23,int n24,int n34, TUTTE tutteMat2, TUTTEO tutteMat2X);
int fixedrandomgraph(int n1,int n2,int n3,int n4,int n5, TUTTE tutteMat2, TUTTEO tutteMat2X);
int randomgraph(int x12,int x13,int x14,int x23,int x24,int x34, int n12,int n13,int n14,int n23,int n24,int n34, TUTTE tutteMat2, TUTTEO tutteMat2X);
int fouredges(int x12,int x13,int x14,int x23,int x24,int x34, int n12,int n13,int n14,int n23,int n24,int n34, TUTTE tutteMat2, TUTTEO tutteMat2X);
int fourtrianglewithatail(int x12,int x13,int x14,int x23,int x24,int x34, int n12,int n13,int n14,int n23,int n24,int n34, TUTTE tutteMat2, TUTTEO tutteMat2X);
int fourcycle(int x12,int x13,int x14,int x23,int x24,int x34, int n12,int n13,int n14,int n23,int n24,int n34, TUTTE tutteMat2, TUTTEO tutteMat2X); 
int fixedfourcycle(int n1,int n2,int n3,int n4, TUTTE tutteMat2, TUTTEO tutteMat2X); 
int fourtree(int x12,int x13,int x14,int x23,int x24,int x34, int n12,int n13,int n14,int n23,int n24,int n34, TUTTE tutteMat2, TUTTEO tutteMat2X);
int fourtreefixed (int n1,int n2,int n3, TUTTE tutteMat2, TUTTEO tutteMat2X);
int fixedtriangle(int n1,int n2,int n3, TUTTE tutteMat2, TUTTEO tutteMat2X);
int fixedthreetree(int n1,int n2, TUTTE tutteMat2, TUTTEO tutteMat2X);
int evaluateFours(int C, TUTTE  tutteMat2,TUTTEO tutteMat2X);
int evaluateSmallGraphs( int C, TUTTE tutteMat, TUTTEO tutteMatX);
int evaluateThreesDriver( int C, TUTTE tutteMat2, TUTTEO tutteMat2X);
void evaluateTutte ( int C, TUTTE tutteMat, TUTTEO tutteMatX);
void findDegOne( struct graph *g); 
void findInvariant(struct graph *g2,int *m1,int canong[]);
/* void
mywrite(graph *g,int m,int n);*/
int computeNumwords(int gv);
int gotMultiple ( int C);
void hashinit();
unsigned int hashvalue(int *h,int n);
void hashinsert(unsigned int *p,unsigned long int hash, int gv,int  gvnew,int noByte);
int * hashlookup(int gv, int gvnew, int canong[],unsigned long int hash,int w);
int isolookup(struct graph *h,int canong[], unsigned long int *hash,TUTTE  tutteMat,TUTTEO tutteMat1);
int isoadd(int gv,int gvnew,int  canong[],unsigned long int hash,TUTTE  tutteMat,TUTTEO tutteMatX);
void isoend();
void isoAndStatSetVars();
int printT1(TUTTEO t);
int printT(TUTTE t);
void identifyFives (struct graph *g, TUTTE tutteMat, TUTTEO tutteMatX);
void identifySixes  (struct graph *g, TUTTE tutteMat1, TUTTEO tutteMat1X);
void identifySixesA1 (struct graph *g,int  degseq,TUTTE  tutteMat1,TUTTEO tutteMat1X);
void identifySixesA2 (struct graph *g,int  degseq,TUTTE  tutteMat1,TUTTEO tutteMat1X);
void identifySixesB1 (struct graph *g,int  degseq,TUTTE  tutteMat1,TUTTEO tutteMat1X);
void identifySixesB2 (struct graph *g,int  degseq,TUTTE  tutteMat1,TUTTEO tutteMat1X);
int degreesofnhbrs(struct graph *g, int vt);
int nextofdegree(struct graph *g, int *vt, int degree);
int nextcommonadj(struct graph *g,int v1, int v2);
int commonadj(struct graph *g,int v1,int v2);
int nextdegnadjtov(struct graph *g,int *ne1,int degree);
int nodegnadjtov(struct graph *g,int vt, int n);
int isadj(int vt1,int vt2, struct graph *g);
int isadjedgename(int vt1, int vt2, struct graph *g);
int nodegn(struct graph *g, int n);
void deletevrtx( struct graph *g, int vt);
void multEdgeSmallGraphElimination( int *C, int startused, TUTTE tutteMat, TUTTEO tutteMatX);
void multiplyByFactors(struct graph *g, TUTTE tutteMat,TUTTEO tutteMatX,TUTTE tutteMat1,TUTTEO tutteMat1X, int  gminusone, int gminustwo);
int matrixspecial(short int n13,TUTTE tutteMat1,TUTTEO tutteMat1X);
int matrixspecial1(int nonzeroColumn,int columnBottom[],int nonzeroRow, short int n13,TUTTE tutteMat1,TUTTEO tutteMat1X);
int matrixspecial1a(int nonzeroColumn,int columnBottom[],int nonzeroRow, short int n13,TUTTE tutteMat1, TUTTEO tutteMat1X);
int popGraphIndex(int C, int startused);
int pushAndPopGraphIndex(int C, int startused);
int findAndEliminateTriangle( int C);
void doDeleteContract(int C ,TUTTE tutteMat,TUTTEO tutteMatX ); 
int savedValues( int C, int *gv, int *gvnew, int *ge, int *yPower, int *gminusone, int *gminustwo, short int savedmult[], TUTTE tutteMat1, TUTTEO tutteMat1X);
int graphIsoTestHash(int *C,int startused,int thresholdValueOnEntry,int canong[], unsigned long int *hash,TUTTE  tutteMat,TUTTEO tutteMatX, int threshtable[], int  newthreshold[]);
void contract(int t1,int t2,struct graph *g);
int areMultiple( struct graph *g);
void printGraph( struct graph *g);
int loop(int t1,struct graph *g);
void copyGraph(struct graph *g,struct graph *k);
int deleteEdge(int place,struct graph *g);
void permEdges(int NCARDS,int cards[]);
short int nfrom ( short int low, short int high );
int shuffl(int deck[], int NCARDS);
int preSevenFindDeg2 (struct graph * g,TUTTE  tutteMat,TUTTEO tutteMatX);
void printTutte(TUTTE tutteMat,TUTTEO tutteMatX);
int recapStats(struct graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void deleteAndContractMultEdge (int C, TUTTE tutteMat, TUTTEO tutteMatX);
int recordMultiples( struct graph *h, int NoMultEdges, int vert1, int edgFIXED, TUTTE tutteMat, TUTTEO tutteMatX);
int deleteMultEdges( struct graph *g, int *NoMultEdges, int edgFIXED);
void retree( struct graph *g);
int nontree( struct graph *g);
void detreeForContract(int e2,int t1,struct graph *g);
int untree(int e2, int t1, struct graph *g);
int findspan( struct graph *g);
int dfs(int vertLoc,struct graph *g);
int detectAndComputeTrees(struct graph *g,TUTTE tutteMat, TUTTEO tutteMatX);
void sevenpart11(struct graph *g,int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart12(struct graph *g,int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart13(struct graph *g,int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart1(struct graph *g, TUTTE tutteMat, TUTTEO tutteMatX);
void sevenpart2dra(struct graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart2drb(struct graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart2drc(struct graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart2drd(struct graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart2dre(struct graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart2drf(struct graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart2drg(struct graph *g, TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart2drh(struct graph *g,  TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart2driver(struct graph *g, TUTTE tutteMat, TUTTEO tutteMatX);
void sevenpart3dra(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drb(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drb1(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drb2(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drb3(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drc(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drc1(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drc2(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drc3(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drd(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drd1(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drd2(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drd3(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3dre(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3dre1(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3dre2(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3dre3(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drf(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drf1(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drf2(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3drf3(struct graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart41(struct graph *g, TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart42(struct graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart43(struct graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart44(struct graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart45(struct graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart4a(struct graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart4b(struct graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void sevensDriver(struct graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void sixOrFewer(struct graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void sixOrFewera(int noVert, struct graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void sixOrFewerb(int noVert, struct graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void twoMultipleEliminate(int *C, int startused,TUTTE  tutteMat,TUTTEO tutteMatX);
void threeMultipleEliminate(int *C, int startused,TUTTE  tutteMat,TUTTEO tutteMatX);
void fourMultipleEliminate(int *C, int startused,TUTTE  tutteMat,TUTTEO tutteMatX);
void fiveMultipleEliminate(int *C, int startused,TUTTE  tutteMat,TUTTEO tutteMatX);
void putonstack(struct stack *used, int D);
void initavail( struct stack *avail);
int mtavail( struct stack *avail);
void pushavail(int C, struct stack *avail);
int popavail( struct stack *avail);
void initused( struct stack *used);
int fullused( struct stack *used);
int mtused( struct stack *used);
int topused( struct stack *used);
int pushused(int C, struct stack *used);
int popused( struct stack *used);
int MAKENULLQ( struct queue *Q1);
int EMPTYQ( struct queue *Q1);
void ENQUEUEQ(int placeincolor, struct queue *Q1);
void DEQUEUEQ( struct queue *Q1);
int FRONTQ( struct queue *Q1);
int main(int argc, char   *argv []);



