
#include "encoder.h"

void encode(char* input, char* output) {
	clock_t start = clock();
	unsigned long long original_size, encoded_size = 0;
	bytereader* reader = init_bytereader(input);
	bitwriter* writer = init_bitwriter(output);
	//While reading isn't finished, huffman encode.
	int block = 0;
	while (!reader->lastblock) {
		if (OUTPUT) {
			printf("=======================\nBlock %d\n=======================\n", block++);
		}
		huffman_encode(reader, writer);
		read_block(reader);
	}
	//One last time, to write last bytes. 
	if (reader->text_length) {
		if (OUTPUT) {
			printf("=======================\nBlock %d\n=======================\n", block++);
		}
		huffman_encode(reader, writer);
	}

	flush_bits(writer);
	original_size = reader->total_size;
	encoded_size = ftell(writer->bytewriter->ofp);

	free_bitwriter(writer);
	free_bytereader(reader);

	clock_t end = clock();
	if (STATISTICS) {
		print_statistics_compression(original_size, encoded_size);
		print_statistics_time("Compression", start, end);
		print_statics_speed("Compression", start, end, original_size);
	}
}