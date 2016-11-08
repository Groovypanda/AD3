#include "delta_decode.h"

void specific_huffman_decode(bitreader* reader, bytewriter* writer, delta_buffer* delta_buffer) {
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
			delta_buffer->buffer[delta_buffer->buffer_index] = cur->value;
			delta_buffer->buffer_index++; 
			if (delta_buffer->buffer_index == MAX_BUFFERSIZE+1) {
				delta_buffer->buffer_index = 0;
				delta_decode(delta_buffer, writer);
			}
			cur = root;
		}
	}
	free_tree(t);
}

//Byte index indicates the index in the current long long byte. If this is 8 a full delta was decided, and thus the previous number is known.
//Else the previous number still has to be decided. 
void delta_decode(delta_buffer* delta_buffer, bytewriter* writer) {
	long long current_number, previous_number;
	char comma = ',';
	char* numbers = delta_buffer->buffer;
	if (delta_buffer->byte_index != 0) {
		long long delta = delta_buffer->last_number; 
		for(int i=delta_buffer->byte_index && *numbers; i<8; i++){
			delta *= 10 + (*numbers - '0');
			numbers++;
		}
		current_number = delta_buffer->previous_number + delta;
		fprintf(writer->ofp, "%lld", current_number);
		fwrite(&comma, 1, 1, writer->ofp);
		previous_number = current_number;
	}
	
	while (*numbers) {
		char* nptr = numbers; 
		char* endptr;
		long long delta = strtoll(numbers, &endptr, 10);
		printf("start: %d, end: %d, diff: %d\n",nptr, endptr,  endptr - nptr);
		if(endptr-nptr==8){
			long long current_number;
			current_number = previous_number + delta;
			fprintf(writer->ofp, "%lld", current_number);
			fwrite(&comma, 1, 1, writer->ofp);
			previous_number = current_number;
		}
		else {
			delta_buffer->byte_index = endptr - nptr; 
			delta_buffer->last_number = delta; 
			delta_buffer->previous_number = previous_number;
		}
	}
}

