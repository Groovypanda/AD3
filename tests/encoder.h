#ifndef ENCODE_H
#define ENCODE_H

/**
	encoder.h
	Purpose: Printer statistics while encoding.
*/

#include "../standaard/standard_coder.h"
#include "../specifiek/specific_coder.h"
#include "bytehandler.h"
#include "bithandler.h"
#include "statistics.h"
#include "debug.h"

#define STANDARD_ALGORITHM 0 
#define SPECIFIC_ALGORITHM 1 

/**
Encodes the given file and places the encoded content into the given file.
@param input The name of a file which has to be encoded.
@param output The name of a file to which the output should be written. If the file doesn't exit it will be created.
@param algorithm 0: The standard algorithm, 1: The specific algorithm. 
*/
void encode(char* input, char* output, int algorithm);

#endif
