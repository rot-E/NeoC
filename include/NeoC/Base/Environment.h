#pragma once

/* ------------------------------------------------------ */
/* 環境開始宣言 */
#define $_ { _Environment._Setup(); _Exception.Try(({ void Try()

/* 環境終了宣言 */
#define _$ ; Try; }), ({ void Catch(Signal_t *sig) { _Environment._MAIN_EXCEPTION_HANDLER(sig); }; Catch; }), ({ void Finally() {}; Finally; })); }
/* ------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include "NeoC/Base/Object.h"

/// #include "NeoC/Base/Exception/Signal.h"
#include "NeoC/Base/Exception/Exception.h"
#include "NeoC/Base/Defer.h"

#include "NeoC/SPEC/CSI.h"
#include "NeoC/SPEC/SGR.h"

#include "NeoC/String.h"
#include "NeoC/System.h"
#include "NeoC/Socket.h"

/// #include "NeoC/Collection/Collection.h"
//#include "NeoC/Collection/Tuple.h"
#include "NeoC/Collection/List.h"
//#include "NeoC/Collection/Stack.h"
#include "NeoC/Collection/Queue.h"
#include "NeoC/Collection/Map.h"
//#include "NeoC/Collection/Set.h"

class __Environment {
	private void (* _Setup)();

	private void (* _MAIN_EXCEPTION_HANDLER)(Signal_t *);
} __Environment;

extern __Environment _Environment;
