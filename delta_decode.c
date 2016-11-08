#include "delta_decode.h"


void specific_huffman_decode(bitreader* reader, deltadecoder* decoder) {
	unsigned int i = 0, text_length;
	int is_maxsize = read_bits(reader, 1);
	if (!is_maxsize) {
		text_length = MAX_BUFFERSIZE;
	}
	else {
		text_length = read_bits(reader, 32);
	}
	tree* t = read_tree(reader);
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
			decoder->inputbuffer[decoder->inputbuffer_index++] = cur->value;
			if (decoder->inputbuffer_index == MAX_BUFFERSIZE) {
				decoder->inputbuffer_index = 0;
				delta_decode(decoder);
			}
			cur = root;
		}
	}
	free_tree(t);
}

//Byte index indicates the index in the current long long byte. If this is 8 a full delta was decided, and thus the previous number is known.
//Else the previous number still has to be decided. 
void delta_decode(deltadecoder* decoder) {
	unsigned long long current_number, previous_number = decoder->previous_number;
	unsigned long long* numbers = (unsigned long long*) decoder->inputbuffer;

	for(int i=0; i<MAX_BUFFERSIZE/8; i++, numbers++){
		unsigned long long delta = *numbers;
		current_number = previous_number + delta;
		write_long(decoder->writer, current_number);
		previous_number = current_number;
	}
	decoder->previous_number = previous_number;
	
}

void write_long(bytewriter* writer, unsigned long long number) {
	int amount = snprintf(writer->buffer + writer->index, MAX_BUFFERSIZE - writer->index, "%llu", number);
	writer->index += amount;
	if (amount > MAX_BUFFERSIZE - writer->index - 1) { //If less bytes are written than should've been written, write out the other bytes. 
		fwrite(writer->buffer, sizeof(char), MAX_BUFFERSIZE, writer->ofp);
		int amount_to_write = amount + writer->index - MAX_BUFFERSIZE + 1;
		writer->index = 0;
		char remainder[20]; //A 64 bit number can't have more than 19 numbers. 
		snprintf(remainder, 20, "%lld", number);
		for (int i = amount_to_write - 1, j = amount - amount_to_write; i >= 0; i--) {
			writer->buffer[writer->index++] = remainder[j++];
		}
	}
	write_byte(writer, ',');
}

deltadecoder* init_deltadecoder(bytewriter* writer) {
	deltadecoder* decoder = (deltadecoder*)malloc(sizeof(deltadecoder));
	decoder->previous_number = 0;
	decoder->inputbuffer_index = 0;
	decoder->writer = writer;
	write_byte(writer, '[');
	return decoder; 
}

void finish_deltadecoder(deltadecoder* decoder) {
	bytewriter* writer = decoder->writer;
	writer->buffer[writer->index - 1] = ']'; //Change trailing comma to ].
	fwrite(writer->buffer, 1, writer->index, writer->ofp);
}