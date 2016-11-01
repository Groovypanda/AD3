#ifndef PQUEUE_H
#define PQUEUE_H

/**
	popqueue.h
	A priority queue data structure implemented as a binary heap for saving binary trees. 
*/

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "errorhandler.h"

/**
	A struct for representing a priority queue. 
*/
typedef struct pqueue {
	tree** list; //A list of tree pointers. 
	unsigned int length; //The amount of trees in the list. 
	unsigned int size; //The total size of the list. 
} pqueue;

/**
	Initialize a new priority queue. 
	@param p The priority queue which should be initialized. 
*/
void init_pqueue(pqueue* p); 

/**
	Pop a tree from the priority queue. 
	@param p The priority queue from which a tree should be popped. 
	@return The first tree pointer in the priority queue. 
*/
tree* pop_pqueue(pqueue* p);

/**
	Push a tree on the priority queue. 
	@param p The priority queue to which the tree should be pushed. 
	@param t The tree which should be pused.
*/
void push_pqueue(pqueue* p, tree* t);

/**
	Displays a priority queue. 
	@param p The priority queue which should be printed. 
*/
void print_pqueue(pqueue* p);

/**
	Fills the priority queue by making trees from the given frequencies. 
	@param frequencies The frequencies of which trees will be created which then will be pushed. 
*/
void fill_pqueue(unsigned int* frequencies, pqueue* queue);

/**
	A help function for the priority queue operations. 
	@param p The priority queue in which we will percolate down. 
	@param spot The spot from where the binary heap will percolate down. 
*/
void percolate_down(pqueue* p, unsigned int spot);


#endif