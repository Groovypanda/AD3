#include "statistics.h"

void print_statistics_time(char* title, clock_t start, clock_t end) {
	unsigned int time = TIME(start, end);
	printf("%s time: %d seconds\n", title, time);
}

void print_statics_speed(char* title, clock_t start, clock_t end, unsigned long long size) {
	double speed = (size/1000000.0) / ((double)(TIME(start, end)));
	printf("%s speed: %f MBs\n", title, speed);
}

void print_statistics_compression(unsigned long long original, unsigned long long encoded) {
	double encodedsize = ((double)encoded) / 1000000.0;
	double originalsize = ((double)original) / 1000000.0;
	double ratio = (encodedsize/originalsize)*100;
	printf("Orginal file: %f MB | Compressed file: %f MB | Compression ratio: %.1f%% \n", originalsize, encodedsize, ratio);
}