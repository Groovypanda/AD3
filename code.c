#include "code.h"

void init_code(code* codes, node* currentnode, int* currentcode, unsigned int currentlength, unsigned int currentsize) {
	if (currentnode->left && currentnode->right) {
		currentlength++; 
		if (currentlength % 32 == 0) { //1 int can't contain more than 32 bits. 
			currentsize++;
			currentcode = (int*)realloc(currentcode, currentsize);
			currentcode[currentsize - 1] = 0;
		}
		currentcode[currentsize - 1] <<= 1;
		//Pass copy of pointer to child nodes. 
		int* leftcode = (int*) allocate_memory(sizeof(int)*currentsize);
		int* rightcode = (int*) allocate_memory(sizeof(int)*currentsize);
		memcpy(leftcode, currentcode, currentsize*sizeof(int));
		memcpy(rightcode, currentcode, currentsize * sizeof(int));
		free(currentcode);
		init_code(codes, currentnode->left, leftcode, currentlength, currentsize);
		rightcode[currentsize-1] |= 1; //Set last bit as 1.
		init_code(codes, currentnode->right, rightcode, currentlength, currentsize);
	
	}
	else {
		code code = codes[currentnode->value];
		code.length = currentlength ? currentlength : 1; //Currentlength can be zero if the root has no children.  
		code.size = currentsize;
		code.value = currentcode;
		codes[currentnode->value] = code; 
	}
}

//Edits currentmax
code* init_codes(tree* t) {
	//For every value, 1 codelist.
	code* codes = (code*)allocate_memory(sizeof(code) * 256);
	for (unsigned int i = 0; i < 256; i++) {
		codes[i].length = 0;
		codes[i].size = 0;
	}
	int* code = (int*)malloc(sizeof(int));
	code[0] = 0; 
	init_code(codes, t->root, code, 0, 1);
	return codes;
}

void free_codes(code* codes) {
	for (unsigned int i = 0; i < 256; i++) {
		if (codes[i].length) {
			free(codes[i].value);
		}
	}
	free(codes);
}

void write_code(bitwriter* writer, code code) {
	write_bits(writer, code.value[code.size - 1], code.length % 32);
	for (int i = code.size-2; i >= 0; i++) { //code is little endian, most significant bytes need to be written first. 
		write_bits(writer, code.value[i], 32);
	}	
}