#include "NeoC/Environment.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"

#include "Derived.h"

void main() $_ {
	Derived_t *der = Derived.New();

	Console.WriteLine(String.NewFormat(
		"%d",
		der->GetNum(der)
		// 代替可能: Derived.GetNum(der, 3)
	));

	der->AddNum(der, 3);
	// 代替可能: Derived.AddNum(der, 3);

	Console.WriteLine(String.NewFormat(
		"%d",
		der->GetNum(der)
	));
} _$
