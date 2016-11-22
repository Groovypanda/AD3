#ifndef HUFFMAN_DEcode_H
#define HUFFMAN_DEcode_H

/**
	huffman_decode.h
	Purpose: Decompressing a file which was compressed by huffman_encode.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "bytehandler.h"
#include "errorhandler.h"



/**
	Decodes one huffman block. The encoder encodes the content of a file in blocks of MAX_BUFFERSIZE. 
	This function takes one block at decodes the block. 
	@param reader A bitreader which reads the bits from the input file. 
	@param writer A bytewriter which writes the bytes to the output file.
*/
void huffman_decode(bitreader* reader, bytewriter* writer);

#endif