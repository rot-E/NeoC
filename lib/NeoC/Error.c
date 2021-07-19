#include "NeoC/Error.h"

static void Panic(uint8_t *colour, uint8_t *message) {
	fprintf(stderr, u8"%s%s%s%s%s\n",
		u8"\e[31m",
		u8"[Error] ",
		colour,
		message,
		u8"\e[39m"
	);
	exit(EXIT_FAILURE);
}

__Error _Error = {
	.Panic = Panic,
};
