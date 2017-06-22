#             Makefile
# This file automates the build and romoval of mycat execcuable files
#
# Ramzey Ghanaim

all: mycat

check : mycat
	valgrind -v --leak-check=full
mycat : mycat.c
	cc -g -O0 -Wall -Wextra -std=c99 -o mycat mycat.c	
clean : mycat
	rm mycat
