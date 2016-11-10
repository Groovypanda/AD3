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
	while (decoder->inputbuffer_index < MAX_BUFFERSIZE) {
		unsigned long long delta = read_number(decoder);
		current_number = previous_number + delta;
		write_long(decoder->writer, current_number);
		previous_number = current_number;

	}
	decoder->previous_number = previous_number;
	
}

//Variable length quantity
unsigned long long read_number(deltadecoder* decoder) {
	char current_byte = decoder->inputbuffer[decoder->inputbuffer_index];
	unsigned char continue_reading = current_byte & 0x80; //Get most significant bit. 
	unsigned long long value = 0; 
	while (continue_reading) {
		value |= current_byte & 0x7F; //Add 7 bits.
		value <<= 7; //Make space for next 7 bits. 
		continue_reading = current_byte & 0x80; //Check most significant bit. 
	}
	value |= current_byte; //Most significant bit is zero. 
	return value;
}


void write_long(bytewriter* writer, unsigned long long number) {
	int amount = snprintf(writer->buffer + writer->index, MAX_BUFFERSIZE - writer->index+1, "%llu", number);
	if (writer->index + amount == MAX_BUFFERSIZE) { //Write out the buffer
		fwrite(writer->buffer, sizeof(char), MAX_BUFFERSIZE, writer->ofp);
		writer->index = 0;
	}
	else if (writer->index + amount > MAX_BUFFERSIZE) { //If less bytes are written than should've been written, write out the other bytes.
			fwrite(writer->buffer, sizeof(char), MAX_BUFFERSIZE, writer->ofp);
			int amount_to_write = amount + writer->index - MAX_BUFFERSIZE;
			writer->index = 0;
			char remainder[20]; //A 64 bit number can't have more than 19 numbers. 
			snprintf(remainder, 20, "%llu", number);
			for (int i = amount_to_write - 1, j = amount - amount_to_write; i >= 0; i--) {
				writer->buffer[writer->index++] = remainder[j++];
			}
		}
	else {
		writer->index += amount;
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
	if (decoder->inputbuffer_index != 0) {
		delta_decode(decoder, decoder->inputbuffer_index/8);
	}
	bytewriter* writer = decoder->writer;
	writer->buffer[writer->index - 1] = ']'; //Change trailing comma to ].
	fwrite(writer->buffer, 1, writer->index, writer->ofp);
}