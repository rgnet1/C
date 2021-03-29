
#include "server.h"


//thread counter mutex
pthread_mutex_t mainMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t emailMutex = PTHREAD_MUTEX_INITIALIZER;

//Shared memory



// Socket variables
int socketFD;
struct sockaddr_in server, client;

// Thread variables
int threadCount, threadWait;



int main(int argc, char* argv[]){	
	// getting port from user input
	// and make a listening socket
	int connected;
	int port, i;
	if(argc == 2){
		port = atoi(argv[1]);
	} else{
		printf("Usage: ./server <port>\n");
		exit(1);
	}

	createConn(port);

	// Netowrking variable
	int addrSize = sizeof(struct sockaddr_in);


	printf("Waiting for clients...\n");

	// Data buffer
	char buffer[MAX];

	// Array of thread Data to
	// handle tMAX threads at a time
	tdata threadData[tMAX];
	for(i = 0; i< tMAX;++i){
		threadData[i].buffer = malloc(sizeof(char) *MAX);
	}

	// Declare tMAX of threads
	pthread_t t[tMAX];

	//Initalize variables
	threadCount=0;
	int threadIndex = 0;
	threadWait = 0;

	//sleep while waiting to accept connections
	while((connected = accept(socketFD,
							 (struct sockaddr *)&client,
							 (socklen_t*)&addrSize)) >0){
		
		//reset buffer
		memset(&buffer,0,MAX);

		// make sure thread index gets reset
	    // back to 0
		if(threadIndex >= tMAX){
			printf("***** REACHED MAX******** %d\n",threadIndex);
			threadIndex = 0;
		}
		printf("Therad Index = %i\n",threadIndex);

		// If we have the maximum number of 
		// threads running wait for a thread
		// to complete
		if(threadCount >=tMAX){
			printf("stuck in here\n");
			if(threadWait  == tMAX){
				threadWait = 0;
			}
			pthread_join(t[threadWait],NULL);
			threadIndex = threadWait;
			++threadWait;
			if(threadWait == tMAX){
				threadWait = 0;
			}
			--threadCount;
					
		}// end threadCount >= tMAX
		
		// save the socket of the sensor that just
		// came in
		threadData[threadIndex].socketFD = connected;


		//------------Set up Time Out for recving from SENSOR--------------------
		struct timeval tvSensor;
		tvSensor.tv_sec = 540;// 9 min
		tvSensor.tv_usec = 0;
		setsockopt((*threadData).socketFD, SOL_SOCKET, SO_RCVTIMEO, 
			       (const char*)&tvSensor, sizeof tvSensor);
		//------------Done setting up Time Out----------------

		// Create a Thread
		if(pthread_create(&t[threadIndex],NULL, getData, &threadData[threadIndex]) !=0){
			perror("error making thread");
		}else{ //created thread successfully
			printf("Made successfully\n");

			// increment variables 
			pthread_mutex_lock(&mainMutex);
				++threadCount;
				++threadIndex;
			pthread_mutex_unlock(&mainMutex);

		}//end else Thread created

	}// end while(accept())

	//   Free malloced Data
	//  (but we never get here)
	for(i = 0; i< tMAX;++i){
		if (threadData[i].buffer != NULL){
			free(threadData[i].buffer);
		}
	}
	return 0;
} //end main()


//           createConn()
// @param: port
//
// This function establishes a connection at
// the specified port
void createConn(int port){
	//crate a socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	
	//check for errors
	if(socketFD <0){
		printf("Error: Can't make a socket\n");
		exit(1);
	}

	//set connection to TCP
	server.sin_family = AF_INET; 

	//assigns port number
	server.sin_port = htons(port);

	//sets addr to any interface
	server.sin_addr.s_addr = htons(INADDR_ANY);
	int option = 1;
	setsockopt(socketFD,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &option,sizeof(option));
	
	//bind server information to socket
	if(bind(socketFD, (struct sockaddr *) &server, sizeof(server)) < 0){
		printf("can't bind\n");
		exit(1);
	}

	//start listening for clients, on the socket we made
	//and listen for up to 501 clients at a time
	listen(socketFD,501);

}



//       getData()
//
// @param: tData
//
// This function is called whenever a new sensor
// has data to send. This function gets the data
// from the sensors and decides what to do with it
void* getData(void* tData){
	printf("NEW THREAD\n");
	tdata *threadData = (tdata*) tData;
	memset((*threadData).buffer,0,MAX);	

	
	// Get File size
	int size;
	if(read((*threadData).socketFD, &size, sizeof(int)) <= 0){
		perror("can't recv from micro controller");
		pthread_exit(NULL);
	}	
	printf("      GOT FROM Micro Controller: \n[%i]\n", size);
	char* msg = "ACK";
	if(send((*threadData).socketFD,msg,sizeof(char)*strlen(msg), 0) < 0){
		perror("Failed to send");
	}



	// Get File Name
	char filename[MAX];
	if(read((*threadData).socketFD, filename, sizeof(char) * MAX) <= 0){
		perror("can't recv from micro controller");
		pthread_exit(NULL);
	}
	printf("FILE NAME is: [%s]\n", filename);
	//char* msg = "ACK";
	if(send((*threadData).socketFD,msg,sizeof(char)*strlen(msg), 0) < 0){
		perror("Failed to send");
	}


	// Get the picture
	int BUFSIZE = 100;
	// int new_sock = (*threadData).socketFD;
	
	
	//Read Picture Byte Array and Copy in file
	printf("Reading Picture Byte Array\n");
	char p_array[BUFSIZE];
	FILE *image = fopen(filename, "w");
	int nb = read((*threadData).socketFD, p_array, BUFSIZE);
	while (nb > 0) {
		fwrite(p_array, 1, nb, image);
		nb = read((*threadData).socketFD, p_array, BUFSIZE);
	}
	fclose(image);
	printf("Sending email...\n");
	// Now send e-mail
	char dest[BUFSIZE];
	memset(dest, 0, BUFSIZE);
	strncpy(dest, "python my_email.py ", strlen("python my_email.py "));
	strncat(dest, filename, strlen(filename));
	printf("About to execute: [%s]\n", dest);
	system(dest);
}