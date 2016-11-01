#ifndef code_H
#define code_H

/**
	codelist.h
	The datastructure for saving a single code. The code can have a length between 0 and 255. There's no datatype which can store
	255 bits, so a list of codes is necessary. 
*/

#include <stdio.h>
#include "tree.h"
#include "bithandler.h"

/**
	A struct for saving a  code.
*/
typedef struct code {
	int* value; //big endian!
	unsigned int length;
	unsigned int size; 
} code;

/**
	Recursively create all codes by going down the tree. If the left path is taken (to the left child), a 0
	is added to the code, else a 1 is added. If the currentnode is a leaf, list of codes (usually a list of size 1) is placed in the correct
	place in the list of lists of codes. The index of a code in the list of codes is defined by the value of the leaf. 
	@param codes A list of codes. Each index represents the code for the value indicated by the index. 
	This variable will be initialised when the function ends.
	@param currentnode The current node in the recursion. 
	@param currentcode The current code in the recursion.
	@param currentlength The length of the current code in the recursion.
*/
void init_code(code* codes, node* currentnode, int* currentcode, unsigned int currentlength, unsigned int currentsize);

/**
	Creates a list of codes from a tree by traversing the tree in order. 
	The code for a value is indicated by the index. For example index 97 contains the code for character 'a'. 
	@param t A huffmantree from which the codes will be formed. 
	@return An initialised code array.
*/
code* init_codes(tree* t);

/**
	A function which frees all of the memory of a list of codes. 
	@param codes The code array which should be freed.
*/
void free_codes(code* codes);

/**
	Writes a code to the bitwriter.
	@param writer The bitwriter to which the code should be written.
	@param code The code which should be written.
*/
void write_code(bitwriter* writer, code code);

#endif 