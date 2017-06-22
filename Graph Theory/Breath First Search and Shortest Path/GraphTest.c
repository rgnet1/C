//      GraphTest.c
//  
//  This is a tester client for Graph.c
// 
//  @author: Ramzey Ghanaim

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

int main(){
    Graph G = newGraph(69); //make a new graph with 69 vertecies
	//assign edges to vertecies
    addEdge(G, 1, 2);
    addEdge(G, 1, 69);
    addEdge(G, 42, 3);
    addEdge(G, 42, 69);
    
    printf("Order: %d\n", getOrder(G)); //print the order
    printf("Size: %d\n", getSize(G)); //print the size
    BFS(G, 1); //apply BFS on the graph with source at 1

	//check getter functions
    printf("Distance: %d\n", getDist(G, 42)); 
    printf("Source: %d\n", getSource(G));
    printf("Parent: %d\n", getParent(G, 69));
   
    
    List trumped = newList();
    getPath(trumped, G, 69); //make a new list and find the path with it
    printf("Size of list path: %d\t", length(trumped)); 
    
	//add more edges
    addEdge(G, 5, 10);
    addEdge(G, 5, 20);
    addEdge(G, 6, 20);
    
	//test makeNull
    makeNull(G);
    printf("Size of Null graph: %d\n", getSize(G));
	
	//test addArc
    addArc(G, 5, 40);
    addArc(G, 42, 5);
    BFS(G, 1);
    printf("Size after addArc: %d\n", getSize(G));


    //Add more edges and apply BFS
    addEdge(G, 5,20);
    addEdge(G, 6, 20);
    BFS(G, 1);

	//test printing graph out to a file called outTest
    FILE *outTest = fopen("outTest", "w");
    printGraph(outTest, G);
   
   //test free
    freeGraph(&G); 
    freeList(&trumped);

    return 0;
}
