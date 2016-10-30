#include "filehandler.h"


void write_bits(bytewriter* b, int bits, unsigned int amount) {
	int i = amount - 1; 
		while(i>=0) {
			if (i+1 <= b->remaining_bits) {
				unsigned int shift = b->remaining_bits - i - 1;
				b->byte |= bits << shift;
				b->remaining_bits -= i+1;
				i = -1; 
			}
			else {
				int bit = (bits >> i) & 1;
				b->byte |= (bit << (b->remaining_bits - 1));
				b->remaining_bits--;
				i--;
			}
			if (b->remaining_bits == 0) {
				b->buffer[b->length++] = b->byte;
				if (b->length == MAX_BUFFERSIZE) {
					fwrite(b->buffer, sizeof(unsigned char), MAX_BUFFERSIZE, b->ofp);
					b->length = 0; 
				}
				b->byte = 0;
				b->remaining_bits = 8;
			}
		}
}	


unsigned int read_bits(bytereader* reader, unsigned int amount) {
	textreader* treader = reader->textreader;
	int result = 0;
	unsigned char byte = treader->buffer[reader->index];
	for (unsigned int i = 0; i < amount; i++) {
		//Get nth bit of byte.
		unsigned int i = reader->remaining_bits_amount - 1;
		int bit = (byte >> i) & 1;
		//Set nth bit of result.
		result |= bit;
		reader->remaining_bits_amount--;
		if (!reader->remaining_bits_amount) {
			byte = treader->buffer[++reader->index];
			reader->remaining_bits_amount = 8;
			if (reader->index == MAX_BUFFERSIZE) {
				read_file(reader->textreader);
				reader->index = 0;
			}
		}
		result <<= 1;
	}
	return result >> 1;
}

//Places text which is read into reader->text.
//Specify amount of bytes to be read in reader->amount_to_read, total amount of bytes which are read are updated into reader->length.
int read_file(textreader* reader) {
	size_t read_amount = fread(reader->buffer, sizeof(unsigned char), MAX_BUFFERSIZE, reader->ifp);
	reader->buffer[read_amount] = '\0';
	reader->text_length = read_amount;
	if (read_amount < MAX_BUFFERSIZE) {
		//Return 1 if finished.
		return 1; 
	}
	else {
		return 0;
	}
}

void write_char(textwriter* writer, char c) {
	writer->buffer[writer->index++] = c;
	if (writer->index == MAX_BUFFERSIZE) {
		fwrite(writer->buffer, sizeof(char), MAX_BUFFERSIZE, writer->ofp);
		writer->index = 0;
	}
}

void flush(textwriter* writer) {
	fwrite(writer->buffer, sizeof(char), writer->index, writer->ofp);
}

bytewriter* init_bytewriter(char* filename) {
	bytewriter* writer = (bytewriter*)allocate_memory(sizeof(bytewriter));
	writer->remaining_bits = 8;
	writer->length = 0; 
	writer->byte = 0;
	writer->ofp = fopen(filename, "wb");
	if (!writer->ofp) {
		printf("The given file couldn't be opened. (File: %s)\n", filename);
	}
	return writer;
}

bytereader* init_bytereader(char* filename) {
	bytereader* reader = (bytereader*)allocate_memory(sizeof(bytereader));
	reader->index = 0;
	reader->remaining_bits_amount = 8; 
	reader->textreader = init_textreader(filename, "rb");
	return reader;
}

textreader* init_textreader(char* filename, char* mode) {
	textreader* reader = (textreader*)allocate_memory(sizeof(textreader));
	reader->ifp = fopen(filename, mode);
	fseek(reader->ifp, 0, SEEK_END);
	reader->total_size = ftell(reader->ifp);
	rewind(reader->ifp);
	return reader; 
}

textwriter* init_textwriter(char* filename) {
	textwriter* writer = (textwriter*)allocate_memory(sizeof(textwriter));
	writer->ofp = fopen(filename, "wb");
	writer->index = 0; 
	return writer; 
}

void free_textreader(textreader* reader) {
	fclose(reader->ifp);
	free(reader);
}

void free_bytewriter(bytewriter* writer) {
	fclose(writer->ofp);
	free(writer);
}

void free_bytereader(bytereader* reader) {
	free_textreader(reader->textreader);
	free(reader);
}

void free_textwriter(textwriter* writer) {
	fclose(writer->ofp);
	free(writer);
}


void write_tree_recurse(bytewriter* writer, node* n) {
	if (n->left && n->right) {
		write_bits(writer, 0, 1);
		write_tree_recurse(writer, n->left);
		write_tree_recurse(writer, n->right);
	}
	else {
		write_bits(writer, 1, 1);
		write_bits(writer, n->value, 8);	
	}
}

void write_tree(bytewriter* writer, tree* t) {
	if (t->root) {
		write_tree_recurse(writer, t->root);
	}
}

void read_tree_recurse(bytereader* reader, node* n) {
	n->frequency = 0;
	unsigned int bit = read_bits(reader, 1);
	if (bit) {
		n->value = read_bits(reader, 8);
		n->left = NULL; 
		n->right = NULL; 
	}
	else {
		n->left = (node*)allocate_memory(sizeof(node));
		n->right = (node*)allocate_memory(sizeof(node));
		read_tree_recurse(reader, n->left);
		read_tree_recurse(reader, n->right);
	}
}

tree* read_tree(bytereader* reader) {
	tree* t = (tree*)allocate_memory(sizeof(tree));
	t->root = (node*)allocate_memory(sizeof(node));
	read_tree_recurse(reader, t->root);
	return t;
}
