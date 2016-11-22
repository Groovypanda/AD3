#ifndef GENERATOR_H
#define GENERATOR_H

/**
	generator.h
	Purpose: Generating special kind of files. 
*/

#include <stdio.h>
#include "errorhandler.h"
#include "delta_decode.h" //This file contains a function for writing long long numbers with a buffer. 
#include "bytehandler.h" //This file contains functionality for writing numbers to a buffer, and these buffers to a file. 
 
#define AMOUNT 10000 //Is used to indicate how many bytes will be written.

/**
	Generate a file containing a json string with climbing numbers. 
	@param filename The file to which the generated content will be written.
	@param numberamount Indicates how many numbers should be written into the file. 
*/
void generate_json_file(char* filename, int numberamount);

/**
	Generate a file containing only zeros. 
	@param filename The file to which the generated content will be written.
*/
void generate_zeros_file(char* filename);

/**
	Generate a file where the bytes have frequencies specified by the fibonacci sequence.
	@param filename The file to which the generated content will be written.
*/
void generate_fibonacci_file(char* filename);

/**
	Generate a file containing all possible values.
	@param filename The file to which the generated content will be written.
*/
void generate_extendedascii_file(input);

#endif