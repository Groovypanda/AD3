#include "generator.h"

#define MAX_SIZE 64*1024
 
unsigned long long generate_random_long() {
	unsigned long long number = rand() % 2; //This generates a 14 bit number;
	for (int i = 0; i < 60; i++) {
		number <<= 1 ;
		number |= rand() % 2; 
	}
	return number; 
}


void generate_small_delta_file(char* filename, int numberamount) {
	unsigned long long x = -1;
	x >>= 2; // 2^62.
	unsigned long index = 0;
	bytewriter* writer = init_bytewriter(filename);
	write_byte(writer, '[');
	for (unsigned long long i = 0; i < numberamount; i++) {
		write_long(writer, x); //This function also writes a comma!
		write_byte(writer, ',');
		x += rand() % 127;
	}
	write_long(writer, x);
	write_byte(writer, ']');
	flush_bytes(writer);
	free_bytewriter(writer);
}

void generate_big_delta_file(char* filename) {
	unsigned long long x = generate_random_long(); 
	bytewriter* writer = init_bytewriter(filename);
	write_byte(writer, '[');
	unsigned long long MAX = -1;
	MAX >>= 1;
	for (unsigned long long i = 0; i < 1000000 && x < MAX; i++) {
			write_long(writer, x); //This function also writes a comma!
			write_byte(writer, ',');
			x += generate_random_long();
		
	}
	writer->buffer[writer->index-1] = ']';

	flush_bytes(writer);
	free_bytewriter(writer);
}

void generate_json_file(char* filename, int numberamount) {
	unsigned long long x = rand();
	unsigned long index = 0; 
	bytewriter* writer = init_bytewriter(filename);
	write_byte(writer, '[');
	for (unsigned long long i = 0; i < numberamount; i++) {
		write_long(writer, x); //This function also writes a comma!
		write_byte(writer, ',');
		x += rand();
	}
	write_long(writer, x);
	write_byte(writer, ']');
	flush_bytes(writer);
	free_bytewriter(writer);
}

void generate_zeros_file(char* filename) {
	FILE* ofp = open_file(filename, "wb");
	unsigned char zero = 0; 
	for (unsigned long long i = 0; i < 10000 * AMOUNT; i++) {
		fwrite(&zero, 1, 1, ofp);
	}
	fclose(ofp);
}

void generate_2chars_file(char* filename) {
	FILE* ofp = open_file(filename, "wb");
	unsigned char zero = 0;
	unsigned char one = 1; 
	for (unsigned long long i = 0; i < 10000 * AMOUNT; i++) {
		fwrite(&zero, 1, 1, ofp);
		fwrite(&one, 1, 1, ofp);
	}
	fclose(ofp);
}

void generate_fibonacci_file(char* filename) {
	unsigned long previous = 0;
	unsigned long current = 1; 
	unsigned long next = 0;
	unsigned char byte = 0; 
	int finished = 0; 
	FILE* ofp = open_file(filename, "wb");
	for(unsigned long i=0; i<MAX_BUFFERSIZE;) {
		previous = current; 
		current = next; 
		next = previous + current;
		for (unsigned long j = 0; j < current && j < MAX_BUFFERSIZE; j++) {
			fwrite(&byte, 1, 1, ofp);
		}
		byte++; 
		i += current;
	}
	fclose(ofp);
}

void generate_extendedascii_file(char* filename) {
	FILE* ofp = open_file(filename, "wb");
	unsigned char byte = 0; 
	for (int i = 0; i < 10000 * AMOUNT; i++) {
		for (unsigned int j = 0; j <= 1; j++) {
			fwrite(&byte, 1, 1, ofp);
		}
		i += byte;
		byte++; 
	}
}

void shutdown(char* errormessage) {
	printf("%s\nPress enter to close the program.\n", errormessage);
	getchar();
	exit(-1);
}

