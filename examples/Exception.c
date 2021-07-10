#include "NeoC/Environment.h"
#include "NeoC/Exception.h"
#include "NeoC/Console.h"

void main() $_ {
	/* signalの宣言 */
	sign (FooException); // 方法1
	sign (BarException);
	sign (BazException);
	sign (QuxException);

	Signal_t QuuxException signal; // 方法2


	int32_t result = 0;

	try {
		Console.WriteLine(String.New("処理1"));
		result = 1;
		throw (QuxException);

		Console.WriteLine(String.New("処理2"));
		result = 2;
	} catch (FooException) {
		Console.WriteErrorLine(String.New("Catch FooException"));
	} catchN (BarException) {
		Console.WriteErrorLine(String.New("Catch BarException"));
	} catchN (BazException) {
		Console.WriteErrorLine(String.New("Catch BazException"));
	} catchAll {
		Console.WriteErrorLine(String.New("Catch Other Exception"));
	} finally {
		result = -1;
	} endX

	Console.WriteLine(String.NewFormat("%d", result));
} _$
