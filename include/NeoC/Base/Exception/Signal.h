#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "NeoC/Base/Object.h"

typedef uint32_t SignalCode_t;

class Signal_t {
	/// extends (Object_t);

	private SignalCode_t _Code;
	private uint8_t *_Message;

	/// public inherit uint8_t *(* GetExpr)(self_t *);

	public SignalCode_t (* GetSignalCode)(self_t *);
	public bool (* MessageExists)(self_t *);
	public void (* SetMessage)(self_t *, const uint8_t *message);
	public uint8_t *(* GetMessage)(self_t *);
} Signal_t;

class _Signal {
	/// private void (* _Setup)();

	public Signal_t *(* Init)(Signal_t *, SignalCode_t code);
	public Signal_t *(* New)(SignalCode_t code);
	public Signal_t *(* Build)(SignalCode_t code, uint8_t *message);
	public void (* Delete)(Signal_t *);

	/// public inherit uint8_t *(* GetExpr)(self_t *);

	public SignalCode_t (* GetSignalCode)(self_t *);
	public bool (* MessageExists)(self_t *);
	public void (* SetMessage)(self_t *, const uint8_t *message);
	public uint8_t *(* GetMessage)(self_t *);
} _Signal;

extern _Signal Signal;
