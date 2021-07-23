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
		map->_Elem = (Elem_t *)(_Memory.ReAllocate(map->_Elem, sizeof(Elem_t) * map->_Size));
	}

	// 格納
	map->_Elem[map->_Length] = (Elem_t){
		.Key	= key,
		.Value	= value,
	};

	map->_Length++;

	mtx_unlock(&map->_Mtx);
}

static void Remove(Map_t *map, void *key) throws (Map.Exception) {
	mtx_lock(&map->_Mtx);

	int32_t i;
	bool existence = false;
	for (i = 0; i < Map.GetLength(map); i++)
		if (map->_KeyComparator(Map.GetElem(map, i).Key, key)) {
			existence = true;
			break;
		}
	if (!existence) {
		mtx_unlock(&map->_Mtx);
		throw (Signal.New(Map.Exception));
	}

	for (int32_t j = i; j < Map.GetLength(map) - 1; j++)
		map->_Elem[j] = map->_Elem[j + 1];

	map->_Length--;

	// 領域過多→解放
	if (map->_Length < map->_Size - Map._ALLOCATION_BLOCK_SIZE) {
		map->_Size -= Map._ALLOCATION_BLOCK_SIZE;
		map->_Elem = (Elem_t *)(_Memory.ReAllocate(map->_Elem, sizeof(Elem_t) * map->_Size));
	}

	mtx_unlock(&map->_Mtx);
}

static int32_t GetLength(Map_t *map) {
	return map->_Length;
}

static Elem_t GetElem(Map_t *map, int32_t i) throws (Map.Exception) {
	if (map->_Length <= i) throw (Signal.New(Map.Exception));

	return map->_Elem[i];
}

static bool IsEmpty(Map_t *map) {
	return map->_Length == 0;
}

static bool ContainsKey(Map_t *map, void *key) {
	for (int32_t i = 0; i < Map.GetLength(map); i++)
		if (map->_KeyComparator(Map.GetElem(map, i).Key, key)) return true;

	return false;
}

static bool ContainsValue(Map_t *map, void *value) {
	for (int32_t i = 0; i < Map.GetLength(map); i++)
		if (map->_ValueComparator(Map.GetElem(map, i).Value, value)) return true;

	return false;
}

static Map_t *New() {
	Map_t *map = (Map_t *)(_Memory.Allocate(sizeof(Map_t)));

	map->_Elem				= (Elem_t *)(_Memory.CountedAllocate(Map._ALLOCATION_BLOCK_SIZE, sizeof(Elem_t)));
	map->_Size				= Map._ALLOCATION_BLOCK_SIZE;
	map->_Length			= 0;
	mtx_init(&map->_Mtx, mtx_plain);

	map->SetComparator		= SetComparator;
	map->Put				= Put;
	map->Remove				= Remove;
	map->GetLength			= GetLength;
	map->GetElem			= GetElem;
	map->IsEmpty			= IsEmpty;
	map->ContainsKey		= ContainsKey;
	map->ContainsValue		= ContainsValue;

	return map;
}

static void Delete(Map_t *map) {
	mtx_destroy(&map->_Mtx);

	_Memory.Free(map->_Elem);
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
	.GetElem						= GetElem,

	.IsEmpty					= IsEmpty,
	.ContainsKey				= ContainsKey,
	.ContainsValue				= ContainsValue,
};
