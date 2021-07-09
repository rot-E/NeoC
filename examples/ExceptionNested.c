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
			Console.WriteErrorLine(String.New("Inner: Catch FugaException"));
		} end

		try {
			throw (HogeException);
		} catch (FugaException) {
			Console.WriteErrorLine(String.New("Inner: Catch FugaException"));
		} finally {
			Console.WriteErrorLine(String.New("Caught HogeException? (Ans:No) ;-)"));
		} endX

		throw (PiyoException);
	} catch (HogeException) {
		Console.WriteErrorLine(String.New("Outer: Catch HogeException"));
	} catchN (FugaException) {
		Console.WriteErrorLine(String.New("Outer: Catch FugaException"));
	} catchN (PiyoException) {
		Console.WriteErrorLine(String.New("Outer: Catch PiyoException"));
	} catchAll {
		Console.WriteErrorLine(String.New("Outer: Catch Other Exception"));
	} finally {
		result = -1;
	} endX

	Console.WriteLine(String.NewFormat("%d", result));
} NeoC$
