#include "specific_coder.h"

void specific_encode(char* input, char* output) {
	bytereader* reader = init_bytereader(input);
	bitwriter* writer = init_bitwriter(output);
	delta_encode(reader, writer);
	flush_bits(writer);
	free_bytereader(reader);
	free_bitwriter(writer);
}

void specific_decode(char* input, char* output) {
	bitreader* reader = init_bitreader(input);
	bytewriter* writer = init_bytewriter(output);
	deltadecoder* decoder = init_deltadecoder(writer);
	while (!reader->bytereader->lastblock) { //Read all of the file buffer by buffer. Finished = 1 if last buffer has been reached. 
		specific_huffman_decode(reader, decoder);
	}
	while (reader->index < reader->bytereader->text_length - 1) { //Read remaining text in buffer of the bytereader. 
		specific_huffman_decode(reader, decoder);
	}
	finish_deltadecoder(decoder);
	free_bitreader(reader);
	free_bytewriter(writer);
	free(decoder);
}
