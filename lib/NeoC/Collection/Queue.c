#include "NeoC/Collection/Queue.h"

static void _Setup() {
	Queue.Exception signal;

	Queue.GetLength		= Collection.GetLength;
	Queue.IsEmpty		= Collection.IsEmpty;
}

static void Enqueue(self_t *q, void *item) {
	mtx_lock(&act(Collection_t, q)->_Mtx);

	// 領域不足→確保
	if (Queue.GetLength(q) + 1 >= act(Collection_t, q)->_Size) {
		act(Collection_t, q)->_Size += Queue._ALLOCATION_BLOCK_SIZE;
		act(Queue_t, q)->_Item = _Memory.ReAllocate(act(Queue_t, q)->_Item, act(Collection_t, q)->_Size * sizeof(void *));
	}

	// 格納
	act(Queue_t, q)->_Item[Queue.GetLength(q)] = item;

	act(Collection_t, q)->_Length++;

	mtx_unlock(&act(Collection_t, q)->_Mtx);
}

static void *Dequeue(self_t *q) throws (Queue.Exception) {
	if (Queue.GetLength(q) <= 0) throw (Signal.New(Queue.Exception));

	mtx_lock(&act(Collection_t, q)->_Mtx);

	void *retv = act(Queue_t, q)->_Item[0];

	// 先頭削除
	for (int32_t i = 0; i < Queue.GetLength(q) - 1; i++)
		act(Queue_t, q)->_Item[i] = act(Queue_t, q)->_Item[i + 1];

	act(Collection_t, q)->_Length--;

	// 領域過多→解放
	if (Queue.GetLength(q) < act(Collection_t, q)->_Size - Queue._ALLOCATION_BLOCK_SIZE) {
		act(Collection_t, q)->_Size -= Queue._ALLOCATION_BLOCK_SIZE;
		act(Queue_t, q)->_Item = _Memory.ReAllocate(act(Queue_t, q)->_Item, act(Collection_t, q)->_Size * sizeof(void *));
	}

	mtx_unlock(&act(Collection_t, q)->_Mtx);

	return retv;
}

static void *Peek(self_t *q) throws (Queue.Exception) {
	if (Queue.GetLength(q) <= 0) throw (Signal.New(Queue.Exception));

	return act(Queue_t, q)->_Item[0];
}

static Queue_t *New() {
	Queue_t *q = (Queue_t *)(_Memory.Allocate(sizeof(Queue_t)));

	Collection.Init(act(Collection_t, q));
	act(Collection_t, q)->_Size	= Queue._ALLOCATION_BLOCK_SIZE;

	q->_Item						= _Memory.CountedAllocate(Queue._ALLOCATION_BLOCK_SIZE, sizeof(void *));

	q->Enqueue						= Enqueue;
		q->Enq						= Enqueue;
	q->Dequeue						= Dequeue;
		q->Deq						= Dequeue;
	q->Peek							= Peek;
	q->GetLength					= act(Collection_t, q)->GetLength;
	q->IsEmpty						= act(Collection_t, q)->IsEmpty;

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
};
