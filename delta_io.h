#ifndef DELTA_IO_H
#define DELTA_IO_H

typedef struct deltawriter {
	char* out_buffer; 
	unsigned char byte;
	unsigned int remaining_bits;
	unsigned int index; 
} deltawriter;

typedef struct deltareader {
	char* in_buffer; 
	unsigned long index;
	unsigned int remaining_bits;
} deltareader;

unsigned long long read_bits(deltareader* reader, unsigned int amount);
unsigned long long read_number(deltareader* reader);
void write_number(deltawriter* writer, unsigned long long delta);
void write_bits(deltawriter* writer, unsigned int amount);

#endif