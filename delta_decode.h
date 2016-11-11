#ifndef DELTA_DECODE_H
#define DELTA_DECODE_H


#include "bytehandler.h"
#include "bithandler.h"
#include "tree.h"


typedef struct deltadecoder {
	char inputbuffer[MAX_BUFFERSIZE]; 
	unsigned int inputbuffer_index; 
	unsigned long long previous_number; 
	bytewriter* writer;
} deltadecoder;

/**
A variation to the huffman decoder. This will huffman decode a block AND delta decode this block afterwards. 
*/
void specific_huffman_decode(bitreader* reader, deltadecoder* decoder);
void delta_decode(deltadecoder* decoder);
void write_long(bytewriter* writer, unsigned long long number);

deltadecoder* init_deltadecoder(bytewriter* writer);
void finish_deltadecoder(deltadecoder* decoder);
unsigned long long read_number(deltadecoder* reader);


#endif