#pragma once

/* ------------------------------------------------------ */
/* signal定義 */
#define signal = _Exception.GenerateSignal()

#define sign(EX) int32_t EX = _Exception.GenerateSignal()

/* 例外処理 */
// 危うい？
#define try _Exception.Try(({ void Try()

#define throw(EX) _Exception.Throw(EX)

#define catch(EX) ; Try; }), ({ void Catch() { const uint32_t sig = _Exception.ElicitSignal(); if (sig == EX)

#define catchN(EX) else if (sig == EX)

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

#include "Annotation.h"
#include "Error.h"
#include "Memory.h"

typedef uint32_t Signal_t;

typedef struct {
	private jmp_buf _Context;
	private Signal_t _Signal;

	/* データ持たせたい場合ここに追記;
	// private void *_Data;
	 *
	 * アクセッサへのポインタ変数を_Context型に定義 */
} Context_t;

typedef struct {
	public Context_t *(* New)();
	public void (* Delete)(Context_t *);
} _Context;

extern _Context Context;


typedef struct {
	private void (* _Setup)();

	private uint32_t _SIGNAL_MAX;
	public Signal_t (* GenerateSignal)();

	private Context_t *_Context;
	private int32_t _Nest;
	private int32_t _NEST_MAX;

	public void (* Try)(const void (* Try)(), const void (* Catch)(), const void (* Finally)());
	public void (* Throw)(const Signal_t);
	public Signal_t (* ElicitSignal)();
} __Exception;

extern __Exception _Exception;
