#include "NeoC/Collection/List.h"

method static void _Setup() {
	List.Exception signal;
	List.Failure signal;

	List.Lock			= Collection.Lock;
	List.Unlock			= Collection.Unlock;
	List.GetLength		= Collection.GetLength;
	List.IsEmpty		= Collection.IsEmpty;
}

method static void SetComparator(self_t *lis, bool (* itemComparator)(any *listItem, any *item)) {
	act(List_t, lis)->_ItemComparator = itemComparator;
}

method static void Add(self_t *lis, any *item) {
	List.Lock(lis);

	// 領域不足→確保
	if (List.GetLength(lis) + 1 >= act(Collection_t, lis)->_Size) {
		act(Collection_t, lis)->_Size += List._ALLOCATION_BLOCK_SIZE;
		act(List_t, lis)->_Item = _Memory.ReAllocate(
			act(List_t, lis)->_Item,
			act(Collection_t, lis)->_Size * sizeof(any *)
		);
	}

	// 格納
	act(List_t, lis)->_Item[List.GetLength(lis)] = item;

	act(Collection_t, lis)->_Length++;

	List.Unlock(lis);
}

method static void Remove(self_t *lis, const int32_t idx) throws (List.Exception) {
	if (List.GetLength(lis) <= idx) throw (Signal.New(List.Exception));

	List.Lock(lis);

	for (int32_t j = idx; j < List.GetLength(lis) - 1; j++)
		act(List_t, lis)->_Item[j] = act(List_t, lis)->_Item[j + 1];

	act(Collection_t, lis)->_Length--;

	// 領域過多→解放
	if (List.GetLength(lis) < act(Collection_t, lis)->_Size - List._ALLOCATION_BLOCK_SIZE) {
		act(Collection_t, lis)->_Size -= List._ALLOCATION_BLOCK_SIZE;
		act(List_t, lis)->_Item = _Memory.ReAllocate(
			act(List_t, lis)->_Item,
			act(Collection_t, lis)->_Size * sizeof(any *)
		);
	}

	List.Unlock(lis);
}

method static void RemoveItem(self_t *lis, any *item) throws (List.Exception) {
	int32_t i;
	bool existence = false;
	for (i = 0; i < List.GetLength(lis); i++)
		if (act(List_t, lis)->_ItemComparator(List.Get(lis, i), item)) {
			existence = true;
			break;
		}
	if (!existence) throw (Signal.New(List.Exception));

	List.Lock(lis);

	for (int32_t j = i; j < List.GetLength(lis) - 1; j++)
		act(List_t, lis)->_Item[j] = act(List_t, lis)->_Item[j + 1];

	act(Collection_t, lis)->_Length--;

	// 領域過多→解放
	if (List.GetLength(lis) < act(Collection_t, lis)->_Size - List._ALLOCATION_BLOCK_SIZE) {
		act(Collection_t, lis)->_Size -= List._ALLOCATION_BLOCK_SIZE;
		act(List_t, lis)->_Item = _Memory.ReAllocate(
			act(List_t, lis)->_Item,
			act(Collection_t, lis)->_Size * sizeof(any *)
		);
	}

	List.Unlock(lis);
}

method static any *Get(self_t *lis, int32_t idx) {
	if (List.GetLength(lis) <= idx) throw (Signal.New(List.Exception));

	return act(List_t, lis)->_Item[idx];
}

method static int32_t IndexOf(self_t *lis, any *item) throws (List.Failure) {
	for (int32_t i = 0; i < List.GetLength(lis); i++) {
		if (act(List_t, lis)->_ItemComparator(List.Get(lis, i), item))
			return i;
	}

	throw (Signal.New(List.Failure));
}

method static bool Contains(self_t *lis, any *item) {
	for (int32_t i = 0; i < List.GetLength(lis); i++) {
		if (act(List_t, lis)->_ItemComparator(List.Get(lis, i), item))
			return true;
	}
	return false;
}

method static List_t *Init(List_t *lis) {
	Collection.Init(act(Collection_t, lis));
	act(Collection_t, lis)->_Size	= List._ALLOCATION_BLOCK_SIZE;

	lis->_Item						= _Memory.CountedAllocate(List._ALLOCATION_BLOCK_SIZE, sizeof(any *));

	lis->SetComparator				= SetComparator;
	lis->Add						= Add;
	lis->Remove						= Remove;
	lis->RemoveItem					= RemoveItem;
	lis->Lock						= Collection.Lock;
	lis->Unlock						= Collection.Unlock;
	lis->GetLength					= Collection.GetLength;
	lis->Get						= Get;
	lis->IndexOf					= IndexOf;
	lis->IsEmpty					= Collection.IsEmpty;
	lis->Contains					= Contains;

	return lis;
}

method static List_t *New() {
	return List.Init(new (List_t));
}

method static void Delete(List_t *lis) {
	if (lis == NULL) return;

	mtx_destroy(&act(Collection_t, lis)->_Mtx);

	_Memory.Free(lis->_Item);
	delete (lis);
}

_List List = {
	._Setup						= _Setup,
	._ALLOCATION_BLOCK_SIZE		= 1000,

	.Init						= Init,
	.New						= New,
	.Delete						= Delete,

	.SetComparator				= SetComparator,

	.Add						= Add,
	.Remove						= Remove,
	.RemoveItem					= RemoveItem,

	.Get						= Get,
	.IndexOf					= IndexOf,
};
