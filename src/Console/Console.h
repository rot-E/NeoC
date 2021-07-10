#pragma once

#include <stdio.h>

#include "Annotation.h"
#include "SPEC/CC.h"
#include "SPEC/CSI.h"
#include "SPEC/SGR.h"
#include "String.h"

typedef struct {
	public void (* SetState)(uint8_t *escSeq);
	public void (* SetColour)(uint8_t *colour);
	public void (* SetDefaultColour)();

	public void (* Write)(String_t *str);
	public void (* WriteChar)(uint8_t ch);
	public void (* WriteLine)(String_t *str);
	public void (* NewLine)();
	public void (* WriteColourLine)(uint8_t *colour, String_t *str);

	public void (* WriteErrorLine)(String_t *str);
	public void (* WriteColourErrorLine)(uint8_t *colour, String_t *str);

	public void (* Erase)();
	public void (* ErasePrevLine)();

	undefined void (* WriteTop)(String_t *str);
	undefined void (* WriteTopLine)(String_t *str);
} _Console;

extern _Console Console;
