#ifndef TUTTE_H
#define TUTTE_H


#define VERTEXSIZE 70 	  /* change MAX_INTS_PER_ENTRY if this increases */
#define EDGE_IN_GRAPH 700 

#define PROFILING_MODE ZERO 

extern int upperIsoAddTestLimit,lowerIsoAddTestLimit;
extern int NoNonzeroOverflowMatricesLongLongInt, NoNonzeroOverflowMatricesInt;
extern int GraphsInHashTable;
extern int zeroentries;
extern int zeroentries1;
extern int zeroentries2,zeroentries2a;
extern int noGraphsLookedUp;
extern int intZeroCtr,llZeroCtr,consecutiveZeroesLL[30],consecutiveZeroesInt[30];
extern int maxCurrentBlock;
extern int currentblock;
extern int smallestThreshold;
extern int bottomThreshold ;
extern int topThreshold; 
#define EDGESIZE 700
#define STACKSIZE 500 
#define GRAPHSIZE 500 

#define MAX_BLOCKS 90  
#define INTS_PER_BLOCK 25000000
extern int * block[MAX_BLOCKS];






/*int  novert;*/                  /* original number of vertices in graph */
extern int LLLLL,LLLLLL,L,LLL,LLLL;
extern int noBytes[10000];
extern int notopt;
extern int origNoVert, origNoEdge;
extern int backwards[30],backwardsa[30];
extern int gvnewMax;
extern int intsleft;
extern int noMult;
extern long long int maxcoeff,maxcoeffin,testNo;
extern int stackDepthPush,stackDepthPop;
extern int permSwitch ;
extern int FiveEDGES[10];
extern int setSig;
extern int noRuns;
extern int oldblock;
extern int smallTree;
#define CHECKVERTEX 7 
/* 64-bit so go for it 17 caused flush with k(18) so try 25 */ 

extern int matchcount1[EDGESIZE],
    matchcount2[EDGESIZE],
    graphcount[EDGESIZE],
    graphcount1[EDGESIZE],
    match[EDGESIZE],
    matchcount[EDGESIZE];
extern long long int    gvBYgvnew[EDGESIZE][EDGESIZE];

/* maximum number of ints per entry in isotable: THREE for canong, ONE
   for tree and then otree */
#define MAX_INTS_PER_ENTRY   \
((sizeof(TUTTE) + sizeof(TUTTEO))/TWO +200) 
/* this size is predicated on the assumption that there is packing as
the estimate judges the upper diagonal half as the most to be packed */
#define HASHTABLESIZE 1500113 
// #define HASHTABLESIZE 45000287
extern unsigned long int hashtable[HASHTABLESIZE];
#define WORDSIZE 32
extern int TUTTECOLS , TUTTEROWS; 
typedef long long int TUTTEMATCH;
typedef long long int TUTTEOMATCH;
typedef TUTTEMATCH TUTTE[300][VERTEXSIZE];
typedef  TUTTEOMATCH TUTTEO[300][VERTEXSIZE];
extern TUTTE tuttey;
extern TUTTEO tuttez;

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
extern struct hashinfo NEWHash[HASHTABLESIZE];


extern Graph g[GRAPHSIZE];
#define CHARZERO '0'
#define MINUSONE -1
#define MINUSTWO -2
#define MINUSTHREE -3
#define EOLIST -1
#define LOCAL_STACK_END -3

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



extern int ent[STACKSIZE];
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
extern struct stack used, avail;
#define DEFAULT_SAVELEVEL 39 
#define SAVELEVEL 39 
#define CHROMIALFILENAME "chromials.dat"
#define DEFAULT_THRESHOLD 39
#define THRESHTABLESIZE  VERTEXSIZE 



void
initGraph(Graph *g);

int
getFileType (FILE *inFile);


void
graphToEdges(Graph *g,int  edges[][TWO], int * numberEdges);
void
enterEdges(int edges[][TWO],int *numberEdges);

int
readEdgeList(int edges[][TWO], int *numberEdges);
int
readGraphEdges();


void
buildGraphStruct(int edges[][TWO], int numberEdges,Graph *g);

int contractAfterDelete (int t1,int t2,int D1,int sendback,
                TUTTE tutteMat,
                TUTTEO tutteMatX
               );
int
degOneDels( Graph *g);
int
triangleDels( Graph *g);
int
getYPower( Graph *g);
int
getMultCount(Graph *g,int  location);
void
removeMultCountValue( Graph *g);
void
copyAndZeroMultCount(Graph *g, short int newMC[]);
void
setMultCount(Graph *g,short int  newMC[]);
void
setNewMultCount(Graph *g,int  value);
void
incrTriangleDels(Graph *g,int  amt);
int
incrDegOneDels(Graph *g,int  amt);

void
deleteContract(
               int C,
               int threshnum,
               int threshtable[],
               int newthreshold[],
               TUTTE tutteMat,
               TUTTEO tutteMatX
              );

int
identifyTriangle(Graph *g, int *vertex1,int *vertex2,int *vertex3, int *edge12,int *edge13,
int *edge23,int *switch5);
int
deleteAndContractTriangle(Graph *g,Graph * k,int vertex1,int vertex2,int vertex3,
int edge12,int edge13,int edge23);
int
eliminateTriangle( Graph *g,Graph *k);
void
enterEdgesBuildGraph(int *C,int *threshcount,int threshtable[],int newthreshold[]);
int fiveTreesnew(
                 int C,
                 int vertIndex[],
                 TUTTE tutteMat2,
                 TUTTEO tutteMat2X
                );

int degseq3200(int C, int vertDeg[], int vertIndex[],TUTTE tutteMat2, TUTTEO tutteMat2X);
int degseq1040(int C, int vertDeg[], int vertIndex[],TUTTE tutteMat2, TUTTEO tutteMat2X);




int
evaluateFivesA(
               int C,
               TUTTE tutteMat2,
               TUTTEO tutteMat2X
              );
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
int completePolyWithNoX(int nx,
                        int n12,
                        int n13,
                        int n14,
                        int n23,
                        int n24,
                        int n34,
                        TUTTE tutteMat2,
                        TUTTEO tutteMat2X
                       );
int completePolyWithX(int nx,
                      int n12,
                      int n13,
                      int n14,
                      int n23,
                      int n24,
                      int n34,
                      TUTTE tutteMat2,
                      TUTTEO tutteMat2X
                     );
int fourcomplete(int n12,int n13,int n14,int n23,int n24,int n34,
                 TUTTE tutteMat2,
                 TUTTEO tutteMat2X);

int fixedrandomgraph(int n1,int n2,int n3,int n4,int n5,
                     TUTTE tutteMat2,
                     TUTTEO tutteMat2X);
int randomgraph(int x12,int x13,int x14,int x23,int x24,int x34,
                int n12,int n13,int n14,int n23,int n24,int n34,
                TUTTE tutteMat2,
                TUTTEO tutteMat2X);
int fouredges(int x12,int x13,int x14,int x23,int x24,int x34,
              int n12,int n13,int n14,int n23,int n24,int n34,
              TUTTE tutteMat2,
              TUTTEO tutteMat2X);
int fourtrianglewithatail(int x12,int x13,int x14,int x23,int x24,int x34,
                          int n12,int n13,int n14,int n23,int n24,int n34,
                          TUTTE tutteMat2,
                          TUTTEO tutteMat2X);
int fourcycle(int x12,int x13,int x14,int x23,int x24,int x34,
              int n12,int n13,int n14,int n23,int n24,int n34,
              TUTTE tutteMat2,
              TUTTEO tutteMat2X);
int fixedfourcycle(int n1,int n2,int n3,int n4,
                   TUTTE tutteMat2,
                   TUTTEO tutteMat2X);
int fourtree(int x12,int x13,int x14,int x23,int x24,int x34,
             int n12,int n13,int n14,int n23,int n24,int n34,
             TUTTE tutteMat2,
             TUTTEO tutteMat2X);
int fourtreefixed (int n1,int n2,int n3,
                  TUTTE tutteMat2,
                  TUTTEO tutteMat2X);
int fixedtriangle(int n1,int n2,int n3,
                  TUTTE tutteMat2,
                  TUTTEO tutteMat2X);
int fixedthreetree(int n1,int n2,
                   TUTTE tutteMat2,
                   TUTTEO tutteMat2X);
int
evaluateFours(int C, TUTTE  tutteMat2,TUTTEO tutteMat2X);
int
evaluateSmallGraphs(
                    int C,
                    TUTTE tutteMat,
                    TUTTEO tutteMatX
                   );
int
evaluateThreesDriver(
                     int C,
                     TUTTE tutteMat2,
                     TUTTEO tutteMat2X
                    );
void
evaluateTutte (
               int C,
               TUTTE tutteMat,
               TUTTEO tutteMatX
              );

void findDegOne( Graph *g);
void
findInvariant(Graph *g2,int *m1,int canong[]);
void
mywrite(Graph *g,int m,int n);
int
computeNumwords(int gv);

void
hashinit();
unsigned int
hashvalue(int *h,int n);
void
hashinsert(unsigned int *p,unsigned long int hash, int gv,int  gvnew,int noByte);
int
* hashlookup(int gv, int gvnew, int canong[],unsigned long int hash,int w);
int
isolookup(Graph *h,int canong[], unsigned long int *hash,TUTTE  tutteMat,TUTTEO tutteMat1);
int
isoadd(int gv,int gvnew,int  canong[],unsigned long int hash,TUTTE  tutteMat,TUTTEO tutteMatX);
void
isoend();
void
isoend1();
void
isoreset();
int printT1(TUTTEO t);
int printT(TUTTE t);
void
identifyFives (Graph *g,
       TUTTE tutteMat,
       TUTTEO tutteMatX
      );
void
identifySixes  (Graph *g,
                TUTTE tutteMat1,
                TUTTEO tutteMat1X
               );
void
identifySixesA1 (Graph *g,int  degseq,TUTTE  tutteMat1,TUTTEO tutteMat1X);
void
identifySixesA2 (Graph *g,int  degseq,TUTTE  tutteMat1,TUTTEO tutteMat1X);
void
identifySixesB1 (Graph *g,int  degseq,TUTTE  tutteMat1,TUTTEO tutteMat1X);
void
identifySixesB2 (Graph *g,int  degseq,TUTTE  tutteMat1,TUTTEO tutteMat1X);
int
degreesofnhbrs(Graph *g, int vt);
int
nextofdegree(Graph *g, int *vt, int degree);
int
nextcommonadj(Graph *g,int v1, int v2);
int
commonadj(Graph *g,int v1,int v2);
int
nextdegnadjtov(Graph *g,int *ne1,int degree);
int
nodegnadjtov(Graph *g,int vt, int n);
int
isadj(int vt1,int vt2, Graph *g);
int
isadjedgename(int vt1, int vt2, Graph *g);
int
nodegn(Graph *g, int n);
void
deletevrtx( Graph *g, int vt);
void
multEdgeSmallGraphElimination(
               int *C,
               int startused,
               TUTTE tutteMat,
               TUTTEO tutteMatX
              );
void
multiplyByFactors(Graph *g, TUTTE tutteMat,TUTTEO tutteMatX,TUTTE tutteMat1,TUTTEO tutteMat1X,
                   int  gminusone, int gminustwo);
int
matrixspecial(short int n13,TUTTE tutteMat1,TUTTEO tutteMat1X);

int
matrixspecial1(int nonzeroColumn,int columnBottom[],int nonzeroRow,
    short int n13,TUTTE tutteMat1,TUTTEO tutteMat1X);
int
matrixspecial1a(int nonzeroColumn,int columnBottom[],int nonzeroRow,
              short int n13,TUTTE tutteMat1, TUTTEO tutteMat1X);
int
popGraphIndex(int C, int startused);
int
pushAndPopGraphIndex(int C, int startused);
int
findAndEliminateTriangle( int C);
void
doDeleteContract(int C ,TUTTE tutteMat,TUTTEO tutteMatX );
void
savedValues(
            int C,
            int *gv,
            int *gvnew,
            int *ge,
            int *yPower,
            int *gminusone,
            int *gminustwo,
            int savedmult[],
            TUTTE tutteMat1,
            TUTTEO tutteMat1X
           );
int
graphIsoTestHash(int *C,int startused,int thresholdValueOnEntry,int canong[],
   unsigned long int *hash,TUTTE  tutteMat,TUTTEO tutteMatX, int threshtable[],
   int  newthreshold[]);





void contract(int t1,int t2,Graph *g);
int areMultiple( Graph *g);
void printGraph( Graph *g);
int loop(int t1,Graph *g);
void copyGraph(Graph *g,Graph *k);

void permEdges(int NCARDS,int cards[]);
short int nfrom ( short int low, short int high );
int shuffl(int deck[], int NCARDS);
int preSevenFindDeg2 (Graph * g,TUTTE  tutteMat,TUTTEO tutteMatX);
void printTutte(TUTTE tutteMat,TUTTEO tutteMatX);
int recapStats(Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);

void deleteAndContractMultEdge (int C, TUTTE tutteMat, TUTTEO tutteMatX);

int recordMultiples(Graph *h, int NoMultEdges, int vert1, int edgFIXED,
TUTTE tutteMat, TUTTEO tutteMatX);
int deleteMultEdges(Graph *g, int *NoMultEdges, int edgFIXED);



void detreeForContract(int e2,int t1,Graph *g);

int detectAndComputeTrees(Graph *g,TUTTE tutteMat, TUTTEO tutteMatX);
void sevenpart11(Graph *g,int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart12(Graph *g,int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart13(Graph *g,int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart1(Graph *g, TUTTE tutteMat, TUTTEO tutteMatX);


void
sevenpart2dra(Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart2drb(Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart2drc(Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart2drd(Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart2dre(Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart2drf(Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart2drg(Graph *g, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart2drh(Graph *g,  TUTTE tutteMat,TUTTEO tutteMatX);

void
sevenpart2driver(Graph *g, TUTTE tutteMat, TUTTEO tutteMatX);

void
sevenpart3dra(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drb(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drb1(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drb2(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drb3(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drc(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drc1(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drc2(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drc3(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drd(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drd1(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drd2(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drd3(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3dre(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3dre1(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3dre2(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3dre3(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drf(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drf1(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drf2(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drf3(Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void sevenpart3dr(Graph *g, TUTTE tutteMat, TUTTEO tutteMatX);
void
sevenpart4(Graph *g, TUTTE tutteMat, TUTTEO tutteMatX);
void
sevenpart41(Graph *g, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart42(Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart43(Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);

void
sevenpart44(Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);

void
sevenpart45(Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);

void
sevenpart4a(Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);

void
sevenpart4b(Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);

void
sevensDriver(Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);

void
sixOrFewer(Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void
twoMultipleEliminate(int *C, int startused,TUTTE  tutteMat,TUTTEO tutteMatX);

void
threeMultipleEliminate(int *C, int startused,TUTTE  tutteMat,TUTTEO tutteMatX);

void
fourMultipleEliminate(int *C, int startused,TUTTE  tutteMat,TUTTEO tutteMatX);
void
fiveMultipleEliminate(int *C, int startused,TUTTE  tutteMat,TUTTEO tutteMatX);
int
simpleSmallGraphElimination(int *C, int startused,TUTTE  tutteMat,TUTTEO tutteMatX);
void
putonstack(struct stack *used, int D);
void
initavail( struct stack *avail);
int
mtavail( struct stack *avail);

void
pushavail(int C, struct stack *avail);

int
popavail( struct stack *avail);
void
initused( struct stack *used);
int
fullused( struct stack *used);
int
mtused( struct stack *used);
int
topused( struct stack *used);
int
pushused(int C, struct stack *used);
int
popused( struct stack *used);
int
MAKENULLQ( struct queue *Q1);
int
EMPTYQ( struct queue *Q1);
void
ENQUEUEQ(int placeincolor, struct queue *Q1);
void
DEQUEUEQ( struct queue *Q1);
int
FRONTQ( struct queue *Q1);
int
main(int argc, char   argv []);

void threshinit(Graph *g, int *threshcount, int threshtable[], int newthreshold[]);
void threshinitb(Graph *g, int *threshcount, int threshtable[], int newthreshold[]);

#endif
