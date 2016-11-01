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
	unsigned char previous = 0;
	unsigned char current = 1; 
	unsigned char next = 0;
	int finished = 0; 
	FILE* ofp = open_file(filename, "wb");
	fwrite(&previous, 1, 1, ofp);
	fwrite(&current, 1, 1, ofp);
	while (!finished) {
		previous = current; 
		current = next; 
		next = previous + current;
		if (((int)previous + (int)current) > next) {
			finished = 1;
		}
		else {
			for (unsigned char i = 0; i < current; i++) {
				fwrite(&current, 1, 1, ofp);
			}
		}
	}
	fclose(ofp);
}

void generate_extendedascii_file(char* filename) {
	FILE* ofp = open_file(filename, "wb");
	unsigned char byte = 0; 
	for (int i = 0; i < 10000 * AMOUNT; i++) {
		for (unsigned int j = 0; j <= byte; j++) {
			fwrite(&byte, 1, 1, ofp);
		}
		i += byte;
		byte++; 
	}
}
