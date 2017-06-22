#------------------------------------------------------------------------------
#  Makefile for Graph Theory (BFS)
#
#  make                     makes FindPath
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on in3
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

all : FindPath GraphTest GraphClient

FindPath : FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

FindPath.o : FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

Graph.o : Graph.c Graph.h
	gcc -c -std=c99 -Wall Graph.c
List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	$(REMOVE) FindPath GraphClient GraphTest FindPath.o GraphClient.o GraphTest.o $(BASE_OBJECTS)

checkFind : FindPath
	$(MEMCHECK) FindPath in3 junk3

checkClient : GraphClient
	$(MEMCHECK) GraphClient
