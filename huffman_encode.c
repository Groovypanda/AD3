#include "huffman_encode.h"

void huffman_encode(bytereader* reader, bitwriter* writer) {
	unsigned int* frequencies = create_frequency_list(reader->buffer, reader->text_length);
	tree* t = build_huffmantree(frequencies);
	
	code* codes = init_codes(t);
	write_bits(writer, reader->text_length, 8*sizeof(unsigned int));
	if (OUTPUT) {
		printf("Text length: %d\n", reader->text_length);
		print_tree(t);
	}
	write_tree(writer, t);

	for (unsigned int i = 0; i < reader->text_length; i++) {
		unsigned char x = reader->buffer[i];
		write_code(writer, codes[x]);
	}

	//Free everything
	free(frequencies);
	free_codes(codes);
	free_tree(t);
}

void encode(char* input, char* output) {
	clock_t start = clock();
	unsigned long long original_size, encoded_size = 0; 
	bytereader* reader = init_bytereader(input);
	bitwriter* writer = init_bitwriter(output);
	//While reading isn't finished, huffman encode.
	int block= 0; 
	while (!reader->lastblock) {
		if (OUTPUT) {
			printf("=======================\nBlock %d\n=======================\n", block++);
		}
		huffman_encode(reader, writer);
		read_block(reader);
	}
	//One last time, to write last bytes. 
	if (reader->text_length) {
		if (OUTPUT) {
			printf("=======================\nBlock %d\n=======================\n", block++);
		}
		huffman_encode(reader, writer);
	}

	flush_bits(writer);
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

tree* build_huffmantree(unsigned int* frequencies) {
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