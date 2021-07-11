#include "NeoC/Environment.h"
#include "NeoC/Defer.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"

#include <stdlib.h>

int fn(int a, int b) {
	int *i = (int *)(malloc(sizeof(int)));
	defer {
		free(i);
	} set

	return execute {
		*i = 3;
		*i = a + b * *i;

		Console.WriteLine(String.NewFormat("ret: %d\n", *i));
		return *i;
	} ret
}

void main() $_ {
	Console.WriteLine(String.NewFormat("catch: %d", fn(12, 31)));
} _$
