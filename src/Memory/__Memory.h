#pragma once

#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>

#include "Annotation.h"

typedef struct {
	protected void (* _HANDLER)();

	/* 確保系 */
	public void *(* Allocate)(const size_t size);
	public void *(* CountedAllocate)(const size_t n, const size_t size);
	public void *(* SharedAllocate)(const size_t size);

	/* 再確保系 */
	public void *(* ReAllocate)(void *ptr, const size_t size);
	public void *(* ReCountedAllocate)(void *ptr, const size_t n, const size_t size);

	/* 解放系 */
	public void (* Free)(void *ptr);
} ___Memory;

extern ___Memory __Memory;
