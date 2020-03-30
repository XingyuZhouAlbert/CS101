/*********************************************************************************
* Xingyu Zhou, xzhou45
* 2019 Summer CMPS101 PA4
* FindComponents.c
* Main program for PA4
* Based partially on FindPath.c
*********************************************************************************/

// Test for memleak valgrind --leak-check=full --show-leak-kinds=all -v GraphClient


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Graph.h"

#define MAX_LEN 255

int main(int argc, char * argv[]){
	FILE *in, *out;
	char line[MAX_LEN];
	int list = 0;
	int neighbours = 0;
	int order = 0;
	int scc = 0;
	// check command line for correct number of arguments
	if( argc != 3 ){
		fprintf(stderr,"Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// open files for reading and writing
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if( in==NULL ){
		fprintf(stderr,"Unable to open file %s for reading\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if( out==NULL ){
		fprintf(stderr,"Unable to open file %s for writing\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	// extract the order of the graph
	fgets(line, MAX_LEN, in);
	sscanf(line, "%d", &order);

	// Construct a new graph and new list
	Graph G = newGraph(order);
	List L = newList();
	List tSort = newList();

	// Put vertices into this new list
	for(int i = 1; i<=order; i++){
		append(L,i);
	}
	// Read following data until the break
	// This is the adj list part 
	while (fgets(line, MAX_LEN, in) != NULL){
		sscanf(line, "%d %d", &list, &neighbours);
		//reach the first dummy line
		if(list == 0 && neighbours == 0) break;
		addArc(G,list,neighbours);
	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out,"\n");

	/* Run DFS(G) and DFS(Gt)
	 * Inside the second call to DFS(), process vertices
	 * in order of decreasing finish times from the first
	 * call to DFS*/
	DFS(G,L);
	Graph tG = transpose(G);
	DFS(tG,L);

	// Now it's time to find the SCC.
	// First find out the number of scc
	for (int j = 1; j<= getOrder(tG); j++){
		if(getParent(tG, j) == NIL){
			scc ++;
		}
	}
	fprintf(out,"G contains %d strongly connected components:\n", scc);
	// Sort the components topologically
	// Start from the end of the list since it's a transpose
	moveBack(L);
	int numComp = 0;
	while(index(L) != -1){
		/* if the parent is NIL, it means the program
		 * reaches the head of the scc. Here just prepend
		 * ,clear the list and move to the next*/
		if(getParent(tG,get(L)) == NIL){
			numComp ++;
			fprintf(out, "Component %d: ",numComp);
			prepend(tSort,get(L));
			printList(out,tSort);
			fprintf(out,"\n");
			// clear the remaining scc
			// so that it's ready for the next
			clear(tSort);
			movePrev(L);
		}	
		/* Adding to the list while the parent is not NIL*/
		else {
			// Use prepend because it's being printed out backwards
			// i.e instead of 2,5,1, i need 1,5,2
			prepend(tSort,get(L));
			movePrev(L);
		}
	}
	freeGraph(&G);
	freeGraph(&tG);
	freeList(&L);
	freeList(&tSort);

	fclose(in);
	fclose(out);
	return(EXIT_SUCCESS);

}