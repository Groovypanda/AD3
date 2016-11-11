#include "delta_encode.h"

void delta_encode(bytereader* reader, bitwriter* writer) {
	char* buffer = reader->buffer;
	unsigned long long numbers[MAX_BUFFERSIZE / 8]; //An unsigned long long is 8 bytes, BUFFERSIZE equals the max amount of bytes in a buffer.
	unsigned int number_index = 0; 
	unsigned long long previous_number = 0, current_number, delta; 
	char out_buffer[MAX_BUFFERSIZE];
	//This loop will encode all the data of the input file. (Not only one buffer, it continues reading into the buffer 
	//until the full file is encoded. 
	while (*buffer) { 
		if (isdigit(*buffer)) {
			delta = read_long(&buffer, reader, &current_number, &previous_number);
			write_number(delta, writer->bytewriter);
			numbers[number_index++] = delta;
			if (number_index == MAX_BUFFERSIZE / 8) {
				char* out_buffer = (char*)((unsigned long*)numbers);
				number_index = 0; 
			}
			
		}
		else { //If it's not a digit, it's not encoded. 
			buffer++;
		}
		if (!*buffer) {
			read_block(reader);
			buffer = reader->buffer;
		}
	}
	if (number_index > 0) {
		unsigned long long* numbers_cpy = (unsigned long long*)malloc(sizeof(unsigned long long)*number_index);
		for (int i = 0; i < number_index; i++) {
			numbers_cpy[i] = numbers[i];
		}
		char* out_buffer = (char*)numbers_cpy;
		huffman_encode_block(out_buffer, number_index*8, writer); //Number index equals index+1 ==> equals size
		free(numbers_cpy);
	}
	
}

long long concatenate(long long number1, long long number2) {
	unsigned long long exp = 10;
	while (exp <= number2) {
		exp *= 10;
	}
	return number1*exp + number2;
}

unsigned long long read_long(char** buffer, bytereader* reader, unsigned long long* current_number, unsigned long long* previous_number) {
	*current_number = strtoll(*buffer, buffer, 10);
	unsigned long long delta = *current_number - *previous_number;
	if (!*(*buffer)) {
		read_block(reader);
		*buffer = reader->buffer;
		if (isdigit(*(*buffer))) { //Calculate actual delta if the buffer ended while reading a long long
			while (*(*buffer) == '0') {
				*current_number *= 10;
				(*buffer)++;
			}
			unsigned long long numberend = strtoll(*buffer, buffer, 10);
			if (numberend != 0) { //if numberend is 0 it means nothing was read by strtoll.
				*current_number = concatenate(*current_number, numberend);
			}
			delta = *current_number - *previous_number;
		}
	}
	*previous_number = *current_number;
	return delta;
}

void write_number(bitwriter* bitwriter, unsigned long long delta) {
	bytewriter* writer = bitwriter->bytewriter;
	unsigned long long value = delta;
	//Calculate amount of bits in delta. (Amount of times 7 bits) 
	int amount_7bits = 0;
	while (value) {
		value >>= 7;
		amount_7bits++;
	}
	for (int i = amount_7bits; i > 1; i--) {
		writer->buffer[writer->index++] = ((delta >> (i - 1) * 7) & 0x7F) | 128;
		if (writer->index == MAX_BUFFERSIZE) {
			huffman_encode_block(writer->buffer, MAX_BUFFERSIZE, writer);
			writer->index = 0;
		}
	}
	writer->buffer[writer->index++] = delta & 0x7F;
	if (writer->index == MAX_BUFFERSIZE) {
		huffman_encode_block(writer->buffer, MAX_BUFFERSIZE, writer);
		writer->index = 0;
	}
}