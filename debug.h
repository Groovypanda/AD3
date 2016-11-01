#ifndef DEBUG_H
#define DEBUG_H

/**
	debug.h
	Purpose: Enabling debugging. 
	Set variables to 1 if you want to test & output the encoding and decoding. 
*/

#include <stdio.h>

#define DEBUG 1 //If you want to debug.
#define OUTPUT 0 //If you want to output.
#define TREE 0 //If you want to output trees.
#define STATISTICS 1 //If you want to show statistics about runtime. This doesn't check if OUTPUT is on or off. 
#define STEPS 0 //If you want to debug in steps. 
#define COMPARE 0 //This will check if compression is correct.

#endif 