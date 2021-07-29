#include <NeoC/Base/Environment.h>
#include <NeoC/Type/Bool.h>
#include <NeoC/Type/String.h>
#include <NeoC/Console.h>

void main() $_ {
	Bool_t *b1 = Bool.New(true);
	Bool_t *b2 = Bool.New(false);

	Console.WriteLine(String.NewFormat(
		"~%s(%d) = %s(%d)",
		Bool.GetExpr(b1),
		Bool.Unpack(b1),
		Bool.GetExpr(Bool.Not(b1)),
		Bool.Unpack(Bool.Not(b1))
	));

	Console.WriteLine(String.NewFormat(
		"%s * %s = %s",
		Bool.GetExpr(b1),
		Bool.GetExpr(b2),
		Bool.GetExpr(Bool.And(b1, b2))
	));

	Console.WriteLine(String.NewFormat(
		"%s + %s = %s",
		Bool.GetExpr(b1),
		Bool.GetExpr(b2),
		Bool.GetExpr(Bool.Or(b1, b2))
	));

	Console.WriteLine(String.NewFormat(
		"%s ~* %s = %s",
		Bool.GetExpr(b1),
		Bool.GetExpr(b2),
		Bool.GetExpr(Bool.Nand(b1, b2))
	));

	Console.WriteLine(String.NewFormat(
		"%s ~+ %s = %s",
		Bool.GetExpr(b1),
		Bool.GetExpr(b2),
		Bool.GetExpr(Bool.Nand(b1, b2))
	));
} _$
