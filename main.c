#include <stdio.h>
#include <time.h>
#include "huffman_encode.h"
#include "huffman_decode.h"

//#define MAX 4294967296//32 bits.
//#define MAX 124294967296
#define MB_amount 1

void generate(char* filename);
void shutdown(char* errormessage);

int main(/*int argc, char* argv[]*/) {
	char* input = "data/Opgave.pdf";
	//generate(input);
	char* encoded = "data/encoded"; 
	encode(input, encoded);
	printf("=============\n=============\n=============\n");
	clock_t start = clock();
	char* decoded = "data/decoded.pdf";
	decode(encoded, decoded);
	/*
	for (int i = 0; i < argc; i++) {
		printf("%d, %s\n", i, argv[i]);
	}
	if (argc!=4) {
		printf("Error 1\n");
		shutdown(ERROR);
	}
	else if (argv[1] == "-c") {
		encode(argv[2], argv[3]);
	}
	else if (argv[1] == "-d") {
		decode(argv[2], argv[3]);
	}
	else if (argv[1] == "-g") {
		generate(argv[2], MAX-RAND_MAX);
	}
	else {
		printf("Error 2\n");
		shutdown(ERROR);
	}
	*/
	clock_t end = clock();
	printf("\nThe program ran for a total of %.3f seconds.\n", TIME(end, start));
	printf("The end of the program has been reached, press enter.\n");

	getchar();
	return 0; 
}

void generate(char* filename) {
	unsigned long long x = rand();

	FILE* ofp = fopen(filename, "w");
	fwrite("[", 1, 1, ofp);
	/*
	while (x < max) {
		fprintf(ofp, "%llu", x);
		fwrite(",", 1, 1, o	fp);
		x += rand();
	}*/
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
