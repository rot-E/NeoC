#pragma once

/* ------------------------------------------------------ */
/* NeoC環境開始宣言 */
#define $NeoC { _S._Setup();

/* NeoC環境終了宣言 */
#define NeoC$ }
/* ------------------------------------------------------ */

#include "Annotation.h"
#include "Exception.h"
#include "CSI.h"
#include "SGR.h"
#include "String.h"
#include "System.h"

typedef struct {
	private void (* _Setup)();
} __S;

extern __S _S;
