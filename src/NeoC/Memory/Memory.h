#pragma once

#include <stdlib.h>
#include <sys/mman.h>

typedef struct {
	void (* HANDLER)();
	void *(* Allocate)(const size_t size);
	void *(* CountedAllocate)(const size_t num, const size_t size);
	void *(* SharedAllocate)(const size_t size);
} _Memory;

extern _Memory Memory;
