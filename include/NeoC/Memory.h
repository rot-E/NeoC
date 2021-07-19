#pragma once

#include <stdlib.h>
#include <sys/mman.h>

#include "Annotation.h"
#include "Error.h"

typedef struct {
	/* 確保系 */
	public void *(* Allocate)(const size_t size);
	public void *(* CountedAllocate)(const size_t n, const size_t size);
	public void *(* SharedAllocate)(const size_t size);

	/* 再確保系 */
	public void *(* ReAllocate)(void *ptr, const size_t size);

	/* 解放系 */
	public void (* Free)(void *ptr);
} __Memory;

extern __Memory _Memory;
