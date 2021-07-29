#pragma once

#include <stdint.h>
#include "NeoC/Base/Object.h"
#include "NeoC/Type/String.h"
#include "NeoC/Type/PrimitiveWrapper.h"

class UInt32_t {
	implements (PrimitiveWrapper_i);

	private uint32_t _UInt32;

	public uint32_t (* Unpack)(self_t *);
	public actualize uint8_t *(* GetExpr)(self_t *);
} UInt32_t;

class _UInt32 {
	public UInt32_t *(* Init)(UInt32_t *, uint32_t ui32);
	public UInt32_t *(* New)(uint32_t ui32);
	public void (* Delete)(UInt32_t *);

	public uint32_t (* Unpack)(self_t *);
	public actualize uint8_t *(* GetExpr)(self_t *);
} _UInt32;

extern _UInt32 UInt32;
