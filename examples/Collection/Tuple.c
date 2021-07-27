#include <NeoC/Base/Environment.h>
#include <NeoC/String.h>
#include <NeoC/Console.h>
#include <NeoC/Collection/Collection.h>
#include <NeoC/Collection/Tuple.h>

void main() $_ {
	/* 4-tuple生成 */
	Tuple_t *tp = Tuple.New(4) in (String_t *, int32_t *, double *);

	/* アドレス格納 */
	tp->Set(tp, 0, String.New(u8"test string"));
	tp->Set(tp, 1, $(int32_t, 42));
	tp->Set(tp, 2, $(double, 3.14));

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
