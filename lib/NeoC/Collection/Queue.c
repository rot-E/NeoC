#include "NeoC/Collection/Queue.h"

method static void _Setup() {
	Queue.Exception signal;

	Queue.Lock			= Collection.Lock;
	Queue.Unlock		= Collection.Unlock;
	Queue.GetLength		= Collection.GetLength;
	Queue.IsEmpty		= Collection.IsEmpty;
}

method static void Enqueue(self_t *q, any *item) {
	Queue.Lock(q);

	// 領域不足→確保
	if (Queue.GetLength(q) + 1 >= act(Collection_t, q)->_Size) {
		act(Collection_t, q)->_Size += Queue._ALLOCATION_BLOCK_SIZE;
		act(Queue_t, q)->_Item = _Memory.ReAllocate(act(Queue_t, q)->_Item, act(Collection_t, q)->_Size * sizeof(any *));
	}

	// 格納
	act(Queue_t, q)->_Item[Queue.GetLength(q)] = item;

	act(Collection_t, q)->_Length++;

	Queue.Unlock(q);
}

method static any *Dequeue(self_t *q) throws (Queue.Exception) {
	if (Queue.GetLength(q) <= 0) throw (Signal.New(Queue.Exception));

	Queue.Lock(q);

	any *retv = act(Queue_t, q)->_Item[0];

	// 先頭削除
	for (int32_t i = 0; i < Queue.GetLength(q) - 1; i++)
		act(Queue_t, q)->_Item[i] = act(Queue_t, q)->_Item[i + 1];

	act(Collection_t, q)->_Length--;

	// 領域過多→解放
	if (Queue.GetLength(q) < act(Collection_t, q)->_Size - Queue._ALLOCATION_BLOCK_SIZE) {
		act(Collection_t, q)->_Size -= Queue._ALLOCATION_BLOCK_SIZE;
		act(Queue_t, q)->_Item = _Memory.ReAllocate(act(Queue_t, q)->_Item, act(Collection_t, q)->_Size * sizeof(any *));
	}

	Queue.Unlock(q);

	return retv;
}

method static any *Peek(self_t *q) throws (Queue.Exception) {
	if (Queue.GetLength(q) <= 0) throw (Signal.New(Queue.Exception));

	return act(Queue_t, q)->_Item[0];
}

method static Queue_t *Init(Queue_t *q) {
	Collection.Init(act(Collection_t, q));
	act(Collection_t, q)->_Size		= Queue._ALLOCATION_BLOCK_SIZE;

	q->_Item						= _Memory.CountedAllocate(Queue._ALLOCATION_BLOCK_SIZE, sizeof(any *));

	q->Enqueue						= Enqueue;
		q->Enq						= Enqueue;
	q->Dequeue						= Dequeue;
		q->Deq						= Dequeue;
	q->Lock							= Collection.Lock;
	q->Unlock						= Collection.Unlock;
	q->Peek							= Peek;
	q->GetLength					= Collection.GetLength;
	q->IsEmpty						= Collection.IsEmpty;

	return q;
}

method static Queue_t *New() {
	return Queue.Init(new (Queue_t));
}

method static void Delete(Queue_t *q) {
	mtx_destroy(&act(Collection_t, q)->_Mtx);

	_Memory.Free(q->_Item);
	delete (q);
}

_Queue Queue = {
	._Setup						= _Setup,
	._ALLOCATION_BLOCK_SIZE		= 1000,

	.Init						= Init,
	.New						= New,
	.Delete						= Delete,

	.Enqueue					= Enqueue,
		.Enq					= Enqueue,
	.Dequeue					= Dequeue,
		.Deq					= Dequeue,
	.Peek						= Peek,
};
