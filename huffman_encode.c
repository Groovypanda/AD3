#include "huffman_encode.h"

void huffman_encode(textreader* reader, bytewriter* writer) {
	unsigned int* frequencies = create_frequency_list(reader->buffer, reader->text_length);
	tree* t = build_tree(frequencies);
	code_list** codes = init_codes(t);

	fwrite(&reader->text_length, sizeof(unsigned int), 1, writer->ofp);
	write_tree(writer, t);
	for (unsigned long i = 0; i < reader->text_length; i++) {
		unsigned char x = reader->buffer[i];
		write_code_list(writer, codes[x]);
	}

	//Write out buffer
	fwrite(writer->buffer, sizeof(unsigned char), writer->length, writer->ofp);
	if (writer->remaining_bits) {
		fwrite(&writer->byte, sizeof(unsigned char), 1, writer->ofp);
	}
	writer->byte = 0;
	writer->length = 0;
	writer->remaining_bits = 8;

	//Free everything
	free(frequencies);
	free(codes);
	free_tree(t);
}

void encode(char* input, char* output) {
	clock_t start = clock();
	unsigned original_size, encoded_size = 0; 

	textreader* reader = init_textreader(input, "rb");
	bytewriter* writer = init_bytewriter(output);
	//While reading isn't finished, huffman encode.
	
	while (!read_file(reader)) {
		huffman_encode(reader, writer);
	}
	//One last time, to write last bytes. 
	if (reader->text_length) {
		huffman_encode(reader, writer);
	}

	original_size = reader->total_size;
	encoded_size = ftell(writer->ofp);

	free_bytewriter(writer);
	free_textreader(reader);

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
		push_pqueue(queue, merge_trees(pop_pqueue(queue), pop_pqueue(queue)));
	}
	tree* t = pop_pqueue(queue);
	//Queue is empty so can be freed. 
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
			list->codes[i].code = currentcode & ((1 << 32) - 1);
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

void write_code_list(bytewriter* writer, code_list* list) {
	for (unsigned int i = 0; i < list->list_length; i++) {
		code c = list->codes[i];
		write_bits(writer, c.code, c.code_length);
	}
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