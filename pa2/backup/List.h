/* Xingyu Zhou
 * xzhou45@ucsc.edu
 * pa2
 * This is the header file of list functions
 * taken from the lab manual
 */


#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
List newList(void); 		// Creates and returns a new empty List.
void freeList(List* pL); 	// Frees all heap memory associated with *pL, and sets
							// *pL to NULL.

// Access functions -----------------------------------------------------------
// Returns the number of elements in L.
int length(List L);

// Returns index of cursor element if defined, -1 otherwise. 
int index(List L); 

// Returns front element of L. Pre: length()>0
void* front(List L);	

// Returns back element of L. Pre: length()>0
void* back(List L); 	

// Returns cursor element of L. Pre: length()>0, index()>=0
void* get(List L); 	
	

// Manipulation procedures ----------------------------------------------------
// Resets L to its original empty state.
void clear(List L); 

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L); 

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L); 

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L); 

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L); 

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, void* data); 

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, void* data); 

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, void* data); 

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, void* data); 

// Delete the front element. Pre: length()>0
void deleteFront(List L); 

// Delete the back element. Pre: length()>0
void deleteBack(List L); 

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L); 


// Other operations -----------------------------------------------------------
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L); 




#endif
