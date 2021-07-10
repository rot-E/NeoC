#include "NeoC/Environment.h"
#include "NeoC/Console.h"
#include "NeoC/String.h"

void main() $_ {
	Console.WriteLine(String.New("test"));
	Console.SetColour(SGR.TEXT.BLUE);
	Console.WriteLine(String.New("test"));
	Console.SetDefaultColour();
	Console.WriteLine(String.New("test"));

	Console.SetState(SGR.SET.BLINK);
	Console.Write(String.New("blink"));
	Console.SetState(SGR.RESET.BLINK);
	Console.WriteLine(String.New(""));

	Console.WriteLine(String.New("test1"));
	Console.WriteLine(String.New("test2"));
	Console.ErasePrevLine();
	Console.WriteLine(String.New("test3"));

	Console.WriteTopLine(String.New("> "));
} _$
