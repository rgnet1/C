// Basic functions that are re-usable for arrays
#include <string.h>
#define MAX 100

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

// Denine len()
#define len(array) (sizeof((array)) / sizeof((array)[0]));

// A function to implement bubble sort integers
void bubbleSortInt(int arr[], int n) {
  int i, j;
  for (i = 0; i < n - 1; i++) {
    // Last i elements are already in place
    for (j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) swap(&arr[j], &arr[j + 1]);
    }
  }
}

//     bubbleSortString()
//
// A bubble sort algorithm to sort strings
//
// @param: arr - Array of strings (MAX of 100 chars per string)
// @param: int n - the size of the array
void bubbleSortString(char arr[][MAX], int n) {
  char temp[MAX];
  // Sorting strings using bubble sort
  for (int j = 0; j < n - 1; j++) {
    for (int i = j + 1; i < n; i++) {
      if (strcmp(arr[j], arr[i]) > 0) {
        strcpy(temp, arr[j]);
        strcpy(arr[j], arr[i]);
        strcpy(arr[i], temp);
      }
    }
  }
}

//         insertion sort()
void insertionSortInt(int arr[], int arrLen) {
  int key, j;
  for (int i = 1; i < arrLen - 1; ++i) {
    key = arr[i];
    j = i - 1;

    // Move each element greater than key to the right
    // of current position
    while (arr[j] > key && j >= 0) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
}

/* Function to print an array */
void printArrayInt(int arr[], int size) {
  int i;
  for (i = 0; i < size; i++) printf("%d ", arr[i]);
  printf("\n");
}

void printArrayString(char arr[][MAX], int size) {
  int i;
  for (i = 0; i < size; i++) printf("%s ", arr[i]);
  printf("\n");
}