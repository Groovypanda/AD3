#ifndef BUFFERSIZE_ANALYZER_H
#define BUFFERSIZE_ANALYZER_H

/**
buffersize_analyzer.h
Purpose: Analyze the encoding with the currently set MAX_BUFFERSIZE. 
*/

#include "../src/gedeeld/bytehandler.h"
#include "prestation_analyzer.h"
#include <stdio.h>

/**
	Runs an analysis with the given algorithm on a file with the given amount of numbers. 
	@param size The amount of numbers in the input file. 
	@param algorithm The algorithm which should be used.
	@param logfile_name The name of the file for the output. 
*/
void run_buffersize_analysis(unsigned long size, int algorithm, char* logfile_name);

#endif