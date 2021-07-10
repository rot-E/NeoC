#pragma once

/* ------------------------------------------------------ */
/* NeoC環境開始宣言 */
#define $NeoC { _S._Setup(); E.Try(({ void Try() {

/* NeoC環境終了宣言 */
#define NeoC$ }; Try; }), ({ void Catch() { _S._HANDLER(); }; Catch; }), ({ void Finally() {}; Finally; })); }
/* ------------------------------------------------------ */

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

	private void (* _HANDLER)();
} __S;

extern __S _S;
