#ifndef STATISTICS_H
#define STATISTICS_H

#include <time.h>
#include <stdio.h>

#define TIME(start, end) ((end - start)/CLOCKS_PER_SEC)

void print_statistics_time(char* title, clock_t start, clock_t end);
void print_statics_speed(char* title, clock_t start, clock_t end, double size);
void print_statistics_compression(int original, int encoded);

#endif