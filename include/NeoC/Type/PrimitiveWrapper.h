#pragma once

#include "NeoC/Base/Object.h"

interface PrimitiveWrapper_i {
	public uint8_t *(* GetExpr)();
} PrimitiveWrapper_i;
