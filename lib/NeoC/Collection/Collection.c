#include "NeoC/Collection/Collection.h"

/// method static void _Setup() {
	/// Collection.GetExpr = Object.GetExpr;
/// }

method static int32_t GetLength(self_t *col) {
	return act(Collection_t, col)->_Length;
}

method static bool IsEmpty(self_t *col) {
	return act(Collection_t, col)->_Length == 0;
}

method static void Lock(self_t *col) {
	mtx_lock(&act(Collection_t, col)->_Mtx);
}

method static void Unlock(self_t *col) {
	mtx_unlock(&act(Collection_t, col)->_Mtx);
}

method static Collection_t *Init(Collection_t *col) {
	/// Object.Init(act(Object_t, col));
	/// act(Object_t, col)->_Expr	= u8"(Object_t ~> Collection_t)";

	col->_Size 					= 0;
	col->_Length				= 0;
	mtx_init(&col->_Mtx, mtx_plain);

	/// col->GetExpr				= Object.GetExpr;

	col->GetLength				= GetLength;
	col->IsEmpty				= IsEmpty;
	col->Lock					= Lock;
	col->Unlock					= Unlock;
}

method static void Delete(Collection_t *col) {
	if (col == NULL) return;

	delete (col);
}

_Collection Collection = {
	/// ._Setup			= _Setup,

	.Init			= Init,
	.Delete			= Delete,

	.GetLength		= GetLength,
	.IsEmpty		= IsEmpty,

	.Lock			= Lock,
	.Unlock			= Unlock,
};
