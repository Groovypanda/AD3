#include "huffman_encode.h"

void write_code(bytewriter* writer, code c);
void print_byte(unsigned char byte);

//This function returns the encoded huffman tree. 
void encode(char* input, char* filename) {
	text inputtext = read_file(input);
	unsigned char* string = inputtext.string;
	unsigned int* frequencies = create_frequency_list(inputtext);
	tree* t = build_tree(frequencies);
	code* codes = init_codes(t);

	bytewriter* writer = init_bytewriter(filename);
	write_tree(writer, t);

	clock_t start = clock();
	for (unsigned long i = 0; i < inputtext.length; i++) {
		write_code(writer, codes[string[i]]);
	}
	//Write out buffer
	fwrite(writer->bytes, sizeof(unsigned char), writer->length, writer->ofp);
	fwrite(&writer->byte, sizeof(unsigned char), 1, writer->ofp);
	clock_t end = clock();
	double size = ftell(writer->ofp, 0L, SEEK_END) / 1000000;
	double originalsize = inputtext.length / 1000000;
	double ratio = (size / originalsize);
	//printf("Orginal file: %.3f MB | Compressed file: %.3f MB | Compression ratio: %.1f%\n", originalsize, size, ratio);
	double time = (end - start) / CLOCKS_PER_SEC;
	//printf("Compression time: %f\n", time);
	double speed = size / time; 
	//printf("Compression speed: %f MBs\n", speed);
	free_bytewriter(writer);
}

unsigned int* create_frequency_list(text input) {
	//Maybe make this more efficient?
	unsigned int i;
	unsigned int* frequencies = (unsigned int*)malloc(sizeof(unsigned int) * 256);
	for (i = 0; i < 256; i++) {
		frequencies[i] = 0;
	}
	i = 0;
	while (i < input.length) {
		unsigned char x = input.string[i];
		frequencies[x]++;
		x = input.string[i++];
	}
	return frequencies;
}

tree* build_tree(unsigned int* frequencies) {
	pqueue* queue = (pqueue*)malloc(sizeof(pqueue));
	init_pqueue(queue);
	fill_pqueue(frequencies, queue);
	while (queue->length > 1) {
		push_pqueue(queue, merge_trees(pop_pqueue(queue), pop_pqueue(queue)));
	}
	tree* t = pop_pqueue(queue);
	//Queue is empty so can be freed. 
	free(queue);
	return t;
}

void init_code(code* codes, node* currentnode, int currentcode, unsigned int currentlength) {
	if (currentnode->value != '\0') {
		codes[currentnode->value].code = currentcode;
		codes[currentnode->value].length = currentlength;
	}
	else {
		currentcode <<= 1;
		if (currentnode->left) {
			init_code(codes, currentnode->left, currentcode, currentlength + 1);
		}
		if (currentnode->right) {
			currentcode |= 1;
			init_code(codes, currentnode->right, currentcode, currentlength + 1);
		}
	}
}

//Edits currentmax
code* init_codes(tree* t) {
	code* codes = (code*)malloc(sizeof(code) * 256);
	for (unsigned int i = 0; i < 256; i++) {
		codes[i].code = -1;
		codes[i].length = 0;
	}
	init_code(codes, t->root->left, 2, 1);
	init_code(codes, t->root->right, 3, 1);
	return codes; 
}

void write_code(bytewriter* writer, code c) {
	//Mss -1? 
	unsigned int length = c.length;
	int x = c.code &  ~(1 << (length));  //Clear nth bit which was set to create the codes correctly.
	write_bits(writer, x, length);
}

void print_byte(unsigned char byte) {
	for (int i = 7; i >= 0; i--) {
		//int bit = (i >> byte) & 1;
		if ((1 << i) & byte) {
			printf("1");
		}
		else {
			printf("0");
		}
	}
	printf(" ");
}