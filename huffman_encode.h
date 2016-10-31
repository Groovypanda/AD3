#ifndef HUFFMAN_ENCODE_H
#define HUFFMAN_ENCODE_H

#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "pqueue.h"
#include "bithandler.h"
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

unsigned int* create_frequency_list(char* text, unsigned int length);

void init_code(code_list** codes, node* currentnode, int currentcode, unsigned int currentlength);

code_list** init_codes(tree* t);

void free_code_list(code_list** codes);

//Returns amount of written bits.
void write_code_list(bitwriter* writer, code_list* list);

void print_byte(unsigned char byte);

#endif