#include <NeoC/Base/Environment.h>
#include <NeoC/Type/Bit.h>
#include <NeoC/Type/String.h>
#include <NeoC/Console.h>

void main() $_ {
	Bit_t *b1 = Bit.New(1);
	Bit_t *b2 = Bit.New(0);

	Console.WriteLine(String.NewFormat(
		"~%s(%d) = %s(%d)",
		Bit.GetExpr(b1),
		Bit.Unpack(b1),
		Bit.GetExpr(Bit.Not(b1)),
		Bit.Unpack(Bit.Not(b1))
	));

	Console.WriteLine(String.NewFormat(
		"%s * %s = %s",
		Bit.GetExpr(b1),
		Bit.GetExpr(b2),
		Bit.GetExpr(Bit.And(b1, b2))
	));

	Console.WriteLine(String.NewFormat(
		"%s + %s = %s",
		Bit.GetExpr(b1),
		Bit.GetExpr(b2),
		Bit.GetExpr(Bit.Or(b1, b2))
	));

	Console.WriteLine(String.NewFormat(
		"%s ^ %s = %s",
		Bit.GetExpr(b1),
		Bit.GetExpr(b2),
		Bit.GetExpr(Bit.Xor(b1, b2))
	));

	Console.WriteLine(String.NewFormat(
		"%s ~* %s = %s",
		Bit.GetExpr(b1),
		Bit.GetExpr(b2),
		Bit.GetExpr(Bit.Nand(b1, b2))
	));

	Console.WriteLine(String.NewFormat(
		"%s ~+ %s = %s",
		Bit.GetExpr(b1),
		Bit.GetExpr(b2),
		Bit.GetExpr(Bit.Nand(b1, b2))
	));
} _$
