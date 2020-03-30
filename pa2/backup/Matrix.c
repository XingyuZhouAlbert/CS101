/* Xingyu Zhou
 * xzhou45@ucsc.edu
 * pa2
 * Matrix.c
 * This file contains the implementation of 
 * my Matrix ADT functions.
 */
//Testing command  valgrind --leak-check=full --show-leak-kinds=all -v MatrixClient
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "List.h"

// Structs--------------------------------------------------------
typedef struct EntryObj{
	int col;
	double data;
} EntryObj;


typedef struct MatrixObj{
	List *row;
	int numRows;
	int nnz;
} MatrixObj;

// private NodeObj type
typedef struct NodeObj{
   void* data;
   struct NodeObj* prev;
   struct NodeObj* next;
} NodeObj;

// private Node type
typedef struct NodeObj* Node;

//private ListObj tyoe
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

#define true 1
#define false 0


// Constructor/Deconstructors--------------------------------------

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
	Matrix M = malloc(sizeof(MatrixObj));
	M->numRows = n;
	M->nnz = 0;	
	//allocate memory for array of lists.
	//(n+1) since 0 index is included.
	M->row = malloc((n+1)*sizeof(List));
	//allocate memory for the lists in my array
	//set i = 1 to skip the index 0.
	for(int i = 1; i<=n; i++){
		M->row[i] = newList();
	}
	return(M);
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
	Matrix M = *pM;
	makeZero(M);
	if(pM!=NULL && *pM!=NULL) { 
		for(int i = 1; i<=M->numRows; i++){
			freeList(&M->row[i]);
		}
		free((*pM)->row);
		free(*pM);
		pM = NULL;
	}
}

Entry newEntry(int col, double data){
	Entry E = malloc(sizeof(EntryObj));
	E->col = col;
	E->data = data;
	return(E);
}

void freeEntry(Entry* pE){
	if(pE!=NULL && *pE!= NULL){
		free(*pE);
		pE = NULL;
	}
}
	

// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
	if( M == NULL){
		printf("Matrix Error: calling size() on NULL Matrix references\n");
		exit(EXIT_FAILURE);
	}
	return(M->numRows);
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
	if( M == NULL){
		printf("Matrix Error: calling NNZ() on NULL Matrix references\n");
		exit(EXIT_FAILURE);
	}
	return(M->nnz);	
}


// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Invalid Matrix\n");
		exit(EXIT_FAILURE);
	}
	int equal = 1;
	//size is different therefore the matrix is different
	if(size(A) != size(B)){
		equal = 0;
	}
	//if they have different nnz then they must be different.
	if(A->nnz != B->nnz){
		equal = 0;
	}
	//Exit the program when they dont match
	for(int i = 1; i<= size(A); i++){
		if(equal == 0){
			break;
		}
		moveFront(A->row[i]);
		moveFront(B->row[i]);
		//Make sure that the length of the list is always the same.
		equal = (length(A->row[i]) == length(B->row[i]));
		while(index(A->row[i])>=0 && equal){
			//comparing the actual data instead of the address.
			Entry P = (Entry)get(A->row[i]);
			Entry N = (Entry)get(B->row[i]);
			//equal will stay 1 as long as both matrices are the same
			equal = ((P->col == N->col) && (P->data == N->data));
			moveNext(A->row[i]);
			moveNext(B->row[i]);
		}
	}
	return equal;
}

// Helper functions-------------------------------------------------------
// vectorDot()
// returns a product of two lists so that I can put it into my product().
double vectorDot(List P, List Q){
	if(P == NULL || Q == NULL){
		printf("Error! Calling vectorDot on NULL list reference!\n");
		exit(EXIT_FAILURE);
	}
	double result = 0.0;
	//prepare for iteration
	moveFront(P);
	moveFront(Q);
	while(index(P) >=0 && index(Q) >= 0){
		//get the data in each list
		Entry PE = (Entry) get(P);
		Entry QE = (Entry) get(Q);
		//start the comparison.
		//1st case: PE->col is less than QE->col
		//then will increase the PE->col until they match
		if(PE->col < QE->col){
			moveNext(P);
		}
		//I did the same for QE->col as well.
		else if(QE->col < PE->col){
			moveNext(Q);
		}
		else{ //here when both cols match, multply and then put into result
			result += ((PE->data) * (QE->data)); 
			moveNext(Q);
			moveNext(P);
		}
	}
	return result;
}


// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M)
{
	List L;
	Entry E;
	//get the length of the array of lists
	for(int i = 1; i<=M->numRows; i++){
		L = M->row[i];
		moveFront(L);
		while(index(L) >= 0){
			E = (Entry) get(L);
			freeEntry(&E);
			moveNext(L);
		}
		clear(L);
	}
	M->nnz = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
	Entry curEntry;
	List L;
	if(M  == NULL){
		exit(EXIT_FAILURE);
	}
	if(i < 1 || size(M) < i){
		printf("Matrix Error: invalid row value\n");
		exit(EXIT_FAILURE);
	}
	if(j < 1 || size(M) < j){
		printf("Matrix Error: invalid column value\n");
		exit(EXIT_FAILURE);
	}
	L = M->row[i];
	curEntry = NULL;
	//get to the front of the current list and start iterating
	moveFront(L);
	while(index(L) >= 0){
		//get the data for current entry in the list.
		curEntry = (Entry) get(L);
		//comparing it with my inputed col.
		if(j <= curEntry->col){
			break;	
		}
		moveNext(L);
	}
	//if j is greater than every col or the List is empty
	//append the data. 
	if(index(L)<0 || get(L) == NULL){
		if(x != 0.0){
			append(L, newEntry(j,x));
			(M->nnz)++;
		}
	}
	//if j is less than it's next col, use insertBefore
	//to keep the order
	else if(j < curEntry->col){
		if(x != 0.0){
			insertBefore(L,newEntry(j,x));
			(M->nnz)++;
		}
	}
	//This is the last case, either swap the data if x is not 0;
	else {
		if(x != 0.0){
			curEntry->data = x;
		}
		// Or delete the current entry if x is 0;
		else{
			delete(L);
			(M->nnz)--;
		}
	}
} 



// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
	int test = size(A);
	if(A == NULL){
		printf("Warning! Calling copy on NULL matrix!\n");
		exit(EXIT_FAILURE);
	}
	//create a new matrix of the same size of A
	Matrix B = newMatrix(test);
	for(int i = 1; i<=size(A); i++){
		moveFront(A->row[i]);
		while(index(A->row[i])>=0){
			//create the entry that contains the data in A
			Entry AE = (Entry) get(A->row[i]);
			//copying them into new matrix
			changeEntry(B, i, AE->col, AE->data);
			moveNext(A->row[i]);
		}
	}
	return B;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
	if(A == NULL){
		printf("ERROR! CAlling transpose on NULL matrix!\n");
		exit(EXIT_FAILURE);
	}
	Matrix B = newMatrix(size(A));
	for(int i=1; i<=size(A); i++){
		moveFront(A->row[i]);
		while(index(A->row[i])>=0){
			Entry AE = (Entry) get(A->row[i]);
			//just simply swap the row and col
			//and you will get the transpose.
			changeEntry(B, AE->col, i, AE->data);
			moveNext(A->row[i]);
		}
	}
	return B;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
	if(A == NULL){
		printf("ERROR! CAlling transpose on NULL matrix!\n");
		exit(EXIT_FAILURE);
	}
	Matrix B = newMatrix(size(A));
	for(int i=1; i<=size(A); i++){
		moveFront(A->row[i]);
		//if x is zero then just simply return my new matrix
		if(x == 0){
			return B;
		}
		//when x is not zero
		else{
			while(index(A->row[i])>=0){
				Entry AE = (Entry) get(A->row[i]);
				changeEntry(B, i, AE->col, (x*(AE->data)));
				moveNext(A->row[i]);
			}
		}
	}
	return B;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("ERROR! Calling sum of NULL matrix!\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("ERROR! Sizes are different!\n");
		exit(EXIT_FAILURE);
	}
	//if they are the same then just use scalmult *2
	if(equals(A,B)){
		Matrix C = scalarMult(2.0,A);
		return C;
	}
	//both matrices are 0 matrices
	else if(A->nnz == 0 && B->nnz == 0){
		Matrix C = newMatrix(size(A));
		return C;
	}
	//One of them is 0 and one of them is not
	else if(A->nnz == 0 && B->nnz != 0){
		Matrix C = copy(B);
		return C;
	}else if(A->nnz != 0 && B->nnz == 0){
		Matrix C = copy(A);
		return C;
	}
	Matrix C = newMatrix(size(A));
	//start iterating through the list
	for(int i = 1; i<=size(A); i++){
		//prepare a new list to store the sum. 
		//I dont want to write another helper function
		//printf("You are in the loop\n");
		moveFront(A->row[i]);
		moveFront(B->row[i]);
		while(index(A->row[i])>=0 || index(B->row[i])>=0){
			//printf("HI\n");
			if(index(A->row[i]) >=0 && index(B->row[i]) >= 0){
				//printf("You are in the while loop\n");
				Entry AE = (Entry) get(A->row[i]);
				Entry BE = (Entry) get(B->row[i]);
				// if col A is greater than col B, append the small one first
				//and increase col B one time
				if(AE->col > BE->col){
					//printf("You are in AE>BE\n");
					append(C->row[i], newEntry(BE->col, BE->data));
					(C->nnz)++;
					moveNext(B->row[i]);
				//if col A is less than col B, do the other way around.
				}else if(AE->col < BE->col){
					//printf("You are in BE>AE\n");
					append(C->row[i], newEntry(AE->col, AE->data));
					(C->nnz)++;
					moveNext(A->row[i]);
				//both cols are the same so just append sum
				}else if(AE->col == BE->col){
					//printf("You are in BE = AE\n");
					if((AE->data + BE->data != 0)){
						append(C->row[i], newEntry(AE->col, ((AE->data)+(BE->data))));
						(C->nnz)++;
					}
					moveNext(A->row[i]);
					//printf("done a move\n");
					moveNext(B->row[i]);
					//printf("done b move\n");
				}
			// These two conditions kick in when say List A fall of the end of the list
			// while List B is still going. So just append whatever List B have to the new
			// list. Vice versa.
			}else if(index(A->row[i]) >= 0 && index(B->row[i]) == -1){
				//printf("You are in here at A >= 0\nn");
				Entry AE = (Entry) get(A->row[i]);
				append(C->row[i], newEntry(AE->col, AE->data));
				(C->nnz)++;
				moveNext(A->row[i]);
			}else if(index(A->row[i]) == -1 && index(B->row[i]) >=0){
				//printf("You are in here at B >=0\n");
				Entry BE = (Entry) get(B->row[i]);
				append(C->row[i], newEntry(BE->col, BE->data));
				(C->nnz)++;
				moveNext(B->row[i]);
			}

		}
	}
	return C;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("ERROR! Calling sum of NULL matrix!\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("ERROR! Sizes are different!\n");
		exit(EXIT_FAILURE);
	}
	if(equals(A,B)){
		Matrix C = newMatrix(size(A));
		return C;
	}
	//both matrices are 0 matrices
	else if(A->nnz == 0 && B->nnz == 0){
		Matrix C = newMatrix(size(A));
		return C;
	}
	//One of them is 0 and one of them is not
	else if(A->nnz == 0 && B->nnz != 0){
		Matrix C = scalarMult(-1.0,B);
		return C;
	}else if(A->nnz != 0 && B->nnz == 0){
		Matrix C = copy(A);
		return C;
	}
	Matrix C;
	B = scalarMult(-1.0, B);
	//printf("scalar_com\n");
	C = sum(A, B);
	freeMatrix(&B);
	return C;	
}


// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Error! Calling product on Null matrix");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("Error! Matrices are of different sizes!!!\n");
		exit(EXIT_FAILURE);
	}
	Matrix Mult = newMatrix(size(A));
	//transpose of matrix Mult
	Matrix TMult = transpose(B);
	for(int i = 1; i<=size(A); i++){
		for(int j=1;j<=size(A); j++){
			changeEntry(Mult, i, j, vectorDot(A->row[i], TMult->row[j]));
		}
	}
	freeMatrix(&TMult);
	return Mult;
}



// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
	if(M == NULL){
		printf("Error! Calling print on NULL matrix!\n");
		exit(EXIT_FAILURE);
	}
	//Only print when matrix has nnz
	if((M->nnz) > 0){		
		for(int i = 1; i<=size(M); i++){
			moveFront(M->row[i]);
			int print_row = true;
			//printf("here\n");
			while(index(M->row[i]) >= 0){
				//printf("here1\n");
				Entry curData = (Entry) get(M->row[i]);
				//avoid priting zero rows
				if(curData->data == 0) {} 
					else {
						//Make sure the row # only prints once per iteration
						if(print_row == true) {
						fprintf(out, "%d: ",i);
						print_row = false;
					}
					fprintf(out, "(%d, %.1f) ", curData->col, curData->data);
				}		
				moveNext(M->row[i]);
			}
			if(print_row == false) {
				fprintf(out, "\n");	
			}	
		}
	}
}



