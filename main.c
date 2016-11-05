#include <stdio.h>
#include <stdlib.h>
#include "encoder.h"
#include "decoder.h"
#include "generator.h"
#include "filecomparator.h"
#include "delta_decoder.h"
#include "delta_encoder.h"

#include "debug.h"

int main(int argc, char* argv[]) {
	if (DEBUG) {
		printf("					DEBUG MODE\n");
		char* input = "data/data.txt";
		//generate_fibonacci_file(input);
		char* encoded = "data/encoded";
		char* huffman_decoded = "data/huffman_decoded";
		char* output = "data/decoded/data.txt";
		if (DELTA_OUTPUT || DELTA_STATISTICS) {
			printf("==========================================================================================================\n					ENCODING:\n==========================================================================================================\n");
		}
		delta_encode(input, encoded);
		if (DELTA_OUTPUT || DELTA_STATISTICS) {
			printf("==========================================================================================================\n					DECODING:\n==========================================================================================================\n");
		}
		decode(encoded, huffman_decoded);
		delta_decode(huffman_decoded, output);
		//decode(encoded, decoded);
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




