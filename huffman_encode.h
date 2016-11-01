#ifndef HUFFMAN_ENCODE_H
#define HUFFMAN_ENCODE_H

/**
	huffman_encode.h 
	Purpose: Encode a file, the encoded file can be decoded by huffman_decode.h afterwards. 
*/

#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "code.h"
#include "bithandler.h"
#include "errorhandler.h"
#include "pqueue.h"
//For testing purposes
#include "statistics.h"

/**
	Encodes the given file with the huffman encoding algorithm, places the encoded content into the given file. 
	@param input The name of a file which has to be encoded. 
	@param output The name of a file to which the output should be written. If the file doesn't exit it wille created. 
*/
void encode(char* input, char* output);

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
unsigned int* create_frequency_list(char* text, unsigned int length);

/**
	Prints a byte to stdout
	@param byte The byte to be printe.
*/
void print_byte(unsigned char byte);

#endif