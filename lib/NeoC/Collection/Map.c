#include "NeoC/Collection/Map.h"

method static void _Setup() {
	Map.Exception signal;

	Map.Lock		= Collection.Lock;
	Map.Unlock		= Collection.Unlock;
	Map.GetLength	= Collection.GetLength;
	Map.IsEmpty		= Collection.IsEmpty;
}

method static void SetComparator(self_t *map, bool (* keyComparator)(any *mapKey, any *key), bool (* valueComparator)(any *mapValue, any *value)) {
	act(Map_t, map)->_KeyComparator		= keyComparator;
	act(Map_t, map)->_ValueComparator	= valueComparator;
}

method static void Put(self_t *map, any *key, any *value) {
	Map.Lock(map);

	// 領域不足→確保
	if (Map.GetLength(map) + 1 >= act(Collection_t, map)->_Size) {
		act(Collection_t, map)->_Size += Map._ALLOCATION_BLOCK_SIZE;
		act(Map_t, map)->_Item = (Item_t *)(_Memory.ReAllocate(
			act(Map_t, map)->_Item,
			act(Collection_t, map)->_Size * sizeof(Item_t))
		);
	}

	// 格納
	act(Map_t, map)->_Item[Map.GetLength(map)] = (Item_t){
		.Key	= key,
		.Value	= value,
	};

	act(Collection_t, map)->_Length++;

	Map.Unlock(map);
}

method static void Remove(self_t *map, any *key) throws (Map.Exception) {
	int32_t i;
	bool existence = false;
	for (i = 0; i < Map.GetLength(map); i++)
		if (act(Map_t, map)->_KeyComparator(Map.Get(map, i).Key, key)) {
			existence = true;
			break;
		}
	if (!existence) throw (Signal.New(Map.Exception));

	Map.Lock(map);

	for (int32_t j = i; j < Map.GetLength(map) - 1; j++)
		act(Map_t, map)->_Item[j] = act(Map_t, map)->_Item[j + 1];

	act(Collection_t, map)->_Length--;

	// 領域過多→解放
	if (Map.GetLength(map) < act(Collection_t, map)->_Size - Map._ALLOCATION_BLOCK_SIZE) {
		act(Collection_t, map)->_Size -= Map._ALLOCATION_BLOCK_SIZE;
		act(Map_t, map)->_Item = (Item_t *)(_Memory.ReAllocate(
			act(Map_t, map)->_Item,
			act(Collection_t, map)->_Size * sizeof(Item_t))
		);
	}

	Map.Unlock(map);
}

method static Item_t Get(self_t *map, int32_t idx) throws (Map.Exception) {
	if (Map.GetLength(map) <= idx) throw (Signal.New(Map.Exception));

	return act(Map_t, map)->_Item[idx];
}

method static bool ContainsKey(self_t *map, any *key) {
	for (int32_t i = 0; i < Map.GetLength(map); i++)
		if (act(Map_t, map)->_KeyComparator(Map.Get(map, i).Key, key)) return true;

	return false;
}

method static bool ContainsValue(self_t *map, any *value) {
	for (int32_t i = 0; i < Map.GetLength(map); i++)
		if (act(Map_t, map)->_ValueComparator(Map.Get(map, i).Value, value)) return true;

	return false;
}

method static Map_t *Init(Map_t *map) {
	Collection.Init(act(Collection_t, map));
	act(Collection_t, map)->_Size		= Map._ALLOCATION_BLOCK_SIZE;

	map->_Item							= (Item_t *)(_Memory.CountedAllocate(Map._ALLOCATION_BLOCK_SIZE, sizeof(Item_t)));

	map->SetComparator					= SetComparator;
	map->Put							= Put;
	map->Remove							= Remove;
	map->Lock							= Collection.Lock;
	map->Unlock							= Collection.Unlock;
	map->GetLength						= Collection.GetLength;
	map->Get							= Get;
	map->IsEmpty						= Collection.IsEmpty;
	map->ContainsKey					= ContainsKey;
	map->ContainsValue					= ContainsValue;

	return map;
}

method static Map_t *New() {
	return Map.Init(new (Map_t));
}

static void Delete(Map_t *map) {
	if (map == NULL) return;

	mtx_destroy(&act(Collection_t, map)->_Mtx);

	_Memory.Free(map->_Item);
	delete (map);
}

_Map Map = {
	._Setup						= _Setup,
	._ALLOCATION_BLOCK_SIZE		= 1000,

	.Init						= Init,
	.New						= New,
	.Delete						= Delete,

	.SetComparator				= SetComparator,

	.Put						= Put,
	.Remove						= Remove,

	.Get						= Get,

	.ContainsKey				= ContainsKey,
	.ContainsValue				= ContainsValue,
};
