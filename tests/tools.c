#include "tools.h"

char** get_filename(unsigned long long size) {
	char** input = (char**)malloc(sizeof(char*));
	*input = (char*)malloc(sizeof(char) * 30);
	int number;
	int remainder;
	char multiplier;
	if (size < 1000 * 1000) {
		multiplier = 'K';
		number = size / 1000;
		remainder = size % 1000;
	}
	else if (size < 1000 * 1000 * 1000) {
		multiplier = 'M';
		number = size / (1000 * 1000);
		remainder = size % (1000 * 1000);
	}
	else {
		multiplier = 'G';
		number = size / (1000 * 1000 * 1000);
		remainder = size % (1000 * 1000 * 1000);
	}
	while (remainder != 0 && (remainder / 10) * 10 == remainder) {
		remainder /= 10;
	}
	sprintf(*input, "data/numbers_%d-%d%c.json", number, remainder, multiplier);
	int length = strlen(*input);
	(*input)[length] = '\0';
	return input;
}

int exists(char *fname) {
	FILE *file = fopen(fname, "r");
	if (file) {
		fclose(file);
		return 1;
	}
	return 0;
}

unsigned long get_interval(struct timeb start, struct timeb end) {
	return (unsigned long)(1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
}