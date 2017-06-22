//
//		Graph.h
//	Graph.h defines functions used
//	in Graph.c
//
// @author: Ramzey Ghanaim
// @assignment: pa5
// @CruzID: rghanaim
//	
#ifndef _Graph_H_INCLUDE
#define _Graph_INCLUDE

#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#define INF -1
#define NIL 0
#define UNDEF -1

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
int getDiscover(Graph G, int u); //new
int getFinsih(Graph G, int u); //new


//*** Manipulation Procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
void DFS(Graph G, List S);//new

//*** Other Functions ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);


//*** other operations ***/
void printGraph(FILE* out, Graph G);

#endif
