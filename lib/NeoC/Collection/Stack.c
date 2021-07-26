#include "NeoC/Collection/Stack.h"

method static void _Setup() {
	Stack.Exception signal;

	Stack.Lock			= Collection.Lock;
	Stack.Unlock		= Collection.Unlock;
	Stack.GetLength		= Collection.GetLength;
	Stack.IsEmpty		= Collection.IsEmpty;
}

method static void Push(self_t *st, any *item) {
	Stack.Lock(st);

	// 領域不足→確保
	if (Stack.GetLength(st) + 1 >= act(Collection_t, st)->_Size) {
		act(Collection_t, st)->_Size += Stack._ALLOCATION_BLOCK_SIZE;
		act(Stack_t, st)->_Item = _Memory.ReAllocate(
			act(Stack_t, st)->_Item,
			act(Collection_t, st)->_Size * sizeof(any *)
		);
	}

	// 格納
	act(Stack_t, st)->_Item[Stack.GetLength(st)] = item;

	act(Collection_t, st)->_Length++;

	Stack.Unlock(st);
}

static any *Pop(self_t *st) throws (Stack.Exception) {
	if (Stack.GetLength(st) <= 0) throw (Signal.New(Stack.Exception));

	Stack.Lock(st);

	any *retv = act(Stack_t, st)->_Item[Stack.GetLength(st) - 1];
	act(Collection_t, st)->_Length--;

	// 領域過多→解放
	if (Stack.GetLength(st) < act(Collection_t, st)->_Size - Stack._ALLOCATION_BLOCK_SIZE) {
		act(Collection_t, st)->_Size -= Stack._ALLOCATION_BLOCK_SIZE;
		act(Stack_t, st)->_Item = _Memory.ReAllocate(
			act(Stack_t, st)->_Item,
			act(Collection_t, st)->_Size * sizeof(any *)
		);
	}

	Stack.Unlock(st);

	return retv;
}

static void Duplicate(self_t *st) throws (Stack.Exception) {
	Stack.Push(st, Stack.Peek(st));
}

static void Exchange(self_t *st) throws (Stack.Exception) {
	Stack_t *top = Stack.Pop(st);
	Stack_t *next = Stack.Pop(st);
	Stack.Push(st, top);
	Stack.Push(st, next);
}

static void LeftRotate(self_t *st, const int32_t n) throws (Stack.Exception) {
	Stack_t *btm = Stack.New();
	for (int32_t i = 0; i < n; i++)
		Stack.Push(btm, Stack.Pop(st));

	Stack_t *top = Stack.New();
	for (int32_t i = Stack.GetLength(st); 0 < i; i--)
		Stack.Push(top, Stack.Pop(st));

	for (int32_t i = Stack.GetLength(btm); 0 < i; i--)
		Stack.Push(st, Stack.Pop(btm));

	for (int32_t i = Stack.GetLength(top); 0 < i; i--)
		Stack.Push(st, Stack.Pop(top));
}

static void RightRotate(self_t *st, const int32_t n) throws (Stack.Exception) {
	Stack_t *btm = Stack.New();
	for (int32_t i = Stack.GetLength(st) - n; 0 < i; i--)
		Stack.Push(btm, Stack.Pop(st));

	Stack_t *top = Stack.New();
	for (int32_t i = 0; i < n; i++)
		Stack.Push(top, Stack.Pop(st));

	for (int32_t i = Stack.GetLength(btm); 0 < i; i--)
		Stack.Push(st, Stack.Pop(btm));

	for (int32_t i = Stack.GetLength(top); 0 < i; i--)
		Stack.Push(st, Stack.Pop(top));
}

static any *Peek(self_t *st) throws (Stack.Exception) {
	if (Stack.GetLength(st) <= 0) throw (Signal.New(Stack.Exception));

	return act(Stack_t, st)->_Item[Stack.GetLength(st) - 1];
}

method static Stack_t *Init(Stack_t *st) {
	Collection.Init(act(Collection_t, st));
	act(Collection_t, st)->_Size		= Stack._ALLOCATION_BLOCK_SIZE;

	st->_Item							= _Memory.CountedAllocate(Stack._ALLOCATION_BLOCK_SIZE, sizeof(any *));

	st->Push							= Push;
	st->Pop								= Pop;
	st->Duplicate						= Duplicate;
		st->Dup							= Duplicate;
	st->Exchange						= Exchange;
	st->LeftRotate						= LeftRotate;
	st->RightRotate						= RightRotate;
	st->Lock							= Collection.Lock;
	st->Unlock							= Collection.Unlock;
	st->Peek							= Peek;
	st->GetLength						= Collection.GetLength;
	st->IsEmpty							= Collection.IsEmpty;

	return st;
}

method static Stack_t *New() {
	return Stack.Init(new (Stack_t));
}

method static void Delete(Stack_t *st) {
	mtx_destroy(&act(Collection_t, st)->_Mtx);

	_Memory.Free(act(Stack_t, st)->_Item);
	delete (st);
}

_Stack Stack = {
	._Setup						= _Setup,
	._ALLOCATION_BLOCK_SIZE		= 1000,

	.Init						= Init,
	.New						= New,
	.Delete						= Delete,

	.Push						= Push,
	.Pop						= Pop,
	.Duplicate					= Duplicate,
		.Dup					= Duplicate,
	.Exchange					= Exchange,
	.LeftRotate					= LeftRotate,
	.RightRotate				= RightRotate,

	.Peek						= Peek,
};
