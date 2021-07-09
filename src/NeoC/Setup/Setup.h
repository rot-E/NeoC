#pragma once

/* ------------------------------------------------------ */
/* 環境下宣言 */
#define $NeoC { _S._Setup();

#define NeoC$ }
/* ------------------------------------------------------ */

#include "Exception.h"
#include "CSI.h"
#include "SGR.h"
#include "String.h"

typedef struct {
	void (* _Setup)();
} __S;

extern __S _S;
