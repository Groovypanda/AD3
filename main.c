#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "huffman_encode.h"
#include "huffman_decode.h"

#define DEBUG 1
#define MB_amount 10000

void generate(char* filename);
void shutdown(char* errormessage);

int main(int argc, char* argv[]) {
	if (argc==1) {
		char* input = "data/data_very_long.txt";
		//generate(input);
		char* encoded = "data/encoded";
		encode(input, encoded);
		char* decoded = "data/decoded.txt";
		decode(encoded, decoded);
	}
	else {
		if (argc != 4) {
			shutdown(USAGE_ERROR);
		}
		else if (strcmp(argv[1], "-c") == 0) {
			encode(argv[2], argv[3]);
		}
		else if (strcmp(argv[1], "-d") == 0) {
			decode(argv[2], argv[3]);
		}
		else if (strcmp(argv[1], "-g") == 0) {
			generate(argv[2]);
		}
		else {
			shutdown(USAGE_ERROR);
		}
	}
	return 0; 
}

void generate(char* filename) {
	unsigned long long x = rand();

	FILE* ofp = fopen(filename, "w");
	fwrite("[", 1, 1, ofp);
	for (int i = 0; i < MB_amount*10000; i++) {
		fprintf(ofp, "%llu", x);
		fwrite(",", 1, 1, ofp);
		x += rand();
	}
	fprintf(ofp, " %llu", x);
	fwrite("]", 1, 1, ofp);
	fclose(ofp);
}

void shutdown(char* errormessage) {
	printf("%s\nPress enter to close the program.\n", errormessage);
	getchar();
	exit(-1);
}
