#pragma once

#include "String.h"

typedef struct {
	void (* Startup)();
} _S;

extern _S S;

#define $NeoC 				\
	{						\
		S.Startup();

#define NeoC$				\
	}
