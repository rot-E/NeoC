#include "NeoC/Environment.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"

#include "Derived.h"

void main() $_ {
	Derived_t *der = Derived.New();

	Console.WriteLine(String.NewFormat(
		"%d",
		der->GetNum(der)
	));

	Console.WriteLine(String.NewFormat(
		"%d",
		Derived.GetNum(der)
	));

	der->AddNum(der, 3);
	Derived.AddNum(der, 6);

	Console.WriteLine(String.NewFormat(
		"%d",
		der->GetNum(der)
	));
} _$
