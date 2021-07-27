#include <NeoC/Base/Environment.h>
#include <NeoC/String.h>
#include <NeoC/Console.h>

void main() $_ {
	Console.WriteLine(String.New(u8"test"));
	Console.SetColour(SGR.TEXT.BLUE);
	Console.WriteLine(String.New(u8"test"));
	Console.SetDefaultColour();
	Console.WriteLine(String.New(u8"test"));

	Console.SetState(SGR.SET.BLINK);
	Console.Write(String.New(u8"blink"));
	Console.SetState(SGR.RESET.BLINK);
	Console.WriteLine(String.New(u8""));

	Console.WriteLine(String.New(u8"test1"));
	Console.WriteLine(String.New(u8"test2"));
	Console.ErasePrevLine();
	Console.WriteLine(String.New(u8"test3"));
} _$
