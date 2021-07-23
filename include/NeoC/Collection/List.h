#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <threads.h>

#include "NeoC/Annotation.h"
#include "NeoC/Exception/Signal.h"
#include "NeoC/Exception/Exception.h"

typedef struct List_t {
	void **_Item;
	private int32_t _Size;
	private bool (* _ItemComparator)(void *listItem, void *item);
	private int32_t _Length;

	private mtx_t _Mtx;

	public void (* SetComparator)(struct List_t *,
		bool (* itemComparator)(void *listItem, void *item)
	);

	/* 操作系 */
	public void (* Add)(struct List_t *, void *item);
	public void (* Remove)(struct List_t *, const int32_t idx) throws (List.Exception);
	public void (* RemoveItem)(struct List_t *, void *item) throws (List.Exception);

	/* 取得系 */
	public int32_t (* GetLength)(struct List_t *);
	public void *(* Get)(struct List_t *, int32_t idx);
	public int32_t (* IndexOf)(struct List_t *, void *item) throws (List.Failure);

	/* 検査系 */
	public bool (* IsEmpty)(struct List_t *);
	public bool (* Contains)(struct List_t *, void *item);
} List_t;

typedef struct {
	private void (* _Setup)();
	public final SignalCode_t Exception;
	public final SignalCode_t Failure;
	private final int32_t _ALLOCATION_BLOCK_SIZE;

	public List_t *(* New)();
	public void (* Delete)(List_t *);

	public void (* SetComparator)(List_t *,
		bool (* itemComparator)(void *listItem, void *item)
	);

	/* 操作系 */
	public void (* Add)(List_t *, void *item);
	public void (* Remove)(List_t *, const int32_t idx) throws (List.Exception);
	public void (* RemoveItem)(List_t *, void *item) throws (List.Exception);

	/* 取得系 */
	public int32_t (* GetLength)(List_t *);
	public void *(* Get)(List_t *, const int32_t idx);
	public int32_t (* IndexOf)(List_t *, void *item) throws (List.Failure);

	/* 検査系 */
	public bool (* IsEmpty)(List_t *);
	public bool (* Contains)(List_t *, void *item);
} _List;

extern _List List;
