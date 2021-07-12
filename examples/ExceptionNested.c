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
			Console.WriteErrorLine(String.New(u8"Inner: Catch FugaException"));
		} fin

		try {
			throw (HogeException);
		} catch (FugaException) {
			Console.WriteErrorLine(String.New(u8"Inner: Catch FugaException"));
		} finally {
			Console.WriteErrorLine(String.New(u8"Caught HogeException? (Ans:No) ;-)"));
		} end

		throw (PiyoException);
	} catch (HogeException) {
		Console.WriteErrorLine(String.New(u8"Outer: Catch HogeException"));
	} catchN (FugaException) {
		Console.WriteErrorLine(String.New(u8"Outer: Catch FugaException"));
	} catchN (PiyoException) {
		Console.WriteErrorLine(String.New(u8"Outer: Catch PiyoException"));
	} catchAll {
		Console.WriteErrorLine(String.New(u8"Outer: Catch Other Exception"));
	} finally {
		result = -1;
	} end

	Console.WriteLine(String.NewFormat(u8"%d", result));
} _$
