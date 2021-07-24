#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "NeoC/Annotation.h"
#include "NeoC/Object.h"
#include "NeoC/Memory.h"

typedef uint32_t SignalCode_t;

class Signal_t {
	private SignalCode_t _Code;
	private uint8_t *_Message;
} Signal_t;

class _Signal {
	public Signal_t *(* New)(SignalCode_t code);
	public Signal_t *(* Build)(SignalCode_t code, uint8_t *message);
	public void (* Delete)(Signal_t *);

	public SignalCode_t (* GetSignalCode)(Signal_t *);

	public bool (* MessageExists)(Signal_t *);
	public void (* SetMessage)(Signal_t *, const uint8_t *message);
	public uint8_t *(* GetMessage)(Signal_t *);
} _Signal;

extern _Signal Signal;
