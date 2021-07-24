#include "NeoC/Base/Environment.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/Collection/Collection.h"
#include "NeoC/Collection/Map.h"

void main() $_ {
	/* Map生成 */
	Map_t *map = Map.New() in (String_t *, int32_t *);

	map->SetComparator(map,
		Comparator(mapK, k, String.Equals(mapK, k)),
		Comparator(mapV, v, *(int32_t *)(mapV) == *(int32_t *)(v))
	);

	Console.WriteLine(String.NewFormat(u8"Empty? %d", map->IsEmpty(map)));
	Console.NewLine();

	/* 領域確保/値配置 */
	String_t *s1 = String.New(u8"test string");
	String_t *s2 = String.New(u8"test string 2");
	String_t *s3 = String.New(u8"test string 3");

	int32_t *i1 = $(int32_t, 42);
	int32_t *i2 = $(int32_t, 24);
	int32_t *i3 = $(int32_t, -12);

	/* アドレス格納 */
	map->Put(map, s1, i1);
	map->Put(map, s2, i2);
	map->Put(map, s3, i3);

	for (int32_t i = 0; i < map->GetLength(map); i++) {
		Console.WriteLine(String.NewFormat(
			"%s:%d",
			String.Unpack( map->Get(map, i).Key ),
			*(int32_t *)( map->Get(map, i).Value )
		));
	}
	Console.WriteLine(String.NewFormat(u8"Empty? %d", map->IsEmpty(map)));

	String_t *tmp = String.New(u8"test");
	int32_t *tmpi = $(int32_t, 100);
	Console.WriteLine(String.NewFormat(u8"Contains key \"%s\"? %d", s3->Unpack(s3), map->ContainsKey(map, s3)));
	Console.WriteLine(String.NewFormat(u8"Contains key \"%s\"? %d", tmp->Unpack(tmp), map->ContainsKey(map, tmp)));
	Console.WriteLine(String.NewFormat(u8"Contains value \"%d\"? %d", *i1, map->ContainsValue(map, i1)));
	Console.WriteLine(String.NewFormat(u8"Contains value \"%d\"? %d", *tmpi, map->ContainsValue(map, tmpi)));
	Console.NewLine();

	/* アドレス削除 */
	map->Remove(map, s2);

	for (int32_t i = 0; i < map->GetLength(map); i++) {
		Console.WriteLine(String.NewFormat(
			"%s:%d",
			String.Unpack( map->Get(map, i).Key ),
			*(int32_t *)( map->Get(map, i).Value )
		));
	}
	Console.NewLine();

	/* 再格納 */
	map->Put(map, String.New(u8"あいうえお"), $(int32_t,  -1));
	map->Put(map, s2, i2);
	map->Put(map, String.New(u8"かきくけこ"), $(int32_t,  -2));
	map->Put(map, String.New(u8"さしすせそ"), $(int32_t,  -3));

	for (int32_t i = 0; i < map->GetLength(map); i++) {
		Console.WriteLine(String.NewFormat(
			"%s:%d",
			String.Unpack( map->Get(map, i).Key ),
			*(int32_t *)( map->Get(map, i).Value )
		));
	}
	Console.NewLine();

	/* Map解放 */
	Map.Delete(map);


	/* 大量確保/解放 */
	map = Map.New() in (String_t *, int32_t *);

	const int32_t SIZE = 5000;
	String_t *strs[SIZE];
	for (int32_t i = 0; i < SIZE; i++) {
		strs[i] = String.NewFormat(u8"STR-%d", i);
		map->Put(map, strs[i], $(int32_t, i));

		if (i % Map._ALLOCATION_BLOCK_SIZE == 0)
			Console.WriteLine(String.NewFormat("Idx: %d, Size: %d", i, map->_Size));
	}

	Console.WriteLine(String.NewFormat(
		"%s:%d",
		String.Unpack( map->Get(map, 3000).Key ),
		*(int32_t *)( map->Get(map, 3000).Value )
	));

	for (int32_t i = SIZE - 1; 0 <= i; i--) {
		if (i == 3535) continue;

		map->Remove(map, strs[i]);

		if ((i - 1) % Map._ALLOCATION_BLOCK_SIZE == 0)
			Console.WriteLine(String.NewFormat("Idx: %d, Size: %d", i, map->_Size));
	}

	Console.WriteLine(String.NewFormat(
		"%s:%d",
		String.Unpack( map->Get(map, 0).Key ),
		*(int32_t *)( map->Get(map, 0).Value )
	));

	Map.Delete(map);
} _$
