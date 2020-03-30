/* Xingyu Zhou
 * xzhou45@ucsc.edu
 * pa3
 * This file contains the inplementation of
 * all my Graph ADT functions.
 */

// Test for memleak valgrind --leak-check=full --show-leak-kinds=all -v GraphClient


#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"


/* Some colors */ 
#define WHITE 0
#define GRAY 1
#define BLACK 2


typedef struct GraphObj{
	List *neighbors;
	int *color;
	int *parent;
	int *distance;
	int order;
	int size;
	int source;
} GraphObj;



/*** Constructors-Destructors ***/

// Returns a new graph with everyting reset
// to an initial state
Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors = calloc(n+1, sizeof(List));
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->distance = calloc(n+1, sizeof(int));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	// initialize a bunch of lists and list of ints
	for (int i = 0; i<=n; i++){
		G->neighbors[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	return (G);
}


// freeGraph()
// Frees heap memory pointed to by *pG, sets *pG to NULL.
// Private.
// Based on freeMatrix();
void freeGraph(Graph* pG){
	Graph G = *pG;
	if(pG != NULL && *pG != NULL){
		for (int i = 0; i<=getOrder(*pG); i++){
			freeList(&G->neighbors[i]);
		}
		free(G->neighbors);
		free(G->parent);
		free(G->distance);
		free(G->color);

		free(*pG);
		*pG = NULL;
	}
}


/*** Access functions ***/

// order means the # of vertices
int getOrder(Graph G){
	if (G == NULL){
		printf("Graph Error: calling getOrder() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE); 
	}
	return (G->order);
}

// size means the # of edges
int getSize(Graph G){
	if (G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE); 
	}
	return (G->size);
}

// Returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called.
int getSource(Graph G){
	if (G == NULL){
		printf("Graph Error: calling getSource() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE); 
	}
	return (G->source);
}

// Return the parent of vertex u in the Breadth-
// First tree created by BFS(), or NIL if BFS() has not yet been called.
int getParent(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getParent() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE); 
	}
	if (u < 1 || u > getOrder(G)){
		printf("Graph Error: out of bounds!!\n"); 
		exit(EXIT_FAILURE);
	}
	return G->parent[u];
}

// Function getDist() returns the
// distance from the most recent BFS source to vertex u, 
// or INF if BFS() has not yet been called.
int getDist(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getDist() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE); 
	}
	if (u < 1 || u > getOrder(G)){
		printf("Graph Error: out of bounds!!\n"); 
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL){
		return INF;
	}
	return G->distance[u];
}

// Function getPath() appends to the List L the vertices of a shortest path in G from source to u, 
// or appends to L the value NIL if no such path exists. 
// getPath() has the precondition getSource(G)!=NIL, so BFS() must
// be called before getPath().
void getPath(List L, Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getPath() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE); 
	}
	if (u < 1 || u > getOrder(G)){
		printf("Graph Error: out of bounds!!\n"); 
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL){
		printf("Graph Error: Calling getPath() on NIL\n");
	}

	// shortest path is the source
	if(u == G->source){
		append(L,G->source);
	}
	// no path exists
	else if(G->parent[u] == NIL){
		append(L,NIL);
	}
	// path exists
	else{
		getPath(L, G, G->parent[u]);
		append(L,u);
	}
}


/*** Manipulation procedures ***/
// Function makeNull() deletes all edges of G, restoring it to its original
// (no edge) state.
// similiar to newGraph().
void makeNull(Graph G){
	if (G == NULL){
		printf("Graph Error: calling makeNull() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE); 
	}
	// reset everything except # of vertices
	for(int i = 0; i<=getOrder(G); i++){
		clear(G->neighbors[i]);
		G->parent[i] = NIL;
		G->color[i] = WHITE;
		G->distance[i] = INF;
	}
	G->size = 0;
	G->source = NIL;
}

// addArc() inserts a new directed edge
// from u to v, i.e. v is added to the adjacency List of u 
// (but not u to the adjacency List of v).
void addArc(Graph G, int u, int v){
	if (G == NULL){
		printf("Graph Error: calling addArc() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE); 
	}
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
		printf("Graph Error: addArc() out of bounds!\n");
		exit(EXIT_FAILURE); 
	}
	// get to the front of the adj list of u
	moveFront(G->neighbors[u]);
	// keep walking through the list
	while(index(G->neighbors[u]) != -1 && v > get(G->neighbors[u])){
		moveNext(G->neighbors[u]);
	}

	// If v is greater than all neighbours in u, add it to the end
	if(index(G->neighbors[u]) == -1){
		append(G->neighbors[u], v);
	}
	// else just use insertBefore()
	else {
		insertBefore(G->neighbors[u], v);
	}
	G->size ++;
}


// addEdge() inserts a new edge
// joining u to v, i.e. u is added to the adjacency List of v, 
// and v to the adjacency List of u. Your program is
// required to maintain these lists in sorted order by increasing labels.
void addEdge(Graph G, int u, int v){
	if (G == NULL){
		printf("Graph Error: calling addEdge() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE); 
	}
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
		printf("Graph Error: addEdge() out of bounds!\n");
		exit(EXIT_FAILURE); 
	}
	// This can be achieved by calling addArc twice.
	// Once on u to v and once on v to u
	addArc(G,u,v);
	addArc(G,v,u);
	// reduce the size by 1 since I'm actually increase the
	// # of edges twice by calling addArc() twice.
	G->size --;
}


// Function BFS() runs the BFS algorithm on the Graph G with source s, 
// setting the color, distance, parent, and source fields of G accordingly.
// Based on the pseudo code provided on handouts, as well as some practice problems.
void BFS(Graph G, int s){
	if (G == NULL){
		printf("Graph Error: calling BFS() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE); 
	}
	if(s<1 || s>getOrder(G)){
		printf("Graph Error: BFS() out of bounds!\n");
	}
	int current = 0;
	int next = 0;
	// Make the source to be s
	G->source = s;
	List Queue = newList();
	// Bring everything to its initial condition
	for (int i = 0; i<=getOrder(G); i++){
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	// Now s is discovered, set color to grey, distant to 0
	// parent to nil. Push to Queue
	G->color[s] = GRAY;
	G->parent[s] = NIL;
	G->distance[s] = 0;
	append(Queue, s);

	// check the Queue to see if it's empty.
	// if not, process the first thing in it by
	// FIFO
	while(length(Queue) != 0){
		moveFront(Queue);
		// Take the first element in Queue.
		// Pops it out.
		current = get(Queue);
		deleteFront(Queue);
		// Process its neighbors.
		moveFront(G->neighbors[current]);
		while(index(G->neighbors[current]) != -1){
			next = get(G->neighbors[current]);
			// Here just checking whether the next vertex has been discovered
			// If it is then just skip, if not, set the color to gray
			// set parent to current, and distant to distant[parent] + 1
			// Then append it to the Queue
			if(G->color[next] == WHITE){
				G->color[next] = GRAY;
				G->parent[next] = current;
				G->distance[next] = G->distance[current] + 1;
				append(Queue,next);
			}
			// Move to the next vertex
			moveNext(G->neighbors[current]);
		}
		// If the current adj list is finished
		// set the color to black.
		G->color[current] = BLACK;
	}
	freeList(&Queue);
}




/*** Other operations ***/
// function printGraph() prints the adjacency list
// representation of G to the file pointed to by out.
// It's basically printList()
void printGraph(FILE* out, Graph G){
	List L = NULL;
	if(G == NULL){
		printf("Graph Error: calling printfGraph on NULL graph references!\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i<=getOrder(G);i++){
		L = (List)G->neighbors[i];
		fprintf(out, "%d: ", i);
		printList(out,L);
		fprintf(out, "\n");
	}
	L = NULL;
}



















