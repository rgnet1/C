//      My Bubble sort example
#include <stdio.h> 
#include "basicArrayFuncs.c"



// Driver program to test above functions 
int main() 
{ 
	int arr[] = {64, 34, 25, 12, 22, 11, 90}; 
	int n = len(arr);
	printf("len is %i\n", n);
	bubbleSort(arr, n);
	printf("Sorted array: \n");
	printArray(arr, n);
	return 0;
} 