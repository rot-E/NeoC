#include "NeoC/Exception.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/System.h"

void main() $NeoC {
	try {
		Console.WriteLine(String.New("call sleep"));
		System.Sleep(3);
		Console.WriteLine(String.New("called sleep"));

		Console.WriteLine(String.New("call usleep"));
		System.USleep(1000 * 1000);
		Console.WriteLine(String.New("called usleep"));
	} catch (System.Exception) {
		Console.WriteErrorLine(String.New("sleep failed."));
	} end
} NeoC$
