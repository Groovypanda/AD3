#include <stdio.h>
#include <stdlib.h>
#include "encoder.h"
#include "decoder.h"
#include "generator.h"
#include "filecomparator.h"

#include "debug.h"
#define MB_AMOUNT 10000

int main(int argc, char* argv[]) {
	if (DEBUG) {
		printf("					DEBUG MODE\n");
		char* input = "data/data_very_long.txt";
		//generate_fibonacci_file(input);
		char* encoded = "data/encoded";
		char* decoded = "data/decoded/data_very_very_long.txt";
		if (OUTPUT || STATISTICS) {
			printf("==========================================================================================================\n					ENCODING:\n==========================================================================================================\n");
		}
		encode(input, encoded);
		if (OUTPUT || STATISTICS) {
			printf("==========================================================================================================\n					DECODING:\n==========================================================================================================\n");
		}
		decode(encoded, decoded);
		if (COMPARE) {
			int equal = compare_file(input, decoded);
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
			encode(argv[2], argv[3]);
		}
		else if (strcmp(argv[1], "-d") == 0) {
			decode(argv[2], argv[3]);
		}
		else {
			shutdown(USAGE_ERROR);
		}
	}
	return 0; 
}




