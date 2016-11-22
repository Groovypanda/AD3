#ifndef STANDARD_CODER_H
#define STANDARD_CODER_H

/**
	standard_coder.h
	Purpose: Encoding and decoding random files with huffman. 
*/

#include "../gedeeld/huffman_decode.h"
#include "../gedeeld/huffman_encode.h"
#include "../gedeeld/bithandler.h"
#include "../gedeeld/bytehandler.h"

/**
Encodes the input file with the standard encoding algorithm.
@param input The filename of the inputfile
@param output The filename of the outputfile
*/
void standard_encode(char* input, char* output);

/**
Decodes the input file with the standard decoding algorithm.
@param input The filename of the inputfile
@param output The filename of the outputfile
*/
void standard_decode(char* input, char* output);

#endif