#include "Map.h"

static void _Setup() {
	Map.Exception signal;
}

static bool IsEmpty(Map_t *map) {
	return map->_Size == 0;
}

static bool ContainsKey(Map_t *map, void *key) {
	for (int32_t i = 0; i < Map.GetSize(map); i++)
		if (map->_KeyComparer(Map.GetSet(map, i).Key, key)) return true;

	return false;
}

static bool ContainsValue(Map_t *map, void *value) {
	for (int32_t i = 0; i < Map.GetSize(map); i++)
		if (map->_ValueComparer(Map.GetSet(map, i).Value, value)) return true;

	return false;
}

static void Put(Map_t *map, void *key, void *value) {
	mtx_lock(&map->_Mtx);

	map->_Set[map->_Size++] = (Set_t){
		.Key	= key,
		.Value	= value,
	};

	mtx_unlock(&map->_Mtx);
}

static void Remove(Map_t *map, void *key) {
	mtx_lock(&map->_Mtx);

	int32_t i;
	for (i = 0; i < Map.GetSize(map); i++)
		if (map->_KeyComparer(Map.GetSet(map, i).Key, key)) break;

	for (int32_t j = Map.GetSize(map) - 1; i < j; j--)
		map->_Set[j - 1] = map->_Set[j];

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

static Map_t *New(const size_t keySize, const size_t valueSize, bool (* keyComparer)(void *mapKey, void *key), bool (* valueComparer)(void *mapValue, void *value)) {
	Map_t *map = (Map_t *)(_Memory.Allocate(sizeof(Map_t)));

	map->_Set				= (Set_t *)(_Memory.CountedAllocate(Map._SIZE_MAX, sizeof(Set_t)));
	map->_Size				= 0;
	map->_KeySize			= keySize;
	map->_ValueSize			= valueSize;
	map->_KeyComparer		= keyComparer;
	map->_ValueComparer		= valueComparer;
	mtx_init(&map->_Mtx, mtx_plain);

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

	.Put				= Put,
	.Remove				= Remove,

	.GetSize			= GetSize,
	.GetSet				= GetSet,

	.IsEmpty			= IsEmpty,
	.ContainsKey		= ContainsKey,
	.ContainsValue		= ContainsValue,
};
