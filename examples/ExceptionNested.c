#include "NeoC/Exception.h"
#include "NeoC/Console.h"

void main() $NeoC {
	int32_t HogeException signal;
	int32_t FugaException signal;
	int32_t PiyoException signal;

	int32_t result;

	try {
		try {
			throw (FugaException);
		} catch (FugaException) {
			Console.WriteLine(String.New("Inner: Catch FugaException"));
		} end

		try {
			throw (HogeException);
		} catch (FugaException) {
			Console.WriteLine(String.New("Inner: Catch FugaException"));
		} finally {
			Console.WriteLine(String.New("Caught HogeException? (Ans:No) ;-)"));
		} endX

		throw (PiyoException);
	} catch (HogeException) {
		Console.WriteLine(String.New("Outer: Catch HogeException"));
	} catchN (FugaException) {
		Console.WriteLine(String.New("Outer: Catch FugaException"));
	} catchN (PiyoException) {
		Console.WriteLine(String.New("Outer: Catch PiyoException"));
	} catchAll {
		Console.WriteLine(String.New("Outer: Catch Other Exception"));
	} finally {
		result = -1;
	} endX

	Console.WriteLine(String.NewFormat("%d\n", result));
} NeoC$
