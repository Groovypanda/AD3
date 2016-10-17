#include "statistics.h"

void print_statistics_time(char* title, clock_t start, clock_t end) {
	double time = TIME(start, end);
	printf("%s time: %f\n", title, time);
}

void print_statics_speed(char* title, clock_t start, clock_t end, double size) {
	double speed = (size/1000000.0) / (TIME(start, end));
	printf("%s speed: %f MBs\n", title, speed);
}

void print_statistics_compression(int original, int encoded) {
	double encodedsize = ((double)encoded) / 1000000.0;
	double originalsize = ((double)original) / 1000000.0;
	double ratio = (originalsize/encodedsize)*100;
	printf("Orginal file: %f MB | Compressed file: %f MB | Compression ratio: %f% \n", originalsize, encodedsize, ratio);
}