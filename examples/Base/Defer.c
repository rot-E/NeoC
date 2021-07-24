#include "NeoC/Base/Defer.h"
#include "NeoC/Base/Environment.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"

void main() $_ {
	int32_t i = 1;

	defer {
		Console.WriteLine(String.New(u8"1"));
		i *= 2;
	} set

	defer {
		Console.WriteLine(String.New(u8"2"));
		i += 10;
	} set

	execute {
		defer { // なぜ内部に1つまでのdefer~setなら動く? スタックに断片残存の為? ：要調査
			Console.WriteLine(String.New(u8"3"));
			i--;
		} set

		Console.WriteLine(String.New(u8"4"));
		i *= 100;
	} ret

	Console.WriteLine(String.NewFormat(u8"%d\n", i));


	defer {
		Console.WriteLine(String.New(u8"defer"));
	} set

	int32_t *r = execute {
		int32_t *v = $(int32_t, 200);

		return v;
	} ret

	Console.WriteLine(String.NewFormat(u8"%d", *r));
} _$
