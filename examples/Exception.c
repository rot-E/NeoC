#include "NeoC/Exception.h"

#include <stdio.h>
#include <stdint.h>

void main() {
	struct {
		int32_t FooException;
		int32_t BarException;
		int32_t BazException;
	} es = {
		E.GenerateSignal(),
		E.GenerateSignal(),
		E.GenerateSignal(),
	};
	int32_t HogeException = E.GenerateSignal();


	int32_t result;

	try {
		printf("処理1\n");
		result = 1;
		throw (HogeException);

		printf("処理2\n");
		result = 2;
	} catch (es.FooException) {
		printf("Catch FooException\n");
	} catchN (es.BarException) {
		printf("Catch BarException\n");
	} catchN (es.BazException) {
		printf("Catch BazException\n");
	} catchAll {
		printf("Catch Other Exception\n");
	} finally {
		result = -1;
	} end

	printf("%d\n", result);
}
