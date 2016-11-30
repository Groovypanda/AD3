#ifndef PRESTATION_H
#define PRESTATION_H

/**
prestation_analyzer.h
Purpose: Analyze the prestation of the algorithms.
*/

#include "../src/standaard/standard_coder.h"
#include "../src/specifiek/specific_coder.h"
#include <sys\timeb.h>
#include "statistics.h"
#include "generator.h"
#include "tools.h"
#include "performance_analyzer.h"

/**
	Runs a prestation analysis with the given algorithm on every file with a certain amount of numbers. 
	The amount of numbers starts with step and is incremented with step until max is reached.
	@param logfile_name outputfile for the analysis
	@param algorithm The algorithm to use
	@param max The max amount of numbers for the analysis
	@param step The step to take in numbers after every file
*/
void run_prestation_analysis(char* logfile_name, int algorithm, int max, int step);

/**
	Test the prestation for the given input_file and with the given algorithm. This analysis is saved into the analyzer. 
	@param input_file Name of the file with the input
	@param encoded_file Name of the file for the encoded output
	@param decoded_file Name of the file for the decoded output
	@param a In this analyzer the analysis will be saved. 
*/
void test_prestation(char* input_file, char* encoded_file, char* decoded_file, int algorithm, analyzer* a);

#endif