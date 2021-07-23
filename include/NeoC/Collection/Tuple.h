#pragma once

#include <stdint.h>

#include "NeoC/Annotation.h"
#include "NeoC/Memory.h"
#include "NeoC/Exception/Signal.h"
#include "NeoC/Exception/Exception.h"

typedef struct Tuple_t {
	private void **_Item;
	private int32_t _Size;

	private void (* Set)(struct Tuple_t *, const int32_t idx, void *item) throws (Tuple.Exception);
	private void *(* Get)(struct Tuple_t *, const int32_t idx) throws (Tuple.Exception);
	private int32_t (* GetSize)(struct Tuple_t *);
} Tuple_t;

typedef struct {
	private void (* _Setup)();
	public final SignalCode_t Exception;

	private Tuple_t *(* New)(const int32_t size);
	private void (* Delete)(Tuple_t *);

	private void (* Set)(Tuple_t *, const int32_t idx, void *item) throws (Tuple.Exception);
	private void *(* Get)(Tuple_t *, const int32_t idx) throws (Tuple.Exception);
	private int32_t (* GetSize)(Tuple_t *);
} _Tuple;

extern _Tuple Tuple;
