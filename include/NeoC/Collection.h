#pragma once

/* ------------------------------------------------------ */
#define in(...)

#define Comparator(X, Y, EqEvaFm)			\
	({										\
		bool _cmptr(void *X, void *Y) {		\
			return EqEvaFm;					\
		};									\
		_cmptr;								\
	})
/* ------------------------------------------------------ */

#include <stdint.h>
#include <stdbool.h>
#include <threads.h>

#include "NeoC/Annotation.h"
#include "NeoC/Object.h"
#include "NeoC/Memory.h"

class Collection_t {
	private int32_t _Size;
	private int32_t _Length;
	private mtx_t _Mtx;

	public int32_t (* GetLength)(derived *);
	public bool (* IsEmpty)(derived *);
} Collection_t;

class _Collection {
	public void (* Init)(Collection_t *);
	public void (* Delete)(Collection_t *);

	public int32_t (* GetLength)(derived *);
	public bool (* IsEmpty)(derived *);
} _Collection;

extern _Collection Collection;
