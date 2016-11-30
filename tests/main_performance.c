#include <stdio.h>
#include <stdlib.h>
#include "performance_analyzer.h"
#include "prestation_analyzer.h"
#define COMPARE 1
#define STANDARD_ALGORITHM 0 
#define SPECIFIC_ALGORITHM 1 

int main() {
	//All code used for experiments is saved in comments for future reference. 
	char* logfile_encoded = "performance/other/performance_de_encoder.csv";
	char* logfile_decoded = "performance/other/performance_de_decoder.csv";
	char* logfile_total = "performance/other/performance_de_total.csv";
	char* logfile_encoded2 = "performance/other/performance_hm_encoder.csv";
	char* logfile_decoded2 = "performance/other/performance_hm_decoder.csv";
	char* logfile_total2 = "performance/other/performance_hm_total.csv";

	//encode("numbers_25 - 0M.json", "encoded.bin", STANDARD_ALGORITHM);
	//decode(encoded, output, algorithm);
	//run_performance_analysis(logfile_encoded, logfile_decoded, logfile_total, SPECIFIC_ALGORITHM, 10, 100);
	run_performance_analysis(logfile_encoded2, logfile_decoded2, logfile_total2, STANDARD_ALGORITHM, 10, 100);
	//run_prestation_analysis("performance/prestation/prestation_hm.csv", STANDARD_ALGORITHM, 25,250);
	//run_prestation_analysis("performance/prestation/prestation_de.csv", SPECIFIC_ALGORITHM, 25,250);
	//run_buffersize_analysis(10 * 1000 * 1000, STANDARD_ALGORITHM, "performance/prestation/buffersize_hm.csv");
	//run_buffersize_analysis(10 * 1000 * 1000, SPECIFIC_ALGORITHM, "performance/prestation/buffersize_de.csv");
	/*
	char* input = "data/big_delta.txt";
	char* encoded = "data/encoded.bin";
	char* output = "data/decoded.txt";
	int algorithm = SPECIFIC_ALGORITHM;
	generate_worst_delta_file(input, 1000000);
	//generate_worst_delta_file(input, 100000);
	encode(input, encoded, algorithm);
	decode(encoded, output, algorithm);
	if (COMPARE) {
	int equal = compare_file(input, output);
	if (equal) {
	printf("The files are equal");
	}
	else {
	printf("The files aren't equal");
	}
	}
	else {
	printf("The files weren't compared.");
	}
	*/
	printf("\n\nDebugging finished. Press enter.");
	getchar(); 
	return 0; 
}





