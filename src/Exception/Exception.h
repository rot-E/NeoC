#pragma once

/* ------------------------------------------------------ */
/* signal定義 */
#define signal = E.GenerateSignal()

#define sign(EX) int32_t EX = E.GenerateSignal()

/* 例外処理 */
#define try E.Try(({ void Try() {

#define throw(EX) E.Throw(EX)

#define catch(EX) }; Try; }), ({ void Catch() { const uint32_t sig = E.ElicitSignal(); if (sig == EX) {

#define catchN(EX) } else if (sig == EX) {

#define catchAll } else {

#define end }}; Catch; }), ({ void Finally() {}; Finally; }));

#define finally }}; Catch; }), ({ void Finally() {

#define endX }; Finally; }));

/* 函数宣言定義時補足宣言 */
#define throws(...)
/* ------------------------------------------------------ */

#include <stdint.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

#include "Annotation.h"
#include "Setup.h"
#include "Memory.h"

typedef uint32_t Signal_t;

typedef struct {
	private jmp_buf _Context;
	private int32_t _Signal;

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
	public uint32_t (* GenerateSignal)();

	private Context_t *_Context;
	private int32_t _Nest;
	private int32_t _NEST_MAX;
	protected void (* _HANDLER)();

	public void (* Try)(const void (* Try)(), const void (* Catch)(), const void (* Finally)());
	public void (* Throw)(const Signal_t);
	public Signal_t (* ElicitSignal)();
} _E;

extern _E E;
