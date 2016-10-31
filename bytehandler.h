#ifndef BYTEHANDLER_H
#define BYTEHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include "errorhandler.h"

#define MAX_BUFFERSIZE 16384 //buffersize of 16 KiB

typedef struct bytereader {
	unsigned long text_length; //length of current text; 
	unsigned long total_size; //length of total text;
	unsigned char buffer[MAX_BUFFERSIZE + 1];
	FILE* ifp;
} bytereader;

typedef struct bytewriter {
	unsigned long index;
	char buffer[MAX_BUFFERSIZE];
	FILE* ofp;
} bytewriter;

int read_bytes(bytereader* reader);

void write_byte(bytewriter* writer, char c);

void flush_bytes(bytewriter* writer);

bytereader* init_bytereader(char* filename, char* mode);

bytewriter* init_bytewriter(char* filename);

void free_bytereader(bytereader* reader);

void free_bytewriter(bytewriter* writer);

#endif 