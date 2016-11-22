#ifndef DELTA_ENCODE_H
#define DELTA_ENCODE_H

/**
delta_decode.h
Encodes a file with the delta encoding algorithm and the huffman encoding algorithm. 
*/

#include "bytehandler.h"
#include "bithandler.h"

/**
	Encodes the file with delta encoding AND huffman encoding. The delta encoder reads a number and computes the difference with the previously read number, 
	this difference, delta. The delta values will be encoded with huffman afterwards. The delta's are formatted with Variable-length quantitiy to minimize the amount of bits
	used for this number. A VLQ is a code to represent a number. It works the following way: 
	- Split the number in groups op 7 bits. 
	- At the start of every group a 1 is added to the start of the group if another group of 7 bit follows, otherwise, a 0 is added. 
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
unsigned long long read_long(char** buffer, bytereader* reader, unsigned long long* current_number, unsigned long long* previous_number);

/**
	Write a number into the given buffer. The given number will be formatted as a VLQ code the out_buffer. Once the buffer is full, the out_buffer will be huffman encoded. 
	@param out_buffer The out_buffer which will be encoded once the MAX_BUFFERSIZE is reached. 
	@param out_buffer_index The current index in the out_buffer. This will be adjusted in this function.
	@param bitwriter The bitwriter used for the huffman encoding
	@param delta The value of the delta number which has to be huffman encoded. 
*/
void write_number(char* out_buffer, unsigned int* out_buffer_index, bitwriter* bitwriter, unsigned long long delta);

#endif