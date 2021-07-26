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
	public any *Key;
	public any *Value;
} Item_t;

class Map_t {
	extends (Collection_t);

	Item_t *_Item;

	private bool (* _KeyComparator)(any *mapKey, any *key);
	private bool (* _ValueComparator)(any *mapValue, any *value);

	/* 操作系 */
	public void (* SetComparator)(self_t *,
		bool (* keyComparator)(any *mapKey, any *key),
		bool (* valueComparator)(any *mapValue, any *value)
	);
	public void (* Put)(self_t *, any *key, any *value);
	public void (* Remove)(self_t *, any *key) throws (Map.Exception);
	public inherit void (* Lock)(self_t *);
	public inherit void (* Unlock)(self_t *);

	/* 取得系 */
	public inherit int32_t (* GetLength)(self_t *);
	public Item_t (* Get)(self_t *, int32_t idx);

	/* 検査系 */
	public inherit bool (* IsEmpty)(self_t *);
	public bool (* ContainsKey)(self_t *, any *key);
	public bool (* ContainsValue)(self_t *, any *value);
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
		bool (* keyComparator)(any *mapKey, any *key),
		bool (* valueComparator)(any *mapValue, any *value)
	);
	public void (* Put)(self_t *, any *key, any *value);
	public void (* Remove)(self_t *, any *key) throws (Map.Exception);
	public inherit void (* Lock)(self_t *);
	public inherit void (* Unlock)(self_t *);

	/* 取得系 */
	public inherit int32_t (* GetLength)(self_t *);
	public Item_t (* Get)(self_t *, int32_t idx);

	/* 検査系 */
	public inherit bool (* IsEmpty)(self_t *);
	public bool (* ContainsKey)(self_t *, any *key);
	public bool (* ContainsValue)(self_t *, any *value);
} _Map;

extern _Map Map;
