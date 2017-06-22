//==================================================
//         List.h
//    Header file for the List ADT
//==================================================

#ifndef _LIST_H_INCLUDE
#define _LIST_INCLUDE

typedef struct ListObj* List;

//====Constructors/Destructors=====================
List newList(void);

void freeList(List *pL);

//====Access Functions=============================

int length(List L);
extern int index(List L);
int front(List L);
int back(List L);
int get(List L);
int equals(List A, List B);

//====Minipulation Functions======================
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);
void printList(FILE* out, List L);
List copyList(List L);

#endif
