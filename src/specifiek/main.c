#include <string.h>
#include "specific_coder.h"
#include "../gedeeld/errorhandler.h"


int main(int argc, char* argv[]) {
	if (argc != 4) {
		shutdown(USAGE_ERROR);
	}
	else if (strcmp(argv[1], "-c") == 0) {
		specific_encode(argv[2], argv[3]);
	}
	else if (strcmp(argv[1], "-d") == 0) {
		specific_decode(argv[2], argv[3]);
	}
	else {
		shutdown(USAGE_ERROR);
	}
	return 0;
}

