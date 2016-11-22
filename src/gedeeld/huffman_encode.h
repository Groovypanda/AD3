#ifndef HUFFMAN_ENcode_H
#define HUFFMAN_ENcode_H

/**
	huffman_encode.h 
	Purpose: Encode a file, the encoded file can be decoded by huffman_decode.h afterwards. 
*/

#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "code.h"
#include "pqueue.h"
#include "bithandler.h"
#include "errorhandler.h"

/**
	Encodes one block of text with the huffman algorithm.
	@param block The block to be encoded
	@param block_length The size of this block
	@param writer The output handler
*/
void huffman_encode_block(unsigned char* block, unsigned int block_length, bitwriter* writer);

/**
	Encodes MAX_BUFFERSIZE amount of bytes from the inputfile (defined in bytereader). The encoded content is written to the outputfile 
	with the bitwriter. 
	@param bitwriter 
*/
void huffman_encode(bytereader* reader, bitwriter* writer);

/**
	Builds a huffmantree from the list of frequencies. The implementation of this function is the actual huffman coding algorithm. 
	(page 110 algorithm 15)
	@param frequencies a list of frequencies: for each value (0->255)as index: the frequency of this value in the content.
	@return A huffmantree. 
*/
tree* build_huffmantree(unsigned int* frequencies);

/**
	Creates a list of frequencies from a text with a certain length, the index is the value of each char (0->256) 
	and the value stored at a certain is the frequency of this value. 
	@param text The text of which the frequencies will be counted.
	@param length The length of the text.
	@return The list of frequencies. 
*/
unsigned int* create_frequency_list(unsigned char* text, unsigned int length);

/**
	Prints a byte to stdout
	@param byte The byte to be printe.
*/
void print_byte(unsigned char byte);

#endif