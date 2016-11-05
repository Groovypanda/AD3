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


