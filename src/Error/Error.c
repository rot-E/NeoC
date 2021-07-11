#include "Error.h"

static void Panic(uint8_t *colour, uint8_t *message) {
	fprintf(stderr, "%s%s%s%s%s\n",
		"\e[31m",
		"[Error] ",
		colour,
		message,
		"\e[39m"
	);
	exit(EXIT_FAILURE);
}

__Error _Error = {
	.Panic = Panic,
};
