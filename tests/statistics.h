#ifndef STATISTICS_H
#define STATISTICS_H

/**
	statistics.h
	Purpose: Printing statistics about the (de)compression function. 
*/

#include <time.h>
#include <stdio.h>
#include "../src/gedeeld/errorhandler.h"

#define STANDARD_ALGORITHM 0 
#define SPECIFIC_ALGORITHM 1 

/**
	@param start The start of the interval assigned by clock()
	@param end The end of the interval assigned by clock()
	@return The interval in seconds
*/
#define TIME(start, end) ((((unsigned int)end) - ((unsigned int)start))/CLOCKS_PER_SEC)

/**
	Print statistics about the runtime of a function.
	@param title The name of the function.
	@param start The amount of clock ticks at the beginning of a function.
	@param end The amount of clock ticks at the end of a function.
*/
void print_statistics_time(char* title, clock_t start, clock_t end);

/**
	Print stastics about (de)compression.
	@param title The name of the function.
	@param start The amount of clock ticks at the beginning of a function.
	@param end The amount of clock ticks at the end of a function.
	@param size The size of the (de)compressed file. 
*/
void print_statics_speed(char* title, clock_t start, clock_t end, unsigned long long size);

/**
	Print statistics about compression.
	@param original The original size of a file.
	@param encoded The compressed size of a file.
*/
void print_statistics_compression(unsigned long long original, unsigned long long encoded);

#endif