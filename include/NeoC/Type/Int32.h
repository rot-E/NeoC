#pragma once

#include <stdint.h>
#include "NeoC/Base/Object.h"
#include "NeoC/Type/String.h"
#include "NeoC/Type/PrimitiveWrapper.h"

class Int32_t {
	implements (PrimitiveWrapper_i);

	private int32_t _Int32;

	public int32_t (* Unpack)(self_t *);
	public actualize uint8_t *(* GetExpr)(self_t *);
} Int32_t;

class _Int32 {
	public Int32_t *(* Init)(Int32_t *, int32_t i32);
	public Int32_t *(* New)(int32_t i32);
	public void (* Delete)(Int32_t *);

	public int32_t (* Unpack)(self_t *);
	public actualize uint8_t *(* GetExpr)(self_t *);
} _Int32;

extern _Int32 Int32;
