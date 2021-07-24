#pragma once

#include <stdint.h>

#include "NeoC/Object.h"

class Base_t {
	private int32_t _Num;

	public int32_t (* GetNum)(self *);
} Base_t;

class _Base {
	public Base_t *(* Init)(Base_t *);
	public Base_t *(* New)();
	public void (* Delete)(Base_t *);

	public int32_t (* GetNum)(self_t *);
} _Base;

extern _Base Base;
