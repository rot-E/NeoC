#include "NeoC/Environment.h"
#include "NeoC/Defer.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"

String_t *fn() {
		// 組立に使った領域は事後解放
	String_t *str = String.New("outer");
	defer {
		Console.WriteLine(String.New("deleting str"));
		String.Delete(str);
		Console.WriteLine(String.New("deleted str"));
	} set

	retrieve {
			// 組立られた領域は解放されずアドレスを返却
		return String.Concat(str, String.New(" innner"));
	} ret
}

void main() $_ {
	Console.WriteLine(fn());
} _$
