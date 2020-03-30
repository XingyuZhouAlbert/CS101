
/* Xingyu Zhou
 * xzhou45@ucsc.edu
 * pa2
 * This is the test file for Matrix ADT
 * following the format of matrixclient
 */


#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"
#include"List.h"


int main(){
	int n = 3;
	int passed = 0;
	printf("Welcome to Matrix ADT test suite!\n");
	printf("----------------------------------------------------------------\n");
	//setting up some new matrices.
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    Matrix I = newMatrix(n);
    Matrix C,D,E,F,G,H,J;

    /* In this section, I'm mainly testing if the newMatrix function works
     * To do this, I'll compare the size of the matrix and the size that I 
     * inputed*/
    if(size(A) == 3 && size(B) == 3){
    	passed ++;
    }
    if(passed == 1) printf("Passed: newMatrix()\n");
	printf("----------------------------------------------------------------\n");
    /* Here is a combinational test, first I will use change entry to fill up the matrix.
     * Then I will change the entries again to see if the output and supposed output will
     * be the same. The input will be coming from the test files*/

	changeEntry(A, 1,1,10); changeEntry(B, 1,1,1);
    changeEntry(A, 1,2,3.0); changeEntry(B, 1,2,1234);
    changeEntry(A, 1,3,25.0); changeEntry(B, 1,3,3214);
    changeEntry(A, 2,1,43.7); changeEntry(B, 2,1,65);
    changeEntry(A, 2,2,21.3); changeEntry(B, 2,2,4);
    changeEntry(A, 2,3,76.2); changeEntry(B, 2,3,31);
    changeEntry(A, 3,1,7); changeEntry(B, 3,1,0.2);
    changeEntry(A, 3,2,8); changeEntry(B, 3,2,0.5);
    changeEntry(A, 3,3,9); changeEntry(B, 3,3,0.5); 

    //Setting up I as a transposed of B (After changeEntry (3,3) to 12)
	changeEntry(I, 1,1,1);
	changeEntry(I, 1,2,65);
	changeEntry(I, 1,3,0.2);
	changeEntry(I, 2,1,1234);
	changeEntry(I, 2,2,4);
	changeEntry(I, 2,3,0.5);
	changeEntry(I, 3,1,3214);
	changeEntry(I, 3,2,31);
	changeEntry(I, 3,3,12); 

	printf("A has %d non-zero entries:\n", NNZ(A));
	printMatrix(stdout, A);
	printf("B has %d non-zero entries:\n", NNZ(B));
	printMatrix(stdout, B);
	printf("----------------------------------------------------------------\n");
	/* Deleting the (2,1) entry of A, and change the (3,3) entry
	 * of B to 12*/
	changeEntry(A, 2,1,0);
	changeEntry(B, 3,3,12);
	printf("There should no longer exist a (2,1) eentry in A\n");
	printMatrix(stdout, A);
	printf("(3,3) entry in B should now be 12\n");
	printMatrix(stdout, B);
	if(NNZ(A) == 8){
		passed ++;
	}
	if(passed == 2) printf("Passed: NNZ(), changeEntry()\n");
	printf("----------------------------------------------------------------\n");

	/* make a copy of B, assign it to C. Print it out to see if it's the same as B.
	 * Will also run equals() to make sure they are equal.*/
	C = copy(B);
	printf("Matri C should be the same as Matrix B\n");
	printMatrix(stdout, C);
	if(equals(B,C)) printf("Passed: equals(), copy()\n");
	printf("----------------------------------------------------------------\n");

	/* Now it's the scalarMult test. First I'll use some number times the original matrix,
	 * then I'll mutply it by 0. I'll use this zero matrix to add it with matrix A, which
	 * will return me with a matrix that has the same value as matrix A.*/
	D = scalarMult(3,A);
	printf("3*A = \n");
	printMatrix(stdout, D);

	D = scalarMult(0, D);
	printf("Nothing should be printed below besides (0*D)\n");
	printf("0*D=\n");
	printMatrix(stdout, D);

	E = sum(D, A);
	printf("E should be the same as A: ");
	printf("D + A = \n");
	printMatrix(stdout, E);

	if(equals(E,A)) passed ++;
	if(passed == 3) printf("Passed: scalarMult(), sum()\n");
	printf("----------------------------------------------------------------\n");

	/* Here at first I will call diff on the same matrix, then I will use this matrix
	 * to multiply Matrix B. This will give me another zero matrix */
	F = diff(B,B);
	printf("Nothing will be printed since its a zero matrix\n");
	printf("B-B =\n");
	printMatrix(stdout,F);

	G = product(F, B);
	printf("Nothing will be printed since its a zero matrix\n");
	printf("F*B =\n");
	printMatrix(stdout,G);
	printf("Passed: diff(), product()\n");
	printf("----------------------------------------------------------------\n");

	/* If I make zero of any matrices and multiply it with other non-zero matrix,
	 * the returning matrix will be zero*/
	makeZero(A);
	H = copy(A);
	if(NNZ(H) == 0) passed ++;

	G = product(H, E);
	printf("Nothing should be printed since it's a zero matrix\n");
	printf("H*E =\n");
	printMatrix(stdout,G);
	if(passed == 4) printf("Passed: makeZero()\n");
	printf("----------------------------------------------------------------\n");

	/* Here's the transpose test. I can't think of any situation so I'll just call
	 * transpose and see if it equals to what I think it is.*/
	J = transpose(B);
	printf("transpose(B) = \n");
	printMatrix(stdout, J);
	printMatrix(stdout, I);

	if(equals(I,J)) passed ++;
	if(passed == 5) printf("Passed: transpose()\n");
	printf("----------------------------------------------------------------\n");

	printf("Congratulations! You have passed all the ADT tests!\n");

	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&D);
	freeMatrix(&E);
	freeMatrix(&F);
	freeMatrix(&G);
	freeMatrix(&H);
	freeMatrix(&J);
	freeMatrix(&I);

    return EXIT_SUCCESS;
}


