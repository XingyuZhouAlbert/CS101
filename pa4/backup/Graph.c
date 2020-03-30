/* Xingyu Zhou
 * xzhou45@ucsc.edu
 * pa4
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
	int *discover;
	int *finish;
	int order;
	int size;
} GraphObj;


/*** Constructors-Destructors ***/

// Returns a new graph with everyting reset
// to an initial state
Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors = calloc(n+1, sizeof(List));
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->discover = calloc(n+1, sizeof(int));
	G->finish = calloc(n+1, sizeof(int));
	G->order = n;
	G->size = 0;
	// initialize a bunch of lists and list of ints
	for (int i = 0; i<=n; i++){
		G->neighbors[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
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
		free(G->discover);
		free(G->finish);
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
	return (G->parent[u]);
}


/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getDiscover() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE); 
	}
	if (u < 1 || u > getOrder(G)){
		printf("Graph Error: out of bounds!!\n"); 
		exit(EXIT_FAILURE);
	}
	return (G->discover[u]);
}

/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u){
	if (G == NULL){
		printf("Graph Error: calling getFinish() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE); 
	}
	if (u < 1 || u > getOrder(G)){
		printf("Graph Error: out of bounds!!\n"); 
		exit(EXIT_FAILURE);
	}
	return (G->finish[u]);
}

/*** Manipulation procedures ***/

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

// helper function for DFS().
// Based on the pseudo code in handout and the book
void Visit(Graph G, int u, int* time, List L){
	int next = 0;
	// Visiting the first undiscovered neighbours in adj list
	// Set the color tp grey 
	// Also increase the discover time by 1
	G->color[u] = GRAY;
	G->discover[u] = ++(*time);
	// Start at the beginning of the adj list
	moveFront(G->neighbors[u]);

	while(index(G->neighbors[u]) != -1){
		next = get(G->neighbors[u]);
		// Here just do almost the same as BFS for pa3
		// If the color is white call Visit again
		// If not then just skip it
		if(G->color[next] == WHITE){
			G->parent[next] = u;
			Visit(G, next, time, L);
		}
		moveNext(G->neighbors[u]);
	}
	// Set the color to black
	// when the vertex is finished
	G->color[u] = BLACK;
	G->finish[u] = ++(*time);
	// push to the stack.
	// last finished goes to top
	prepend(L,u);
}

/* Pre: length(S)==getOrder(G) */
// Following the pseudo code from handout
void DFS(Graph G, List S){
	if(G == NULL){
		printf("Graph Error: calling DFS() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE);
	}
	if(length(S) != getOrder(G)){
		printf("Error! Size is different! \n");
		exit(EXIT_FAILURE);
	} 
	// start by making all vertices white
	for(int i = 0; i <=getOrder(G); i++){
		G->color[i] = WHITE;
		G->parent[i] = NIL;
	}
	int time = 0;
	int current = 0;
	// start iterating through list
	moveFront(S);
	while (index(S) != -1){
		current = get(S);
		if(G->color[current] == WHITE){
			Visit(G, current, &time, S);
		}
		moveNext(S);
	}
	/* Forgot to delete the order that
	 * vertices being processed in the list
	 * They will get pushed in the list as well
	 * Using deleteBack because I used prepend().*/
	for(int j = 0; j<getOrder(G); j++){
		deleteBack(S);
	}
}


/* Other Functions */
// reverse all directions 
Graph transpose(Graph G){
	if(G == NULL){
		printf("Graph Error: calling traspose() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE);
	}	
	Graph GT = newGraph(getOrder(G));
	int reverse = 0;
	for (int i = 1; i<= getOrder(G); i++){
		moveFront(G->neighbors[i]);
		// Adding edges from back to front (or reversed)
		while(index(G->neighbors[i]) != -1){
			reverse = get(G->neighbors[i]);
			addArc(GT, reverse, i);
			moveNext(G->neighbors[i]);
		}
	}
	return (GT);
}


// Copies everything to a new Graph
Graph copyGraph(Graph G){
	if(G == NULL){
		printf("Graph Error: calling copyGraph() on NULL Graph reference\n"); 
		exit(EXIT_FAILURE);
	}
	Graph newG = newGraph(getOrder(G));
	//newG->order = getOrder(G);
	//newG->size = getSize(G);
	for (int i = 0; i<= getOrder(G); i++){
		moveFront(G->neighbors[i]);
		// Here basically what I do is
		// Copying everything into newG
		while(index(G->neighbors[i]) != -1){
			addArc(newG, i, get(G->neighbors[i]));
			moveNext(G->neighbors[i]);
		}
	}
	return(newG);	
}


void printGraph(FILE* out , Graph G){
	List L = NULL;
	if(G == NULL){
		printf("Graph Error: calling printGraph() on NULL Graph reference\n"); 
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