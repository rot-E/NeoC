#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <threads.h>

#include "NeoC/Annotation.h"
#include "NeoC/Memory.h"
#include "NeoC/Exception/Signal.h"
#include "NeoC/Exception/Exception.h"

typedef struct Stack_t {
	private void **_Item;
	private int32_t _Size;
	private int32_t _Length;

	private mtx_t _Mtx;

	/* 操作系 */
	public void (* Push)(struct Stack_t *, void *item);
	public void *(* Pop)(struct Stack_t *) throws (Stack.Exception);
	public void (* Duplicate)(struct Stack_t *) throws (Stack.Exception);
		public void (* Dup)(struct Stack_t *) throws (Stack.Exception);
	public void (* Exchange)(struct Stack_t *) throws (Stack.Exception);
	public void (* LeftRotate)(struct Stack_t *, const int32_t n) throws (Stack.Exception);
	public void (* RightRotate)(struct Stack_t *, const int32_t n) throws (Stack.Exception);

	/* 取得系 */
	public void *(* Peek)(struct Stack_t *) throws (Stack.Exception);
	public int32_t (* GetLength)(struct Stack_t *);

	/* 検査系 */
	public bool (* IsEmpty)(struct Stack_t *);
} Stack_t;

typedef struct {
	private void (* _Setup)();
	public final SignalCode_t Exception;
	private final int32_t _ALLOCATION_BLOCK_SIZE;

	public Stack_t *(* New)();
	public void (* Delete)(Stack_t *);

	/* 操作系 */
	public void (* Push)(Stack_t *, void *item);
	public void *(* Pop)(Stack_t *) throws (Stack.Exception);
	public void (* Duplicate)(Stack_t *) throws (Stack.Exception);
		public void (* Dup)(Stack_t *) throws (Stack.Exception);
	public void (* Exchange)(Stack_t *) throws (Stack.Exception);
	public void (* LeftRotate)(Stack_t *, const int32_t n) throws (Stack.Exception);
	public void (* RightRotate)(Stack_t *, const int32_t n) throws (Stack.Exception);

	/* 取得系 */
	public void *(* Peek)(Stack_t *) throws (Stack.Exception);
	public int32_t (* GetLength)(Stack_t *);

	/* 検査系 */
	public bool (* IsEmpty)(Stack_t *);
} _Stack;

extern _Stack Stack;
