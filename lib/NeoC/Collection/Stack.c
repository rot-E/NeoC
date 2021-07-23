#include "NeoC/Collection/Stack.h"

static void _Setup() {
	Stack.Exception signal;
}

static void Push(Stack_t *st, void *item) {
	mtx_lock(&st->_Mtx);

	// 領域不足→確保
	if (st->_Length + 1 >= st->_Size) {
		st->_Size += Stack._ALLOCATION_BLOCK_SIZE;
		st->_Item = _Memory.ReAllocate(st->_Item, st->_Size * sizeof(void *));
	}

	// 格納
	st->_Item[st->_Length] = item;

	st->_Length++;

	mtx_unlock(&st->_Mtx);
}

static void *Pop(Stack_t *st) throws (Stack.Exception) {
	if (st->_Length <= 0) throw (Signal.New(Stack.Exception));

	mtx_lock(&st->_Mtx);

	void *retv = st->_Item[st->_Length - 1];
	st->_Length--;

	// 領域過多→解放
	if (st->_Length < st->_Size - Stack._ALLOCATION_BLOCK_SIZE) {
		st->_Size -= Stack._ALLOCATION_BLOCK_SIZE;
		st->_Item = _Memory.ReAllocate(st->_Item, st->_Size * sizeof(void *));
	}

	mtx_unlock(&st->_Mtx);

	return retv;
}

static void Duplicate(Stack_t *st) throws (Stack.Exception) {
	Stack.Push(st, Stack.Peek(st));
}

static void Exchange(Stack_t *st) throws (Stack.Exception) {
	void *top = Stack.Pop(st);
	void *next = Stack.Pop(st);
	Stack.Push(st, top);
	Stack.Push(st, next);
}

static void LeftRotate(Stack_t *st, const int32_t n) throws (Stack.Exception) {
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

static void RightRotate(Stack_t *st, const int32_t n) throws (Stack.Exception) {
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

static void *Peek(Stack_t *st) throws (Stack.Exception) {
	if (st->_Length <= 0) throw (Signal.New(Stack.Exception));

	return st->_Item[st->_Length - 1];
}

static int32_t GetLength(Stack_t *st) {
	return st->_Length;
}

static bool IsEmpty(Stack_t *st) {
	return Stack.GetLength(st) == 0;
}

static Stack_t *New() {
	Stack_t *st = (Stack_t *)(_Memory.Allocate(sizeof(Stack_t)));

	st->_Item			= _Memory.CountedAllocate(Stack._ALLOCATION_BLOCK_SIZE, sizeof(void *));
	st->_Size			= Stack._ALLOCATION_BLOCK_SIZE;
	st->_Length			= 0;
	mtx_init(&st->_Mtx, mtx_plain);

	st->Push			= Push;
	st->Pop				= Pop;
	st->Duplicate		= Duplicate;
		st->Dup			= Duplicate;
	st->Exchange		= Exchange;
	st->LeftRotate		= LeftRotate;
	st->RightRotate		= RightRotate;
	st->Peek			= Peek;
	st->GetLength		= GetLength;
	st->IsEmpty			= IsEmpty;

	return st;
}

static void Delete(Stack_t *st) {
	mtx_destroy(&st->_Mtx);

	_Memory.Free(st->_Item);
	_Memory.Free(st);
}

_Stack Stack = {
	._Setup						= _Setup,
	._ALLOCATION_BLOCK_SIZE		= 1000,

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
	.GetLength					= GetLength,
	.IsEmpty					= IsEmpty,
};
