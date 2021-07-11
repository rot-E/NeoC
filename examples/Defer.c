#include "NeoC/Environment.h"
#include "NeoC/Defer.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"

void main() $_ {
	int32_t i = 1;

	defer {
		Console.WriteLine(String.New("1"));
		i *= 2;
	} set

	defer {
		Console.WriteLine(String.New("2"));
		i += 10;
	} set

	int *r = execute {
		defer { // なぜ内部に1つまでのdefer~setなら動く? スタックに断片残存の為? ：要調査
			Console.WriteLine(String.New("3"));
			i--;
		} set

		Console.WriteLine(String.New("4"));
		i *= 100;

		int *v = (int *)(malloc(sizeof(int)));
		*v = 100;

		return v;
	} ret

	printf("%d\n", i);
	printf("%d\n", *r);
} _$
