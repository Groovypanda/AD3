#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "errorhandler.h"
#include "text.h"
#include "tree.h"

typedef struct bytewriter {
	FILE* ofp;
	//Value of byte at this moment
	unsigned char byte;
	//Amount of bits to fill
	unsigned int remaining_bits;
	//All bytes which have to bee written.
	unsigned char* bytes; 
	//Max amount of bytes. 
	unsigned int buffersize;
	//Amount of current bytes
	unsigned int length;
} bytewriter;

typedef struct bytereader {
	unsigned char* bytes;
	unsigned int index;
	//Remaining bits on current index.
	unsigned int remaining_bits_amount;
} bytereader;

void write_tree(bytewriter* writer, tree* t);

tree* read_tree(bytereader* reader);

text read_file(char* filename);

//Returns bytes of binary file. 
unsigned char* read_binary_file(char* filename);
void print_binary_file(char* filename);

void write_bits(bytewriter* b, int bits, unsigned int amount);

unsigned int read_bits(bytereader* reader, unsigned int amount);

bytewriter* init_bytewriter(char* filename);

bytereader* init_bytereader(char* filename);

void free_bytewriter(bytewriter* writer);

void free_bytereader(bytereader* reader);

#endif

