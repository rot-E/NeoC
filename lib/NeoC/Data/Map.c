#include "NeoC/Data/Map.h"

static void _Setup() {
	Map.Exception signal;
}

static void SetComparator(Map_t *map, bool (* keyComparator)(void *mapKey, void *key), bool (* valueComparator)(void *mapValue, void *value)) {
	map->_KeyComparator		= keyComparator;
	map->_ValueComparator	= valueComparator;
}

static void Put(Map_t *map, void *key, void *value) {
	mtx_lock(&map->_Mtx);

	// map->_Size++次第で例外スロー

	map->_Set[map->_Size++] = (Set_t){
		.Key	= key,
		.Value	= value,
	};

	mtx_unlock(&map->_Mtx);
}

static void Remove(Map_t *map, void *key) throws (Map.Exception) {
	mtx_lock(&map->_Mtx);

	int32_t i;
	bool existence = false;
	for (i = 0; i < Map.GetSize(map); i++)
		if (map->_KeyComparator(Map.GetSet(map, i).Key, key)) {
			existence = true;
			break;
		}
	if (!existence) {
		mtx_unlock(&map->_Mtx);
		throw (Signal.New(Map.Exception));
	}

	for (int32_t j = i; j < Map.GetSize(map) - 1; j++)
		map->_Set[j] = map->_Set[j + 1];

	map->_Size--;

	mtx_unlock(&map->_Mtx);
}

static int32_t GetSize(Map_t *map) {
	return map->_Size;
}

static Set_t GetSet(Map_t *map, int32_t i) throws (Map.Exception) {
	if (map->_Size < i) throw (Signal.New(Map.Exception));

	return map->_Set[i];
}

static bool IsEmpty(Map_t *map) {
	return map->_Size == 0;
}

static bool ContainsKey(Map_t *map, void *key) {
	for (int32_t i = 0; i < Map.GetSize(map); i++)
		if (map->_KeyComparator(Map.GetSet(map, i).Key, key)) return true;

	return false;
}

static bool ContainsValue(Map_t *map, void *value) {
	for (int32_t i = 0; i < Map.GetSize(map); i++)
		if (map->_ValueComparator(Map.GetSet(map, i).Value, value)) return true;

	return false;
}

static Map_t *New(const size_t keySize, const size_t valueSize) {
	Map_t *map = (Map_t *)(_Memory.Allocate(sizeof(Map_t)));

	map->_Set				= (Set_t *)(_Memory.CountedAllocate(Map._SIZE_MAX, sizeof(Set_t)));
	map->_Size				= 0;
	map->_KeySize			= keySize;
	map->_ValueSize			= valueSize;
	mtx_init(&map->_Mtx, mtx_plain);

	map->SetComparator		= SetComparator;
	map->Put				= Put;
	map->Remove				= Remove;
	map->GetSize			= GetSize;
	map->GetSet				= GetSet;
	map->IsEmpty			= IsEmpty;
	map->ContainsKey		= ContainsKey;
	map->ContainsValue		= ContainsValue;

	return map;
}

static void Delete(Map_t *map) {
	mtx_destroy(&map->_Mtx);

	_Memory.Free(map->_Set);
	_Memory.Free(map);
}

_Map Map = {
	._Setup				= _Setup,
	._SIZE_MAX			= 1000,

	.New				= New,
	.Delete				= Delete,

	.SetComparator		= SetComparator,

	.Put				= Put,
	.Remove				= Remove,

	.GetSize			= GetSize,
	.GetSet				= GetSet,

	.IsEmpty			= IsEmpty,
	.ContainsKey		= ContainsKey,
	.ContainsValue		= ContainsValue,
};
