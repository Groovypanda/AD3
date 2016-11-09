#ifndef BYTEHANDLER_H
#define BYTEHANDLER_H

/**
	bytehandler.h
	Purpose: Reading and writing bytes from and to files. Handler for I/O operations. 
*/

#include <stdio.h>
#include <stdlib.h>
#include "errorhandler.h"

#define MAX_BUFFERSIZE 128*1024

/**
	Struct used for reading bytes from a file. 
*/
typedef struct bytereader {
	unsigned int text_length; //length of current text.
	unsigned long long total_size; //length of total text.
	unsigned char buffer[MAX_BUFFERSIZE + 1]; //buffer which contains a part of the content of ifp.
	int lastblock; //Specifies if the last block of the input file is in the buffer.
	FILE* ifp; //File from which bytes will be read. 
} bytereader;

/**
	Struct used for writing bytes to a file. 
*/
typedef struct bytewriter {
	unsigned long index; //index in buffer, also specifies how many bytes in buffer are filled. 
	char buffer[MAX_BUFFERSIZE + 1]; //buffer which contains the bytes which ought to be written. 
	FILE* ofp; //File to which bytes will be written. 
} bytewriter;

/**
	Reads maximum MAX_BUFFERSIZE bytes from the file in bytereader. If the last block is reached, 1 is placed into last_block.
	@param reader The bytereader which will be read the bytes. 
*/
void read_block(bytereader* reader);

/**
	Write a byte to the given bytewriter.
	@param writer The writer to which the byte will be written. 
	@param c The byte which will be written. 
*/
void write_byte(bytewriter* writer, char c);

/**
	Writes all bytes in the writer to the ofp.
	@param writer The writer of which all bytes will be written.
*/
void flush_bytes(bytewriter* writer);

/**
	Initiates a bytereader which will read bytes from filename.
	@param filename The bytereader will read bytes from this file. 
	@return An initialised bytereader. 
*/
bytereader* init_bytereader(char* filename);

/**
	Initiates a bytewriter to which bytes will be written. 
	@param filename The bytewriter will write bytes to this file. 
	@return An initialised bytewriter.
*/
bytewriter* init_bytewriter(char* filename);

/**
	@param reader Frees the memory and closes the input file of this bytereader.
*/
void free_bytereader(bytereader* reader);

/**
	@param writer Frees the memory and closes the output file of this bytewriter. 
*/
void free_bytewriter(bytewriter* writer);

#endif 