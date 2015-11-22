//list.c
//This program represents a singlly linked list in C
#include <stdio.h>
#include <stdlib.h>

// A node in a singly-linked list
struct node {
    int value;
    struct node *next;
};

// Head of the linked list
struct node *head= NULL;
//declaration of variables
int nelms=0;
// Insert a value into linked list
void list_insert(int v) {
    struct node *n;
    n = (struct node *)malloc(sizeof(struct node));
    n->value = v;
    n->next = head;
    head = n;
    nelms++;
  // n = temp;
    n = head;

}

// Insert two values at once into linked list
void list_insert2(int a, int b) {
    struct node *u, *v;

    u =(struct node *)malloc(sizeof(struct node));
    v =(struct node *)malloc(sizeof(struct node));
    u->value = a;
    u->next = v;
    v->value = b;
    v->next = head;
    head = u; 
    nelms +=2;
        
}

// Remove an element from linked list
void list_remove(int v) {
  struct node *n=head;
  struct node *previous = head;
   while(n->value != v) {
        previous = n;
        n = n->next;
    }
    if(n == head) {
        head = head->next;
          }
   else if(n->next == NULL){
     
      previous->next = NULL;
       }
   else{
  
         previous->next =n->next;
             
 }
    nelms--;
     free(n);
  //    free(previous);

  }

// Print out all values in linked list
void list_printall(void) {
    struct node *p= head;
   int n = 0;
    while(n<nelms) {
        printf("%d ", p->value);
        p=p->next;
        n++;
        if(n > 100) break;
    }
    printf("\n");
    p =head;
    }


// Deallocate all memory used in linked list
void list_destroy(void) {
   struct node *temp;
   while(head != NULL){
   temp = head->next;
   free(head);
   head = temp;  
  }
}

int main(int argc, char *argv[]) {
    printf("Test linked lists\n");
    list_printall(); // Should print nothing
    list_insert(42);
    list_insert2(17, 10);
    list_insert(18);
    list_remove(10);
    list_printall(); // Should print 18 17 42
    // Cleanup memory
    list_destroy();
    return 0;
}
