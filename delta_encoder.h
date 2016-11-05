
#include "bytehandler.h"
#include "encoder.h"
//For testing purposes
#include "statistics.h"
#include "debug.h"
#include "math.h"

void delta_encode(char* input, char* output);
void delta_encode_block(bytereader* reader, bitwriter* writer);