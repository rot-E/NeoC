#pragma once

#include <unistd.h>

#include "Exception/Signal.h"
#include "Exception/Exception.h"

typedef struct {
	private void (* _Setup)();

	public final SignalCode_t Exception;

	public void (* Sleep)(uint32_t sec) throws (System.Exception);
	public void (* USleep)(useconds_t usec) throws (System.Exception);
} _System;

extern _System System;
