#include "NeoC/Collection/Queue.h"

static void _Setup() {
	Queue.Exception signal;
}

static void Enqueue(Queue_t *q, void *item) {
	mtx_lock(&q->_Mtx);

	// 領域不足→確保
	if (q->_Length + 1 >= q->_Size) {
		q->_Size += Queue._ALLOCATION_BLOCK_SIZE;
		q->_Item = _Memory.ReAllocate(q->_Item, sizeof(void *) * q->_Size);
	}

	// 格納
	q->_Item[q->_Length] = item;

	q->_Length++;

	mtx_unlock(&q->_Mtx);
}

static void *Dequeue(Queue_t *q) throws (Queue.Exception) {
	if (q->_Length <= 0) throw (Signal.New(Queue.Exception));

	mtx_lock(&q->_Mtx);

	void *retv = q->_Item[0];

	// 先頭削除
	for (int32_t i = 0; i < Queue.GetLength(q) - 1; i++)
		q->_Item[i] = q->_Item[i + 1];

	q->_Length--;

	// 領域過多→解放
	if (q->_Length < q->_Size - Queue._ALLOCATION_BLOCK_SIZE) {
		q->_Size -= Queue._ALLOCATION_BLOCK_SIZE;
		q->_Item = _Memory.ReAllocate(q->_Item, sizeof(void *) * q->_Size);
	}

	mtx_unlock(&q->_Mtx);

	return retv;
}

static void *Peek(Queue_t *q) throws (Queue.Exception) {
	if (q->_Length <= 0) throw (Signal.New(Queue.Exception));

	return q->_Item[0];
}

static int32_t GetLength(Queue_t *q) {
	return q->_Length;
}

static bool IsEmpty(Queue_t *q) {
	return Queue.GetLength(q) == 0;
}

static Queue_t *New() {
	Queue_t *q = (Queue_t *)(_Memory.Allocate(sizeof(Queue_t)));

	q->_Item		= _Memory.CountedAllocate(Queue._ALLOCATION_BLOCK_SIZE, sizeof(void *));
	q->_Size		= Queue._ALLOCATION_BLOCK_SIZE;
	q->_Length		= 0;
	mtx_init(&q->_Mtx, mtx_plain);

	q->Enqueue		= Enqueue;
		q->Enq		= Enqueue;
	q->Dequeue		= Dequeue;
		q->Deq		= Dequeue;
	q->Peek			= Peek;
	q->GetLength	= GetLength;
	q->IsEmpty		= IsEmpty;

	return q;
}

static void Delete(Queue_t *q) {
	mtx_destroy(&q->_Mtx);

	_Memory.Free(q->_Item);
	_Memory.Free(q);
}

_Queue Queue = {
	._Setup						= _Setup,
	._ALLOCATION_BLOCK_SIZE		= 1000,

	.New						= New,
	.Delete						= Delete,

	.Enqueue					= Enqueue,
		.Enq					= Enqueue,
	.Dequeue					= Dequeue,
		.Deq					= Dequeue,
	.Peek						= Peek,
	.GetLength					= GetLength,
	.IsEmpty					= IsEmpty,
};
