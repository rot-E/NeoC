#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <threads.h>
#include "NeoC/Base/Object.h"
#include "NeoC/Base/Exception/Signal.h"
#include "NeoC/Base/Exception/Exception.h"
#include "NeoC/Collection/Collection.h"

class List_t {
	extends (Collection_t);

	any **_Item;
	private bool (* _ItemComparator)(any *listItem, any *item);

	/* 操作系 */
	public void (* SetComparator)(self_t *,
		bool (* itemComparator)(any *listItem, any *item)
	);
	public void (* Add)(self_t *, any *item);
	public void (* Remove)(self_t *, const int32_t idx) throws (List.Exception);
	public void (* RemoveItem)(self_t *, any *item) throws (List.Exception);
	public inherit void (* Lock)(self_t *);
	public inherit void (* Unlock)(self_t *);

	/* 取得系 */
	public inherit int32_t (* GetLength)(self_t *);
	public any *(* Get)(self_t *, int32_t idx);
	public int32_t (* IndexOf)(self_t *, any *item) throws (List.Failure);

	/* 検査系 */
	public inherit bool (* IsEmpty)(self_t *);
	public bool (* Contains)(self_t *, any *item);
} List_t;

class _List {
	private void (* _Setup)();
	public final SignalCode_t Exception;
	public final SignalCode_t Failure;
	private final int32_t _ALLOCATION_BLOCK_SIZE;

	public List_t *(* Init)(List_t *);
	public List_t *(* New)();
	public void (* Delete)(List_t *);

	/* 操作系 */
	public void (* SetComparator)(self_t *,
		bool (* itemComparator)(any *listItem, any *item)
	);
	public void (* Add)(self_t *, any *item);
	public void (* Remove)(self_t *, const int32_t idx) throws (List.Exception);
	public void (* RemoveItem)(self_t *, any *item) throws (List.Exception);
	public inherit void (* Lock)(self_t *);
	public inherit void (* Unlock)(self_t *);

	/* 取得系 */
	public inherit int32_t (* GetLength)(self_t *);
	public any *(* Get)(self_t *, const int32_t idx);
	public int32_t (* IndexOf)(self_t *, any *item) throws (List.Failure);

	/* 検査系 */
	public inherit bool (* IsEmpty)(self_t *);
	public bool (* Contains)(self_t *, any *item);
} _List;

extern _List List;
