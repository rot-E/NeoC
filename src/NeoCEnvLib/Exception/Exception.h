#pragma once

#include <stdint.h>
#include <setjmp.h>

#include "Memory.h"

typedef struct E_t {
	jmp_buf _Context;
	int32_t _Signal;
} E_t;

typedef struct {
	int32_t _SIGNAL_MAX;

	int32_t (* GenerateSignal)();

	E_t *(* Begin)();
	void (* End)(E_t *);

	void (* Try)(E_t *, void (* Code)(), void (* Catch)(), void (* Finally)());
	void (* Throw)(E_t *, int32_t);
	int32_t (* ElicitSignal)(E_t *);
} _E;

extern _E E;

#define try												\
	E_t *cxt = E.Begin();								\
	E.Try(cxt, ({										\
		void Code() {

#define throw(X);										\
			E.Throw(cxt, X);

#define catch(X)										\
		};												\
		Code;											\
	}), ({												\
		void Catch() {									\
			int32_t sig = E.ElicitSignal(cxt);			\
			if (sig == X) {

#define catchN(X)										\
			} else if (sig == X) {

#define catchAll										\
			} else {

#define finally											\
			}											\
		};												\
		Catch;											\
	}), ({												\
		void Finally() {

#define end												\
		};												\
		Finally;										\
	}));												\
	E.End(cxt);
