#include "huffman_decode.h"

//This function decodes a huffman tree. 

int huffman_decode(bytereader* reader, textwriter* writer) {
	textreader* textreader = reader->textreader;
	unsigned long i = 0, text_length =0;
	memcpy(&text_length, textreader->buffer+reader->index, sizeof(unsigned int));
	reader->index += sizeof(unsigned int);
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
			write_char(writer, cur->value);
			cur = root;
		}
	}
	free_tree(t);
	if (reader->remaining_bits_amount) {
		reader->remaining_bits_amount = 8;
		reader->index++;
	}
	return textreader->text_length < MAX_BUFFERSIZE; //IS THIS CORRECT? 

}

void decode(char* input, char* output) {
	time_t start = clock();
	bytereader* reader = init_bytereader(input);
	textwriter* writer = init_textwriter(output);
	int finished = 0;
	read_file(reader->textreader);
	printf("Decoding\n");
	int block = 0; 
	while (!finished) {
		printf("Block %d\n", block++);
		finished = huffman_decode(reader, writer);
	}
	printf("Block %d\n", block++);
	huffman_decode(reader, writer);
	flush(writer);
	free_bytereader(reader);
	free_textwriter(writer);
	clock_t end = clock();
	print_statistics_time("Decompression", start, end);
	
}
