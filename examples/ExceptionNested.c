#include "NeoC/Environment.h"
#include "NeoC/Exception.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"

void main() $_ {
	Signal_t HogeException signal;
	Signal_t FugaException signal;
	Signal_t PiyoException signal;

	int32_t result;

	try {
		try {
			throw (FugaException);
		} catch (FugaException) {
			Console.WriteErrorLine(String.New("Inner: Catch FugaException"));
		} fin

		try {
			throw (HogeException);
		} catch (FugaException) {
			Console.WriteErrorLine(String.New("Inner: Catch FugaException"));
		} finally {
			Console.WriteErrorLine(String.New("Caught HogeException? (Ans:No) ;-)"));
		} end

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
	} end

	Console.WriteLine(String.NewFormat("%d", result));
} _$
