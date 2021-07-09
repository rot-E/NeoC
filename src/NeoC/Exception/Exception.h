#pragma once

#include <stdint.h>
#include <setjmp.h>

#include "Memory.h"

typedef struct {
	jmp_buf _Context;
	int32_t _Signal;

	int32_t _SIGNAL_MAX;
	int32_t (* GenerateSignal)();

	void (* Try)(const void (* Try)(), const void (* Catch)(), const void (* Finally)());
	void (* Throw)(const int32_t);
	int32_t (* ElicitSignal)();
} _E;

extern _E E;

#define try E.Try(({ void Try() {

#define throw(X) E.Throw(X)

#define catch(X) }; Try; }), ({ void Catch() { const int32_t sig = E.ElicitSignal(); if (sig == X) {

#define catchN(X) } else if (sig == X) {

#define catchAll } else {

#define finally }}; Catch; }), ({ void Finally() {

#define end }; Finally; }));
