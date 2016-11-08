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

#endif