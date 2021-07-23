#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <threads.h>

#include "NeoC/Annotation.h"
#include "NeoC/Exception/Signal.h"
#include "NeoC/Exception/Exception.h"

typedef struct List_t {
	void *_Item;
	private int32_t _Size;
	private int32_t _ItemSize;
	private bool (* _Comparator)(void *listItem, void *item);
	private int32_t _Length;

	mtx_t _Mtx;

	public void (* SetComparator)(struct Map_t *,
		bool (* Comparator)(void *listItem, void *item),
	);

	/* 操作系 */
	public void (* Put)(struct Map_t *, void *key, void *value);
	public void (* Remove)(struct Map_t *, void *key) throws (Map.Exception);

	/* 取得系 */
	public int32_t (* GetLength)(struct Map_t *);
	public Set_t (* GetSet)(struct Map_t *, int32_t);

	/* 検査系 */
	public bool (* IsEmpty)(struct Map_t *);
	public bool (* ContainsKey)(struct Map_t *, void *key);
	public bool (* ContainsValue)(struct Map_t *, void *value);
} List_t;

typedef struct {
	private void (* _Setup)();
	public final SignalCode_t Exception;
	private final int32_t _ALLOCATION_BLOCK_SIZE;

	public Map_t *(* New)(const size_t keySize, const size_t valueSize);
	public void (* Delete)(Map_t *);

	public void (* SetComparator)(Map_t *,
		bool (* keyComparator)(void *mapKey, void *key),
		bool (* valueComparator)(void *mapValue, void *value)
	);

	/* 操作系 */
	public void (* Put)(struct Map_t *, void *key, void *value);
	public void (* Remove)(Map_t *, void *key) throws (Map.Exception);

	/* 取得系 */
	public int32_t (* GetLength)(Map_t *);
	public Set_t (* GetSet)(Map_t *, int32_t);

	/* 検査系 */
	public bool (* IsEmpty)(Map_t *);
	public bool (* ContainsKey)(Map_t *, void *key);
	public bool (* ContainsValue)(Map_t *, void *value);
} _List;

extern _List List;
