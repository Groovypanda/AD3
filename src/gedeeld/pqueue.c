#include "pqueue.h"

void init_pqueue(pqueue* p) {
	p->length = 0;
	p->size = 2;
	p->list = (tree**)allocate_memory(sizeof(tree*)*p->size);
}

void print_pqueue(pqueue* p) {
	printf("PRIORITY QUEUE WITH LENGTH %d\n", p->length);
	unsigned int frequency = 0;
	for (unsigned int i = 0; i < p->length; i++) {
		printf("%c: %d\n", p->list[i]->root->value, p->list[i]->root->frequency);
		frequency += p->list[i]->frequency;
	}
	printf("THIS QUEUE HAS TOTAL FREQUENCY: %d\n--------\n", frequency);
}

void push_pqueue(pqueue* p, tree* t) {
	if (p->length == 0) {
		p->list[0] = t;
		p->length++;
	}
	else {
		if (p->length >= p->size) {
			p->size *= 2;
			p->list = (tree**)realloc(p->list, p->size*sizeof(tree*));
			if (!p->list) {
				throw_error(MEMORY_ERROR);
			}
		}
		//Place of new element. 
		int spot = p->length;
		//Compare with parent.
		int parent = (int)(spot - 1) / 2;
		//Percolate up
		//Lowest frequencies must be the highest in our heap.
		//If the frequency of the new element is lower is must go up in the heap.
		while (spot > 0 && p->list[parent]->frequency > t->frequency) {
			//Move parent to child to make place for new node. 
			p->list[spot] = p->list[parent];
			spot = parent;
			parent = (int)(spot - 1) / 2;
		}
		p->list[spot] = t;
		p->length++;
	}

}

tree* pop_pqueue(pqueue* p) {
	if (p->length <= 0) {
		printf("Trying to pop while the queue is empty.");
		exit(-1);
	}
	tree* first = p->list[0];
	//Make space for last element, afterwards we perculate down.
	p->list[0] = p->list[--p->length];
	p->list[p->length] = NULL;
	percolate_down(p, 0);
	return first;
}

void percolate_down(pqueue* p, unsigned int spot) {
	unsigned int left = 2 * spot + 1;
	unsigned int right = 2 * spot + 2;
	unsigned int smallest = spot;
	if (left< p->length && p->list[smallest]->frequency > p->list[left]->frequency) {
		smallest = left;
	}
	if (right < p->length && p->list[smallest]->frequency > p->list[right]->frequency) {
		smallest = right;
	}
	if (smallest != spot) {
		tree* tmp = p->list[spot];
		p->list[spot] = p->list[smallest];
		p->list[smallest] = tmp;
		percolate_down(p, smallest);
	}
}

void fill_pqueue(unsigned int* frequencies, pqueue* queue) {
	for (unsigned int i = 0; i < 256; i++) {
		if (frequencies[i]) {
			tree* t = (tree*)allocate_memory(sizeof(tree));
			t->root = (node*)allocate_memory(sizeof(node));
			t->root->left = NULL;
			t->root->right = NULL;
			t->root->value = (char)i;
			t->root->frequency = frequencies[i];
			t->frequency = frequencies[i];
			push_pqueue(queue, t);
		}
	}
}