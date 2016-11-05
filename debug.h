#ifndef DEBUG_H
#define DEBUG_H

/**
	debug.h
	Purpose: Enabling debugging. 
	Set variables to 1 if you want to test & output the encoding and decoding. 
*/

#include <stdio.h>

#define DEBUG 1 //If you want to debug.
#define HUFFMAN_OUTPUT 0 //If you want to output huffman.
#define DELTA_OUTPUT 0 //If you want to output delta.
#define TREE 0 //If you want to output trees.
#define HUFFMAN_STATISTICS 0 //If you want to show statistics about huffman runtime. This doesn't check if HUFFMAN_OUTPUT is on or off. 
#define DELTA_STATISTICS 1 //If you want to show statistics about delta runtime. This doesn't check if DELTA_OUTPUT is on or off. 
#define STEPS 0 //If you want to debug in steps. 
#define COMPARE 1 //This will check if compression is correct.

#endif 