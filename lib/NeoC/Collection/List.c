#include "NeoC/Collection/List.h"

static void _Setup() {
	List.Exception signal;
	List.Failure signal;
}

static void SetComparator(List_t *lis, bool (* itemComparator)(void *listItem, void *item)) {
	lis->_ItemComparator = itemComparator;
}

static void Add(List_t *lis, void *item) {
	mtx_lock(&lis->_Mtx);

	// 領域不足→確保
	if (lis->_Length + 1 >= lis->_Size) {
		lis->_Size += List._ALLOCATION_BLOCK_SIZE;
		lis->_Item = _Memory.ReAllocate(lis->_Item, lis->_Size * sizeof(void *));
	}

	// 格納
	lis->_Item[lis->_Length] = item;

	lis->_Length++;

	mtx_unlock(&lis->_Mtx);
}

static void Remove(List_t *lis, const int32_t idx) throws (List.Exception) {
	if (lis->_Length <= idx) throw (Signal.New(List.Exception));

	mtx_lock(&lis->_Mtx);

	for (int32_t j = idx; j < List.GetLength(lis) - 1; j++)
		lis->_Item[j] = lis->_Item[j + 1];

	lis->_Length--;

	mtx_unlock(&lis->_Mtx);
}

static void RemoveItem(List_t *lis, void *item) throws (List.Exception) {
	int32_t i;
	bool existence = false;
	for (i = 0; i < List.GetLength(lis); i++)
		if (lis->_ItemComparator(List.Get(lis, i), item)) {
			existence = true;
			break;
		}
	if (!existence) throw (Signal.New(List.Exception));

	mtx_lock(&lis->_Mtx);

	for (int32_t j = i; j < List.GetLength(lis) - 1; j++)
		lis->_Item[j] = lis->_Item[j + 1];

	lis->_Length--;

	// 領域過多→解放
	if (lis->_Length < lis->_Size - List._ALLOCATION_BLOCK_SIZE) {
		lis->_Size -= List._ALLOCATION_BLOCK_SIZE;
		lis->_Item = _Memory.ReAllocate(lis->_Item, lis->_Size * sizeof(void *));
	}

	mtx_unlock(&lis->_Mtx);
}

static int32_t GetLength(List_t *lis) {
	return lis->_Length;
}

static void *Get(List_t *lis, int32_t idx) {
	if (lis->_Length <= idx) throw (Signal.New(List.Exception));

	return lis->_Item[idx];
}

static int32_t IndexOf(List_t *lis, void *item) throws (List.Failure) {
	for (int32_t i = 0; i < List.GetLength(lis); i++) {
		if (lis->_ItemComparator(List.Get(lis, i), item))
			return i;
	}

	throw (Signal.New(List.Failure));
}

static bool IsEmpty(List_t *lis) {
	return List.GetLength(lis) == 0;
}

static bool Contains(List_t *lis, void *item) {
	for (int32_t i = 0; i < List.GetLength(lis); i++) {
		if (lis->_ItemComparator(List.Get(lis, i), item))
			return true;
	}
	return false;
}

static List_t *New() {
	List_t *lis = (List_t *)(_Memory.Allocate(sizeof(List_t)));

	lis->_Item				= _Memory.CountedAllocate(List._ALLOCATION_BLOCK_SIZE, sizeof(void *));
	lis->_Size				= List._ALLOCATION_BLOCK_SIZE;
	lis->_Length			= 0;
	mtx_init(&lis->_Mtx, mtx_plain);

	lis->SetComparator		= SetComparator;
	lis->Add				= Add;
	lis->Remove				= Remove;
	lis->RemoveItem			= RemoveItem;
	lis->GetLength			= GetLength;
	lis->Get				= Get;
	lis->IndexOf			= IndexOf;
	lis->IsEmpty			= IsEmpty;
	lis->Contains			= Contains;

	return lis;
}

static void Delete(List_t *lis) {
	mtx_destroy(&lis->_Mtx);

	_Memory.Free(lis->_Item);
	_Memory.Free(lis);
}

_List List = {
	._Setup						= _Setup,
	._ALLOCATION_BLOCK_SIZE		= 1000,

	.New						= New,
	.Delete						= Delete,

	.SetComparator				= SetComparator,

	.Add						= Add,
	.Remove						= Remove,
	.RemoveItem					= RemoveItem,

	.GetLength					= GetLength,
	.Get						= Get,
	.IndexOf					= IndexOf,

	.IsEmpty					= IsEmpty,
	.Contains					= Contains,
};
