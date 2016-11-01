#include "filecomparator.h"

int compare_file(char* filename1, char* filename2) {
	bytereader* reader1 = init_bytereader(filename1);
	bytereader* reader2 = init_bytereader(filename2);
	if (reader1->total_size != reader2->total_size) {
		return 0; 
	}
	int finished = read_bytes(reader1);
	read_bytes(reader2);
	while (!finished) {
		for (unsigned long i = 0; i < reader1->text_length; i++) {
			if (reader1->buffer[i] != reader2->buffer[i]) {
				return 0;
			}
		}
		finished = read_bytes(reader1);
		read_bytes(reader2);
	}
	return 1;
}