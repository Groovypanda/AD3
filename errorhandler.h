#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

/**
	errorhandler.h
	Purpose: Throw errors and allocate memory.
*/

#include <stdio.h>
#include <stdlib.h>

#define USAGE_ERROR "The arguments are incorrect.\nUsage: comprimeer1 <-c/-d> <inputfile> <outputfile>"
#define MEMORY_ERROR "The given memory couldn't be allocated."

/**
	Displays the given error. 
	@param The error.
*/
void throw_error(char* error);

/**
	Allocate some memory. 
	@param The size of the error.
	@return A pointer to the allocated memory.
*/
void* allocate_memory(int size);

/**
	Open a file.
	@param filename The file which has to be opened. 
	@return The opened file.
*/
FILE* open_file(char* filename, char* mode);

/**
	Close the program with the given error message. 
	@param errormessage This message is thrown before closing. 
*/
void shutdown(char* errormessage);

#endif
