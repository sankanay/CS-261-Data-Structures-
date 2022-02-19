/*
 * In this file, you should implement an application that compares the
 * performance of a dynamic array and a linked list, as described in the
 * README. Don't forget to include your name and @oregonstate.edu email
 * address below.
 *
 * Name: Yash Sankanagouda
 * Email: sankanay@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>

#include "dynarray.h"
#include "list.h"
#include <time.h>

#define TEST_DATA_SIZE 1000000

/*
 * This function generates and an array of random integers of size n.
 */
int* generate_random_array(int n) {
  int* arr = malloc(n * sizeof(int));
  int i;

  for (i = 0; i < n; i++) {
    arr[i] = rand();
  }

  return arr;
}

int main(int argc, char const *argv[]) {
  int* test_data = generate_random_array(TEST_DATA_SIZE);

  /*
   * You should write code here to insert the data in test_data into a
   * dynamic array using the dynamic array interface you implemented.  As
   * you're doing this, measure two things:
   *   1. The total amount of time it takes to insert all the data into the
   *      dynamic array.
   *   2. The maximum amount of time it takes to insert any single element into
   *      the dynamic array.
   * To help with this, you can use the C functions time() and difftime()
   * from time.h.  Don't forget to include time.h above!
   */
  printf("\n");

  clock_t start, end;
  clock_t s, e;
  double diff_a, diff_b;

  start = clock();
  struct dynarray* da = dynarray_create();
  for (int i = 0; i < TEST_DATA_SIZE; i++) {
    s = clock();
    dynarray_insert(da, &test_data[i]);
    e = clock();
    double diff = ((double) (e - s)) / CLOCKS_PER_SEC;
    if(diff > diff_a){
      diff_a = diff;
    }
  }
  end = clock();
  diff_b = ((double) (end - start)) / CLOCKS_PER_SEC;
  
  printf("Total time dynarray: %f\n", diff_b);
  printf("Max time dynarray: %f\n", diff_a);
  dynarray_free(da);

  printf("***********************************************************\n");

   /*
    * You should write code here to insert the data in test_data into a
    * linked list using the linked list interface you implemented.  As
    * you're doing this, measure two things:
    *   1. The total amount of time it takes to insert all the data into the
    *      linked list.
    *   2. The maximum amount of time it takes to insert any single element into
    *      the linked list.
    * Again, you can use the C functions time() and difftime() from time.h to
    * help with this.
    *
    * How do the times associated with the dynamic array compare to the times
    * associated with the linked list?  How does this change if you modify the
    * value of TEST_DATA_SIZE above?
    */

  start = clock();
  struct list* l = list_create();
  for (int i = 0; i < TEST_DATA_SIZE; i++) {
    s = clock();
    list_insert(l, &test_data[i]);
    e = clock();
    double diff = ((double) (e - s)) / CLOCKS_PER_SEC;
    if(diff > diff_a){
      diff_a = diff;
    }
  }
  end = clock();
  diff_b = ((double) (end - start)) / CLOCKS_PER_SEC;
  
  printf("Total time linked list: %f\n", diff_a);
  printf("Max time linked list: %f\n", diff_b);
  list_free(l);
  free(test_data);
  printf("\n");

  return 0;
}
