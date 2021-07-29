#include "NeoC/Collection/Collection.h"

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
	col->_Size 					= 0;
	col->_Length				= 0;
	mtx_init(&col->_Mtx, mtx_plain);

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
	.Init			= Init,
	.Delete			= Delete,

	.GetLength		= GetLength,
	.IsEmpty		= IsEmpty,

	.Lock			= Lock,
	.Unlock			= Unlock,
};
