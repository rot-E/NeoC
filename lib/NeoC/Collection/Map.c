#include "NeoC/Collection/Map.h"

static void _Setup() {
	Map.Exception signal;
}

static void SetComparator(Map_t *map, bool (* keyComparator)(void *mapKey, void *key), bool (* valueComparator)(void *mapValue, void *value)) {
	map->_KeyComparator		= keyComparator;
	map->_ValueComparator	= valueComparator;
}

static void Put(Map_t *map, void *key, void *value) {
	mtx_lock(&map->_Mtx);

	// 領域不足→確保
	if (map->_Length + 1 >= map->_Size) {
		map->_Size += Map._ALLOCATION_BLOCK_SIZE;
		map->_Item = (Item_t *)(_Memory.ReAllocate(map->_Item, sizeof(Item_t) * map->_Size));
	}

	// 格納
	map->_Item[map->_Length] = (Item_t){
		.Key	= key,
		.Value	= value,
	};

	map->_Length++;

	mtx_unlock(&map->_Mtx);
}

static void Remove(Map_t *map, void *key) throws (Map.Exception) {
	int32_t i;
	bool existence = false;
	for (i = 0; i < Map.GetLength(map); i++)
		if (map->_KeyComparator(Map.Get(map, i).Key, key)) {
			existence = true;
			break;
		}
	if (!existence) throw (Signal.New(Map.Exception));

	mtx_lock(&map->_Mtx);

	for (int32_t j = i; j < Map.GetLength(map) - 1; j++)
		map->_Item[j] = map->_Item[j + 1];

	map->_Length--;

	// 領域過多→解放
	if (map->_Length < map->_Size - Map._ALLOCATION_BLOCK_SIZE) {
		map->_Size -= Map._ALLOCATION_BLOCK_SIZE;
		map->_Item = (Item_t *)(_Memory.ReAllocate(map->_Item, sizeof(Item_t) * map->_Size));
	}

	mtx_unlock(&map->_Mtx);
}

static int32_t GetLength(Map_t *map) {
	return map->_Length;
}

static Item_t Get(Map_t *map, int32_t idx) throws (Map.Exception) {
	if (map->_Length <= idx) throw (Signal.New(Map.Exception));

	return map->_Item[idx];
}

static bool IsEmpty(Map_t *map) {
	return Map.GetLength(map) == 0;
}

static bool ContainsKey(Map_t *map, void *key) {
	for (int32_t i = 0; i < Map.GetLength(map); i++)
		if (map->_KeyComparator(Map.Get(map, i).Key, key)) return true;

	return false;
}

static bool ContainsValue(Map_t *map, void *value) {
	for (int32_t i = 0; i < Map.GetLength(map); i++)
		if (map->_ValueComparator(Map.Get(map, i).Value, value)) return true;

	return false;
}

static Map_t *New() {
	Map_t *map = (Map_t *)(_Memory.Allocate(sizeof(Map_t)));

	map->_Item				= (Item_t *)(_Memory.CountedAllocate(Map._ALLOCATION_BLOCK_SIZE, sizeof(Item_t)));
	map->_Size				= Map._ALLOCATION_BLOCK_SIZE;
	map->_Length			= 0;
	mtx_init(&map->_Mtx, mtx_plain);

	map->SetComparator		= SetComparator;
	map->Put				= Put;
	map->Remove				= Remove;
	map->GetLength			= GetLength;
	map->Get			= Get;
	map->IsEmpty			= IsEmpty;
	map->ContainsKey		= ContainsKey;
	map->ContainsValue		= ContainsValue;

	return map;
}

static void Delete(Map_t *map) {
	mtx_destroy(&map->_Mtx);

	_Memory.Free(map->_Item);
	_Memory.Free(map);
}

_Map Map = {
	._Setup						= _Setup,
	._ALLOCATION_BLOCK_SIZE		= 1000,

	.New						= New,
	.Delete						= Delete,

	.SetComparator				= SetComparator,

	.Put						= Put,
	.Remove						= Remove,

	.GetLength					= GetLength,
	.Get						= Get,

	.IsEmpty					= IsEmpty,
	.ContainsKey				= ContainsKey,
	.ContainsValue				= ContainsValue,
};
