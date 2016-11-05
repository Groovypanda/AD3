
#include "decoder.h"

void decode(char* input, char* output) {
	clock_t start = clock();
	bitreader* reader = init_bitreader(input);
	bytewriter* writer = init_bytewriter(output);
	int block = 0;
	while (!reader->bytereader->lastblock) { //Read all of the file buffer by buffer. Finished = 1 if last buffer has been reached. 
		if (OUTPUT) {
			printf("=======================\nBlock %d\n=======================\n", block++);
		}
		huffman_decode(reader, writer);
	}
	while (reader->index < reader->bytereader->text_length - 1) { //Read remaining text in buffer of the bytereader. 
		if (OUTPUT) {
			printf("=======================\nBlock %d\n=======================\n", block++);
		}
		huffman_decode(reader, writer);
	}
	unsigned long long decoded_size = ftell(writer->ofp);
	flush_bytes(writer);
	free_bitreader(reader);
	free_bytewriter(writer);
	clock_t end = clock();
	if (STATISTICS) {
		print_statistics_time("Decompression", start, end);
		print_statics_speed("Decompression", start, end, decoded_size);
	}
}