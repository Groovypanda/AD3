#ifndef HUFFMAN_DECODE_H
#define HUFFMAN_DECODE_H

#include <stdio.h>
#include <stdlib.h>
#include "bytehandler.h"
#include "tree.h"
#include "errorhandler.h"
#include "statistics.h"

//This functions decodes a huffman tree. 
void decode(char* filename, char* filename_decoded);

#endif