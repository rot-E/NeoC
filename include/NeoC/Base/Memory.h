#pragma once

/* ------------------------------------------------------ */
#define $(T, VAL)										\
	({													\
		T *_tmp = (T *)(_Memory.Allocate(sizeof(T)));	\
		*_tmp = VAL;									\
		_tmp;											\
	})
/* ------------------------------------------------------ */

#include <stdlib.h>
#include <sys/mman.h>
#include "NeoC/Base/Object.h"
#include "NeoC/Base/Error.h"

class __Memory {
	/* 確保系 */
	public any *(* Allocate)(const size_t size);
	public any *(* CountedAllocate)(const size_t n, const size_t size);
	public any *(* SharedAllocate)(const size_t size);

	/* 再確保系 */
	public any *(* ReAllocate)(any *ptr, const size_t size);

	/* 解放系 */
	public void (* Free)(any *ptr);
	public void (* SharedFree)(any *ptr, const size_t size);
} __Memory;

extern __Memory _Memory;
