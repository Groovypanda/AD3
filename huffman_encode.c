#include "huffman_encode.h"

void huffman_encode(bytereader* reader, bitwriter* writer) {
	unsigned int* frequencies = create_frequency_list(reader->buffer, reader->text_length);
	tree* t = build_tree(frequencies);
	code_list** codes = init_codes(t);

	fwrite(&reader->text_length, sizeof(unsigned int), 1, writer->bytewriter->ofp);
	write_tree(writer, t);
	for (unsigned long i = 0; i < reader->text_length; i++) {
		unsigned char x = reader->buffer[i];
		write_code_list(writer, codes[x]);
	}

	//Write out buffer
	flush_bits(writer);

	//Free everything
	free(frequencies);
	free_code_list(codes);
	free_tree(t);
}

void encode(char* input, char* output) {
	clock_t start = clock();
	unsigned original_size, encoded_size = 0; 
	bytereader* reader = init_bytereader(input, "rb");
	bitwriter* writer = init_bitwriter(output);
	//While reading isn't finished, huffman encode.
	
	while (!read_bytes(reader)) {
		huffman_encode(reader, writer);
	}
	//One last time, to write last bytes. 
	if (reader->text_length) {
		huffman_encode(reader, writer);
	}
	original_size = reader->total_size;
	encoded_size = ftell(writer->bytewriter->ofp);

	free_bitwriter(writer);
	free_bytereader(reader);

	clock_t end = clock();
	print_statistics_compression(original_size,encoded_size);
	print_statistics_time("Compression", start, end);
	print_statics_speed("Compression", start, end, original_size);
	

}

unsigned int* create_frequency_list(char* text, unsigned int length) {
	unsigned int i;
	unsigned int* frequencies = (unsigned int*)allocate_memory(sizeof(unsigned int) * 256);
	for (i = 0; i < 256; i++) {
		frequencies[i] = 0;
	}
	i = 0;
	while (i < length) {
		unsigned char x = text[i];
		frequencies[x]++;
		x = text[i++];
	}
	return frequencies;
}

tree* build_tree(unsigned int* frequencies) {
	pqueue* queue = (pqueue*)allocate_memory(sizeof(pqueue));
	init_pqueue(queue);
	fill_pqueue(frequencies, queue);
	while (queue->length > 1) {
		tree* t1 = pop_pqueue(queue);
		tree* t2 = pop_pqueue(queue);
		push_pqueue(queue, merge_trees(t1, t2));
	}
	tree* t = pop_pqueue(queue);
	//Queue is empty so can be freed. 
	free(queue->list);
	free(queue);
	return t;
}

void init_code(code_list** codes, node* currentnode, int currentcode, unsigned int currentlength) {
	if (currentnode->left && currentnode->right) {
		currentcode <<= 1;
		currentlength++;
		init_code(codes, currentnode->left, currentcode, currentlength);
		currentcode |= 1;
		init_code(codes, currentnode->right, currentcode, currentlength);
	}
	else {
		unsigned int amount = currentlength / 32 + 1;
		code_list* list = codes[currentnode->value];
		list->list_length = amount;
		list->codes = (code*)allocate_memory(sizeof(code)*amount);
		for (unsigned int i = 0; i < amount; i++) {
			list->codes[i].code = currentcode;
			list->codes[i].code_length = 32;
			currentcode >>= 32;
		}
		list->codes[amount - 1].code_length = currentlength % 32;
		codes[currentnode->value] = list;
	}
}

//Edits currentmax
code_list** init_codes(tree* t) {
	//For every value, 1 code_list.
	code_list** codes = (code_list**)allocate_memory(sizeof(code_list*) * 256);
	for (unsigned int i = 0; i < 256; i++) {
		codes[i] = (code_list*)allocate_memory(sizeof(code_list));
		codes[i]->list_length = 0;
	}
	init_code(codes, t->root, 0, 0);
	return codes; 
}

void free_code_list(code_list** codes) {
	for (unsigned int i = 0; i < 256; i++) {
		if (codes[i]->list_length) {
			free(codes[i]->codes);
		}
		free(codes[i]);
	}
	free(codes);
}

void write_code_list(bitwriter* writer, code_list* list) {
	for (unsigned int i = 0; i < list->list_length; i++) {
		code c = list->codes[i];
		write_bits(writer, c.code, c.code_length);
	}
}

void print_byte(unsigned char byte) {
	for (int i = 7; i >= 0; i--) {
		if ((1 << i) & byte) {
			printf("1");
		}
		else {
			printf("0");
		}
	}
	printf(" ");
}