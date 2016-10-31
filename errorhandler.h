#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

/**
	errorhandler.h
	Purpose: Throw errors and allocate memory.
*/

#include <stdio.h>
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
*/
void* allocate_memory(int size);

#endif