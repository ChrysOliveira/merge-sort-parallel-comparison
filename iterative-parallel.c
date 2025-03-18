#include "iterative-parallel.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>

void merge_iterative_parallel(int arr[], int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  int *L = (int *)malloc(n1 * sizeof(int));
  int *R = (int *)malloc(n2 * sizeof(int));

  for (int i = 0; i < n1; i++) {
    L[i] = arr[left + i];
  }
  for (int j = 0; j < n2; j++) {
    R[j] = arr[mid + 1 + j];
  }

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k++] = L[i++];
    } else {
      arr[k++] = R[j++];
    }
  }
  while (i < n1) {
    arr[k++] = L[i++];
  }
  while (j < n2) {
    arr[k++] = R[j++];
  }

  free(L);
  free(R);
}

void mergeSort_iterative_parallel(int arr[], int n) {
  for (int curr_size = 1; curr_size < n; curr_size *= 2) {

#pragma omp parallel for
    for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
      int mid = left_start + curr_size - 1;
      int right_end = left_start + (2 * curr_size) - 1;

      if (mid >= n) {
        mid = n - 1;
      }
      if (right_end >= n) {
        right_end = n - 1;
      }

      merge_iterative_parallel(arr, left_start, mid, right_end);
    }
  }
}

double execution_iterative_parallel(int array_size) {
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

  mergeSort_iterative_parallel(arr, arr_size);

  double end = omp_get_wtime();

  /* printf("\nSorted array is: \n"); */
  /* for (int i = 0; i < arr_size; i++) { */
  /*   printf("%d ", arr[i]); */
  /* } */
  /* printf("\n"); */

  double time_taken = end - start;
  /* printf("Time taken (iterative-parallel): %f\n", time_taken); */
  return time_taken;
}
