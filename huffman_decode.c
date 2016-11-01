#include "huffman_decode.h"

//This function decodes a huffman tree. 

void huffman_decode(bitreader* reader, bytewriter* writer) {
	bytereader* bytereader = reader->bytereader;
	unsigned int i = 0, text_length = 0;
	unsigned int amount = 0;
	unsigned char number[4];
	if (reader->index + 4 >= bytereader->text_length) {
		//Integer is formatted as little endian. 
		for(unsigned int i = reader->index; i < bytereader->text_length; i++) {
			number[amount++] = bytereader->buffer[i];
		}
		read_block(bytereader);
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
	print_tree(t);
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
			if (cur == root) {
				read_bits(reader, 1);
			}
			write_byte(writer, cur->value);
			cur = root;
		}
	}
	free_tree(t);
	if (reader->remaining_bits) {
		reader->remaining_bits = 8;
		reader->index++;
	}
}

void decode(char* input, char* output) {
	clock_t start = clock();
	bitreader* reader = init_bitreader(input);
	bytewriter* writer = init_bytewriter(output);
	while (!reader->bytereader->lastblock) { //Read all of the file buffer by buffer. Finished = 1 if last buffer has been reached. 
		huffman_decode(reader, writer);
	}
	while (reader->index < reader->bytereader->text_length) { //Read remaining text in buffer of the bytereader. 
		huffman_decode(reader, writer);
	}
	flush_bytes(writer);
	free_bitreader(reader);
	free_bytewriter(writer);
	clock_t end = clock();
	print_statistics_time("Decompression", start, end);
	
}
