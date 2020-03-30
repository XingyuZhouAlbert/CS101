/* Xingyu Zhou
 * xzhou45@ucsc.edu
 * pa3
 * GraphTest.c	
 * This is a test file written by myself
 * to test the functionality of my Graph ADT
 */




#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"



int main(){
	int passed = 0;
	int order = 6;
	Graph G = newGraph(order);

	// Here just testng to see if the addEdge()
	// is working properly
	addEdge(G,1,3);
	addEdge(G,1,2); 
	addEdge(G,2,3);
	addEdge(G,3,1);
	addEdge(G,2,4);
	addEdge(G,2,5);
	addEdge(G,5,6);

	printf("Here's what you get:\n");
	printGraph(stdout, G);

	// The total number of edges should be 7 now
	if(getSize(G) == 7){
		passed ++;
	}

	if(getOrder(G) == 6){
		passed ++;
	}

	// Parent of 1 should be Nil and parent of 3 should also be NIL.
	// since BFS has not been called
	if(getParent(G,1) == NIL && getParent(G,3) == NIL){
		passed ++;
	}
	if (passed == 3) printf("Passed: addEdge(), getSize(), getOrder()\n");

	// Run BFS with 1 as source
	BFS(G,1);
	// The distance from 1 to 6 should be 3
	if(getDist(G,6) == 3) passed ++;
	List L = newList();
	// I'll print out the path, which would be 
	// 1, 2, 5, 6
	getPath(L,G,6);
	printf("Path from 1 to 6 is: ");
	printList(stdout,L);
	printf("\n");

	// determin the distance of selfloop
	getDist(G,1);
	if(getDist(G,1) == 0) passed ++;

	// Now I can test getParent()
	// parent of 3 should be 1, parent of 6 should be 5
	if(getParent(G,3) == 1 && getParent(G,6) == 5) passed ++;

	// Test if getSource() is working. Source should be 1
	if(getSource(G) == 1) passed ++;
	if(passed == 7) printf("Passed: getParent(), getDist(), getPath(), getSource()\n");


	// Use makeNull() the edge should be 0
	makeNull(G);
	if(getSize(G) == 0) passed ++;



	printf("Total of %d/8 tests passed\n", passed);
	printf("You have passed all tests\n");
	freeList(&L);
	freeGraph(&G);
	return (EXIT_SUCCESS);






}