#ifndef DECODE_H
#define DECODE_H

#include "huffman_decode.h"
#include "delta_decode.h"
//For testing purposes. 
#include "statistics.h"
#include "debug.h"

#define STANDARD_ALGORITHM 0 
#define SPECIFIC_ALGORITHM 1 

/**
Decodes the input file with the standard decoding algorithm.
@param A bitreader initialised with the input file.
@param A bytewriter initialised with the output file.
*/
void standard_decode(bitreader* reader, bytewriter* writer);

/**
Decodes the input file with the specific decoding algorithm.
@param A bitreader initialised with the input file.
@param A bytewriter initialised with the output file.
*/
void specific_decode(bitreader* reader, bytewriter* writer);

/**
Decodes the given file and places the decoded content into the given file.
@param input The name of a file which has to be decoded.
@param output The name of a file to which the output should be written. If the file doesn't exit it will be created.
@param algorithm 0: The standard algorithm, 1: The specific algorithm.
*/
void decode(char* input, char* output, int algorithm);

#endif