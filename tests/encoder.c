  
#include "encoder.h"

void encode(char* input, char* output, int algorithm) {
	clock_t start = clock();

	if (algorithm == SPECIFIC_ALGORITHM) { // 1 means specific algorithm
		specific_encode(input, output);
	}
	else if(algorithm == STANDARD_ALGORITHM) { // 0 means standard algorithm
		standard_encode(input, output);
	}
	else {
		printf("Something went wrong. Nothing will be encoded.");
	}

	unsigned long long original_size = get_filesize(input);
	unsigned long long encoded_size = get_filesize(output);

	clock_t end = clock();
	if (STATISTICS) {
		print_statistics_compression(original_size, encoded_size);
		print_statistics_time("Compression", start, end);
		print_statics_speed("Compression", start, end, original_size);
	}
}