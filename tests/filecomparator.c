#include "filecomparator.h"

int compare_file(char* filename1, char* filename2) {
	bytereader* reader1 = init_bytereader(filename1);
	bytereader* reader2 = init_bytereader(filename2);
	int correct = 1; 
	if (reader1->total_size != reader2->total_size) {
		return 0; 
	}
	while (!reader1->lastblock) {
		correct = compare_block(reader1, reader2);
		if (!correct) {
			return 0; 
		}
	}
	//Compare the last block. 
	correct = compare_block(reader1, reader2);
	return correct; 
}

int compare_block(bytereader* reader1, bytereader* reader2) {
	for (unsigned long i = 0; i < reader1->text_length; i++) {
		if (reader1->buffer[i] != reader2->buffer[i]) {
			return 0;
		}
	}
	read_block(reader1);
	read_block(reader2);
	return 1; 
}