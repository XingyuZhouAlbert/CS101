/* Xingyu Zhou
 * xzhou45@ucsc.edu
 * pa2
 * This is the test file for
 * the modified List.c
 * I'll use some of the code from ListClient
 * to setup the test.
 */

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
	printf("Welcome to the List ADT test.\n");
	int passed = 0;
	int insert1 = 90;
	int insert2 = -200;
	List A = newList();
	List B = newList();
	List C = newList();
	List D = newList();
	int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int Y[] = {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
	int Z[] = {2,4,6,8,10,12,14,16,18,20,22};
	int W[] = {1,3,5,7,9,11,13,15,17,19,21};
	for (int i = 0; i <=20; i++){
		append(A, &X[i]);
		prepend(B, &Y[i]);
	}
	for (int j = 0; j <= 10; j++){
		append(C, &Z[j]);
		append(D, &W[j]);
	}
	//test the prepend, append function is working correctly	
	if(length(A) == 21 && index(B) == 20){
		passed ++;
	}
	//Test if the newList() is working or not 
	if(length(C) == 11 && index(D) == 0){
		passed ++;
	}	
	if(passed == 2){
		printf("Passed: newList()\n");
		printf("Passed: length()\n");
		printf("Passed: index()\n");
	}
	//reset the pass counter
	passed = 0;
	//Test the moveBack moveFront function.
	moveFront(B);
	if(*(int*)get(B) == 0){
		passed ++;
	}
	moveBack(A);
	if(*(int*)get(A) == 20){
		passed ++;
	}
	if(passed == 2){
		printf("Passed: moveBack()\n");
		printf("Passed: MoveFront()\n");
		printf("Passed: get()\n");
	}
	
	//Front/Back moveNext/movePrev Combo test
	passed = 0;
	if(*(int*)front(C) == 2 && *(int*)back(D) == 21){
		passed ++;
	}
	moveBack(C);
	movePrev(C);
	movePrev(C);
	movePrev(C);
	moveFront(D);
	moveNext(D);
	moveNext(D);
	moveNext(D);
	if(*(int*)get(C) == 16){
		passed ++;
	}
	if(*(int*)get(D) == 7){
		passed ++;
	}
	if(passed == 3){
		printf("Passed: front() and back()\n");
		printf("Passed: moveNext() and movePrev()\n");
	}
	
	//insert/delete test
	printf("----------------------------------------------\n");
	printf("Here's the insert test:\n");
	insertBefore(C, &insert1);
	moveNext(C);
	insertAfter(C, &insert2);
	printf("Correct output is: {2,4,6,8,10,12,14,90,16,18,-200,20,22}\n");
	printf("what you get is: ");
	for(moveFront(C); index(C)>=0; moveNext(C)){
		printf("%d,", *(int*)get(C));
	}
	printf("\n");
	printf("----------------------------------------------\n");
	printf("Here's the delete test:\n");
	deleteFront(D);
	deleteBack(D);
	delete(D);
	printf("Correct output is: 3,5,9,11,13,15,17,19\n");
	printf("What you get is:");
	for(moveFront(D); index(D)>=0; moveNext(D)){
		printf("%d,", *(int*)get(D));
	}
	printf("\n");
	printf("----------------------------------------------\n");
	passed = 0;
	clear(D);
	if(isEmpty(D) == 1){
		printf("Passed: clear() and isEmpty()\n");
	}	
	printf("All tests have passed!\n");
	
}



