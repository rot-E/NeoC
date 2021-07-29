#include <NeoC/Base/Defer.h>
#include <NeoC/Base/Environment.h>
#include <NeoC/Type/String.h>
#include <NeoC/Console.h>

String_t *fn() {
		// 組立に使った領域は事後解放
	String_t *str = String.New(u8"outer");
	defer {
		Console.WriteLine(String.New(u8"deleting str"));
		String.Delete(str);
		Console.WriteLine(String.New(u8"deleted str"));
	} set

	retrieve {
			// 組立られた領域は解放されずアドレスを返却
		return String.Concat(str, String.New(u8" innner"));
	} ret
}

void main() $_ {
	Console.WriteLine(fn());
} _$
