#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <threads.h>
#include "NeoC/Annotation.h"
#include "NeoC/Object.h"
#include "NeoC/Memory.h"
#include "NeoC/Exception/Signal.h"
#include "NeoC/Exception/Exception.h"

class Set_t {

} Set_t;

class _Set {
	private void (* _Setup)();
	public final SignalCode_t Exception;
	private final int32_t _ALLOCATION_BLOCK_SIZE;

	public Set_t *(* New)();
	public void (* Delete)(Set_t *);
} _Set;

extern _Set Set;