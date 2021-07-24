#include "NeoC/Collection/Collection.h"

static int32_t GetLength(self *col) {
	return act(Collection_t, col)->_Length;
}

static bool IsEmpty(self *col) {
	return act(Collection_t, col)->_Length == 0;
}

static void Init(Collection_t *col) {
	Collection.Init(act(Collection_t, q));
	act(Collection_t, q)->_Expr		= u8"(Object_t ~> Collection_t)";

	col->_Size 						= 0;
	col->_Length					= 0;
	mtx_init(&col->_Mtx, mtx_plain);

	col->GetLength					= GetLength;
	col->IsEmpty					= IsEmpty;
}

static void Delete(Collection_t *col) {
	delete (col);
}

_Collection Collection = {
	.Init			= Init,
	.Delete			= Delete,

	.GetLength		= GetLength,

	.IsEmpty		= IsEmpty,
};
