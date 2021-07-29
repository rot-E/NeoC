#pragma once

#include <stdlib.h>
#include "NeoC/Base/Object.h"
#include "NeoC/Base/Exception/Signal.h"
#include "NeoC/Base/Exception/Exception.h"
#include "NeoC/Type/PrimitiveWrapper.h"

class Bit_t {
	implements (PrimitiveWrapper_i);

	private int32_t _Bit;

	public int32_t (* Unpack)(self_t *);
	public actualize uint8_t *(* GetExpr)(self_t *);

	public self_t *(* Not)(self_t *);
	public self_t *(* And)(self_t *, self_t *);
	public self_t *(* Or)(self_t *, self_t *);
	public self_t *(* Xor)(self_t *, self_t *);
	public self_t *(* Nand)(self_t *, self_t *);
	public self_t *(* Nor)(self_t *, self_t *);
} Bit_t;

class _Bit {
	private void (* _Setup)();
	public final SignalCode_t Exception;

	public Bit_t *(* Init)(Bit_t *, const int32_t b);
	public Bit_t *(* New)(const int32_t b) throws (Bit.Exception);
	public void (* Delete)(Bit_t *);

	public int32_t (* Unpack)(self_t *);
	public actualize uint8_t *(* GetExpr)(self_t *);

	public self_t *(* Not)(self_t *);
	public self_t *(* And)(self_t *, self_t *);
	public self_t *(* Or)(self_t *, self_t *);
	public self_t *(* Xor)(self_t *, self_t *);
	public self_t *(* Nand)(self_t *, self_t *);
	public self_t *(* Nor)(self_t *, self_t *);
} _Bit;

extern _Bit Bit;
