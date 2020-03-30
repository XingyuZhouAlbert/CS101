#include<stdio.h>
#include<stdlib.h>
#include "List.h"


int main(int argc, char* argv[]){
	List A = newList();
        prepend(A, 5);
        prepend(A, 65);
        prepend(A, 43);
        prepend(A, 2);
        prepend(A, 8);
        prepend(A, 1);
        moveFront(A);
        deleteFront(A);
        printf("index:%d\n",index(A));
        if (index(A) != -1) return 1;
        moveBack(A);
        deleteFront(A);
        printf("index:%d\n",index(A));
        if (index(A) != 3) return 2;
        freeList(&A);
        return 0;
}