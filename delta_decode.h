#ifndef DELTA_DECODE_H
#define DELTA_DECODE_H

/**
	delta_decode.h
	Decodes a file encoded by the delta encoding algorithm followed by the huffman encoding algorithm. 
*/

#include "bytehandler.h"
#include "bithandler.h"
#include "tree.h"


typedef struct deltadecoder {
	char inputbuffer[MAX_BUFFERSIZE]; //Inputbuffer with a block of the data produced from the huffman decoding.
	unsigned int inputbuffer_length; //Current length of inputbuffer. 
	unsigned int inputbuffer_index; //Index in the inputbuffer. 
	unsigned long long previous_number; //Previous number fully decoded by the deltadecoder.
	unsigned long long current_number; //Current number we're building. (A number which isn't finished. 
	unsigned char finished; //Returns if deltadecoder finished reading the whole number. 
	bytewriter* writer; //A bytewriter for writing the output to a file. 
} deltadecoder;

/**
	A variation to the huffman decoder. This will huffman decode a block AND delta decode this block afterwards. 
	@param reader A bitreader which reads the bits from the input file.
	@param writer A bytewriter which writes the bytes to the output file.
*/
void specific_huffman_decode(bitreader* reader, deltadecoder* decoder);

/**
	This function decodes the block in the inputbuffer of the decoder and writes it to the outputfile with the bytewriter. 
	It reads bytes from the inputbuffer and decodes the delta's produced by the delta encoder. These delta's can be used to reproduce 
	the original file. How these delta's are produced and should be read is explained in delta_encode.h 
	@param decoder A struct which handles a collection of variables for the decoding. It contains the input and the output. 
*/
void delta_decode(deltadecoder* decoder);

/**
	This function is used to write an unsigned long long number to the destination file. 
	@param writer This struct contains a buffer with output and the output file for writing. It will save the number and write it when necessary. 
*/
void write_long(bytewriter* writer, unsigned long long number);

/**
	Initialises the deltadecoder with the given bytewriter. The deltadecoder is for handling all of the input from the huffman algorithm and uses the bytewriter for all of the output. 
	It also saves a few variables in order to be able to keep decoding block after block. 
	@param writer The bytewriter which handles the output.
*/
deltadecoder* init_deltadecoder(bytewriter* writer);

/**
	Finished the delta decoding by delta decoding the remaining inputbuffer content, releasing all memory and closing the output file.
	@param decoder The decoder used for decoding the input. 
*/
void finish_deltadecoder(deltadecoder* decoder);

/**
	Reads a number from the inputbuffer. The number is formatted as a variable length quantity (VLQ). If the full number can't be read, 
	the finished variable will be set to zero. 
	@param decoder The decoder containing the input data produced by the huffman decoder.
	@param value The value read will be appended to the given value. This value is 0 by default, but can be another value if the previous block didn't finish reading a full number. 
	@return Returns the value read from the buffer. 
*/
unsigned long long read_number(deltadecoder* decoder, unsigned long long value);


#endif