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
	unsigned int code_length;
} code;

typedef struct code_list {
	code* codes;
	unsigned int list_length; 
} code_list;

//This function returns the encoded huffman tree. 
void encode(char* input, char* filename);

tree* build_tree(unsigned int* frequencies);

unsigned int* create_frequency_list(text input);

void init_code(code_list** codes, node* currentnode, int currentcode, unsigned int currentlength);

code_list** init_codes(tree* t);

//Returns amount of written bits.
unsigned int write_code_list(bytewriter* writer, code_list* list);

#endif