/* Xingyu Zhou
 * xzhou45@ucsc.edu
 * pa4
 * GraphTest.c
 * This is the testfile created by myself
 * to if my graph.c is working correctly
 */



#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(){
	printf("Welcome to the DFS() test file!\n");
	int order = 8;
	Graph G = newGraph(order);
	Graph A = NULL, B = NULL;
	List S = newList();

	for (int i = 1; i<= order; i++){
		append(S,i);
	}

	/* Setting up the Graph */
   	addArc(G, 1, 2);
   	addArc(G, 2, 3);
   	addArc(G, 2, 5);
   	addArc(G, 2, 6);
   	addArc(G, 3, 4);
   	addArc(G, 3, 7);
   	addArc(G, 4, 3);
   	addArc(G, 4, 8);
   	addArc(G, 5, 1);
   	addArc(G, 5, 6);
   	addArc(G, 6, 7);
   	addArc(G, 7, 6);
   	addArc(G, 7, 8);
   	addArc(G, 8, 8);
   	printf("The graph G contains %d vertices and %d egdes\n",order, getSize(G));
   	printGraph(stdout,G);
   	printf("\n");

   	/* Tesing if the copyGraph() and transpose is working properly */
   	A = transpose(G);
   	B = copyGraph(G);

   	printf("The transposed graph(A) is:\n");
   	printGraph(stdout,A);
   	printf("\n");
   	
   	printf("Copying graph G to B, they should be the same:\n");
   	printGraph(stdout,B);
   	printf("Order of the copied graph B is %d, size of graph B is %d\n",getOrder(B), getSize(B));
   	printf("\n");
   	/* Here just playing with the code, test to see if the transpose
   	 * of a transpose will be the same as the original one */
   	printf("Transpose of a transposed graph(A) is:\n");
   	printGraph(stdout,transpose(A));

   	/* Used the code in GraphClient.c becuase I think it did a pretty good job
   	 * testing DFS and the getDiscover() getFinish() function */
   	DFS(G, S);
   	printf("\n");
   	printf("1st call to DFS:\n");
   	printf("x:  d  f  p\n");
   	for(int i = 1; i<=order; i++){
   		printf("%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));	
   	}

   	printf("\n");

   	printf("Here's what you have in the List after DFS:\n");
   	printList(stdout, S);
   	printf("\n");

   	DFS(A,S);
   	printf("\n");
   	printf("2nd call to DFS:\n");
   	printf("x:  d  f  p\n");
   	for(int i = 1; i<=order; i++){
   		printf("%d: %2d %2d %2d\n", i, getDiscover(A, i), getFinish(A, i), getParent(A, i));	
   	}
   	printf("\n");

   	printf("Here's what you have in the List after second DFS:\n");
   	printList(stdout, S);
   	printf("\n");
   	/* Based on my own calculation, there are 4 SCCs in this graph
   	 * They should begin with 1, 3, 7, 8. I'll print out their parents
   	 * and if the parents are 0(NIL), then it means they are SCC*/
   	printf("The parent of 1 should be NIL: %d\n",getParent(A,1));
   	printf("The parent of 3 should be NIL: %d\n",getParent(A,3));
   	printf("The parent of 7 should be NIL: %d\n",getParent(A,7));
   	printf("The parent of 8 should be NIL: %d\n",getParent(A,8));

   	/* Here the four SCC should be 152 34 67 8 but I'll only print out
   	 * the parent of 5 and 2 to verify that it's correct*/
   	printf("The parent of 5 should be 1: %d\n", getParent(A,5));
   	printf("The parent of 2 should be 5: %d\n", getParent(A,2));


   	printf("The testing is over! You passed!\n");

   	freeGraph(&G);
   	freeGraph(&A);
   	freeGraph(&B);
   	freeList(&S);
   	return (EXIT_SUCCESS);

}
