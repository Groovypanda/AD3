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
			//Instead of writing the output to a file (as the initial algorithm), now the output will be saved into a buffer which should be delta decoded when full.
			decoder->inputbuffer[decoder->inputbuffer_index++] = cur->value;
			if (decoder->inputbuffer_index == MAX_BUFFERSIZE) { 
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
	decoder->inputbuffer_length = decoder->inputbuffer_index; //Save the size
	decoder->inputbuffer_index = 0; //Reset the index
	unsigned long long current_number, previous_number = decoder->previous_number;
	//Check if the decoder had finished reading its last number. If not continue with the last number.
	if (!decoder->finished) { //Complete the last delta if necessary
		unsigned long long delta = read_number(decoder, decoder->current_number);
		current_number = previous_number + delta;
		write_long(decoder->writer, current_number); 
		write_byte(decoder->writer, ','); //One comma after each number. 
		previous_number = current_number;
	}

	while (decoder->inputbuffer_index < decoder->inputbuffer_length) { //Decode all delta values in the inputbuffer.
		unsigned long long delta = read_number(decoder, 0); //Read the next delta
		if (!decoder->finished) { //If the decoder didn't finish reading the number, place the current delta into current_number.
			decoder->current_number = delta; 
		}
		else {
			current_number = previous_number + delta; //Calculate the actual number
			write_long(decoder->writer, current_number); //Write this number with the bytewriter
			write_byte(decoder->writer, ','); //Append with a comma
			previous_number = current_number; //The new previous number is the current number
		}
	}
	decoder->previous_number = previous_number; //Save the previous_number
	decoder->inputbuffer_index = 0; //Reset the index
}

//Variable length quantity
unsigned long long read_number(deltadecoder* decoder, unsigned long long value) { //The given value will be filled with the bits from the inputstream. In a default case value should be zero. 
	unsigned char current_byte = decoder->inputbuffer[decoder->inputbuffer_index++];
	unsigned char continue_reading = current_byte & 0x80; //Get most significant bit. 
	while (continue_reading && decoder->inputbuffer_index < decoder->inputbuffer_length) {
		value |= current_byte & 0x7F; //Add 7 bits.
		value <<= 7; //Make space for next 7 bits. 
		current_byte = decoder->inputbuffer[decoder->inputbuffer_index++]; //Read next byte. 
		continue_reading = current_byte & 0x80; //Check most significant bit. 
	}
	value |= current_byte & 0x7F;
	//If most significant bit wasn't zero, the read number function didn't finish. 
	if (continue_reading) {
		value <<= 7; //Make space for next bits. 
		decoder->finished = 0;
	}
	else {
		decoder->finished = 1; 
	}
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
}

deltadecoder* init_deltadecoder(bytewriter* writer) {
	deltadecoder* decoder = (deltadecoder*)malloc(sizeof(deltadecoder));
	decoder->previous_number = 0;
	decoder->inputbuffer_index = 0;
	decoder->writer = writer;
	decoder->finished = 1; //Default case 
	decoder->current_number = 0; 
	write_byte(writer, '[');
	return decoder; 
}

void finish_deltadecoder(deltadecoder* decoder) {
	if (decoder->inputbuffer_index != 0) {
		delta_decode(decoder);
	}
	bytewriter* writer = decoder->writer;
	writer->buffer[writer->index - 1] = ']'; //Change trailing comma to ].
	fwrite(writer->buffer, 1, writer->index, writer->ofp);
}