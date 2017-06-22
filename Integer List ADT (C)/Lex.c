/*
*	Lex.c
* This program takes in a file as an argument, orders it indirectly
* and sends it to an output file (second argument). Lex.c uses the
* the List ADT in List.c

* @assignment: pa2
* @author Ramzey Ghanaim
* @CruzID rghanaim
* 
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX 100
int main(int argc, char * argv[]){
	int lines = 0;
	FILE *in, *out;
	char line[MAX];

	//check for correct number of arguments
	if(argc !=3){
		printf("Usage: %s <input file> <output file>\n",argv[0]);
		exit(1);
	}
	
	//open files for reading
	in = fopen(argv[1],"r");
	out = fopen(argv[2], "w");
	if(in == NULL){
		printf("Unable to open file %s for reading\n",argv[1]);
		exit(1);
	}
	if(out == NULL){
		printf("Unable to open file %s for writing\n",argv[2]);
		exit(1);
	}
	//counting number of lines
	while(fgets(line, MAX, in) != NULL){
		lines++;
	}
	rewind(in); //resets file reader to beginning of file
	char array[lines-1][MAX];
	int dex = -1;
//copy file to array
	while(fgets(line, MAX, in) != NULL){
		strcpy(array[++dex],line);
	}
	//Make a list
	List final = newList();	
	append(final,0);
	//=========INSERTION SORT========================================
	int j;
	for(j = 1;j<lines;j++){
		char* temp = array[j];
		int isDone = 0;
		//keep going back to find correct place to insert
		moveBack(final);
		while(isDone != 1 && strcmp(temp, array[get(final)]) <=0){
			if(index(final) == 0){
				insertBefore(final, j);
				isDone = 1;
			}
			else{
				movePrev(final);
			}
		}
		if(isDone == 0){	
				insertAfter(final, j);		
			}	
	}
	//now Save order to file
	moveFront(final);//move cursor to front
	int i;
	for(i = 0; i< lines;i++){//itterate through
		fprintf(out, "%s",array[get(final)]);
		moveNext(final); //final= final.next
	}
	//close and free everything (List, in reader, out reader)
	fclose(out);
	fclose(in);
	freeList(&final);
	
	return 0;// main always returns 0
}
