#pragma once

#include <stdbool.h>
#include "NeoC/Base/Object.h"

class Bool_t {
	private bool _bool;
} Bool_t;

class _Bool_ {
	public Bool_t *(* Init)(Bool_t *);
	public Bool_t *(* New)();
	public void (* Delete)(Bool_t *);

	public bool (* Unpack)(self_t *);

	public self_t (* Not)(self_t *);
	public self_t (* And)(self_t *, self_t *);
	public self_t (* Or)(self_t *, self_t *);
	public self_t (* Nand)(self_t *, self_t *);
	public self_t (* Nor)(self_t *, self_t *);
} _Bool_;

extern _Bool_ Bool;
