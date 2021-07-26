#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <threads.h>
#include "NeoC/Base/Object.h"
#include "NeoC/Base/Memory.h"
#include "NeoC/Base/Exception/Signal.h"
#include "NeoC/Base/Exception/Exception.h"
#include "NeoC/Collection/Collection.h"

class Queue_t {
	extends (Collection_t);

	private void **_Item;

	/* 操作系 */
	public void (* Enqueue)(self_t *, void *item);
		public void (* Enq)(self_t *, void *item);
	public void *(* Dequeue)(self_t *) throws (Queue.Exception);
		public void *(* Deq)(self_t *) throws (Queue.Exception);
	public inherit void (* Lock)(self_t *);
	public inherit void (* Unlock)(self_t *);

	/* 取得系 */
	public void *(* Peek)(self_t *) throws (Queue.Exception);
	public inherit int32_t (* GetLength)(self_t *);

	/* 検査系 */
	public inherit bool (* IsEmpty)(self_t *);
} Queue_t;

class _Queue {
	private void (* _Setup)();
	public final SignalCode_t Exception;
	private final int32_t _ALLOCATION_BLOCK_SIZE;

	public Queue_t *(* Init)(Queue_t *);
	public Queue_t *(* New)();
	public void (* Delete)(Queue_t *);

	/* 操作系 */
	public void (* Enqueue)(self_t *, void *item);
		public void (* Enq)(self_t *, void *item);
	public void *(* Dequeue)(self_t *) throws (Queue.Exception);
		public void *(* Deq)(self_t *) throws (Queue.Exception);
	public inherit void (* Lock)(self_t *);
	public inherit void (* Unlock)(self_t *);

	/* 取得系 */
	public void *(* Peek)(self_t *) throws (Queue.Exception);
	public inherit int32_t (* GetLength)(self_t *);

	/* 検査系 */
	public inherit bool (* IsEmpty)(self_t *);
} _Queue;

extern _Queue Queue;
