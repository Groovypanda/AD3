#include "huffman_decode.h"

//This functions decodes a huffman tree. 
void decode(char* filename, char* filename_decoded) {
	FILE* ofp;
	bytereader* reader = init_bytereader(filename);
	tree* t = read_tree(reader);
	//Check if tree with codes is correct.  
	/*TODO*///print_tree(t->root, 0);
	node* root = t->root; 
	node* cur = t->root;
	ofp = fopen(filename_decoded, "w");
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
			fwrite(&cur->value, 1, 1, ofp);
			cur = root;
		}
	}
	fclose(ofp);
	free_bytereader(reader);
}
