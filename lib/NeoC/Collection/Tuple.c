#include "NeoC/Collection/Tuple.h"

static void _Setup() {
	Tuple.Exception signal;
}

static void Set(self_t *tp, const int32_t idx, any *item) throws (Tuple.Exception) {
	if (act(Tuple_t, tp)->_Size <= idx) throw (Signal.New(Tuple.Exception));

	act(Tuple_t, tp)->_Item[idx] = item;
}

static any *Get(self_t *tp, const int32_t idx) throws (Tuple.Exception) {
	if (act(Tuple_t, tp)->_Size <= idx) throw (Signal.New(Tuple.Exception));

	return act(Tuple_t, tp)->_Item[idx];
}

static int32_t GetSize(self_t *tp) {
	return act(Tuple_t, tp)->_Size;
}

static Tuple_t *Init(Tuple_t *tp, const int32_t size) {
	tp->_Item		= _Memory.CountedAllocate(size, sizeof(any *));
	tp->_Size		= size;

	tp->Set			= Set;
	tp->Get			= Get;
	tp->GetSize		= GetSize;

	return tp;
}

static Tuple_t *New(const int32_t size) {
	return Tuple.Init(new (Tuple_t), size);
}

static void Delete(Tuple_t *tp) {
	if (tp == NULL) return;

	_Memory.Free(act(Tuple_t, tp)->_Item);
	delete (tp);
}

_Tuple Tuple = {
	._Setup		= _Setup,

	.Init		= Init,
	.New		= New,
	.Delete		= Delete,

	.Set		= Set,
	.Get		= Get,
	.GetSize	= GetSize,
};
