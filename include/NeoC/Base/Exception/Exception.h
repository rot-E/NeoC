#pragma once

/* ------------------------------------------------------ */
/* signal定義 */
#define signal = _Exception.AssignSignalCode()

#define sign(EX) SignalCode_t EX = _Exception.AssignSignalCode()

/* 例外処理 */
// 危うい？
#define try _Exception.Try(({ void Try()

#define throw(EX) _Exception.Throw(EX)

#define catch(EX) ; Try; }), ({ void Catch(Signal_t *sig) { if (Signal.GetSignalCode(sig) == EX)

#define elicit() sig

#define catchN(EX) else if (Signal.GetSignalCode(sig) == EX)

#define catchAll else

#define fin }; Catch; }), ({ void Finally() {}; Finally; }));

#define finally }; Catch; }), ({ void Finally()

#define end ; Finally; }));

/* 函数宣言定義時補足宣言 */
#define throws(...)
/* ------------------------------------------------------ */

#include <stdint.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "NeoC/Base/Object.h"
#include "NeoC/Base/Error.h"
#include "NeoC/Base/Memory.h"
#include "NeoC/Base/Exception/Signal.h"
#include "NeoC/Base/Defer.h"

class Context_t {
	extends (Object_t);

	private jmp_buf _Context;
	private Signal_t *_Signal;

	public uint8_t *(* GetExpr)(self_t *);
} Context_t;

class _Context {
	public Context_t *(* Init)(Context_t *);
	public Context_t *(* New)();
	public void (* Delete)(Context_t *);

	public uint8_t *(* GetExpr)(self_t *);
} _Context;

extern _Context Context;


class __Exception {
	private void (* _Setup)();

	private uint32_t _SIGNAL_CODE_MAX;
	public SignalCode_t (* AssignSignalCode)();

	private Context_t *_Context;
	private int32_t _Nest;
	private int32_t _NEST_MAX;

	public void (* Try)(const void (* Try)(), const void (* Catch)(Signal_t *), const void (* Finally)());
	public void (* Throw)(Signal_t *);
} __Exception;

extern __Exception _Exception;
