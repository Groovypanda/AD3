#include "errorhandler.h"

void throw_error(char* error) {
	printf("%s\nPress enter to close this program.\n", error);
	getchar();
	exit(-1);
}

void* allocate_memory(int size) {
	void* memory = malloc(size);
	if (!memory) {
		throw_error(MEMORY_ERROR);
	}
	return memory;
}

FILE* open_file(char* filename, char* mode) {
	FILE* file = fopen(filename, mode);
	if (!file) {
		printf("The file %s couldn't be opened.", filename);
		throw_error("");
	}
	return file; 
}
