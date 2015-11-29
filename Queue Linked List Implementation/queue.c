
/* queue.c
 *this file creates an abstact queue using nodes
 * in a linked list format.
 *
 *
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf(stderr, __VA_ARGS__);

/* Internal implementation definitions */
struct queue_node {
   queue_item_t item;
   struct queue_node *link;
};

typedef struct queue_node queue_node;

struct queue {
   queue_node *front;
   queue_node *rear;
};

/* Functions */

queue *queue_new(void) {
   queue *queue_node = malloc(sizeof (struct queue));  
   queue_node->front = NULL;
   queue_node->rear = NULL;
   printf("made a new queue \n");
   return queue_node;
}

void queue_free(queue *this) {
  printf("freeing the queue \n"); 
  if(queue_isempty(this)== false){
    while(this->front->link !=NULL){
      printf("freeing the queue");
     queue_node *temp = this->front;
      this->front = this->front->link; 
       free(temp);
    //  free(this);
    }
   }
   free(this);
} 

void queue_insert(queue *this, queue_item_t item) {
  // STUBPRINTF("item = \"%s\"\n", item);
    printf("inserting into the queue \n");
    struct queue_node *n = (struct queue_node *)malloc(sizeof(struct queue_node));
    n->item = item;
    if(queue_isempty(this)){
        this->front = n;
        this->rear = n;
    }
    else
      this-> rear->link = n ;
       this->rear = n;
     }
//on this next mehtod, I got help from my friend Estaban Quijada
queue_item_t queue_remove(queue *this) {
 //  assert(!queue_isempty(this));
   if(this->front == this->rear){
      queue_item_t tempitem = this->front->item;//
      queue_node *tempnode = this->front;
      this->front = this->front->link;
      free(tempnode);
      this-> front = NULL;
      this->rear = NULL;
      return tempitem;

   }
   else{
      queue_item_t tempitem = this->front->item;
      queue_node *tempnode = this->front;
      this->front = this->front->link;
      free(tempnode);
      return tempitem;
   }
     //free(linepos);
  }


bool queue_isempty(queue *this) {
   if(this->front == NULL)
        return true;
else
   return false;
}
