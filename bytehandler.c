#include "bytehandler.h"

//Places text which is read into reader->text.
//Specify amount of bytes to be read in reader->amount_to_read, total amount of bytes which are read are updated into reader->length.
int read_bytes(bytereader* reader) {
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

void write_byte(bytewriter* writer, char c) {
	writer->buffer[writer->index++] = c;
	if (writer->index == MAX_BUFFERSIZE) {
		fwrite(writer->buffer, sizeof(char), MAX_BUFFERSIZE, writer->ofp);
		writer->index = 0;
	}
}

void flush_bytes(bytewriter* writer) {
	fwrite(writer->buffer, sizeof(char), writer->index, writer->ofp);
	writer->index = 0; 
}

bytereader* init_bytereader(char* filename) {
	bytereader* reader = (bytereader*)allocate_memory(sizeof(bytereader));
	reader->ifp = open_file(filename, "rb");  
	fseek(reader->ifp, 0, SEEK_END);
	reader->total_size = ftell(reader->ifp);
	rewind(reader->ifp);
	return reader;
}

bytewriter* init_bytewriter(char* filename) {
	bytewriter* writer = (bytewriter*)allocate_memory(sizeof(bytewriter));
	writer->ofp = open_file(filename, "wb");
	writer->index = 0;
	return writer;
}



void free_bytereader(bytereader* reader) {
	fclose(reader->ifp);
	free(reader);
}


void free_bytewriter(bytewriter* writer) {
	fclose(writer->ofp);
	free(writer);
}



