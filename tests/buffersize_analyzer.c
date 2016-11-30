#include "buffersize_analyzer.h"

void run_buffersize_analysis(unsigned long size, int algorithm, char* logfile_name) {
	analyzer a;
	char** input;
	char* encoded = "data/encoded.bin";
	char* output = "data/decoded/decoded.json";
	input = get_filename(size);
	FILE* logfile = fopen(logfile_name, "a");
	test_prestation(*input, encoded, output, algorithm, &a);
	fprintf(logfile, "%d %f %lu\n", MAX_BUFFERSIZE, a.original_size / (float)a.encoded_size, a.encoding_runtime);
	fclose(logfile);
}
