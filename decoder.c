
#include "decoder.h"

void standard_decode(bitreader* reader, bytewriter* writer) {
	while (!reader->bytereader->lastblock) { //Read all of the file buffer by buffer. Finished = 1 if last buffer has been reached. 
		huffman_decode(reader, writer);
	}
	while (reader->index < reader->bytereader->text_length - 1) { //Read remaining text in buffer of the bytereader. 
		huffman_decode(reader, writer);
	}
	flush_bytes(writer);
}


void specific_decode(bitreader* reader, bytewriter* writer) {

	deltadecoder* decoder = init_deltadecoder(writer); 
	while (!reader->bytereader->lastblock) { //Read all of the file buffer by buffer. Finished = 1 if last buffer has been reached. 
		specific_huffman_decode(reader, decoder);
	}
	while (reader->index < reader->bytereader->text_length - 1) { //Read remaining text in buffer of the bytereader. 
		specific_huffman_decode(reader, decoder);
	}
	finish_deltadecoder(decoder);
	free(decoder);
}


void decode(char* input, char* output, int algorithm) {
	clock_t start = clock();
	bitreader* reader = init_bitreader(input);
	bytewriter* writer = init_bytewriter(output);

	if (SPECIFIC_ALGORITHM) { // 1 means specific algorithm
		specific_decode(reader, writer);
	}
	else if (STANDARD_ALGORITHM) { // 0 means standard algorithm
		standard_decode(reader, writer);
	}
	else {
		printf("Something went wrong. Nothing will be encoded.");
	
	}

	unsigned long long decoded_size = ftell(writer->ofp);

	free_bitreader(reader);
	free_bytewriter(writer);

	clock_t end = clock();
	if (STATISTICS) {
		print_statistics_time("Decompression", start, end);
		print_statics_speed("Decompression", start, end, decoded_size);
	}
}