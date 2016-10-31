#include "huffman_decode.h"

//This function decodes a huffman tree. 

int huffman_decode(bitreader* reader, bytewriter* writer) {
	bytereader* bytereader = reader->bytereader;
	unsigned long i = 0, text_length = 0;
	unsigned int amount = 0;
	unsigned char number[4];
	if (reader->index + 4 >= bytereader->text_length) {
		//Integer is formatted as little endian. 
		for(unsigned int i = reader->index; i < bytereader->text_length; i++) {
			number[amount++] = bytereader->buffer[i];
		}
		read_bytes(bytereader);
		reader->index = 0;
		for (unsigned int i = 0; i < 4 - amount; i++) {
			number[amount+i] = bytereader->buffer[i];
			reader->index++; 
		}
		memcpy(&text_length, number, sizeof(unsigned int));
	}
	else {
		memcpy(&text_length, bytereader->buffer + reader->index, sizeof(unsigned int));
		reader->index += sizeof(unsigned int);
	}
	tree* t = read_tree(reader);
	node* root = t->root;
	node* cur = t->root;
	while (i < text_length) {
		if (cur->left && cur->right) {
			int x = read_bits(reader, 1);
			if (x) {
				cur = cur->right;
			}
			else {
				cur = cur->left;
			}
		}
		else {
			i++;
			write_byte(writer, cur->value);
			cur = root;
		}
	}
	free_tree(t);
	if (reader->remaining_bits_amount) {
		reader->remaining_bits_amount = 8;
		reader->index++;
	}
	return bytereader->text_length < MAX_BUFFERSIZE;  

}

void decode(char* input, char* output) {
	clock_t start = clock();
	bitreader* reader = init_bitreader(input);
	bytewriter* writer = init_bytewriter(output);
	int finished = 0;
	read_bytes(reader->bytereader);
	int block = 0; 
	while (!finished) {
		block++;
		finished = huffman_decode(reader, writer);
	}
	if (reader->index < reader->bytereader->text_length) {
		huffman_decode(reader, writer);
	}
	flush_bytes(writer);
	free_bitreader(reader);
	free_bytewriter(writer);
	clock_t end = clock();
	print_statistics_time("Decompression", start, end);
	
}
