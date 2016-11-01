#include "huffman_decode.h"

//This function decodes a huffman tree. 

void huffman_decode(bitreader* reader, bytewriter* writer) {
	bytereader* bytereader = reader->bytereader;
	unsigned int i = 0;
	unsigned int text_length = read_bits(reader, 32);
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
			if (cur == root) {
				read_bits(reader, 1);
			}
			write_byte(writer, cur->value);
			cur = root;
		}
	}
	free_tree(t);
	/*
	if (reader->remaining_bits) {
		reader->remaining_bits = 8;
		reader->index++;
	}
	*/
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
