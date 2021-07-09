#pragma once

#include "CSI.h"
#include "SGR.h"
#include "String.h"

typedef struct {
	void (* _Setup)();
} __S;

extern __S _S;

#define $NeoC { _S._Setup();

#define NeoC$ }
