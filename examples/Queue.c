#include "NeoC/Environment.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/Exception/Exception.h"
#include "NeoC/Collection.h"
#include "NeoC/Collection/Queue.h"

void main() $_ {
	/* Queue生成 */
	Queue_t *q = Queue.New() in (String_t *);

	Console.WriteLine(String.NewFormat(u8"Empty? %d", q->IsEmpty(q)));
	Console.NewLine();

	/* アドレス格納 */
	q->Enq(q, String.New(u8"test string"));
	q->Enq(q, String.New(u8"test string 2"));
	q->Enq(q, String.New(u8"test string 3"));
	Console.WriteLine(String.NewFormat(u8"Empty? %d", q->IsEmpty(q)));

	Console.WriteLine(String.NewFormat(
		"%d: %s (Peek)",
		q->GetLength(q),
		String.Unpack(q->Peek(q))
	));
	Console.WriteLine(String.NewFormat(
		"%d: %s (Peek)",
		q->GetLength(q),
		String.Unpack(q->Peek(q))
	));
	Console.WriteLine(String.NewFormat(
		"%d: %s (Peek)",
		q->GetLength(q),
		String.Unpack(q->Peek(q))
	));

	while (!q->IsEmpty(q)) {
		const int32_t i = q->GetLength(q);
		Console.WriteLine(String.NewFormat(
			"%d: %s",
			i, // ここでGetLengthを呼ぶと次のDeq後の値が返される
			String.Unpack(q->Deq(q))
		));
	}
	Console.NewLine();

	/* 再格納 */
	q->Enqueue(q, String.New(u8"あいうえお"));
	q->Enqueue(q, String.New(u8"かきくけこ"));
	q->Enqueue(q, String.New(u8"さしすせそ"));

	while (!q->IsEmpty(q)) {
		Console.WriteLine(String.NewFormat(
			"%d: %s",
			q->GetLength(q),
			String.Unpack(q->Dequeue(q))
		));
	}
	Console.NewLine();

	/* Queue解放 */
	Queue.Delete(q);


	/* 大量確保/解放 */
	q = Queue.New() in (String_t *);

	const int32_t SIZE = 5000;
	for (int32_t i = 0; i < SIZE; i++) {
		q->Enq(q, String.NewFormat(u8"STR-%d", i));

		if (i % Queue._ALLOCATION_BLOCK_SIZE == 0)
			Console.WriteLine(String.NewFormat("Idx: %d, Size: %d", i, q->_Size));
	}

	for (int32_t i = SIZE - 2; 0 <= i; i--) {
		q->Deq(q);

		if ((i - 1) % List._ALLOCATION_BLOCK_SIZE == 0)
			Console.WriteLine(String.NewFormat("Idx: %d, Size: %d", i, q->_Size));
	}

	Console.WriteLine(String.NewFormat(
		"%s", String.Unpack(q->Deq(q))
	));

	/* Queue解放 */
	Queue.Delete(q);
} _$
