#include "generator.h"

void generate_json_file(char* filename, int size) {
	unsigned long long x = rand();

	FILE* ofp = open_file(filename, "wb");
	fwrite("[", 1, 1, ofp);
	for (unsigned long long i = 0; i < size * 10000; i++) {
		fprintf(ofp, "%llu", x);
		fwrite(",", 1, 1, ofp);
		x += rand();
	}
	fprintf(ofp, " %llu", x);
	fwrite("]", 1, 1, ofp);
	fclose(ofp);
}

void generate_zeros_file(char* filename) {
	FILE* ofp = open_file(filename, "wb");
	unsigned char zero = 0; 
	for (unsigned long long i = 0; i < 10000 * AMOUNT; i++) {
		fwrite(&zero, 1, 1, ofp);
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
	for(unsigned long i=0; i<10000*AMOUNT; i++) {
		previous = current; 
		current = next; 
		next = previous + current;
		for (unsigned long i = 0; i < current; i++) {
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
