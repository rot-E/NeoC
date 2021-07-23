#pragma once

/* ------------------------------------------------------ */
/* 環境開始宣言 */
#define $_ { _Environment._Setup(); _Exception.Try(({ void Try()

/* 環境終了宣言 */
#define _$ ; Try; }), ({ void Catch(Signal_t *sig) { _Environment._MAIN_EXCEPTION_HANDLER(sig); }; Catch; }), ({ void Finally() {}; Finally; })); }
/* ------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>

#include "NeoC/Annotation.h"
#include "NeoC/Exception/Exception.h"
#include "NeoC/Defer.h"
#include "NeoC/SPEC/CSI.h"
#include "NeoC/SPEC/SGR.h"
#include "NeoC/String.h"
#include "NeoC/System.h"
#include "NeoC/Socket.h"
#include "NeoC/Collection/Tuple.h"
#include "NeoC/Collection/Map.h"
#include "NeoC/Collection/List.h"
#include "NeoC/Collection/Set.h"
#include "NeoC/Collection/Stack.h"
#include "NeoC/Collection/Queue.h"
#include "NeoC/Exception/Signal.h"

typedef struct {
	private void (* _Setup)();

	private void (* _MAIN_EXCEPTION_HANDLER)(Signal_t *);
} __Environment;

extern __Environment _Environment;
