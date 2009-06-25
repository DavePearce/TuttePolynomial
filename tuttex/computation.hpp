// (C) Copyright David James Pearce and Gary Haggard, 2007. 
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied 
// warranty, and with no claim as to its suitability for any purpose.
//
// Email: david.pearce@mcs.vuw.ac.nz

#ifndef COMPUTATION_HPP
#define COMPUTATION_HPP

#include "nauty_graph.hpp"

// A graph node represents a canonically labelled graph which has been
// encountered already.
struct graph_node {
  struct graph_node *next;  
  struct graph_node *prev;  
  unsigned int gindex; // gindex of original graph.
  unsigned int hit_count;
  unsigned int size; // in bytes including header
  // nauty graph key starts here
};

#define NAUTY_GRAPH(x) (((unsigned char*)x)+sizeof(struct graph_node))

// a tree node represents a component of the computation tree.
#define TREE_FRONTIER 0
#define TREE_SUM 1
#define TREE_PRODUCT 2
#define TREE_FACTOR 3
#define TREE_CONSTANT 4

struct tree_node {
  unsigned char type;
  unsigned int refcount;
  unsigned int lhs;
  unsigned int rhs;
};

class computation {
private:
  std::vector<graph_node *> gindex;     // map tree numbers to graph locations
  std::vector<graph_node> buckets;      // bucket array  
  std::vector<tree_node *> tindex;     // map tree numbers to tree location
  std::vector<unsigned int> frontier;  // graphs on BFS frontier
  uint64_t bufsize;            
  unsigned char *start_p;        // buffer start ptr
  unsigned char *graph_p;        // pointer to next available space for graph
  unsigned char *tree_p;         // pointer to last tree node
  unsigned int hits;
  unsigned int misses;
  unsigned int collisions;
public:
  computation(uint64_t max_size, size_t nbs = 10000) : buckets(nbs) {
    bufsize = max_size;
    start_p = new unsigned char[max_size];
    graph_p = start_p;    
    tree_p = start_p + bufsize;
    hits = 0;
    misses = 0;
    collisions = 0;
  }

  ~computation() {
    delete [] start_p;
  }

  void clear() {
    // reset graph and tree pointers
    graph_p = start_p;    
    tree_p = start_p + bufsize;
    // empty all buckets
    for(int i=0;i!=buckets.size();++i) { 
      buckets[i].next=NULL; 
      buckets[i].prev=NULL; 
    }    
    // done
  }

  template<class T>
  void initialise(T const &root) {
    // first, create a canonical labelling of the root
    unsigned char *ng = nauty_graph_build<T>(root);

    graph_node *gnode = graph_node_alloc(root.num_vertices() + root.num_multiedges());
    // second, create a canonical labelling of the graph
    nauty_graph_canon(ng,NAUTY_GRAPH(gnode));

    delete [] ng;    
    // third, create a tree node.
    struct tree_node *tnode = tree_node_alloc();
    // now, add it to the frontier and give it an index.
    frontier.push_back(gindex.size());
    gindex.push_back(gnode);
    tindex.push_back(tnode);
  }

  unsigned int frontier_size() { 
    return frontier.size();
  }

  unsigned int frontier_get(unsigned int index) { 
    return frontier[index];
  }

  // This method splits the frontier node on a biconnected component.
  // That is, it splits out the biconnected component and all edges it
  // contains into a separate graph, leaving what's left as is.
  unsigned int frontier_split(unsigned int index, unsigned int N, std::vector<bool> const &bicomp) { 
    unsigned int id = frontier[index];
    struct graph_node *gnode = gindex[id];
    unsigned char *graph = NAUTY_GRAPH(gnode);
    struct tree_node *tnode = tindex[id];
    tnode->type = TREE_PRODUCT;
    
    // First, compute residue graph
    struct graph_node *gresidue = graph_node_alloc(N);
    unsigned char *residueg = NAUTY_GRAPH(gresidue);
    nauty_graph_clone(graph,residueg);
    unsigned int gresidueid = gindex.size();
    tnode->lhs = gresidueid;
    gindex.push_back(gresidue);
    tindex.push_back(tree_node_alloc());
    frontier[index] = gresidueid;

    // Second, compute split graph
    struct graph_node *gsplit = graph_node_alloc(N);
    unsigned char *splitg = NAUTY_GRAPH(gsplit);
    static std::vector<unsigned int> mapping;
    mapping.resize(N);
    
    unsigned int i1=0,i2=0;
    for(std::vector<bool>::const_iterator i(bicomp.begin());i!=bicomp.end();++i) {
      if(*i) {
	mapping[i1++] = i2;
      }
      i2++;
    }

    for(unsigned int i=0;i!=N;++i) {
      for(unsigned int j=i;j!=N;++j) {
	unsigned int mi = mapping[i];
	unsigned int mj = mapping[j];
	if(nauty_graph_is_edge(residueg,mi,mj)) {
	  nauty_graph_add(splitg,i,j);
	  nauty_graph_delete(residueg,mi,mj);
	}
      }
    }

    unsigned int gsplitid = gindex.size();
    gsplit->gindex = gsplitid;
    tnode->rhs = gsplitid;
    gindex.push_back(gsplit);
    tindex.push_back(tree_node_alloc());
    frontier.push_back(gsplitid);

    return 1;
  }

  unsigned int frontier_delcontract(unsigned int index, unsigned int from, unsigned int to) {
    unsigned int id = frontier[index];
    struct graph_node *gnode = gindex[id];
    struct tree_node *tnode = tindex[id];

    tnode->type = TREE_SUM;

    // First, compute delete graph.
    struct graph_node *gdel = graph_node_alloc(nauty_graph_numverts(NAUTY_GRAPH(gnode)));
    nauty_graph_canong_delete(NAUTY_GRAPH(gnode),NAUTY_GRAPH(gdel),from,to);
    
    unsigned int isoid;
    bool lhs_match = lookup(NAUTY_GRAPH(gdel),isoid);
    if(lhs_match) {
      // this branch is now terminated.
      tnode->lhs = isoid;
      tindex[isoid]->refcount++;
      graph_p -= gdel->size; // free space!
    } else {
      store(gdel); // add to isomorph cache
      unsigned int gdelid = gindex.size();
      gdel->gindex = gdelid;
      tnode->lhs = gdelid;
      gindex.push_back(gdel);
      tindex.push_back(tree_node_alloc());
    }

    // Second, compute contract graph.
    struct graph_node *gcontract = graph_node_alloc(nauty_graph_numverts(NAUTY_GRAPH(gdel)));
    nauty_graph_canong_contract(NAUTY_GRAPH(gnode),NAUTY_GRAPH(gcontract),from,to,false); // ignore loops for now!

    bool rhs_match = lookup(NAUTY_GRAPH(gcontract),isoid);
    if(rhs_match) {
      // this branch is now terminated.
      tnode->rhs = isoid;
      tindex[isoid]->refcount++;
      graph_p -= gcontract->size; // free space!
    } else {
      store(gcontract); // add to isomorph cache
      unsigned int gconid = gindex.size();
      gcontract->gindex = gconid;
      tnode->rhs = gconid;
      gindex.push_back(gcontract);
      tindex.push_back(tree_node_alloc());
    }

    // At this point, we now have to figure out what's left on the
    // frontier.

    if(lhs_match && rhs_match) {
      frontier[index] = frontier.back();
      frontier.pop_back();
      return 0;
    } else if(rhs_match) {
      frontier[index] = tnode->lhs;
    } else if(lhs_match) {
      frontier[index] = tnode->rhs;
    } else {
      frontier[index] = tnode->lhs;
      frontier.push_back(tnode->rhs);
    }

    return 1;
  }

  bool frontier_terminate(unsigned int index) {
    unsigned int id = frontier[index];
    frontier[index] = frontier.back();
    frontier.pop_back();
    tree_node *tnode = tindex[id];
    tnode->type = TREE_CONSTANT;
  }  

  unsigned char *graph_ptr(unsigned int gidx) {
    return NAUTY_GRAPH(gindex[gidx]);
  }

private:
  inline graph_node *graph_node_alloc(unsigned int NN) {
    setword M = ((NN % WORDSIZE) > 0) ? (NN / WORDSIZE)+1 : NN / WORDSIZE;
    unsigned int size = (((NN*M)+NAUTY_HEADER_SIZE)*sizeof(setword))+sizeof(graph_node);
    
    if((graph_p+size) >= tree_p) { 
      std::cout << "BAD ALLOC IN GRAPH NODE ALLOC" << std::endl;
      throw std::bad_alloc(); // temporary for now
    }

    struct graph_node *r = (struct graph_node *) graph_p;
    memset(graph_p,0,size);
    graph_p += size;

    r->prev = NULL;
    r->next = NULL;
    r->size = size;

    return r;
  }
  
  inline tree_node *tree_node_alloc() {
    unsigned char *r = tree_p - sizeof(tree_node);

    if((tree_p - sizeof(tree_node)) <= graph_p) {
      throw std::bad_alloc(); // temporary for now
    }    

    tree_p -= sizeof(tree_node);
    tree_node* tp = (tree_node*) tree_p;
    tp->refcount = 1;
    return tp;
  }

  bool lookup(unsigned char const *key, unsigned int &id) {
    // identify containing bucket
    unsigned int bucket = nauty_graph_hashcode(key) % buckets.size();
    struct graph_node *node_p = buckets[bucket].next;

    // traverse bucket looking for match
    while(node_p != NULL) {
      unsigned char *key_p = (unsigned char *) node_p;
      key_p += sizeof(struct graph_node);
      if(nauty_graph_equals(key,key_p)) {
	// match made
	// set id
	id = node_p->gindex;
	// update hit count
	node_p->hit_count++;
	// move node to front of bucket
	remove_node(node_p);
	insert_node_after(node_p,&buckets[bucket]);
	// update hit count and we're done!	
	hits++;
	return true;
      }
      collisions++;
      node_p = node_p->next;
    }
    misses++;
    return false;    
  }

  void store(graph_node *gnode) {
    unsigned int bucket = nauty_graph_hashcode(NAUTY_GRAPH(gnode)) % buckets.size();
    insert_node_after(gnode,&buckets[bucket]);
  }  

  struct graph_node *next_node(struct graph_node *ptr) {
    unsigned char *p = (unsigned char *) ptr;
    p += ptr->size;
    return (struct graph_node *) p;
  }

  void insert_node_after(struct graph_node *new_node, struct graph_node *pos) {
    new_node->next = pos->next;
    new_node->prev = pos;
    pos->next = new_node;
    if(new_node->next != NULL) { new_node->next->prev = new_node; }
  }
  
  void remove_node(struct graph_node *node) {
    node->prev->next = node->next;
    if(node->next != NULL) {
      node->next->prev = node->prev;
    }
    node->next = NULL;
    node->prev = NULL;
  }

  void move_node(unsigned char *dst, struct graph_node *ptr) {
    struct graph_node *dstptr = (struct graph_node *) dst;
    ptr->prev->next = dstptr;
    if(ptr->next != NULL) {
      ptr->next->prev = dstptr;
    }
    memmove(dst,ptr,ptr->size);
  }

};

#endif
