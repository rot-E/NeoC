#include "NeoC/Environment.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/Exception/Exception.h"
#include "NeoC/Data/Map.h"

void main() $_ {
	/* Map生成 */
	Map_t *map = Map.New(
		T(String_t *, int32_t *), ({
			bool kcmpr(void *mapK, void *k) {
				return String.Equals((String_t *)(mapK), (String_t *)(k));
			};
			kcmpr;
		}), ({
			bool vcmpr(void *mapV, void *v) {
				return *(int32_t *)(mapV) == *(int32_t *)(v);
			};
			vcmpr;
		})
	);
	Console.WriteLine(String.NewFormat("Empty? %d", map->IsEmpty(map)));
	Console.NewLine();

	/* 領域確保/値配置 */
	String_t *s1 = String.New("test string");
	String_t *s2 = String.New("test string 2");
	String_t *s3 = String.New("test string 3");

	int32_t *i1 = (int32_t *)(_Memory.Allocate(sizeof(int32_t)));
	*i1 = 42;
	int32_t *i2 = (int32_t *)(_Memory.Allocate(sizeof(int32_t)));
	*i2 = 24;
	int32_t *i3 = (int32_t *)(_Memory.Allocate(sizeof(int32_t)));
	*i3 = -12;

	/* アドレス格納 */
	map->Put(map, s1, i1);
	map->Put(map, s2, i2);
	map->Put(map, s3, i3);

	for (int32_t i = 0; i < map->GetSize(map); i++) {
		Console.WriteLine(String.NewFormat(
			"%s:%d",
			String.Unpack((String_t *)( map->GetSet(map, i).Key )),
			*(int32_t *)( map->GetSet(map, i).Value )
		));
	}
	Console.WriteLine(String.NewFormat("Empty? %d", map->IsEmpty(map)));
	int32_t *tmpi = (int32_t *)(_Memory.Allocate(sizeof(int32_t)));
	*tmpi = 100;

	String_t *tmp = String.New("test");
	Console.WriteLine(String.NewFormat("Contains key \"%s\"? %d", s3->Unpack(s3), map->ContainsKey(map, s3)));
	Console.WriteLine(String.NewFormat("Contains key \"%s\"? %d", tmp->Unpack(tmp), map->ContainsKey(map, tmp)));
	Console.WriteLine(String.NewFormat("Contains value \"%d\"? %d", *i1, map->ContainsValue(map, i1)));
	Console.WriteLine(String.NewFormat("Contains value \"%d\"? %d", *tmpi, map->ContainsValue(map, tmpi)));
	Console.NewLine();

	/* アドレス削除 */
	map->Remove(map, s2);

	for (int32_t i = 0; i < map->GetSize(map); i++) {
		Console.WriteLine(String.NewFormat(
			"%s:%d",
			String.Unpack((String_t *)( map->GetSet(map, i).Key )),
			*(int32_t *)( map->GetSet(map, i).Value )
		));
	}
	Console.NewLine();

	/* 再格納 */
	map->Put(map, s2, i2);
	map->Put(map, s2, i2);
	map->Put(map, s2, i2);

	for (int32_t i = 0; i < map->GetSize(map); i++) {
		Console.WriteLine(String.NewFormat(
			"%s:%d",
			String.Unpack((String_t *)( map->GetSet(map, i).Key )),
			*(int32_t *)( map->GetSet(map, i).Value )
		));
	}
	Console.NewLine();

	/* Map解放 */
	Map.Delete(map);
} _$
