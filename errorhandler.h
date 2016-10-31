#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdio.h>
#define USAGE_ERROR "The arguments are incorrect.\nUsage: comprimeer1 <-c/-d> <inputfile> <outputfile>"
#define MEMORY_ERROR "The given memory couldn't be allocated."

void throw_error(char* error);

void* allocate_memory(int size);

#endif