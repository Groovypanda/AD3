#ifndef DELTA_ENCODE_H
#define DELTA_ENCODE_H

#include "bytehandler.h"
#include "bithandler.h"

/**
	Encodes the file with delta encoding AND huffman encoding.
	@param reader A bytereader with the input. 
	@param writer A bitwriter for the output.
*/
void delta_encode(bytereader* reader, bitwriter* writer);

/**
	Concatenates 2 long longs.
	@param number1, number2 The 2 longs which have to be concatenated.
	@return The concatenated value. 
*/
long long concatenate(long long number1, long long number2);

/**
	Reads an unsigned long long from the buffer and sets the current and previous number correctly. 
	@param buffer The output buffer
	@param reader A reader with the input
	@param current_number The last number which was read.
	@param previous_number The number before current_number.
	@return delta: the difference between the last number read and current_number. 
*/
unsigned long long read_long(char* buffer, bytereader* reader, unsigned long long* current_number, unsigned long long* previous_number);

#endif