#Makefile

all : server ./client/client

server: server.c server.h
	gcc -pthread -I -Wall server.c -o server

client: ./client/client.c
	gcc -Wall client.c -o client

# checkin: checkin.c
# 	gcc -Wall checkin.c -o checkin

# run: client server
# 	./server 1111

clean:
	rm server
	rm ./client/client
