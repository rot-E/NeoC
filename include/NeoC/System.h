#pragma once

#include <unistd.h>

#include "NeoC/Base/Exception/Signal.h"
#include "NeoC/Base/Exception/Exception.h"

class _System {
	private void (* _Setup)();

	public final SignalCode_t Exception;

	public void (* Sleep)(uint32_t sec) throws (System.Exception);
	public void (* USleep)(useconds_t usec) throws (System.Exception);

	private final fd_set _State;
	public bool (* Keystroked)();
} _System;

extern _System System;
