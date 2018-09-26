//         mycat.c
//
// This program replicates the LINUX
// "cat" command using system calls
//
// @author: Ramzey Ghanaim

#include <stdio.h>
#include <unistd.h>
#include <string.h>

//used for system calls: read() write() open() close()
#include <fcntl.h>

#include <stdlib.h>

// allows "while(true)"
#include <stdbool.h>

int main(int argc, char* argv[]){
//check for correct usage
	
//no files:
	if(argc <= 1){ //not correct number of arguments
		char  buff [2048];
		while(true){ //loop infininetly since no arguments exist
			memset(buff, 0, sizeof buff -1);//reset buffer
		    int t=  read(0, buff, sizeof buff); //read input
			if( t == 0){  //read returns 0 if CTRL + D is hit
				return 0; //exit
			}
		    write (1, buff , sizeof buff); //print buffer to screen
		    if (t == -1 ){ //if error occured
				perror("usage: ./mycat file1 file2");//error

		    }
		}
	}  //end part 1 (no files, infinite loop of user input)

//open each file
	for (int i = 1; i<argc; i++){
		char buffer [2048]; 
		char* file = argv[i];
		int x = open(file, O_RDONLY); //open file to read it
		size_t files; // size_t is an unsigned int type files_read

		if( x <0){ //if number of characters in file is nothing (empty file)....
		
//-------------------------------------------------------------------
//The following joins the program name and file name as one string
//the purpose is because perror only takes in one charater input.
//the goal is to output "proramName: fileName: "
			char *programname = "mycat: ";
			char print[123];
			strcpy(print, programname);
			strcat(print, file);
//--------------------------------------------------------------------
			perror(print);//... then print error
		}
		else{
			while((files = read(x, buffer, sizeof buffer)) > 0){
				size_t written = 0; // total number of files written total
		
		//now we want to continously read through all the files
				while(files > written) { //while not all the files have been written..
					size_t newlyWritten = write(1, buffer + written, files - written);
					written = written + newlyWritten;
				}
			} //end first while

		} //end else

		close(x); //close the file
	}//end part 2 (itteration through parameters
	return 0;
}

