#pragma once
#include <stdio.h>
#include <sys\timeb.h>


/**
	Get the name of the file with the given size. 
	@param size
	@return The name of the file
*/
char** get_filename(unsigned long long size);

/**
	Check if the given file exists.
	@param fname The name of the file
	@return 1 if it exists.
*/
int exists(char* fname);

/**
	Get the interval in ms between the given times.
	@param start Start of the interval
	@param end End of the interval
	@return The amount of time between start and end. 
*/
unsigned long get_interval(struct timeb start, struct timeb end);
