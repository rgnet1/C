//       List.c
//
// List is an ADT that represents a list of integers.
// Lex.c uses this to implement a non-direct method of
// ordering an array of strings but using teh integer 
// the list ADT as indecies for the elements in the 
// string array in Lex
//
// @CruzID: rghanaim
// @author: Ramzey Ghanaim
// @assignment: pa5
//
//
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
//
//create node structure
typedef struct nodeObj{
	int data;
	struct nodeObj *next;
	struct nodeObj *prev;
} nodeObj;

typedef nodeObj *Node;

//create List object
typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

//constructor for a node
Node newNode(int data){
	Node N = malloc(sizeof(nodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return (N);
}

//Now for the methods:
//freeNode() frees memeory pointed to by *pN, and sets it to NULL
void freeNode(Node* pN){
	if(pN !=NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}
//newList()
// returns a pointer to a new empty list obj
List newList(void){
	List X;
	X = malloc(sizeof(ListObj));//assign memory for a list
	X-> front = X-> back = NULL;
	X->length = 0;
	X->index = -1; //loction of cursor
	X->cursor = NULL;
	return (X);
}

//freeList()
//frees the entire list
void freeList(List *pL){
	if(pL !=NULL && *pL !=NULL){
		while(length(*pL)!=0){
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

//==============Access Functions ====================
int length(List L){ //return lenght of list if List exists
	if(L != NULL){
		return L->length;
	}
	else
		printf("error length(): can't find length of an empty list");
		exit(1);
}

int index(List L){ //return location of cursor
	if(L->cursor == NULL){
		//printf("index() error: can't index on null cursor");
		//exit(1);
		return -1;
	}
	return (L->index);
}
//returns data at the front of the list if list is not empty
int front(List L){
	if(L->length >0){
		return (L->front->data);
	}
	else{
		printf("error front(): Called an empty List");
		exit(1);
		}
}

//returns data in back of list if list is not empty 
int back(List L){
	if(L->length >0)
		return (L->back->data);
	else{
		printf("error back(): Called empty list");
		exit(1);
		}
	
}

//returns data of cursor node
int get(List L){
	if(L->length >0 && L->cursor !=NULL){
		return (L->cursor->data);}
	else{
		printf("error get(): called empty list");
		exit(1);
		}
}
//equals(list A, List B) returns 1 if A = B and 0 otherwise
int equals(List A, List B){
	if(A->length != B->length)
		return 0;
	else{
		Node og = A->front;
		Node tardis = B->front;
		while(og != NULL && tardis != NULL){
			if(og->data != tardis->data){
				return 0;}
			og= og->next;
			tardis = tardis->next;
		}
		return 1;
	}
}

//===========Manipulation procedures=========================

//Resets this list to its original empty state
void clear(List L){
	if(L!=NULL){
		while(L->length > 0){
			deleteFront(L);

		}
	}
	else{
		printf("error clear(): called empty list");
		exit(1);
	} //end else

}// end clear()

void moveFront(List L){//place cursor at front of list iff list is not empty
	if(L->length>0){
		L->cursor = L->front;
		L->index = 0;
	}
}

void moveBack(List L){//place cursor at back of list iff list is not empty
	if(L->length>0){
		L->cursor = L->back;
		L->index = L->length-1;
	}
}

//move cursor back if cursor is defined and not at front
void movePrev(List L){
	//if cursor is not front and index is not 0
	if(L->cursor != NULL && L->cursor->data != L->front->data){
		L->cursor = L->cursor->prev;
		L->index --;
	} 
	//if cursor is in the front..
	else if(L->cursor != NULL && L->cursor->data == L->front->data){
		L->cursor = NULL;//null the cursor
		L->index = -1;//set index to -1
	}
}
//if cursor is defined and not at back, move cursor to next element
void moveNext(List L){
	if(L->cursor !=NULL && L->cursor->data != L->back->data){
		L->cursor = L->cursor->next;
		L->index++;
	}
	else if(L->cursor == L->back){
		L->cursor = NULL;
		L->index = -1;
	}
}

//insert data into the front of the list
void prepend(List L, int data){
     if(L->length ==0){ //If list is empty
		Node temp = newNode(data);//make a new node
		L->front = L->back = temp;//first element in list
	}
	else{//if list is not empty
		Node temp = newNode(data);//make a new node
		temp->next = L->front;
		L->front->prev = temp;
		L->front = temp;
	}
	L->length++; //always increase length
}

//insert elements into the back of the list
void append(List L, int data){
	Node temp = newNode(data);//make a new node
	temp->next = NULL; //initialize to null
	if(L->length ==0){ //first element in the list
		L->front = temp;
		L->back = temp;
	}
	else{ //not first element in the list
		L->back->next = temp;
		temp->prev = L->back;
		L->back = temp;
	}
	L->length++;//always increase the length
}

//inserte element before the cursor if list is not empty and 
//cursor is not null
void insertBefore(List L, int data){
	if(L->length ==0){
		printf("error: insertBefore() doesn't work on empty list");
		exit(1);
	}
	else if(index(L)<0){
		printf("error: insertBefore(), null cursor");
		exit(1);
	}
	Node temp = newNode(data);
	if(L->cursor->prev ==NULL){ //if cursor is in the front
		temp->next = L->cursor;
		L->cursor->prev = temp;
		L->front = temp;
	}
	else{ //curosr is not in the front
		L->cursor->prev->next = temp;
		temp->prev = L->cursor->prev;
		L->cursor->prev = temp;
		temp->next = L->cursor;
	}
	L->length++;//always increase length
}

//insert element after the cursor if list is not empty
//or if curor is not null
void insertAfter(List L, int data){
	if(length(L) == 0){
		printf("error: insertAfter() doesn't work on empty lists");
		exit(1);
	}
	else if(index(L)<0){
		printf("error: insertAfter(), null cursor");
		exit(1);
	}
	Node temp = newNode(data);
	if(L->cursor->next == NULL){//if cursor is in the back
		L->cursor->next = temp;
		temp->prev = L->cursor;
		L->back = temp;
	}
	else{//if curor is not in back
		L->cursor->next->prev = temp;
		temp->next = L->cursor->next;
		L->cursor->next = temp;
		temp->prev = L->cursor;
	}
	L->length++;
}

//Deletesthe element at the front of the list if the list
//is not empty
void deleteFront(List L){
	if(length(L)>0){
		Node temp = L->front;
		if(L->cursor != NULL && L->front != NULL && L->cursor->data == L->front->data)
			L->index = -1;
		L->length--;
		L->front->prev = NULL;
		L->front = L->front->next;
		freeNode(&temp);
	}
	else{//list is empty
		printf("error deleteFront(), can't delete on empty list");
		exit(1);
	}
	
}

//delete's back element of list if the list is nnot empty
void deleteBack(List L){	
	
   if(L->length <=0) { //pre lenght >= 0
      printf("error on deleteBack(): list is empty\n");
      exit(1);
   }
   if(L == NULL) { //pre list is not null
      printf("error on deleteBack():list is null\n");
      exit(1);
   }
   if(L->cursor == L->back) { //if cursor is already in the back...
      L->cursor = NULL; //make it null
      L->index = -1; //make cursor index -1
   }

   if(L->back == L->front) //if there's only one element in list..
      L->front = NULL; //make front null
  //now deal with the back..
   Node temp = L->back;
   if(L->back->prev != NULL)
      L->back =L->back->prev;
   L->back->next = NULL;
   --L->length;
   freeNode(&temp);
	
}


//delets the cursor  if list is not null and cursor is defined,
//and if lenght>=0
void delete(List L){
	if( L == NULL){
		printf("error on delete(). Cannot delete null list");
		exit(1);
	}
	if(L->index<0){
		printf("error delete(). cursor is undefined");
		exit(1);
	}
	if(L->length<0){
		printf("effor on delete(). cannot delet empty list");
		exit(1);
	}
	if(L->cursor == L->back){
		deleteBack(L);
	}
	else if(L->cursor ==L->front){
		deleteFront(L);
	}
	else{
		Node temp = L->cursor;
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		freeNode(&temp);
		L->length--;
	}
}

//print list to a file
void printList(FILE* out, List L){
		moveFront(L);
		while(L->cursor != NULL){
			fprintf(out, "%d ",get(L));
			moveNext(L); //final= final.next
		}
	//	fclose(out);
}

//make a copy of a list and return it
List copyList(List L){
	List A = newList();
	Node temp;
	for(temp = L->front;temp !=NULL; temp=temp->next){//itterate through list
		append(A, temp->data);
	}
	return A;//return the list
}
