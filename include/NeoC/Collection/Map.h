#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <threads.h>
#include "NeoC/Base/Object.h"
#include "NeoC/Base/Exception/Signal.h"
#include "NeoC/Base/Exception/Exception.h"
#include "NeoC/Collection/Collection.h"

class {
	public void *Key;
	public void *Value;
} Item_t;

class Map_t {
	extends (Collection_t);

	Item_t *_Item;

	private bool (* _KeyComparator)(void *mapKey, void *key);
	private bool (* _ValueComparator)(void *mapValue, void *value);

	/* 操作系 */
	public void (* SetComparator)(self_t *,
		bool (* keyComparator)(void *mapKey, void *key),
		bool (* valueComparator)(void *mapValue, void *value)
	);
	public void (* Put)(self_t *, void *key, void *value);
	public void (* Remove)(self_t *, void *key) throws (Map.Exception);
	public inherit void (* Lock)(self_t *);
	public inherit void (* Unlock)(self_t *);

	/* 取得系 */
	public inherit int32_t (* GetLength)(self_t *);
	public Item_t (* Get)(self_t *, int32_t idx);

	/* 検査系 */
	public inherit bool (* IsEmpty)(self_t *);
	public bool (* ContainsKey)(self_t *, void *key);
	public bool (* ContainsValue)(self_t *, void *value);
} Map_t;

class _Map {
	private void (* _Setup)();
	public final SignalCode_t Exception;
	private final int32_t _ALLOCATION_BLOCK_SIZE;

	public Map_t *(* Init)(Map_t *);
	public Map_t *(* New)();
	public void (* Delete)(Map_t *);

	/* 操作系 */
	public void (* SetComparator)(self_t *,
		bool (* keyComparator)(void *mapKey, void *key),
		bool (* valueComparator)(void *mapValue, void *value)
	);
	public void (* Put)(self_t *, void *key, void *value);
	public void (* Remove)(self_t *, void *key) throws (Map.Exception);
	public inherit void (* Lock)(self_t *);
	public inherit void (* Unlock)(self_t *);

	/* 取得系 */
	public inherit int32_t (* GetLength)(self_t *);
	public Item_t (* Get)(self_t *, int32_t idx);

	/* 検査系 */
	public inherit bool (* IsEmpty)(self_t *);
	public bool (* ContainsKey)(self_t *, void *key);
	public bool (* ContainsValue)(self_t *, void *value);
} _Map;

extern _Map Map;
