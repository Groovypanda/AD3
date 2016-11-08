#include "delta_encode.h"

void delta_encode(bytereader* reader, bitwriter* writer) {
	char* numbers = reader->buffer;
	char buffer[MAX_BUFFERSIZE+1];
	buffer[MAX_BUFFERSIZE] = '\0';
	int buffer_index = 0; 
	long long previous_number = 0;
	while (*numbers) {
		if (isdigit(*numbers)) {
			long long current_number = strtoll(numbers, &numbers, 10);
			long long delta = current_number - previous_number;
			if (!*numbers) { 
				read_block(reader);
				numbers = reader->buffer;
				if (isdigit(*numbers)) { //Calculate actual delta
					while (*numbers == '0') {
						current_number *= 10; 
						numbers++; 
					}
					long long numberend = strtoll(numbers, &numbers, 10);
					if (numberend != 0) {
						current_number = concatenate(current_number, numberend);
					}
					delta = current_number - previous_number;
				}
			}
			int amount = snprintf(buffer+buffer_index, MAX_BUFFERSIZE-buffer_index, "%lld", delta);
			if (amount > MAX_BUFFERSIZE - buffer_index - 1) { //If less bytes are written than should've been written, write out the other bytes. 
				huffman_encode_block(buffer, MAX_BUFFERSIZE, writer);
				int amount_to_write = amount + buffer_index - MAX_BUFFERSIZE + 1;
				buffer_index = 0; 
				char remainder[20]; //A 64 bit number can't have more than 19 numbers. 
				snprintf(remainder, 20, "%lld", delta);
				for (int i = amount_to_write-1, j=amount-amount_to_write; i >= 0; i--) {
					buffer[buffer_index++] = remainder[j++];
				}
			}
			else {
				buffer_index += amount;
			}
			previous_number = current_number; 
		}
		else {
			numbers++; 
		}
		if (!*numbers) {
			read_block(reader);
			numbers = reader->buffer;
		}
	}
	if (buffer_index > 0) {
		huffman_encode_block(buffer, buffer_index, writer);
	}
}

long long concatenate(long long number1, long long number2) {
	unsigned long long exp = 10;
	while (exp <= number2) {
		exp *= 10;
	}
	return number1*exp + number2;
}
