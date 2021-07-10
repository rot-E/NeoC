#include "Memory.h"

static void _DEFAULT_HANDLER() {
	fprintf(stderr, "%s%s%s%s%s\n",
		"\e[31m",
		"[Error] ",
		"\e[36m",
		"Memory System",
		"\e[39m"
	);
	exit(EXIT_FAILURE);
}

static void *Allocate(const size_t size) {
	void *pointer = malloc(size);
	if (pointer == NULL) Memory._HANDLER();

	return pointer;
}

static void *CountedAllocate(const size_t num, const size_t size) {
	void *pointer = calloc(num, size);
	if (pointer == NULL) Memory._HANDLER();

	return pointer;
}

static void *SharedAllocate(const size_t size) {
	void *pointer = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (pointer == NULL) Memory._HANDLER();

	return pointer;
}

_Memory Memory = {
	._HANDLER				= _DEFAULT_HANDLER,
	.Allocate				= Allocate,
	.CountedAllocate		= CountedAllocate,
	.SharedAllocate			= SharedAllocate,
};
