#include "huffman_decode.h"

//This functions decodes a huffman tree. 

void decode(char* filename, char* filename_decoded) {
	time_t start = clock();
	FILE* ofp;
	bytereader* reader = init_bytereader(filename);
	//char* code_length = (char*)malloc(sizeof(char)*4); 
	unsigned int code_length;
	memcpy(&code_length, reader->bytes, sizeof(unsigned int));
	reader->index += sizeof(unsigned int);
	tree* t = read_tree(reader);
	node* root = t->root; 
	node* cur = t->root;
	unsigned int i = 0, length = 0, buffersize=100;
	unsigned char* buffer =(unsigned char*)allocate_memory(sizeof(unsigned char) * buffersize);
	//While not EOF
while(i < code_length+1){ 
		if (cur->left && cur->right) {
			int x = read_bits(reader, 1);
			i++;
			if (x) {
				cur = cur->right;
			}
			else {
				cur = cur->left;
			}
		}
		else {
			buffer[length++] = cur->value;
			if (length == buffersize) {
				buffersize *= 2;
				buffer = (unsigned char*)realloc(buffer, buffersize);
				if (!buffer) {
					throw_error(MEMORY_ERROR);
				}
			}
			cur = root;
		}
	}
	ofp = fopen(filename_decoded, "w");
	fwrite(buffer, sizeof(unsigned char), length, ofp);
	fclose(ofp);
	clock_t end = clock();
	print_statistics_time("Decompression", start, end);
	free_bytereader(reader);
	
}
