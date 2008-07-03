#ifndef TUTTE_HPP
#define TUTTE_HPP

/* This is the core algorithm for the tutte computation
 * it reduces a graph to two smaller graphs using a delete operation
 * for one, and a contract operation for the other.
 *
 * The algorithm also uses a number of tricks to prune the computation
 * space.  These include: eliminating small graphs using optimised, 
 * hand-coded decision procedures; storing previously seen graphs
 * in a cache; and, dynamically monitoring the "treeness" of the graph.
 */
template<class G, class P>
P tutte(G &graph, unsigned int mid) { 
  if(current_timeout <= 0) { return P(X(0)); }
  if(status_flag) { print_status(); }
  num_steps++;

  // === 1. APPLY SIMPLIFICATIONS ===

  // P RF = reduce<G,P>(graph);
  P RF = Y(reduce_loops(graph));

  // === 2. CHECK IN CACHE ===

  unsigned char *key = NULL;
  if(graph.num_vertices() >= small_graph_threshold && !graph.is_multitree()) {      
    key = graph_key(graph); 
    unsigned int match_id;
    P r;
    if(cache.lookup(key,r,match_id)) { 
      if(write_tree) { write_tree_match(mid,match_id,graph,cout); }
      delete [] key; // free space used by key
      return r * RF;
    }
  }

  P poly;

  // === 3. CHECK FOR ARTICULATIONS, DISCONNECTS AND/OR TREES ===

  if(reduce_multicycles && graph.is_multicycle()) {
    num_cycles++;
    poly = reduce_cycle<G,P>(X(1),graph);
    if(write_tree) { write_tree_leaf(mid,graph,cout); }
  } else if(!graph.is_biconnected()) {
    vector<G> biconnects;
    G copyg(graph);
    graph.extract_biconnected_components(biconnects);
    poly = reduce_tree<G,P>(X(1),graph);
    if(graph.is_multitree()) { num_trees++; }
    if(biconnects.size() > 1) { num_disbicomps++; }
    // figure out how many tree ids I need
    unsigned int tid(tree_id);
    tree_id += biconnects.size();
    if(biconnects.size() > 0 && write_tree) { write_tree_nonleaf(mid,tid,tree_id-tid,copyg,cout); }
    else if(write_tree) { write_tree_leaf(mid,graph,cout); }
    // now, actually do the computation
    for(typename vector<G>::iterator i(biconnects.begin());i!=biconnects.end();++i){
      num_bicomps++;
      if(i->is_multicycle()) {
	// this is actually a cycle!
	num_cycles++;
	poly *= reduce_cycle<G,P>(X(1),*i);
	if(write_tree) { write_tree_leaf(tid++,*i,cout); }
      } else {
	poly *= tutte<G,P>(*i,tid++);      
      }
    }
  } else {

    // TREE OUTPUT STUFF
    unsigned int lid = tree_id;
    unsigned int rid = tree_id+1;
    tree_id = tree_id + 2; // allocate id's now so I know them!
    if(write_tree) { write_tree_nonleaf(mid,lid,2,graph,cout); }
    
    // === 4. PERFORM DELETE / CONTRACT ===
    
    G g2(graph); 
    line_t line = select_line(graph);

    // now, delete/contract on the line's endpoints
    graph.remove_line(line);
    g2.contract_line(line);
    // recursively compute the polynomial   
    poly = (tutte<G,P>(graph, lid) * FP<G,P>(line)) + (tutte<G,P>(g2, rid) * LP<G,P>(line));
  }

  // Finally, save computed polynomial
  if(key != NULL) {
    // there is, strictly speaking, a bug with using mid
    // here, since the graph being stored is not the same as that
    // at the beginning.
    cache.store(key,poly,mid);
    delete [] key;  // free space used by key
  }    

  return poly * RF;
}

#endif
