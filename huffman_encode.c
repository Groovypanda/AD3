#include "huffman_encode.h"

#define INTERVAL(time1, time2) time2-time1

void write_code(bytewriter* writer, code c);
void print_byte(unsigned char byte);

//This function returns the encoded huffman tree. 
void encode(char* input, char* filename) {
	clock_t start = clock();
	text inputtext = read_file(input);
	unsigned char* string = inputtext.string;
	unsigned int* frequencies = create_frequency_list(inputtext);
	tree* t = build_tree(frequencies);
	code* codes = init_codes(t);

	bytewriter* writer = init_bytewriter(filename);
	write_tree(writer, t);

	for (unsigned long i = 0; i < inputtext.length; i++) {
		write_code(writer, codes[string[i]]);
	}
	//Write out buffer
	fwrite(writer->bytes, sizeof(unsigned char), writer->length, writer->ofp);
	fwrite(&writer->byte, sizeof(unsigned char), 1, writer->ofp);
	clock_t end = clock();
	double size = ftell(writer->ofp, 0L, SEEK_END);
	print_statistics_compression(size, inputtext.length);
	print_statistics_time("Compression", start, end);
	print_statics_speed("Compression", start, end, size);
	//Free everything
	free(frequencies);
	free(codes);
	free(string);
	free_tree(t);
	free_bytewriter(writer);
}

unsigned int* create_frequency_list(text input) {
	//Maybe make this more efficient?
	unsigned int i;
	unsigned int* frequencies = (unsigned int*)allocate_memory(sizeof(unsigned int) * 256);
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
	pqueue* queue = (pqueue*)allocate_memory(sizeof(pqueue));
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
	code* codes = (code*)allocate_memory(sizeof(code) * 256);
	if (!codes) {

	}
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