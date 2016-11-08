#ifndef DELTA_DECODE_H
#define DELTA_DECODE_H


#include "bytehandler.h"
#include "bithandler.h"
#include "tree.h"

typedef struct delta_buffer {
	char buffer[MAX_BUFFERSIZE+1]; //The buffer containing the output. 
	int buffer_index; //The index in the buffer. 
	long long previous_number; //Indicates the last decoded number.
	long long last_number; //Indicates the last number which was read.
	int byte_index; //Indicates the index in a long long number. This is the amount of bytes contained in last_number. 
} delta_buffer;

/**
A variation to the huffman decoder. This will huffman decode a block AND delta decode this block afterwards. 
*/
void specific_huffman_decode(bitreader* reader, bytewriter* writer, delta_buffer* delta_buffer);
void delta_decode(delta_buffer* delta_buffer, bytewriter* writer);

#endif