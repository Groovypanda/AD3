#include "huffman_decode.h"

//This functions decodes a huffman tree. 

void decode(char* filename, char* filename_decoded) {
	time_t start = clock();
	FILE* ofp;
	bytereader* reader = init_bytereader(filename);
	tree* t = read_tree(reader);
	//Check if tree with codes is correct.  
	/*TODO*///print_tree(t->root, 0);
	node* root = t->root; 
	node* cur = t->root;
	unsigned int length = 0, buffersize=100;
	unsigned char* buffer =(unsigned char*)malloc(sizeof(unsigned char) * buffersize);
	//While not EOF
	while (cur->value != 3) {
		if (cur->value=='\0') {
			int x = read_bits(reader, 1);
			if (x) {
				cur = cur->right;
			}
			else {
				cur = cur->left;
			}
		}
		else if (cur->value != 3) {
			//String opbouwen en wegschrijven daarna!
			buffer[length++] = cur->value;
			if (length == buffersize) {
				buffersize *= 2;
				buffer = (unsigned char*)realloc(buffer, buffersize);
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
