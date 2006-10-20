#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "tutte.h"

/**********************************************/
/*                                            */
/*        start of contractAfterDelete        */
/*                                            */
/*                                            */


// WHAT IS SENDBACK ????????????????????????????

int contractAfterDelete (int t1,int t2,int D1,int sendback, TUTTE tutteMat, TUTTEO tutteMatX) {
  int smallreturn;
  int treeornot;
  
  
  if( sendback == ZERO )
    {/* sendback==0 */
      contract(t1,t2,&g[D1]);      
      treeornot = detectAndComputeTrees(&g[D1], tutteMat,tutteMatX);

      if(treeornot) { 
	pushavail(D1, &avail); 
      } else if( numVertices(&g[D1]) <= FIVE ) {

	smallreturn = evaluateSmallGraphs(D1,tutteMat,tutteMatX);

	if( smallreturn ) {
	  pushavail(D1,&avail); 
	} else { 
	  findDegOne(&g[D1]);
	  putonstack(&used,D1); 
	}
      } else {
	findDegOne(&g[D1]);           
	putonstack(&used, D1);
      } 

    } else if( sendback == ONE ) {

      treeornot = detectAndComputeTrees(&g[D1], tutteMat, tutteMatX);
      pushavail(D1, &avail);

    } else if( sendback == TWO ) {
	treeornot = detectAndComputeTrees(&g[D1], tutteMat, tutteMatX);

         if( treeornot ) { 
	   pushavail(D1, &avail); 
	 } else {
	   findDegOne(&g[D1]);
	   retree(&g[D1]);                   
	   putonstack(&used,  D1);
	 }
    }

} /* end contractAfterDelete  */


/*                                            */
/*        end of contractAfterDelete          */
/*                                            */
/**********************************************/




