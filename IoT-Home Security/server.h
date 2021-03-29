#define MAX 10000
#define tMAX 10
#define GETTIMEOUT 120 //120 is 10 min
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <netdb.h>

//          struct tdata
// Data is passed to a particular thread
// via the tdata struct
typedef struct{
	int socketFD;
	char *buffer;
	int index;
}tdata;




//      createConn()
// 
// @param: port
//
// Creates a listening connection at the
// specified port
void createConn(int port);



//       getData()
//
// @param: tData
//
// This function is called whenever a new sensor
// has data to send. This function gets the data
// from the sensors and decides what to do with it
void* getData(void* tData);


