/* Xingyu Zhou
 * xzhou45@ucsc.edu
 * pa1
 * This file contains the inplementation of
 * all my List ADT functions.
 * It's written based on the Queue.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* prev;
   struct NodeObj* next;
} NodeObj;


// private Node type
typedef NodeObj* Node;

//private ListObj tyoe
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length==0);
}
// freeNode()
// Frees all heap memory associated with List *pL
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( !isEmpty(*pL) ) { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

// index()
// Returns the index of L.
int index(List L){
   if( L==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->index);
}

//front()
//returns the value at the front of L
//pre: !isEmpty(L);
int front(List L){
	if(L == NULL){
		printf("List Error: calling front() on NULL List Reference\n");
		exit(EXIT_FAILURE);
	}
	if(isEmpty(L) ){
		printf("List Error: calling front() on an empty List\n");
		exit(EXIT_FAILURE);
	}

	return(L->front->data);
}

//back()
//returns the value at the back of L
//pre: !isEmpty(L);
int back(List L){
	if(L == NULL){
		printf("List Error: calling front() on NULL List Reference\n");
		exit(EXIT_FAILURE);
	}
	if(isEmpty(L) ){
		printf("List Error: calling front() on an empty List\n");
		exit(EXIT_FAILURE);
	}

	return(L->back->data);
}

//get()
//Returns cursor element of L.
//Pre: length()>0, index()>=0
int get(List L){
	if(L == NULL){
		printf("List Error: calling get() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(isEmpty(L)){
		printf("List Error: calling get() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return(L->cursor->data);
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){

    printf("List Error: calling equals() on NULL List reference\n");
    exit(EXIT_FAILURE);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L){
	//Make sure I'm not calling this on nothing
	if(L == NULL){
		printf("List Error: calling clear() on NULL List reference\n");
      	exit(EXIT_FAILURE);
	}
	while(L->length > 0){
		deleteFront(L);
	}
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
	if(L == NULL){
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->length > 0){
		L->cursor = L->front;
		L->index=0;
	}
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
	if(L == NULL){
		printf("List Error: calling moveBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->length > 0){
		L->cursor = L->back;
		L->index = L->length-1;
	}
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){	
	if(L == NULL){
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	//if the cursor is not at front, move towards the front
	if(L->cursor != NULL && L->index != 0){
		L->cursor = L->cursor->prev;
		L->index --;
	}
	//make the cursor undefined if at front
	else if(L->cursor != NULL && L->index == 0){
		L->cursor = NULL;
		L->index = -1;
	}
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
	if(L == NULL){
		printf("List Error: calling moveNext() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	//if the cursor is not at back, move towards the end
	if(L->cursor != NULL && L->index != L->length - 1){
		L->cursor = L->cursor->next;
		L->index ++;
	}
	//make the cursor undefined if at the end
	else if(L->cursor != NULL && L->index == L->length - 1){
		L->cursor = NULL;
		L->index = -1;
	}
}


// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int data){
	if(L == NULL){
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node newData = newNode(data);

	if(L->front == NULL){
		L->front = newData;
		L->back = newData;
		//L->cursor = newData;
		L->index = 0;
	}
	else{
		L->front->prev = newData;
		newData->next = L->front;
		L->front = newData;
		L->index ++;
	}
	L->length ++;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int data){
	if(L == NULL){
		printf("List Error: calling append() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node newData = newNode(data);
	//append at the head of the list
	if(L->front == NULL){
		L->front = newData;
		L->back = newData;
		//L->cursor = newData;
		L->index = 0;
	}
	//append at the back of the list
	else{
		L->back->next = newData;
		newData->prev = L->back;
		L->back = newData;
	}
	L->length ++;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
	if(L == NULL){
		printf("List Error: calling insertbefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == NULL){
		printf("List Error: calling insertBefore() on NULL cursor\n");
		exit(EXIT_FAILURE);
	}
	if(L->index == 0){
		prepend(L,data);
	}
	else{
		Node newData = newNode(data);
		newData->prev = L->cursor->prev;
		newData->next = L->cursor;
		L->cursor->prev->next = newData;
		L->cursor->prev = newData;
		L->index++;
		L->length++;
	}
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
	if(L == NULL){
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == NULL){
		printf("List Error: calling insertAfter() on NULL cursor\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == L->back){
		append(L,data);
	}
	else{
		Node newData = newNode(data);
		L->cursor->next->prev = newData;
		newData->prev = L->cursor;
		newData->next = L->cursor->next;
		L->cursor->next = newData;
		L->length++;
	}
}

// Delete the front element. Pre: length()>0
// Taken from the example Dequeue
void deleteFront(List L){
	if(L == NULL){
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
   	if( isEmpty(L) ){
      	printf("List Error: calling deleteFront() on an empty List\n");
      	exit(EXIT_FAILURE);
   	}   
/*   	//if the cursor is already at front, reset the cursor	
   	if(L->index == 0){
   		L->index = -1;
   		L->cursor = NULL;
   	}*/ 

   	Node N = L->front;
   	if(L->length > 1){
   		L->front = L->front->next;
   		L->front->prev = NULL;
   	}else{
   		L->front = L->back = NULL;
   	}
   	freeNode(&N);
   	L->index--;
   	L->length--;
   	
}

// Delete the back element. Pre: length()>0
void deleteBack(List L){
	Node N = NULL;
	if(L == NULL){
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
   	if( isEmpty(L) ){
      	printf("List Error: calling deleteBack() on an empty List\n");
      	exit(EXIT_FAILURE);
   	}
   	N = L->back;   	

   	if(L->index == L->length-1){
   		L->index = -1;
   		L->cursor = NULL;
   	}
   	if(L->length > 1){
   		L->back = L->back->prev;
   		L->back->next = NULL;
   	}else{
   		L->front = L->back = NULL;
   	}
   	L->length--;
   	freeNode(&N);

}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
	Node N = NULL;
	N = L->cursor;
	if(L == NULL){
		printf("List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
   	if( isEmpty(L) ){
      	printf("List Error: calling delete() on an empty List\n");
      	exit(EXIT_FAILURE);
   	}
   	//the cursor is at the head of the list
   	if(L->index == 0){
   		deleteFront(L);
   	}
   	//the cursor is at the end of the list
   	else if(L->cursor == L->back){
   		deleteBack(L);
   	}
   	//somewhere in the list
   	else{
   		L->cursor->prev->next = L->cursor->next;
   		L->cursor->next->prev = L->cursor->prev;
   		L->length--;
   		L->index = -1;
   		L->cursor = NULL;
   		freeNode(&N);
   	}
}


// Other operations -----------------------------------------------------------
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){
   Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   for(N = L->front; N != NULL; N = N->next){
      fprintf(out ,"%d ", N->data);
   }
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
  if(L == NULL){
    printf("List Error: calling copyList() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
	Node copy = L->front;
	List new = newList();
	if(L->length > 0){
		while(copy!=NULL){
			append(new, copy->data);
			copy = copy->next;
		}
	}
	return new;
}
