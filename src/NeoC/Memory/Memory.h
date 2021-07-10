#pragma once

#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>

#include "Annotation.h"

typedef struct {
	protected void (* _HANDLER)();
	public void *(* Allocate)(const size_t size);
	public void *(* CountedAllocate)(const size_t num, const size_t size);
	public void *(* SharedAllocate)(const size_t size);
} _Memory;

extern _Memory Memory;
