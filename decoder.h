
#include "statistics.h"
#include "debug.h"
#include "huffman_decode.h"

/**
Decode an input file which was compressed by huffman_encode.h
@param input The name of a huffman encoded file.
@param output The name of the file in which the decoded content will be written
*/
void decode(char* input, char* output);