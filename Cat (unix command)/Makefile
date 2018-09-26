#             Makefile for a C program
#
# This file automates the build and romoval of mycat execcuable files
#
# Ramzey Ghanaim

# Source code should be in the variable: "SRC".
# This makefile can be re-used simply by 
# changing the source file variable bellow. 
SRC = mycat

all: ${SRC}

check : ${SRC}
	valgrind -v --leak-check=full
mycat : ${SRC}.c
	cc -g -O0 -Wall -Wextra -std=c99 -o mycat mycat.c	
clean : ${SRC}
	rm mycat

