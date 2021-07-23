#include "NeoC/Environment.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/Exception/Exception.h"
#include "NeoC/Collection.h"
#include "NeoC/Collection/Tuple.h"

void main() $_ {
	/* 4-tuple生成 */
	Tuple_t *tp = Tuple.New(4);

	/* 領域確保/値配置 */
	String_t *s = String.New(u8"test string");
	int32_t *i = $(int32_t, 42);
	double *d = $(double, 3.14);

	/* アドレス格納 */
	tp->Set(tp, 0, s);
	tp->Set(tp, 1, i);
	tp->Set(tp, 2, d);

	for (int32_t i = 0; i < tp->GetSize(tp); i++) {
		if (i == 0)
			Console.Write(String.NewFormat(
				"(\"%s\", ",
				String.Unpack( tp->Get(tp, i) )
			));
		if (i == 1)
			Console.Write(String.NewFormat(
				"%d, ",
				*(int32_t *)( tp->Get(tp, i) )
			));
		if (i == 2)
			Console.WriteLine(String.NewFormat(
				"%f )",
				*(double *)( tp->Get(tp, i) )
			));
	}

	/* Tuple解放 */
	Tuple.Delete(tp);
} _$
