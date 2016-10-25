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
				b->byte |= bit << b->remaining_bits - 1;
				b->remaining_bits--;
				i--;
			}
			if (b->remaining_bits == 0) {
				b->bytes[b->length++] = b->byte;
				if (b->length == b->buffersize) {
					b->buffersize *= 2; 
					b->bytes = (unsigned char*)realloc(b->bytes, b->buffersize);
					if (b->buffersize >= 500000000) {
						printf("ERROR: BUFFERSIZE IS TO HIGH");
					}
				}
				b->byte = 0;
				b->remaining_bits = 8;
			}
		}
}	


unsigned int read_bits(bytereader* reader, unsigned int amount) {
	assert(amount > 0);
	int result = 0;
	unsigned char byte = reader->bytes[reader->index];
	for (unsigned int i = 0; i < amount; i++) {
		//Get nth bit of byte.
		unsigned int index = reader->remaining_bits_amount - 1;
		int bit = (byte >> index) & 1;
		//Set nth bit of result.
		result |= bit;
		reader->remaining_bits_amount--;
		if (!reader->remaining_bits_amount) {
			byte = reader->bytes[++reader->index];
			reader->remaining_bits_amount = 8;
		}
		result <<= 1;
	}
	return result >> 1;
}


text read_file(char* filename) {
	FILE *fp;
	unsigned char* buffer;
	text input; 
	/* Open file for both reading and writing */
	fp = fopen(filename, "r");
	fseek(fp, 0, SEEK_END);
	//Add 1 place for end of file. 
	unsigned int size = ftell(fp);

	/* Seek to the beginning of the file */
	rewind(fp);

	buffer = (unsigned char*)malloc(sizeof(unsigned char)*size + 1);

	/* Read and return data, we ignore the [ and ] */
	fread(buffer, size, 1, fp);
	fclose(fp);

	//Add end of file to buffer
	buffer[size] = '\0';
	input.length = size; 
	input.string = buffer; 
	return input;
}


unsigned char* read_binary_file(char* filename) {
	FILE *fp;
	unsigned char* buffer;

	/* Open file for both reading and writing */
	fp = fopen(filename, "rb");
	if (!fp) {
		throw_error(FILE_ERROR);
	}

	fseek(fp, 0, SEEK_END);
	unsigned int size = ftell(fp);

	/* Seek to the beginning of the file */
	rewind(fp);

	buffer =(unsigned char*) allocate_memory(sizeof(unsigned char)*size + 1);

	buffer[size] = '\0';
	//buffer[size] = '\0';

	/* Read and return data, we ignore the [ and ] */
	fread(buffer, size, 1, fp);
	fclose(fp);
	return buffer; 
}

bytewriter* init_bytewriter(char* filename) {
	bytewriter* writer = (bytewriter*)allocate_memory(sizeof(bytewriter));
	writer->remaining_bits = 8;
	writer->buffersize = 100;  
	writer->length = 0; 
	writer->byte = 0;
	writer->ofp = fopen(filename, "wb");
	if (!writer->ofp) {
		printf("The given file couldn't be opened. (File: %s)\n", filename);
	}
	writer->bytes = (unsigned char*)allocate_memory(sizeof(unsigned char)*writer->buffersize);
	return writer;
}

bytereader* init_bytereader(char* filename) {
	bytereader* reader = (bytereader*)allocate_memory(sizeof(bytereader));
	reader->index = 0;
	reader->remaining_bits_amount = 8;
	reader->bytes = read_binary_file(filename);
	return reader;
}

void free_bytewriter(bytewriter* writer) {
	fclose(writer->ofp);
	free(writer);
}

void free_bytereader(bytereader* reader) {
	free(reader->bytes);
	free(reader);
}

void print_binary_file(char* filename) {
	FILE *fp;
	unsigned char* buffer;

	/* Open file for both reading and writing */
	fp = fopen(filename, "rb");

	fseek(fp, 0, SEEK_END);
	unsigned int size = ftell(fp);

	/* Seek to the beginning of the file */
	rewind(fp);

	buffer = (unsigned char*)malloc(sizeof(unsigned char)*size + 1);

	/* Read and return data, we ignore the [ and ] */
	fread(buffer, size, 1, fp);
	fclose(fp);
	printf("--------\n");
	for (unsigned int i = 0; i < size; i++) {
		printf("%d\n", buffer[i]);
	}
	printf("--------\n");
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
		n->value = '\0';
		n->left = (node*)malloc(sizeof(node));
		n->right = (node*)malloc(sizeof(node));
		read_tree_recurse(reader, n->left);
		read_tree_recurse(reader, n->right);
	}
}

tree* read_tree(bytereader* reader) {
	tree* t = (tree*)malloc(sizeof(tree));
	t->root = (node*)malloc(sizeof(node));
	read_tree_recurse(reader, t->root);
	return t;
}
