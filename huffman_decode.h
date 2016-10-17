#ifndef HUFFMAN_DECODE_H
#define HUFFMAN_DECODE_H

#include <stdio.h>
#include <stdlib.h>
#include "filehandler.h"
//For build tree  function
#include "huffman_encode.h"

//This functions decodes a huffman tree. 
void decode(char* filename, char* filename_decoded);

#endif