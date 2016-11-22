  
#include "encoder.h"

void standard_encode(bytereader* reader, bitwriter* writer) {
	//While reading isn't finished, huffman encode.
	while (!reader->lastblock) {
		huffman_encode(reader, writer);
		read_block(reader);
	}
	//One last time, to write last bytes. 
	if (reader->text_length) {
		huffman_encode(reader, writer);
	}
	flush_bits(writer);

}

void specific_encode(bytereader* reader, bitwriter* writer) {
	delta_encode(reader, writer);
	flush_bits(writer);
}

void encode(char* input, char* output, int algorithm) {
	clock_t start = clock();
	bytereader* reader = init_bytereader(input);
	bitwriter* writer = init_bitwriter(output);

	if (algorithm == SPECIFIC_ALGORITHM) { // 1 means specific algorithm
		specific_encode(reader, writer);
	}
	else if(algorithm == STANDARD_ALGORITHM) { // 0 means standard algorithm
		standard_encode(reader, writer);
	}
	else {
		printf("Something went wrong. Nothing will be encoded.");
	}

	unsigned long long original_size = reader->total_size;
	unsigned long long encoded_size = ftell(writer->bytewriter->ofp);

	free_bitwriter(writer);
	free_bytereader(reader);

	clock_t end = clock();
	if (STATISTICS) {
		print_statistics_compression(original_size, encoded_size);
		print_statistics_time("Compression", start, end);
		print_statics_speed("Compression", start, end, original_size);
	}
}