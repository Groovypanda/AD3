#include "delta_encode.h"

void delta_encode(bytereader* reader, bitwriter* writer) {
	char* buffer = reader->buffer;
	long long numbers[MAX_BUFFERSIZE / 8];
	unsigned int number_index = 0; 
	unsigned long long previous_number = 0, current_number, delta; 
	while (*buffer) {
		if (isdigit(*buffer)) {
			current_number = strtoll(buffer, &buffer, 10);
			delta = current_number - previous_number;
			if (!*buffer) { 
				read_block(reader);
				buffer = reader->buffer;
				if (isdigit(*buffer)) { //Calculate actual delta if the buffer ended while reading a long long
					while (*buffer == '0') {
						current_number *= 10; 
						buffer++; 
					}
					unsigned long long numberend = strtoll(buffer, &buffer, 10);
					if (numberend != 0) {
						current_number = concatenate(current_number, numberend);
					}
					delta = current_number - previous_number;
				}
			}
			numbers[number_index++] = delta;
			previous_number = current_number; 
			if (number_index == MAX_BUFFERSIZE / 8) {
				char* out_buffer = (char*)numbers;
				huffman_encode_block(out_buffer, MAX_BUFFERSIZE, writer);
				number_index = 0; 
			}
		}
		else {
			buffer++;
		}
		if (!*buffer) {
			read_block(reader);
			buffer = reader->buffer;
		}
	}
}

long long concatenate(long long number1, long long number2) {
	unsigned long long exp = 10;
	while (exp <= number2) {
		exp *= 10;
	}
	return number1*exp + number2;
}
