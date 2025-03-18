#include "iterative-parallel.h"
#include "iterative-sequential.h"
#include "recursive-parallel.h"
#include "recursive-sequential.h"
#include <omp.h>
#include <stdio.h>

void execution(int n_threads) {
  int execs = 10;
  int array_size = 1000000;

  double r_recursive_parallel = 0.0f;
  double r_recursive_sequential = 0.0f;
  double r_iterative_sequential = 0.0f;
  double r_iterative_parallel = 0.0f;

  for (int i = 0; i < execs; i++) {
    r_recursive_parallel += execution_recursive_parallel(array_size);
  }

  for (int i = 0; i < execs; i++) {
    r_recursive_sequential += execution_recursive_sequential(array_size);
  }

  for (int i = 0; i < execs; i++) {
    r_iterative_sequential += execution_iterative_sequential(array_size);
  }

  for (int i = 0; i < execs; i++) {
    r_iterative_parallel += execution_iterative_parallel(array_size);
  }

  printf(
      "Average time taken per execution (recursive-parallel %d threads): %f\n",
      n_threads, r_recursive_parallel / execs);
  printf("Average time taken per execution (recursive-sequential %d threads): "
         "%f\n",
         n_threads, r_recursive_sequential / execs);
  printf(
      "Average time taken per execution (iterative_parallel %d threads): %f\n",
      n_threads, r_iterative_parallel / execs);
  printf("Average time taken per execution (iterative_sequential %d threads): "
         "%f\n",
         n_threads, r_iterative_sequential / execs);
}

int main() {

  omp_set_num_threads(2);
  execution(2);

  printf("\n");

  omp_set_num_threads(4);
  execution(4);

  printf("\n");

  omp_set_num_threads(8);
  execution(8);

  printf("\n");

  omp_set_num_threads(16);
  execution(16);

  return 0;
}
