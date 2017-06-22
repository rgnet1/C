//		Graph.c
//  
//  Graph is the Graph ADT that preforms BFS on graphs, and
//  finds paths between vertecies, and adds directed and 
//  non-directed edges between vertecies
//
//  
// @author: Ramzey Ghanaim
//
//
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

typedef struct GraphObj{
	int order;// vertecies
	int size; //number of edges
	int source; //source (used for BFS)
	List *neighbors; //list containing adjacent vertecies
	int *color; //color of vertecie: white, black or gray
	int *parent;//the parent of a vertecy
	int *distance; //the distance each vertecy is from the source
} GraphObj;

typedef enum color{
	WHITE,
	GRAY,
	BLACK
}color;

void insertionSort(List L, int v); //declare insertion sort

//newGraph creates a new graph with n vertecies
Graph newGraph(int n){
	if (n<1){ //make sure n is valid
		printf("error on newGraph(): invalid size");
		exit(1);
	}

	//alocate memory
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors = malloc((n+1) * sizeof(List));
	G->color = malloc((n+1) * sizeof(int));
	G->parent = malloc((n+1) * sizeof(int));
	G->distance = malloc((n+1) * sizeof(int));
	G->order = n;
	G->size = 0;
	for(int i = 1; i <= n; i++){//initalize all vertecies
		G->neighbors[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}

	return G;//retrun the new graph
}

//frees the graph
void freeGraph(Graph *pG){
		for(int i=0; i <=(*pG)->order; i++){
			freeList( &(*pG)->neighbors[i] );
			//(*pG)->neighbors[i] = NULL;
		}
		free( (*pG)->neighbors);
		free( (*pG)->color );
		free( (*pG)->parent );
		free( (*pG)->distance );

		(*pG)->color = NULL;
		(*pG)->parent = NULL;
		(*pG)->distance = NULL;

		(*pG)->neighbors = NULL;
		free(*pG);
		*pG = NULL;
}

//getOrder retruns order: the number of vertecies 
//if the graph is not null
int getOrder(Graph G){
	if(G== NULL){
		printf("error on getOrder: G is null\n");
		exit(1);
	}
	return G->order; 
}

//getSize returns the size of the graph
//if the graph is not null
int getSize(Graph G){
	if(G== NULL){
		printf("error on getSize(): G is null");
		exit(1);
	}
	return G->size;
}

//getSource returns the source of the graph 
//if the graph is not null
int getSource(Graph G){
	if(G== NULL){
		printf("Error on getSource(): G is null");
		exit(1);
	}
	return G->source;
}

//getParent returns the parent of vertecy u
//if G is not null and u is a valid vertecy
int getParent(Graph G, int u){
	if(G == NULL){
		printf("error on getParent(): G is null");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		printf("error on getParent(): u is out of bounds\n");
		exit(1);
	}
	return (G->parent[u]);
}

//getDist returns the distance of verttecy u 
//if G is not null and u is a valid vertecy
int getDist(Graph G, int u){
	if(G== NULL){
		printf("error on getDist(): G is null");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		printf("error on getDist(): u is out of bounds\n");
		exit(1);
	}
	return (G->distance[u]);
}

//getPath appends to the List L the vertecies of a shortest path 
//in G from source to u, or appends to L the value of NIL if no such path exits
//IF G is not null, the source is not nil and u is a valid vertecy
void getPath(List L, Graph G, int u){
	if(G== NULL){
		printf("error on getPath: G is null\n");
		exit(1);
	}
	if(G->source == NIL){
		printf("error on getPath(): source is NIL\n");
		exit(1);
	}
	
	if(u < 1 || u > getOrder(G)){
		printf("error on getPath(): u is out of bounds\n");
		exit(1);
	}
	if(G->parent[u] != NIL){
		getPath(L, G,G->parent[u]);
		append(L,u);
	}
	else if(G->source == u){
		append(L,u);
	}
}

//makeNull makes the graph null and size 0
//if G is not null already
void makeNull(Graph G){
	if(G== NULL){
		printf("error on makeNull(): G is null");
		exit(1);
	}
	for(int i = 1; i <= G->order; i++){
		clear(G->neighbors[i]);
	}
	G->size = 0;
}

//addEdge adds an edge betwen two vertecies 
//if both vertecies are valid in the graph
void addEdge(Graph G, int u, int v){
	if(G== NULL){
		printf("error at addEdge(): G is null");
		exit(1);
	}
	if(u < 1 || u > getOrder(G)){
		printf("error at addEdge: u is out of bounds\n");
		exit(1);
	} else if(v < 1 || v > getOrder(G)){
		printf("error at addEdge(): v is out of bounds\n");
		exit(1);
	}
	
	insertionSort((G->neighbors[u]), v); 
	insertionSort((G->neighbors[v]),u);
	G->size++;
}

//adds a one directional edge between two vertecies
//if both vertecies are valid in the graph
void addArc(Graph G, int u, int v){
	if(u < 1 || u > getOrder(G)){
		printf("error at addArc(): u is out of bounds\n");
		exit(1);
	}if(v < 1 || v > getOrder(G)){
		printf("error at addArc(): v is out of bounds\n");
		exit(1);
	}
	insertionSort((G->neighbors[u]), v);
	G->size++;
}

//BFS preforms Breath First Search on a graph with
//source s if G is not null and s is a valid
//vertecy.
//
//This is just the sudo code provided from class and
//inthe text book
void BFS(Graph G, int s) {
	if (G == NULL) {
		printf("Error: BFS called on NULL Graph pointer\n");
		exit(1);
	} else if (s < 1 || s > G->order) {
		printf("Error: BFS called with invalid source.\n");
		exit(1);
	}
	for (int i = 1; i <= getOrder(G); i++) { //initialize...
		G->color[i] 	= WHITE;
		G->distance[i] 	= INF;
		G->parent[i] 	= NIL;
	}
	G->source = s;
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List L = newList();
	append(L, s);
	while(length(L) != 0) {
		//deque----
		int x = front(L);
		deleteFront(L);
		//-------------
		List temp = G->neighbors[x];
		for (moveFront(temp); index(temp) != -1; moveNext(temp)) {
			int y = get(temp);
			if (G->color[y] == WHITE) {
				G->color[y] = GRAY;
				G->distance[y] = G->distance[x] +1;
				G->parent[y] = x;
				append(L, y);
			}
		}
		G->color[x] = BLACK; //done with vertecy, set color black
	}
	freeList(&L);
}


//insertionSort applies insertion sort algorithm
//to inserting v into list L
void insertionSort(List L, int v){
	if( length(L) == 0) {
		append(L, v); return;
	}
		moveBack(L);
		int Done = 0;
		while( v < get(L) && Done == 0){
			if(index(L) == 0){
				Done++;
				insertBefore(L, v);
			} 
			else
				movePrev(L);
		}
		if(Done == 0) 
			insertAfter(L, v);	
}

//printGraph prints the graph to an output file
//if the file is valid and the graph is not null
void printGraph(FILE* out, Graph G){
	if(out == NULL){
		printf("error at printGraph(): out is null");
		exit(1);
	}
	if(G ==NULL){
		printf("error at printGraph(): G is null");
		exit(1);
	}
	for(int i = 1; i <= G->order; i++){
		fprintf(out, "%d: ", i);
		printList(out, G->neighbors[i]);
		fprintf(out, "\n");
	}
}
