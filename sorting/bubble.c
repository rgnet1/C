//      My Bubble sort example
#include <stdio.h>
#include "basicArrayFuncs.c"

// Driver program to test above functions
int main() {
  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  int n = len(arr);
  printf("len is %i\n", n);
  bubbleSortInt(arr, n);
  printf("Sorted ints with BubbleSort: \n");
  printArrayInt(arr, n);

  // MAX is 100, defined in basicArrayFuncs.c
  char arrStr[][MAX] = {"Watch", "Those", "Wrist", "Rockets", "Please"};
  n = len(arrStr);
  printf("len is %i\n", n);
  bubbleSortString(arrStr, n);
  printf("Sorted String with BubbleSort: \n");
  printArrayString(arrStr, n);

  // Insertion Sort test
  int arr2[] = {64, 34, 25, 12, 22, 11, 90};
  n = len(arr);
  insertionSortInt(arr, n);
  printf("Insertion Sort Result: ");
  printArrayInt(arr, n);
  return 0;
}