#include "delta_decoder.h"



void delta_decode_block(bytereader* reader, bytewriter* writer) {
	char* numbers = reader->buffer;
	long long previous_number = 0;
	while (*numbers) {
		if (isdigit(*numbers)) {
			long long delta = strtoll(numbers, &numbers, 10);
			long long current_number; 
			if (!*numbers) {
				read_block(reader);
				numbers = reader->buffer;
				if (isdigit(*numbers)) {
					while (*numbers == '0') {
						delta *= 10;
						numbers++;
					}
					long long numberend = strtoll(numbers, &numbers, 10);
					if (numberend != 0) {
						delta = concatenate(delta, numberend);
					}
				}
			}
			current_number = previous_number + delta;
			fprintf(writer->ofp, "%lld", current_number);
			previous_number = current_number;
		}
		else {
			fwrite(numbers, sizeof(char), 1, writer->ofp);
			numbers++;
		}
		if (!*numbers) {
			read_block(reader);
			numbers = reader->buffer;
		}
	}
}

void delta_decode(char* input, char* output) {
	clock_t start = clock();
	bytereader* reader = init_bytereader(input);
	bytewriter* writer = init_bytewriter(output);
	delta_decode_block(reader, writer);
	unsigned long long decoded_size = ftell(writer->ofp);
	free_bytereader(reader);
	free_bytewriter(writer);
	clock_t end = clock();
	if (DELTA_STATISTICS) {
		print_statistics_time("Decompression", start, end);
		print_statics_speed("Decompression", start, end, decoded_size);
	}
}	