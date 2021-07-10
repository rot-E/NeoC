#pragma once

#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>

#include "Annotation.h"
#include "Exception.h"
#include "Setup.h"

typedef struct {
	private void (* _Setup)();

	public final uint32_t Exception;

	/* 確保系 */
	public void *(* Allocate)(const size_t size) throws (Memory.Exception);
	public void *(* CountedAllocate)(const size_t n, const size_t size) throws (Memory.Exception);
	public void *(* SharedAllocate)(const size_t size) throws (Memory.Exception);

	/* 再確保系 */
	public void *(* ReAllocate)(void *ptr, const size_t size) throws (Memory.Exception);
	public void *(* ReCountedAllocate)(void *ptr, const size_t n, const size_t size) throws (Memory.Exception);

	/* 解放系 */
	public void (* Free)(void *ptr);
} _Memory;

extern _Memory Memory;
