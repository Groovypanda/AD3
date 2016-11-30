#ifndef ENCODE_H
#define ENCODE_H

/**
	benchmark_encoder.h
	Purpose: Prints benchmarks while encoding.
*/

#include "../src/standaard/standard_coder.h"
#include "../src/specifiek/specific_coder.h"
#include "statistics.h"

/**
Encodes the given file and places the encoded content into the given file.
@param input The name of a file which has to be encoded.
@param output The name of a file to which the output should be written. If the file doesn't exit it will be created.
@param algorithm 0: The standard algorithm, 1: The specific algorithm. 
*/
void encode(char* input, char* output, int algorithm);

#endif
