#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <threads.h>

#include "NeoC/Annotation.h"
#include "NeoC/Object.h"
#include "NeoC/Memory.h"
#include "NeoC/Exception/Signal.h"
#include "NeoC/Exception/Exception.h"

class Queue_t {
	private void **_Item;
	private int32_t _Size;
	private int32_t _Length;

	private mtx_t _Mtx;

	/* 操作系 */
	public void (* Enqueue)(struct Queue_t *, void *item);
		public void (* Enq)(struct Queue_t *, void *item);
	public void *(* Dequeue)(struct Queue_t *) throws (Queue.Exception);
		public void *(* Deq)(struct Queue_t *) throws (Queue.Exception);

	/* 取得系 */
	public void *(* Peek)(struct Queue_t *) throws (Queue.Exception);
	public int32_t (* GetLength)(struct Queue_t *);

	/* 検査系 */
	public bool (* IsEmpty)(struct Queue_t *);
} Queue_t;

class _Queue {
	private void (* _Setup)();
	public final SignalCode_t Exception;
	private final int32_t _ALLOCATION_BLOCK_SIZE;

	public Queue_t *(* New)();
	public void (* Delete)(Queue_t *);

	/* 操作系 */
	public void (* Enqueue)(Queue_t *, void *item);
		public void (* Enq)(Queue_t *, void *item);
	public void *(* Dequeue)(Queue_t *) throws (Queue.Exception);
		public void *(* Deq)(Queue_t *) throws (Queue.Exception);

	/* 取得系 */
	public void *(* Peek)(Queue_t *) throws (Queue.Exception);
	public int32_t (* GetLength)(Queue_t *);

	/* 検査系 */
	public bool (* IsEmpty)(Queue_t *);
} _Queue;

extern _Queue Queue;
