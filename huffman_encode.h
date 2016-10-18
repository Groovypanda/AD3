#ifndef HUFFMAN_ENCODE_H
#define HUFFMAN_ENCODE_H

#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "pqueue.h"
#include "filehandler.h"
#include "errorhandler.h"
//For testing purposes
#include "statistics.h"

typedef struct code {
	int code;
	unsigned int length;
} code;

//This function returns the encoded huffman tree. 
void encode(char* input, char* filename);

tree* build_tree(unsigned int* frequencies);

unsigned int* create_frequency_list(text input);

void init_code(code* codes, node* currentnode, int currentcode, unsigned int currentlength);

code* init_codes(tree* t);

#endif