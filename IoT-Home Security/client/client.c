#define MAX 10000//128000
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <netdb.h>

char ip[50];
char msg[100];

struct sockaddr_in server;
int makeConn(int port){
	//crate a socket
	int socketFD = socket(AF_INET, SOCK_STREAM, 0);
	
	//check for errors
	if(socketFD <0){
		printf("Error: Can't make a socket\n");
		exit(1);
	}
	
	//set up attributes
	server.sin_family = AF_INET; //set connection to TCP
	server.sin_port = htons(port); //assigns port number
	
	struct hostent *host;
	struct sockaddr_in data_addr;
	strcpy(ip,"127.0.0.1");
	host = gethostbyname(ip);
					
	// check for errors
    if (host == NULL) {
        printf("Host error\n");
        exit(0);
    }
	
	inet_pton(AF_INET, ip, &data_addr.sin_addr);
	
	struct in_addr **address;
	address = (struct in_addr **) host->h_addr_list;
	char dest[100];
	strcpy(dest,inet_ntoa(*address[0]));
	inet_pton(AF_INET,dest,&(data_addr.sin_addr));
	
	//server.sin_addr.s_addr = htons(atoi(ip));//sets addr to any interface
	int option = 1;
	setsockopt(socketFD,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &option,sizeof(option));
	
	if(connect(socketFD, (struct sockaddr *)&server, sizeof(server))<0){
		perror("Failed to connect");
		exit(1);
	}
	return socketFD;
	
}

int main(int argc, char* argv[]){
	//strcpy(msg, temp);
	int port;
	printf("argc is : %i", argc);
	if(argc ==3 ){
		port = atoi(argv[1]);
	}
	else{
		printf("format: ./client <port> <file>\n");
		exit(1);
	}
	
	if(port < 0){
		printf("Error, wrong port");
		exit(1);
	}
	
    

	int sock = makeConn(port);
	//strcat(msg,argv[3]);
	char * picture_name = argv[2];
    printf("Getting Picture Size\n");
    FILE *picture;
    picture = fopen(argv[2], "r");
    int size;
    fseek(picture, 0, SEEK_END);
    size = ftell(picture);
    fseek(picture, 0, SEEK_SET);
	
    printf("About to send [%s]\n",msg );
	if(send(sock,&size,sizeof(size), 0) < 0){
		perror("Failed to send");
	}
    printf("Waiting to get ack...\n");
    char buff[MAX];
    memset(buff,0,MAX);
    if(recv(sock,buff,MAX,0) < 0){
        perror("Failed to recv");
    }

	// Send Filename
	printf("About to send [%s]\n",picture_name );
	if(send(sock,picture_name,strlen(picture_name), 0) < 0){
		perror("Failed to send");
	}

	// Get ack
	printf("Waiting to get ack...\n");
    // char buff[MAX];
    memset(buff,0,MAX);
    if(recv(sock,buff,MAX,0) < 0){
        perror("Failed to recv");
    }

	int BUFSIZE = 100;
   //Send Picture as Byte Array (without need of a buffer as large as the image file)
	printf("Sending Picture as Byte Array\n");
	char send_buffer[BUFSIZE]; // no link between BUFSIZE and the file size
	int nb = fread(send_buffer, 1, sizeof(send_buffer), picture);
	while(!feof(picture)) {
		write(sock, send_buffer, nb);
		nb = fread(send_buffer, 1, sizeof(send_buffer), picture);
		// no need to bzero
	}
	
	printf("DONE SEDNING\n");

	return 0;
}