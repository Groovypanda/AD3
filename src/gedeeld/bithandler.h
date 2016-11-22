#ifndef BITHANDLER_H
#define BITHANDLER_H

/**
	bithandler.h
	Purpose: Handling individual bits, this file uses bytehandler.h for I/O operations. 
*/

#include "bytehandler.h"

/**
	Struct which is used to write bits to a file.  
*/
typedef struct bitwriter {
	//Bytewriter for writing the byte once it's filled. 
	bytewriter* bytewriter;
	//Value of byte at this moment.
	unsigned char byte;
	//Amount of bits to fill.
	unsigned int remaining_bits;	
} bitwriter;

/**
	Struct which is used to read bits from a file. 
*/
typedef struct bitreader { 
	//Bytereader for reading a byte once one is needed.  
	bytereader* bytereader;
	//Current index of the bytereader.
	unsigned long index;
	//Remaining bits on current index.
	unsigned int remaining_bits;
} bitreader;

/**
	Saves the bits in the bitwriter, and writes them once MAX_BUFFERSIZE is reached. 
	@param writer The writer to which the bits will be written.
	@param bits The bits which will be written.
	@param amount The amount of bits the variable bits contains.
*/
void write_bits(bitwriter* writer, int bits, unsigned int amount);

/**
	Read a certain amount of bits from the reader.
	@param reader The reader from which the bits should be read. 
	@param amount The amount of bits to be read. 
	@return The bytes which are read. 
*/
unsigned int read_bits(bitreader* reader, unsigned int amount);

/**
	Writes all remaining bits in the writer to the outputfile. 
	@param reader The writer of which all the bits will be written.
*/
void flush_bits(bitwriter* writer);

/** 
	Initiates a bitwriter which will write bits to the given filename.
	@param filename The file to which the bits should be written. 
	@return An initialised bitwriter which will write bits to the given file. 
*/
bitwriter* init_bitwriter(char* filename);

/**
	Initiates a bitreader which will read bits from the given filename. 
	@param filename The file from which the bits should be read. 
	@return An initialised bitreader which will read bits from the given file. 
*/
bitreader* init_bitreader(char* filename);

/**
	Frees the memory from the bitwriter and closes the outputfile. 
	@param writer The bitwriter which needs to be freed. 
*/
void free_bitwriter(bitwriter* writer);

/**
	Frees the memory from the bitreader and closes the infile. 
	@param reader The bitreader which needs to be freed. 
*/
void free_bitreader(bitreader* reader);

#endif 
