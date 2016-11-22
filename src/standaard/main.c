#include <string.h>
#include "standard_coder.h"
#include "../gedeeld/errorhandler.h"

int main(int argc, char* argv[]) {
	if (argc != 4) {
		shutdown(USAGE_ERROR);
	}
	else if (strcmp(argv[1], "-c") == 0) {
		standard_encode(argv[2], argv[3]);
	}
	else if (strcmp(argv[1], "-d") == 0) {
		standard_decode(argv[2], argv[3]);
	}
	else {
		shutdown(USAGE_ERROR);
	}
	return 0;
}
