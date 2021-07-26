#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <threads.h>
#include "NeoC/Base/Object.h"
#include "NeoC/Base/Memory.h"
#include "NeoC/Base/Exception/Signal.h"
#include "NeoC/Base/Exception/Exception.h"

class Stack_t {
	extends (Collection_t);

	private any **_Item;

	/* 操作系 */
	public void (* Push)(self_t *, any *item);
	public any *(* Pop)(self_t *) throws (Stack.Exception);
	public void (* Duplicate)(self_t *) throws (Stack.Exception);
		public void (* Dup)(self_t *) throws (Stack.Exception);
	public void (* Exchange)(self_t *) throws (Stack.Exception);
	public void (* LeftRotate)(self_t *, const int32_t n) throws (Stack.Exception);
	public void (* RightRotate)(self_t *, const int32_t n) throws (Stack.Exception);
	public inherit void (* Lock)(self_t *);
	public inherit void (* Unlock)(self_t *);
	/* 取得系 */
	public any *(* Peek)(self_t *) throws (Stack.Exception);
	public inherit int32_t (* GetLength)(self_t *);

	/* 検査系 */
	public inherit bool (* IsEmpty)(self_t *);
} Stack_t;

class _Stack {
	private void (* _Setup)();
	public final SignalCode_t Exception;
	private final int32_t _ALLOCATION_BLOCK_SIZE;

	public Stack_t *(* New)();
	public void (* Delete)(self_t *);

	/* 操作系 */
	public void (* Push)(self_t *, any *item);
	public any *(* Pop)(self_t *) throws (Stack.Exception);
	public void (* Duplicate)(self_t *) throws (Stack.Exception);
		public void (* Dup)(self_t *) throws (Stack.Exception);
	public void (* Exchange)(self_t *) throws (Stack.Exception);
	public void (* LeftRotate)(self_t *, const int32_t n) throws (Stack.Exception);
	public void (* RightRotate)(self_t *, const int32_t n) throws (Stack.Exception);

	/* 取得系 */
	public any *(* Peek)(self_t *) throws (Stack.Exception);
	public int32_t (* GetLength)(self_t *);

	/* 検査系 */
	public bool (* IsEmpty)(self_t *);
} _Stack;

extern _Stack Stack;
