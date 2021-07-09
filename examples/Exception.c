#include "NeoC/Exception.h"

#include <stdio.h>

void main() $NeoC {
	/* signalの宣言 */
	sign (FooException); // 方法1
	sign (BarException);
	sign (BazException);
	sign (QuxException);

	int32_t QuuxException signal; // 方法2


	int32_t result = 0;

	try {
		printf("処理1\n");
		result = 1;
		throw (QuxException);

		printf("処理2\n");
		result = 2;
	} catch (FooException) {
		printf("Catch FooException\n");
	} catchN (BarException) {
		printf("Catch BarException\n");
	} catchN (BazException) {
		printf("Catch BazException\n");
	} catchAll {
		printf("Catch Other Exception\n");
	} finally {
		result = -1;
	} end

	printf("%d\n", result);
} NeoC$
