#ifndef BITHANDLER_H
#define BITHANDLER_H

#include "bytehandler.h"

typedef struct bitwriter {
	bytewriter* bytewriter;
	//Value of byte at this moment
	unsigned char byte;
	//Amount of bits to fill
	unsigned int remaining_bits;	
} bitwriter;

typedef struct bitreader {
	bytereader* bytereader;
	//Current index of the bytereader
	unsigned long index;
	//Remaining bits on current index.
	unsigned int remaining_bits_amount;
} bitreader;

void write_bits(bitwriter* b, int bits, unsigned int amount);

unsigned int read_bits(bitreader* reader, unsigned int amount);

void flush_bits(bitwriter* reader);

bitwriter* init_bitwriter(char* filename);

bitreader* init_bitreader(char* filename);

void free_bitwriter(bitwriter* writer);

void free_bitreader(bitreader* reader);

#endif 
