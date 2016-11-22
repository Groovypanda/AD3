#include "delta_encode.h"


void delta_encode(bytereader* reader, bitwriter* writer) {
	unsigned char* buffer = reader->buffer;
	unsigned int out_buffer_index = 0; 
	unsigned char out_buffer[MAX_BUFFERSIZE];
	unsigned long long previous_number = 0, current_number, delta; 
	//This loop will encode all the data of the input file. (Not only one buffer, it continues reading into the buffer 
	//until the full file is encoded. 
	while (*buffer) { 
		if (isdigit(*buffer)) {
			delta = read_long(&buffer, reader, &current_number, &previous_number); //Calculate the delta.
			write_number(out_buffer, &out_buffer_index, writer, delta); //Add the number to the buffer. 
		}
		else { //If it's not a digit, it's not encoded. 
			buffer++;
		}
		if (!*buffer) {
			read_block(reader);
			buffer = reader->buffer;
		}
	}
	huffman_encode_block(out_buffer, out_buffer_index, writer); //Encode the block once all delta's in a buffer are calculated. 
	
}

unsigned long long concatenate(unsigned long long number1, unsigned long long number2) {
	unsigned long long exp = 10;
	while (exp <= number2) {
		exp *= 10;
	}
	return number1*exp + number2;
}

unsigned long long read_long(unsigned char** buffer, bytereader* reader, unsigned long long* current_number, unsigned long long* previous_number) {
	*current_number = strtoll((char*) *buffer, (char**) buffer, 10); //Read a number from the input.  
	unsigned long long delta = *current_number - *previous_number;  //Calculate the delta value
	if (!*(*buffer)) { //If the buffer is empty, read a new block. 
		read_block(reader);
		*buffer = reader->buffer;
		if (isdigit(*(*buffer))) { //Calculate actual delta if the buffer ended while reading the number
			while (*(*buffer) == '0') { //Add zero's the incomplete number if necessary
				*current_number *= 10;
				(*buffer)++;
			}
			unsigned long long numberend = strtoll((char*) *buffer, (char**) buffer, 10); 
			if (numberend != 0) { //if numberend is 0 it means nothing was read by strtoll.
				*current_number = concatenate(*current_number, numberend); //Append the numbers which weren't read in the initial strtoll.
			}
			delta = *current_number - *previous_number; //Calculate the real delta
		}
	}
	*previous_number = *current_number;
	return delta;
}

void write_number(unsigned char* out_buffer, unsigned int* out_buffer_index, bitwriter* bitwriter, unsigned long long delta) {
	unsigned long long value = delta;
	//Calculate amount of bits in delta. (Amount of times 7 bits) 
	int amount_7bits = 0;
	while (value) { //Calculate the amount of groups with 7 bits
		value >>= 7; 
		amount_7bits++;
	}
	for (int i = amount_7bits; i > 1; i--) { //Place all the groups in the buffer
		out_buffer[(*out_buffer_index)++] = ((delta >> (i - 1) * 7) & 0x7F) | 128; //If there's another group following, a group starts with 1. The group is calculated with the shift (i-1)/7 
		if (*out_buffer_index == MAX_BUFFERSIZE) { //If the buffer is full, encode the block with huffman.
			*out_buffer_index = 0;
			huffman_encode_block(out_buffer, MAX_BUFFERSIZE, bitwriter);
		}
	}
	out_buffer[(*out_buffer_index)++] = delta & 0x7F; //Add the last 7 bits to the buffer, now the first bit should be zero as there aren't anymore groups following.
	if (*out_buffer_index == MAX_BUFFERSIZE) { //Again, if the buffer is full, it should be encoded.
		*out_buffer_index = 0;
		huffman_encode_block(out_buffer, MAX_BUFFERSIZE, bitwriter);
	}
}