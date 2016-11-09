#include <stdio.h>
#include <stdlib.h>
#include "encoder.h"
#include "decoder.h"
#include "generator.h"
#include "filecomparator.h"
#include "debug.h"

#define STANDARD_ALGORITHM 0 
#define SPECIFIC_ALGORITHM 1 

int main(int argc, char* argv[]) {
	if (DEBUG) {
		printf("					DEBUG MODE\n");
		char* input = "data/numbers_1M";
		//generate_json_file(input, 1000000);
		char* encoded = "data/encoded";
		char* output = "data/decoded/decoded.txt";
		int algorithm = SPECIFIC_ALGORITHM; 
		if (DELTA_OUTPUT || STATISTICS) {
			printf("==========================================================================================================\n					ENCODING:\n==========================================================================================================\n");
		}
		encode(input, encoded, algorithm);
		if (DELTA_OUTPUT || STATISTICS) {
			printf("==========================================================================================================\n					DECODING:\n==========================================================================================================\n");
		}
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
		printf("\n\nDebugging finished. Press enter.");
		getchar(); 
	}
	else {
		if (argc != 4) {
			shutdown(USAGE_ERROR);
		}
		else if (strcmp(argv[1], "-c") == 0) {
			encode(argv[2], argv[3], STANDARD_ALGORITHM);
		}
		else if (strcmp(argv[1], "-d") == 0) {
			decode(argv[2], argv[3], STANDARD_ALGORITHM);
		}
		else {
			shutdown(USAGE_ERROR);
		}
	}
	return 0; 
}




