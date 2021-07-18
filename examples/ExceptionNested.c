#include "NeoC/Environment.h"
#include "NeoC/Exception/Signal.h"
#include "NeoC/Exception/Exception.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"

void f(SignalCode_t c) {
	throw (Signal.Build(c, "f"));
}

void main() $_ {
	SignalCode_t HogeException signal;
	SignalCode_t FugaException signal;
	SignalCode_t PiyoException signal;

	int32_t result;

	try {
		try {
			/* Signal.New + SetMessage */
			Signal_t *sig = Signal.New(FugaException);
			Signal.SetMessage(sig, "message from fugaex thrower");
			throw (sig);
		} catch (FugaException) {
			Console.WriteErrorLine(String.New(u8"Inner: Catch FugaException"));

			if (Signal.MessageExists(elicit()))
				Console.WriteErrorLine(String.New(Signal.GetMessage(elicit())));
		} fin

		try {
			/* Signal.New */
			throw (Signal.New(HogeException));
		} catch (FugaException) {
			Console.WriteErrorLine(String.New(u8"Inner: Catch FugaException"));

			if (Signal.MessageExists(elicit()))
				Console.WriteErrorLine(String.New(Signal.GetMessage(elicit())));
		} finally {
			Console.WriteErrorLine(String.New(u8"Caught HogeException? (Ans:No) ;-)"));
		} end

		/* Signal.Build */
		throw (Signal.Build(PiyoException, u8"HELLO :)"));
	} catch (HogeException) {
		Console.WriteErrorLine(String.New(u8"Outer: Catch HogeException"));

		if (Signal.MessageExists(elicit()))
			Console.WriteErrorLine(String.New(Signal.GetMessage(elicit())));
	} catchN (FugaException) {
		Console.WriteErrorLine(String.New(u8"Outer: Catch FugaException"));

		if (Signal.MessageExists(elicit()))
			Console.WriteErrorLine(String.New(Signal.GetMessage(elicit())));
	} catchN (PiyoException) {
		Console.WriteErrorLine(String.New(u8"Outer: Catch PiyoException"));

		if (Signal.MessageExists(elicit()))
			Console.WriteErrorLine(String.New(Signal.GetMessage(elicit())));
	} catchAll {
		Console.WriteErrorLine(String.New(u8"Outer: Catch Other Exception"));

		if (Signal.MessageExists(elicit()))
			Console.WriteErrorLine(String.New(Signal.GetMessage(elicit())));
	} finally {
		result = -1;
	} end

	Console.WriteLine(String.NewFormat(u8"%d", result));

	throw (Signal.Build(HogeException, "Message"));

	f(HogeException);
} _$
