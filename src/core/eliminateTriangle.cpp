#include "tutte.h"

/**********************************************/
/*                                            */
/*           start of eliminateTriangle       */
/*                                            */
 
/* 

Precondition: A graph g that may contain a vertex of degree two that is
              part of a triangle and an instantiated graph that may be
              initialized before being returned  

Modifies: if there is a triangle in the graph, the graph structure has edges 
          and vertices removed but remains a graph the computation value 
          for the number of triangles deleted is incremented

Postcondition:  the original graph will have its triangle removed (the 
                two edges incident to the vertex of degree two
                and the structure value (*g).minustwo will be incremented
                If no triangle is found or the graph is a tree or has three or fewer vertices
                0 is returned and the instantiation of k remains an instantiuation

Return: if the graph has three or fewer vertices, it is immediately returned whether 
        it has a triangle or not. Either 0 or 1 is returned. 1 is returned if a 
        triangle is found and removed together with a second graph called k that 
        is required by the d/c process. if no triangle is found, 0 is returned. 

*/


int 
eliminateTriangle( struct Graph *g,struct Graph *k)
{
int vertex1, 
    vertex2, 
    vertex3, 
    nameVertex3,
    edge12, 
    edge13, 
    edge23,
    switch5;            /* switch to indicate presence of triangle edge          */

//printf("eliminateTriangle\n");
/* eliminate a triangle with a degree two vertex */
if( ( numVertices(g)  <= THREE ) 
   || ( ( ( numEdges(g)  - numVertices(g)  + ONE ) / TWO + ONE )
                            == numVertices(g)  ) ) 
  {
     return(ZERO); 
  }


for(vertex1 = firstVertex(g); vertex1 != LIST_END; vertex1 = nextVertex(g, vertex1))
  { /* 2 */
     if( vertDegree(g, vertex1)  == TWO ) 
       { /* 3 */
identifyTriangle(g,&vertex1,&vertex2,&vertex3,&edge12,&edge13,&edge23,&switch5);

          if ( switch5 == ONE ) 
            { /* 5 */
deleteAndContractTriangle(g,k,vertex1,vertex2,vertex3,edge12,edge13,edge23);
return(ONE);
              }  /* 5 */
            } /* 3 */
       } /* 2 */ 
        
return( ZERO );

} /* end eliminateTriangle */

int
deleteAndContractTriangle(struct Graph *g,struct Graph * k,int vertex1,int vertex2,int vertex3,
int edge12,int edge13,int edge23)
{

//                trianglevertex = vertex3;  //vertListOtherEnd(g, edge23);  
                deleteEdge(
                        edge12,
                        g
                       );
                deleteEdge(
                        edge13,
                        g
                       );
                retree(g);
                copyGraph(
                          g,
                          k
                         );
                incrTriangleDels(g, ONE);  
                 /* deleteEdge removes vertices that had degree 1 before the edge
                    deletion-this causes contract consternation so we check for it
                 */
                if( ( vertDegree(k, vertex2)  == ONE ) 
                        || ( vertDegree(k, vertex3/*trianglevertex*/)  == ONE ) )
                  {
                     deleteEdge(
                             edge23,
                             k
                            );
                     /* really a contraction of the edge 
                        because one end has degree 1 */
                  }
                else
                  {
                     deleteEdge(
                             edge23,
                             k
                            );
                     contract(
                              vertex2,
                              vertex3,  //trianglevertex,
                              k
                             );
                  }
                incrYPower(k, ONE);  
                retree(k);
                findDegOne(k); 
                findDegOne(g);
                return( ONE );
              }  /* end deleteAndContractTriangle */ 


/*                                            */
/*           end of eliminateTriangle         */
/*                                            */
/**********************************************/
/*                                            */
/*           end of identifyTriangle          */
/*                                            */
/*                                            */
int
identifyTriangle(struct Graph *g, int *vertex1,int *vertex2,int *vertex3,
int *edge12,int *edge13,int *edge23,int *switch5)
{
int aimVertex3,
    possibleEdge;


	  
           /* vertex1 has edges at nne and nnee */
          *edge12 = firstEdge(g, *vertex1);
          *edge13 = nextEdge(g, *edge12);  
          *vertex2 = vertListOtherEnd(g, *edge12);
          *vertex3 = vertListOtherEnd(g, *edge13);
           
           aimVertex3 = nameOtherEnd(g, *edge13);  
	  *switch5 = ZERO;

          for(possibleEdge = firstEdge(g, *vertex2); 
                 possibleEdge != LIST_END && *switch5 == ZERO; 
                    possibleEdge = nextEdge(g, possibleEdge))
            { /* 4 */
               if ( aimVertex3  == nameOtherEnd(g, possibleEdge ) )
                 {
                    /* set switch when we find third edge of triangle */
                    *switch5 = ONE;
                    *edge23 = possibleEdge;
                 }
            } /* 4 */
return(*switch5);
}




