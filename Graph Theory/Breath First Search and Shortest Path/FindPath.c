//		FindPath.c
//	
// This program takes an input file and convets it to a graph
// then graph operations are preformed and distances
// between vertecies and their paths are displayed
//
//
//	@author: Ramzey Ghanaim
//	@CruzID: rghanaim
//	@assignment: pa4
//
// I worked closely with Avi Varshney
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"


typedef char *string;

int main(int argc, char* argv[]){

	FILE *in, *out;
 
	//check for correct number of arguments
	if(argc !=3){
		printf("Usage: %s <input file> <output file>\n",argv[0]);
		exit(1);
	}
	
	//get file names
	in = fopen(argv[1],"r");
	out = fopen(argv[2], "w");
	//make ure files exits
	if(in == NULL){
		printf("Unable to open file %s for reading\n",argv[1]);
		exit(1);
	}
	if(out == NULL){
		printf("Unable to open file %s for writing\n",argv[2]);
		exit(1);
	}
	
	int vertecies;
	fscanf(in, "%d",&vertecies);//scan firs tine for number of vertecies
	Graph G = newGraph(vertecies); //make a new graph
	
	int one, two;
	while(fscanf(in,"%d %d", &one, &two)==2){
		if(one == 0 && two == 0) break;
		addEdge(G,one,two); //add edges by scanning in the file
	}

	printGraph(out, G);//print out graph
	fprintf(out,"\n"); //skip a line
	int s =0; int d = 0;
	while(fscanf(in,"%d %d",&s,&d)){
		if(d ==0 && s ==0){
			break;
		}
		BFS(G,s); //apply BFS
		int distance = getDist(G, d); //find teh distance between two vertecies
		fprintf(out, "The distance from %d to %d is ",s,d);
		if(distance != INF){
			fprintf(out,"%d\n",distance); //print the distance
		}
		else{
			fprintf(out, "infinity\n"); //if infity print "infinity"
		}
		List T = newList();
		getPath(T,G,d); //get the path of between vertecies
		if(length(T)>0){
			fprintf(out, "A shortest %d-%d path is: ",s,d);
			printList(out,T); //display the shortest path
			fprintf(out, "\n\n"); //skip 2 lines
		}
		else{
			fprintf(out, "No %d-%d path exists \n\n",s,d); //if not path exits, print it
		}
		freeList(&T); //free the list
	}
	
	freeGraph(&G);//free the graph

	fclose(out);//close the output file
    fclose(in); //close the input file
}	
