#include "huffman_decode.h"

//This function decodes a huffman tree. 

void huffman_decode(bitreader* reader, bytewriter* writer) {
	bytereader* bytereader = reader->bytereader;
	unsigned int i = 0, text_length;
	int is_maxsize = read_bits(reader, 1);
	if (!is_maxsize) {
		text_length = MAX_BUFFERSIZE;
	}
	else {
		text_length = read_bits(reader, 32);
	}
	//unsigned int text_length = read_bits(reader, 32);
	tree* t = read_tree(reader);
	if (OUTPUT) {
		printf("Text length: %d\n", text_length);
		if (STEPS) {
			printf("Press enter to continue.\n");
			getchar();
		}
		if (TREE) {
			print_tree(t);
		}
	}
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
}

void decode(char* input, char* output) {
	clock_t start = clock();
	bitreader* reader = init_bitreader(input);
	bytewriter* writer = init_bytewriter(output);
	int block = 0;
	while (!reader->bytereader->lastblock) { //Read all of the file buffer by buffer. Finished = 1 if last buffer has been reached. 
		if (OUTPUT) {
			printf("=======================\nBlock %d\n=======================\n", block++);
		}
		huffman_decode(reader, writer);	}
	while (reader->index < reader->bytereader->text_length-1) { //Read remaining text in buffer of the bytereader. 
		if (OUTPUT) {
			printf("=======================\nBlock %d\n=======================\n", block++);
		}
		huffman_decode(reader, writer);
	}
	unsigned long long decoded_size = ftell(writer->ofp);
	flush_bytes(writer);
	free_bitreader(reader);
	free_bytewriter(writer);
	clock_t end = clock();
	if (STATISTICS) {
		print_statistics_time("Decompression", start, end);
		print_statics_speed("Decompression", start, end, decoded_size);
	}
}
