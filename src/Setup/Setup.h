#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "Annotation.h"
#include "Exception.h"
#include "SPEC/CSI.h"
#include "SPEC/SGR.h"
#include "String.h"
#include "System.h"

typedef struct {
	private void (* _Setup)();

	private void (* _MAIN_EXCEPTION_HANDLER)();
} __S;

extern __S _S;
