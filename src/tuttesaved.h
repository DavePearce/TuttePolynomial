#include <stdio.h>


//#define PROFILING_MODE ZERO 




/* input file types--required by nauty */
#define EDGELISTFILE 0
#define NAUTYFILE 1		/* see readgraph in naututil.c */
/*int  novert;*/                  /* original number of vertices in graph */
int LLLLL,LLLLLL,L,LLL,LLLL;
int noBytes[10000];
#define LOCAL_STACK_END -3
int NoNonzeroOverflowMatricesLongLongInt, NoNonzeroOverflowMatricesInt;
int notopt;
int origNoVert, origNoEdge;
int backwards[30],backwardsa[30];
int gvnewMax;
int intsleft;
//#ifdef PROFILING_MODE

int GraphsInHashTable;

//#endif
int zeroentries;
int zeroentries1;
int zeroentries2,zeroentries2a;
int noGraphsLookedUp;
int intZeroCtr,llZeroCtr,consecutiveZeroesLL[30],consecutiveZeroesInt[30];
int noMult;
int maxCurrentBlock;
long long int maxcoeff,maxcoeffin,testNo;
int currentblock;
int stackDepthPush,stackDepthPop;
int permSwitch ;
int FiveEDGES[10];
int setSig;
int noRuns;
int oldblock;
int smallestThreshold;
int smallTree;
int bottomThreshold ;
int topThreshold; 
#define EDGESIZE 700
#define CHECKVERTEX 7 
#define STACKSIZE 500 
#define GRAPHSIZE 500 
#define VERTEXSIZE 70 	  /* change MAX_INTS_PER_ENTRY if this increases */
#define EDGE_IN_GRAPH 700 
#define MAX_BLOCKS 90  
/* 64-bit so go for it 17 caused flush with k(18) so try 25 */ 
#define INTS_PER_BLOCK 25000000
//#ifdef PROFILING_MODE

int matchcount1[EDGESIZE],
    matchcount2[EDGESIZE],
    graphcount[EDGESIZE],
    graphcount1[EDGESIZE],
    match[EDGESIZE],
    matchcount[EDGESIZE],
    gvBYgvnew[EDGESIZE][EDGESIZE];
//#endif
int * block[MAX_BLOCKS];

/* maximum number of ints per entry in isotable: THREE for canong, ONE
   for tree and then otree */
#define MAX_INTS_PER_ENTRY   \
((sizeof(TUTTE) + sizeof(TUTTEO))/TWO +200) 
/* this size is predicated on the assumption that there is packing as
the estimate judges the upper diagonal half as the most to be packed */
/*#define HASHTABLESIZE 1500113 */
#define HASHTABLESIZE 45000287
unsigned long int hashtable[HASHTABLESIZE];
#define WORDSIZE 32
int TUTTECOLS , 
    TUTTEROWS; 
typedef long long int TUTTEMATCH;
typedef long long int TUTTEOMATCH;
typedef TUTTEMATCH TUTTE[300][VERTEXSIZE];
typedef  TUTTEOMATCH TUTTEO[300][VERTEXSIZE];
TUTTE tuttey;
TUTTEO tuttez;

struct hashinfo
{
unsigned long int hash_addr;
//#ifdef PROFILING_MODE
int noOldVertices;
int noNewVertices;
int noHits;
int noBytes;
//#endif
};
struct hashinfo NEWHash[HASHTABLESIZE];


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
  edge  edg[EDGE_IN_GRAPH];
  
short  int multCount[100],
           v,
           e,
           minusone,
           minustwo,
           yPower,
           vnew;

};
struct graph g[GRAPHSIZE];
#define CHARZERO '0'
#define MINUSONE -1
#define MINUSTWO -2
#define MINUSTHREE -3
#define EOLIST -1
#define LIST_END -1
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define EIGHT 8
#define SEVEN 7 
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
#define DEFAULT_SAVELEVEL 39 
#define SAVELEVEL 39 
#define CHROMIALFILENAME "chromials.dat"
#define DEFAULT_THRESHOLD 39
#define THRESHTABLESIZE  VERTEXSIZE 


/* PROTOTYPES */
int FIVEStrial(int C, TUTTE tutteMat2, TUTTEO tutteMat2X);
int contractAfterDelete(int t1, int t2, int C,int sendback, TUTTE tutteMat,TUTTEO tututeMatX);
int countVertex(struct graph * g);void findInvariant(struct graph * g2,int * m1, int canong []);
void printGraph(struct graph * g);
void deleteContract(int C,  int threshnum, int 
threshtable [], int newthreshold [], TUTTE tutteMat,TUTTEO tutteMatX 
);

void evaluateTutte (int C,  TUTTE tutteMat,TUTTEO tutteMatX);
int main ();
void printTutte (/*int origNoVert, int origNoEdge,*/ TUTTE tutteMat,TUTTEO tutteMatX );
void retree(struct graph * g);
void initGraph(struct graph * g);
void enterEdges(int edges [][TWO], int * numberEdges);
int readGraphEdges();
void readEdgeList(int edges [][TWO], int * numberEdges);
void buildGraphStruct(int edges [][TWO], int numberEdges, struct 
graph * g);
int gotMultiple( int C);
void contract(int t1, int t2, struct graph * g);
int nontree(struct graph * g);
void detreeForContract(int e2,int t1, struct graph * g);
void findspan(struct graph * g);
void dfs(int start, struct graph * g);
int selectEdge(int C);
int ckfordeg(struct graph * g, int deg);
void permEdges(int NCARDS, int cards []);
int shuffl(int deck [],int NCARDS);
short int nfrom( short low, short high);
void copyGraph(struct graph * g, struct graph * k);
void identifySixes(struct graph * g, 
TUTTE tutteMat1,TUTTEO tutteMat1X);
void identifySixesA(struct graph * g, 
TUTTE tutteMat1,TUTTEO tutteMat1X);
void fourorfewer(struct graph * g, TUTTE tutteMat); 
void mtwo4(struct graph * g,  
TUTTE tutteMat, TUTTEO tutteMatX,TUTTE tuttemat1,  TUTTEO tutteMat1X, int gminusone,int gminustwo); 
int preseven(struct graph * h,
TUTTE tutteMat,TUTTEO tutteMatX);
int eliminateTriangle(struct graph * g, struct graph * k );
void findDegONe(struct graph * g);
int isTree(struct graph * g, 
TUTTE tutteMat,TUTTEO tutteMatX);
void hashinit();
unsigned int hashvalue( int h [],int n);
void hashinsert(unsigned int * p,unsigned long int hash, int gv, int gvnew, int noByte);
int * hashlookup(int gv,int gvnew,  int  canong [],unsigned long int hash,
int w);
int * hashlookup1(int gv, int gvnew, int  canong [],unsigned long int hash,
int w);
int isoinit();
void isoreset();
int isolookup(struct graph * h, int canong [],unsigned long int 
* hash, TUTTE tutteMat,TUTTEO tutteMatX);
int isoadd(int gv,int gvnew, int canong [],unsigned long int hash,TUTTE tutteMat,TUTTEO tutteMatX);
void isoend();
void isoend1();
void isoreset1();
int degreesofnhbrs(struct graph * g,int vt);
int nextofdegree(struct graph * g,int * vt,int degree);
int nextcommonadj(struct graph *  g,int v1,int v2);
int commonadj(struct graph *  g,int v1,int v2);
int nextdegnadjtov(struct graph * g,int * ne1,int degree);
int nodegnadjtov(struct graph * g,int vt,int n);
int isadj(int vt1,int vt2,struct graph *  g);
int nodegn(struct graph * g,int n);
void deletevrtx(struct graph * g,int vt);
void putonstack(struct stack * used, int D);
void initavail(struct stack * avail);
int mtavail(struct stack * avail);
void pushavail(int C,struct stack * avail);
int popavail(struct stack * avail);
void initused(struct stack * used);
int fullused(struct stack * used);
int topused(struct stack * used);
int mtused(struct stack * used);
void pushused(int C,struct stack *  used);
int popused(struct stack * used);
void MAKENULL(struct queue * Q1);
int EMPTYQ(struct queue * Q1);
void ENQUEUEQ(int placeincolor,struct queue * Q1);
int FRONTQ(struct queue * Q1);
void DEQUEUEQ(struct queue * Q1);
void threshinit(struct graph * g,int * threshcount,int threshtable 
[],int newthreshold []);
void threshinitb(struct graph * g,int * threshcount,int threshtable 
[],int newthreshold []);
int computeNumwords(int gv);
void sixOrFewer(struct graph * g,  TUTTE tutteMat,TUTTEO tutteMatX);
void identifyFives(struct graph *g, TUTTE tutteMat1,TUTTEO tuttteMat1X);
void removeMultEdge(int C, TUTTE tutteMat,TUTTEO tutteMatX);
int evaluateFours(int C, TUTTE tutteMat2, TUTTEO tutteMat2X);
int evaluateThreesDriver(int C, TUTTE tutteMat2,TUTTEO tutteMat2X);
int evaluateFives(int C, TUTTE tutteMat2,TUTTEO tutteMat2X);
int evalFives(int C, TUTTE tutteMat2,TUTTEO tutteMat2X, struct graph * w);
int fourtree(int x12, int x13, int x14, int x23, int x24, int x34,int n12, int n13, int n14, int n23, int n24, int n34, TUTTE tutteMat2, TUTTEO tuttet2X);
int fixedfivetree(int n1, int n2, int n3, int n4,  TUTTE tutteMat2, TUTTEO tutteMat2X);
int fourtreefixed(int n1, int n2, int n3, TUTTE tutteMat2, TUTTEO tutteMat2X);
int fixedthreetree(int n1, int n2, TUTTE tutteMat2, TUTTEO tutteMat2X);
int fixedfourcycle(int n1, int n2, int n3,int n4, TUTTE tutteMat2, TUTTEO tutteMat2X);
int fixedfourcyclefast(int n1, int n2, int n3,int n4, TUTTE tutteMat2,TUTTEO tutteMat2X);
int fixedtriangle(int n1, int n2, int n3, TUTTE tutteMat2,TUTTEO tutteMat2X);
int fouredges(int x12, int x13, int x14, int x23, int x24, int x34,int n12, int n13, int n14, int n23, int n24, int n34, TUTTE tutteMat2,TUTTEO tutteMat2X);
int randomgraph(int x12, int x13, int x14, int x23, int x24, int x34,int n12, int n13, int n14, int n23, int n24, int n34, TUTTE tutteMat2,TUTTEO tutteMat2X);
int fixedrandomgraph(int n1,int n2,int n3,int n4,int n5, TUTTE tutteMat2,TUTTEO tutteMat2X);
int fourcomplete(int n12, int n13, int n14, int n23, int n24, int n34, TUTTE tutteMat2,TUTTEO tutteMat2X);
int fourcompletefixed(int n12, int n13, int n14, int n23, int n24, int n34,int C, TUTTE tutteMat2,TUTTEO tutteMat2X);
int fourcycle(int x12, int x13, int x14, int x23, int x24, int x34,int n12, int n13, int n14, int n23, int n24, int n34, TUTTE tutteMat2,TUTTEO tutteMat2X);
int fourtrainglewithatail(int x12, int x13, int x14, int x23, int x24, int x34,int n12, int n13, int n14, int n23, int n24, int n34, TUTTE tutteMat2,TUTTEO tutteMat2X);
void detectLoop(struct graph *g);
int loopsweepf(struct graph *g);
int completePolyWithX(int nx,int n12, int n13, int n14, int n23, int n24, int n34, TUTTE tutteMat2,TUTTEO tutteMat2X);
int completePolyWithNoX(int nx,int n12, int n13, int n14, int n23, int n24, int n34, TUTTE tutteMat2,TUTTEO tutteMat2X);
int matrixspecial( int n13, TUTTE tuttteMat1,TUTTEO tutteMat1X);
int evaluateSmallGraphs(int C,  TUTTE tutteMat, TUTTEO tuttteMatX);
int matrixspecial1a(int lastnonzeroRow,int lastnonzeroRowinColumn [], int lastnonzeroColumn, short int n13, TUTTE tutteMat1,TUTTEO tutteMat1X);
int matrixspecial1(int lastnonzeroRow,int lastnonzeroRowinColumn [],int lastnonzeroColumn, short int n13, TUTTE tuttteMat1,TUTTEO tutteMat1X);
void printT(TUTTE t);
void printT1(TUTTEO t);
