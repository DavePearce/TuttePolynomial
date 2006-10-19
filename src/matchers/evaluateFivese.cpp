#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "core/tutte.h"

/******************************************************/
/*                                                    */
/*                   start degseq410                  */
/*                                                    */
/*                                                    */
/*                                                    */

/*
Precondition: C--index to graph array pointing to graph with degree sequence 410
              arrays vertDeg and vertIndex give a canonical description of the graph
	      tutteMat2 and tutteMat2X are arrays with values for the
	      current state of the computation

Postcondition: tutteMat2 and tutteMat2X contain the current state of the
		computation after processing g[C]

Modify: tutteMat2 and tutteMat2X are augmented by the value of the tutte poly
	of the 410 graph

Return: 1 to signify graph needs replacing

*/


int degseq410(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X)
{

int i,                   /* for parameter                            */
    j,
    k,
    m,
    ne,                  /* location of edge                         */
    xp,                  /* degree of x in monomial                  */
    yp,                  /* degree of y in monomial                  */
    vertRename[10],      /* canonical labelling                      */
    edgeCount[10][10];   /* incidence of vertex [*][] with [][*]     */

//printf("GOT INTO 410\n");
for(i=1;i<=5;i++)
  if(vertDeg[i]==2)
    {
       vertRename[1]=vertIndex[i];
       break;
    }

j=1;
for(i=1;i<=5;i++)
  if((vertDeg[i]==3)&&isadj(vertIndex[i],vertRename[1],&g[C])) 
    {
      j++;
      vertRename[j]=vertIndex[i];
    }
vertRename[5]=vertRename[3];

j=2;
for(i=1;i<=5;i++)
  if((vertDeg[i]==3)&&!isadj(vertIndex[i],vertRename[1],&g[C])) 
    {
      j++;
      vertRename[j]=vertIndex[i];
    }
assert(vertRename[1]>0);
assert(vertRename[2]>0);
assert(vertRename[3]>0);
assert(vertRename[4]>0);
assert(vertRename[5]>0);


edgeCount[1][2]=0;
edgeCount[2][3]=0;
edgeCount[3][4]=0;
edgeCount[4][5]=0;
edgeCount[1][5]=0;
edgeCount[2][4]=0;
edgeCount[3][5]=0;
ne=g[C].edg[g[C].vrtx[vertRename[2]].fedge].front;
while(ne!=EOLIST) {
  if(g[C].edg[ne].vertlist==vertRename[1])
    ++edgeCount[1][2];
  else
    if(g[C].edg[ne].vertlist==vertRename[3])
      ++edgeCount[2][3];
    else
      if(g[C].edg[ne].vertlist==vertRename[4])
        ++edgeCount[2][4];
  ne=g[C].edg[ne].front;
}

ne=g[C].edg[g[C].vrtx[vertRename[5]].fedge].front;
while(ne!=EOLIST) 
  {
     if(g[C].edg[ne].vertlist==vertRename[1])
       ++edgeCount[1][5];
     else
       if(g[C].edg[ne].vertlist==vertRename[4])
         ++edgeCount[4][5];
       else
         if(g[C].edg[ne].vertlist==vertRename[3])
           ++edgeCount[3][5];
     ne=g[C].edg[ne].front;
  }

ne=g[C].edg[g[C].vrtx[vertRename[3]].fedge].front;
while(ne!=EOLIST) 
  {
    if(g[C].edg[ne].vertlist==vertRename[4])
      ++edgeCount[3][4];
    ne=g[C].edg[ne].front;
  }



assert(edgeCount[1][2]>0);
assert(edgeCount[2][3]>0);
assert(edgeCount[3][4]>0);
assert(edgeCount[4][5]>0);
assert(edgeCount[1][5]>0);
assert(edgeCount[2][4]>0);
assert(edgeCount[3][5]>0);


for(i=0;i<edgeCount[1][5];i++)
for(j=0;j<edgeCount[1][2];j++)
for(k=0;k<edgeCount[2][3];k++)
for(m=0;m<edgeCount[3][4];m++)
  {
    xp=((i==0)?1:0)+
       ((j==0)?1:0)+
       ((k==0)?1:0)+
       ((m==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }

for(i=0;i<edgeCount[1][2];i++)
for(j=0;j<edgeCount[2][3];j++)
for(k=0;k<edgeCount[3][4];k++)
for(m=0;m<edgeCount[3][5];m++)
  {
    xp=((i==0)?1:0)+
       ((j==0)?1:0)+
       ((k==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }


for(i=0;i<edgeCount[3][4];i++)
for(j=0;j<edgeCount[1][2]+edgeCount[2][3];j++)
for(k=0;k<edgeCount[1][5];k++)
for(m=0;m<edgeCount[3][5];m++)
  {
    xp=((i==0)?1:0)+
       ((j==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }

for(i=0;i<edgeCount[1][2];i++)
for(j=0;j<edgeCount[3][5]+edgeCount[3][4];j++)
for(k=0;k<edgeCount[1][5];k++)
for(m=0;m<edgeCount[4][5];m++)
  {
    xp=((i==0)?1:0)+
       ((j==0)?1:0)+
       ((k==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }


for(i=0;i<edgeCount[1][2];i++)
for(j=0;j<edgeCount[3][4]+edgeCount[3][5];j++)
for(k=0;k<edgeCount[2][3];k++)
for(m=0;m<edgeCount[4][5];m++)
  {
    xp=((i==0)?1:0)+
       ((j==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }


for(i=0;i<edgeCount[1][2]+edgeCount[3][5]+edgeCount[3][4];i++)
for(j=0;j<edgeCount[2][3];j++)
for(k=0;k<edgeCount[1][5];k++)
for(m=0;m<edgeCount[4][5];m++)
  {
    xp=((i==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }


for(i=0;i<edgeCount[1][5];i++)
for(j=0;j<edgeCount[4][5];j++)
for(k=0;k<edgeCount[2][3]+edgeCount[3][4];k++)
for(m=0;m<edgeCount[2][4];m++)
  {
    xp=((i==0)?1:0)+
       ((j==0)?1:0)+
       ((k==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }

for(i=0;i<edgeCount[1][5]+edgeCount[4][5];i++)
for(j=0;j<edgeCount[2][3]+edgeCount[3][4];j++)
for(k=0;k<edgeCount[1][2];k++)
for(m=0;m<edgeCount[2][4];m++)
  {
    xp=((i==0)?1:0)+
       ((j==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }



for(i=0;i<edgeCount[1][5];i++)
for(j=0;j<edgeCount[4][5]+edgeCount[2][3]+edgeCount[3][4];j++)
for(k=0;k<edgeCount[2][4];k++)
for(m=0;m<edgeCount[3][5];m++)
  {
    xp=((i==0)?1:0)+
       ((j==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }


for(i=0;i<edgeCount[1][5]+edgeCount[4][5]+edgeCount[2][3]+edgeCount[3][4];i++)
for(j=0;j<edgeCount[2][4];j++)
for(k=0;k<edgeCount[1][2];k++)
for(m=0;m<edgeCount[3][5];m++)
  {
    xp=((i==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }


return(ONE);

} /* end degseq410 */



/*                                                    */
/*                                                    */
/*                   end degseq410                    */
/*                                                    */
/*                                                    */
/******************************************************/
/*                                                    */
/*                                                    */
/*                   start degseq5000                 */
/*                                                    */
/*                                                    */
/*                                                    */

/*
Precondition: C--index to graph array pointing to graph with degree sequence 5000
              arrays vertDeg and vertIndex give a canonical description of the graph
	      tutteMat2 and tutteMat2X are arrays with values for the
	      current state of the computation

Postcondition: tutteMat2 and tutteMat2X contain the current state of the
		computation after processing g[C]

Modify: tutteMat2 and tutteMat2X are augmented by the value of the tutte poly
	of the 5000 graph

Return: 1 to signify graph needs replacing

*/


int degseq5000(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X)
{
int i,                   /* for parameter                            */
    j,
    k,
    m,
    ne,                  /* location of edge                         */
    xp,                  /* degree of x in monomial                  */
    yp,                  /* degree of y in monomial                  */
    edgeCount[10][10];   /* incidence of vertex [*][] with [][*]     */


for(i=0;i<6;i++) 
for(j=0;j<6;j++) 
  {
    edgeCount[i][j]=0;
  }


ne=g[C].edg[g[C].vrtx[vertIndex[1]].fedge].front;
while(ne!=EOLIST) 
  {
    if(g[C].edg[ne].vertlist==vertIndex[2])
      ++edgeCount[1][2];
    else
      if(g[C].edg[ne].vertlist==vertIndex[3])
        ++edgeCount[1][3];
      else
        if(g[C].edg[ne].vertlist==vertIndex[4])
          ++edgeCount[1][4];
        else
          if(g[C].edg[ne].vertlist==vertIndex[5])
            ++edgeCount[1][5];
    ne=g[C].edg[ne].front;
  }

ne=g[C].edg[g[C].vrtx[vertIndex[2]].fedge].front;
while(ne!=EOLIST) 
  {
    if(g[C].edg[ne].vertlist==vertIndex[3])
      ++edgeCount[2][3];
    else
      if(g[C].edg[ne].vertlist==vertIndex[4])
        ++edgeCount[2][4];
      else
        if(g[C].edg[ne].vertlist==vertIndex[5])
          ++edgeCount[2][5];
    ne=g[C].edg[ne].front;
  }

ne=g[C].edg[g[C].vrtx[vertIndex[3]].fedge].front;
while(ne!=EOLIST) 
  {
    if(g[C].edg[ne].vertlist==vertIndex[4])
      ++edgeCount[3][4];
    else
      if(g[C].edg[ne].vertlist==vertIndex[5])
        ++edgeCount[3][5];
    ne=g[C].edg[ne].front;
  }

ne=g[C].edg[g[C].vrtx[vertIndex[4]].fedge].front;
while(ne!=EOLIST) 
  {
    if(g[C].edg[ne].vertlist==vertIndex[5])
      ++edgeCount[4][5];
    ne=g[C].edg[ne].front;
  }

assert(edgeCount[1][2]>0);
assert(edgeCount[1][3]>0);
assert(edgeCount[1][4]>0);
assert(edgeCount[1][5]>0);
assert(edgeCount[2][3]>0);
assert(edgeCount[2][4]>0);
assert(edgeCount[2][5]>0);
assert(edgeCount[3][4]>0);
assert(edgeCount[3][5]>0);
assert(edgeCount[4][5]>0);


  completePolyWithNoX(edgeCount[1][5],
                      edgeCount[1][2]+edgeCount[2][5],
                      edgeCount[1][3]+edgeCount[3][5],
                      edgeCount[1][4]+edgeCount[4][5],
                      edgeCount[2][3],
                      edgeCount[2][4],
                      edgeCount[3][4],
                      tutteMat2,
                      tutteMat2X);
  completePolyWithNoX(edgeCount[2][5],
                      edgeCount[1][2],
                      edgeCount[1][3],
                      edgeCount[1][4],
                      edgeCount[2][3]+edgeCount[3][5],
                      edgeCount[2][4]+edgeCount[4][5],
                      edgeCount[3][4],
                      tutteMat2,
                      tutteMat2X);
  completePolyWithNoX(edgeCount[3][5],
                      edgeCount[1][2],
                      edgeCount[1][3],
                      edgeCount[1][4],
                      edgeCount[2][3],
                      edgeCount[2][4],
                      edgeCount[3][4]+edgeCount[4][5],
                      tutteMat2,
                      tutteMat2X);
  completePolyWithX(edgeCount[4][5],
                    edgeCount[1][2],
                    edgeCount[1][3],
                    edgeCount[1][4],
                    edgeCount[2][3],
                    edgeCount[2][4],
                    edgeCount[3][4],
                    tutteMat2,
                    tutteMat2X);



return(ONE);

} /* end degseq5000 */



/*                                                    */
/*                                                    */
/*                   end degseq5000                   */
/*                                                    */
/*                                                    */
/******************************************************/
/*                                                    */
/*                                                    */
/*                 start degseq1400                   */
/*                                                    */
/*                                                    */
/******************************************************/

/*
Precondition: C--index to graph array pointing to graph with degree sequence 1400
	      arrays vertDeg and vertIndex give a canonical description of the graph
	      tutteMat2 and tutteMat2X are arrays with values for the
	      current state of the computation

Postcondition: tutteMat2 and tutteMat2X contain the current state of the
		computation after processing g[C]

Modify: tutteMat2 and tutteMat2X are augmented by the value of the tutte poly
	of the 1400 graph

Return: 1 to signify graph needs replacing

*/


int degseq1400(int C,int vertDeg[],int vertIndex[],TUTTE tutteMat2,TUTTEO tutteMat2X)
{
int i,                   /* for parameter                            */
    j,
    k,
    m,
    ne,                  /* location of edge                         */
    xp,                  /* degree of x in monomial                  */
    yp,                  /* degree of y in monomial                  */
    vertRename[10],      /* canonical labelling                      */
    edgeCount[10][10];   /* incidence of vertex [*][] with [][*]     */


//printf("K(5) - (3, 4) - (2, 5)\n"); 


for(i=1;i<=5;i++)
  if(vertDeg[i]==4) 
    {
      vertRename[1]=vertIndex[i];
      break;
    }

vertRename[2]=g[C].edg[g[C].edg[g[C].vrtx[vertRename[1]].fedge].front].vertlist;

j=2;
for(i=1;i<=5;i++)
  if(vertDeg[i]==3 &&vertRename[2]!=vertIndex[i]
                   && isadj(vertRename[2],vertIndex[i],&g[C])) 
    {
      ++j;
      vertRename[j]=vertIndex[i];
      if(j==4)
        break;
    }
for(i=1;i<=5;i++)
  if(vertDeg[i]==3 && vertRename[2]!=vertIndex[i]
                   && !isadj(vertRename[2],vertIndex[i],&g[C])) 
    {
      vertRename[5]=vertIndex[i];
      break;
    }

assert(vertRename[1]>0);
assert(vertRename[2]>0);
assert(vertRename[3]>0);
assert(vertRename[4]>0);
assert(vertRename[5]>0);


for(i=0;i<10;i++)
for(j=0;j<10;j++)
  edgeCount[i][j]=ZERO;

ne=g[C].edg[g[C].vrtx[vertRename[1]].fedge].front;
while(ne!=EOLIST) 
  {
    if(g[C].edg[ne].vertlist==vertRename[2])
      ++edgeCount[1][2];
    else
      if(g[C].edg[ne].vertlist==vertRename[3])
        ++edgeCount[1][3];
      else
        if(g[C].edg[ne].vertlist==vertRename[4])
          ++edgeCount[1][4];
        else
          if(g[C].edg[ne].vertlist==vertRename[5])
            ++edgeCount[1][5];
    ne=g[C].edg[ne].front;
  }

ne=g[C].edg[g[C].vrtx[vertRename[4]].fedge].front;
while(ne!=EOLIST) 
  {
    if(g[C].edg[ne].vertlist==vertRename[2])
      ++edgeCount[2][4];
    else
      if(g[C].edg[ne].vertlist==vertRename[5])
        {
           ++edgeCount[4][5];
        }
    ne=g[C].edg[ne].front;
  }

ne=g[C].edg[g[C].vrtx[vertRename[3]].fedge].front;
while(ne!=EOLIST) 
  {
    if(g[C].edg[ne].vertlist==vertRename[2])
      ++edgeCount[2][3];
    else
      if(g[C].edg[ne].vertlist==vertRename[5])
        ++edgeCount[3][5];
    ne=g[C].edg[ne].front;
  }

assert(edgeCount[1][2]>0);
assert(edgeCount[1][3]>0);
assert(edgeCount[1][4]>0);
assert(edgeCount[1][5]>0);
assert(edgeCount[2][3]>0);
assert(edgeCount[2][4]>0);
assert(edgeCount[4][5]>0);
assert(edgeCount[3][5]>0);

completePolyWithNoX(edgeCount[2][4],edgeCount[1][3],
                    edgeCount[1][5],
                    edgeCount[1][2]+edgeCount[1][4],
                    edgeCount[3][5],
                    edgeCount[2][3],
                    edgeCount[4][5],
                    tutteMat2,
                    tutteMat2X);






for(i=0;i<edgeCount[1][3];i++)
for(j=0;j<edgeCount[2][3];j++)
for(k=0;k<edgeCount[3][5];k++)
for(m=0;m<edgeCount[4][5];m++)
  {
    xp=((i==0)?1:0)+
       ((j==0)?1:0)+
       ((k==0)?1:0)+
       ((m==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }


for(i=0;i<edgeCount[1][3]+edgeCount[3][5];i++)
for(j=0;j<edgeCount[2][3];j++)
for(k=0;k<edgeCount[4][5];k++)
for(m=0;m<edgeCount[1][5];m++)
  {
    xp=((i==0)?1:0)+
       ((j==0)?1:0)+
       ((k==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }


for(i=0;i<edgeCount[1][3]+edgeCount[2][3];i++)
for(j=0;j<edgeCount[3][5];j++)
for(k=0;k<edgeCount[4][5];k++)
for(m=0;m<edgeCount[1][2];m++)
  {
    xp=((i==0)?1:0)+
       ((j==0)?1:0)+
       ((k==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }


for(i=0;i<edgeCount[1][3]+edgeCount[3][5]+edgeCount[2][3];i++)
for(j=0;j<edgeCount[4][5];j++)
for(k=0;k<edgeCount[1][2];k++)
for(m=0;m<edgeCount[1][5];m++)
  {
    xp=((i==0)?1:0)+
       ((j==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }


for(i=0;i<edgeCount[2][3];i++)
for(j=0;j<edgeCount[3][5];j++)
for(k=0;k<edgeCount[1][5]+edgeCount[4][5];k++)
for(m=0;m<edgeCount[1][4];m++)
  {
    xp=((i==0)?1:0)+
       ((j==0)?1:0)+
       ((k==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }


for(i=0;i<edgeCount[2][3];i++)
for(j=0;j<edgeCount[1][5]+edgeCount[4][5]+edgeCount[3][5];j++)
for(k=0;k<edgeCount[1][3];k++)
for(m=0;m<edgeCount[1][4];m++)
  {
    xp=((i==0)?1:0)+
       ((j==0)?1:0);
    yp=i+j+k+m;
    tutteMat2[yp][xp]++;
  }


for(i=0;i<edgeCount[1][3]+edgeCount[2][3];i++)
for(j=0;j<edgeCount[1][5]+edgeCount[4][5];j++)
for(k=0;k<edgeCount[1][2];k++)
for(m=0;m<edgeCount[1][4];m++)
  {
     xp=((i==0)?1:0)+
       ((j==0)?1:0);
     yp=i+j+k+m;
     tutteMat2[yp][xp]++;
  }


for(i=0;i<edgeCount[1][5]+edgeCount[4][5]+edgeCount[2][3]+edgeCount[1][3];i++)
for(j=0;j<edgeCount[1][2];j++)
for(k=0;k<edgeCount[1][4];k++)
for(m=0;m<edgeCount[3][5];m++)
  {
     xp=((i==0)?1:0);
     yp=i+j+k+m;
     tutteMat2[yp][xp]++;
  }


return(ONE);

} /* end degseq1400 */

/*                                                    */
/*                                                    */
/*                   end degseq1400                   */
/*                                                    */
/*                                                    */
/******************************************************/




