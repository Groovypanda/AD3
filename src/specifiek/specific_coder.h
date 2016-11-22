#ifndef SPECIFIC_CODER_H
#define SPECIFIC_CODER_H

/**
	specific_coder.h
	Purpose: For encoding and decoding a list of rising numbers formatted as a JSON-string with delta and huffman encoding.
*/

#include "delta_decode.h"
#include "delta_encode.h"
#include "../gedeeld/bithandler.h"
#include "../gedeeld/bytehandler.h"

/**
Encodes the input file with the specific encoding algorithm.
@param input Name of the inputfile
@param output Name of the outputfile
*/
void specific_encode(char* input, char* output);

/**
Decodes the input file with the specific decoding algorithm.
@param input Name of the inputfile
@param output Name of the outputfile
*/
void specific_decode(char* input, char* output);

#endif