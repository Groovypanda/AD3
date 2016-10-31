#include "bithandler.h"

void write_bits(bitwriter* writer, int bits, unsigned int amount) {
	bytewriter* bytewriter = writer->bytewriter;
	int i = amount - 1;
	while (i >= 0) {
		if (i + 1 <= writer->remaining_bits) {
			unsigned int shift = writer->remaining_bits - i - 1;
			writer->byte |= bits << shift;
			writer->remaining_bits -= i + 1;
			i = -1;
		}
		else {
			int bit = (bits >> i) & 1;
			writer->byte |= (bit << (writer->remaining_bits - 1));
			writer->remaining_bits--;
			i--;
		}
		if (writer->remaining_bits == 0) {
			write_byte(bytewriter, writer->byte);
			writer->byte = 0;
			writer->remaining_bits = 8;
		}
	}
}


unsigned int read_bits(bitreader* reader, unsigned int amount) {
	bytereader* bytereader = reader->bytereader;
	int result = 0;
	unsigned char byte = bytereader->buffer[reader->index];
	for (unsigned int i = 0; i < amount; i++) {
		//Get nth bit of byte.
		unsigned int i = reader->remaining_bits_amount - 1;
		int bit = (byte >> i) & 1;
		//Set nth bit of result.
		result |= bit;
		reader->remaining_bits_amount--;
		if (!reader->remaining_bits_amount) {
			byte = bytereader->buffer[++reader->index];
			reader->remaining_bits_amount = 8;
			if (reader->index == MAX_BUFFERSIZE) {
				read_bytes(reader->bytereader);
				reader->index = 0;
			}
		}
		result <<= 1;
	}
	return result >> 1;
}

void flush_bits(bitwriter* writer) {
	bytewriter* bytewriter = writer->bytewriter;
	flush_bytes(bytewriter);
	if (writer->remaining_bits) {
		fwrite(&writer->byte, sizeof(unsigned char), 1, bytewriter->ofp);
	}
	writer->byte = 0;
	writer->remaining_bits = 8;
}

bitwriter* init_bitwriter(char* filename) {
	bitwriter* writer = (bitwriter*)allocate_memory(sizeof(bitwriter));
	writer->remaining_bits = 8;
	writer->byte = 0;
	writer->bytewriter = init_bytewriter(filename);
	return writer;
}

bitreader* init_bitreader(char* filename) {
	bitreader* reader = (bitreader*)allocate_memory(sizeof(bitreader));
	reader->index = 0;
	reader->remaining_bits_amount = 8;
	reader->bytereader = init_bytereader(filename, "rb");
	return reader;
}

void free_bitwriter(bitwriter* writer) {
	free_bytewriter(writer->bytewriter);
	free(writer);
}

void free_bitreader(bitreader* reader) {
	free_bytereader(reader->bytereader);
	free(reader);
}
