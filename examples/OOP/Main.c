#include <NeoC/Base/Environment.h>
#include <NeoC/String.h>
#include <NeoC/Console.h>

#include "Derived.h"

void f(Base_t *b) {
	Console.WriteLine(String.NewFormat(
		u8"%d",
		b->GetNum(b)
	));
}

void g(self_t *b) {
	Console.WriteLine(String.NewFormat(
		u8"%d",
		Base.GetNum(b)
	));
}

void main() $_ {
	Derived_t *der = Derived.New();

	Console.WriteLine(String.NewFormat(
		u8"%d",
		der->GetNum(der)
	));

	Console.WriteLine(String.NewFormat(
		u8"%d",
		Derived.GetNum(der)
	));

	der->AddNum(der, 3);
	Derived.AddNum(der, 6);

	Console.WriteLine(String.NewFormat(
		u8"%d",
		der->GetNum(der)
	));

	f(act(Base_t, der));
	g(der);
} _$
