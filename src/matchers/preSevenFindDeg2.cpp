#include "core/tutte.h"

/********************************************/
/*                                          */
/*       start of preSevenFindDeg2          */
/*                                          */

/*

Precondition: a graph location g and the arrays tutteNat and tutteMatX
              that hold the current status of the computation

Postcondition: if *g is a graph with a vertex of degree 2, the vertex is deleted
               and the contract graph has its tutte poly comtribute to arrays 
               tutteMat and tutteMatX. g is returned as the address of the 
               graph with the vertex of degree 2 deleted or just returned with 
               no change if no vertex of degree 2 is found

*/




int
preSevenFindDeg2 (struct Graph * g,TUTTE  tutteMat,TUTTEO tutteMatX)
{

/* cannot get here if the graph is the seven cycle-
   filtered out in the protection of the call
   also cannot have any trees as K5 because
   the 7 cycle doesn't get here */

int triangletwo,    /* return value for twoApex:
  			1==found real triangle and */
    D1,      
    verttwo,        /*0== no degree 2 vertex identified
      			1== degeree 2 vertex identified               */
    vt,             /* location on vertex list                        */
    nevt,
    nnevt,
    nne,            /* location of edge                               */      
    ne,             /* location on edge list of degree 2 vertex       */
    neopposite;     /* location on vertex list identifying the 
      			other end of one of the edges incident with 
      			degree 2 vertex                               */
struct Graph k5;    /* graph used in local delete/contract            */
//printf("preSevenFindDeg2\n");

/* graph is not a tree */
if( ( numVertices(g)  != ( ( numEdges(g)  - numVertices(g) +  ONE ) / TWO + ONE ) ) )
  {  /* b */
     verttwo = ZERO;
     for(vt = firstVertex(g); ( vt != LIST_END ) && ( verttwo == ZERO ); vt = nextVertex(g, vt)) 
       {  /* c */
          if( vertDegree(g, vt) == TWO )
            { 
               verttwo = vt;
            }
       } /* c */
     if( verttwo != ZERO )
       { /* d */
          ne = firstEdge(g, verttwo);  
          nne = nextEdge(g, ne);  
          nevt = vertListOtherEnd(g, ne); 
          nnevt = vertListOtherEnd(g, nne);  
          if( isadj(nevt,nnevt,g) )
            {
               return( ZERO );
            }
          if( vertDegree(g, nevt)  == ONE )
            printf("degree 1 nevt\n");
          deleteEdge(ne,g);
          retree(g);
          copyGraph(
                    g,
                    &k5
                   ); /*k5 = (*g);*/
          findDegOne(g);
          contract(
                   verttwo,
                   nevt,
                   &k5
                  );
          retree(&k5);
          /*                                            */
          /* A 7 vertex graph with a vertex deleted is  */
          /* no more than a 6 vertex graph for which    */
          /* we know the answers!                       */
          /*                                            */ 
          sixOrFewer(
                     &k5,
                     tutteMat,
                     tutteMatX
                    );
          retree( g );
          return( ZERO );
       }  /* d */
  }  /* b */

return( ZERO );

}/* end preSevenFindDeg2 */
  
/*                                            */
/*       end of preSevenFindDeg2              */
/*                                            */
/**********************************************/

