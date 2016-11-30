#include "prestation_analyzer.h"

void run_prestation_analysis(char* logfile_name, int algorithm, int max, int step) {
	analyzer a;
	unsigned long long i;
	unsigned long long startsize = 1000;
	char** input;
	char* encoded = "data/encoded.bin";
	char* output = "data/decoded/decoded.json";
	FILE* logfile = fopen(logfile_name, "w");
	for (i = step; i <= 1000 * max; i += step) {
		unsigned long long size = i*startsize;
		input = get_filename(size);
		if (!exists(*input)) {
			generate_json_file(*input, size);
		}
		test_prestation(*input, encoded, output, algorithm, &a);
		fprintf(logfile, "%llu %f\n", a.original_size, a.original_size / (float)a.encoded_size) ;
	}
	fclose(logfile);
}



analyzer* test_prestation(char* input_file, char* encoded_file, char* decoded_file, int algorithm, analyzer* a) {
	struct timeb start, end;
	ftime(&start);
	if (algorithm == SPECIFIC_ALGORITHM) { // 1 means specific algorithm
		specific_encode(input_file, encoded_file);
	}
	else if (algorithm == STANDARD_ALGORITHM) { // 0 means standard algorithm
		standard_encode(input_file, encoded_file);
	}
	else {
		printf("Wrong algorithm specification.");

	}
	ftime(&end);
	a->encoding_runtime = get_interval(start, end);
	a->original_size = get_filesize(input_file);
	a->encoded_size = get_filesize(encoded_file);
	printf("%s\n", input_file);
	return a;
}
