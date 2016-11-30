
#include "benchmark_decoder.h"

void decode(char* input, char* output, int algorithm) {
	clock_t start = clock();

	if (algorithm == SPECIFIC_ALGORITHM) { // 1 means specific algorithm
		specific_decode(input, output);
	}
	else if (algorithm == STANDARD_ALGORITHM) { // 0 means standard algorithm
		standard_decode(input, output);
	}
	else {
		printf("Wrong algorithm specification.");
	
	}

	unsigned long long decoded_size = get_filesize(output);
	printf("==========================================================================================================\n					DECODING:\n==========================================================================================================\n");
	clock_t end = clock();
	print_statistics_time("Decompression", start, end);
	print_statics_speed("Decompression", start, end, decoded_size);
}