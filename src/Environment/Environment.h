#pragma once

/* ------------------------------------------------------ */
/* 環境開始宣言 */
#define $_ { _Environment._Setup(); _Exception.Try(({ void Try()

/* 環境終了宣言 */
#define _$ ; Try; }), ({ void Catch(Signal_t *sig) { _Environment._MAIN_EXCEPTION_HANDLER(sig); }; Catch; }), ({ void Finally() {}; Finally; })); }
/* ------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>

#include "Annotation.h"
#include "Exception/Exception.h"
#include "Defer.h"
#include "SPEC/CSI.h"
#include "SPEC/SGR.h"
#include "String.h"
#include "System.h"
#include "Socket.h"
#include "Exception/Signal.h"

typedef struct {
	private void (* _Setup)();

	private void (* _MAIN_EXCEPTION_HANDLER)(Signal_t *);
} __Environment;

extern __Environment _Environment;
