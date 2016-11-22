
#include "decoder.h"

void decode(char* input, char* output, int algorithm) {
	clock_t start = clock();

	if (algorithm == SPECIFIC_ALGORITHM) { // 1 means specific algorithm
		specific_decode(input, output);
	}
	else if (algorithm == STANDARD_ALGORITHM) { // 0 means standard algorithm
		standard_decode(input, output);
	}
	else {
		printf("Something went wrong. Nothing will be encoded.");
	
	}

	unsigned long long decoded_size = get_filesize(output);

	clock_t end = clock();
	if (STATISTICS) {
		print_statistics_time("Decompression", start, end);
		print_statics_speed("Decompression", start, end, decoded_size);
	}
}