#include "recursive-sequential.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge_recursive_sequential(int arr[], int left, int mid, int right) {
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;

  int *L = (int *)malloc(n1 * sizeof(int));
  int *R = (int *)malloc(n2 * sizeof(int));

  for (i = 0; i < n1; i++) {
    L[i] = arr[left + i];
  }
  for (j = 0; j < n2; j++) {
    R[j] = arr[mid + 1 + j];
  }

  i = 0;
  j = 0;
  k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }

  free(L);
  free(R);
}

void mergeSort_recursive_sequential(int arr[], int left, int right) {
  if (left < right) {
    int size = (right - left + 1);
    int mid = left + (right - left) / 2;

    mergeSort_recursive_sequential(arr, left, mid);
    mergeSort_recursive_sequential(arr, mid + 1, right);
    merge_recursive_sequential(arr, left, mid, right);
  }
}

double execution_recursive_sequential(int array_size) {
  srand(time(NULL));

  int arr[array_size];

  for (int i = 0; i < array_size; i++) {
    arr[i] = rand() % 1000;
  }

  int arr_size = sizeof(arr) / sizeof(arr[0]);

  /* printf("Given array is: \n"); */
  /* for (int i = 0; i < arr_size; i++) { */
  /*   printf("%d ", arr[i]); */
  /* } */
  /* printf("\n"); */

  double start = omp_get_wtime();

  mergeSort_recursive_sequential(arr, 0, arr_size - 1);
  double end = omp_get_wtime();

  /* printf("\nSorted array is: \n"); */
  /* for (int i = 0; i < arr_size; i++) { */
  /*   printf("%d ", arr[i]); */
  /* } */
  /* printf("\n"); */

  double time_taken = end - start;
  /* printf("Time taken (recursive-sequential): %f\n", time_taken); */
  return time_taken;
}
