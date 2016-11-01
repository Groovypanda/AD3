#include <stdio.h>
#include <stdlib.h>
#include "huffman_encode.h"
#include "huffman_decode.h"
#include "generator.h"
#include "filecomparator.h"

#define DEBUG 1
#define MB_AMOUNT 10000


void shutdown(char* errormessage);

int main(int argc, char* argv[]) {
	if (argc==1) {
		printf("As there are no arguments, the program will be tested.\n");
		char* input = "data/data_very_long.txt";
		//generate_fibonacci_file(input);
		char* encoded = "data/encoded";
		char* decoded = "data/decoded/data_very_long.txt";
		encode(input, encoded);
		decode(encoded, decoded);
		int equal = compare_file(input, decoded);
		if (equal) {
			printf("The files are equal.");
		}
		else {
			printf("The files aren't equal.");
		}
		getchar(); 
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
			generate_json_file(argv[2], MB_AMOUNT);
		}
		else {
			shutdown(USAGE_ERROR);
		}
	}
	return 0; 
}



void shutdown(char* errormessage) {
	printf("%s\nPress enter to close the program.\n", errormessage);
	getchar();
	exit(-1);
}
