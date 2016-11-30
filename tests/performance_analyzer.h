#ifndef PERFORMANCE_H
#define PERFORMANCE_H

/**
performance_analyzer.h
Purpose: Analyze the performance of the algorithms.
*/

#include "../src/standaard/standard_coder.h"
#include "../src/specifiek/specific_coder.h"
#include <sys\timeb.h>
#include "statistics.h"
#include "generator.h"
#include "tools.h"

/**
  * Contains information about runtime. 
**/
typedef struct analyzer {
	unsigned long long original_size; 
	unsigned long long encoded_size; 
	unsigned long encoding_runtime;
	unsigned long decoding_runtime; 
} analyzer;


/**
Runs a performance analysis with the given algorithm on every file with a certain amount of numbers.
The amount of numbers starts with step and is incremented with step until max is reached.
@param logfile_name outputfile for the analysis
@param algorithm The algorithm to use
@param max The max amount of numbers for the analysis
@param step The step to take in numbers after every file
*/
void run_performance_analysis(char* logfile_encoded_name, char* logfile_decoded_name, char* logfile_total_name, int algorithm, int max, int step);

/**
Test the performance for the given input_file and with the given algorithm. This analysis is saved into the analyzer.
@param input_file Name of the file with the input
@param encoded_file Name of the file for the encoded output
@param decoded_file Name of the file for the decoded output
@param a In this analyzer the analysis will be saved.
*/
analyzer* test_performance(char* input_file, char* encoded_file, char* decoded_file, int algorithm, analyzer* a);

/**
Write the given analysis to the given logfiles. 
@param analyzer
@param logfile_encoded analysis for encoding will be written here.
@param logfile_decoded analysis for decoding will be written here.
@param logfile_total The total analysis will be written here.
*/
void write_analysis(analyzer* analyzer, FILE* logfile_encoded, FILE* logfile_decoded, FILE* logfile_total);


#endif