#ifndef PQUEUE_H
#define PQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "errorhandler.h"


typedef struct pqueue {
	tree** list;
	unsigned int length;
	unsigned int size;
} pqueue;

void init_pqueue(pqueue* p);
tree* pop_pqueue(pqueue* p);
void push_pqueue(pqueue* p, tree* t);
void print_pqueue(pqueue* p);
void fill_pqueue(unsigned int* frequencies, pqueue* queue);

#endif