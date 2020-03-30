/* Xingyu Zhou
 * xzhou45@ucsc.edu
 * pa2
 Sparse.c
 * This is the main function for Matrix Calculator
 * Calls basically all Matrix ADT functions and print the outputs
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Matrix.h"

#define MAX_LEN 255
int main(int argc, char * argv[]){
	FILE *in, *out;
	int n, nnzA, nnzB;
	char line[MAX_LEN];		
	int row, col;
	double val;
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
	//Read the first line of the input file, get the size, nnzA and nnzB
	fgets(line, MAX_LEN, in);
	sscanf(line, "%d %d %d", &n, &nnzA, &nnzB);
	Matrix A = newMatrix(n);
	Matrix B = newMatrix(n);
	Matrix D,E,F,G,H,I,J,K;
	//Continue reading data for the matrix A
	//And fill it up.
	//Skip the blank line 
	fgets(line,MAX_LEN, in);
	for(int i = 0; i< nnzA; i++){
		fgets(line,MAX_LEN, in);
		sscanf(line, "%d %d %lf", &row, &col, &val);
		changeEntry(A, row, col, val);
		}
	//read data for matrix B
	//And fill it up
	//Skip the blank line
	fgets(line,MAX_LEN, in);
	for(int i = 0; i<nnzB; i++){
		fgets(line,MAX_LEN, in);
		sscanf(line, "%d %d %lf", &row, &col, &val);
		changeEntry(B, row, col, val);
	}

	//printf Matrices
	fprintf(out,"A has %d non-zero entries:\n", nnzA);
	printMatrix(out, A);
	fprintf(out, "\n");

	fprintf(out,"B has %d non-zero entries:\n", nnzB);
	printMatrix(out, B);
	fprintf(out, "\n");

	//ScalarMult()
	fprintf(out, "(1.5)*A =\n");	
	D = scalarMult(1.5, A);
	printMatrix(out, D);
	fprintf(out, "\n");

	//Sum(A+B)
	fprintf(out, "A+B =\n");
	E = sum(A,B);
	printMatrix(out, E);
	fprintf(out, "\n");

	//Sum(A+A)
	fprintf(out, "A+A =\n");
	F = sum(A,A);
	printMatrix(out,F);
	fprintf(out, "\n");


	//diff(B-A)
	fprintf(out, "B-A =\n");
	G = diff(B,A);
	printMatrix(out,G);
	fprintf(out, "\n");


	//diff(A-A)
	fprintf(out, "A-A =\n");
	H = diff(A,A);
	printMatrix(out,H);
	fprintf(out, "\n");


	//transpose(A)
	fprintf(out, "Transpose(A) =\n");
	I = transpose(A);
	printMatrix(out,I);
	fprintf(out, "\n");

	//product(A*B)
	fprintf(out, "A*B =\n");
	J = product(A,B);
	printMatrix(out,J);
	fprintf(out, "\n");

	//product(B*B)
	fprintf(out, "B*B =\n");
	K = product(B,B);
	printMatrix(out,K);
	fprintf(out, "\n");


	fclose(in);
	fclose(out);
	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I); 
    freeMatrix(&J);
    freeMatrix(&K);
	return(EXIT_SUCCESS);

}







