#include "NeoC/Exception.h"

#include <stdio.h>

void main() $NeoC {
	int32_t HogeException signal;
	int32_t FugaException signal;
	int32_t PiyoException signal;

	int32_t result;

	try {
		try {
			throw (FugaException);
		} catch (FugaException) {
			printf("Inner: Catch FugaException\n");
		} endX

		try {
			throw (HogeException);
		} catch (FugaException) {
			printf("Inner: Catch FugaException\n");
		} finally {
			printf("Caught HogeException? (Ans:No) ;-)\n");
		} end

		throw (PiyoException);
	} catch (HogeException) {
		printf("Outer: Catch HogeException\n");
	} catchN (FugaException) {
		printf("Outer: Catch FugaException\n");
	} catchN (PiyoException) {
		printf("Outer: Catch PiyoException\n");
	} catchAll {
		printf("Outer: Catch Other Exception\n");
	} finally {
		result = -1;
	} end

	printf("%d\n", result);
} NeoC$
