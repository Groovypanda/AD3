
#include "bytehandler.h"
#include "decoder.h"
//For testing purposes
#include "statistics.h"
#include "debug.h"

void delta_decode_block(bytereader* reader, bytewriter* writer);
void delta_decode(char* input, char* output);
