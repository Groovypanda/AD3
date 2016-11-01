#ifndef FILECOMPARATOR_H
#define FILECOMPARATOR_H

/**
	filecomparator.h 
	Purpose: comparing if the contents of 2 files are equal.
*/

#include <stdio.h>
#include "bytehandler.h"

/**
	Compares the content of 2 files
	@param filename1, filename2 The 2 files which should be compared
	@return Returns 1 if the files are equal, 0 otherwise.
*/
int compare_file(char* filename1, char* filename2);

#endif 