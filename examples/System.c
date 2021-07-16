#include "NeoC/Environment.h"
#include "NeoC/Exception/Exception.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/System.h"

void main() $_ {
	try {
		Console.WriteLine(String.New(u8"call sleep"));
		System.Sleep(3);
		Console.WriteLine(String.New(u8"called sleep"));

		Console.WriteLine(String.New(u8"call usleep"));
		System.USleep(1000 * 1000);
		Console.WriteLine(String.New(u8"called usleep"));
	} catch (System.Exception) {
		Console.WriteErrorLine(String.New(u8"sleep failed."));
	} fin
} _$
