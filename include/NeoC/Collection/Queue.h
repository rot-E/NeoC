#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <threads.h>

#include "NeoC/Annotation.h"
#include "NeoC/Object.h"
#include "NeoC/Memory.h"
#include "NeoC/Exception/Signal.h"
#include "NeoC/Exception/Exception.h"
#include "NeoC/Collection.h"

class Queue_t {
	extends (Collection_t);

	private void **_Item;
	private mtx_t _Mtx;

	/* 操作系 */
	public void (* Enqueue)(self *, void *item);
		public void (* Enq)(self *, void *item);
	public void *(* Dequeue)(self *) throws (Queue.Exception);
		public void *(* Deq)(self *) throws (Queue.Exception);

	/* 取得系 */
	public void *(* Peek)(self *) throws (Queue.Exception);
	public int32_t (* GetLength)(self *);

	/* 検査系 */
	public bool (* IsEmpty)(self *);
} Queue_t;

class _Queue {
	private void (* _Setup)();
	public final SignalCode_t Exception;
	private final int32_t _ALLOCATION_BLOCK_SIZE;

	public Queue_t *(* New)();
	public void (* Delete)(Queue_t *);

	/* 操作系 */
	public void (* Enqueue)(self_t *, void *item);
		public void (* Enq)(self_t *, void *item);
	public void *(* Dequeue)(self_t *) throws (Queue.Exception);
		public void *(* Deq)(self_t *) throws (Queue.Exception);

	/* 取得系 */
	public void *(* Peek)(self_t *) throws (Queue.Exception);
	public int32_t (* GetLength)(self_t *);

	/* 検査系 */
	public bool (* IsEmpty)(self_t *);
} _Queue;

extern _Queue Queue;
