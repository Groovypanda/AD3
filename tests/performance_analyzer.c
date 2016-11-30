#include "performance_analyzer.h"

void run_performance_analysis(char* logfile_encoded_name, char* logfile_decoded_name, char* logfile_total_name, int algorithm, int max, int step) {
	analyzer a;
	unsigned long long i;
	unsigned long long startsize = 1000;
	char** input;
	char* encoded = "data/encoded.bin";
	char* output = "data/decoded/decoded.json";
	FILE* logfile_encoded = fopen(logfile_encoded_name, "w");
	FILE* logfile_decoded = fopen(logfile_decoded_name, "w");
	FILE* logfile_total = fopen(logfile_total_name, "w");
	for (i = step; i <= 1000*max; i += step) {
		unsigned long long size = i*startsize;
		input = get_filename(size);
		if (!exists(*input)) {
			generate_json_file(*input, size);
		}
		test_performance(*input, encoded, output, algorithm, &a);
		write_analysis(&a, logfile_encoded, logfile_decoded, logfile_total);
	} 
	fclose(logfile_encoded);
	fclose(logfile_decoded);
	fclose(logfile_total);
}



analyzer* test_performance(char* input_file, char* encoded_file, char* decoded_file, int algorithm, analyzer* a) {
	struct timeb start_encode, end_encode, end_decode;
	ftime(&start_encode);
	if (algorithm == SPECIFIC_ALGORITHM) { // 1 means specific algorithm
		specific_encode(input_file, encoded_file);
		ftime(&end_encode);
		specific_decode(encoded_file, decoded_file);
	}
	else if (algorithm == STANDARD_ALGORITHM) { // 0 means standard algorithm
		standard_encode(input_file, encoded_file);
		ftime(&end_encode);
		standard_decode(encoded_file, decoded_file);
	}
	else {
		printf("Wrong algorithm specification.");

	}
	ftime(&end_decode);
	a->encoding_runtime = get_interval(start_encode, end_encode);  
	a->decoding_runtime = get_interval(end_encode, end_decode);
	printf("%f\n", (a->original_size/ 1000000.0) / (a->encoding_runtime/1000.0));
	a->original_size = get_filesize(input_file);
	a->encoded_size = get_filesize(encoded_file);
	printf("%s\n", input_file);
	//print_statistics_time("Compression", start_encode, end_encode);
	//print_statics_speed("Compression", start_encode, end_encode, a.original_size);
	//print_statistics_time("Decompression", end_encode, end_decode);
	//print_statics_speed("Decompression", end_encode, end_decode, a.encoded_size);
	return a; 
}

void write_analysis(analyzer* analyzer, FILE* logfile_encoded, FILE* logfile_decoded, FILE* logfile_total) {
	fprintf(logfile_encoded, "%llu %lu\n", analyzer->original_size, analyzer->encoding_runtime);
	fprintf(logfile_decoded, "%llu %lu\n", analyzer->encoded_size, analyzer->decoding_runtime);
	fprintf(logfile_total, "%llu %lu\n", analyzer->original_size, (analyzer->decoding_runtime + analyzer->encoding_runtime));
}
