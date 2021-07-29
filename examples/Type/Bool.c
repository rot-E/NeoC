#include <NeoC/Base/Environment.h>
#include <NeoC/Type/Bool.h>
#include <NeoC/Type/String.h>
#include <NeoC/Console.h>

void main() $_ {
	Bool_t *b1 = Bool.New(true);
	Bool_t *b2 = Bool.New(false);

	Console.WriteLine(String.NewFormat(
		"~%s(%d) = %s(%d)",
		Bool.ToString(b1),
		Bool.Unpack(b1),
		Bool.ToString(Bool.Not(b1)),
		Bool.Unpack(Bool.Not(b1))
	));

	Console.WriteLine(String.NewFormat(
		"%s * %s = %s",
		Bool.ToString(b1),
		Bool.ToString(b2),
		Bool.ToString(Bool.And(b1, b2))
	));

	Console.WriteLine(String.NewFormat(
		"%s + %s = %s",
		Bool.ToString(b1),
		Bool.ToString(b2),
		Bool.ToString(Bool.Or(b1, b2))
	));

	Console.WriteLine(String.NewFormat(
		"%s ~* %s = %s",
		Bool.ToString(b1),
		Bool.ToString(b2),
		Bool.ToString(Bool.Nand(b1, b2))
	));

	Console.WriteLine(String.NewFormat(
		"%s ~+ %s = %s",
		Bool.ToString(b1),
		Bool.ToString(b2),
		Bool.ToString(Bool.Nand(b1, b2))
	));
} _$
