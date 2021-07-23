#include "NeoC/Collection/Tuple.h"

static void _Setup() {
	Tuple.Exception signal;
}

static void Set(Tuple_t *tp, const int32_t idx, void *item) throws (Tuple.Exception) {
	if (tp->_Size <= idx) throw (Signal.New(Tuple.Exception));

	tp->_Item[idx] = item;
}

static void *Get(Tuple_t *tp, const int32_t idx) throws (Tuple.Exception) {
	if (tp->_Size <= idx) throw (Signal.New(Tuple.Exception));

	return tp->_Item[idx];
}

static int32_t GetSize(Tuple_t *tp) {
	return tp->_Size;
}

static Tuple_t *New(const int32_t size) {
	Tuple_t *tp = (Tuple_t *)(_Memory.Allocate(sizeof(Tuple_t)));

	tp->_Item		= _Memory.CountedAllocate(size, sizeof(void *));
	tp->_Size		= size;

	tp->Set			= Set;
	tp->Get			= Get;
	tp->GetSize		= GetSize;

	return tp;
}

static void Delete(Tuple_t *tp) {
	_Memory.Free(tp);
}

_Tuple Tuple = {
	._Setup		= _Setup,

	.New		= New,
	.Delete		= Delete,

	.Set		= Set,
	.Get		= Get,
	.GetSize	= GetSize,
};
