/* Xingyu Zhou
 * xzhou45@ucsc.edu
 * pa3
 * This in the main function for PA3
 * It will read the input file, sort it
 * and print it out.
 * Based on Sparse.c 
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Graph.h"


#define MAX_LEN 255

int main(int argc, char * argv[]){
	FILE *in, *out;
	char line[MAX_LEN];
	int order = 0;
	int list = 0;
	int neighbours = 0;
	int start = 0;
	int end = 0;
	int distance = 0;
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

	// Read following data until the first break
	// This is the adj list part 
	while (fgets(line, MAX_LEN, in) != NULL){
		sscanf(line, "%d %d", &list, &neighbours);
		//reach the first dummy line
		if(list == 0 && neighbours == 0) break;
		addEdge(G,list,neighbours);
	}
	printGraph(out, G);
	// Read the second part of the data
	// Find path part
	while (fgets(line, MAX_LEN, in) != NULL){
		sscanf(line, "%d %d", &start, &end);
		if(start == 0 && end == 0) break;
		BFS(G, start);
		getPath(L, G, end);
		distance = getDist(G, end);
		// a path is found
		if(distance != INF){
			fprintf(out, "\nThe distance from %d to %d is %d\n", start, end, distance);
			fprintf(out, "A shortest %d-%d path is: ", start, end);
			printList(out, L);
			fprintf(out,"\n");
		}
		else{ // No path is found
			fprintf(out, "\nThe distance from %d to %d is infinity\n", start, end);
			fprintf(out, "No %d-%d path exists\n", start, end);
		}
		clear(L);
	}
	freeGraph(&G);
	freeList(&L);
	fclose(in);
	fclose(out);
	return(EXIT_SUCCESS);
}