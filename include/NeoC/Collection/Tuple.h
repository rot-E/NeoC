#pragma once

#include <stdint.h>
#include "NeoC/Base/Object.h"
#include "NeoC/Base/Memory.h"
#include "NeoC/Base/Exception/Signal.h"
#include "NeoC/Base/Exception/Exception.h"

class Tuple_t {
	private any **_Item;
	private int32_t _Size;

	private void (* Set)(self_t *, const int32_t idx, any *item) throws (Tuple.Exception);
	private any *(* Get)(self_t *, const int32_t idx) throws (Tuple.Exception);
	private int32_t (* GetSize)(self_t *);
} Tuple_t;

class _Tuple {
	private void (* _Setup)();
	public final SignalCode_t Exception;

	private Tuple_t *(* Init)(Tuple_t *, const int32_t size);
	private Tuple_t *(* New)(const int32_t size);
	private void (* Delete)(Tuple_t *);

	private void (* Set)(self_t *, const int32_t idx, any *item) throws (Tuple.Exception);
	private any *(* Get)(self_t *, const int32_t idx) throws (Tuple.Exception);
	private int32_t (* GetSize)(self_t *);
} _Tuple;

extern _Tuple Tuple;
