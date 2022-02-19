/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Yash Sankanagouda  
 * Email: sankanay@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
//struct pq;

struct pq {
  struct dynarray* da_val;
  struct dynarray* da_prior;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {

  struct pq* pq = (struct pq*)malloc(sizeof(struct pq));
  pq->da_val = dynarray_create();
  pq->da_prior = dynarray_create();
  return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq){
  
  dynarray_free(pq->da_val);
  dynarray_free(pq->da_prior);
  free(pq);
  return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {

  if(dynarray_size(pq->da_val) == 0){
    return 1;
  }
  else{
    return 0;
  }
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */

void pq_insert(struct pq* pq, void* value, int priority){

  assert(pq);
  int* pri = (int*)malloc(sizeof(int));
  *pri = priority;
  int end = dynarray_size(pq->da_val);
  dyn_insert(pq->da_val, end, value);
  dyn_insert(pq->da_prior, end, pri);
  swap_node_up(pq, end - 1);

  return;
}

void swap_node_up(struct pq* pq, int idx){

  assert(pq);
  
  int parent = (idx - 1) / 2;
  if(idx && (*((int*)dynarray_get(pq->da_prior, parent))) > (*((int*)dynarray_get(pq->da_prior, idx)))){
    swap(pq, parent, idx);
    swap_node_up(pq, parent);
  }
}


void swap(struct pq* pq, int p, int i){

  assert(pq);
  void* val = dynarray_get(pq->da_val, p);
  void* priority = dynarray_get(pq->da_prior, p);
  dynarray_set(pq->da_val, p, dynarray_get(pq->da_val, i));
  dynarray_set(pq->da_prior, p, dynarray_get(pq->da_prior, i));
  dynarray_set(pq->da_val, i, val);
  dynarray_set(pq->da_prior, i, priority);
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  assert(pq);
  return dynarray_get(pq->da_val, 0);
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  assert(pq);
  int* p = dynarray_get(pq->da_prior, 0);
  return *p;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  
  assert(pq);
  void* first = dynarray_get(pq->da_val, 0);
  int last_idx = dynarray_size(pq->da_val) - 1;
  swap(pq, 0, last_idx);
  free(dynarray_get(pq->da_prior, last_idx));
  dynarray_remove(pq->da_val, last_idx);
  dynarray_remove(pq->da_prior, last_idx);
  if(dynarray_size(pq->da_val) > 0){
    swap_node_down(pq, 0);
  }
  return first;
}

void swap_node_down(struct pq* pq, int idx){

  assert(pq);
  int lowest_pri = idx;
  int lidx = 2 * idx + 1;
  int ridx = 2 * idx + 2;
  if(lidx < dynarray_size(pq->da_val) && (*((int*)dynarray_get(pq->da_prior, lidx))) < (*((int*)dynarray_get(pq->da_prior, idx)))){
    lowest_pri = lidx;
  }
  if(ridx < dynarray_size(pq->da_val) && (*((int*)dynarray_get(pq->da_prior, ridx))) < (*((int*)dynarray_get(pq->da_prior, lowest_pri)))){
    lowest_pri = ridx;
  }
  if(lowest_pri != idx){
    swap(pq, idx, lowest_pri);
    swap_node_down(pq, lowest_pri);
  }
}


