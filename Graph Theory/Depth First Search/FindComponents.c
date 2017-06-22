//		FindComponents.c
//
//	This program Finds the components of various graphs 
//	using DFS 
//
//	@author: Ramzey Ghanaim
//	@CruzID: rghanaim
//	@assignment: pa5
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

#define LEN 200

typedef char *string;

int main(int argc, char * argv[]){
	FILE *in, *out;
	char line[LEN];

	if(argc !=3){ //check for input and output files
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	in = fopen(argv[1], "r"); // read input file
	out = fopen(argv[2], "w"); //write to an output file 
	
	//make sure files are valid
	if(in == NULL){ 
		printf("Write file is null\n");
		exit(1);
	}
	if(out == NULL){
		printf("Write file is null\n");
		exit(1);
	}
	
	//scan thorough each line
	int vertecies=0;
	fgets(line, LEN, in);
	sscanf(line,"%d",&vertecies);
	
	//create a list and fill it
	List R = newList();
	for(int x = 1; x<= vertecies; ++x){
		append(R,x);
	}
	//create a graph and fill it
	Graph G = newGraph(vertecies);
	while(fgets(line, LEN, in) != NULL){
		int one =0, two = 0;
		sscanf(line, "%d %d", &one, &two);
		if(one == 0 && two == 0){
			break;
		}
		addArc(G,one, two);
	}
	DFS(G,R); //run DFS on the graph now that its complete
	//Find Transpose of graph and run DFS
	Graph Trans = transpose(G);
	int count = 0; //initialize counter
	DFS(Trans, R);
	moveFront(R); //start in the font of the list

	while(index(R)>=0){//itterate through list
		if(getParent(Trans, get(R)) == NIL){ //check parents
			count++; //increment counter
		}
		moveNext(R); //itterate through
	}
	List L[count]; //create a list with the number of roots
	for(int i = 0;i<count; ++i){
		L[i] = newList(); //List of lists! (Listception)
	}
	moveFront(R);
	int x = count;

	
	while(index(R) >=0){ //itterate through list again
		if(getParent(Trans, get(R)) == NIL){ //same as before
			x--; //but decrease number of roots
		}
		if(x == count){ //if you havent found one root yet..
			break; //...break
		}
		append(L[x], get(R)); //otherwise, append
		moveNext(R); //and move through the list
	}
	//Now for the printouts..
	fprintf(out, "Adjacency List Representation of G: \n");
	printGraph(out,G);
	fprintf(out, "\n");
	fprintf(out, "G contains  %d strongly connected components: ", count);
	for(int a =0; a<count; a++){ //itterae through list of roots
		fprintf(out, "\n");
		fprintf(out, "Component %d: ", (a+1)); 
		printList(out, L[a]); //print out the components
		freeList(&(L[a])); //free list, we are done with it
	}
	fprintf(out,"\n"); //new line for formating
	
	//now free everything!
	freeGraph(&Trans);
	freeGraph(&G);
	freeList(&R);

	//we done with in and out files
	fclose(out);
	fclose(in);
}
