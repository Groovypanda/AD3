#ifndef ENCODE_H
#define ENCODE_H


#include "huffman_encode.h"
#include "delta_encode.h"
//For testing purposes
#include "statistics.h"
#include "debug.h"

#define STANDARD_ALGORITHM 0 
#define SPECIFIC_ALGORITHM 1 

/**
Encodes the input file with the standard encoding algorithm.
@param A bytereader initialised with the input file. 
@param A bitwriter initialised with the output file. 
*/
void standard_encode(bytereader* reader, bitwriter* writer);

/**
Encodes the input file with the specific encoding algorithm. 
@param A bytereader initialised with the input file.
@param A bitwriter initialised with the output file.
*/
void specific_encode(bytereader* reader, bitwriter* writer);

/**
Encodes the given file and places the encoded content into the given file.
@param input The name of a file which has to be encoded.
@param output The name of a file to which the output should be written. If the file doesn't exit it will be created.
@param algorithm 0: The standard algorithm, 1: The specific algorithm. 
*/
void encode(char* input, char* output, int algorithm);

#endif
