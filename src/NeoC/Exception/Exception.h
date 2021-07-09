#pragma once

/* ------------------------------------------------------ */
/* signal定義 */
#define signal = E.GenerateSignal()

#define sign(EX) int32_t EX = E.GenerateSignal()

/* 例外処理 */
#define try E.Try(({ void Try() {

#define throw(EX) E.Throw(EX)

#define catch(EX) }; Try; }), ({ void Catch() { const int32_t sig = E.ElicitSignal(); if (sig == EX) {

#define catchN(EX) } else if (sig == EX) {

#define catchAll } else {

#define finally }}; Catch; }), ({ void Finally() {

#define end }; Finally; }));

#define endX }}; Catch; }), ({ void Finally() {}; Finally; }));

/* 函数宣言定義時補足宣言 */
#define throws(...)
/* ------------------------------------------------------ */

#include <stdint.h>
#include <setjmp.h>
#include <stdlib.h>

#include "Setup.h"

#include "Memory.h"

typedef struct {
	jmp_buf _Context;
	int32_t _Signal;
	/* データ持たせたい場合ここに追記;
	// void *_Data;
	 *
	 * アクセッサへのポインタ変数を_Context型に定義 */
} Context_t;

typedef struct {
	Context_t *(* New)();
	void (* Delete)(Context_t *);
} _Context;

extern _Context Context;


typedef struct {
	void (* _Setup)();

	int32_t _SIGNAL_MAX;
	int32_t (* GenerateSignal)();

	int32_t _Nest;
	int32_t _NEST_MAX;
	void (* _HANDLER)();
	Context_t *_Context;

	void (* Try)(const void (* Try)(), const void (* Catch)(), const void (* Finally)());
	void (* Throw)(const int32_t);
	int32_t (* ElicitSignal)();
} _E;

extern _E E;
