#include <NeoC/Base/Exception/Signal.h>
#include <NeoC/Base/Exception/Exception.h>
#include <NeoC/Base/Environment.h>
#include <NeoC/String.h>
#include <NeoC/Console.h>

void main() $_ {
	/* signalの宣言 */
	sign (FooException); // 方法1
	sign (BarException);
	sign (BazException);
	sign (QuxException);

	SignalCode_t QuuxException signal; // 方法2


	int32_t result = 0;

	try {
		Console.WriteLine(String.New(u8"処理1"));
		result = 1;
		throw (Signal.New(QuxException));

		Console.WriteLine(String.New(u8"処理2"));
		result = 2;
	} catch (FooException) {
		Console.WriteErrorLine(String.New(u8"Catch FooException"));
	} catchN (BarException) {
		Console.WriteErrorLine(String.New(u8"Catch BarException"));
	} catchN (BazException) {
		Console.WriteErrorLine(String.New(u8"Catch BazException"));
	} catchAll {
		Console.WriteErrorLine(String.New(u8"Catch Other Exception"));
	} finally {
		result = -1;
	} end

	Console.WriteLine(String.NewFormat(u8"%d", result));
} _$
