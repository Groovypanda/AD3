#include "standard_coder.h"

void standard_encode(char* input, char* output) {
	bytereader* reader = init_bytereader(input);
	bitwriter* writer = init_bitwriter(output);
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
	free_bytereader(reader);
	free_bitwriter(writer);	
}

void standard_decode(char* input, char* output) {
	bitreader* reader = init_bitreader(input);
	bytewriter* writer = init_bytewriter(output);
	while (!reader->bytereader->lastblock) { //Read all of the file buffer by buffer. Finished = 1 if last buffer has been reached. 
		huffman_decode(reader, writer);
	}
	while (reader->index < reader->bytereader->text_length - 1) { //Read remaining text in buffer of the bytereader. 
		huffman_decode(reader, writer);
	}
	flush_bytes(writer);
	free_bitreader(reader);
	free_bytewriter(writer);
}

