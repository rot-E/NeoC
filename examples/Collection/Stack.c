#include "NeoC/Base/Environment.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/Collection/Collection.h"
#include "NeoC/Collection/Stack.h"

void main() $_ {
	/* Stack生成 */
	Stack_t *st = Stack.New() in (String_t *);

	Console.WriteLine(String.NewFormat(u8"Empty? %d", st->IsEmpty(st)));
	Console.NewLine();

	/* アドレス格納 */
	st->Push(st, String.New(u8"test string"));
	st->Push(st, String.New(u8"test string 2"));
	st->Push(st, String.New(u8"test string 3"));
	st->Push(st, String.New(u8"あいうえお"));
	st->Push(st, String.New(u8"かきくけこ"));
	st->Push(st, String.New(u8"さしすせそ"));
	Console.WriteLine(String.NewFormat(u8"Empty? %d", st->IsEmpty(st)));

	Console.WriteLine(String.NewFormat(
		"%s (Peek)", String.Unpack(st->Peek(st))
	));
	Console.WriteLine(String.NewFormat(
		"%s (Peek)", String.Unpack(st->Peek(st))
	));
	Console.WriteLine(String.NewFormat(
		"%s (Peek)", String.Unpack(st->Peek(st))
	));

	for (int32_t i = st->GetLength(st); 0 < i; i--) {
		Console.WriteLine(String.NewFormat(
			"%s", String.Unpack(st->Pop(st))
		));
	}
	Console.NewLine();

	/* Duplicate / Exchange */
	st->Push(st, String.New(u8"sssss"));
	st->Duplicate(st);
	st->Push(st, String.New(u8"ttttt"));
	st->Push(st, String.New(u8"aaaaa"));
	st->Dup(st);
	st->Push(st, String.New(u8"ccccc"));
	st->Push(st, String.New(u8"kkkkk"));
	st->Exchange(st);

	for (int32_t i = st->GetLength(st); 0 < i; i--) {
		Console.WriteLine(String.NewFormat(
			"%s", String.Unpack(st->Pop(st))
		));
	}
	Console.NewLine();

	/* LeftRotate / RightRotate */
	st->Push(st, String.New(u8"sssss"));
	st->Push(st, String.New(u8"ttttt"));
	st->Push(st, String.New(u8"aaaaa"));
	st->Push(st, String.New(u8"ccccc"));
	st->Push(st, String.New(u8"kkkkk"));
	st->LeftRotate(st, 2);

	for (int32_t i = st->GetLength(st); 0 < i; i--) {
		Console.WriteLine(String.NewFormat(
			"%s", String.Unpack(st->Pop(st))
		));
	}
	Console.NewLine();

	st->Push(st, String.New(u8"sssss"));
	st->Push(st, String.New(u8"ttttt"));
	st->Push(st, String.New(u8"aaaaa"));
	st->Push(st, String.New(u8"ccccc"));
	st->Push(st, String.New(u8"kkkkk"));
	st->RightRotate(st, 2);

	for (int32_t i = st->GetLength(st); 0 < i; i--) {
		Console.WriteLine(String.NewFormat(
			"%s", String.Unpack(st->Pop(st))
		));
	}
	Console.NewLine();

	/* Stack解放 */
	Stack.Delete(st);


	/* 大量確保/解放 */
	st = Stack.New() in (String_t *);

	const int32_t SIZE = 5000;
	for (int32_t i = 0; i < SIZE; i++) {
		st->Push(st, String.NewFormat(u8"STR-%d", i));

		if (i % Stack._ALLOCATION_BLOCK_SIZE == 0)
			Console.WriteLine(String.NewFormat("Idx: %d, Size: %d", i, st->_Size));
	}

	for (int32_t i = SIZE - 1; 0 <= i; i--) {
		st->Pop(st);

		if ((i - 1) % List._ALLOCATION_BLOCK_SIZE == 0)
			Console.WriteLine(String.NewFormat("Idx: %d, Size: %d", i, st->_Size));
	}

	Stack.Delete(st);
} _$
