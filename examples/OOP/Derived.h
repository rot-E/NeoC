#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "NeoC/Base/Object.h"

#include "Base.h"

class Derived_t {
	extends (Base_t);

	public int32_t (* GetNum)(self_t *);
	public void (* AddNum)(self_t *, const int32_t num);
} Derived_t;

class _Derived {
	private bool _Initialised;
	private void (* _Setup)();

	public Derived_t *(* Init)(Derived_t *);
	public Derived_t *(* New)();
	public void (* Delete)(Derived_t *);

	public int32_t (* GetNum)(self_t *);
	public void (* AddNum)(self_t *, const int32_t num);
} _Derived;

extern _Derived Derived;
