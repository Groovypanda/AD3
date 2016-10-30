#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "errorhandler.h"
#include "tree.h"


#define MAX_BUFFERSIZE 16384 //buffersize of 1 KiB

typedef struct bytewriter {
	FILE* ofp;
	//Value of byte at this moment
	unsigned char byte;
	//Amount of bits to fill
	unsigned int remaining_bits;
	//All bytes which have to be written.
	unsigned char buffer[MAX_BUFFERSIZE]; 
	//Amount of current bytes
	unsigned int length;
} bytewriter;

typedef struct textreader {
	unsigned long text_length; //length of current text; 
	unsigned long total_size; //length of total text;
	char buffer[MAX_BUFFERSIZE+1]; 
	FILE* ifp;
} textreader;

typedef struct bytereader {
	textreader* textreader;
	//Current index
	unsigned long index;
	//Remaining bits on current index.
	unsigned int remaining_bits_amount;
} bytereader;

typedef struct textwriter {
	unsigned long index;
	char buffer[MAX_BUFFERSIZE];
	FILE* ofp; 
} textwriter;

void write_tree(bytewriter* writer, tree* t);

tree* read_tree(bytereader* reader);

int read_file(textreader* reader);

void write_bits(bytewriter* b, int bits, unsigned int amount);

void write_char(textwriter* writer, char c);

void flush(textwriter* writer);

unsigned int read_bits(bytereader* reader, unsigned int amount);

bytewriter* init_bytewriter(char* filename);

bytereader* init_bytereader(char* filename);

textreader* init_textreader(char* filename, char* mode);

textwriter* init_textwriter(char* filename);

void free_bytewriter(bytewriter* writer);

void free_bytereader(bytereader* reader);

void free_textreader(textreader* reader);

void free_textwriter(textwriter* writer);


#endif

