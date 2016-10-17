#include <stdio.h>
#include <time.h>
#include "huffman_encode.h"
#include "huffman_decode.h"

#define TIME(end, start) (double)(end - start) / CLOCKS_PER_SEC
#define MAX 16777216 //32 bits.
#define ERROR "The arguments are incorrect.\nUsage: comprimeer1 <-c/-d> <inputfile> <outputfile>"

void generate(char* filename, unsigned long long maximum);
void shutdown(char* errormessage);

/*
TODO FREE TREE FUNCTIE
*/

int main(/*int argc, char* argv[]*/) {
	clock_t start = clock();
	generate("data/data.txt", MAX);
	char* input = "data/data.txt";
	//generate(input, MAX);
	char* encoded = "data/encoded"; 
	encode(input, encoded);
	char* decoded = "data/decoded.txt";
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

void generate(char* filename, unsigned long long max) {
	int seed = time(NULL);
	unsigned long long x = rand(seed);

	FILE* ofp = fopen(filename, "w");
	fwrite("[", 1, 1, ofp);
	while (x < max) {
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
