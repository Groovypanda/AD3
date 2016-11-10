#include "delta_io.h"

unsigned long long read_bits(deltareader* reader, unsigned int amount) {
	int result = 0;
	unsigned char byte = reader->in_buffer[reader->index];
	for (unsigned int i = 0; i < amount; i++) {
		//Get nth bit of byte.
		unsigned int i = reader->remaining_bits - 1;
		int bit = (byte >> i) & 1;
		//Set nth bit of result.
		result |= bit;
		reader->remaining_bits--;
		if (!reader->remaining_bits) {
			reader->index++;
			byte = reader->in_buffer[reader->index];
			reader->remaining_bits = 8;
		}
		result <<= 1;
	}
	return result >> 1;
}

//Variable length quantity
unsigned long long read_number(deltareader* reader) {
	unsigned char continue_reading = read_bits(reader, 1); 
	unsigned long long value = 0; 
	unsigned int bit_index = 0; 
	//There's another byte if continue_reading is 1. 
	while (read_bits(reader, 1)) {
		value |= read_bits(reader, 7);
		value <<= 7; 
	}
	//7 more bits if read_bits return 0. 
	value |= read_bits(reader, 7); 
	return value; 
}

void write_number(deltawriter* writer, unsigned long long delta) {
	
}

void write_bits(deltawriter* writer, unsigned char bits,  unsigned int amount) {
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
			writer->out_buffer[writer->index] = writer->byte;
			writer->byte = 0;
			writer->remaining_bits = 8;
		}
	}
}	