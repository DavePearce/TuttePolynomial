
void
initGraph(struct Graph *g);

int
getFileType (FILE *inFile);


void
graphToEdges(graph *g,int  edges[][TWO], int * numberEdges);
void
enterEdges(int edges[][TWO],int *numberEdges);

int
readEdgeList(int edges[][TWO], int *numberEdges);
int
readGraphEdges();


void
buildGraphStruct(int edges[][TWO], int numberEdges,struct Graph *g);

int contractAfterDelete (int t1,int t2,int D1,int sendback,
                TUTTE tutteMat,
                TUTTEO tutteMatX
               );
int
nextVertex(struct Graph *g,int  vt);
int
prevVert( struct Graph *g, int vt);
int
headEdgeList( struct Graph *g, int vt);
int vertVisited( struct Graph *g, int vt);
int
vertName( struct Graph *g, int vt);
int
vertDegree( struct graph *g, int vt);
void
setNextVertex( struct graph *g, int vt,int  vt1);
void
setPrevVert( struct graph *g, int vt,int  vt1);
void
setVertDegree( struct graph *g, int vt,int  amt);
void
setVertVisited( struct graph *g, int vt,int amt);
void
incrVertDegree( struct graph *g, int vt,int  amt);
int
nextEdge( struct graph *g, int ne);
int
prevEdge( struct graph *g, int ne);
int
vertListOtherEnd( struct graph *g, int ne);
int
edgeInSpTree( struct graph *g, int ne);
int
nameOtherEnd( struct graph *g, int ne);
int
otherEndEntry( struct graph *g, int ne);
int
firstEdge( struct graph *g, int vt);
void
setEdgeInSpTree( struct graph *g, int ne,int amt);
void
setEdgeEndsInSpTree( struct graph *g, int ne,int  amt);
void
setNameOtherEnd( struct graph *g, int ne,int  vt);
void
setNextEdge (struct graph *g,int  ne, int ne1);
void
setOtherEndEntry(struct graph *g,int  ne, int ne1);
void
setPrevEdge(struct graph *g, int ne,int  ne1);
int
firstVertex( struct graph *g);
int
numVertices( struct graph *g);
int
numEdges( struct graph *g);
int
multEdgeGphVert( struct graph *g)
int
degOneDels( struct graph *g);
int
triangleDels( struct graph *g);
int
getYPower( struct graph *g);
int
getMultCount(struct graph *g,int  location);
void
removeMultCountValue( struct graph *g);
void
copyAndZeroMultCount(struct graph *g, short int newMC[]);
void
setMultCount(struct graph *g,short int  newMC[]);
void
setNoVertices(struct graph *g,int  amt);
void
setNoEdges(struct graph *g,int  amt);
void
setMinusone(struct graph *g, int amt);
void
setYPower(struct graph *g, int amt);
void
setVNew(struct graph *g,int  amt);
void
setMinustwo(struct graph *g,int  amt);
void
setNewMultCount(struct graph *g,int  value);
void
incrYPower(struct graph *g,int  amt);
void
incrNoVertices(struct graph *g,int  amt);
void
incrNoEdges(struct graph *g,int  amt);
void
incrTriangleDels(struct graph *g,int  amt);
int
incrDegOneDels(struct graph *g,int  amt);

id
deleteContract(
               int C,
               int threshnum,
               int threshtable[],
               int newthreshold[],
               TUTTE tutteMat,
               TUTTEO tutteMatX
              );
void
detectAndDeleteLoop( struct graph *g);
int
eliminateTriangle( struct graph *g,struct graph *k);
void
enterEdgesBuildGraph(int *C,int *threshcount,int threshtable[],int newthreshold[]);
int fiveTreesnew(
                 int C,
                 int vertIndex[],
                 TUTTE tutteMat2,
                 TUTTEO tutteMat2X
                );
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

void findDegOne( struct Graph *g);
void
findInvariant(struct Graph *g2,int *m1,int canong[]);
void
mywrite(Graph *g,int m,int n);
int
computeNumwords(int gv);
int
gotMultiple ( int C);

void
hashinit();
unsigned int
hashvalue(int *h,int n);
void
hashinsert(unsigned int *p,unsigned long int hash, int gv,int  gvnew,int noByte);
int
* hashlookup(int gv, int gvnew, int canong[],unsigned long int hash,int w);
int
isolookup(struct Graph *h,int canong[], unsigned long int *hash,TUTTE  tutteMat,TUTTEO tutteMat1);
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
identifyFives (struct Graph *g,
       TUTTE tutteMat,
       TUTTEO tutteMatX
      );
void
identifySixes  (struct Graph *g,
                TUTTE tutteMat1,
                TUTTEO tutteMat1X
               );
void
identifySixesA1 (struct Graph *g,int  degseq,TUTTE  tutteMat1,TUTTEO tutteMat1X);
void
identifySixesA2 (struct Graph *g,int  degseq,TUTTE  tutteMat1,TUTTEO tutteMat1X);
void
identifySixesB1 (struct Graph *g,int  degseq,TUTTE  tutteMat1,TUTTEO tutteMat1X);
void
identifySixesB2 (struct Graph *g,int  degseq,TUTTE  tutteMat1,TUTTEO tutteMat1X);
int
degreesofnhbrs(struct Graph *g, int vt);
int
nextofdegree(struct Graph *g, int *vt, int degree);
int
nextcommonadj(struct Graph *g,int v1, int v2);
int
commonadj(struct Graph *g,int v1,int v2);
int
nextdegnadjtov(struct Graph *g,int *ne1,int degree);
int
nodegnadjtov(struct Graph *g,int vt, int n);
int
isadj(int vt1,int vt2, struct Graph *g);
int
isadjedgename(int vt1, int vt2, struct Graph *g);
int
nodegn(struct Graph *g, int n);
void
deletevrtx( struct Graph *g, int vt);
void
multEdgeSmallGraphElimination(
               int *C,
               int startused,
               TUTTE tutteMat,
               TUTTEO tutteMatX
              );
void
multiplyByFactors(struct Graph *g, TUTTE tutteMat,TUTTEO tutteMatX,TUTTE tutteMat1,TUTTEO tutteMat1X,
                   int  gminusone, int gminustwo);
int
matrixspecial(short int n13,TUTTE tutteMat1,TUTTEO tutteMat1X);

int
matrixspecial1(int nonzeroColumn,int columnBottom[],int nonzeroRow,
    short int n13,TUTTE tutteMat1,TUTTEO tutteMat1X);

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





void
contract(int t1,int t2,struct Graph *g);
int
areMultiple( struct Graph *g);
void
printGraph( struct Graph *g);
int
loop(int t1,struct Graph *g);
void
copyGraph(struct Graph *g,struct Graph *k);
int
deleteEdge(int place,struct Graph *g);
void
permEdges(int NCARDS,int cards[]);
short int nfrom ( short int low, short int high );
int shuffl(int deck[], int NCARDS);
int
preSevenFindDeg2 (struct Graph * g,TUTTE  tutteMat,TUTTEO tutteMatX);
void printTutte(TUTTE tutteMat,TUTTEO tutteMatX);
int
recapStats(struct Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void
deleteAndContractMultEdge (int C,
                TUTTE tutteMat,
                TUTTEO tutteMatX
               );
void
retree( struct Graph *g);
int
nontree( struct Graph *g);
void
detreeForContract(int e2,int t1,struct Graph *g);
int
untree(int e2, int t1, struct Graph *g);
int
findspan( struct Graph *g);
int
dfs(int vertLoc,struct Graph *g);

int detectAndComputeTrees(struct Graph *g,TUTTE tutteMat, TUTTEO tutteMatX);
void
sevenpart11(struct Graph *g,int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart12(struct Graph *g,int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart13(struct Graph *g,int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart1(struct Graph *g, TUTTE tutteMat, TUTTEO tutteMatX);


void
sevenpart2dra(struct Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart2drb(struct Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart2drc(struct Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart2drd(struct Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart2dre(struct Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart2drf(struct Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart2drg(struct Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart2drh(struct Graph *g, int degseq, TUTTE tutteMat,TUTTEO tutteMatX);

void
sevenpart2driver(struct Graph *g, TUTTE tutteMat, TUTTEO tutteMatX);

void
sevenpart3dra(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drb(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drb1(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drb2(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drb3(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drc(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drc1(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drc2(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drc3(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drd(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drd1(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drd2(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drd3(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3dre(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3dre1(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3dre2(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3dre3(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drf(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drf1(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drf2(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart3drf3(struct Graph *g, int degseq,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart41(struct Graph *g, TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart42(struct Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void
sevenpart43(struct Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);

void
sevenpart44(struct Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);

void
sevenpart45(struct Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);

void
sevenpart4a(struct Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);

void
sevenpart4b(struct Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);

void
sevensDriver(struct Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);

void
sixOrFewer(struct Graph *g,TUTTE tutteMat,TUTTEO tutteMatX);
void
twoMultipleEliminate(int *C, int startused,TUTTE  tutteMat,TUTTEO tutteMatX);

void
threeMultipleEliminate(int *C, int startused,TUTTE  tutteMat,TUTTEO tutteMatX);

void
fourMultipleEliminate(int *C, int startused,TUTTE  tutteMat,TUTTEO tutteMatX);
void
fiveMultipleEliminate(int *C, int startused,TUTTE  tutteMat,TUTTEO tutteMatX);
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

