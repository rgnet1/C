//
//		Graph.h
//	Graph.h defines functions used
//	in Graph.c
//
//	
#ifndef _Graph_H_INCLUDE
#define _Graph_INCLUDE

#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#define INF -1
#define NIL 0

typedef struct GraphObj* Graph;

Graph newGraph(int n);
void freeGraph(Graph* pG);

//*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

//*** Manipulation Procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

//*** other operations ***/
void printGraph(FILE* out, Graph G);

#endif
