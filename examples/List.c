#include "NeoC/Environment.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/Exception/Exception.h"
#include "NeoC/Collection.h"
#include "NeoC/Collection/List.h"

void main() $_ {
	/* List生成 */
	List_t *lis = List.New() in (String_t *);

	lis->SetComparator(lis,
		Comparator(lI, i, String.Equals(lI, i))
	);

	Console.WriteLine(String.NewFormat(u8"Empty? %d", lis->IsEmpty(lis)));
	Console.NewLine();

	/* 領域確保/値配置 */
	String_t *s1 = String.New(u8"test string");
	String_t *s2 = String.New(u8"test string 2");
	String_t *s3 = String.New(u8"test string 3");

	/* アドレス格納 */
	lis->Add(lis, s1);
	lis->Add(lis, s2);
	lis->Add(lis, s3);

	for (int32_t i = 0; i < lis->GetLength(lis); i++) {
		Console.WriteLine(String.NewFormat(
			"%s",
			String.Unpack( lis->Get(lis, i) )
		));
	}

	Console.WriteLine(String.NewFormat(u8"Empty? %d", lis->IsEmpty(lis)));

	String_t *tmp = String.New(u8"test");
	Console.WriteLine(String.NewFormat(u8"Contains \"%s\"? %d", s3->Unpack(s3), lis->Contains(lis, s3)));
	Console.WriteLine(String.NewFormat(u8"Contains \"%s\"? %d", tmp->Unpack(tmp), lis->Contains(lis, tmp)));
	Console.NewLine();

	/* アドレス削除 */
	lis->RemoveItem(lis, s2);
	lis->Remove(lis, 1);

	for (int32_t i = 0; i < lis->GetLength(lis); i++) {
		Console.WriteLine(String.NewFormat(
			"%s",
			String.Unpack( lis->Get(lis, i) )
		));
	}
	Console.NewLine();

	/* 再格納 */
	String_t *s4 = String.New(u8"あいうえお");
	String_t *s5 = String.New(u8"かきくけこ");
	String_t *s6 = String.New(u8"さしすせそ");

	lis->Add(lis, s4);
	lis->Add(lis, s2);
	lis->Add(lis, s5);
	lis->Add(lis, s6);

	for (int32_t i = 0; i < lis->GetLength(lis); i++) {
		Console.WriteLine(String.NewFormat(
			"%s",
			String.Unpack( lis->Get(lis, i) )
		));
	}
	Console.NewLine();

	/* List解放 */
	List.Delete(lis);


	/* 大量確保/解放 */
	lis = List.New() in (String_t *);

	const int32_t SIZE = 5000;
	String_t *strs[SIZE];
	for (int32_t i = 0; i < SIZE; i++) {
		strs[i] = String.NewFormat(u8"STR-%d", i);
		lis->Add(lis, strs[i]);

		if (i % List._ALLOCATION_BLOCK_SIZE == 0)
			Console.WriteLine(String.NewFormat("Idx: %d, Size: %d", i, lis->_Size));
	}

	Console.WriteLine(String.NewFormat(
		"%s",
		String.Unpack( lis->Get(lis, 3000) )
	));

	for (int32_t i = SIZE - 1; 0 <= i; i--) {
		if (i == 3535) continue;

		lis->RemoveItem(lis, strs[i]);

		if ((i - 1) % List._ALLOCATION_BLOCK_SIZE == 0)
			Console.WriteLine(String.NewFormat("Idx: %d, Size: %d", i, lis->_Size));
	}

	Console.WriteLine(String.NewFormat(
		"%s",
		String.Unpack( lis->Get(lis, 0) )
	));

	/* List解放 */
	List.Delete(lis);
} _$
