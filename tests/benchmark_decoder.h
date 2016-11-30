#ifndef DECODE_H
#define DECODE_H

/**
	benchmark_encoder.h 
	Purpose: Prints benchmarks after decoding.
*/

#include "../src/standaard/standard_coder.h"
#include "../src/specifiek/specific_coder.h"
#include "statistics.h"

#define STANDARD_ALGORITHM 0 
#define SPECIFIC_ALGORITHM 1 

/**
Decodes the given file and places the decoded content into the given file.
@param input The name of a file which has to be decoded.
@param output The name of a file to which the output should be written. If the file doesn't exit it will be created.
@param algorithm 0: The standard algorithm, 1: The specific algorithm.
*/
void decode(char* input, char* output, int algorithm);

#endif