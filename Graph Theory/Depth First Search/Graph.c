//		Graph.c
//  
//  Graph is the Graph ADT that preforms BFS on graphs, and
//  finds paths between vertecies, and adds directed and 
//  non-directed edges between vertecies
//
//  
// @author: Ramzey Ghanaim
// @CruzID: rghanaim
// @assignmetn: pa5
//
//
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

typedef struct GraphObj{
	int order;// vertecies
	int size; //number of edges
	List *neighbors; //list containing adjacent vertecies
	int *color; //color of vertecie: white, black or gray
	int *parent;//the parent of a vertecy
	int *discover; //new
	int *finish; //new
} GraphObj;

typedef enum color{
	WHITE,
	GRAY,
	BLACK
}color;

void insertionSort(List L, int v); //declare insertion sort
void visit(Graph G, List S, int u, int *time); //declare visit

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
	G->discover = malloc((n+1) * sizeof(int));
	G->finish = malloc((n+1) * sizeof(int));
	G->order = n;
	G->size = 0;
	for(int i = 1; i <= n; i++){//initalize all vertecies
		G->neighbors[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}

	return G;//retrun the new graph
}

//frees the graph
void freeGraph(Graph *pG){
		for(int i=0; i <=(*pG)->order; i++){
			freeList( &(*pG)->neighbors[i] );
		}
		free( (*pG)->neighbors);
		free( (*pG)->color );
		free( (*pG)->parent );
		free((*pG) -> discover);
		free((*pG)-> finish);

		(*pG)->color = NULL;
		(*pG)->parent = NULL;
		(*pG)->neighbors = NULL;
		(*pG)->discover = NULL;
		(*pG)->finish = NULL;
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

int getDiscover(Graph G, int u){ //new for DFS
	if(G == NULL){
		printf(" error on getDiscover(): G is null\n");
		exit(1);
	} 
	if(u<1 || u> getOrder(G)){
		printf("error at getDiscover(): u is out of bounds\n");
		exit(1);
	}
	
	return G->discover[u];
}

int getFinish(Graph G, int u){
	if(G == NULL){
		printf("error at getFinish(): G is null\n");
		exit(1);
	}
	if(u<1 || u> getOrder(G)){
		printf("error at getFinsih(): u is invalid\n");
		exit(1);
	}
	
	return G->finish[u];
}

void DFS(Graph G, List S){
	if(S == NULL){
		printf("error at DFS(): G is null\n");
		exit(1);
	}
	if(G== NULL){
		printf("error at DFS(): G is null\n");
		exit(1);
	}
	if(getOrder(G) != length(S)){
		printf("error at DFS: S is invalid\n");
		exit(1);
	}
	
	for(int i = 1; i<=G->order; i++){
		G->finish[i] = UNDEF;
		G->color[i] = WHITE;
		G->parent[i]= NIL;
		G->discover[i] = UNDEF;
	}
	int time = 0;
	moveFront(S);
	while(index(S) >= 0){
		if(G->color[get(S)] == WHITE){
			visit(G,S,get(S), &time);
		}
		moveNext(S);
	}
	for(int d = (length(S)/2); d >0; --d){
		deleteBack(S);
	}
}

void visit(Graph G, List S, int u, int *time){
	G->discover[u]=++*time;
	G->color[u] = GRAY;
	moveFront(G->neighbors[u]);
	while(index(G->neighbors[u])>=0){
		int node = get(G->neighbors[u]);
		if(G->color[node] == WHITE){
			G->parent[node] = u;
			visit(G, S, node, time);
			//G->parent[get(G->neighbors[u])]= u;
			//visit(G,S,get(G->neighbors[u]),time);
		}
		moveNext(G->neighbors[u]);
	}
	G->finish[u] = ++*time;
	G->color[u] = BLACK;
	prepend(S,u);
}

Graph transpose(Graph G){
	Graph trans = newGraph(G->order);
	for(int i = 1; i<= G->order; ++i){
		moveFront(G->neighbors[i]);
		while(index(G->neighbors[i])>=0){
			addArc(trans, get(G->neighbors[i]),i);
			moveNext(G->neighbors[i]);
		}
	}
	return trans;
}

Graph copyGraph(Graph G){
	Graph copy = newGraph(G->order);
	for(int i=1; i<=G->order;i++){
		moveFront(G->neighbors[i]);
		while(index(G->neighbors[i]) >=0){
			addArc(copy, i, get(G->neighbors[i]));
			moveNext(G->neighbors[i]);
		}
	}
	return copy;
}
