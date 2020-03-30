/*********************************************************************************
* Xingyu Zhou, xzhou45
* 2019 Summer CMPS101 PA1
* Lex.c
* Main program for PA1
* Based on FileIO.c
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){
	int n, countline = 0;
	FILE *in, *out; 
	char line[MAX_LEN];
	List sort = newList();


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

	//Count the line of the input file
	while(fgets(line, MAX_LEN, in) != NULL){
		countline++;
	}

	//reset the pointer to the beginning
	fseek(in, 0, SEEK_SET);

	//create an array to store the files.
	char Array[countline][MAX_LEN];
	//reseting my n to 0 again because the system will assign it a random value.
	//which will give me seg fault.
	n = 0;
	//Copy the stuff in inputfile to my array.
	while(fgets(line, MAX_LEN, in) != NULL){
		strcpy(Array[n],line);
		n++;
	}

	//starts at the beginning
	append(sort,0);
	//Move my cursor to the back to start the comparison 
	moveBack(sort);
	//start the indirect sort
	for(int i = 1; i<countline; i++){
		int countdown = length(sort);
		moveBack(sort);
		while(countdown > 0){
			int compare = strcmp(Array[i], Array[get(sort)]);
			//perform the swap
			if(compare > 0){
				insertAfter(sort,i);
				break;
			}
			//Do nothing if two elements are the same.
			else if (compare == 0){
				insertAfter(sort,i);
				break;
			}
			countdown --;
			movePrev(sort);
			//if the current element is the smallest, make it to the front of the list.
			if(index(sort) == -1){
				prepend(sort,i);
				break;
			}
		}
	}

	//set the cursor to the front of the List.
	moveFront(sort);
	//Print out the somehow sorted array.
	for(int j = 0; j < length(sort); j++){
		fprintf(out, "%s", Array[get(sort)]);
		moveNext(sort);
	}
	fclose(in);
	fclose(out);
	freeList(&sort);
	return(EXIT_SUCCESS);

}




